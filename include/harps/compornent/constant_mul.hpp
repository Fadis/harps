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


#ifndef HARPS_COMPORNENT_CONSTANT_MUL
#define HARPS_COMPORNENT_CONSTANT_MUL

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/config.hpp>

namespace harps {
  namespace compornent {
        /*!
     * 入力を定数倍して出力します。
         */
    template< typename ModuleType, int _value >
      class ConstantMul {
        public:
          template< typename SampleType >
            inline void operator()( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
              static const float value = static_cast< float >( _value ) / 1000.0f;
              source_module( _buffer, _clock, _note );
              int index;
              typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
              for( index = 0; index != SAMPLE_COUNT; index++ )
                raw_buffer[ index ] *= value;
            }
        private:
          ModuleType source_module;
      };
  }
}

#endif
