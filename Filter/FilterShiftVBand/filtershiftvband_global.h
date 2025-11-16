#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FILTERSHIFTVBAND_LIB)
#  define FILTERSHIFTVBAND_EXPORT Q_DECL_EXPORT
# else
#  define FILTERSHIFTVBAND_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILTERSHIFTVBAND_EXPORT
#endif
