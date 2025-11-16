#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(ACTIVATEDLICENSE_LIB)
#  define ACTIVATEDLICENSE_EXPORT Q_DECL_EXPORT
# else
#  define ACTIVATEDLICENSE_EXPORT Q_DECL_IMPORT
# endif
#else
# define ACTIVATEDLICENSE_EXPORT
#endif
