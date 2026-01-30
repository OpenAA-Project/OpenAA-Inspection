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

#ifndef SELECTSHADOWTREEDIALOG_H
#define SELECTSHADOWTREEDIALOG_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XServiceForLayers.h"

namespace Ui {
class SelectShadowTreeDialog;
}
class	ShadowTree;
class	LayersBase;

class SelectShadowTreeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectShadowTreeDialog(LayersBase *pbase ,QWidget *parent = nullptr);
    ~SelectShadowTreeDialog();

    void    Initial(int ShadowLevel,int ShadowNumber);

    ShadowTree  *ShadowTreePoint;
private slots:
    void on_treeWidgetShadowTree_itemSelectionChanged();
    void on_treeWidgetShadowTree_itemDoubleClicked(QTreeWidgetItem *item, int column);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectShadowTreeDialog *ui;

    void    ShowTree(void);
    void    AddShowTree(QTreeWidgetItem *ParentW,LayersBase *ParentBase);
    virtual void resizeEvent(QResizeEvent *)    override;
};

#endif // SELECTSHADOWTREEDIALOG_H