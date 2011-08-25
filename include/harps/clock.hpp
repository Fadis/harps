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

#ifndef HARPS_CLOCK
#define HARPS_CLOCK

#include <harps/utils.hpp>
#include <harps/config.hpp>

#include <utility>

namespace harps {
  /*!
   * MIDIノートナンバーから周波数に変換します。
   * \param _note ノートナンバー
   * \return 周波数
   */
  inline float noteToFrequency( float _note ) {
    return 13.75f * exp2f( ( _note - 9.0f ) / 12.0f );
  }

  typedef double Time;
  typedef std::pair< Time, Time > TimeMatrix;

  enum {
    GLOBAL = -1,
    LOCAL = 0,
    KEY = 1,
    TONE = 2
  };

  /*!
   * 時刻変換行列の計算をコンパイル時に分岐するためのクラス
   */
  template< unsigned int _which > class ClockMatrixCalc {
  };

  /*!
   * ローカルクロックのキャッシュを更新します
   */
  template<> class ClockMatrixCalc< LOCAL > {
    public:
      inline static void updateCache( TimeMatrix *_cache, TimeMatrix *_coef ) {
        _cache[ LOCAL ] = _coef[ LOCAL ];
        _cache[ KEY ].first = _coef[ LOCAL ].first * _coef[ KEY ].first;
        _cache[ KEY ].second =
          _coef[ LOCAL ].second * _coef[ KEY ].first + _coef[ KEY ].second;
        _cache[ TONE ].first = _coef[ LOCAL ].first * _coef[ TONE ].first;
        _cache[ TONE ].second =
          _coef[ LOCAL ].second * _coef[ TONE ].first + _coef[ TONE ].second;
    }
  };
  /*!
   * キークロックのキャッシュを更新します
   */
  template<> class ClockMatrixCalc< KEY > {
    public:
      inline static void updateCache( TimeMatrix *_cache, TimeMatrix *_coef ) {
        _cache[ KEY ].first = _coef[ LOCAL ].first * _coef[ KEY ].first;
        _cache[ KEY ].second =
          _coef[ LOCAL ].second * _coef[ KEY ].first + _coef[ KEY ].second;
    }
  };
  /*!
   * トーンクロックのキャッシュを更新します
   */
  template<> class ClockMatrixCalc< TONE > {
    public:
      inline static void updateCache( TimeMatrix *_cache, TimeMatrix *_coef ) {
        _cache[ TONE ].first = _coef[ LOCAL ].first * _coef[ TONE ].first;
        _cache[ TONE ].second =
          _coef[ LOCAL ].second * _coef[ TONE ].first + _coef[ TONE ].second;
    }
  };

