#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CONTROLLERACCESSSELF_LIB)
#  define CONTROLLERACCESSSELF_EXPORT Q_DECL_EXPORT
# else
#  define CONTROLLERACCESSSELF_EXPORT Q_DECL_IMPORT
# endif
#else
# define CONTROLLERACCESSSELF_EXPORT
#endif
