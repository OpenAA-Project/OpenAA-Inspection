#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWRESULTDETAIL_LIB)
#  define SHOWRESULTDETAIL_EXPORT Q_DECL_EXPORT
# else
#  define SHOWRESULTDETAIL_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWRESULTDETAIL_EXPORT
#endif