  /*!
   * 現在時刻を保持します。現在時刻は4つの時刻変換行列を通して取得することができます。
   */
  class CurrentTime {
    public:
      enum {
        MATRIX_COUNT = 3
      };
  /*!
   * コンストラクタ
   * \param _tick_lenght 1クロックの時間
   */
      CurrentTime( Time _tick_length )
        : global_time( 0.0 ), tick_length( _tick_length ), pitch( 0.0f ) {
          int index;
          for( index = 0; index != MATRIX_COUNT; index++ ) {
            time_matrix[ index ].first = 1.0;
            time_matrix[ index ].second = 0.0;
          }
          ClockMatrixCalc< LOCAL >::updateCache( matrix_cache, time_matrix );
      }
  /*!
   * デストラクタ
   */
      virtual ~CurrentTime() {}
  /*!
   * 現在時刻から_offsetクロック先の時刻を指定した行列を通して取得します。
   * \param _offset 現在時刻からのずれ
   * \return 指定された条件での時刻
   */
      template< unsigned int _which >
          inline double getTime( unsigned int _offset ) const {
        double temp = global_time + tick_length * _offset;
        temp = temp * matrix_cache[ _which ].first + matrix_cache[ _which ].second;
        return temp;
      }
  /*!
   * 時刻をリセットします。
   */
      inline void reset() {
        global_time = 0.0;
        int index;
        for( index = 0; index != MATRIX_COUNT; index++ ) {
          time_matrix[ index ].first = 1.0;
          time_matrix[ index ].second = 0.0;
        }
        ClockMatrixCalc< LOCAL >::updateCache( matrix_cache, time_matrix );
      }
  /*!
   * 時刻変換行列を交換します。引数で渡された行列に古い行列が代入されます。
   * \param _matrix 新しい行列
   */
      template< unsigned int _which >
        inline void swapMatrix( TimeMatrix &_matrix ) {
          std::swap( time_matrix[ _which ], _matrix );
          ClockMatrixCalc< _which >::updateCache( matrix_cache, time_matrix );
        }
  /*!
   * 時刻変換行列を取得します。
   * \return 時刻変換行列
   */
      template< unsigned int _which >
        inline const TimeMatrix &getMatrix() const {
          return time_matrix[ _which ];
        }
  /*!
   * 鍵盤が押されたことを通知します。ノートナンバーからトーンクロックの時刻変換行列が自動的に生成されます。また、ローカルクロックとキークロックが0をさすようになります。
   * \param _note ノートナンバー
   */
      inline void noteOn( int _note ) {
        note = _note;
        freq = noteToFrequency( note + pitch );
        time_matrix[ TONE ].first = freq;
        time_matrix[ TONE ].second = 0.0f;
        time_matrix[ LOCAL ].first = 1.0f;
        time_matrix[ LOCAL ].second = -global_time;
        time_matrix[ KEY ].first = 1.0f;
        time_matrix[ KEY ].second = 0.0f;
        ClockMatrixCalc< LOCAL >::updateCache( matrix_cache, time_matrix );
      }
  /*!
   * 鍵盤が離されたことを通知します。また、キークロックが0をさすようになります。
   * \param _note ノートナンバー
   */
      inline void noteOff() {
        time_matrix[ KEY ].first = 1.0f;
        time_matrix[ KEY ].second = -getTime< LOCAL >( 0 );
        ClockMatrixCalc< KEY >::updateCache( matrix_cache, time_matrix );
      }
  /*!
   * ピッチベンドします。
   * \param _pitch ピッチベンド値
   */
      inline void setPitchBend( float _pitch ) {
        pitch = _pitch;
        freq = noteToFrequency( note + pitch );
        float old_time = loop( getTime< TONE >( 0 ) );
        time_matrix[ TONE ].first = freq;
        ClockMatrixCalc< TONE >::updateCache( matrix_cache, time_matrix );
        float new_time = loop( getTime< TONE >( 0 ) );
        time_matrix[ TONE ].second -= new_time - old_time;
        ClockMatrixCalc< TONE >::updateCache( matrix_cache, time_matrix );
      }
  /*!
   * 現在の音の周波数を取得します。
   * \return 周波数
   */
      inline float getToneFrequency() const {
        return freq;
      }
  /*!
   * 現在の音の音階を取得します。
   * \return ノートナンバー
   */
      inline int getTone() const {
        return note;
      }
  /*!
   * 現在のピッチベンド値を取得します。
   * \return ピッチベンド値
   */
      inline float getPitchBend() const {
        return pitch;
      }
  /*!
   * 時刻を指定したクロック数分進めます。
   * \param _sample_count クロック数
   */
      inline void tick( unsigned int _sample_count ) {
        global_time += tick_length * _sample_count;
      }
    private:
      Time global_time;
      const Time tick_length;
      TimeMatrix time_matrix[ MATRIX_COUNT ];
      TimeMatrix matrix_cache[ MATRIX_COUNT ];
      Time clock_cache[ MATRIX_COUNT ];
      int note;
      float pitch;
      float freq;
  };

  /*!
   * CurrentTimeのtick幅をバッファの長さに固定したものです。
   */
  template< unsigned int _sampling_rate, unsigned int _sample_count >
    class Clock : public CurrentTime {
      public:
        Clock() :
          CurrentTime( 1.0 / static_cast< double >( _sampling_rate ) ) {}
        virtual ~Clock() {}
        inline void tick() {
          CurrentTime::tick( _sample_count );
        }
      private:
    };
}

#endif
