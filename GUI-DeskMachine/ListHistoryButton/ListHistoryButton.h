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


#ifndef LISTHISTORYBUTTON_H
#define LISTHISTORYBUTTON_H

#include "listhistorybutton_global.h"
#include <QPushButton>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"

class ListHistoryButtonForm;

class ListHistoryButton : public GUIFormBase
{
	Q_OBJECT

	QPushButton		Button;
	ListHistoryButtonForm	*ListHistoryForm;

public:
	QString		Msg;
	QFont		CFont;
	int32		PopupFormX;
	int32		PopupFormY;
	bool		Popup;
	bool		AnytimeShow;
	bool		LocationInForm;

	ListHistoryButton(LayersBase *Base ,QWidget *parent);
	~ListHistoryButton();

	virtual void	Prepare(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID)		override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

protected:
	virtual	void	keyPressEvent	( QKeyEvent * event )	override;
	virtual	void	keyReleaseEvent	( QKeyEvent * event )	override;

private:

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // LISTHISTORYBUTTON_H