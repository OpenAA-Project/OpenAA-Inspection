#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DISPLAYIMAGE3D_LIB)
#  define DISPLAYIMAGE3D_EXPORT Q_DECL_EXPORT
# else
#  define DISPLAYIMAGE3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define DISPLAYIMAGE3D_EXPORT
#endif
