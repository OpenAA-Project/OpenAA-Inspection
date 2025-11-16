#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RASTER_LIB)
#  define RASTER_EXPORT Q_DECL_EXPORT
# else
#  define RASTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define RASTER_EXPORT
#endif
