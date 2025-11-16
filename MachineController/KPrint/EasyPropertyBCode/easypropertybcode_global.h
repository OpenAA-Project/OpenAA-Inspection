#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EASYPROPERTYBCODE_LIB)
#  define EASYPROPERTYBCODE_EXPORT Q_DECL_EXPORT
# else
#  define EASYPROPERTYBCODE_EXPORT Q_DECL_IMPORT
# endif
#else
# define EASYPROPERTYBCODE_EXPORT
#endif
