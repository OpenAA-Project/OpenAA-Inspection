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


#ifndef AUTOSAVEIMAGEMASTERBUTTON_H
#define AUTOSAVEIMAGEMASTERBUTTON_H

#include "autosaveimagemasterbutton_global.h"
#include <QLabel>
#include <QTranslator>
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QIODevice>
#include <QByteArray>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	AutoSaveImageMasterButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
	QString		ButtonObjectName;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	DirectoryNameForSaving;

	AutoSaveImageMasterButton(LayersBase *Base ,QWidget *parent);
	~AutoSaveImageMasterButton(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	bool SaveImage(QString FileName);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqSaveMasterImage : public GUICmdPacketBase
{
public:
	int	TopY;
	int	YCount;
	int	Layer;

	GUICmdReqSaveMasterImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveMasterImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveMasterImage(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // AUTOSAVEIMAGEMASTERBUTTON_H