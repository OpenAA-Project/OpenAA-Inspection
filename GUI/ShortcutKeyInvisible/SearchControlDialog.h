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

#ifndef SEARCHCONTROLDIALOG_H
#define SEARCHCONTROLDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "NList.h"

namespace Ui {
class SearchControlDialog;
}
class	GUIItemInstance;


class	ChildControl : public NPList<ChildControl>
{
public:
	QWidget		*Control;
	QString		ClassName;
	QString		Path;

	ChildControl(QWidget *p,const QString &classname):Control(p),ClassName(classname){}
	void	SetPath(QWidget *Root);
};

class SearchControlDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	QString		DLLRoot;
	QString		DLLName;
	QString		DLLInst;
	QString		ObjPath;
	QString		ObjName;
	
	explicit SearchControlDialog(LayersBase *base,QWidget *parent = 0);
    ~SearchControlDialog();

private slots:
    void on_tableWidgetComponent_clicked(const QModelIndex &index);
    void on_tableWidgetControl_doubleClicked(const QModelIndex &index);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::SearchControlDialog *ui;

	class	GUIItemInstancePointerList : public NPList<GUIItemInstancePointerList>
	{
	public:
		GUIItemInstance	*Point;

		GUIItemInstancePointerList(GUIItemInstance *p):Point(p){}
	};

	NPListPack<GUIItemInstancePointerList>	ItemListContainer;

	NPListPack<ChildControl> ControlChildren;

	void ShowComponentList(void);
	void ShowControlList(void);
};

#endif // SEARCHCONTROLDIALOG_H