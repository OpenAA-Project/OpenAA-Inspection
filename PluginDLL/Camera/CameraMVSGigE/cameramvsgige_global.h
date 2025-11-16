#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CAMERAMVSGIGE_LIB)
#  define CAMERAMVSGIGE_EXPORT Q_DECL_EXPORT
# else
#  define CAMERAMVSGIGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define CAMERAMVSGIGE_EXPORT
#endif
