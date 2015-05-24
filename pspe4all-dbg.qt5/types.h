/*
This file is part of pcsp.

pcsp is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

pcsp is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with pcsp.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef TYPES_H_
#define TYPES_H_

typedef long long s64;
typedef int s32;
typedef short s16;
typedef char s8;
typedef unsigned long long u64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef float f32;

#define DO_PRAGMA(x) _Pragma (#x)
#define TODO(x) DO_PRAGMA(message ("TODO - " #x))

#ifdef __GNUC__
#define __forceinline inline __attribute__((always_inline))
#endif

typedef u64 insn_count_t;

#if defined(WIN32) || defined(__WINS__) || defined(__MINGW32__) || defined(_MSC_VER)
#define inline __inline
#define snprintf _snprintf
#endif


#endif /* TYPES_H_ */
