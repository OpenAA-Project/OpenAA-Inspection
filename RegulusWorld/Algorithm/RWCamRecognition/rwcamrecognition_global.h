#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RWCAMRECOGNITION_LIB)
#  define RWCAMRECOGNITION_EXPORT Q_DECL_EXPORT
# else
#  define RWCAMRECOGNITION_EXPORT Q_DECL_IMPORT
# endif
#else
# define RWCAMRECOGNITION_EXPORT
#endif
