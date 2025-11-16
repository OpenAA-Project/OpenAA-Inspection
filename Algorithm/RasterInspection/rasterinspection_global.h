#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RASTERINSPECTION_LIB)
#  define RASTERINSPECTION_EXPORT Q_DECL_EXPORT
# else
#  define RASTERINSPECTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define RASTERINSPECTION_EXPORT
#endif
