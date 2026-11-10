#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SELECTLIBRARYINMASK_LIB)
#  define SELECTLIBRARYINMASK_EXPORT Q_DECL_EXPORT
# else
#  define SELECTLIBRARYINMASK_EXPORT Q_DECL_IMPORT
# endif
#else
# define SELECTLIBRARYINMASK_EXPORT
#endif
