#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYROBOTACTION_LIB)
#  define PROPERTYROBOTACTION_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYROBOTACTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYROBOTACTION_EXPORT
#endif
