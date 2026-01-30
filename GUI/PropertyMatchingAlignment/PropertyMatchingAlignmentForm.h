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

#ifndef PROPERTYMATCHINGALIGNMENTFORM_H
#define PROPERTYMATCHINGALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "ui_PropertyMatchingAlignmentForm.h"
#include <QWidget>
#include "XGUIPacketForDLL.h"
#include "XFlexArea.h"

class	MatchingAlignmentBase;

class PropertyMatchingAlignmentForm : public GUIFormBase
{
	Q_OBJECT

public:
	PropertyMatchingAlignmentForm(LayersBase *Base ,QWidget *parent = 0);
	~PropertyMatchingAlignmentForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	void	ShowAreaGrid(void);
	MatchingAlignmentBase	*GetMatchingAlignmentBase(void);

private:
	Ui::PropertyMatchingAlignmentFormClass ui;

private slots:
	void on_pushButtonCreateSpecified_clicked();
	void on_toolButtonSpecified_clicked();
};

//=================================================================================

class	DisplayModeOfMatchingAlignment : public GUIDirectMessage
{
public:
	bool	ModeSpecified;
	DisplayModeOfMatchingAlignment(LayersBase *base):GUIDirectMessage(base){}
};

class	GUICmdAddMatchingAlignmentArea : public GUICmdPacketBase
{
public:
	FlexArea		Area;
	IntList			LayerList;
	double			MatchingRate;
	int				SearchDot;

	GUICmdAddMatchingAlignmentArea(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdCreateSpecified : public GUICmdPacketBase
{
public:
	double	CoverRate;
	double	PickUpVar;
	int		BlockSize;

	GUICmdCreateSpecified(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PROPERTYMATCHINGALIGNMENTFORM_H