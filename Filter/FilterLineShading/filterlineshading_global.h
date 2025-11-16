#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FILTERLINESHADING_LIB)
#  define FILTERLINESHADING_EXPORT Q_DECL_EXPORT
# else
#  define FILTERLINESHADING_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILTERLINESHADING_EXPORT
#endif
