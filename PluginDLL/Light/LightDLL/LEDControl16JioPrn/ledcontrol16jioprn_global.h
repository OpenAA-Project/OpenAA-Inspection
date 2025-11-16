#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LEDCONTROL16JIOPRN_LIB)
#  define LEDCONTROL16JIOPRN_EXPORT Q_DECL_EXPORT
# else
#  define LEDCONTROL16JIOPRN_EXPORT Q_DECL_IMPORT
# endif
#else
# define LEDCONTROL16JIOPRN_EXPORT
#endif
