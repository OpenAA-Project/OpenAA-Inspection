#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CCSCONTROLBYLANVER2_LIB)
#  define CCSCONTROLBYLANVER2_EXPORT Q_DECL_EXPORT
# else
#  define CCSCONTROLBYLANVER2_EXPORT Q_DECL_IMPORT
# endif
#else
# define CCSCONTROLBYLANVER2_EXPORT
#endif
