/*
 * Copyright (C) 2025
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

#include "buttonreplacecolorinlibid_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonReplaceColorInLibID : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	bool		ModeMasterImage;
	QString		AlgoRoot;
	QString		AlgoName;
	int			NeighborLength;
	int			LibID;
	int			PickUpColorRL;
	int			PickUpColorGL;
	int			PickUpColorBL;
	int			PickUpColorRH;
	int			PickUpColorGH;
	int			PickUpColorBH;
	int			ReplaceColorR;
	int			ReplaceColorG;
	int			ReplaceColorB;


	ButtonReplaceColorInLibID(LayersBase *Base ,QWidget *parent);

	virtual void	Prepare(void)	override;

public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

class	GUICmdReplaceColorInLibID : public GUICmdPacketBase
{
public:
	bool		ModeMasterImage	;
	QString		AlgoRoot		;
	QString		AlgoName		;
	int			NeighborLength	;
	int			LibID			;
	int			PickUpColorRL	;
	int			PickUpColorGL	;
	int			PickUpColorBL	;
	int			PickUpColorRH	;
	int			PickUpColorGH	;
	int			PickUpColorBH	;
	int			ReplaceColorR	;
	int			ReplaceColorG	;
	int			ReplaceColorB	;

	GUICmdReplaceColorInLibID(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	void	PickupByColorZone(BYTE **BMap,int XLen ,int YLen
							,ImagePointerContainer &Images,FlexArea &Area);

};