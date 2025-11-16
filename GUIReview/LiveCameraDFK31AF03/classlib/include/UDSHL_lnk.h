
/** This file checks the compiler version and binds to the udshl library and other libraries needed.
 * To use the link feature you must define the UDSHL_LIB_BASEDIR macro.
 * UDSHL_LIB_BASEDIR must contain the relative path to the lib base directory of imaging control.
 *
 * For example this define is used by the samples :
	#define UDSHL_LIB_BASEDIR "..\..\..\ClassLib\"
 * This is automatically expanded to point to the right file for the build.
 *
 * You can prevent linking with anything by specifying UDSHL_LIB_NO_LINK.
 *
 * This file checks the following defines :
	_MSC_VER	// compiler version, defined by the compiler
	_MT			// version of the C runtime, is defined by the compiler when you choose "Multithreaded debug/release DLL"
	_DLL		// version of the C runtime, is defined by the compiler when you choose "Multithreaded debug/release DLL"
 *
 * You may pass UDSHL_LIB_NO_COMPILER_CHECK to prevent the compiler checks.
 * 
 */

#ifndef UDSHL_LNK_H_INC_
#define UDSHL_LNK_H_INC_

#pragma once

#if !defined UDSHL_LIB_DIR
	#if defined UDSHL_LIB_BASEDIR
		#ifdef _DEBUG
			#define UDSHL_LIB_DIR UDSHL_LIB_BASEDIR "debug/"
		#else
			#define UDSHL_LIB_DIR UDSHL_LIB_BASEDIR "release/"
		#endif
	#else 
		#define UDSHL_LIB_DIR ""
	#endif
#endif

#ifndef UDSHL_LIB_NO_COMPILER_CHECK

	#if !defined _MSC_VER
		#error Wrong Compiler. This library does only run with Visual C++ 7.1, 8.0 and 9.0.
	#else
		#if _MSC_VER <= 1300
			// VC7.0, 6.0 not supported
			#error Wrong Compiler. This library does not run with Visual C++ prior to version 7.1
		#elif _MSC_VER == 1310
			// VC71
		#elif _MSC_VER == 1400
			// VC80
		#elif _MSC_VER == 1500
			// VC90
		#elif _MSC_VER == 1600
			// VC100
		#else
			#error Wrong Compiler. This library does only run with Visual C++ 7.1, 8.0, 9.0 and 10.0.
			// other maybe newer compiler ...
		#endif
	#endif

	#if !defined _MT
	#	error "Wrong C Runtime specified. This library requires you to link to the Multithreaded Runtime"
	#endif

	#if !defined _DLL
	#	error "Wrong C Runtime specified. This library requires you to link to the Multithreaded DLL Runtime"
	#endif

	// depend on vc10 to define
	#if _MSC_VER >= 1600
	#	if defined _DEBUG && !(_SECURE_SCL == 1)
	#		error "When compiling a debug build, this library requires your project to build with _SECURE_SCL=1"
	#	elif !(defined _DEBUG) && !(_SECURE_SCL == 0)
	#		error "When compiling a release build, this library requires your project to build with _SECURE_SCL=0"
	#	endif
	#elif _MSC_VER >= 1400
	#	if !(_SECURE_SCL == 1)
	#		error "_SECURE_SCL != 1. This library requires you to build your project with _SECURE_SCL=1."
	#	endif
	#endif
#endif

// #define UDSHL_BASE_NAME is in libbasedefs.h
#define __UDSHL_LPREFIX(txt)	L##txt
#define _UDSHL_LPREFIX(txt)		__UDSHL_LPREFIX(txt)

// link
#if (!defined _MSC_VER || _MSC_VER >= 1600)
	#define UDSHL_SUFFIX_COMPILER	"_vc10"
#elif (!defined _MSC_VER || _MSC_VER >= 1500)
	#define UDSHL_SUFFIX_COMPILER	"_vc9"
#elif (!defined _MSC_VER || _MSC_VER >= 1400)	// vc80 compiler, and other here
	#define UDSHL_SUFFIX_COMPILER	"_vc8"
#elif (!defined _MSC_VER || _MSC_VER >= 1300)	// vc71 compiler, and other here
	#define UDSHL_SUFFIX_COMPILER	"_vc71"
#endif

#if defined _DEBUG
#	define UDSHL_SUFFIX_CONFIGURATION "d"
#else 
#	define UDSHL_SUFFIX_CONFIGURATION ""
#endif
#if defined _M_AMD64
#	define UDSHL_SUFFIX_PLATFORM "_x64"
#else 
#	define UDSHL_SUFFIX_PLATFORM ""
#endif

#define UDSHL_NAME		UDSHL_NAME_BASE UDSHL_SUFFIX_COMPILER UDSHL_SUFFIX_CONFIGURATION UDSHL_SUFFIX_PLATFORM
#define UDSHL_NAME_W	_UDSHL_LPREFIX(UDSHL_NAME_BASE) _UDSHL_LPREFIX(UDSHL_SUFFIX_COMPILER) _UDSHL_LPREFIX(UDSHL_SUFFIX_CONFIGURATION) _UDSHL_LPREFIX(UDSHL_SUFFIX_PLATFORM)

#define UDSHL_DLL_NAME		UDSHL_NAME ".dll"
#define UDSHL_LIB_NAME		UDSHL_NAME ".lib"
#define UDSHL_DLL_NAME_W	UDSHL_NAME_W L".dll"
#define UDSHL_LIB_NAME_W	UDSHL_NAME_W L".lib"

#if !defined UDSHL_LIB_NO_LINK
	// other libraries sometimes needed by applications using ImagingControl
	#include <comdef.h>		// commsupp.lib
	
	#pragma comment ( lib, UDSHL_LIB_DIR UDSHL_LIB_NAME )
#endif

// remove previous defined macro
#undef UDSHL_LIB_DIR

#endif // UDSHL_LNK_H_INC_
