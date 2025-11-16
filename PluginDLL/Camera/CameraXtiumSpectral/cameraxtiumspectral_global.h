#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAXTIUMSPECTRAL_LIB)
#  define CAMERAXTIUMSPECTRAL_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAXTIUMSPECTRAL_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAXTIUMSPECTRAL_EXPORT
#endif
