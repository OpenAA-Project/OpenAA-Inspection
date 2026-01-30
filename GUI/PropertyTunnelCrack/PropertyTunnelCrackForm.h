/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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