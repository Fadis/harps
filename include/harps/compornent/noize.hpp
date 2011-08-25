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


#ifndef HARPS_COMPORNENT_NOIZE
#define HARPS_COMPORNENT_NOIZE

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/shared_buffer.hpp>
#include <harps/config.hpp>

#include <boost/random.hpp>
#include <boost/array.hpp>

#include <complex>
#include <utility>
#include <cmath>
#include <cstring>

namespace harps {
  namespace compornent {
    /*!
    * 高速フーリエ変換を行うためのクラスです。
     */
    template< size_t size >
    class FFT {
      public:
        FFT ( int _inverse ) : inverse ( _inverse ) {
          float direction = -1.0f;
          if ( inverse )
            direction = 1.0f;

          int counter;
          for ( counter = 0; counter != size; counter++ ) {
            float angle =
              direction * 2.0f * static_cast< float > ( M_PI ) *
              static_cast< float > ( counter ) / static_cast< float > ( size );
            w[ counter ] = std::complex< float > ( cosf ( angle ), sinf ( angle ) );
          }
        }
        void operator() ( float *_buffer ) {
          boost::array< std::complex< float >, size > complex_buffer;
          int counter;
          for ( counter = 0; counter != size; counter++ )
            complex_buffer[ counter ] = std::complex< float > ( _buffer[ counter ], 0.0f );
          ( *this ) ( & ( complex_buffer.front() ) );
          for ( counter = 0; counter != size; counter++ )
            _buffer[ counter ] = complex_buffer[ counter ].real();
        }
        void operator() ( std::complex< float > *_buffer ) {
          swap ( _buffer );
          boost::array< std::complex< float >, size > swap_vector;
          std::complex< float > *swap = & ( swap_vector.front() );
          std::complex< float > *original_swap = swap;
          int counter;
          for ( counter = 2; counter <= size; counter <<= 1 ) {
            process ( swap, _buffer, counter );
            std::swap ( swap, _buffer );
          }
          if ( inverse )
            div ( _buffer );
          if ( swap != original_swap ) {
            std::swap ( swap, _buffer );
            memcpy ( _buffer, swap, sizeof ( std::complex< float > ) * size );
          }
        }
        void process ( std::complex< float > *_dest, std::complex< float > *_src, unsigned int _block_size ) {
          unsigned int counter;
          for ( counter = 0; counter != size; counter++ ) {
            unsigned int left = counter;
            unsigned int right = ( counter & ~ ( _block_size >> 1 ) ) | ( ~counter & ( _block_size >> 1 ) );
            if ( left > right ) {
              unsigned int temp = left;
              left = right;
              right = temp;
            }
            unsigned int w_step = size / _block_size;
            _dest[ counter ] = _src[ left ] + w[ ( counter % _block_size ) * w_step ] * _src[ right ];
          }
        }
      private:
        unsigned int flipBit ( unsigned int _value ) {
          int counter;
          unsigned int temp = 0;
          unsigned int log_size = log2f ( size );
          for ( counter = 0; counter != log_size; counter++ ) {
            temp <<= 1;
            temp |= ( _value >> counter ) & 0x01;
          }
          return temp;
        }
        void swap ( std::complex< float > *_buffer ) {
          unsigned int counter;
          for ( counter = 0; counter != size; counter++ ) {
            unsigned int flipped = flipBit ( counter );
            if ( counter < flipped )
              std::swap ( _buffer[ counter ], _buffer[ flipped ] );
          }
        }
        void div ( std::complex< float > *_buffer ) {
          unsigned int counter;
          for ( counter = 0; counter != size; counter++ )
            _buffer[ counter ] /= size;
        }
        boost::array< std::complex< float >, size > w;
        bool inverse;
    };
    /*!
    * 指定された周波数分布をもつノイズを出力します。
     */

    template< unsigned int _lpf, unsigned int _hpf >
    class Noize {
      public:
        enum {
          CACHE_SIZE = 8192
        };
        Noize() : current_position ( 0 ),
            cache (
              SharedBuffer< Noize< _lpf, _hpf >, float, CACHE_SIZE >::init ( &Noize< _lpf, _hpf >::initCache )
            ) {}
        static void initCache ( boost::array< float, CACHE_SIZE > &_dest ) {
          static const float lpf = std::min ( std::max ( static_cast< float > ( _lpf ) / 1000.0f, 0.0f ), 1.0f );
          static const float hpf = std::min ( std::max ( static_cast< float > ( _hpf ) / 1000.0f, 0.0f ), 1.0f );
          boost::minstd_rand gen ( 512 );
          boost::uniform_real<> dst ( -1.0, 1.0 );
          boost::variate_generator <
          boost::minstd_rand&, boost::uniform_real<>
          > random ( gen, dst );
          boost::array< std::complex< float >, CACHE_SIZE > complex_cache;
          int index;
          for ( index = 0; index != CACHE_SIZE; index++ )
            complex_cache[ index ] = random();
          FFT< CACHE_SIZE > fft ( false );
          fft ( & ( complex_cache.front() ) );
          for ( index = 0; index < CACHE_SIZE * hpf; index++ )
            complex_cache[ index ] = 0.0f;
          for ( index = CACHE_SIZE * lpf; index != CACHE_SIZE; index++ )
            complex_cache[ index ] = 0.0f;
          FFT< CACHE_SIZE > ifft ( true );
          ifft ( & ( complex_cache.front() ) );
          for ( index = 0; index != CACHE_SIZE; index++ )
            _dest[ index ] = complex_cache[ index ].real();
        }
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          int index;
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          for ( index = 0; index != SAMPLE_COUNT; index++ ) {
            if ( current_position == CACHE_SIZE )
              current_position = 0;
            raw_buffer[ index ] = cache[ current_position ];
            current_position++;
          }
        }
      private:
        void fft ( float *_dest, float *_source ) {
        }
        void ifft ( float *_dest, float *_source ) {
        }
        int current_position;
        boost::array< float, CACHE_SIZE > &cache;
    };
  }
}

#endif
