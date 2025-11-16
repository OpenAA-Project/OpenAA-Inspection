#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(WORLD3DIMAGEPANEL_LIB)
#  define WORLD3DIMAGEPANEL_EXPORT Q_DECL_EXPORT
# else
#  define WORLD3DIMAGEPANEL_EXPORT Q_DECL_IMPORT
# endif
#else
# define WORLD3DIMAGEPANEL_EXPORT
#endif
