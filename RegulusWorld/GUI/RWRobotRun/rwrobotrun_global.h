#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWROBOTRUN_LIB)
#  define RWROBOTRUN_EXPORT Q_DECL_EXPORT
# else
#  define RWROBOTRUN_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWROBOTRUN_EXPORT
#endif
