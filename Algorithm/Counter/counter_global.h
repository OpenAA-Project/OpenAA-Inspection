#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COUNTER_LIB)
#  define COUNTER_EXPORT Q_DECL_EXPORT
# else
#  define COUNTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define COUNTER_EXPORT
#endif
