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


#ifndef HARPS_COMPORNENT_DISTOTION
#define HARPS_COMPORNENT_DISTOTION

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/config.hpp>

namespace harps {
  namespace compornent {
            /*!
     * 入力を意図的に音割れさせて出力します。
             */
    template<
      typename ModuleType,
      int _linear_begin,
      int _linear_end,
      int _flat_begin
    >
      class Distotion {
        public:
          enum {
            CACHE_SIZE = 1024
          };

          Distotion() : cache( cache_array + CACHE_SIZE ) {
            static const float linear_begin = static_cast< float >( _linear_begin ) / 1000.0f;
            static const float linear_end = static_cast< float >( _linear_end ) / 1000.0f;
            static const float flat_begin = static_cast< float >( _flat_begin ) / 1000.0f;
            static const int linear_begin_index = linear_begin / flat_begin * CACHE_SIZE;
            static const int linear_end_index = linear_end / flat_begin * CACHE_SIZE;
            static const float height = 1.0f / ( ( flat_begin + linear_end - linear_begin ) * 0.5f );
            int index;
            for( index = 0; index != linear_begin_index; index++ ) {
              float x = static_cast< float >( index ) * flat_begin / CACHE_SIZE;
              float y = x * height / linear_begin;
              cache[ index ] = x * y * 0.5f;
            }
            for( ; index != linear_end_index; index++ ) {
              float xl = static_cast< float >( index ) * flat_begin / CACHE_SIZE;
              float xh = static_cast< float >( index ) * flat_begin / CACHE_SIZE - linear_begin;
               cache[ index ] = ( xl + xh ) * height * 0.5f;
            }
            for( ; index != CACHE_SIZE; index++ ) {
              float x = flat_begin - static_cast< float >( index ) * flat_begin / CACHE_SIZE;
              float y = x * height / ( flat_begin - linear_end );
              cache[ index ] = 1.0f - x * y * 0.5f;
            }

            static const float linear_half_begin = linear_begin * 0.5f;
            static const float linear_half_end = ( linear_end + flat_begin ) * 0.5f;
            static const int linear_half_begin_index = linear_half_begin / flat_begin * CACHE_SIZE;
            static const int linear_half_end_index = linear_half_end / flat_begin * CACHE_SIZE;
            static const float half_height = 0.5f / ( ( flat_begin + linear_half_end - linear_half_begin ) * 0.5f );

            for( index = 0; index != linear_half_begin_index / 2; index++ ) {
              float x = static_cast< float >( index ) * flat_begin / CACHE_SIZE;
              float y = x * half_height / linear_half_begin;
              cache[ -index ] = -( x * y * 0.5f );
            }
            for( ; index != linear_half_end_index; index++ ) {
              float xl = static_cast< float >( index ) * flat_begin / CACHE_SIZE;
              float xh = static_cast< float >( index ) * flat_begin / CACHE_SIZE - linear_half_begin;
              cache[ -index ] = -( ( xl + xh ) * half_height * 0.5f );
            }
            for( ; index != CACHE_SIZE; index++ ) {
              float x = flat_begin - static_cast< float >( index ) * flat_begin / CACHE_SIZE;
              float y = x * half_height / ( flat_begin - linear_half_end );
              cache[ -index ] = -( 0.5f - x * y * 0.5f );
            }
          }
          template< typename SampleType >
            inline void operator()( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
              static const float linear_begin = static_cast< float >( _linear_begin ) / 1000.0f;
              static const float linear_end = static_cast< float >( _linear_end ) / 1000.0f;
              static const float flat_begin = static_cast< float >( _flat_begin ) / 1000.0f;
              static const float negative_total = ( ( flat_begin + ( linear_end + flat_begin ) / 2 - linear_begin / 2 ) * 0.5f * 0.5f );

              source_module( _buffer, _clock, _note );
              int index;
              typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
              for( index = 0; index != SAMPLE_COUNT; index++ ) {
                if( fabsf( raw_buffer[ index ] ) < flat_begin )
                  raw_buffer[ index ] = cache[ static_cast< int >( raw_buffer[ index ] / flat_begin * CACHE_SIZE ) ];
                else if( raw_buffer[ index ] > 0.0f )
                  raw_buffer[ index ] = 1.0f;
                else
                  raw_buffer[ index ] = -0.5f;
              }
            }
        private:
          float cache_array[ CACHE_SIZE * 2 ];
          float * const cache;
          ModuleType source_module;
      };
  }
}

#endif
