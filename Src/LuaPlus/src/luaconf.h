/*
** $Id: luaconf.h,v 1.82.1.7 2008/02/11 16:25:08 roberto Exp $
** Configuration file for Lua
** See Copyright Notice in lua.h
*/


#ifndef lconfig_h
#define lconfig_h

#include <limits.h>
#include <stddef.h>

#ifndef LUA_TILDE_DEBUGGER
#define LUA_TILDE_DEBUGGER 1
#endif /* LUA_TILDE_DEBUGGER */

#ifndef LUA_FASTREF_SUPPORT
#define LUA_FASTREF_SUPPORT 1
#endif /* LUA_FASTREF_SUPPORT */

#ifndef LUA_WIDESTRING
#define LUA_WIDESTRING 1
#endif /* LUA_WIDESTRING */

#ifndef LUA_WIDESTRING_FILE
#define LUA_WIDESTRING_FILE 1
#endif /* LUA_WIDESTRING_FILE */

#ifndef LUA_BITFIELD_OPS
#define LUA_BITFIELD_OPS 1
#endif /* LUA_BITFIELD_OPS */

#ifndef LUA_EXT_HEXADECIMAL
#define LUA_EXT_HEXADECIMAL 1
#endif /* LUA_EXT_HEXADECIMAL */

#ifndef LUA_ENDIAN_SUPPORT
#define LUA_ENDIAN_SUPPORT 1
#endif /* LUA_ENDIAN_SUPPORT */

#ifndef LUA_MEMORY_STATS
#define LUA_MEMORY_STATS 1
#endif /* LUA_MEMORY_STATS */

#ifndef LUA_AUTO_INCLUDE_STRING_PACK_LIBRARY
#define LUA_AUTO_INCLUDE_STRING_PACK_LIBRARY 1
#endif /* LUA_AUTO_INCLUDE_STRING_PACK_LIBRARY */

#ifndef LUA_STRING_FORMAT_EXTENSIONS
#define	LUA_STRING_FORMAT_EXTENSIONS 1
#endif /* LUA_STRING_FORMAT_EXTENSIONS */

#ifndef LUA_PT_POPEN
#define LUA_PT_POPEN 1
#endif /* LUA_PT_POPEN */

#ifndef LUAPLUS_EXTENSIONS
#define LUAPLUS_EXTENSIONS 1
#endif /* LUAPLUS_EXTENSIONS */

#ifndef LUAPLUS_DUMPOBJECT
#define LUAPLUS_DUMPOBJECT 1
#endif /* LUAPLUS_DUMPOBJECT */

#ifndef LUA_EXT_CONTINUE
#define LUA_EXT_CONTINUE 1
#endif /* LUA_EXT_CONTINUE */

#ifndef LUA_EXT_RESUMABLEVM
#define LUA_EXT_RESUMABLEVM 0
#endif /* LUA_EXT_RESUMABLEVM */

/* Still has bugs... */
#ifndef LUA_REFCOUNT
#define LUA_REFCOUNT 0
#endif /* LUA_REFCOUNT */

#ifndef LUAPLUS_EXCEPTIONS
#define LUAPLUS_EXCEPTIONS 0
#endif // LUAPLUS_EXCEPTIONS

#if LUA_WIDESTRING
#define lua_wstr2number(s,p)    triow_to_double((s), (p))
#endif /* LUA_WIDESTRING */

#ifndef LUA_PACK_VALUE
#define LUA_PACK_VALUE 0
#endif /* LUA_PACK_VALUE */

#ifndef LNUM_PATCH
#define LNUM_PATCH 0
#define LNUM_INT32
#define LNUM_FLOAT
#endif /* LNUM_PATCH */

#if !defined(LUA_PACK_VALUE)
/* on platform with lua number double we could use nan packing for value */
#if (defined(__i386) || defined (_M_IX86) || defined(__i386__)) && defined(LUA_NUMBER_DOUBLE)
/* currently try it on known little endian platform :) */
#define LUA_PACK_VALUE 1
#else
#define LUA_PACK_VALUE 0
#endif
#endif

/*
** ==================================================================
** Search for "@@" to find all configurable definitions.
** ===================================================================
*/


/*
@@ LUA_ANSI controls the use of non-ansi features.
** CHANGE it (define it) if you want Lua to avoid the use of any
** non-ansi feature or library.
*/
#if defined(__STRICT_ANSI__)
#define LUA_ANSI
#endif


#if !defined(LUA_ANSI) && defined(_WIN32) && !defined(_XBOX) && !defined(_XBOX_VER)  
#define LUA_WIN
#endif

#if defined(LUA_USE_LINUX)
#define LUA_USE_POSIX
#define LUA_USE_DLOPEN		/* needs an extra library: -ldl */
#define LUA_USE_READLINE	/* needs some extra libraries */
#endif

#if defined(LUA_USE_MACOSX)
#define LUA_USE_POSIX
#define LUA_DL_DYLD		/* does not need extra library */
#endif



/*
@@ LUA_USE_POSIX includes all functionallity listed as X/Open System
@* Interfaces Extension (XSI).
** CHANGE it (define it) if your system is XSI compatible.
*/
#if defined(LUA_USE_POSIX)
#define LUA_USE_MKSTEMP
#define LUA_USE_ISATTY
#define LUA_USE_POPEN
#define LUA_USE_ULONGJMP
#endif


