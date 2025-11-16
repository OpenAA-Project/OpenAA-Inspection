#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTXMLPRINTFAST_LIB)
#  define RESULTXMLPRINTFAST_EXPORT Q_DECL_EXPORT
# else
#  define RESULTXMLPRINTFAST_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTXMLPRINTFAST_EXPORT
#endif
