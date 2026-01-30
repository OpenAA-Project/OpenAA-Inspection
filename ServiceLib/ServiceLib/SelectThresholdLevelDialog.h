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

#ifndef SELECTTHRESHOLDLEVELDIALOG_H
#define SELECTTHRESHOLDLEVELDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class SelectThresholdLevelDialog;
}
class LevelFolder;

class SelectThresholdLevelDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectThresholdLevelDialog(LayersBase *Base, QWidget *parent = 0);
    ~SelectThresholdLevelDialog();
    int SelectedLevelID;

private slots:
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_treeWidgetLevel_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SelectThresholdLevelDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    void    ShowCurrentParent(void);
    void    ShowLevelItem(int LevelID);
    QTreeWidgetItem *GetCurrentItem(void);

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTTHRESHOLDLEVELDIALOG_H