#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHIFTMARK_LIB)
#  define SHIFTMARK_EXPORT Q_DECL_EXPORT
# else
#  define SHIFTMARK_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHIFTMARK_EXPORT
#endif
