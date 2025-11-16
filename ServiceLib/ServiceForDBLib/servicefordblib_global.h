#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SERVICEFORDBLIB_LIB)
#  define SERVICEFORDBLIB_EXPORT Q_DECL_EXPORT
# else
#  define SERVICEFORDBLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define SERVICEFORDBLIB_EXPORT
#endif
