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

#ifndef HARPS_COMPORNENT_VECTOR
#define HARPS_COMPORNENT_VECTOR

#include <harps/utils.hpp>
#include <harps/clock.hpp>
#include <harps/buffer.hpp>
#include <harps/note.hpp>
#include <harps/normalize.hpp>
#include <harps/shared_buffer.hpp>
#include <harps/config.hpp>

#include <boost/array.hpp>

namespace harps {
  namespace compornent {
    template< unsigned int array_size >
      class Vector {
        public:
          Vector() {}
          struct Point {
            float x;
            float y;
          };
          virtual ~Vector() {}
          template< typename TagType, typename PointIterator >
            void init( PointIterator _begin, PointIterator _end ) {
              std::map< float, float > sorted;
              sorted[ 0.0f ] = 0.0f;
              for( ; _begin != _end; _begin++ )
                sorted[ _begin->x ] = _begin->y;
              std::map< float, float >::const_iterator last_iter = sorted.end();
              last_iter--;
              total_time = last_iter->first;
              cache =
                SharedBuffer< TagType, float, array_size >::init(
                  boost::bind( &Vector< array_size >::initInternal, _1, total_time, sorted )
                );
            }
          static void initInternal(
            boost::array< float, array_size > &_dest,
            float total_time,
            const std::map< float, float > &_sorted
          ) {
            std::map< float, float >::const_iterator previous = sorted.begin();
            std::map< float, float >::const_iterator current = sorted.begin();
            current++;
            std::map< float, float >::const_iterator end = sorted.end();
            int index;
            for( ; current != end; previous = current, current++ ) {
              // y = ax + b
              float a = ( current->y - previous->y ) / ( current->x - previous->x );
              float b = -a * current->x + current->y;
              for( index = 0; index != _dest.size(); index++ ) {
                double current_time = total_time * index / _dest.size();
                _dest[ index ] = a * current_time + b;
              }
            }
          }
          template< typename SampleType >
            inline void operator()( Buffer< SampleType > &_buffer, CurrentTime &_clock, Note &_note ) {
              int index;
              typename Buffer< SampleType >::SampleType *raw_buffer = _buffer.get();
              for( index = 0; index != SAMPLE_COUNT; index++ )
                raw_buffer[ index ] = noteon_cache[ static_cast<int>( time / total_time * array_size ) ];
            }
      private:
        boost::array< float, array_size > &cache;
        float total_time
    };
  }
}