/*
@@ LUA_PATH and LUA_CPATH are the names of the environment variables that
@* Lua check to set its paths.
@@ LUA_INIT is the name of the environment variable that Lua
@* checks for initialization code.
** CHANGE them if you want different names.
*/
#define LUA_PATH        "LUA_PATH"
#define LUA_CPATH       "LUA_CPATH"
#define LUA_INIT	"LUA_INIT"


/*
@@ LUA_PATH_DEFAULT is the default path that Lua uses to look for
@* Lua libraries.
@@ LUA_CPATH_DEFAULT is the default path that Lua uses to look for
@* C libraries.
** CHANGE them if your machine has a non-conventional directory
** hierarchy or if you want to install your libraries in
** non-conventional directories.
*/
#if defined(WIN32)
#define LUA_CSUFFIX_PLATFORM ".dll"
#elif defined(macintosh)  ||  defined(__APPLE__)
#define LUA_CSUFFIX_PLATFORM ".dylib"
#else
#define LUA_CSUFFIX_PLATFORM ".so"
#endif

#ifdef _DEBUG
#define LUA_CSUFFIX ".debug" LUA_CSUFFIX_PLATFORM
#else
#define LUA_CSUFFIX LUA_CSUFFIX_PLATFORM
#endif

#if defined(_WIN32)
/*
** In Windows, any exclamation mark ('!') in the path is replaced by the
** path of the directory of the executable file of the current process.
*/
#if LUAPLUS_EXTENSIONS
#define LUA_LDIR	"!\\lua\\"
#define LUA_CDIR	"!\\modules\\"
#define LUA_PATH_DEFAULT  \
        "./?.lua;"  LUA_LDIR"?.lua;"  LUA_LDIR"?/init.lua;" \
                     LUA_CDIR"?.lua;"  LUA_CDIR"?/init.lua"
#define LUA_CPATH_DEFAULT \
    "./?" LUA_CSUFFIX ";"  LUA_CDIR"?" LUA_CSUFFIX ";" LUA_CDIR"loadall" LUA_CSUFFIX
#else
#define LUA_LDIR	"!\\lua\\"
#define LUA_CDIR	"!\\"
#define LUA_PATH_DEFAULT  \
        ".\\?.lua;"  LUA_LDIR"?.lua;"  LUA_LDIR"?\\init.lua;" \
                     LUA_CDIR"?.lua;"  LUA_CDIR"?\\init.lua"
#define LUA_CPATH_DEFAULT \
    ".\\?.dll;"  LUA_CDIR"?.dll;" LUA_CDIR"loadall.dll"
#endif

#else
#if LUAPLUS_EXTENSIONS
#define LUA_ROOT	"/usr/local/"
#define LUA_LDIR	"!/share/lua/5.1/"
#define LUA_CDIR	"!/lib/lua/5.1/"
#define LUA_PATH_DEFAULT  \
        "./?.lua;"  LUA_LDIR"?.lua;"  LUA_LDIR"?/init.lua;" \
                    LUA_CDIR"?.lua;"  LUA_CDIR"?/init.lua"
#define LUA_PATH_DEFAULT  \
        "./?.lua;"  LUA_LDIR"?.lua;"  LUA_LDIR"?/init.lua;" \
                     LUA_CDIR"?.lua;"  LUA_CDIR"?/init.lua"
#define LUA_CPATH_DEFAULT \
    "./?" LUA_CSUFFIX ";"  LUA_CDIR"?" LUA_CSUFFIX ";" LUA_CDIR"loadall" LUA_CSUFFIX
#else
#define LUA_ROOT	"/usr/local/"
#define LUA_LDIR	LUA_ROOT "share/lua/5.1/"
#define LUA_CDIR	LUA_ROOT "lib/lua/5.1/"
#define LUA_PATH_DEFAULT  \
        "./?.lua;"  LUA_LDIR"?.lua;"  LUA_LDIR"?/init.lua;" \
                    LUA_CDIR"?.lua;"  LUA_CDIR"?/init.lua"
#define LUA_CPATH_DEFAULT \
    "./?.so;"  LUA_CDIR"?.so;" LUA_CDIR"loadall.so"
#endif
#endif


/*
@@ LUA_DIRSEP is the directory separator (for submodules).
** CHANGE it if your machine does not use "/" as the directory separator
** and is not Windows. (On Windows Lua automatically uses "\".)
*/
#if defined(_WIN32)
#define LUA_DIRSEP	"\\"
#else
#define LUA_DIRSEP	"/"
#endif


/*
@@ LUA_PATHSEP is the character that separates templates in a path.
@@ LUA_PATH_MARK is the string that marks the substitution points in a
@* template.
@@ LUA_EXECDIR in a Windows path is replaced by the executable's
@* directory.
@@ LUA_IGMARK is a mark to ignore all before it when bulding the
@* luaopen_ function name.
** CHANGE them if for some reason your system cannot use those
** characters. (E.g., if one of those characters is a common character
** in file/directory names.) Probably you do not need to change them.
*/
#define LUA_PATHSEP	";"
#define LUA_PATH_MARK	"?"
#define LUA_EXECDIR	"!"
#define LUA_IGMARK	"-"


