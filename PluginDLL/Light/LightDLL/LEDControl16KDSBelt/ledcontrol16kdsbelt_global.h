#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LEDCONTROL16KDSBELT_LIB)
#  define LEDCONTROL16KDSBELT_EXPORT Q_DECL_EXPORT
# else
#  define LEDCONTROL16KDSBELT_EXPORT Q_DECL_IMPORT
# endif
#else
# define LEDCONTROL16KDSBELT_EXPORT
#endif
