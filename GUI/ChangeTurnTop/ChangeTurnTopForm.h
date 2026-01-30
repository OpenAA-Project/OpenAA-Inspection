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

#ifndef CHANGETURNTOPFORM_H
#define CHANGETURNTOPFORM_H

#include "XGUIFormBase.h"
#include <QStringList>
#include <QLabel>

namespace Ui {
class ChangeTurnTopForm;
}

class ChangeTurnTopForm : public GUIFormBase
{
    Q_OBJECT

public:
	QStringList	RelatedPanels;

    explicit ChangeTurnTopForm(LayersBase *Base ,QWidget *parent = 0);
    ~ChangeTurnTopForm();

	virtual void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;
private slots:
    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::ChangeTurnTopForm *ui;
private slots:
	void	ResizeAction();
};

#endif // CHANGETURNTOPFORM_H