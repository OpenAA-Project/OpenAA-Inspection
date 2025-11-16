#pragma once

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(SHOWBINDNGNAMINGLIST_LIB)
#  define SHOWBINDNGNAMINGLIST_EXPORT Q_DECL_EXPORT
# else
#  define SHOWBINDNGNAMINGLIST_EXPORT Q_DECL_IMPORT
# endif
#else
# define SHOWBINDNGNAMINGLIST_EXPORT
#endif
