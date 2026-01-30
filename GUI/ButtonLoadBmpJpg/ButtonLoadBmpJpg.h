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


#ifndef BUTTONLOADBMPJPG_H
#define BUTTONLOADBMPJPG_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonLoadBmpJpg : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ToMaster;
	int32	LoadedPage;

	QString LoadedFileName;

	ButtonLoadBmpJpg(LayersBase *Base ,QWidget *parent);
	virtual void	Prepare(void)								override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	QString	LoadFileWithDialog(void);
	bool	LoadFile(QString &FileName,bool iToMaster);
	bool	LoadFile(QString &FileName ,QImage &Img);
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)							override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdReqLoadBmpJpg : public GUICmdPacketBase
{
public:
	QImage	Img;
	bool	ToMaster;

	GUICmdReqLoadBmpJpg(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdLoadBmpJpgPacket : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBmpJpgPacketMaster : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgPacketMaster(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBmpJpgPacketTarget : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgPacketTarget(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdLoadBmpJpgPacketQImage : public GUIDirectMessage
{
public:
	QString FileName;
	QImage	Image;
	bool	Success;
	CmdLoadBmpJpgPacketQImage(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdLoadBmpJpgWithDialogPacket : public GUIDirectMessage
{
public:
	QString FileName;
	bool	Success;
	CmdLoadBmpJpgWithDialogPacket(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONLOADBMPJPG_H