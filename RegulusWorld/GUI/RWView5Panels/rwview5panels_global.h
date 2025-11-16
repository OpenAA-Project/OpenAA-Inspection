#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWVIEW5PANELS_LIB)
#  define RWVIEW5PANELS_EXPORT Q_DECL_EXPORT
# else
#  define RWVIEW5PANELS_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWVIEW5PANELS_EXPORT
#endif
