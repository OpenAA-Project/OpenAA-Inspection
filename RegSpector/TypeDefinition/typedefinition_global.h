#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(TYPEDEFINITION_LIB)
#  define TYPEDEFINITION_EXPORT Q_DECL_EXPORT
# else
#  define TYPEDEFINITION_EXPORT Q_DECL_IMPORT
# endif
#else
# define TYPEDEFINITION_EXPORT
#endif
