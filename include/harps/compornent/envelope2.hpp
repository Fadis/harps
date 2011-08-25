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


#ifndef HARPS_COMPORNENT_ENVELOPE2
#define HARPS_COMPORNENT_ENVELOPE2

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/shared_buffer.hpp>
#include <harps/config.hpp>

#include <boost/array.hpp>

namespace harps {
  namespace compornent {
    bool lu ( float *_lu, unsigned int *_index );
    bool inverse ( float *_dest, const float *_source_orig );

    // ax + b = y
    void calcCoef (
      float &_a, float &_b,
      float _x0, float _y0,
      float _x1, float _y1
    );

    // ax^2 + bx + c = y
    void calcCoef (
      float &_a, float &_b, float &_c,
      float _x0, float _y0,
      float _x1, float _y1,
      float _x2, float _y2
    );

    /*!
    * 2次補間のエンベロープを生成して出力します。エンベロープのリリースが完了するとノートの終了を要求します。
     */
    template <
    unsigned int _clock_select,
    int _delay,
    int _attack, int _attack_middle, int _attack_middle_level,
    int _hold, int _hold_level,
    int _decay1, int _decay1_middle, int _decay1_middle_level,
    int _decay1_end_level,
    int _decay2, int _decay2_middle, int _decay2_middle_level,
    int _sustain_level,
    int _release, int _release_middle, int _release_middle_level
    > class Envelope2 {
      public:
        enum {
          CACHE_SIZE = 2048
        };
        typedef
        Envelope2 <
        _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level,
        _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level,
        _decay2, _decay2_middle, _decay2_middle_level, _sustain_level,
        _release, _release_middle, _release_middle_level
        > ThisType;
        class NoteOn {};
        class NoteOff {};
        Envelope2()
            : last_level ( 0.0f ),
            noteon_cache (
              SharedBuffer< NoteOn, float, CACHE_SIZE >::init ( &ThisType::initNoteOnEnvelope )
            ),
            noteoff_cache (
              SharedBuffer< NoteOff, float, CACHE_SIZE >::init ( &ThisType::initNoteOffEnvelope )
            ) {}
        static void initNoteOnEnvelope ( boost::array< float, CACHE_SIZE > &_dest ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float attack_middle = static_cast< float > ( _attack_middle ) / 1000.0f;
          static const float attack_middle_level = static_cast< float > ( _attack_middle_level ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float hold_level = static_cast< float > ( _hold_level ) / 1000.0f;
          static const float decay1 = static_cast< float > ( _decay1 ) / 1000.0f;
          static const float decay1_middle = static_cast< float > ( _decay1_middle ) / 1000.0f;
          static const float decay1_middle_level = static_cast< float > ( _decay1_middle_level ) / 1000.0f;
          static const float decay1_end_level = static_cast< float > ( _decay1_end_level ) / 1000.0f;
          static const float decay2 = static_cast< float > ( _decay2 ) / 1000.0f;
          static const float decay2_middle = static_cast< float > ( _decay2_middle ) / 1000.0f;
          static const float decay2_middle_level = static_cast< float > ( _decay2_middle_level ) / 1000.0f;
          static const float sustain_level = static_cast< float > ( _sustain_level ) / 1000.0f;
          static const float total = delay + attack + hold + decay1 + decay2;
          // ax^2 + bx + c = y
          float attack_a, attack_b, attack_c;
          calcCoef ( attack_a, attack_b, attack_c, 0.0f, 0.0f, attack_middle, attack_middle_level, attack, hold_level );
          float decay1_a, decay1_b, decay1_c;
          calcCoef ( decay1_a, decay1_b, decay1_c, 0.0f, hold_level, decay1_middle, decay1_middle_level, decay1, decay1_end_level );
          float decay2_a, decay2_b, decay2_c;
          calcCoef ( decay2_a, decay2_b, decay2_c, 0.0f, decay1_end_level, decay2_middle, decay2_middle_level, decay2, sustain_level );
          int index;
          for ( index = 0; index != _dest.size(); index++ ) {
            double time = total * index / _dest.size();
            if ( time < delay ) {
              _dest[ index ] = 0.0f;
              continue;
            }
            time -= delay;
            if ( time < attack ) {
              _dest[ index ] = attack_a * time * time + attack_b * time + attack_c;
              continue;
            }
            time -= attack;
            if ( time < hold ) {
              _dest[ index ] = hold_level;
              continue;
            }
            time -= hold;
            if ( time < decay1 ) {
              _dest[ index ] = decay1_a * time * time + decay1_b * time + decay1_c;
              continue;
            }
            time -= decay1;
            if ( time < decay2 ) {
              _dest[ index ] = decay2_a * time * time + decay2_b * time + decay2_c;
              continue;
            }
          }
        }
        static void initNoteOffEnvelope ( boost::array< float, CACHE_SIZE > &_dest ) {
          static const float sustain_level = static_cast< float > ( _sustain_level ) / 1000.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float release_middle = static_cast< float > ( _release_middle ) / 1000.0f;
          static const float release_middle_level = static_cast< float > ( _release_middle_level ) / 1000.0f;
          float release_a, release_b, release_c;
          calcCoef ( release_a, release_b, release_c, 0.0f, 1.0f, release_middle, release_middle_level, release, 0.0f );
          int index;
          for ( index = 0; index != _dest.size(); index++ ) {
            double time = release * index / _dest.size();
            _dest[ index ] = release_a * time * time + release_b * time + release_c;
          }
        }
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float decay1 = static_cast< float > ( _decay1 ) / 1000.0f;
          static const float decay2 = static_cast< float > ( _decay2 ) / 1000.0f;
          static const float sustain_level = static_cast< float > ( _sustain_level ) / 1000.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float total = delay + attack + hold + decay1 + decay2;
          int index;
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          if ( _note.getStatus() == Note::NOTE_ON ) {
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              if ( time < total )
                raw_buffer[ index ] = noteon_cache[ static_cast<int> ( time / total * CACHE_SIZE ) ];
              else
                raw_buffer[ index ] = sustain_level;
            }
            last_level = raw_buffer[ SAMPLE_COUNT - 1 ];
            _buffer.requestContinue();
          }
          else if ( _note.getStatus() == Note::NOTE_OFF && last_level != 0.0f ) {
            bool end = false;
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              if ( time < release )
                raw_buffer[ index ] = noteoff_cache[ static_cast<int> ( time / release * CACHE_SIZE ) ] * last_level;
              else {
                raw_buffer[ index ] = 0.0f;
                end = true;
              }
            }
            if ( end )
              _buffer.requestEnd();
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
        boost::array< float, CACHE_SIZE > &noteon_cache;
        boost::array< float, CACHE_SIZE > &noteoff_cache;
    };

