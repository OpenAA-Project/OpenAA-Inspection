#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(PROPERTYTEMPLATERULE_LIB)
#  define PROPERTYTEMPLATERULE_EXPORT Q_DECL_EXPORT
# else
#  define PROPERTYTEMPLATERULE_EXPORT Q_DECL_IMPORT
# endif
#else
# define PROPERTYTEMPLATERULE_EXPORT
#endif