#if !LNUM_PATCH
/*
@@ LUA_INTEGER is the integral type used by lua_pushinteger/lua_tointeger.
** CHANGE that if ptrdiff_t is not adequate on your machine. (On most
** machines, ptrdiff_t gives a good choice between int or long.)
*/
#define LUA_INTEGER	ptrdiff_t
#endif /* !LNUM_PATCH */


/*
@@ LUA_API is a mark for all core API functions.
@@ LUALIB_API is a mark for all standard library functions.
** CHANGE them if you need to define those functions in some special way.
** For instance, if you want to create one Windows DLL with the core and
** the libraries, you may want to use the following definition (define
** LUA_BUILD_AS_DLL to get it).
*/
#ifndef LUA_API
#if defined(LUA_BUILD_AS_DLL)

#if defined(LUA_CORE) || defined(LUA_LIB)
#define LUA_API __declspec(dllexport)
#else
#define LUA_API __declspec(dllimport)
#endif

#else

#ifndef LUA_API
#define LUA_API		extern
#endif

#endif
#endif

/* more often than not the libs go together with the core */
#define LUALIB_API	LUA_API


/*
@@ LUAI_FUNC is a mark for all extern functions that are not to be
@* exported to outside modules.
@@ LUAI_DATA is a mark for all extern (const) variables that are not to
@* be exported to outside modules.
** CHANGE them if you need to mark them in some special way. Elf/gcc
** (versions 3.2 and later) mark them as "hidden" to optimize access
** when Lua is compiled as a shared library.
*/
#if defined(luaall_c)
#define LUAI_FUNC	static
#define LUAI_DATA	/* empty */

#elif defined(__GNUC__) && ((__GNUC__*100 + __GNUC_MINOR__) >= 302) && \
      defined(__ELF__)
#define LUAI_FUNC	__attribute__((visibility("hidden"))) extern
#define LUAI_DATA	LUAI_FUNC

#else
#define LUAI_FUNC	extern
#define LUAI_DATA	extern
#endif



/*
@@ LUA_QL describes how error messages quote program elements.
** CHANGE it if you want a different appearance.
*/
#define LUA_QL(x)	"'" x "'"
#define LUA_QS		LUA_QL("%s")


/*
@@ LUA_IDSIZE gives the maximum size for the description of the source
@* of a function in debug information.
** CHANGE it if you want a different size.
*/
#define LUA_IDSIZE	60


/*
** {==================================================================
** Stand-alone configuration
** ===================================================================
*/

#if defined(lua_c) || defined(luaall_c)

/*
@@ lua_stdin_is_tty detects whether the standard input is a 'tty' (that
@* is, whether we're running lua interactively).
** CHANGE it if you have a better definition for non-POSIX/non-Windows
** systems.
*/
#if defined(LUA_USE_ISATTY)
#include <unistd.h>
#define lua_stdin_is_tty()	isatty(0)
#elif defined(LUA_WIN)
#include <io.h>
#include <stdio.h>
#define lua_stdin_is_tty()	_isatty(_fileno(stdin))
#else
#define lua_stdin_is_tty()	1  /* assume stdin is a tty */
#endif


/*
@@ LUA_PROMPT is the default prompt used by stand-alone Lua.
@@ LUA_PROMPT2 is the default continuation prompt used by stand-alone Lua.
** CHANGE them if you want different prompts. (You can also change the
** prompts dynamically, assigning to globals _PROMPT/_PROMPT2.)
*/
#define LUA_PROMPT		"> "
#define LUA_PROMPT2		">> "


/*
@@ LUA_PROGNAME is the default name for the stand-alone Lua program.
** CHANGE it if your stand-alone interpreter has a different name and
** your system is not able to detect that name automatically.
*/
#define LUA_PROGNAME		"lua"


/*
@@ LUA_MAXINPUT is the maximum length for an input line in the
@* stand-alone interpreter.
** CHANGE it if you need longer lines.
*/
#define LUA_MAXINPUT	512


/*
@@ lua_readline defines how to show a prompt and then read a line from
@* the standard input.
@@ lua_saveline defines how to "save" a read line in a "history".
@@ lua_freeline defines how to free a line read by lua_readline.
** CHANGE them if you want to improve this functionality (e.g., by using
** GNU readline and history facilities).
*/
#if defined(LUA_USE_READLINE)
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#define lua_readline(L,b,p)	((void)L, ((b)=readline(p)) != NULL)
#define lua_saveline(L,idx) \
    if (lua_strlen(L,idx) > 0)  /* non-empty line? */ \
      add_history(lua_tostring(L, idx));  /* add it to history */
#define lua_freeline(L,b)	((void)L, free(b))
#else
#define lua_readline(L,b,p)	\
    ((void)L, fputs(p, stdout), fflush(stdout),  /* show prompt */ \
    fgets(b, LUA_MAXINPUT, stdin) != NULL)  /* get line */
#define lua_saveline(L,idx)	{ (void)L; (void)idx; }
#define lua_freeline(L,b)	{ (void)L; (void)b; }
#endif

#endif

/* }================================================================== */


/*
@@ LUAI_GCPAUSE defines the default pause between garbage-collector cycles
@* as a percentage.
** CHANGE it if you want the GC to run faster or slower (higher values
** mean larger pauses which mean slower collection.) You can also change
** this value dynamically.
*/
#define LUAI_GCPAUSE	200  /* 200% (wait memory to double before next GC) */


