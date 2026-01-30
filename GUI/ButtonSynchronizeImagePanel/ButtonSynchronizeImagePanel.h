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

#ifndef BUTTONSYNCHRONIZEIMAGEPANEL_H
#define BUTTONSYNCHRONIZEIMAGEPANEL_H

#include "buttonsynchronizeimagepanel_global.h"

#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "mtToolButtonColored.h"
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

class ButtonSynchronizeImagePanel : public GUIFormBase
{
	Q_OBJECT

	int	IconSizeW;
	int	IconSizeH;
public:
	QString		ButtonTitle;
	QFont		ButtonFont;
	QColor		UncheckedColor;
	QColor		ActiveColor;

	QString		SrcAlgoImagePanelRoot;
	QString		SrcAlgoImagePanelName;
	QString		SrcAlgoImagePanelInst;

	QString		TargetImagePanelRoot;
	QString		TargetImagePanelName;
	QString		TargetImagePanelInst;

	QPushButton	Button;

	ButtonSynchronizeImagePanel(LayersBase *Base ,QWidget *parent);
	~ButtonSynchronizeImagePanel(void);

	virtual void	Prepare(void)		override;
	void	Release(void);
	virtual void	ShowInEdit(void)	override;

private:

private slots:
	void	ResizeAction();
	void	SlotButtonDown();
};

#endif // BUTTONSYNCHRONIZEIMAGEPANEL_H