/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUIInExe.h
** Author : YYYYYYYYYY
****************************************************************************-**/


#if	!defined(XGUIInExe_H)
#define	XGUIInExe_H

#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include "XServiceForLayers.h"
#include <QBuffer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "XDatabase.h"
#include "XFastComm.h"
#include "XIntegrationComm.h"

class	GUIFastComm : public FastComm ,public ServiceForLayers
{
    Q_OBJECT
public:
	GUIFastComm(LayersBase *base ,QObject * parent = 0);
	~GUIFastComm(void){}

private slots:
	virtual	void	SlotReceived(int,int);
};

inline	GUIFastComm::GUIFastComm(LayersBase *base ,QObject * parent)
	: FastComm(parent),ServiceForLayers(base)
{}

class	GUIIntegrationCommPack : public IntegrationCommPack
{
    Q_OBJECT
public:
	GUIIntegrationCommPack(LayersBase *base) : IntegrationCommPack(base){}
	~GUIIntegrationCommPack(void){}

private slots:
	virtual	void	SlotReceived(int,int);
};


#endif