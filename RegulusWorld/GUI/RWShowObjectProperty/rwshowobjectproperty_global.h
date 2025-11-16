#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWSHOWOBJECTPROPERTY_LIB)
#  define RWSHOWOBJECTPROPERTY_EXPORT Q_DECL_EXPORT
# else
#  define RWSHOWOBJECTPROPERTY_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWSHOWOBJECTPROPERTY_EXPORT
#endif
