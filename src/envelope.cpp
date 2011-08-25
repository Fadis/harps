/***************************************************************************
 *   Copyright (C) 2009 by Naomasa Matsubayashi   *
 *   harps@quaternion.sakura.ne.jp   *
 *                                                                         *
 *   All rights reserved.                                                  *
 *                                                                         *
 *   Redistribution and use in source and binary forms, with or without    *
 *   modification, are permitted provided that the following conditions    *
 *   are met:                                                              *
 *     * Redistributions of source code must retain the above copyright    *
 *       notice, this list of conditions and the following disclaimer.     *
 *     * Redistributions in binary form must reproduce the above copyright *
 *       notice, this list of conditions and the following disclaimer in   *
 *       the documentation and/or other materials provided with the        *
 *       distribution.                                                     *
 *   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   *
 *   "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     *
 *   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR *
 *   A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  *
 *   OWNER OR                                                              *
 *   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, *
 *   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,   *
 *   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR    *
 *   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY   *
 *   OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT          *
 *   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE *
 *   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  *
 ***************************************************************************/

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/shared_buffer.hpp>
#include <harps/config.hpp>
#include <harps/compornent/envelope2.hpp>

#include <boost/array.hpp>

namespace harps {
  namespace compornent {
    /*!
     * 行列をLU分解します。
     * \param _lu 行列
     * \param _lu ピボット
     * \return LU分解が成功したらtrue 失敗したらfalse
     */
    bool lu( float *_lu, unsigned int *_index ) {
      typedef float ElementType;
      static const int element_count = 3;
      ElementType weight[ element_count ];
      int row;
      for( row = 0; row != element_count; row++ ) {
        ElementType max_in_row = 0.0;
        int col;
        for( col = 0; col != element_count; col++ ) {
          ElementType distance = _lu[ row * element_count + col ];
          if( distance < 0.0 )
            distance = -distance;
          if( distance > max_in_row )
            max_in_row = distance;
        }
        if( max_in_row == 0.0 )
          return false;
        weight[ row ] = 1.0 / max_in_row;
      }
      int col;
      for( col = 0; col != element_count; col++ ) {
        for( row = 0; row != col; row++ ) {
          ElementType sum = _lu[ row * element_count + col ];
          int index;
          for( index = 0; index != row; index++ )
            sum -= _lu[ row * element_count + index ] * _lu[ index * element_count + col ];
          _lu[ row * element_count + col ] = sum;
        }
        int max_rated_row = 0.0;
        ElementType max_rate = 0.0;
        for( row = col; row != element_count; row++ ) {
          ElementType sum = _lu[ row * element_count + col ];
          int index;
          for( index = 0; index != col; index++ )
            sum -= _lu[ row * element_count + index ] * _lu[ index * element_count + col ];
          _lu[ row * element_count + col ] = sum;
          if( sum < 0.0 )
            sum = -sum;
          ElementType rate = weight[ row ] * sum;
          if( rate >= max_rate ){
            max_rate = rate;
            max_rated_row = row;
          }
        }
        row = col;
        if( row != max_rated_row ) {
          int index;
          for( index = 0; index != element_count; index++ ) {
            {
              ElementType temp = _lu[ max_rated_row * element_count + index ];
              _lu[ max_rated_row * element_count + index ] = _lu[ row * element_count + index ];
              _lu[ row * element_count + index ] = temp;
            }
          }
          {
            unsigned int temp = _index[ row ];
            _index[ row ] = _index[ max_rated_row ];
            _index[ max_rated_row ] = temp;
          }
          weight[ max_rated_row ] = weight[ row ];
        }
        if( _lu[ row * element_count + row ] == 0.0 )
          return false;
        if( row != element_count - 1 ) {
          ElementType temp = 1.0 / _lu[ row * element_count + row ];
          for( row = col + 1; row < element_count; row++ )
            _lu[ row * element_count + col ] *= temp;
        }
      }
      return true;
    }
    