/*
@@ LUAI_GCMUL defines the default speed of garbage collection relative to
@* memory allocation as a percentage.
** CHANGE it if you want to change the granularity of the garbage
** collection. (Higher values mean coarser collections. 0 represents
** infinity, where each step performs a full collection.) You can also
** change this value dynamically.
*/
#define LUAI_GCMUL	200 /* GC runs 'twice the speed' of memory allocation */



/*
@@ LUA_COMPAT_GETN controls compatibility with old getn behavior.
** CHANGE it (define it) if you want exact compatibility with the
** behavior of setn/getn in Lua 5.0.
*/
#undef LUA_COMPAT_GETN

/*
@@ LUA_COMPAT_LOADLIB controls compatibility about global loadlib.
** CHANGE it to undefined as soon as you do not need a global 'loadlib'
** function (the function is still available as 'package.loadlib').
*/
#undef LUA_COMPAT_LOADLIB

/*
@@ LUA_COMPAT_VARARG controls compatibility with old vararg feature.
** CHANGE it to undefined as soon as your programs use only '...' to
** access vararg parameters (instead of the old 'arg' table).
*/
#define LUA_COMPAT_VARARG

/*
@@ LUA_COMPAT_MOD controls compatibility with old math.mod function.
** CHANGE it to undefined as soon as your programs use 'math.fmod' or
** the new '%' operator instead of 'math.mod'.
*/
#define LUA_COMPAT_MOD

/*
@@ LUA_COMPAT_LSTR controls compatibility with old long string nesting
@* facility.
** CHANGE it to 2 if you want the old behaviour, or undefine it to turn
** off the advisory error when nesting [[...]].
*/
#define LUA_COMPAT_LSTR		1

/*
@@ LUA_COMPAT_GFIND controls compatibility with old 'string.gfind' name.
** CHANGE it to undefined as soon as you rename 'string.gfind' to
** 'string.gmatch'.
*/
#define LUA_COMPAT_GFIND

/*
@@ LUA_COMPAT_OPENLIB controls compatibility with old 'luaL_openlib'
@* behavior.
** CHANGE it to undefined as soon as you replace to 'luaL_register'
** your uses of 'luaL_openlib'
*/
#define LUA_COMPAT_OPENLIB



/*
@@ luai_apicheck is the assert macro used by the Lua-C API.
** CHANGE luai_apicheck if you want Lua to perform some checks in the
** parameters it gets from API calls. This may slow down the interpreter
** a bit, but may be quite useful when debugging C code that interfaces
** with Lua. A useful redefinition is to use assert.h.
*/
#define LUA_USE_APICHECK
#if defined(LUA_USE_APICHECK)
#include <assert.h>
#define luai_apicheck(L,o)	{ (void)L; assert(o); }
#define lua_assert(o)	assert(o)
#else
#define luai_apicheck(L,o)	{ (void)L; }
#endif


/*
@@ LUAI_BITSINT defines the number of bits in an int.
** CHANGE here if Lua cannot automatically detect the number of bits of
** your machine. Probably you do not need to change this.
*/
/* avoid overflows in comparison */
#if INT_MAX-20 < 32760
#define LUAI_BITSINT	16
#elif INT_MAX > 2147483640L
/* int has at least 32 bits */
#define LUAI_BITSINT	32
#else
#error "you must define LUA_BITSINT with number of bits in an integer"
#endif


/*
@@ LUAI_UINT32 is an unsigned integer with at least 32 bits.
@@ LUAI_INT32 is an signed integer with at least 32 bits.
@@ LUAI_UMEM is an unsigned integer big enough to count the total
@* memory used by Lua.
@@ LUAI_MEM is a signed integer big enough to count the total memory
@* used by Lua.
** CHANGE here if for some weird reason the default definitions are not
** good enough for your machine. (The definitions in the 'else'
** part always works, but may waste space on machines with 64-bit
** longs.) Probably you do not need to change this.
*/
#if LUAI_BITSINT >= 32
#define LUAI_UINT32	unsigned int
#define LUAI_INT32	int
#define LUAI_MAXINT32	INT_MAX
#define LUAI_UMEM	size_t
#define LUAI_MEM	ptrdiff_t
#else
/* 16-bit ints */
#define LUAI_UINT32	unsigned long
#define LUAI_INT32	long
#define LUAI_MAXINT32	LONG_MAX
#define LUAI_UMEM	unsigned long
#define LUAI_MEM	long
#endif


/*
@@ LUAI_MAXCALLS limits the number of nested calls.
** CHANGE it if you need really deep recursive calls. This limit is
** arbitrary; its only purpose is to stop infinite recursion before
** exhausting memory.
*/
#define LUAI_MAXCALLS	20000


/*
@@ LUAI_MAXCSTACK limits the number of Lua stack slots that a C function
@* can use.
** CHANGE it if you need lots of (Lua) stack space for your C
** functions. This limit is arbitrary; its only purpose is to stop C
** functions to consume unlimited stack space. (must be smaller than
** -LUA_REGISTRYINDEX)
*/
#define LUAI_MAXCSTACK	8000



