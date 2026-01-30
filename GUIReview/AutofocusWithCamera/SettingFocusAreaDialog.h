/*
 * Copyright (C) 2016
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

#ifndef SETTINGFOCUSAREADIALOG_H
#define SETTINGFOCUSAREADIALOG_H

#include <QDialog>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "mtGraphicUnit.h"

namespace Ui {
class SettingFocusAreaDialog;
}

class	AutofocusWithCameraForm;

class SettingFocusAreaDialog : public QDialog
{
    Q_OBJECT

	AutofocusWithCameraForm	*Parent;
	mtGraphicUnit	ImagePanel;
	QImage			SampleImage;
public:
    explicit SettingFocusAreaDialog(AutofocusWithCameraForm *p, QWidget *parent = 0);
    ~SettingFocusAreaDialog();

	void	Initial(QImage &Image ,int x1, int y1 ,int x2, int y2);

	int32		FocusAreaX1;
	int32		FocusAreaY1;
	int32		FocusAreaX2;
	int32		FocusAreaY2;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
	void	SlotOnPaint(QPainter &pnt);
	void	SlotDrawEnd(void);
    void on_pushButtonSetDarkLightSetting_clicked();

private:
    Ui::SettingFocusAreaDialog *ui;
};

#endif // SETTINGFOCUSAREADIALOG_H