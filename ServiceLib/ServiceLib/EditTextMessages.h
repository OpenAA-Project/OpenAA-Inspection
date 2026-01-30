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

#ifndef EDITTEXTMESSAGES_H
#define EDITTEXTMESSAGES_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XServiceForLayers.h"

namespace Ui {
class EditTextMessages;
}

class EditTextMessages : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditTextMessages(LayersBase *base,TextMessageContainer &TextMessageContainerData,QWidget *parent = 0);
    ~EditTextMessages();

    TextMessageContainer	TextMessageContainerData;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();

private:
    Ui::EditTextMessages *ui;

    void	GetDataFromWindow(void);
    void	SetDataToWindow(void);

    virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // EDITTEXTMESSAGES_H