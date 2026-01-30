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

#ifndef LISTCONDITIONFORM_H
#define LISTCONDITIONFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ListConditionForm;
}

class ListConditionForm : public GUIFormBase
{
    Q_OBJECT
    
	QStringList		FileNames;

public:
    explicit ListConditionForm(LayersBase *Base ,QWidget *parent = 0);
    ~ListConditionForm();
    
	virtual	void	Prepare(void)	override;

private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonSelect_clicked();
    void on_listWidgetConditions_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdate_clicked();

private:
    Ui::ListConditionForm *ui;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif // LISTCONDITIONFORM_H