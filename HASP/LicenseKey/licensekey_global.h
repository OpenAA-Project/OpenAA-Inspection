#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LICENSEKEY_LIB)
#  define LICENSEKEY_EXPORT Q_DECL_EXPORT
# else
#  define LICENSEKEY_EXPORT Q_DECL_IMPORT
# endif
#else
# define LICENSEKEY_EXPORT
#endif
