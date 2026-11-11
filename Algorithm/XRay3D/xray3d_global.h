#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(XRAY3D_LIB)
#  define XRAY3D_EXPORT Q_DECL_EXPORT
# else
#  define XRAY3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define XRAY3D_EXPORT
#endif
