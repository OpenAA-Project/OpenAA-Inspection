/*
 * Copyright (C) 2026
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

#pragma once

#include "showocr_global.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XGUIFormBase.h"
#include "XOCRInspection.h"
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>
#include <QTextEdit>

class	ShowOCR :public GUIFormBase
{
    Q_OBJECT

	QString			ResultOCR;
	QTextEdit		OCRTextEdit;
	bool			OkOCR;	
public:
	QFont	MessageSize;
	QColor	ColorOCR;
	QColor	ColorNoOCR;
	int32	Phase	;
	int32	Page	;
	QString	ItemName;

	ShowOCR(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
private slots:
	void	ResizeAction();
};


class	GUICmdReqOCRResult : public GUICmdPacketBase
{
public:
	QString	ItemName;
	int32	Phase;	

	GUICmdReqOCRResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckOCRResult : public GUICmdPacketBase
{
public:
	QString	ResultOCR;

	GUICmdAckOCRResult(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};