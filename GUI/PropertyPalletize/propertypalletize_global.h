#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYPALLETIZE_LIB)
#  define PROPERTYPALLETIZE_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYPALLETIZE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYPALLETIZE_EXPORT
#endif
