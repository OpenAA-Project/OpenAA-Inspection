#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(COPYBYCONTROLPOINTS_LIB)
#  define COPYBYCONTROLPOINTS_EXPORT Q_DECL_EXPORT
# else
#  define COPYBYCONTROLPOINTS_EXPORT Q_DECL_IMPORT
# endif
#else
# define COPYBYCONTROLPOINTS_EXPORT
#endif
