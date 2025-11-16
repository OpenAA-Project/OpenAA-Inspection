#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(WORLD3D_LIB)
#  define WORLD3D_EXPORT Q_DECL_EXPORT
# else
#  define WORLD3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define WORLD3D_EXPORT
#endif
