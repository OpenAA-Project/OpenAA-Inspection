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

#ifndef BUTTONCHANGECURRENTPHASE_H
#define BUTTONCHANGECURRENTPHASE_H

//#include "buttonchangecurrentphase_global.h"
#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "mtToolButtonColored.h"


#define	MaxButtonPhaseNumb	100

class ButtonChangeCurrentPhase : public GUIFormBase
{
	Q_OBJECT

	int	IconSizeW;
	int	IconSizeH;
public:
	QStringList	PhaseTitles;
	QFont		ButtonFont;
	QColor		UncheckedColor;
	QColor		ActiveColor;
	int32		CurrentPhase;
	bool		UsePhaseName;
	QString		OrientationStr;		//Horizontal,Vertical

	mtToolButtonColored	*Buttons[MaxButtonPhaseNumb];

	ButtonChangeCurrentPhase(LayersBase *Base ,QWidget *parent);
	~ButtonChangeCurrentPhase(void);

	virtual void	Prepare(void)	override;
	void	Release(void);
	virtual void	ShowInEdit	(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)override;
private:
	void	ShowButtons(void);
private slots:
	void	ResizeAction();
	void	SlotButtonDown(bool);
	void	SlotChangedPhasePageLayer();
	void	SlotChangeCurrentPhase();
};

class	GUICmdChangeCurrentPhase : public GUICmdPacketBase
{
public:
	int	NewPhase;

	GUICmdChangeCurrentPhase(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCHANGECURRENTPHASE_H