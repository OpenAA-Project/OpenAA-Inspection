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

#ifndef SELECTTHRESHOLDPARENTLEVELDIALOG_H
#define SELECTTHRESHOLDPARENTLEVELDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class SelectThresholdParentLevelDialog;
}

class LevelFolder;

class SelectThresholdParentLevelDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectThresholdParentLevelDialog(LayersBase *Base, QWidget *parent = 0);
    ~SelectThresholdParentLevelDialog();
    
    int SelectedLevelID;
private slots:
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();
    void on_treeWidgetLevel_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_treeWidgetLevel_clicked(const QModelIndex &index);
    void on_pushButtonTopRoot_clicked();

private:
    Ui::SelectThresholdParentLevelDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    QTreeWidgetItem *GetCurrentItem(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTTHRESHOLDPARENTLEVELDIALOG_H