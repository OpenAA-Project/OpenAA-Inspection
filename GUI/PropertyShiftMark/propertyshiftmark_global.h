#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYSHIFTMARK_LIB)
#  define PROPERTYSHIFTMARK_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYSHIFTMARK_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYSHIFTMARK_EXPORT
#endif
