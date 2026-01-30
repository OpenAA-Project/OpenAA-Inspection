/*
 * Copyright (C) 2022
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

#ifndef PROPERTYZREGULATIONFORM_H
#define PROPERTYZREGULATIONFORM_H

#include "ui_PropertyZRegulationForm.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XZAxisRegulation.h"

class PropertyZRegulationForm : public GUIFormBase
{
	Q_OBJECT

	ItemInfoList	*LList[1000];

public:
	PropertyZRegulationForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyZRegulationForm();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	BuildForShow(void)	override;
	
private:
	Ui::PropertyZRegulationFormClass ui;

	void	ShowGrid(void);

private slots:
	void on_tableWidget_doubleClicked(QModelIndex);
	void on_pushButtonCalc_clicked();
};

//========================================================================

class	GUICmdAddItem : public GUICmdPacketBase
{
public:
	FlexArea	Area;
	IntList		Layers;
	int32		AxisID;
	int32		CenterInMaster;
	int32		OKZone;

	GUICmdAddItem(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdExecuteCalc: public GUICmdPacketBase
{
public:
	GUICmdExecuteCalc(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqItemInfo: public GUICmdPacketBase
{
public:
	GUICmdReqItemInfo(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckItemInfo: public GUICmdPacketBase
{
public:
	ItemInfoContainer	Infos;

	GUICmdAckItemInfo(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSetItemInfo: public GUICmdPacketBase
{
public:
	int32	AxisID;
	int32	ItemID;
	int32	Layer;
	int32	Page;
	int32		CenterInMaster;
	int32		OKZone;

	GUICmdSetItemInfo(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};

#endif // PROPERTYZREGULATIONFORM_H