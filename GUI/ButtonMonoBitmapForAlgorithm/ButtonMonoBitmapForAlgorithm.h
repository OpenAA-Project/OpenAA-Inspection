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


#ifndef BUTTONMONOBITMAPFORALGORITHM_H
#define BUTTONMONOBITMAPFORALGORITHM_H

#include "buttonmonobitmapforalgorithm_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonMonoBitmapForAlgorithm : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	ButtonMonoBitmapForAlgorithm(LayersBase *Base ,QWidget *parent);
	~ButtonMonoBitmapForAlgorithm(void);
	
	virtual void	Prepare(void)	override;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

//============================================================================================

class	GUICmdReqMonoBitmapForAlgorithm : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QString	AlgorithmRoot;
	QString	AlgorithmName;
	int32	DotPerLine;
	int32	XByte;
	int32	MaxLines;

	GUICmdReqMonoBitmapForAlgorithm(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendMonoBitmapForAlgorithm : public GUICmdPacketBase
{
public:
	int		GlobalPage;
	QBuffer	Data;

	GUICmdSendMonoBitmapForAlgorithm(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONMONOBITMAPFORALGORITHM_H