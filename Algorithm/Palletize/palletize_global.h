#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PALLETIZE_LIB)
#  define PALLETIZE_EXPORT Q_DECL_EXPORT
# else
#  define PALLETIZE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PALLETIZE_EXPORT
#endif
