#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWROBOTACTIVITY_LIB)
#  define SHOWROBOTACTIVITY_EXPORT Q_DECL_EXPORT
# else
#  define SHOWROBOTACTIVITY_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWROBOTACTIVITY_EXPORT
#endif
