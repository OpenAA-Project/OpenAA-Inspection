#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(FILTERSHIFTBYLAYER_LIB)
#  define FILTERSHIFTBYLAYER_EXPORT Q_DECL_EXPORT
# else
#  define FILTERSHIFTBYLAYER_EXPORT Q_DECL_IMPORT
# endif
#else
# define FILTERSHIFTBYLAYER_EXPORT
#endif
