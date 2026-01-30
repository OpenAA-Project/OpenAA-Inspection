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

#ifndef EDITSTATUSDIALOG_H
#define EDITSTATUSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class EditStatusDialog;
}

class EditStatusDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT
    
    QWidget *Control;
public:
	QString	GUIRoot;
	QString	GUIName;
	QString	GUIInst;
	QStringList	ObjectPath;
	bool	HTMLMode;
    bool	HTMLModeToopTip;

	explicit EditStatusDialog(LayersBase *base ,QWidget *Ctrl,QWidget *parent = 0);
    ~EditStatusDialog();
    
private slots:
    void on_pushButtonUpdate_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonLoadHTML_clicked();
    void on_pushButtonClear_clicked();
    void on_pushButtonLoadToolTipHTML_clicked();
    void on_pushButtonToolTipClear_clicked();
    void on_checkBoxEnableToolTip_clicked();

private:
    Ui::EditStatusDialog *ui;

	virtual	void	showEvent ( QShowEvent * event )		override;
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // EDITSTATUSDIALOG_H