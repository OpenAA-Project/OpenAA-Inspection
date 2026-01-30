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


#ifndef LISTHISTORYFORM_H
#define LISTHISTORYFORM_H

#include "XGUIFormBase.h"
#include "ui_ListHistoryForm.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ListHistoryForm : public GUIFormBase
{
	Q_OBJECT

	bool	SyncMode;
	bool	LocalMode;
	int		ColumnNoID		;
	int		ColumnNoTime	;
	int		ColumnNoOKNG	;	
	int		ColumnNoSV		;
	int		ColumnNoMS		;

	QString	StrResultNot;
	QString	StrResultOK;
	QString	StrResultTMHalt;
	QString	StrResultErHalt;
	QString	StrResultNG;
	QString	StrResultNGOther;
	QString	StrWrittenTrue;
	QString	StrWrittenFalse;

public:
	QColor	ColorOK;
	QColor	ColorNG;
	QColor	ColorNot;
	QColor	ColorIrregular;
	bool	ShowColumnID	;
	bool	ShowColumnTime	;
	bool	ShowColumnOKNG	;
	bool	ShowColumnSV	;
	bool	ShowColumnMS	;

	ListHistoryForm(LayersBase *Base ,QWidget *parent = 0);
	~ListHistoryForm();

	virtual void	Prepare(void)			override;
	virtual void	ReadyParam(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)		override;
	virtual void	RxSync(QByteArray &f)	override;

	QString	OutputFileName;
	bool	EditMode;

private:
	Ui::ListHistoryFormClass ui;

private slots:
	void on_tableWidgetHistory_doubleClicked(QModelIndex);
	void on_ButtonReset_clicked();
	void	ResizeAction();
};


class	GUIReqRemoveHistry : public GUICmdPacketBase
{
public:

	GUIReqRemoveHistry(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // LISTHISTORYFORM_H