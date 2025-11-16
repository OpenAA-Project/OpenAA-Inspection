/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XNetworkDrive.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XNETWORKDRIVE_H)
#define	XNETWORKDRIVE_H

/*
	Link MPR.lib
*/

#include <QString>

extern	"C"{

bool	CreateNetworkDrive(bool tInitialConnect 
						,int DriveCode				//A drive=0 ,B drive=1 ,,, Z drive=25
						,const QString &tRemoteDiskName
						,const QString &tPassword
						,const QString &tUserName);

bool	DisconnectNetworkDrive(int DriveCode);

};



#endif