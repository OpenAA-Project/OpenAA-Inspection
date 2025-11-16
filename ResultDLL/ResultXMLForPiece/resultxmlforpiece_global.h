#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(RESULTXMLFORPIECE_LIB)
#  define RESULTXMLFORPIECE_EXPORT Q_DECL_EXPORT
# else
#  define RESULTXMLFORPIECE_EXPORT Q_DECL_IMPORT
# endif
#else
# define RESULTXMLFORPIECE_EXPORT
#endif
