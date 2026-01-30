/*
 * Copyright (C) 2020
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

#ifndef EASYGENERATEALIGNMENTFORM_H
#define EASYGENERATEALIGNMENTFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include <QPushButton>
#include <QModelIndex>


namespace Ui {
class EasyGenerateAlignmentForm;
}

class EasyGenerateAlignmentForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit EasyGenerateAlignmentForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyGenerateAlignmentForm();
	virtual void	Prepare(void)		override;
signals:
	void	SignalBusy();
	void	SignalIdle();    
private slots:
    void on_toolButtonAutoGenerate_clicked();
	void	ResizeAction();
private:
    Ui::EasyGenerateAlignmentForm *ui;
};

#endif // EASYGENERATEALIGNMENTFORM_H