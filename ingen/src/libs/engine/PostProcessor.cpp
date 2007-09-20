/* This file is part of Ingen.
 * Copyright (C) 2007 Dave Robillard <http://drobilla.net>
 * 
 * Ingen is free software; you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 * 
 * Ingen is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include <cassert>
#include <iostream>
#include <pthread.h>
#include <raul/SRSWQueue.hpp>
//#include <raul/Maid.hpp>
#include "Event.hpp"
#include "PostProcessor.hpp"

using std::cerr; using std::cout; using std::endl;

namespace Ingen {


PostProcessor::PostProcessor(size_t queue_size)
    : _events(queue_size)
{
}


void
PostProcessor::process()
{
	while ( ! _events.empty()) {
		Event* const ev = _events.front();
		_events.pop();
		assert(ev);
		ev->post_process();
        delete ev;
	}
}


} // namespace Ingen
