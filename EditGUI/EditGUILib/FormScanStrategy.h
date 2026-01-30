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

#ifndef FORMSCANSTRATEGY_H
#define FORMSCANSTRATEGY_H

#include <QWidget>
#include "WMultiGrid.h"
#include"XParamGlobal.h"
#include "XServiceForLayers.h"

namespace Ui {
class FormScanStrategy;
}

class	FormScanStrategy;
class	StrategyGrid : public WMultiGrid
{
    FormScanStrategy	*RootParent;
public:

    StrategyGrid(FormScanStrategy *root,QWidget * parent=0):WMultiGrid(parent),RootParent(root){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};

class	CalcStrategyGrid : public WMultiGrid
{
    FormScanStrategy	*RootParent;
public:

    CalcStrategyGrid(FormScanStrategy *root,QWidget * parent=0):WMultiGrid(parent),RootParent(root){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};
class	AllocCameraGrid : public WMultiGrid
{
    FormScanStrategy	*RootParent;
public:

    AllocCameraGrid(FormScanStrategy *root ,QWidget * parent=0):WMultiGrid(parent),RootParent(root){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};

class FormScanStrategy : public QWidget,public ServiceForLayers
{
    friend	class	StrategyGrid;
    friend	class	CalcStrategyGrid;
    friend	class	AllocCameraGrid;
    Q_OBJECT
    
public:
    explicit FormScanStrategy(LayersBase *Base ,QWidget *parent = 0);
    ~FormScanStrategy();

    StrategyGrid		dGrid;
    CalcStrategyGrid	cGrid;
    AllocCameraGrid	aGrid;
    void LoadFromWindow(void);
    void ShowToWindow(void);
    void CopyFromOriginal(LayersBase *src);

signals:
    void	SignalClose();
private slots:
    void on_OKButton_clicked();
    void on_CancelButton_clicked();
    void on_SpinBoxMaxStrategyNumb_valueChanged(int arg1);

private:
    Ui::FormScanStrategy *ui;
    ParamGlobal	LocalData;
    virtual	void closeEvent (QCloseEvent * event)	override;
};

#endif // FORMSCANSTRATEGY_H