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

#ifndef SHOWCHECKEVERYDAYFORM_H
#define SHOWCHECKEVERYDAYFORM_H

#include <QDialog>
#include "XCheckEveryday.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"

namespace Ui {
class ShowCheckEverydayForm;
}

class ShowCheckEverydayForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    bool    UpdateInEveryInspection;
    explicit ShowCheckEverydayForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowCheckEverydayForm();
    
	CheckEverydayBase	*GetCheckEverydayBase(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Prepare(void)	override;
	virtual void	ShowInPlayer		(int64 shownInspectionID=-1)    override;
private slots:
    void on_pushButtonUpdate_clicked();
	void	ResizeAction();
private:
    Ui::ShowCheckEverydayForm *ui;
};

#endif // SHOWCHECKEVERYDAYFORM_H