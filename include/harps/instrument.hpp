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

#ifndef HARPS_INSTRUMENT
#define HARPS_INSTRUMENT

#include <harps/buffer.hpp>
#include <harps/clock.hpp>
#include <harps/normalize.hpp>
#include <harps/dummy.hpp>
#include <harps/compornent/dynamic_module.hpp>

#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

#include <tbb/parallel_for.h>
#include <tbb/blocked_range.h>

#include <dlfcn.h>

/*!
 * harpsはテンプレートベースで作られたモジュールシンセサイザーです。
 * harpsではスタック操作の最適化の効果を最大限に得るために殆どの関数はインラインかされています。
 */
namespace harps {
  /*!
   * モジュールの発音とクロックを管理するインスツルメントクラスです。
   * ダイナミックモノフォニーは外部トーンモジュールを読み込んで同時に1音を鳴らすことが出来ます。
   */
  class DynamicMonophony {
    public:
      /*!
      * コンストラクタ
      */
      DynamicMonophony() : clock ( 1.0 / static_cast< double > ( SAMPLING_RATE ) ) {}
      /*!
      * デストラクタ
      */
      virtual ~DynamicMonophony() {}
      /*!
      * モジュールを実行し、クロックを1ブロック分進めます。
      * \param _buffer 実行結果を出力するバッファブロック
      */
      template< typename SampleType >
      inline void operator() ( Buffer< SampleType > &_buffer ) {
        ( *module ) ( _buffer, clock, note );
        clock.tick ( SAMPLE_COUNT );
      }
      /*!
      * 指定した鍵盤を押された状態にします。
      * \param _note 鍵盤(MIDIノートナンバーで指定)
      * \param _touch 鍵盤を押す強さ
      * \return ノートID(モノフォニーは1音しか発音しないため、ノートIDは必ず0になります)
      */
      inline int noteOn ( int _note, float _touch ) {
        clock.noteOn ( _note );
        note.noteOn ( _touch );
        return 0;
      }
      /*!
      * 現在押している鍵盤から指を離します。モジュールによっては鍵盤から指を離してもすぐに音は止まりません。音を完全に止めてインスツルメントを待機状態にするにはnoteWaitを呼び出す必要があります。
      * \param _dummy ノートID(ポリフォニーとインターフェースを揃えるために用意されています。この値は無視されます)
      */
      inline void noteOff ( int _dummy = 0 ) {
        clock.noteOff();
        note.noteOff();
      }
      /*!
       * 発音処理を終了します。
       * \param _dummy ノートID(ポリフォニーとインターフェースを揃えるために用意されています。この値は無視されます)
       */
      inline void noteWait ( int _dummy = 0 ) {
        note.noteWait();
      }
      /*!
       * ピッチベンドします。設定したピッチベンド値はresetされるまで引き継がれます。
       * \param _pitch ピッチ(1.0で音階が1上がり、12.0で1オクターブ上がります)
       */
      inline void setPitchBend ( float _pitch ) {
        clock.setPitchBend ( _pitch );
      }
      /*!
       * インスツルメントをリセットします。設定されたピッチベンドは0に戻ります。
       */
      inline void reset() {
        clock.reset();
      }
      /*!
       * 現在のノートの状態を取得します。
       * \return ノートの状態
       */
      inline Note::NoteState getStatus() const {
        return note.getStatus();
      }
      /*!
       * 現在の処理中の箇所の時刻を返します。
       * \return 現在時刻
       */
      inline double getGlobalTime() {
        return clock.getTime< 0 > ( 0 );
      }
      /*!
       * モジュールを変更します。
       * \param _filename 新しいモジュールのファイル名
       */
      void programChange ( const char *_filename ) {
        module.reset ( new DynamicModuleSlot ( _filename ) );
      }
    private:
      boost::shared_ptr< DynamicModuleSlot > module;
      CurrentTime clock;
      Note note;
  };

