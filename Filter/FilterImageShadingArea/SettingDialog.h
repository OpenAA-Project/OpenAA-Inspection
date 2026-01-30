/*
 * Copyright (C) 2018
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

#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SettingDialog;
}
class	FilterImageShadingArea;

class SettingDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	FilterImageShadingArea	*Parent;
public:
    explicit SettingDialog(LayersBase *base,FilterImageShadingArea *parent ,QWidget *p = 0);
    ~SettingDialog();

	void	Reflect(void);

	double	MagR;
	double	MagG;
	double	MagB;
	int		UsagePhaseNumber;
	int		UsagePageNumber;
	QStringList	FileList;

private slots:
    void on_pushButtonAddFiles_clicked();
    void on_pushButtonDelFiles_clicked();
    void on_pushButtonCalculate_clicked();
    void on_pushButtonClose_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::SettingDialog *ui;

	bool	AddPix(int UsePhaseNumber,int UsePageNumber,const QString &FileName,short ***MultiplePerDot ,int XLen ,int YLen);
};

#endif // SETTINGDIALOG_H