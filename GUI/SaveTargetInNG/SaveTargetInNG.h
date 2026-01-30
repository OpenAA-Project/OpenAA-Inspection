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

#ifndef SAVETARGETINNG_H
#define SAVETARGETINNG_H

#include "savetargetinng_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "XResult.h"

class	SaveTargetInNG : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	int64		LastInspectionID;
	GUIFormBase	*SaveForm;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	SavedFolder;
	bool	OnlyNG;
	bool	BootupON;
	bool	UseCamImage;
	bool	CheckDisk;
	bool	UseGeneralStockerToGetPath;
	QStringList		SaveFolderList;
	int32			DiskSpaceToCheck;
	int32	UseLayer;	//-1::Save all layers


	SaveTargetInNG(LayersBase *Base ,QWidget *parent);
	~SaveTargetInNG(void);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;

private slots:

	void	ResizeAction();
};

//-----------------------------------------------------------------------

class	GUICmdReqOkNG : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendOkNG : public GUICmdPacketBase
{
public:
	ResultInspection::CriticalErrorMode	CriticalError;
	bool3	ResultOk;
	bool	ResultTimeOut ;
	bool	ResultMaxError;

	GUICmdSendOkNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // SAVETARGETINNG_H