/*
** {==================================================================
** CHANGE (to smaller values) the following definitions if your system
** has a small C stack. (Or you may want to change them to larger
** values if your system has a large C stack and these limits are
** too rigid for you.) Some of these constants control the size of
** stack-allocated arrays used by the compiler or the interpreter, while
** others limit the maximum number of recursive calls that the compiler
** or the interpreter can perform. Values too large may cause a C stack
** overflow for some forms of deep constructs.
** ===================================================================
*/


/*
@@ LUAI_MAXCCALLS is the maximum depth for nested C calls (short) and
@* syntactical nested non-terminals in a program.
*/
#define LUAI_MAXCCALLS		200


/*
@@ LUAI_MAXVARS is the maximum number of local variables per function
@* (must be smaller than 250).
*/
#define LUAI_MAXVARS		200


/*
@@ LUAI_MAXUPVALUES is the maximum number of upvalues per function
@* (must be smaller than 250).
*/
#define LUAI_MAXUPVALUES	60


/*
@@ LUAL_BUFFERSIZE is the buffer size used by the lauxlib buffer system.
*/
#define LUAL_BUFFERSIZE		BUFSIZ

/* }================================================================== */




#if !LNUM_PATCH

/*
** {==================================================================
@@ LUA_NUMBER is the type of numbers in Lua.
** CHANGE the following definitions only if you want to build Lua
** with a number type different from double. You may also need to
** change lua_number2int & lua_number2integer.
** ===================================================================
*/

#define LUA_NUMBER_DOUBLE
#define LUA_NUMBER	double

/*
@@ LUAI_UACNUMBER is the result of an 'usual argument conversion'
@* over a number.
*/
#define LUAI_UACNUMBER	double


/*
@@ LUA_NUMBER_SCAN is the format for reading numbers.
@@ LUA_NUMBER_FMT is the format for writing numbers.
@@ lua_number2str converts a number to a string.
@@ LUAI_MAXNUMBER2STR is maximum size of previous conversion.
@@ lua_str2number converts a string to a number.
*/
#define LUA_NUMBER_SCAN		"%lf"
#define LUA_NUMBER_FMT		"%.14g"
#define lua_number2str(s,n)	sprintf((s), LUA_NUMBER_FMT, (n))
#define LUAI_MAXNUMBER2STR	32 /* 16 digits, sign, point, and \0 */
#define lua_str2number(s,p)	strtod((s), (p))

/*
@@ The luai_num* macros define the primitive operations over numbers.
*/
#if defined(LUA_CORE)
#include <math.h>
#define luai_numadd(a,b)	((a)+(b))
#define luai_numsub(a,b)	((a)-(b))
#define luai_nummul(a,b)	((a)*(b))
#define luai_numdiv(a,b)	((a)/(b))
#define luai_nummod(a,b)	((a) - floor((a)/(b))*(b))
#define luai_numpow(a,b)	(pow(a,b))
#define luai_numunm(a)		(-(a))
#define luai_numeq(a,b)		((a)==(b))
#define luai_numlt(a,b)		((a)<(b))
#define luai_numle(a,b)		((a)<=(b))
#define luai_numisnan(a)	(!luai_numeq((a), (a)))
#endif


/*
@@ lua_number2int is a macro to convert lua_Number to int.
@@ lua_number2integer is a macro to convert lua_Number to lua_Integer.
** CHANGE them if you know a faster way to convert a lua_Number to
** int (with any rounding method and without throwing errors) in your
** system. In Pentium machines, a naive typecast from double to int
** in C is extremely slow, so any alternative is worth trying.
*/

/* On a Pentium, resort to a trick */
#if defined(LUA_NUMBER_DOUBLE) && !defined(LUA_ANSI) && !defined(__SSE2__) && \
    (defined(__i386) || defined (_M_IX86) || defined(__i386__))

/* On a Microsoft compiler, use assembler */
#if defined(_MSC_VER)

#if LUAPLUS_EXTENSIONS
#define lua_number2int(i,d)   i = (int)d;
#else
#define lua_number2int(i,d)   __asm fld d;   __asm fistp i;
#endif /* LUAPLUS_EXTENSIONS */
#define lua_number2integer(i,n)		lua_number2int(i, n)

/* the next trick should work on any Pentium, but sometimes clashes
   with a DirectX idiosyncrasy */
#else

union luai_Cast { double l_d; long l_l; };
#define lua_number2int(i,d) \
  { volatile union luai_Cast u; u.l_d = (d) + 6755399441055744.0; (i) = u.l_l; }
#define lua_number2integer(i,n)		lua_number2int(i, n)

#endif


/* this option always works, but may be slow */
#else
#define lua_number2int(i,d)	((i)=(int)(d))
#define lua_number2integer(i,d)	((i)=(lua_Integer)(d))

#endif

#else /* LNUM_PATCH */

/*
@@ LUA_COMPAT_TOINTEGER controls compatibility with 5.1 'lua_tointeger()';
@* allows values not fitting in 'lua_Integer' to be rounded.
*/
#define LUA_COMPAT_TOINTEGER

/*
** Default number mode
*/
#if (!defined LNUM_DOUBLE) && (!defined LNUM_FLOAT) && (!defined LNUM_LDOUBLE)
# define LNUM_DOUBLE
#endif

