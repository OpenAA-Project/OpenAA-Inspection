#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LEARNTHRESHOLD_LIB)
#  define LEARNTHRESHOLD_EXPORT Q_DECL_EXPORT
# else
#  define LEARNTHRESHOLD_EXPORT Q_DECL_IMPORT
# endif
#else
# define LEARNTHRESHOLD_EXPORT
#endif
