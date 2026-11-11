#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LIGHTHIKROBOTLAN_LIB)
#  define LIGHTHIKROBOTLAN_EXPORT Q_DECL_EXPORT
# else
#  define LIGHTHIKROBOTLAN_EXPORT Q_DECL_IMPORT
# endif
#else
# define LIGHTHIKROBOTLAN_EXPORT
#endif
