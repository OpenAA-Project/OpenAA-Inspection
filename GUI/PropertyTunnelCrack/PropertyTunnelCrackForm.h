/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PropertyTunnelCrack\PropertyTunnelCrackForm.h
** Author : YYYYYYYYYY
****************************************************************************-**/
#ifndef PROPERTYTUNNELCRACKFORM_H
#define PROPERTYTUNNELCRACKFORM_H


#include "ui_PropertyTunnelCrackForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XTunnelCrack.h"

class PropertyTunnelCrackForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyTunnelCrackForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyTunnelCrackForm();


	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::PropertyTunnelCrackFormClass ui;

	TunnelCrackBase	*GetTunnelCrackBase(void);
	void	ShowAreaGrid(void);
	TunnelCrackInfoListContainer	TunnelCrackInfo;

private slots:
	void on_pushButtonLoadAll_clicked();
	void on_pushButtonSaveAll_clicked();
	void on_pushButtonEditLibrary_clicked();
};

//==================================================================

class	GUICmdSendAddManualTunnelCrack : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	int			SelectedLibID;
	IntList		LayerList;

	GUICmdSendAddManualTunnelCrack(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqTunnelCrackList : public GUICmdPacketBase
{
public:
	GUICmdReqTunnelCrackList(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUICmdSendTunnelCrackList : public GUICmdPacketBase
{
public:
	TunnelCrackInfoListContainer	TunnelCrackInfo;

	GUICmdSendTunnelCrackList(LayersBase *Base ,QString emitterRoot ,QString emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	void	MakeData(int localPage);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PROPERTYTUNNELCRACKFORM_H
