#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(LISTSELECTFIXEDPAGE_LIB)
#  define LISTSELECTFIXEDPAGE_EXPORT Q_DECL_EXPORT
# else
#  define LISTSELECTFIXEDPAGE_EXPORT Q_DECL_IMPORT
# endif
#else
# define LISTSELECTFIXEDPAGE_EXPORT
#endif
