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

#ifndef HARPS_INPUT_SIMPLE
#define HARPS_INPUT_SIMPLE

#include <harps/config.hpp>

#include <utility>
#include <stack>

#include <boost/shared_ptr.hpp>
#include <boost/array.hpp>

#define NL( name ) \
  ( ( name ) * ( 60.0 / tempo ) )

#define N32 \
  NL( 0.125 )

#define N16 \
  NL( 0.25 )

#define N8 \
  NL( 0.5 )

#define N4 \
  NL( 1.0 )

#define N2 \
  NL( 2.0 )

#define N1 \
  NL( 4.0 )

namespace harps {
      /*!
       * 楽譜の入力に関するクラスはこの名前空間にまとめられています。
       */
  namespace input {
      /*!
       * SimpleReaderが読む楽譜データの要素です。
       */
    struct Score {
      /*!
       * この音を発音する時刻です。前の音より後でなければなりません。
       */
      double pos;
      /*!
       * この音の長さです。長さ0のノートは曲の終了を意味します。
       */
      float length;
      /*!
       * この音の音階です。
       */
      unsigned int note;
      /*!
       * この音を発音する時の鍵盤を叩く強さです。
       */
      float touch;
    };

      /*!
       * 配列から楽譜データを読み出すシンプルな入力クラスです。
       */
    template< typename InstrumentType >
    class SimpleReader {
      public:
      /*!
       * コンストラクタ
       * \param _score 楽譜データ
       */
        SimpleReader ( const Score * const _score ) : score ( _score ), current_score ( _score ), is_end ( false ) {}
       /*!
        * デストラクタ
        */
        virtual ~SimpleReader() {}
      /*!
       * 楽譜を読んでオーディオデータを出力します。
       * \param _buffer 出力バッファ
       */
        template< typename SampleType >
        void operator() ( Buffer< SampleType > &_buffer ) {
          if ( is_end ) {
            fillZero ( _buffer );
            return;
          }
          double time = instrument.getGlobalTime();
          while ( !release_stack.empty() && time - release_stack.top().first >= -0.00001f ) {
            instrument.noteOff ( release_stack.top().second );
            release_stack.pop();
          }
          while ( time - current_score->pos >= -0.00001f ) {
            if ( current_score->length == 0.0f ) {
              is_end = true;
              fillZero ( _buffer );
              return;
            }
            else {
              std::pair< double, int > temp;
              temp.first = current_score->pos + current_score->length;
              temp.second = instrument.noteOn ( current_score->note, exp2f ( ( current_score->touch - 1.0f ) * 10.0f ) );
              release_stack.push ( temp );
            }
            current_score++;
          }
          instrument ( _buffer );
        }
      /*!
       * 楽譜が終端に達しているかどうかを調べます
       * \return 終端ならtrue そうでなければfalse
       */
        inline bool isEnd() const {
          return is_end;
        }
      /*!
       * モジュールを変更します。
       * \param _filename 新しいモジュールのファイル名
       */
        void programChange ( const char *_filename ) {
          instrument.programChange ( _filename );
        }
      private:
        template< typename SampleType >
        void fillZero ( Buffer< SampleType > &_buffer ) {
          typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
          int sample_index;
          for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
            raw_buffer[ sample_index ] = 0.0f;
        }
        InstrumentType instrument;
        std::stack< std::pair< double, int > > release_stack;
        const Score *current_score;
        const Score * const score;
        bool is_end;
    };

      /*!
       * 複数のSimpleReaderを束ねて2つ以上の楽器を同時に演奏します。
       */
    template< typename OutputType, typename ReaderType, typename BufferType, unsigned int track_count >
    class Tracks {
      public:
      /*!
       * コンストラクタ
       * \param _sink オーディオデータの出力先
       */
        Tracks ( const char *_sink ) : output ( _sink ) {}
        void setScore ( unsigned int _target, const char *_prog, const harps::input::Score *_score ) {
          readers[ _target ].reset ( new ReaderType ( _score ) );
          readers[ _target ]->programChange ( _prog );
          buffers[ _target ].reset ( new BufferType );
        }
      /*!
       * 楽譜を読んでオーディオデータを生成し、指定された出力先に出力します。
       */
        void operator() () {
          tbb::parallel_for ( tbb::blocked_range< unsigned int > ( 0, track_count, 1 ),
                         TrackRunner ( readers, buffers ) );
          BufferType sum;
          Buffer< float >::SampleType *sum_raw = sum.get();
          unsigned int sample_index;
          for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
            sum_raw[ sample_index ] = 0.0;
          unsigned int track_index;
          for ( track_index = 0; track_index != track_count; track_index++ ) {
            if ( buffers[ track_index ] ) {
              Buffer< float >::SampleType *buffer_raw = buffers[ track_index ]->get();
              for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
                sum_raw[ sample_index ] += buffer_raw[ sample_index ];
            }
          }
          BufferType nlevel;
          Buffer< float >::SampleType *nlevel_raw = nlevel.get();
          for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ ) {
            normalizer.setValue ( sum_raw[ sample_index ] );
            nlevel_raw[ sample_index ] = normalizer.getAmp();
          }
          reduceNormalizingNoize ( nlevel );
          for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
            sum_raw[ sample_index ] /= nlevel_raw[ sample_index ];
          output ( sum/*, SAMPLE_COUNT*/ );
        }
      /*!
       * 楽譜が終端に達しているかどうかを調べます
       * \return 終端ならtrue そうでなければfalse
       */
        bool isEnd() {
          unsigned int track_index;
          for ( track_index = 0; track_index != track_count; track_index++ )
            if ( readers[ track_index ] )
              return readers[ track_index ]->isEnd();
        }
      private:
        class TrackRunner {
          public:
            TrackRunner ( boost::array< boost::shared_ptr< ReaderType >, track_count > &_readers,
                          boost::array< boost::shared_ptr< BufferType >, track_count > &_buffers )
                : readers ( _readers ), buffers ( _buffers ) {}
            void operator() ( const tbb::blocked_range<unsigned int> &_r ) const {
              unsigned int index;
              for ( index = _r.begin(); index != _r.end(); index++ ) {
                if ( readers[ index ] )
                  ( *readers[ index ] ) ( *buffers[ index ] );
              }
            }
          private:
            boost::array< boost::shared_ptr< ReaderType >, track_count > &readers;
            boost::array< boost::shared_ptr< BufferType >, track_count > &buffers;
        };
        OutputType output;
        harps::Normalizer< SAMPLING_RATE * 10 > normalizer;
        boost::array< boost::shared_ptr< ReaderType >, track_count > readers;
        boost::array< boost::shared_ptr< BufferType >, track_count > buffers;
    };
  }
}

#endif
