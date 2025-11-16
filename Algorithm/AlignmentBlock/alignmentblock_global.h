#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ALIGNMENTBLOCK_LIB)
#  define ALIGNMENTBLOCK_EXPORT Q_DECL_EXPORT
# else
#  define ALIGNMENTBLOCK_EXPORT Q_DECL_IMPORT
# endif
#else
# define ALIGNMENTBLOCK_EXPORT
#endif
