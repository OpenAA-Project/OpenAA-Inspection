#ifndef IOLOGGER_GLOBAL_H
#define IOLOGGER_GLOBAL_H

#include <qglobal.h>

#ifdef IOLOGGER_LIB
# define IOLOGGER_EXPORT Q_DECL_EXPORT
#else
# define IOLOGGER_EXPORT Q_DECL_IMPORT
#endif

#endif // IOLOGGER_GLOBAL_H
