/*
 * Copyright (C) 2021
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

#ifndef INSERTTELOP_H
#define INSERTTELOP_H

#include "inserttelop_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QImage>
#include <QString>
#include <QColor>
#include <QFont>
#include <QTimer>
#include <QDateTime>
#include "XServiceForLayers.h"
#include "XGUIFormBase.h"

class	ImageBuffer;

class	InsertTelop : public GUIFormBase
{
    Q_OBJECT
		
	QString		AddedMessage;
	bool		Visible;
	QTimer		TM;
	QImage		Img1;
	QImage		Img2;

	QImage		*WImage;
	QImage		*RImage;
	QMutex		MutexChangeImageSize;
	int			ImgNumber;

	QDateTime	NowTime;
public:
	QString		Position;
	bool		ShowDate;
	bool		ShowTime;
	QColor		SubtitleColor;
	QFont		SubtitleFont;
	bool		ShowOnMaster;
	bool		ShowOnTarget;
	int32		Phase;
	int32		Page;

	InsertTelop(LayersBase *Base ,QWidget *parent);

	virtual	void	ReadyParam(void) override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	InsertText(int Phase,int Page,const QString &s);
private:
	void	PasteImage(ImageBuffer *Buffer[] ,int DimCounts);
	void	SlotCaptured(ImageBuffer *Buffer[] ,int BufferDimCounts,bool &XReverse ,bool &YReverse);
	void	MakeImage(const QString &s);

	QImage	*GetWPoint(void);
	QImage	*GetRPoint(void);

private slots:
	void	SlotTimeout();
};


class	CmdSetTelopInfoPacket : public GUIDirectMessage
{
public:
	QString		Position;
	bool		ShowDate;
	bool		ShowTime;
	QColor		SubtitleColor;
	QFont		SubtitleFont;

	CmdSetTelopInfoPacket(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSetMessagePacket : public GUIDirectMessage
{
public:
	QString		AddedMessage;

	CmdSetMessagePacket(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdSetVisiblePacket : public GUIDirectMessage
{
public:
	bool		Visible;

	CmdSetVisiblePacket(LayersBase *base):GUIDirectMessage(base){}
};


#endif // INSERTTELOP_H