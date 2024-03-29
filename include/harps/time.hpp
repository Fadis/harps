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


#ifndef HARPS_TIME
#define HARPS_TIME

#include <harps/config.hpp>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>


namespace harps {
  /*!
   * 現在時刻を取得します。
   * \return 現在時刻
   */
  inline double getTime() {
    struct timeval tv;
    gettimeofday( &tv, NULL );
    return static_cast< double >( tv.tv_sec ) + static_cast< double >( tv.tv_usec ) * 0.000001;
  }

  /*!
   * 指定した時刻までプロセスを停止させます。
   * \param _until 再開予定時刻
   */
  inline void sleep( double _until ) {
    long int sleep_time = static_cast< long int >( ( _until - getTime() ) * 1000000 );
    usleep( sleep_time );
  }
}

#endif
