/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\Open\XDatabaseType.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#if	!defined(XDATABASETYPE_H)
#define	XDATABASETYPE_H

enum	FieldType{
	ftUnknown
	,ftInteger
	,ftWord
	,ftSmallint
	,ftFixedChar
	,ftDateTime
	,ftFloat
	,ftVarBytes
	,ftString
	,ftBlob
};

enum TriggerAction{
	_TA_BeforeInsert   =1
	,_TA_AfterInsert    =2
	,_TA_BeforeUpdate   =3
	,_TA_AfterUpdate    =4
	,_TA_BeforeDelete   =5
	,_TA_AfterDelete    =6
};

#endif