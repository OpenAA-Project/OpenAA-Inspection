#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWDEV3DMOUSE_LIB)
#  define RWDEV3DMOUSE_EXPORT Q_DECL_EXPORT
# else
#  define RWDEV3DMOUSE_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWDEV3DMOUSE_EXPORT
#endif
