#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTVALUE_LIB)
#  define RESULTVALUE_EXPORT Q_DECL_EXPORT
# else
#  define RESULTVALUE_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTVALUE_EXPORT
#endif
