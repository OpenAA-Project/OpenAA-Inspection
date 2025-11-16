#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(DISPLAYPRODUCTIVITY_LIB)
#  define DISPLAYPRODUCTIVITY_EXPORT Q_DECL_EXPORT
# else
#  define DISPLAYPRODUCTIVITY_EXPORT Q_DECL_IMPORT
# endif
#else
# define DISPLAYPRODUCTIVITY_EXPORT
#endif
