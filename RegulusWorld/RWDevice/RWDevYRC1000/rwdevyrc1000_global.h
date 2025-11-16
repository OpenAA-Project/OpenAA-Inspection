#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWDEVYRC1000_LIB)
#  define RWDEVYRC1000_EXPORT Q_DECL_EXPORT
# else
#  define RWDEVYRC1000_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWDEVYRC1000_EXPORT
#endif
