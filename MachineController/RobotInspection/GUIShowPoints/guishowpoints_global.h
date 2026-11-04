#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(GUISHOWPOINTS_LIB)
#  define GUISHOWPOINTS_EXPORT Q_DECL_EXPORT
# else
#  define GUISHOWPOINTS_EXPORT Q_DECL_IMPORT
# endif
#else
# define GUISHOWPOINTS_EXPORT
#endif
