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

#include "buttongeneratemaskfrombackground_global.h"
#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include "XAlgorithmLibrary.h"

class	ButtonGenerateMaskFromBackGround : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	DiffBrightness	 ;
	int32	MinObjectDotCount;
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int32							BoundaryWidth ;
	int32							SearchDot;
	bool	CombineArea;

	ButtonGenerateMaskFromBackGround(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};


class	GUICmdGenerateMaskFromBackGround : public GUICmdPacketBase
{
public:
	int		DiffBrightness;
	int		MinObjectDotCount;
	bool							Effective;
	AlgorithmLibraryListContainer	LimitedLib;
	int32							BoundaryWidth ;
	int32							SearchDot;
	bool	CombineArea;

	GUICmdGenerateMaskFromBackGround(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

/*
class	CmdGenerateMaskFromBackGround : public GUIDirectMessage
{
public:

	CmdGenerateMaskFromBackGround(LayersBase *base):GUIDirectMessage(base){}
	CmdGenerateMaskFromBackGround(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};
*/
