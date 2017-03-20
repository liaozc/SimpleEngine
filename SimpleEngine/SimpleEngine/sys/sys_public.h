#ifndef __SYS_PUBLIC__
#define __SYS_PUBLIC__

// Win32
#if defined(WIN32) || defined(_WIN32)

#define ALIGN16( x )					__declspec(align(16)) x
#define PACKED

#define _alloca16( x )					((void *)((((int)_alloca( (x)+15 )) + 15) & ~15))

#define PATHSEPERATOR_STR				"\\"
#define PATHSEPERATOR_CHAR				'\\'

#define SE_INLINE						__forceinline
#define SE_STATIC_TEMPLATE				static

#define assertmem( x, y )				assert( _CrtIsValidPointer( x, y, true ) )

#endif

typedef unsigned int			dword;		// 32 bits

#ifdef INSIDE_ENGINE
#define DLL_INTERFACE __declspec( dllexport )
#else
#define DLL_INTERFACE __declspec(dllimport)
#endif

#endif