#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONLOADSHIFTMARK_LIB)
#  define BUTTONLOADSHIFTMARK_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONLOADSHIFTMARK_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONLOADSHIFTMARK_EXPORT
#endif