/*
** Require C99 mode for COMPLEX, FLOAT and LDOUBLE (only DOUBLE is ANSI C).
*/
#if defined(LNUM_COMPLEX) && (__STDC_VERSION__ < 199901L)
# error "Need C99 for complex (use '--std=c99' or similar)"
#elif defined(LNUM_LDOUBLE) && (__STDC_VERSION__ < 199901L) && !defined(_MSC_VER)
# error "Need C99 for 'long double' (use '--std=c99' or similar)"
#elif defined(LNUM_FLOAT) && (__STDC_VERSION__ < 199901L)
/* LNUM_FLOAT not supported on Windows */
//# error "Need C99 for 'float' (use '--std=c99' or similar)"
#endif

/*
** COMPLEX mode currently only with integer optimization
*/
#if defined(LNUM_COMPLEX) && !(defined(LNUM_INT32) || defined(LNUM_INT64))
# error "LNUM_COMPLEX needs to be used together with LNUM_INTxx"
#endif
 
/*
** Number mode identifier to accompany the version string.
*/
#ifdef LNUM_COMPLEX
# define _LNUM1 "complex "
#else
# define _LNUM1 ""
#endif
#ifdef LNUM_DOUBLE
# define _LNUM2 "double"
#elif defined(LNUM_FLOAT)
# define _LNUM2 "float"
#elif defined(LNUM_LDOUBLE)
# define _LNUM2 "ldouble"
#endif
#ifdef LNUM_INT32
# define _LNUM3 " int32"
#elif defined(LNUM_INT64)
# define _LNUM3 " int64"
#else
# define _LNUM3 ""
#endif
#ifdef __FAST_MATH__
# define _LNUM4 "fastmath"
#else
# define _LNUM4 ""
#endif
#define LUA_LNUM _LNUM1 _LNUM2 _LNUM3 _LNUM4


/* 
** LUAI_MAXNUMBER2STR: size of a buffer fitting any number->string result.
**
**  double:  24 (sign, x.xxxxxxxxxxxxxxe+nnnn, and \0)
**  int64:   21 (19 digits, sign, and \0)
**  long double: 43 for 128-bit (sign, x.xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxe+nnnn, and \0)
**           30 for 80-bit (sign, x.xxxxxxxxxxxxxxxxxxxxe+nnnn, and \0)
*/
#ifdef LNUM_LDOUBLE
# define _LUAI_MN2S 44
#else
# define _LUAI_MN2S 24
#endif

#ifdef LNUM_COMPLEX
# define LUAI_MAXNUMBER2STR (2*_LUAI_MN2S)
#else
# define LUAI_MAXNUMBER2STR _LUAI_MN2S
#endif

/*
@@ LNUM_DOUBLE | LNUM_FLOAT | LNUM_LDOUBLE: Generic Lua number mode
@@ LNUM_INT32 | LNUM_INT64: Integer type (optional)
@@ LNUM_COMPLEX: Define for using 'a+bi' numbers
@*
@* You can combine LNUM_xxx but only one of each group. I.e. 'LNUM_FLOAT
@* LNUM_INT32 LNUM_COMPLEX' gives float range complex numbers, with 
@* 32-bit scalar integer range optimized.
*/
/*#define LNUM_DOUBLE*/


/*
** LUA_NUMBER is the type of floating point number in Lua
** LUA_NUMBER_SCAN is the format for reading numbers.
** LUA_NUMBER_FMT is the format for writing numbers.
*/
#ifdef LNUM_FLOAT
# define LUA_NUMBER         float
# define LUA_NUMBER_SCAN    "%f"
# define LUA_NUMBER_FMT     "%g"  
#elif defined(LNUM_LDOUBLE)
# define LUA_NUMBER         long double
# define LUA_NUMBER_SCAN    "%Lg"
# define LUA_NUMBER_FMT     "%.20Lg"
#else
# define LUA_NUMBER	        double
# define LUA_NUMBER_SCAN    "%lf"
# define LUA_NUMBER_FMT     "%.14g"
#endif


/*
@@ LUAI_BITSINT defines the number of bits in an int.
** CHANGE here if Lua cannot automatically detect the number of bits of
** your machine. Probably you do not need to change this.
*/
/* avoid overflows in comparison */
#if INT_MAX-20 < 32760
#define LUAI_BITSINT	16
#elif INT_MAX > 2147483640L
/* int has at least 32 bits */
#define LUAI_BITSINT	32
#else
#error "you must define LUA_BITSINT with number of bits in an integer"
#endif


/*
** LUA_INTEGER is the integer type used by lua_pushinteger/lua_tointeger/lua_isinteger.
** LUA_INTEGER_SCAN is the format for reading integers
** LUA_INTEGER_FMT is the format for writing integers
*/
#ifdef LNUM_INT64
# define LUA_INTEGER	long long
# ifdef _MSC_VER
#  define lua_str2ul    _strtoui64
# else
#  define lua_str2ul    strtoull
# endif
# define LUA_INTEGER_SCAN "%lld"
# define LUA_INTEGER_FMT "%lld"
# define LUA_INTEGER_MAX 0x7fffffffffffffffLL       /* 2^63-1 */ 
# define LUA_INTEGER_MIN (-LUA_INTEGER_MAX - 1LL)   /* -2^63 */
/* */
#else
# if LUAI_BITSINT == 32
#  define LUA_INTEGER   int
#  define LUA_INTEGER_SCAN "%d"
#  define LUA_INTEGER_FMT "%d"
# else
/* Note: 'LUA_INTEGER' being 'ptrdiff_t' (as in Lua 5.1) causes problems with
 *       'printf()' operations. Also 'unsigned ptrdiff_t' is invalid. */
