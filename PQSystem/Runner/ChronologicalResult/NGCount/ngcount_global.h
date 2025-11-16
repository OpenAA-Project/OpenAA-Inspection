#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NGCOUNT_LIB)
#  define NGCOUNT_EXPORT Q_DECL_EXPORT
# else
#  define NGCOUNT_EXPORT Q_DECL_IMPORT
# endif
#else
# define NGCOUNT_EXPORT
#endif
