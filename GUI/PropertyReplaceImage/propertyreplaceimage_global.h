#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYREPLACEIMAGE_LIB)
#  define PROPERTYREPLACEIMAGE_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYREPLACEIMAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYREPLACEIMAGE_EXPORT
#endif
