#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GIOHIKROBOTCAMERA_LIB)
#  define GIOHIKROBOTCAMERA_EXPORT Q_DECL_EXPORT
# else
#  define GIOHIKROBOTCAMERA_EXPORT Q_DECL_IMPORT
# endif
#else
# define GIOHIKROBOTCAMERA_EXPORT
#endif
