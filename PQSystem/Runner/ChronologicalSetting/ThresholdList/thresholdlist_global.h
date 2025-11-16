#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(THRESHOLDLIST_LIB)
#  define THRESHOLDLIST_EXPORT Q_DECL_EXPORT
# else
#  define THRESHOLDLIST_EXPORT Q_DECL_IMPORT
# endif
#else
# define THRESHOLDLIST_EXPORT
#endif
