#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EASYPROPERTYRASTER_LIB)
#  define EASYPROPERTYRASTER_EXPORT Q_DECL_EXPORT
# else
#  define EASYPROPERTYRASTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define EASYPROPERTYRASTER_EXPORT
#endif
