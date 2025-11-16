#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PQSYSTEMSETTING_LIB)
#  define PQSYSTEMSETTING_EXPORT Q_DECL_EXPORT
# else
#  define PQSYSTEMSETTING_EXPORT Q_DECL_IMPORT
# endif
#else
# define PQSYSTEMSETTING_EXPORT
#endif
