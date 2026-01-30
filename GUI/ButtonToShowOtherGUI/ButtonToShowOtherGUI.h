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


#ifndef BUTTONTOSHOWOTHERGUI_H
#define BUTTONTOSHOWOTHERGUI_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QColor>
#include <QFont>

class	ButtonToShowOtherGUI : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	GUIFileName;
	GUIFormBase	*CurrentGUI;

	ButtonToShowOtherGUI(LayersBase *Base ,QWidget *parent);
	~ButtonToShowOtherGUI(void);
	
	virtual void	Prepare(void)	override;
	//virtual	void	AssociateComponent(ComponentListContainer &List)	override;
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
	void	SlotClicked( bool checked );
	void	ResizeAction();
};


#endif // BUTTONTOSHOWOTHERGUI_H