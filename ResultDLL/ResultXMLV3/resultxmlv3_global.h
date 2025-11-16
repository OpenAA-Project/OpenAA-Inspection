#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTXMLV3_LIB)
#  define RESULTXMLV3_EXPORT Q_DECL_EXPORT
# else
#  define RESULTXMLV3_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTXMLV3_EXPORT
#endif
