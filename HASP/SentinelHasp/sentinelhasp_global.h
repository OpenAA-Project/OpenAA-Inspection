#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SENTINELHASP_LIB)
#  define SENTINELHASP_EXPORT Q_DECL_EXPORT
# else
#  define SENTINELHASP_EXPORT Q_DECL_IMPORT
# endif
#else
# define SENTINELHASP_EXPORT
#endif
