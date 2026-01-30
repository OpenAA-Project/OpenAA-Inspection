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

#ifndef BUTTONSELECTMACHINEFORREVIEW_H
#define BUTTONSELECTMACHINEFORREVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"

namespace Ui {
class ButtonSelectMachineForReview;
}

class ButtonSelectMachineForReview : public GUIFormBase
{
    Q_OBJECT
    
public:
	QString	Msg;
	QFont	CFont;
	int32		DefaultTopMachineID;
	int32		DefaultBottomMachineID;

    explicit ButtonSelectMachineForReview(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSelectMachineForReview();

	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSelectMachineForReview *ui;
};

#endif // BUTTONSELECTMACHINEFORREVIEW_H