#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(NGCAUSE_LIB)
#  define NGCAUSE_EXPORT Q_DECL_EXPORT
# else
#  define NGCAUSE_EXPORT Q_DECL_IMPORT
# endif
#else
# define NGCAUSE_EXPORT
#endif
