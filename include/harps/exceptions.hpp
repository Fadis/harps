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

#ifndef HARPS_EXCEPTIONS
#define HARPS_EXCEPTIONS

#include <harps/config.hpp>
#include <stdexcept>

namespace harps {
  /*!
   * Harpsの中で投げられる例外はこのクラスを継承します。
   */
  class HarpsException : public std::domain_error {
    public:
      HarpsException( const char *_value ) : std::domain_error( _value ) {}
  };
  /*!
   * 外部モジュールが見つからない場合この例外が投げられます。
   */
  class ModuleNotFound : public HarpsException {
    public:
      ModuleNotFound() : HarpsException( "module not found" ) {}
  };
  /*!
   * モジュールのインスタンスを生成出来ない場合はこの例外が投げられます。
   */
  class UnableToCreateInstance : public HarpsException {
    public:
      UnableToCreateInstance() : HarpsException( "unable to create the instance" ) {}
  };
  /*!
   * 出力を開くことが出来ない場合はこの例外が投げられます。
   */
  class UnableToOpenSink : public HarpsException {
    public:
      UnableToOpenSink() : HarpsException( "unable to open the sink" ) {}
  };
  /*!
   * 出力にパラメータの指定が出来ない場合はこの例外が投げられます。
   */
  class SinkConfigurationFailed : public HarpsException {
    public:
      SinkConfigurationFailed() : HarpsException( "the sink configuration failed" ) {}
  };
  /*!
   * 出力に失敗した場合はこの例外が投げられます。
   */
  class SinkOutputFailed : public HarpsException {
    public:
      SinkOutputFailed() : HarpsException( "output to the sink failed" ) {}
  };
}

#endif
