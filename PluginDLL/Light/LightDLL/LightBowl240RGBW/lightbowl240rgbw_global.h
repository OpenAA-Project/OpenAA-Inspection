#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LIGHTBOWL240RGBW_LIB)
#  define LIGHTBOWL240RGBW_EXPORT Q_DECL_EXPORT
# else
#  define LIGHTBOWL240RGBW_EXPORT Q_DECL_IMPORT
# endif
#else
# define LIGHTBOWL240RGBW_EXPORT
#endif
