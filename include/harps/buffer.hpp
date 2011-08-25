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

#ifndef HARPS_BUFFER
#define HARPS_BUFFER

#include <harps/config.hpp>

namespace harps {
  /*!
   * モジュールの出力を保持するバッファです。
   * モノラル、またはステレオであらかじめ指定された長さの音を保持します。
   */
  template< typename _SampleType >
    class Buffer {
      public:
        typedef _SampleType SampleType;
      /*!
      * コンストラクタ
      */
        Buffer() : is_stereo( 0 ), continue_request( 0 ), end_request( 0 ), used( false ) {}
      /*!
      * デストラクタ
      */
        virtual ~Buffer() {}
      /*!
      * モノラルバッファに使われている配列を取得します。
      */
        inline SampleType *get() {
          return buffer[ 0 ];
        }
      /*!
      * ステレオバッファに使われている左側の音を保持している配列を取得します。
      * \return 配列
      */
        inline SampleType *getLeft() {
          return buffer[ 0 ];
        }
      /*!
      * ステレオバッファに使われている右側の音を保持している配列を取得します。
      * \return 配列
      */
        inline SampleType *getRight() {
          return buffer[ is_stereo ];
        }
      /*!
      * モノラルバッファに使われている配列を取得します。
      * \return 配列
      */
        inline const SampleType *get() const {
          return buffer[ 0 ];
        }
      /*!
      * ステレオバッファに使われている左側の音を保持している配列を取得します。
      * \return 配列
      */
        inline const SampleType *getLeft() const {
          return buffer[ 0 ];
        }
      /*!
      * ステレオバッファに使われている右側の音を保持している配列を取得します。
      * \return 配列
      */
        inline const SampleType *getRight() const {
          return buffer[ is_stereo ];
        }
      /*!
      * バッファをステレオにします。
      */
        inline void setStereo() {
          is_stereo = 1;
        }
      /*!
      * バッファをモノラルにします。
      */
        inline void setMonoral() {
          is_stereo = 0;
        }
      /*!
      * バッファがステレオかどうか確認します。
      * \return ステレオの場合true モノラルの場合false
      */
        inline bool isStereo() const {
          return is_stereo;
        }
      /*!
      * 継続要求を出します。このバッファで音が終わってもらっては困る場合に、モジュールが呼び出します。
      * 継続要求が全く無く、終了要求が1回以上ある場合バッファは音の終了をインスツルメントに提案します。
      * 実際に音が終了するかどうかはインスツルメントに依存します。
      */
        inline void requestContinue() {
          continue_request++;
        }
      /*!
      * 終了要求を出します。このバッファで音が終わっていると考えられる場合に、モジュールが呼び出します。
      * 継続要求が全く無く、終了要求が1回以上ある場合バッファは音の終了をインスツルメントに提案します。
      * 実際に音が終了するかどうかはインスツルメントに依存します。
      */
        inline void requestEnd() {
          end_request++;
        }
      /*!
      * バッファの状態をリセットします。リセットされるのは状態だけでバッファの値はクリアされません。
      */
        inline void reset() {
          continue_request = 0;
          end_request = 0;
          used = false;
        }
      /*!
      * 音を終了すべきかどうかを判断します。
      * 継続要求が全く無く、終了要求が1回以上ある場合バッファは音の終了をインスツルメントに提案します。
      * 実際に音が終了するかどうかはインスツルメントに依存します。
      * \return 終了すべきならtrue 継続すべきならfalse
      */
        inline bool shouldEnd() {
          if( end_request && !( continue_request ) )
            return true;
          else
            return false;
        }
      /*!
      * 複数のバッファの投票を足し合わせます。
      * \param _source 足し合わせるバッファ
      */
        inline void mergeVote( const Buffer< _SampleType > &_source ) {
          continue_request += _source.continue_request;
          end_request += _source.end_request;
        }
      /*!
      * 継続要求の回数を取得します。
      * \return 回数
      */
        inline unsigned int getContinueRequestCount() const {
          return continue_request;
        }
      /*!
      * 終了要求の回数を取得します。
      * \return 回数
      */
        inline unsigned int getEndRequestCount() const {
          return end_request;
        }
      /*!
      * バッファに使用済フラグを立てます。
      */
        void setUsed() {
          used = true;
        }
      /*!
      * バッファが使用済かどうか調べます。
      * \return 使用済ならtrue 未使用ならfalse
      */
        bool getUsed() const {
          return used;
        }
      private:
        bool used;
        int is_stereo;
        SampleType buffer[ 2 ][ SAMPLE_COUNT ];
        unsigned int continue_request;
        unsigned int end_request;
    };
}

#endif
