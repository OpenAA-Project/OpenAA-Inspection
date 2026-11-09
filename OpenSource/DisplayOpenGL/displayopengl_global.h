#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DISPLAYOPENGL_LIB)
#  define DISPLAYOPENGL_EXPORT Q_DECL_EXPORT
# else
#  define DISPLAYOPENGL_EXPORT Q_DECL_IMPORT
# endif
#else
# define DISPLAYOPENGL_EXPORT
#endif
