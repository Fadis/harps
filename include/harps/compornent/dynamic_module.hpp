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

#ifndef HARPS_COMPORNENT_DYNAMIC_MODULE
#define HARPS_COMPORNENT_DYNAMIC_MODULE

#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/dummy.hpp>
#include <harps/exceptions.hpp>
#include <harps/config.hpp>

#include <boost/preprocessor.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <fstream>
#include <dlfcn.h>

#define HARPS_DYNAMIC_MODULE_SOCKET( module ) \
  typedef harps::DynamicModuleSocket< module > Socket; \
  extern "C" \
    Socket *harpsDynamicModuleCreate() { \
      Socket *temp = new Socket; \
      return temp; \
    } \
  extern "C" \
    void harpsDynamicModuleDestroy( Socket *_module ) { \
      delete _module; \
    } \
  extern "C" \
    void BOOST_PP_CAT( harpsDynamicModuleRun, BOOST_PP_CAT( SAMPLE_COUNT, float ) ) ( \
      Socket *_module, \
      harps::Buffer< float > &_buffer, \
      harps::CurrentTime &_clock, \
      harps::Note &_note \
    ) { \
      ( *_module )( _buffer, _clock, _note ); \
    } \
  extern "C" \
    void BOOST_PP_CAT( harpsDynamicModuleRun, BOOST_PP_CAT( SAMPLE_COUNT, double ) ) ( \
      Socket *_module, \
      harps::Buffer< double > &_buffer, \
      harps::CurrentTime &_clock, \
      harps::Note &_note \
    ) { \
      ( *_module )( _buffer, _clock, _note ); \
    }

#define HARPS_DYNAMIC_MODULE_SLOT_LOAD_FUNCTION( z, index, type ) \
  BOOST_PP_CAT( run, BOOST_PP_CAT( BOOST_PP_ADD( index, 1 ), type ) ) = \
    reinterpret_cast< void (*)( Dummy*, Buffer< type, 16 * BOOST_PP_ADD( index, 1 ) >&, CurrentTime&, Note& ) >( \
    dlsym( handle.get(), BOOST_PP_STRINGIZE( BOOST_PP_CAT( harpsDynamicModuleRun, BOOST_PP_CAT( BOOST_PP_ADD( index, 1 ), type ) ) ) ) \
    );

#define HARPS_DYNAMIC_MODULE_SLOT_RUN( z, index, type ) \
  inline void operator()( Buffer< type, 16 * BOOST_PP_ADD( index, 1 ) > &_buffer, CurrentTime &_clock, Note &_note ) { \
    ( BOOST_PP_CAT( *run, BOOST_PP_CAT( BOOST_PP_ADD( index, 1 ), type ) ) )( instance.get(), _buffer, _clock, _note ); \
  }

#define HARPS_DYNAMIC_MODULE_SLOT_FUNCTION_POINTER( z, index, type ) \
  void ( BOOST_PP_CAT( *run, BOOST_PP_CAT( BOOST_PP_ADD( index, 1 ), type ) ) )( Dummy*, Buffer< type, 16 * BOOST_PP_ADD( index, 1 ) >&, CurrentTime&, Note& );

namespace harps {
  /*!
   * 動的ロードされるモジュールはモジュールのルートがこのクラスになっていなければなりません。
   */
  template< typename ModuleType >
    class DynamicModuleSocket {
      public:
        inline void operator() (
          Buffer< float > &_buffer,
          CurrentTime &_clock,
          Note &_note
        ) {
          source_module( _buffer, _clock, _note );
        }
        inline void operator() (
          Buffer< double > &_buffer,
          CurrentTime &_clock,
          Note &_note
        ) {
          source_module( _buffer, _clock, _note );
        }
      private:
        ModuleType source_module;
    };

  /*!
   * モジュールを探すパスを取得します。モジュールを探すパスはビルド時に指定されたprefixをもとに決定されます。
   * \return 探索パス
   */
  const char *getModulePath();

  /*!
   * 動的ロードモジュールのソケットを接続するためのスロットです。
   */
  class DynamicModuleSlot {
    public:
  /*!
   * コンストラクタ
   * \param _filename 動的ロードモジュールの名前
   */
      DynamicModuleSlot( const char *_filename ) {
        std::string filename = getModulePath();
        filename += _filename;
        handle.reset( reinterpret_cast< Dummy* >( dlopen( filename.c_str(), RTLD_LAZY ) ), &dlclose );
        if( !handle ) {
          throw ModuleNotFound();
        }
        create = reinterpret_cast< Dummy *(*)() >( dlsym( handle.get(), "harpsDynamicModuleCreate" ) );
        destroy = reinterpret_cast< void (*)( Dummy* ) >( dlsym( handle.get(), "harpsDynamicModuleDestroy" ) );
        BOOST_PP_CAT( run, BOOST_PP_CAT( SAMPLE_COUNT, float ) ) =
          reinterpret_cast< void (*)( Dummy*, Buffer< float >&, CurrentTime&, Note& ) >(
            dlsym(
              handle.get(),
              BOOST_PP_STRINGIZE( BOOST_PP_CAT( harpsDynamicModuleRun, BOOST_PP_CAT( SAMPLE_COUNT, float ) ) )
            )
          );
        BOOST_PP_CAT( run, BOOST_PP_CAT( SAMPLE_COUNT, double ) ) =
          reinterpret_cast< void (*)( Dummy*, Buffer< double >&, CurrentTime&, Note& ) >(
            dlsym(
              handle.get(),
              BOOST_PP_STRINGIZE( BOOST_PP_CAT( harpsDynamicModuleRun, BOOST_PP_CAT( SAMPLE_COUNT, double ) ) )
            )
          );
        instance.reset( create(), destroy );
        if( !instance ) {
          throw UnableToCreateInstance();
        }
      }
      inline void operator()( Buffer< float > &_buffer, CurrentTime &_clock, Note &_note ) {
        BOOST_PP_CAT( run, BOOST_PP_CAT( SAMPLE_COUNT, float ) )( instance.get(), _buffer, _clock, _note );
      }
      inline void operator()( Buffer< double > &_buffer, CurrentTime &_clock, Note &_note ) {
        BOOST_PP_CAT( run, BOOST_PP_CAT( SAMPLE_COUNT, double ) )( instance.get(), _buffer, _clock, _note );
      }
    private:
      boost::shared_ptr< Dummy > handle;
      boost::shared_ptr< Dummy > instance;
      Dummy *(*create)();
      void (*destroy)( Dummy* );
      void ( BOOST_PP_CAT( *run, BOOST_PP_CAT( SAMPLE_COUNT, float ) ) )( Dummy*, Buffer< float >&, CurrentTime&, Note& );
      void ( BOOST_PP_CAT( *run, BOOST_PP_CAT( SAMPLE_COUNT, double ) ) )( Dummy*, Buffer< double >&, CurrentTime&, Note& );
  };
};

#endif
