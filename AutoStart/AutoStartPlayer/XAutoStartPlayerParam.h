/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\AutoStart\AutoStartPlayer\XAutoStartPlayerParam.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XAUTOSTARTPLAYERPARAM_H)
#define	XAUTOSTARTPLAYERPARAM_H

#include"XParamBase.h"
#include"XIntClass.h"


class	ParamAutoStart : public ParamBase
{
public:
	int32	LoopCount;
	QString	Arguments;
	QString	SettingFileName;

	ParamAutoStart(void);
	~ParamAutoStart(void){}
	virtual	QString	GetDataText(void){	return("AutoStartData");	};
	virtual	QString	GetDefaultFileName(void){	return(SettingFileName);	}
	void	SetDefaultFileName(const QString &filename)	{	SettingFileName=filename;	}
};

#endif