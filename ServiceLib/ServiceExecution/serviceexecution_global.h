#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SERVICEEXECUTION_LIB)
#  define SERVICEEXECUTION_EXPORT Q_DECL_EXPORT
# else
#  define SERVICEEXECUTION_EXPORT Q_DECL_IMPORT
# endif
#else
# define SERVICEEXECUTION_EXPORT
#endif
