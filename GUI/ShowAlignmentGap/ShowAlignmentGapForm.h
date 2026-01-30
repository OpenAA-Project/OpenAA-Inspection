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


#ifndef SHOWALIGNMENTGAPFORM_H
#define SHOWALIGNMENTGAPFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowAlignmentGapForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XAutoAlignment.h"

class ShowAlignmentGapForm : public GUIFormBase
{
	Q_OBJECT

public:
	ShowAlignmentGapForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowAlignmentGapForm();

	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)	override;

private:
	Ui::ShowAlignmentGapFormClass ui;

private slots:
	void	ResizeAction();
};

class	GUICmdReqAlignGap : public GUICmdPacketBase
{
public:
	int	ShownInspectionID;

	GUICmdReqAlignGap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendAlignGap : public GUICmdPacketBase
{
public:
	GUICmdSendAlignGap(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
/*
	struct GapXY{
		int	X,Y;
		int	GapX,GapY;
	};
	struct GapXY FirstPoint,SecondPoint,ThirdPoint;
*/
	int	FirstX,FirstY;
	int	FirstGapX,FirstGapY;
	int	SecondX,SecondY;
	int	SecondGapX,SecondGapY;
	int	ThirdX,ThirdY;
	int	ThirdGapX,ThirdGapY;
};

#endif // SHOWALIGNMENTGAPFORM_H