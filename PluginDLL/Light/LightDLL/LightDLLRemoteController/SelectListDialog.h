/*
 * Copyright (C) 2014
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

#ifndef SELECTLISTDIALOG_H
#define SELECTLISTDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectListDialog;
}


class	LightList : public NPList<LightList>
{
public:
	int ID;
	QString Name;
	QString Remark;

	LightList(int id, const QString &name ,const QString &remark)
		:ID(id),Name(name),Remark(remark){}
};

class SelectListDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectListDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectListDialog();
    
	void	Initial(int LightID);
	void	ShowLightList(void);

	int	LightID;
	NPListPack<LightList>	LightListContainer;

private slots:
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

    void on_tableWidgetLight_clicked(const QModelIndex &index);

private:
    Ui::SelectListDialog *ui;
};

#endif // SELECTLISTDIALOG_H