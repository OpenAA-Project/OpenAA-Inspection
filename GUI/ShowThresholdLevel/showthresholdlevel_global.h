#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWTHRESHOLDLEVEL_LIB)
#  define SHOWTHRESHOLDLEVEL_EXPORT Q_DECL_EXPORT
# else
#  define SHOWTHRESHOLDLEVEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWTHRESHOLDLEVEL_EXPORT
#endif
