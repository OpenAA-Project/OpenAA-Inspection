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

#pragma once

#include "buttonconvertcolordistribution_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIFormBase.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>
#include "XDoubleClass.h"

class	ButtonConvertColorDistribution : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ChangeMasterImage;

	ButtonConvertColorDistribution(LayersBase *Base ,QWidget *parent);
	~ButtonConvertColorDistribution(void);
	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

//============================================================================================

class	GUICmdConvertColorDistribution : public GUICmdPacketBase
{
public:
	bool	ChangeMasterImage;

	GUICmdConvertColorDistribution(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
private:
	void	MakeAvrV(const ImagePointerContainer &Images ,const BYTE **MaskBitmap,DoubleList &Avr,DoubleList &V
					,int X1,int Y1,int X2,int Y2,bool SmoothMode);
	void	Convert(const ImagePointerContainer &Images ,const BYTE	**MaskBitmap,DoubleList &SrcAvr,DoubleList &DstAvr,DoubleList &DifV
					,int X1,int Y1,int X2,int Y2);

};