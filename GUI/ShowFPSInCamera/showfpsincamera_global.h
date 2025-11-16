#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWFPSINCAMERA_LIB)
#  define SHOWFPSINCAMERA_EXPORT Q_DECL_EXPORT
# else
#  define SHOWFPSINCAMERA_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWFPSINCAMERA_EXPORT
#endif
