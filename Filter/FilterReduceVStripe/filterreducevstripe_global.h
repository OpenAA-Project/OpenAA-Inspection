#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FILTERREDUCEVSTRIPE_LIB)
#  define FILTERREDUCEVSTRIPE_EXPORT Q_DECL_EXPORT
# else
#  define FILTERREDUCEVSTRIPE_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILTERREDUCEVSTRIPE_EXPORT
#endif
