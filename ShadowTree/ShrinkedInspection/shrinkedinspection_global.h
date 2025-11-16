#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHRINKEDINSPECTION_LIB)
#  define SHRINKEDINSPECTION_EXPORT Q_DECL_EXPORT
# else
#  define SHRINKEDINSPECTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHRINKEDINSPECTION_EXPORT
#endif
