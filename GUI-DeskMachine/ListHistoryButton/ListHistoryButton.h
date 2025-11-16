/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\ListHistoryButton\ListHistoryButton.h
** Author : YYYYYYYYYY
****************************************************************************-**/

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
