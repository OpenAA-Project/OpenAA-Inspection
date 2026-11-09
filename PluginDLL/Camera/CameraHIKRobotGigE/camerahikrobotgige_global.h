#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAHIKROBOTGIGE_LIB)
#  define CAMERAHIKROBOTGIGE_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAHIKROBOTGIGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAHIKROBOTGIGE_EXPORT
#endif
