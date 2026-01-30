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


#ifndef SHOWCURRENTOPINIONFORM_H
#define SHOWCURRENTOPINIONFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowCurrentOpinionForm.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowCurrentOpinionForm : public GUIFormBase
{
	Q_OBJECT

public:
	ShowCurrentOpinionForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowCurrentOpinionForm();

	virtual void	Prepare(void)	override;
private:
	Ui::ShowCurrentOpinionFormClass ui;

private slots:
	void on_tableWidgetGUI_clicked(const QModelIndex &);
	void on_pushButtonUpdate_clicked();
    void on_listWidgetCommentOpinionList_clicked(const QModelIndex &index);
};

#endif // SHOWCURRENTOPINIONFORM_H