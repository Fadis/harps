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

#ifndef HARPS_UTILS
#define HARPS_UTILS

#include <harps/table/sine.hpp>
#include <harps/table/exp2.hpp>

#include <cmath>
#include <tr1/cstdint>

namespace harps {
  /*!
   * 入力値を0.0から1.0(1.0を含まない)の間でループします。
   * \param _source 入力値
   * \return 出力値
   */
  inline float loop( float _source ) {
    return _source - ::floorf( _source );
  }
  /*!
   * 入力値を0.0から1.0(1.0を含まない)の間でループします。
   * \param _source 入力値
   * \return 出力値
   */
  inline double loop( double _source ) {
    return _source - ::floor( _source );
  }
  /*!
   * テーブルを使って高速に正弦の近似値を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return sin( _theta )
   */
  inline float sin( float _theta ) {
    return table::sine[ static_cast< int >( loop( _theta ) * HARPS_SINE_TABLE_SIZE ) ];
  }
  /*!
   * テーブルを使って高速に正弦の近似値を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return sin( _theta )
   */
  inline double sin( double _theta ) {
    return table::sine[ static_cast< int >( loop( _theta ) * HARPS_SINE_TABLE_SIZE ) ];
  }
  /*!
   * テーブルを使って高速に音量と実際の振幅の変換を行います。
   * \param _linear 音量
   * \return 振幅
   */
  inline float volume( float _linear ) {
    if( _linear >= 1.0f )
      return 0.999023f;
    else if( _linear < 0.0f )
      return 0.0f;
    else
      return table::exp2[ static_cast< int >( _linear * HARPS_EXP2_TABLE_SIZE ) ];
  }
  /*!
   * テーブルを使って高速に音量と実際の振幅の変換を行います。
   * \param _linear 音量
   * \return 振幅
   */
  inline double volume( double _linear ) {
    if( _linear >= 1.0 )
      return 0.999023;
    else if( _linear < 0.0 )
      return 0.0;
    else
      return table::exp2[ static_cast< int >( _linear * HARPS_EXP2_TABLE_SIZE ) ];
  }
  /*!
   * 三角波を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return triangle( _theta )
   */
  inline float triangle( float _theta ) {
    float loop_theta = loop( _theta );
    if( loop_theta < 0.25f )
      return loop_theta * 4.0f;
    else if( loop_theta < 0.75f )
      return loop_theta * -4.0f + 2.0f;
    else
      return loop_theta * 4.0f - 4.0f;
  }
  /*!
   * 三角波を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return triangle( _theta )
   */
  inline double triangle( double _theta ) {
    double loop_theta = loop( _theta );
    if( loop_theta < 0.25 )
      return loop_theta * 4.0;
    else if( loop_theta < 0.75 )
      return loop_theta * -4.0 + 2.0;
    else
      return loop_theta * 4.0 - 4.0;
  }

  /*!
   * 矩形波を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return rectangle( _theta )
   */
  inline float rectangle( float _duty, float _theta ) {
    float loop_duty = loop( _duty );
    float loop_theta = loop( _theta );
    if( loop_theta < loop_duty )
      return 1.0f;
    else
      return 0.0f;
  }
  /*!
   * 矩形波を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return rectangle( _theta )
   */
  inline double rectangle( double _duty, double _theta ) {
    double loop_duty = loop( _duty );
    double loop_theta = loop( _theta );
    if( loop_theta < loop_duty )
      return 1.0;
    else
      return 0.0;
  }
  /*!
   * ファミコンっぽい三角波を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return triangle( _theta )をある程度の精度で丸めたもの
   */
  inline float nes( float _theta ) {
    float loop_theta = loop( _theta );
    float result;
    if( loop_theta < 0.25f )
      result = loop_theta * 4.0f;
    else if( loop_theta < 0.75f )
      result = loop_theta * -4.0f + 2.0f;
    else
      result = loop_theta * 4.0f - 4.0f;
    return roundf( result * 7.0f ) / 7.0f;
  }
  /*!
   * ファミコンっぽい三角波を返します。
   * \param _theta 角度(1周を1.0とする)
   * \return triangle( _theta )をある程度の精度で丸めたもの
   */
  inline double nes( double _theta ) {
    double loop_theta = loop( _theta );
    double result;
    if( loop_theta < 0.25 )
      result = loop_theta * 4.0;
    else if( loop_theta < 0.75 )
      result = loop_theta * -4.0 + 2.0;
    else
      result = loop_theta * 4.0 - 4.0;
    return round( result * 7.0 ) / 7.0;
  }
}

#endif
