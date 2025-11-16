#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LOADTHRESHOLD_LIB)
#  define LOADTHRESHOLD_EXPORT Q_DECL_EXPORT
# else
#  define LOADTHRESHOLD_EXPORT Q_DECL_IMPORT
# endif
#else
# define LOADTHRESHOLD_EXPORT
#endif
