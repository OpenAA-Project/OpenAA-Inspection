#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SETANGLEINSPECTION_LIB)
#  define SETANGLEINSPECTION_EXPORT Q_DECL_EXPORT
# else
#  define SETANGLEINSPECTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define SETANGLEINSPECTION_EXPORT
#endif
