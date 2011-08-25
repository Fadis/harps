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


#ifndef HARPS_COMPORNENT_BRANCHBYNOTE
#define HARPS_COMPORNENT_BRANCHBYNOTE

#include <harps/dummy.hpp>
#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/config.hpp>

#include <harps/compornent/combiner.hpp>

#include <boost/preprocessor.hpp>
#include <boost/static_assert.hpp>
#include <boost/ref.hpp>
#include <boost/function.hpp>

#define HARPS_PP_BRANCHBYNOTE_TYPENAME( z, module_index, total ) \
  typename BOOST_PP_CAT( ModuleType, module_index ) \
    BOOST_PP_COMMA_IF( BOOST_PP_NOT_EQUAL( module_index, BOOST_PP_SUB( total, 1 ) ) )

#define HARPS_PP_BRANCHBYNOTE_MEMBER( z, module_index, unused ) \
  BOOST_PP_CAT( ModuleType, module_index ) BOOST_PP_CAT( module, module_index );

#define HARPS_PP_BRANCHBYNOTE_MEMBER( z, module_index, unused ) \
  BOOST_PP_CAT( ModuleType, module_index ) BOOST_PP_CAT( module, module_index );

#define HARPS_PP_BRANCHBYNOTE_CASE( z, module_index, unused ) \
  case module_index : \
    BOOST_PP_CAT( module, module_index ) ( _buffer, _clock, _note ); \
    break;

#define HARPS_PP_BRANCHBYNOTE_ARRAY( z, module_index, type ) \
  BOOST_PP_CAT( type, _modules )[ module_index ] = boost::ref( BOOST_PP_CAT( module, module_index ) );

namespace harps {
  namespace compornent {
    /*!
     * 現在のノートの音階によって選ばれたモジュールの出力を返します
     */
    template<
      BOOST_PP_REPEAT( 128, HARPS_PP_BRANCHBYNOTE_TYPENAME, 128 )
    >
      class BranchByNote {
        public:
          BranchByNote() {
            BOOST_PP_REPEAT( 128, HARPS_PP_BRANCHBYNOTE_ARRAY, float )
            BOOST_PP_REPEAT( 128, HARPS_PP_BRANCHBYNOTE_ARRAY, double )
          }
          template< typename SampleType >
            inline void operator()( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
              switch( _clock.getTone() ) {
                BOOST_PP_REPEAT( 128, HARPS_PP_BRANCHBYNOTE_CASE, 128 )
                default:
                  int index;
                  typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
                  for( index = 0; index != SAMPLE_COUNT; index++ )
                    raw_buffer[ index ] = 0.0f;
              };
            }
          template<>
            inline void operator()< float >( Buffer< float > &_buffer, CurrentTime &_clock, Note &_note ) {
              float_modules[ _clock.getTone() ]( _buffer, _clock, _note );
            }
          template<>
            inline void operator()< double >( Buffer< double > &_buffer, CurrentTime &_clock, Note &_note ) {
              double_modules[ _clock.getTone() ]( _buffer, _clock, _note );
            }
        private:
          BOOST_PP_REPEAT( 128, HARPS_PP_BRANCHBYNOTE_MEMBER, 128 )
          boost::array< boost::function< void ( Buffer< float >&, CurrentTime&, Note& ) > 128 > float_modules;
          boost::array< boost::function< void ( Buffer< double >&, CurrentTime&, Note& ) > 128 > double_modules;
      };
  }
}

#endif
