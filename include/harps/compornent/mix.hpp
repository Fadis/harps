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


#ifndef HARPS_COMPORNENT_MIX
#define HARPS_COMPORNENT_MIX

#include <harps/dummy.hpp>
#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>

#include <harps/compornent/combiner.hpp>

#include <boost/preprocessor.hpp>
#include <boost/static_assert.hpp>

#define HARPS_PP_MIX_OPERATION_ONCE \
  module0( _buffer, _clock, _note ); \
  Buffer< SampleType > temp_buffer; \
  typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get(); \
  typename Buffer< SampleType >::SampleType *raw_temp_buffer = temp_buffer.get(); \
  int index;

#define HARPS_PP_MIX_OPERATION_LOOP( z, module_index, unused ) \
  temp_buffer.reset(); \
  BOOST_PP_CAT( module, module_index ) ( temp_buffer, _clock, _note ); \
  for( index = 0; index != SAMPLE_COUNT; index++ ) \
    raw_buffer[ index ] += raw_temp_buffer[ index ]; \
  _buffer.mergeVote( temp_buffer );

#define HARPS_PP_MIX_SPECIALIZATION( z, active_module_count, unused ) \
  template< \
  BOOST_PP_REPEAT( active_module_count, HARPS_PP_MODULE_TYPENAME, active_module_count ) \
  > \
  class Mix< \
        BOOST_PP_REPEAT( active_module_count, HARPS_PP_MODULE_SPECIALIZATION_TYPENAMES, unused ) \
        BOOST_PP_REPEAT_FROM_TO( active_module_count, HARPS_MAX_MODULES_PER_MIXER, HARPS_PP_MODULE_DUMMY, HARPS_MAX_MODULES_PER_MIXER )  \
        > { \
    public: \
      template< typename SampleType > \
      inline void operator()( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) { \
        HARPS_PP_MIX_OPERATION_ONCE \
        BOOST_PP_REPEAT_FROM_TO( 1, active_module_count, HARPS_PP_MIX_OPERATION_LOOP, HARPS_PP_UNUSED ) \
        for( index = 0; index != SAMPLE_COUNT; index++ ) \
          raw_buffer[ index ] /= active_module_count; \
      } \
    private: \
      BOOST_PP_REPEAT( active_module_count, HARPS_PP_MODULE_MEMBER, HARPS_PP_UNUSED ) \
  };

namespace harps {
  namespace compornent {
    /*!
    * 複数のソースからの入力を混ぜて出力します。
     */
    template <
    BOOST_PP_REPEAT ( HARPS_MAX_MODULES_PER_MIXER, HARPS_PP_MODULE_TYPENAME_WITH_DEFAULT, HARPS_MAX_MODULES_PER_MIXER )
    >
    class Mix {
      public:
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          HARPS_PP_MIX_OPERATION_ONCE
          BOOST_PP_REPEAT_FROM_TO ( 1, HARPS_MAX_MODULES_PER_MIXER, HARPS_PP_MIX_OPERATION_LOOP, HARPS_PP_UNUSED )
          for ( index = 0; index != SAMPLE_COUNT; index++ )
            raw_buffer[ index ] /= HARPS_MAX_MODULES_PER_MIXER;
        }
      private:
        BOOST_PP_REPEAT ( HARPS_MAX_MODULES_PER_MIXER, HARPS_PP_MODULE_MEMBER, HARPS_PP_UNUSED )
    };

    BOOST_PP_REPEAT_FROM_TO ( 1, HARPS_MAX_MODULES_PER_MIXER, HARPS_PP_MIX_SPECIALIZATION, HARPS_PP_UNUSED )

    /*!
    * 複数のソースからの入力を混ぜて出力します。
     */
    template<>
    class Mix <
          BOOST_PP_REPEAT ( HARPS_MAX_MODULES_PER_MIXER, HARPS_PP_MODULE_DUMMY, HARPS_MAX_MODULES_PER_MIXER )
          > {
      public:
        template< typename SampleType >
        inline void operator() ( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
          int index;
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          for ( index = 0; index != SAMPLE_COUNT; index++ )
            raw_buffer[ index ] = 0.0f;
        }
    };
  }
}

#endif
