#ifndef I3D_OS_S3E
#   define I3D_OS_S3E 1
#endif
#ifndef I3D_PLATFORM_S3E
#   define I3D_PLATFORM_S3E 1
#endif
#ifndef IW_APP_NAME
#   define IW_APP_NAME "brixpath"
#endif
#ifndef IW_APP_VERSION
#   define IW_APP_VERSION "1.0"
#endif
#ifndef IW_ASSERTION_CHANNEL_2D
#   define IW_ASSERTION_CHANNEL_2D 1
#endif
#ifndef IW_GXFONT_TTF
#   define IW_GXFONT_TTF 1
#endif
#ifndef IW_MKF_IW2D
#   define IW_MKF_IW2D 1
#endif
#ifndef IW_MKF_IWGEOM
#   define IW_MKF_IWGEOM 1
#endif
#ifndef IW_MKF_IWGL
#   define IW_MKF_IWGL 1
#endif
#ifndef IW_MKF_IWGX
#   define IW_MKF_IWGX 1
#endif
#ifndef IW_MKF_IWGXFONT
#   define IW_MKF_IWGXFONT 1
#endif
#ifndef IW_MKF_IWRESMANAGER
#   define IW_MKF_IWRESMANAGER 1
#endif
#ifndef IW_MKF_IWUTIL
#   define IW_MKF_IWUTIL 1
#endif
#ifndef IW_MKF_LIBJPEG
#   define IW_MKF_LIBJPEG 1
#endif
#ifndef IW_MKF_LIBPNG
#   define IW_MKF_LIBPNG 1
#endif
#ifndef IW_MKF_TINICONV
#   define IW_MKF_TINICONV 1
#endif
#ifndef IW_MKF_ZLIB
#   define IW_MKF_ZLIB 1
#endif
#ifndef IW_PLATFORM_S3E
#   define IW_PLATFORM_S3E 1
#endif
#ifndef IW_SDK
#   define IW_SDK 1
#endif
#ifndef __S3E__
#   define __S3E__ 1
#endif

/* including "extra_body" specified by the mkb plugin */

#undef win32

#ifndef unix
    #define unix
#endif

#ifndef __unix
    #define __unix
#endif

/*
#ifndef _REENTRANT
    #define _REENTRANT
#endif
*/

#if !defined I3D_ARCH_ARM && !defined I3D_ARCH_X86 && !defined I3D_ARCH_AMD64 && !defined I3D_ARCH_MIPS && !defined I3D_ARCH_PS3 && !defined I3D_ARCH_X360 && !defined I3D_ARCH_PSP
    #if defined __ARMCC_VERSION || defined __ARMC__ || defined __arm__
        #define I3D_ARCH_ARM
    #elif defined __mipsel || defined __MIPSEL
        #define I3D_ARCH_MIPS
    #elif defined __amd64
        #define I3D_ARCH_AMD64
    #else
        #define I3D_ARCH_X86
    #endif
#endif

#if defined I3D_ARCH_X86 && !defined __i386__
    #define __i386__
#endif

#if defined I3D_ARCH_ARM && !defined __ARM__
    #define __ARM__
#endif

#if defined __cplusplus && defined _MSC_VER && _MSC_VER < 1400 && !defined IW_WCHAR_T_DEFINED
    // wchar_t is a builtin in C++ .. but not for MSVC <= 2003
    typedef unsigned short wchar_t;
    #define IW_WCHAR_T_DEFINED
#endif

#ifdef _MSC_VER
    #pragma warning (disable: 4786)
#endif

#undef _WIN32
#undef WIN32
#undef __linux__
#undef __linux
#undef linux
#if !defined I3D_ARCH_ARM && !defined I3D_ARCH_X86 && !defined I3D_ARCH_PS3 && !defined I3D_ARCH_X360
    #if defined __ARMCC_VERSION || defined __arm__
        #define I3D_ARCH_ARM
    #else
        #define I3D_ARCH_X86
        #define I3D_ARCH_I386
    #endif
#endif

#if defined I3D_ARCH_X86 && !defined __i386__
    #define __i386__
#endif

#if defined I3D_ARCH_ARM && !defined __ARM__
    #define __ARM__
#endif
