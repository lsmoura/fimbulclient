/*
	YA3DE is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	YA3DE is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with YA3DE.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef _GLCONTEXT_H_
#define _GLCONTEXT_H_

#ifdef _WIN32
#include <YA3DE/System/Win32GLContext.h>
#elif defined(_LINUX)
#include <YA3DE/System/XGLContext.h>
#else
#error "This platform is not supported yet."
#endif

#endif
