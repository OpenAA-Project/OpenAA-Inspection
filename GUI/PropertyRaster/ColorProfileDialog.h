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

#ifndef COLORPROFILEDIALOG_H
#define COLORPROFILEDIALOG_H

#include <QDialog>
#include "XRaster.h"
#include "mtPushButtonColored.h"
#include "XServiceForLayers.h"

namespace Ui {
class ColorProfileDialog;
}

class	PropertyRasterForm;

class	ColorProfileColorButton : public mtPushButtonColored
{
    Q_OBJECT

    int Line;
public:
    ColorProfileColorButton(int Line);
private slots:
	void	SlotClicked();
signals:
	void	SignalClicked(int Line);
};

class ColorProfileDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    PropertyRasterForm  *Parent;

public:
    bool    Changed;

    explicit ColorProfileDialog(LayersBase *base
                                ,PropertyRasterForm *p
                                ,ColorProfileContainerWithTable &_ColorProfiles
                                ,QWidget *parent = nullptr);
    ~ColorProfileDialog();

    ColorProfileContainerWithTable		ColorProfiles;
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();

    void	SlotImageClicked(int Line);
    void	SlotRasterClicked(int Line);

    void on_pushButtonClear_clicked();
    void on_pushButtonAppend_clicked();
    void on_pushButtonSaveDefault_clicked();
    void on_pushButtonLoadDefault_clicked();

private:
    Ui::ColorProfileDialog *ui;

    void    ShowGrid(void);
};

#endif // COLORPROFILEDIALOG_H