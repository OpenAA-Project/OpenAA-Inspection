#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(CHECKDATAVALIDATION_LIB)
#  define CHECKDATAVALIDATION_EXPORT Q_DECL_EXPORT
# else
#  define CHECKDATAVALIDATION_EXPORT Q_DECL_IMPORT
# endif
#else
# define CHECKDATAVALIDATION_EXPORT
#endif
