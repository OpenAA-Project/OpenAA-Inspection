#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PQSYSTEMLIB_LIB)
#  define PQSYSTEMLIB_EXPORT Q_DECL_EXPORT
# else
#  define PQSYSTEMLIB_EXPORT Q_DECL_IMPORT
# endif
#else
# define PQSYSTEMLIB_EXPORT
#endif
