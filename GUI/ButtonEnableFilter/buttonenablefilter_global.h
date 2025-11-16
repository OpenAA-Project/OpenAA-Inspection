#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONENABLEFILTER_LIB)
#  define BUTTONENABLEFILTER_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONENABLEFILTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONENABLEFILTER_EXPORT
#endif
