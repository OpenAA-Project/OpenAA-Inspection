#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EASYPROPERTYMEASURE_LIB)
#  define EASYPROPERTYMEASURE_EXPORT Q_DECL_EXPORT
# else
#  define EASYPROPERTYMEASURE_EXPORT Q_DECL_IMPORT
# endif
#else
# define EASYPROPERTYMEASURE_EXPORT
#endif
