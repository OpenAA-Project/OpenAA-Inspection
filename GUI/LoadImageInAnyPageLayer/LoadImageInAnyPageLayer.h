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


#ifndef LOADIMAGEINANYPAGELAYER_H
#define LOADIMAGEINANYPAGELAYER_H

//#include "loadimageinanypagelayer_global.h"


#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QString>
#include <QColor>
#include <QFont>

class	LoadImageInAnyPageLayer : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ToMaster;
	int32	InPage;
	int32	InLayer;

	QString LoadedFileName;

	LoadImageInAnyPageLayer(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	LoadFile(QString &FileName,int CPage ,int CLayer,bool iToMaster);

private:
	void	LoadFile(QString &FileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

class	GUICmdSendLoadImageInAnyPagelayer : public GUICmdPacketBase
{
public:
	bool	ToMaster;
	int32	InLayer;

	int	TopY;
	int	YCount;
	int	Layer;
	int	iDotPerLine;
	QByteArray	Data;

	GUICmdSendLoadImageInAnyPagelayer(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdLoadImageInAnyPageLayerPacket : public GUIDirectMessage
{
public:
	QString FileName;
	CmdLoadImageInAnyPageLayerPacket(LayersBase *base):GUIDirectMessage(base){}
	CmdLoadImageInAnyPageLayerPacket(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
#endif // LOADIMAGEINANYPAGELAYER_H