  /*!
   * モジュールの発音とクロックを管理するインスツルメントクラスです。
   * ダイナミックポリフォニーは外部トーンモジュールを読み込んで同時に複数音を鳴らすことが出来ます。
   */
  template< typename MonophonyType, unsigned int max_polyphony >
  class DynamicPolyphony {
    public:
      /*!
      * コンストラクタ
      */
      DynamicPolyphony() : current_note_id ( 0 ), default_pitch ( 0.0f ), clock ( 1.0 / static_cast< double > ( SAMPLING_RATE ) ) {
        int monophony_index;
        for ( monophony_index = 0; monophony_index != max_polyphony; monophony_index++ )
          active_since[ monophony_index ] = 0;
      }
      /*!
      * デストラクタ
      */
      virtual ~DynamicPolyphony() {}
      /*!
      * 全てのモジュールを実行しクロックを1ブロック分進めます。
      * \param _buffer 実行結果の総和を出力するバッファブロック
      */
      template< typename SampleType >
      void operator() ( Buffer< SampleType > &_buffer ) {
        typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
        int sample_index;
        for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
          raw_buffer[ sample_index ] = 0.0f;

        Buffer< SampleType > temp_buffer[ max_polyphony ];
        int monophony_index;
        tbb::parallel_for ( tbb::blocked_range< unsigned int > ( 0, max_polyphony, 4 ),
                       Renderer< SampleType > ( monophony, temp_buffer ) );
        for ( monophony_index = 0; monophony_index != max_polyphony; monophony_index++ ) {
          for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
            if ( temp_buffer[ monophony_index ].getUsed() )
              raw_buffer[ sample_index ] += temp_buffer[ monophony_index ].get() [ sample_index ];
        }

        Buffer< SampleType > amp_buffer;
        int index;
        typename Buffer< SampleType >::SampleType *raw_amp_buffer = amp_buffer.get();
        for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ ) {
          normalizer.setValue ( raw_buffer[ sample_index ] );
          raw_amp_buffer[ sample_index ] = normalizer.getAmp();
        }
        reduceNormalizingNoize ( amp_buffer );
        for ( sample_index = 0; sample_index != SAMPLE_COUNT; sample_index++ )
          raw_buffer[ sample_index ] /= raw_amp_buffer[ sample_index ];

