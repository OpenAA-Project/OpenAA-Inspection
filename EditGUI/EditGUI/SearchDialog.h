/*
 * Copyright (C) 2017
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

#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "NList.h"
#include "XGUI.h"
#include "XServiceForLayers.h"

namespace Ui {
class SearchDialog;
}

class	GUINameClassifiedPointer : public NPList<GUINameClassifiedPointer>
{
public:
	GUINameClassified	*GUIItemPointer;

	GUINameClassifiedPointer(GUINameClassified *v):GUIItemPointer(v){}
};



class SearchDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

	NPListPack<GUINameClassifiedPointer>	PointerList;
public:
    explicit SearchDialog(LayersBase *base ,QWidget *parent = 0);
    ~SearchDialog();

private slots:
    void on_listWidgetRootList_clicked(const QModelIndex &index);
    void on_pushButtonSearcg_clicked();
    void on_tableWidgetComponents_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SearchDialog *ui;

	void ShowGUIItemGrid(void);
};

#endif // SEARCHDIALOG_H