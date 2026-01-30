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

#ifndef CREATETHRESHOLDLEVELDIALOG_H
#define CREATETHRESHOLDLEVELDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include <QDrag>
#include <QMimeData>
#include <QModelIndex>
#include <QTreeWidgetItem>

namespace Ui {
class CreateThresholdLevelDialog;
}

class LevelFolder;

class CreateThresholdLevelDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int SourceLevelID;
public:
    explicit CreateThresholdLevelDialog(LayersBase *Base ,QWidget *parent = 0);
    ~CreateThresholdLevelDialog();
    
private slots:
    void on_treeWidgetLevel_itemSelectionChanged();
    void on_pushButtonCreateNew_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonDelete_clicked();
    void on_pushButtonClose_clicked();
    void on_treeWidgetLevel_clicked(const QModelIndex &index);
    void on_pushButtonTopRoot_clicked();
    void on_pushButtonCopy_clicked();
    void on_pushButtonPaste_clicked();

private:
    Ui::CreateThresholdLevelDialog *ui;

    void    ShowTreeGrid(void);
    void    ShowTreeGrid(QTreeWidgetItem *Item,LevelFolder *Parent);
    void    ShowLevelItem(int LevelID);
    void    ShowCurrentParent(void);

    virtual void    dropEvent(QDropEvent *event)    override;
    virtual void resizeEvent(QResizeEvent *event)   override;
    QTreeWidgetItem *GetCurrentItem(void);
};

#endif // CREATETHRESHOLDLEVELDIALOG_H