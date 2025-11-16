#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(BUTTONSHIFTIMAGE_LIB)
#  define BUTTONSHIFTIMAGE_EXPORT Q_DECL_EXPORT
# else
#  define BUTTONSHIFTIMAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define BUTTONSHIFTIMAGE_EXPORT
#endif
