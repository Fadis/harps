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


#ifndef HARPS_COMPORNENT_RECTANGLE
#define HARPS_COMPORNENT_RECTANGLE

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/config.hpp>

namespace harps {
  namespace compornent {
    /*!
    * 指定されたデューティ比の矩形波を出力します。
     */

    template< typename ModuleType, typename DutyModuleType >
    class Rectangle {
      public:
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          source_module ( _buffer, _clock, _note );
          int index;
          Buffer< SampleType > duty_buffer;
          duty_module ( duty_buffer, _clock, _note );
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          typename Buffer< SampleType >::SampleType *raw_duty_buffer = duty_buffer.get();
          for ( index = 0; index != SAMPLE_COUNT; index++ )
            raw_buffer[ index ] = rectangle ( raw_duty_buffer[ index ], raw_buffer[ index ] );
        }
      private:
        ModuleType source_module;
        DutyModuleType duty_module;
    };
  }
}

#endif
