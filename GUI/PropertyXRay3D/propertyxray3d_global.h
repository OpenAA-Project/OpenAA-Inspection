#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYXRAY3D_LIB)
#  define PROPERTYXRAY3D_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYXRAY3D_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYXRAY3D_EXPORT
#endif
