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


#ifndef HARPS_OUTPUT_ALSA
#define HARPS_OUTPUT_ALSA

#include <harps/config.hpp>
#include <harps/time.hpp>
#include <harps/exceptions.hpp>

#include <boost/shared_ptr.hpp>

#include <alsa/asoundlib.h>

namespace harps {
    /*!
     * オーディオ出力に関するクラスはこの名前空間にまとめられています。
     */
  namespace output {
    /*!
     * Linuxのオーディオシステム、Advanced Linux Audio Architecture( http://www.alsa-project.org/ )を使って再生します。
     */
    template< bool is_stereo, unsigned int bytes_per_sample >
      class ALSA {
        public:
              /*!
               * コンストラクタ
               * \param _filename 出力デバイス名
               */
          ALSA( const char *_filename ) : system_time( 0.0 ) {
            int open_result = snd_pcm_open( &pcm_raw, _filename, SND_PCM_STREAM_PLAYBACK, 0 );
            if( open_result )
              throw UnableToOpenSink();
            pcm.reset( pcm_raw, &snd_pcm_close );
            int param_result =
              snd_pcm_set_params( pcm_raw, SND_PCM_FORMAT_S16_LE, SND_PCM_ACCESS_RW_INTERLEAVED,
                                  1, SAMPLING_RATE, 1, 20000 );
            if( param_result )
              throw SinkConfigurationFailed();
          }
              /*!
               * デストラクタ
               */
          virtual ~ALSA() {}
              /*!
               * バッファを再生します
               * \param _buffer バッファ
               */
          template< typename SampleType >
            void operator()( Buffer< SampleType > &_buffer ) {
              int index;
              typename Buffer< SampleType >::SampleType *left_raw_buffer = _buffer.getLeft();
              typename Buffer< SampleType >::SampleType *right_raw_buffer = _buffer.getRight();
              int16_t int_buffer[ SAMPLE_COUNT ];
              for( index = 0; index != SAMPLE_COUNT; index++ )
                int_buffer[ index ] = static_cast< int16_t >( left_raw_buffer[ index ] * ( 32767 - 4096 ) );
              int write_result = snd_pcm_writei ( pcm_raw, static_cast< const void* >( int_buffer ), SAMPLE_COUNT );
              if( write_result < 0 ) {
                write_result = snd_pcm_recover( pcm_raw, write_result, 0 );
                if( write_result < 0 ) {
                  throw SinkOutputFailed();
                }
              }
            }
          private:
            snd_pcm_t *pcm_raw;
            boost::shared_ptr< snd_pcm_t > pcm;
            double system_time;
      };
  }
}

#endif