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


#ifndef HARPS_NOTE
#define HARPS_NOTE

namespace harps {
  /*!
   * ノートは発音中の音の音階と鍵盤を押した強さ、鍵盤の現在の状態を保持します。
   */
  class Note {
    public:
      enum NoteState {
        NOTE_ON = 1,
        NOTE_OFF = 2,
        NOTE_WAIT = 3
      };
      /*!
       * コンストラクタ
       */
      Note() : status( NOTE_WAIT ) {}
      /*!
       * デストラクタ
       */
      virtual ~Note() {}
      /*!
       * 指定した強さで鍵盤を押します。
       * \param _touch 鍵盤を押す強さ
       */
      void noteOn( float _touch = 1.0f ) {
        status = NOTE_ON;
        touch = _touch;
      }
      /*!
       * 鍵盤から指を離します
       */
      void noteOff() {
        status = NOTE_OFF;
      }
      /*!
       * 発音を終了します
       */
      void noteWait() {
        status = NOTE_WAIT;
      }
      /*!
       * 現在の音の状態を取得します
       * \return 音の状態
       */
      NoteState getStatus() const {
        return status;
      }
      /*!
       * 現在発音中の音の鍵盤が押された時の強さを取得します
       * \return 鍵盤を押した強さ
       */
      float getTouch() const {
        return touch;
      }
    private:
      NoteState status;
      float touch;
  };
}

#endif
