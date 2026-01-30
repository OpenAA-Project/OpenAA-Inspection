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


#ifndef MASTERCATEGORYINPUTFORM_H
#define MASTERCATEGORYINPUTFORM_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class MasterCategoryInputForm;
}

class MasterCategoryInputForm : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit MasterCategoryInputForm(LayersBase *lbase ,const QString &folderName ,const QString &remark ,QWidget *parent = 0);
    ~MasterCategoryInputForm();

    QString	FolderName;
    QString	Remark;

private slots:
    void on_ButtonOK_clicked();
    void on_ButtonCancel_clicked();

private:
    Ui::MasterCategoryInputForm *ui;
    virtual	void closeEvent ( QCloseEvent * event ) 	override;
};

#endif // MASTERCATEGORYINPUTFORM_H