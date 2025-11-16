/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SeqLib\SeqLib\seqlib_global.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#ifndef SEQLIB_GLOBAL_H
#define SEQLIB_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SEQLIB_LIB
# define SEQLIB_EXPORT Q_DECL_EXPORT
#else
# define SEQLIB_EXPORT Q_DECL_IMPORT
#endif

#endif // SEQLIB_GLOBAL_H
