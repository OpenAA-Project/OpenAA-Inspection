#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(AREACOLORCONVERTER_LIB)
#  define AREACOLORCONVERTER_EXPORT Q_DECL_EXPORT
# else
#  define AREACOLORCONVERTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define AREACOLORCONVERTER_EXPORT
#endif
