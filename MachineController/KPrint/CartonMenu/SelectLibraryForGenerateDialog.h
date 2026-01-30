/*
 * Copyright (C) 2024
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

#ifndef SELECTLIBRARYFORGENERATEDIALOG_H
#define SELECTLIBRARYFORGENERATEDIALOG_H

#include <QDialog>
#include <QPushButton>
#include "XServiceForLayers.h"
namespace Ui {
class SelectLibraryForGenerateDialog;
}
class	CartonMenuForm;
class   SetThresholdLevelForm;

const   int    GenerationMaxCamDimCount =10;
const   int    GenerationMaxLibCount    =100;

class SelectLibraryForGenerateDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	CartonMenuForm	*Parent;
    QPushButton     *SelectionButton[GenerationMaxCamDimCount][GenerationMaxLibCount];
    SetThresholdLevelForm	*SForm;
public:
    explicit SelectLibraryForGenerateDialog(CartonMenuForm *p,QWidget *parent = 0);
    ~SelectLibraryForGenerateDialog();
    
private slots:
    void on_PushButtonStartGenerate_clicked();
    void on_PushButtonCancel_clicked();
    void    SlotChangeThresholdLevelID(int ThresholdLevelID);

private:
    Ui::SelectLibraryForGenerateDialog *ui;
};

#endif // SELECTLIBRARYFORGENERATEDIALOG_H