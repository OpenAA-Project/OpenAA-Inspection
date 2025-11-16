#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FORLINUX_LIB)
#  define FORLINUX_EXPORT Q_DECL_EXPORT
# else
#  define FORLINUX_EXPORT Q_DECL_IMPORT
# endif
#else
# define FORLINUX_EXPORT
#endif
