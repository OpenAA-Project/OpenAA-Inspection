#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONRESETCAMERA_LIB)
#  define BUTTONRESETCAMERA_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONRESETCAMERA_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONRESETCAMERA_EXPORT
#endif