    /*!
    * 2次補間のエンベロープを生成して出力します。エンベロープのリリースが完了するとノートの終了を要求します。
     */
    template <
    unsigned int _clock_select,
    int _delay,
    int _attack, int _attack_middle, int _attack_middle_level,
    int _hold, int _hold_level,
    int _decay1, int _decay1_middle, int _decay1_middle_level,
    int _decay1_end_level,
    int _decay2, int _decay2_middle, int _decay2_middle_level,
    int _release, int _release_middle, int _release_middle_level
    > class Envelope2 <
          _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level,
          _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level,
          _decay2, _decay2_middle, _decay2_middle_level, 0,
          _release, _release_middle, _release_middle_level
          > {
      public:
        enum {
          CACHE_SIZE = 2048
        };
        typedef
        Envelope2 <
        _clock_select, _delay, _attack, _attack_middle, _attack_middle_level, _hold, _hold_level,
        _decay1, _decay1_middle, _decay1_middle_level, _decay1_end_level,
        _decay2, _decay2_middle, _decay2_middle_level, 0,
        _release, _release_middle, _release_middle_level
        > ThisType;
        class NoteOn {};
        class NoteOff {};
        Envelope2()
            : last_level ( 0.0f ),
            noteon_cache (
              SharedBuffer< NoteOn, float, CACHE_SIZE >::init ( &ThisType::initNoteOnEnvelope )
            ),
            noteoff_cache (
              SharedBuffer< NoteOff, float, CACHE_SIZE >::init ( &ThisType::initNoteOffEnvelope )
            ) {}
        static void initNoteOnEnvelope ( boost::array< float, CACHE_SIZE > &_dest ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float attack_middle = static_cast< float > ( _attack_middle ) / 1000.0f;
          static const float attack_middle_level = static_cast< float > ( _attack_middle_level ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float hold_level = static_cast< float > ( _hold_level ) / 1000.0f;
          static const float decay1 = static_cast< float > ( _decay1 ) / 1000.0f;
          static const float decay1_middle = static_cast< float > ( _decay1_middle ) / 1000.0f;
          static const float decay1_middle_level = static_cast< float > ( _decay1_middle_level ) / 1000.0f;
          static const float decay1_end_level = static_cast< float > ( _decay1_end_level ) / 1000.0f;
          static const float decay2 = static_cast< float > ( _decay2 ) / 1000.0f;
          static const float decay2_middle = static_cast< float > ( _decay2_middle ) / 1000.0f;
          static const float decay2_middle_level = static_cast< float > ( _decay2_middle_level ) / 1000.0f;
          static const float sustain_level = 0.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float release_middle = static_cast< float > ( _release_middle ) / 1000.0f;
          static const float release_middle_level = static_cast< float > ( _release_middle_level ) / 1000.0f;
          static const float total = delay + attack + hold + decay1 + decay2;
          // ax^2 + bx + c = y
          float attack_a, attack_b, attack_c;
          calcCoef ( attack_a, attack_b, attack_c, 0.0f, 0.0f, attack_middle, attack_middle_level, attack, hold_level );
          float decay1_a, decay1_b, decay1_c;
          calcCoef ( decay1_a, decay1_b, decay1_c, 0.0f, hold_level, decay1_middle, decay1_middle_level, decay1, decay1_end_level );
          float decay2_a, decay2_b, decay2_c;
          calcCoef ( decay2_a, decay2_b, decay2_c, 0.0f, decay1_end_level, decay2_middle, decay2_middle_level, decay2, sustain_level );
          int index;
          for ( index = 0; index != _dest.size(); index++ ) {
            double time = total * index / _dest.size();
            if ( time < delay ) {
              _dest[ index ] = 0.0f;
              continue;
            }
            time -= delay;
            if ( time < attack ) {
              _dest[ index ] = attack_a * time * time + attack_b * time + attack_c;
              continue;
            }
            time -= attack;
            if ( time < hold ) {
              _dest[ index ] = hold_level;
              continue;
            }
            time -= hold;
            if ( time < decay1 ) {
              _dest[ index ] = decay1_a * time * time + decay1_b * time + decay1_c;
              continue;
            }
            time -= decay1;
            if ( time < decay2 ) {
              _dest[ index ] = decay2_a * time * time + decay2_b * time + decay2_c;
              continue;
            }
          }
        }
        static void initNoteOffEnvelope ( boost::array< float, CACHE_SIZE > &_dest ) {
          static const float sustain_level = 0.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float release_middle = static_cast< float > ( _release_middle ) / 1000.0f;
          static const float release_middle_level = static_cast< float > ( _release_middle_level ) / 1000.0f;
          float release_a, release_b, release_c;
          calcCoef ( release_a, release_b, release_c, 0.0f, 1.0f, release_middle, release_middle_level, release, 0.0f );
          int index;
          for ( index = 0; index != _dest.size(); index++ ) {
            double time = release * index / _dest.size();
            _dest[ index ] = release_a * time * time + release_b * time + release_c;
          }
        }
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          static const float delay = static_cast< float > ( _delay ) / 1000.0f;
          static const float attack = static_cast< float > ( _attack ) / 1000.0f;
          static const float hold = static_cast< float > ( _hold ) / 1000.0f;
          static const float decay1 = static_cast< float > ( _decay1 ) / 1000.0f;
          static const float decay2 = static_cast< float > ( _decay2 ) / 1000.0f;
          static const float sustain_level = 0.0f;
          static const float release = static_cast< float > ( _release ) / 1000.0f;
          static const float total = delay + attack + hold + decay1 + decay2;
          int index;
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          if ( _note.getStatus() == Note::NOTE_ON ) {
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              if ( time < total ) {
                raw_buffer[ index ] = noteon_cache[ static_cast<int> ( time / total * CACHE_SIZE ) ];
                _buffer.requestContinue();
              }
              else {
                raw_buffer[ index ] = sustain_level;
                _buffer.requestEnd();
              }
            }
            last_level = raw_buffer[ SAMPLE_COUNT - 1 ];
          }
          else if ( _note.getStatus() == Note::NOTE_OFF && last_level != 0.0f ) {
            bool end = false;
            for ( index = 0; index != SAMPLE_COUNT; index++ ) {
              double time = _clock.template getTime< _clock_select > ( index );
              if ( time < release )
                raw_buffer[ index ] = noteoff_cache[ static_cast<int> ( time / release * CACHE_SIZE ) ] * last_level;
              else {
                raw_buffer[ index ] = 0.0f;
                end = true;
              }
            }
            if ( end )
              _buffer.requestEnd();
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
        boost::array< float, CACHE_SIZE > &noteon_cache;
        boost::array< float, CACHE_SIZE > &noteoff_cache;
    };
  }
}

#endif
