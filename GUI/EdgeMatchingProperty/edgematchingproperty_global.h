#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EDGEMATCHINGPROPERTY_LIB)
#  define EDGEMATCHINGPROPERTY_EXPORT Q_DECL_EXPORT
# else
#  define EDGEMATCHINGPROPERTY_EXPORT Q_DECL_IMPORT
# endif
#else
# define EDGEMATCHINGPROPERTY_EXPORT
#endif
