#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWTRIALINFORMATION_LIB)
#  define SHOWTRIALINFORMATION_EXPORT Q_DECL_EXPORT
# else
#  define SHOWTRIALINFORMATION_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWTRIALINFORMATION_EXPORT
#endif
