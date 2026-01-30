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


#ifndef SAVEIMAGEMASTERBUTTON_H
#define SAVEIMAGEMASTERBUTTON_H

#include "saveimagemasterbutton_global.h"
#include <QLabel>
#include <QTranslator>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	SaveImageMasterButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	FileNameForSaving;
	int32	UseLayer;	//-1::Save all layers

	SaveImageMasterButton(LayersBase *Base ,QWidget *parent);
	~SaveImageMasterButton(void);
	
	virtual void	Prepare(void)	override;
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
	int	Phase;
	int	TopY;
	int	YCount;
	int	Layer;

	GUICmdReqSaveMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendSaveMasterImage : public GUICmdPacketBase
{
public:
	QByteArray	Data;

	GUICmdSendSaveMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // SAVEIMAGEMASTERBUTTON_H