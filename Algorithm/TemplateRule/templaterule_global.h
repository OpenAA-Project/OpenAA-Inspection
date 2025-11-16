#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TEMPLATERULE_LIB)
#  define TEMPLATERULE_EXPORT Q_DECL_EXPORT
# else
#  define TEMPLATERULE_EXPORT Q_DECL_IMPORT
# endif
#else
# define TEMPLATERULE_EXPORT
#endif
