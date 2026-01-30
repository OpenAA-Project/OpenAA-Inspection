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


#ifndef SHOWBARCODE_H
#define SHOWBARCODE_H

#include "showbarcode_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XGUIFormBase.h"
#include "XBCRInspection.h"
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

class	SignalOperandString;
class	SignalOperandInt;

class	ShowBarCode :public GUIFormBase
{
    Q_OBJECT

	QStringList		ResultBarcode;
	QPushButton		ManualButton;

	SignalOperandString *ioCurrentBarcode;

public:
	QFont	MessageSize;
	QColor	ColorBarcode;
	QColor	ColorNoBarcode;
	int32	SysNoCurrentBarcode;

	ShowBarCode(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private slots:
	virtual	void paintEvent ( QPaintEvent * event )	override;
	void	ResizeAction();
	 void on_pushButtonManual_clicked();
};


class	GUICmdReqBarcode : public GUICmdPacketBase
{
public:

	GUICmdReqBarcode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckBarcode : public GUICmdPacketBase
{
public:
	QStringList	ResultBarcode;

	GUICmdAckBarcode(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};


#endif // SHOWBARCODE_H