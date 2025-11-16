#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAXTIUMCISVIENEX_LIB)
#  define CAMERAXTIUMCISVIENEX_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAXTIUMCISVIENEX_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAXTIUMCISVIENEX_EXPORT
#endif
