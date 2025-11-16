#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SPLITTER_LIB)
#  define SPLITTER_EXPORT Q_DECL_EXPORT
# else
#  define SPLITTER_EXPORT Q_DECL_IMPORT
# endif
#else
# define SPLITTER_EXPORT
#endif
