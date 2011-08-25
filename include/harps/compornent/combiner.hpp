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

#ifndef HARPS_COMBINER
#define HARPS_COMBINER

#include <harps/config.hpp>

#define HARPS_PP_UNUSED \
  BOOST_STATIC_ASSERT( sizeof( int ) ^ sizeof( int ) )

#define HARPS_PP_MODULE_TYPENAME_WITH_DEFAULT( z, module_index, total ) \
  typename BOOST_PP_CAT( ModuleType, module_index ) = \
    Dummy BOOST_PP_COMMA_IF( BOOST_PP_NOT_EQUAL( module_index, BOOST_PP_SUB( total, 1 ) ) )

#define HARPS_PP_MODULE_MEMBER( z, module_index, unused ) \
  BOOST_PP_CAT( ModuleType, module_index ) BOOST_PP_CAT( module, module_index );

#define HARPS_PP_MODULE_TYPENAME( z, module_index, total ) \
  typename BOOST_PP_CAT( ModuleType, module_index ) BOOST_PP_COMMA_IF( BOOST_PP_NOT_EQUAL( module_index, BOOST_PP_SUB( total, 1 ) ) )

#define HARPS_PP_MODULE_SPECIALIZATION_TYPENAMES( z, module_index, unused ) \
  BOOST_PP_CAT( ModuleType, module_index ) BOOST_PP_COMMA()

#define HARPS_PP_MODULE_DUMMY( z, module_index, total ) \
  Dummy BOOST_PP_COMMA_IF( BOOST_PP_NOT_EQUAL( module_index, BOOST_PP_SUB( total, 1 ) ) )

#endif
