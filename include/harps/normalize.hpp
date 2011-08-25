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


#ifndef HARPS_NORMALIZE
#define HARPS_NORMALIZE

#include <harps/buffer.hpp>

namespace harps {
  /*!
   * 正規化のスケール値にローパスフィルタをかけて急激なスケーリングによるノイズを低減します。
   * \param _buffer スケール値バッファ
   */
  template< typename SampleType >
    inline void reduceNormalizingNoize(
      Buffer< SampleType > &_buffer
    ) {
      int index;
      typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
      float current_tangent = ( raw_buffer[ SAMPLE_COUNT - 1 ] - raw_buffer[ 0 ] ) / ( SAMPLE_COUNT - 1 );
      for( index = SAMPLE_COUNT - 2; index; index-- ) {
        float smoothed_value = current_tangent * ( index ) + raw_buffer[ 0 ];
        if( raw_buffer[ index ] < smoothed_value )
          raw_buffer[ index ] = smoothed_value;
        else
          current_tangent = ( raw_buffer[ index ] - raw_buffer[ 0 ] ) / index;
      }
      for( index = 2; index != SAMPLE_COUNT - 2; index++ ) {
        raw_buffer[ index ] =
          raw_buffer[ index - 2 ] * 0.05f +
          raw_buffer[ index - 1 ] * 0.15f +
          raw_buffer[ index     ] * 0.6f +
          raw_buffer[ index + 1 ] * 0.15f +
          raw_buffer[ index + 2 ] * 0.05f;
      }
    }

  /*!
   * ノーマライザは波形が出力可能な振幅を越えてしまう場合にどのくらい音量を絞れば良いかを計算します。
   */
  template< int tail >
    class Normalizer {
      public:
      /*!
      * コンストラクタ
      */
        Normalizer()
          : top_level( 0.0f ), top_time( 0 ) {}
      /*!
      * デストラクタ
      */
        virtual ~Normalizer() {}
      /*!
      * 波形データを供給します
      * \param _arg_value サンプル値
      */
      inline void setValue( float _arg_value ) {
        top_time--;
        _arg_value = fabsf( _arg_value );
        if( ( _arg_value * tail ) > top_level * top_time ) {
          top_level = _arg_value;
          top_time = tail;
        }
      }
      /*!
      * 適切な音量を取得します
      * \return スケール値
      */
      inline float getAmp() {
        float highest = top_level * top_time / tail;
        if( highest > 1.0f )
          return highest;
        else
          return 1.0f;
      }
    private:
      float top_level;
      int top_time;
  };
};

#endif
