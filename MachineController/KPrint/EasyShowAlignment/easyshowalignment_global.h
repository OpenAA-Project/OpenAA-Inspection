#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(EASYSHOWALIGNMENT_LIB)
#  define EASYSHOWALIGNMENT_EXPORT Q_DECL_EXPORT
# else
#  define EASYSHOWALIGNMENT_EXPORT Q_DECL_IMPORT
# endif
#else
# define EASYSHOWALIGNMENT_EXPORT
#endif
