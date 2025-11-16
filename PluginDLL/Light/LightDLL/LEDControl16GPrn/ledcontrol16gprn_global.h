#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LEDCONTROL16GPRN_LIB)
#  define LEDCONTROL16GPRN_EXPORT Q_DECL_EXPORT
# else
#  define LEDCONTROL16GPRN_EXPORT Q_DECL_IMPORT
# endif
#else
# define LEDCONTROL16GPRN_EXPORT
#endif
