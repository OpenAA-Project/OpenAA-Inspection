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

#ifndef BUTTONCLEARMASTERINFO_H
#define BUTTONCLEARMASTERINFO_H

#include "buttonclearmasterinfo_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>

class	ButtonClearMasterInfo : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QImage	ButtonIcon;
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	int32	WaitingMilisec;

	ButtonClearMasterInfo(LayersBase *Base ,QWidget *parent);
	~ButtonClearMasterInfo(void);
	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);
	void SlotClickedPhase (bool checked);
private slots:
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqButtonClearMasterInfo : public GUICmdPacketBase
{
public:
	GUICmdReqButtonClearMasterInfo(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdReqButtonClearMasterInfoPhase : public GUICmdPacketBase
{
public:
	GUICmdReqButtonClearMasterInfoPhase(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCLEARMASTERINFO_H