/*
 * Copyright (C) 2026
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

#ifndef ADDBCODEINSPECTIONDIALOG_H
#define ADDBCODEINSPECTIONDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QCheckBox>
#include "XServiceForLayers.h"
#include "XBCRInspection.h"
#include "XGeneralFunc.h"

namespace Ui {
class AddBCodeInspectionDialog;
}

class AddBCodeInspectionDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit AddBCodeInspectionDialog(LayersBase *Base,QWidget *parent = 0);
    ~AddBCodeInspectionDialog();
    
	int		                CheckType;		    //0:Read	1:Quality Check
	double	                QuilityGrade;
	BCRGradeListContainer	GradeList;
    bool					BarcodeIsOnlyDigit;

    void	GetDataFromWindow(void);
    void	SetDataToWindow(void);


private slots:
    void on_comboBoxCheckType_currentIndexChanged(int index);
    void on_pushButtonLoad_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonAdd_clicked();
    void on_pushButtonSub_clicked();
    void on_pushButtonSet_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::AddBCodeInspectionDialog *ui;

    void    ShowGradeList(BCRGradeListContainer &List);
    void    LoadGradeListFromWindow(BCRGradeListContainer &List);

};

#endif // ADDBCODEINSPECTIONDIALOG_H