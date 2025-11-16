#ifndef PIECEDEF_GLOBAL_H
#define PIECEDEF_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PIECEDEF_LIB
# define PIECEDEF_EXPORT Q_DECL_EXPORT
#else
# define PIECEDEF_EXPORT Q_DECL_IMPORT
#endif

#endif // PIECEDEF_GLOBAL_H
