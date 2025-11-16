#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTWRITECSV_LIB)
#  define RESULTWRITECSV_EXPORT Q_DECL_EXPORT
# else
#  define RESULTWRITECSV_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTWRITECSV_EXPORT
#endif
