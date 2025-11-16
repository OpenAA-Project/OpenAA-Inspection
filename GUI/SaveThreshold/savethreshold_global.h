#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SAVETHRESHOLD_LIB)
#  define SAVETHRESHOLD_EXPORT Q_DECL_EXPORT
# else
#  define SAVETHRESHOLD_EXPORT Q_DECL_IMPORT
# endif
#else
# define SAVETHRESHOLD_EXPORT
#endif