        clock.tick ( SAMPLE_COUNT );
      }
      /*!
      * 指定した鍵盤を押された状態にします。
      * \param _note 鍵盤(MIDIノートナンバーで指定)
      * \param _touch 鍵盤を押す強さ
      * \return ノートID
      */
      inline int noteOn ( int _note, float _touch ) {
        int monophony_id = getNewMonophony();
        if ( monophony_id == -1 )
          monophony_id = killOldMonophony();
        monophony[ monophony_id ].noteOn ( _note, _touch );
        monophony[ monophony_id ].setPitchBend ( default_pitch );
        current_note_id++;
        active_since[ monophony_id ] = current_note_id;
        return current_note_id;
      }
      /*!
      * 現在押している鍵盤から指を離します。モジュールによっては鍵盤から指を離してもすぐに音は止まりません。音を完全に止めてインスツルメントを待機状態にするにはnoteWaitを呼び出す必要があります。
      * \param _note_id 指を離す鍵盤をnoteOn時に取得したノートIDで指定します
      */
      inline void noteOff ( int _note_id ) {
        int monophony_id = findMonophony ( _note_id );
        if ( monophony_id != -1 )
          monophony[ monophony_id ].noteOff();
      }
      /*!
       * ピッチベンドします。設定したピッチベンド値は指定した音のみに影響します。
       * \param _note_id ノートID
       * \param _pitch ピッチ(1.0で音階が1上がり、12.0で1オクターブ上がります)
       */
      inline void setPitchBend ( int _note_id, float _pitch ) {
        int monophony_id = findMonophony ( _note_id );
        if ( monophony_id != -1 )
          monophony[ monophony_id ].setPitchBend ( _pitch );
      }
      /*!
       * ピッチベンドします。設定したピッチベンド値は発音中の全ての音に影響します。
       * \param _pitch ピッチ(1.0で音階が1上がり、12.0で1オクターブ上がります)
       */
      inline void setPitchBend ( float _pitch ) {
        int index;
        default_pitch = _pitch;
        for ( index = 0; index != max_polyphony; index++ )
          monophony[ index ].setPitchBend ( default_pitch );
      }
      /*!
       * インスツルメントをリセットします。それまでに生成されたNoteIDは全て無効になります。無効になったNoteIDを使ってnoteOffした場合の動作は未定義です。
       */
      inline void reset() {
        int index;
        current_note_id = 0;
        default_pitch = 0.0f;
        for ( index = 0; index != max_polyphony; index++ )
          monophony[ index ].reset();
        clock.reset();
      }
      /*!
       * 指定したIDの音が割り当てられているモノフォニーインスツルメントのIDを返します。これはnoteOnした音が実際に発音されているか、あるいはインスツルメントが最大同時発音数に達した等の理由によって発音されなかったかを調べるために使うことが出来ます。
       * \param _note_id ノートID
       * \return モノフォニーインスツルメントのID(見つからなかった場合は-1)
       */
      inline int findMonophony ( int _note_id ) {
        int index;
        for ( index = 0; index != max_polyphony; index++ )
          if ( active_since[ index ] == _note_id )
            return index;
        return -1;
      }
      /*!
       * 現在の処理中の箇所の時刻を返します。
       * \return 現在時刻
       */
      inline double getGlobalTime() {
        return clock.template getTime< 0 > ( 0 );
      }
      /*!
       * モジュールを変更します。
       * \param _filename 新しいモジュールのファイル名
       */
      void programChange ( const char *_filename ) {
        int index;
        for ( index = 0; index != max_polyphony; index++ )
          monophony[ index ].programChange ( _filename );
      }
    private:
      /*!
      * これはダイナミックポリフォニーがIntel Threading Building Blocksでモジュールの実行を分散するために使う内部クラスです。
       */
      template< typename SampleType >
      class Renderer {
        public:
          Renderer ( MonophonyType *_monophony, Buffer< SampleType > *_buffer ) : monophony ( _monophony ), buffer ( _buffer ) {}
          void operator() ( const tbb::blocked_range<unsigned int> &_r ) const {
            unsigned int index;
            for ( index = _r.begin(); index != _r.end(); index++ ) {
              MonophonyType &current_monophony = monophony[ index ];
              Buffer< SampleType > &current_buffer = buffer[ index ];
              if ( current_monophony.getStatus() != Note::NOTE_WAIT ) {
                current_buffer.reset();
                current_monophony ( current_buffer );
                bool end_flag = current_buffer.shouldEnd();
                if ( end_flag )
                  current_monophony.noteWait();
                current_buffer.setUsed();
              }
            }
          }
        private:
          MonophonyType * const monophony;
          Buffer< SampleType > * const buffer;
      };
      /*!
       * 新しい音を発音するためのモノフォニーインスツルメントを取得します。
       * \return モノフォニーインスツルメントのID (空きがなければ-1)
       */
      inline int getNewMonophony() {
        int index;
        for ( index = 0; index != max_polyphony; index++ )
          if ( monophony[ index ].getStatus() == Note::NOTE_WAIT )
            return index;
        return -1;
      }
      /*!
       * 発音を打ち切っても影響が少ないと考えられる音を選んで終了させます。
       * \return 発音終了させたモノフォニーインスツルメントのID
       */
      inline int killOldMonophony() {
        int oldest_monophony = -1;
        unsigned int oldest_time = current_note_id;
        int index;
        for ( index = 0; index != max_polyphony; index++ )
          if ( active_since[ index ] <= oldest_time ) {
            if ( monophony[ index ].getStatus() == Note::NOTE_OFF ) {
              oldest_monophony = index;
              oldest_time = active_since[ index ];
            }
          }
        if ( oldest_monophony != -1 )
          return oldest_monophony;
        else {
          for ( index = 0; index != max_polyphony; index++ )
            if ( active_since[ index ] <= oldest_time ) {
              oldest_monophony = index;
              oldest_time = active_since[ index ];
            }
          monophony[ oldest_monophony ].noteOff();
          return oldest_monophony;
        }
      }
      Normalizer< SAMPLING_RATE * 10 > normalizer;
      MonophonyType monophony[ max_polyphony ];
      unsigned int current_note_id;
      float default_pitch;
      unsigned int active_since[ max_polyphony ];
      CurrentTime clock;
  };
}

#endif
