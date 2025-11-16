#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MULTISPECTRAL_LIB)
#  define MULTISPECTRAL_EXPORT Q_DECL_EXPORT
# else
#  define MULTISPECTRAL_EXPORT Q_DECL_IMPORT
# endif
#else
# define MULTISPECTRAL_EXPORT
#endif
