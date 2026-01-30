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

#ifndef FORMDIRECTIONONEACHPAGE_H
#define FORMDIRECTIONONEACHPAGE_H

#include <QWidget>
#include "WMultiGrid.h"
#include"XParamGlobal.h"
#include "XServiceForLayers.h"

namespace Ui {
class FormDirectionOnEachPage;
}

class	FormDirectionOnEachPage;

class	DirectionGrid : public WMultiGrid
{
    FormDirectionOnEachPage	*RootParent;
public:

    DirectionGrid(FormDirectionOnEachPage *root,QWidget * parent=0):WMultiGrid(parent),RootParent(root){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};

class FormDirectionOnEachPage : public QWidget,public ServiceForLayers
{
    friend	class	DirectionGrid;
    Q_OBJECT
    
public:
    explicit FormDirectionOnEachPage(LayersBase *Base ,QWidget *parent = 0);
    ~FormDirectionOnEachPage();

    DirectionGrid	dGrid;
    void LoadFromWindow(void);
    void	ShowGrid(void);
    void	CopyFromOriginal(LayersBase *src);

signals:
    void	SignalClose();
private slots:
    void on_OKButton_clicked();
    void on_CancelButton_clicked();

private:
    Ui::FormDirectionOnEachPage *ui;

    ParamGlobal	LocalData;
    
    virtual	void closeEvent (QCloseEvent * event)	override;
};

#endif // FORMDIRECTIONONEACHPAGE_H