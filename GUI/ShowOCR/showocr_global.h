#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWOCR_LIB)
#  define SHOWOCR_EXPORT Q_DECL_EXPORT
# else
#  define SHOWOCR_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWOCR_EXPORT
#endif
