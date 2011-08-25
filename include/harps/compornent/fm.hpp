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

#ifndef HARPS_COMPORNENT_FM
#define HARPS_COMPORNENT_FM

#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>

#include <harps/compornent/sine.hpp>
#include <harps/compornent/envelope.hpp>
#include <harps/compornent/envelope2.hpp>
#include <harps/compornent/add.hpp>
#include <harps/compornent/mul.hpp>
#include <harps/compornent/volume.hpp>

namespace harps {
  namespace compornent {
    /*!
    * FM音源のオペレータです。2つの入力を使って正弦波を周波数変調して出力します。線形補間エンベロープを使用します。
     */
    template <
    typename ModuleType0, typename ModuleType1,
    unsigned int _clock_select = 0,
    int _delay = 0, int _attack = 0, int _hold = 0, int _decay = 0, int _sustain = 0, int _release = 0
    >
    class FM {
      public:
        typedef
        Mul <
        Sine <
        Add< ModuleType0, ModuleType1 >
        > ,
        Envelope< _clock_select, _delay, _attack, _hold, _decay, _sustain, _release >
        > OperatorType;
        template< typename SampleType >
        void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          source_module ( _buffer, _clock, _note );
        }
      private:
        OperatorType source_module;
    };

    template <
    typename ModuleType0, typename ModuleType1
    >
    /*!
    * FM音源のオペレータです。2つの入力を使って正弦波を周波数変調して出力します。エンベロープを使用しません。
     */

    class FM< ModuleType0, ModuleType1, 0, 0, 0, 0, 0, 0, 0 > {
      public:
        typedef
        Sine <
        Add< ModuleType0, ModuleType1 >
        > OperatorType;
        template< typename SampleType >
        void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          source_module ( _buffer, _clock, _note );
        }
      private:
        OperatorType source_module;
    };

    /*!
    * FM音源のオペレータです。2つの入力を使って正弦波を周波数変調して出力します。2次補間エンベロープを使用します。
     */

    template <
    typename ModuleType0, typename ModuleType1,
    unsigned int _clock_select,
    int _delay,
    int _attack, int _attack_middle, int _attack_middle_level,
    int _hold, int _hold_level,
    int _decay1, int _decay1_middle, int _decay1_middle_level,
    int _decay1_end_level,
    int _decay2, int _decay2_middle, int _decay2_middle_level,
    int _sustain_level,
    int _release, int _release_middle, int _release_middle_level
    >
    class FM2 {
      public:
        typedef
        Volume <
        Sine <
        Add< ModuleType0, ModuleType1 >
        > ,
        Envelope2 <
        _clock_select,
        _delay,
        _attack, _attack_middle, _attack_middle_level,
        _hold, _hold_level,
        _decay1, _decay1_middle, _decay1_middle_level,
        _decay1_end_level,
        _decay2, _decay2_middle, _decay2_middle_level,
        _sustain_level,
        _release, _release_middle, _release_middle_level
        >
        > OperatorType;
        template< typename SampleType >
        void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          source_module ( _buffer, _clock, _note );
        }
      private:
        OperatorType source_module;
    };
  }
}

#endif
