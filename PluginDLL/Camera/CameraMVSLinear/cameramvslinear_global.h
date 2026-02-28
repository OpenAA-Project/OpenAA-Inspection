#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAMVSLINEAR_LIB)
#  define CAMERAMVSLINEAR_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAMVSLINEAR_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAMVSLINEAR_EXPORT
#endif
