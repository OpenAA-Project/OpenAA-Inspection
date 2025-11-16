#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CONTROLLERACCESSG_LIB)
#  define CONTROLLERACCESSG_EXPORT Q_DECL_EXPORT
# else
#  define CONTROLLERACCESSG_EXPORT Q_DECL_IMPORT
# endif
#else
# define CONTROLLERACCESSG_EXPORT
#endif
