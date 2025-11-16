#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYWORLD3D_LIB)
#  define PROPERTYWORLD3D_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYWORLD3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYWORLD3D_EXPORT
#endif
