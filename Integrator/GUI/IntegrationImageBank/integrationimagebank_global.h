#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(INTEGRATIONIMAGEBANK_LIB)
#  define INTEGRATIONIMAGEBANK_EXPORT Q_DECL_EXPORT
# else
#  define INTEGRATIONIMAGEBANK_EXPORT Q_DECL_IMPORT
# endif
#else
# define INTEGRATIONIMAGEBANK_EXPORT
#endif
