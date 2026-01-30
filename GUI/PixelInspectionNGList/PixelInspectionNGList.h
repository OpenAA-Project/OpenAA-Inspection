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


#ifndef PIXELINSPECTIONNGLIST_H
#define PIXELINSPECTIONNGLIST_H

#include <QPushButton>
#include <QTableWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XAlgorithmLibrary.h"
#include "XPixelInspection.h"



class	PixelInspectionNGList :public GUIFormBase
{
    Q_OBJECT
public:
	int32	WidthLineNumber;
	int32	WidthPageNumber;
	int32	WidthPosition;
	int32	WidthAttribute;

	PixelInspectionNGDataListContainer	NGData;
	AlgorithmLibraryListContainer	LibList;
	QTableWidget	NGList;
	
	QString			TargetImagePanelName;

	PixelInspectionNGList(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private slots:
	void	ResizeAction();
	void	ListItemClicked ( QTableWidgetItem * item );
	void	ListItemSelectionChanged ();
};


class	GUICmdReqNGList : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendNGList : public GUICmdPacketBase
{
public:
	PixelInspectionNGDataListContainer	NGData;

	GUICmdSendNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PIXELINSPECTIONNGLIST_H