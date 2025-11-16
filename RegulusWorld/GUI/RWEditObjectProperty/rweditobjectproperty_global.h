#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWEDITOBJECTPROPERTY_LIB)
#  define RWEDITOBJECTPROPERTY_EXPORT Q_DECL_EXPORT
# else
#  define RWEDITOBJECTPROPERTY_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWEDITOBJECTPROPERTY_EXPORT
#endif
