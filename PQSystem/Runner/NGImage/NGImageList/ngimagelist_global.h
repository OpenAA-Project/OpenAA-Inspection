#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NGIMAGELIST_LIB)
#  define NGIMAGELIST_EXPORT Q_DECL_EXPORT
# else
#  define NGIMAGELIST_EXPORT Q_DECL_IMPORT
# endif
#else
# define NGIMAGELIST_EXPORT
#endif
