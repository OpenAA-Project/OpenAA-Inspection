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


#ifndef BUTTONSAVEMASTERDATA_H
#define BUTTONSAVEMASTERDATA_H

#include "buttonsavemasterdata_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonSaveMasterData : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString ErrorMessageOfFalse;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	ModeCheckDupName;
	bool	ExecuteInitialAfterSaving;

	ButtonSaveMasterData(LayersBase *Base ,QWidget *parent);
	~ButtonSaveMasterData(void);
	
	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

	virtual	void	RxSync(QByteArray &f)	override;
	
	bool	CommandSaveMaster	(QString &tMasterName,QString &tRemark ,bool SilentMode);
	int		CommandSearchMaster	(QString &tMasterName);
public slots:
	void SlotClicked (bool checked);
private slots:
	void	ResizeAction();
};


#endif // BUTTONSAVEMASTERDATA_H