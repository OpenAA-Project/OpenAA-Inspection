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

#ifndef BUTTONLOADHISTOGRAMDATA_H
#define BUTTONLOADHISTOGRAMDATA_H

#include "buttonloadhistogramdata_global.h"

#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonLoadHistogramData : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	ButtonLoadHistogramData(LayersBase *Base ,QWidget *parent);
	~ButtonLoadHistogramData(void);
	
	virtual void	Prepare(void)	override;

	void ExecuteLoad(QIODevice &F);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


//============================================================================================

class	GUICmdWriteHistogramData : public GUICmdPacketBase
{
public:
	QBuffer	Data;

	GUICmdWriteHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUIAckWriteHistogramData : public GUICmdPacketBase
{
public:
	bool	Ok;
	QString	ErrorMsg;

	GUIAckWriteHistogramData(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	ExecuteLoadHistogram : public GUIDirectMessage
{
public:
	QString	FileName;

	ExecuteLoadHistogram(LayersBase *base):GUIDirectMessage(base){}
};

#endif // BUTTONLOADHISTOGRAMDATA_H