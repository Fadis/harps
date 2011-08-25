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

#ifndef HARPS_OUTPUT_WAVE
#define HARPS_OUTPUT_WAVE

#include <harps/config.hpp>
#include <harps/exceptions.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/filesystem/operations.hpp>

#include <fstream>

namespace harps {
  namespace output {
        /*!
         * RIFF Wave形式でファイルに書き出します。
         */
    template< bool is_stereo, unsigned int bytes_per_sample >
      class Wave {
        public:
              /*!
               * コンストラクタ
               * \param _filename 出力ファイル名
               */
          Wave( const char *_filename )
          : filepath( _filename, boost::filesystem::native ), outfile( new std::fstream( _filename, std::ios::out ) ) {
            if( outfile->fail() )
              throw UnableToOpenSink();
            static const char header[] = {
              'R', 'I', 'F', 'F',
              0xF8, 0xFF, 0x3F, 0x00,
              'W', 'A','V','E',
              'f', 'm', 't', ' ',
              0x10, 0x00, 0x00, 0x00,
              0x01, 0x00
            };
            outfile->write ( header, 22 );
            static const unsigned int channels = ( ( is_stereo ) ? 2 : 1 );
            outfile->put ( static_cast< char >( channels ) );
            outfile->put ( 0x00 );
            outfile->put ( static_cast< char >( SAMPLING_RATE ) );
            outfile->put ( static_cast< char >( SAMPLING_RATE >> 8 ) );
            outfile->put ( static_cast< char >( SAMPLING_RATE >> 16 ) );
            outfile->put ( static_cast< char >( SAMPLING_RATE >> 24 ) );
            static const unsigned int byte_per_sec = SAMPLING_RATE * channels * bytes_per_sample;
            outfile->put ( static_cast< char >( byte_per_sec ) );
            outfile->put ( static_cast< char >( byte_per_sec >> 8 ) );
            outfile->put ( static_cast< char >( byte_per_sec >> 16 ) );
            outfile->put ( static_cast< char >( byte_per_sec >> 24 ) );
            static const unsigned int sample_size = bytes_per_sample * channels;
            outfile->put ( static_cast< char >( sample_size ) );
            outfile->put ( static_cast< char >( sample_size >> 8 ) );
            static const unsigned int bits_per_sample = bytes_per_sample * 8;
            outfile->put ( static_cast< char >( bits_per_sample ) );
            outfile->put ( static_cast< char >( bits_per_sample >> 8 ) );
            static const char footer[] = {
              'd', 'a', 't', 'a',
              0xD4, 0xFF, 0x3F, 0x00,
            };
            outfile->write ( footer, 8 );
          }
              /*!
               * デストラクタ
               */
          virtual ~Wave() {
            const unsigned int filesize = boost::filesystem::file_size( filepath );
            outfile->seekp ( 4, std::ios_base::beg );
            const unsigned int riff_size = filesize - 8;
            outfile->put ( static_cast< char >( riff_size ) );
            outfile->put ( static_cast< char >( riff_size >> 8 ) );
            outfile->put ( static_cast< char >( riff_size >> 16 ) );
            outfile->put ( static_cast< char >( riff_size >> 24 ) );
            outfile->seekp ( 40, std::ios_base::beg );
            const unsigned int data_size = filesize - 44;
            outfile->put ( static_cast< char >( data_size ) );
            outfile->put ( static_cast< char >( data_size >> 8 ) );
            outfile->put ( static_cast< char >( data_size >> 16 ) );
            outfile->put ( static_cast< char >( data_size >> 24 ) );
          }
              /*!
           * バッファを書き出します
           * \param _buffer バッファ
               */
          template< typename SampleType >
            void operator()( Buffer< SampleType > &_buffer ) {
              int index;
              typename Buffer< SampleType >::SampleType *left_raw_buffer = _buffer.getLeft();
              typename Buffer< SampleType >::SampleType *right_raw_buffer = _buffer.getRight();
              for( index = 0; index != SAMPLE_COUNT; index++ ) {
                writeValue( left_raw_buffer[ index ] );
                if( is_stereo )
                  writeValue( right_raw_buffer[ index ] );
              }
            }
        private:
          void writeValue( float _value ) {
            if( bytes_per_sample == 1 ) {
              int8_t int_value = _value * 127;
              outfile->put( int_value );
            }
            else if( bytes_per_sample == 2 ) {
              int16_t int_value = _value * ( 32767 - 4096 );
              outfile->put( static_cast< char >( int_value ) );
              outfile->put( static_cast< char >( int_value >> 8 ) );
            }
          }
          boost::filesystem::path filepath;
          boost::shared_ptr< std::fstream > outfile;
      };
  }
}

#endif
