#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTFRAMEDLL_LIB)
#  define RESULTFRAMEDLL_EXPORT Q_DECL_EXPORT
# else
#  define RESULTFRAMEDLL_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTFRAMEDLL_EXPORT
#endif
