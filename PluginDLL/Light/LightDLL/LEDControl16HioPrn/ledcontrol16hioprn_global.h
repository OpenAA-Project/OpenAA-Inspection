#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LEDCONTROL16HIOPRN_LIB)
#  define LEDCONTROL16HIOPRN_EXPORT Q_DECL_EXPORT
# else
#  define LEDCONTROL16HIOPRN_EXPORT Q_DECL_IMPORT
# endif
#else
# define LEDCONTROL16HIOPRN_EXPORT
#endif