#  define LUA_INTEGER   long
#  define LUA_INTEGER_SCAN "%ld"
#  define LUA_INTEGER_FMT "%ld"
# endif
# define LUA_INTEGER_MAX 0x7FFFFFFF             /* 2^31-1 */
#endif

#ifndef lua_str2ul
# define lua_str2ul (unsigned LUA_INTEGER)strtoul
#endif
#ifndef LUA_INTEGER_MIN
# define LUA_INTEGER_MIN (-LUA_INTEGER_MAX -1)  /* -2^16|32 */
#endif

/*
@@ lua_number2int is a macro to convert lua_Number to int.
@@ lua_number2integer is a macro to convert lua_Number to lua_Integer.
** CHANGE them if you know a faster way to convert a lua_Number to
** int (with any rounding method and without throwing errors) in your
** system. In Pentium machines, a naive typecast from double to int
** in C is extremely slow, so any alternative is worth trying.
**
** Note: Using '-msse' or '-msse3' is highly recommended for newer x86
**      processors. They have fast instructions to bypass the Pentium FP->int
**      efficiency problem altogether.  --AKa 6-Apr-2009
*/

/* On old Pentium (SSE not enabled), resort to a trick */
#if defined(LNUM_DOUBLE) && !defined(LUA_ANSI) && !defined(__SSE2__) && \
    (defined(__i386) || defined (_M_IX86) || defined(__i386__))

#if LUAPLUS_EXTENSIONS
#define lua_number2int(i,d)   i = (int)d;

/* On a Microsoft compiler, use assembler */
# elif defined(_MSC_VER)
#  define lua_number2int(i,d)   __asm fld d   __asm fistp i
# else

/* the next trick should work on any Pentium, but sometimes clashes
   with a DirectX idiosyncrasy */
union luai_Cast { double l_d; long l_l; };
#  define lua_number2int(i,d) \
  { volatile union luai_Cast u; u.l_d = (d) + 6755399441055744.0; (i) = u.l_l; }
# endif

# ifndef LNUM_INT64
#  define lua_number2integer    lua_number2int
# endif

/* this option always works (and is fast on most platforms) */
#else
# define lua_number2int(i,d)        ((i)=(int)(d))
#endif

/* Note: Some compilers (OS X gcc 4.0?) may choke on double->long long conversion 
 *       since it can lose precision. Others do require 'long long' there.  
 */
#ifndef lua_number2integer
# define lua_number2integer(i,d)    ((i)=(lua_Integer)(d))
#endif

/*
** 'luai_abs()' to give absolute value of 'lua_Integer'
*/
#ifdef LNUM_INT64
# if (__STDC_VERSION__ >= 199901L)
#  define luai_abs llabs
# else
#  define luai_abs(v) ((v) >= 0 ? (v) : -(v))
# endif
#else
# define luai_abs abs
#endif

/*
** LUAI_UACNUMBER is the result of an 'usual argument conversion' over a number.
** LUAI_UACINTEGER the same, over an integer.
*/
#define LUAI_UACNUMBER	double
#define LUAI_UACINTEGER long

/* ANSI C only has math funcs for 'double. C99 required for float and long double
 * variants.
 */
#ifdef LNUM_DOUBLE
# define _LF(name) name
#elif defined(LNUM_FLOAT)
# define _LF(name) name ## f
#elif defined(LNUM_LDOUBLE)
# define _LF(name) name ## l
#endif

#endif /* LNUM_PATCH */

/* }================================================================== */



/*
@@ LUAI_USER_ALIGNMENT_T is a type that requires maximum alignment.
** CHANGE it if your system requires alignments larger than double. (For
** instance, if your system supports long doubles and they must be
** aligned in 16-byte boundaries, then you should add long double in the
** union.) Probably you do not need to change this.
*/
#define LUAI_USER_ALIGNMENT_T	union { double u; void *s; long l; }


/*
@@ LUAI_THROW/LUAI_TRY define how Lua does exception handling.
** CHANGE them if you prefer to use longjmp/setjmp even with C++
** or if want/don't to use _longjmp/_setjmp instead of regular
** longjmp/setjmp. By default, Lua handles errors with exceptions when
** compiling as C++ code, with _longjmp/_setjmp when asked to use them,
** and with longjmp/setjmp otherwise.
*/
#if !defined(LUA_FORCE_USE_LONGJMP)  &&  defined(__cplusplus)
/* C++ exceptions */
#define LUAI_THROW(L,c)	throw(c)
#if LUA_EXT_RESUMABLEVM
#define LUAI_TRY(L,c,a)	try { a } catch(...) \
    { if ((c)->status == 0) (c)->status = LUA_ERREXC; }
#else
#define LUAI_TRY(L,c,a)	try { a } catch(...) \
    { if ((c)->status == 0) (c)->status = -1; }
#endif /* LUA_EXT_RESUMABLEVM */
#define luai_jmpbuf	int  /* dummy variable */

#elif defined(LUA_USE_ULONGJMP)
/* in Unix, try _longjmp/_setjmp (more efficient) */
#define LUAI_THROW(L,c)	_longjmp((c)->b, 1)
#define LUAI_TRY(L,c,a)	if (_setjmp((c)->b) == 0) { a }
#define luai_jmpbuf	jmp_buf