    /*!
     * 逆行列を求めます。
     * \param _dest 逆行列
     * \param _source_orig もとの行列
     * \return 逆行列が存在するならtrue 存在しないならfalse
     */
    bool inverse( float *_dest, const float *_source_orig ) {
      typedef float ElementType;
      static const int element_count = 3;
      unsigned int row_index[ element_count ];
      float _source[ element_count * element_count ];
      int index;
      for( index = 0; index != element_count; index++ )
        row_index[ index ] = index;
      for( index = 0; index != element_count * element_count; index++ )
        _source[ index ] = _source_orig[ index ];
      for( index = 0; index != element_count * element_count; index++ )
        _dest[ index ] = 0;

      if( !lu( _source, row_index ) )
        return false;

      int row;
      int col;
      for( index = 0; index != element_count; index++ ) {
        for( row = 0; row != element_count; row++ ) {
          int pivot = row_index[ row ];
          ElementType sum = ( ( pivot == index ) ? 1 : 0 );
          for( col = 0; col != row; col++ )
            sum -= _source[ row * element_count + col ] * _dest[ col * element_count + index ];
          _dest[ row * element_count + index ] = sum;
        }
        for( row = element_count - 1; row != -1; row-- ) {
          ElementType sum = _dest[ row * element_count + index ];
          for( col = row + 1; col != element_count; col++ )
            sum -= _source[ row * element_count + col ] * _dest[ col * element_count + index ];
          _dest[ row * element_count + index ] = sum / _source[ row * element_count + row ];
        }
      }
      return true;
    }

    // ax + b = y
    void calcCoef(
      float &_a, float &_b,
      float _x0, float _y0,
      float _x1, float _y1
    ) {
      _a = ( _y1 - _y0 ) / ( _x1 - _x0 );
      _b = -_a * _x1 + _y1;
    }

    // ax^2 + bx + c = y
    void calcCoef(
      float &_a, float &_b, float &_c,
      float _x0, float _y0,
      float _x1, float _y1,
      float _x2, float _y2
    ) {
      if( _x0 < _x1 ) {
        if( _x1 < _x2 ) {
          float matrix[ 3 * 3 ];
          float imatrix[ 3 * 3 ];
          matrix[ 0 * 3 + 0 ] = _x0 * _x0; matrix[ 0 * 3 + 1 ] = _x0; matrix[ 0 * 3 + 2 ] = 1;
          matrix[ 1 * 3 + 0 ] = _x1 * _x1; matrix[ 1 * 3 + 1 ] = _x1; matrix[ 1 * 3 + 2 ] = 1;
          matrix[ 2 * 3 + 0 ] = _x2 * _x2; matrix[ 2 * 3 + 1 ] = _x2; matrix[ 2 * 3 + 2 ] = 1;
          inverse( imatrix, matrix );
          _a = imatrix[ 0 * 3 + 0 ] * _y0 + imatrix[ 0 * 3 + 1 ] * _y1 + imatrix[ 0 * 3 + 2 ] * _y2;
          _b = imatrix[ 1 * 3 + 0 ] * _y0 + imatrix[ 1 * 3 + 1 ] * _y1 + imatrix[ 1 * 3 + 2 ] * _y2;
          _c = imatrix[ 2 * 3 + 0 ] * _y0 + imatrix[ 2 * 3 + 1 ] * _y1 + imatrix[ 2 * 3 + 2 ] * _y2;
        }
        else { // x1 = x2
          _a = 0.0f;
          calcCoef( _b, _c, _x0, _y0, _x1, _y1 );
        }
      }
      else { // x0 = x1
        if( _x1 < _x2 ) {
          _a = 0.0f;
          calcCoef( _b, _c, _x1, _y1, _x2, _y2 );
        }
        else { // x0 = x1 = x2
          _a = 0.0f;
          _b = 0.0f;
          _c = _y2;
        }
      }
    }
  }
}