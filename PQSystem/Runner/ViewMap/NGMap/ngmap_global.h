#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NGMAP_LIB)
#  define NGMAP_EXPORT Q_DECL_EXPORT
# else
#  define NGMAP_EXPORT Q_DECL_IMPORT
# endif
#else
# define NGMAP_EXPORT
#endif