#else
/* default handling with long jumps */
#define LUAI_THROW(L,c)	longjmp((c)->b, 1)
#define LUAI_TRY(L,c,a)	if (setjmp((c)->b) == 0) { a }
#define luai_jmpbuf	jmp_buf

#endif


/*
@@ LUA_MAXCAPTURES is the maximum number of captures that a pattern
@* can do during pattern-matching.
** CHANGE it if you need more captures. This limit is arbitrary.
*/
#define LUA_MAXCAPTURES		32


/*
@@ lua_tmpnam is the function that the OS library uses to create a
@* temporary name.
@@ LUA_TMPNAMBUFSIZE is the maximum size of a name created by lua_tmpnam.
** CHANGE them if you have an alternative to tmpnam (which is considered
** insecure) or if you want the original tmpnam anyway.  By default, Lua
** uses tmpnam except when POSIX is available, where it uses mkstemp.
*/
#if defined(loslib_c) || defined(luaall_c)

#if defined(LUA_USE_MKSTEMP)
#include <unistd.h>
#define LUA_TMPNAMBUFSIZE	32
#define lua_tmpnam(b,e)	{ \
    strcpy(b, "/tmp/lua_XXXXXX"); \
    e = mkstemp(b); \
    if (e != -1) close(e); \
    e = (e == -1); }

#else
#define LUA_TMPNAMBUFSIZE	L_tmpnam
#define lua_tmpnam(b,e)		{ e = (tmpnam(b) == NULL); }
#endif

#endif


/*
@@ lua_popen spawns a new process connected to the current one through
@* the file streams.
** CHANGE it if you have a way to implement it in your system.
*/
#if defined(LUA_USE_POPEN)

#define lua_popen(L,c,m)	((void)L, fflush(NULL), popen(c,m))
#define lua_pclose(L,file)	((void)L, (pclose(file) != -1))

#elif defined(LUA_WIN) && !defined(_XBOX) && !defined(_XBOX_VER) && !defined(PLATFORM_PS3)

#if LUA_PT_POPEN
#define lua_popen(L,c,m) ((void)L, pt_popen(c,m))
#define lua_pclose(L,file) ((void)L, (pt_pclose(file) != -1))
#else
#define lua_popen(L,c,m)	((void)L, _popen(c,m))
#define lua_pclose(L,file)	((void)L, (_pclose(file) != -1))
#endif /* LUA_PT_POPEN */

#else

#define lua_popen(L,c,m)	((void)((void)c, m),  \
        luaL_error(L, LUA_QL("popen") " not supported"), (FILE*)0)
#define lua_pclose(L,file)		((void)((void)L, file), 0)

#endif

/*
@@ LUA_DL_* define which dynamic-library system Lua should use.
** CHANGE here if Lua has problems choosing the appropriate
** dynamic-library system for your platform (either Windows' DLL, Mac's
** dyld, or Unix's dlopen). If your system is some kind of Unix, there
** is a good chance that it has dlopen, so LUA_DL_DLOPEN will work for
** it.  To use dlopen you also need to adapt the src/Makefile (probably
** adding -ldl to the linker options), so Lua does not select it
** automatically.  (When you change the makefile to add -ldl, you must
** also add -DLUA_USE_DLOPEN.)
** If you do not want any kind of dynamic library, undefine all these
** options.
** By default, _WIN32 gets LUA_DL_DLL and MAC OS X gets LUA_DL_DYLD.
*/
#if defined(LUA_USE_DLOPEN)
#define LUA_DL_DLOPEN
#endif

#if defined(LUA_WIN)
#define LUA_DL_DLL
#endif


/*
@@ LUAI_EXTRASPACE allows you to add user-specific data in a lua_State
@* (the data goes just *before* the lua_State pointer).
** CHANGE (define) this if you really need that. This value must be
** a multiple of the maximum alignment required for your machine.
*/
#define LUAI_EXTRASPACE		0


/*
@@ luai_userstate* allow user-specific actions on threads.
** CHANGE them if you defined LUAI_EXTRASPACE and need to do something
** extra when a thread is created/deleted/resumed/yielded.
*/
#if LUAPLUS_EXTENSIONS
#define luai_userstateopen(L)		LuaState_UserStateOpen(L)
#else
#define luai_userstateopen(L)		((void)L)
#endif /* LUAPLUS_EXTENSIONS */
#define luai_userstateclose(L)		((void)L)
#define luai_userstatethread(L,L1)	((void)L)
#define luai_userstatefree(L)		((void)L)
#define luai_userstateresume(L,n)	((void)L)
#define luai_userstateyield(L,n)	((void)L)


/*
@@ LUA_INTFRMLEN is the length modifier for integer conversions
@* in 'string.format'.
@@ LUA_INTFRM_T is the integer type correspoding to the previous length
@* modifier.
** CHANGE them if your system supports long long or does not support long.
*/

#if defined(LUA_USELONGLONG)

#define LUA_INTFRMLEN		"ll"
#define LUA_INTFRM_T		long long

#else

#define LUA_INTFRMLEN		"l"
#define LUA_INTFRM_T		long

#endif



/* =================================================================== */

/*
** Local configuration. You can use this space to add your redefinitions
** without modifying the main part of the file.
*/

#endif

