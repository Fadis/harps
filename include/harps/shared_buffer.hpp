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


#ifndef HARPS_COMPORNENT_SHARED_BUFFER
#define HARPS_COMPORNENT_SHARED_BUFFER

#include <boost/thread.hpp>
#include <boost/array.hpp>
#include <boost/function.hpp>

namespace harps {
  /*!
   * モジュール内の複数の箇所で共有されるバッファ
   */
  template< typename Tag, typename SampleType, unsigned int count >
    class SharedBuffer {
      public:
        /*!
         * バッファを取得します
         * \param _initializer バッファの初期化に用いる関数
         */
        static boost::array< SampleType, count > &init( boost::function< void ( boost::array< SampleType, count >& ) > _initializer ) {
          static boost::mutex singleton_lock;
          static SharedBuffer< Tag, SampleType, count > *instance;
          boost::mutex::scoped_lock lock ( singleton_lock );
          if ( !instance ) {
            instance = getNonThreadSafe();
            _initializer( instance->buffer );
          }
          return instance->buffer;
        }
      private:
        static SharedBuffer< Tag, SampleType, count > *getNonThreadSafe() {
          static SharedBuffer< Tag, SampleType, count > singleton;
          return &singleton;
        }
        SharedBuffer() {}
        virtual ~SharedBuffer() {}
        boost::array< SampleType, count > buffer;
    };
}

#endif