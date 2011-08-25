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


#ifndef HARPS_COMPORNENT_ENVELOPE
#define HARPS_COMPORNENT_ENVELOPE

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/config.hpp>

namespace harps {
  namespace compornent {
    /*!
    * 線形補間のエンベロープを生成して出力します。エンベロープのリリースが完了するとノートの終了を要求します。
     */
    template< unsigned int _clock_select, int _delay, int _attack, int _hold, int _decay, int _sustain, int _release >
    class Envelope {
      public:
        enum {
          CACHE_SIZE = 1024
        };
        Envelope() : last_level ( 0.0f ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float decay = static_cast< float > ( _decay ) / 1000.0f;
          static const float sustain = static_cast< float > ( _sustain ) / 1000.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float total = delay + attack + hold + decay;
          int index;
          for ( index = 0; index != CACHE_SIZE; index++ ) {
            double time = total * index / CACHE_SIZE;
            if ( time < delay ) {
              cache[ index ] = 0.0f;
              continue;
            }
            time -= delay;
            if ( time < attack ) {
              cache[ index ] = time / attack;
              continue;
            }
            time -= attack;
            if ( time < hold ) {
              cache[ index ] = 1.0f;
              continue;
            }
            time -= hold;
            if ( time < decay ) {
              cache[ index ] = - time * ( 1.0f - sustain ) / decay + 1.0f;
              continue;
            }
          }
        }
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float decay = static_cast< float > ( _decay ) / 1000.0f;
          static const float sustain = static_cast< float > ( _sustain ) / 1000.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float total = delay + attack + hold + decay;
          int index;
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          if ( _note.getStatus() == Note::NOTE_ON ) {
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              if ( time < total )
                raw_buffer[ index ] = cache[ static_cast<int> ( time / total * CACHE_SIZE ) ];
              else
                raw_buffer[ index ] = sustain;
            }
            last_level = raw_buffer[ SAMPLE_COUNT - 1 ];
            _buffer.requestContinue();
          }
          else if ( _note.getStatus() == Note::NOTE_OFF && last_level != 0.0f ) {
            bool end = false;
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              raw_buffer[ index ] = last_level - time * last_level / release;
              if ( raw_buffer[ index ] <= 0.0f ) {
                raw_buffer[ index ] = 0.0f;
                end = true;
              }
            }
            if ( end ) {
              last_level = 0.0f;
              _buffer.requestEnd();
            }
            else
              _buffer.requestContinue();
          }
          else {
            for ( index = 0; index != SAMPLE_COUNT; index++ )
              raw_buffer[ index ] = 0.0f;
            _buffer.requestEnd();
          }
        }
      private:
        float last_level;
        float cache[ CACHE_SIZE ];
    };
    /*!
    * 線形補間のエンベロープを生成して出力します。エンベロープのリリースが完了するとノートの終了を要求します。
    */
    template< unsigned int _clock_select, int _delay, int _attack, int _hold, int _decay, int _release >
    class Envelope< _clock_select, _delay, _attack, _hold, _decay, 0, _release > {
      public:
        enum {
          CACHE_SIZE = 1024
        };
        Envelope() : last_level ( 0.0f ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float decay = static_cast< float > ( _decay ) / 1000.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float total = delay + attack + hold + decay;
          int index;
          for ( index = 0; index != CACHE_SIZE; index++ ) {
            double time = total * index / CACHE_SIZE;
            if ( time < delay ) {
              cache[ index ] = 0.0f;
              continue;
            }
            time -= delay;
            if ( time < attack ) {
              cache[ index ] = time / attack;
              continue;
            }
            time -= attack;
            if ( time < hold ) {
              cache[ index ] = 1.0f;
              continue;
            }
            time -= hold;
            if ( time < decay ) {
              cache[ index ] = - time / decay + 1.0f;
              continue;
            }
          }
        }
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float decay = static_cast< float > ( _decay ) / 1000.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float total = delay + attack + hold + decay;
          int index;
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          if ( _note.getStatus() == Note::NOTE_ON ) {
            bool is_sustain = false;
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              if ( time < total )
                raw_buffer[ index ] = cache[ static_cast<int> ( time / total * CACHE_SIZE ) ];
              else {
                raw_buffer[ index ] = 0.0f;
                is_sustain = true;
              }
            }
            last_level = raw_buffer[ SAMPLE_COUNT - 1 ];
            if ( is_sustain )
              _buffer.requestEnd();
            else
              _buffer.requestContinue();
          }
          else if ( _note.getStatus() == Note::NOTE_OFF && last_level != 0.0f ) {
            bool end = false;
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              raw_buffer[ index ] = last_level - time * last_level / release;
              if ( raw_buffer[ index ] <= 0.0f ) {
                raw_buffer[ index ] = 0.0f;
                end = true;
              }
            }
            if ( end ) {
              last_level = 0.0f;
              _buffer.requestEnd();
            }
            else
              _buffer.requestContinue();
          }
          else {
            for ( index = 0; index != SAMPLE_COUNT; index++ )
              raw_buffer[ index ] = 0.0f;
            _buffer.requestEnd();
          }
        }
      private:
        float last_level;
        float cache[ CACHE_SIZE ];
    };
  }
}

#endif
