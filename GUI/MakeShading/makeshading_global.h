#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MAKESHADING_LIB)
#  define MAKESHADING_EXPORT Q_DECL_EXPORT
# else
#  define MAKESHADING_EXPORT Q_DECL_IMPORT
# endif
#else
# define MAKESHADING_EXPORT
#endif
