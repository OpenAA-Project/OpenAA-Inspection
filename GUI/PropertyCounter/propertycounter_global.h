#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYCOUNTER_LIB)
#  define PROPERTYCOUNTER_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYCOUNTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYCOUNTER_EXPORT
#endif
