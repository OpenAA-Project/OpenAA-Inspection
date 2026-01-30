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

#ifndef EVDLLLISTFORM_H
#define EVDLLLISTFORM_H

#include <QWidget>
#include "XExecuteVisualizer.h"
#include "XExecuteVisualizerForLib.h"
#include "WMultiGrid.h"

namespace Ui {
    class EVDLLListForm;
}

class	EVDLLList : public NPList<EVDLLList>
{
public:
	RunnerObjDLL	*Item;

	EVDLLList(RunnerObjDLL *item):Item(item){}
};

class	EVCategoryList : public NPList<EVCategoryList> , public NPListPack<EVDLLList>
{
public:
	QString	DLLRoot;

	EVCategoryList(const QString &_DLLRoot):DLLRoot(_DLLRoot){}
};

class	CategoryListGrid : public WMultiGrid
{
public:
	EVCategoryList *Category;

	CategoryListGrid(EVCategoryList *category,QWidget * parent=0);

	virtual	void	ChangeValue(int row ,int col,const QVariant &value)	override;
	virtual	void	GetValue(int row ,int col,QVariant &value)			override;

private:
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

class EVDLLListForm : public QWidget
{
    Q_OBJECT

	RunnerMap	&RMap;
	NPListPack<EVCategoryList>	CategoryContainer;

public:
    explicit EVDLLListForm(RunnerMap &_RMap,QWidget *parent = 0);
    ~EVDLLListForm();

	RunnerObjDLL	*GetCurrentDLL(void);
private:
	void	BuildCategoryData(void);
	void	MakeTabList(void);
	virtual	void	resizeEvent ( QResizeEvent * event )	override;
private:
    Ui::EVDLLListForm *ui;
};

#endif // EVDLLLISTFORM_H