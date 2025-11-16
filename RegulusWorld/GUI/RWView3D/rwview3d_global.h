#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWVIEW3D_LIB)
#  define RWVIEW3D_EXPORT Q_DECL_EXPORT
# else
#  define RWVIEW3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWVIEW3D_EXPORT
#endif
