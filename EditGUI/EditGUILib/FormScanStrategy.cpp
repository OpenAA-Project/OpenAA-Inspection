/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\FormScanStrategy.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "FormScanStrategy.h"
#include "ui_FormScanStrategy.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include <swap.h>

void	StrategyGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    RootParent->LocalData.SetStrategyCode(row,col,value.toInt());
}
void	StrategyGrid::GetValue(int row ,int col,QVariant &value)
{
    value=QVariant(RootParent->LocalData.GetStrategyCode(row,col));
}


void	CalcStrategyGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    RootParent->LocalData.SetCalcStrategyCode(row,col,value.toInt());
}
void	CalcStrategyGrid::GetValue(int row ,int col,QVariant &value)
{
    value=QVariant(RootParent->LocalData.GetCalcStrategyCode(row,col));
}


void	AllocCameraGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    RootParent->LocalData.SetCameraNo(row,value.toInt());
}
void	AllocCameraGrid::GetValue(int row ,int col,QVariant &value)
{
    value=RootParent->LocalData.GetCameraNo(row);
}

FormScanStrategy::FormScanStrategy(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,dGrid(this),cGrid(this),aGrid(this)
    ,ui(new Ui::FormScanStrategy)
    ,LocalData(Base)
{
    ui->setupUi(this);
    LangSolverGUILib.SetUI(this);
    LocalData.CopyFrom(*GetLayersBase()->GetParamGlobal());

    LocalData.ReallocStrategy();
    dGrid.setParent(ui->frameStrategy);
    dGrid.move(0,0);
    dGrid.resize(ui->frameStrategy->width(),ui->frameStrategy->height());

    cGrid.setParent(ui->frameCalcStrategy);
    cGrid.move(0,0);
    cGrid.resize(ui->frameCalcStrategy->width(),ui->frameCalcStrategy->height());

    aGrid.setParent(ui->frameAllocCam);
    aGrid.setColumnWidth(0,50);
    aGrid.SetColumnCount(1);
    aGrid.move(0,0);
    aGrid.resize(ui->frameAllocCam->width(),ui->frameAllocCam->height());

    aGrid.SetTopHeader(0, LangSolverGUILib.GetString(FormScanStrategy_LS,LID_14)/*"Camera"*/);

    ShowToWindow();
}

FormScanStrategy::~FormScanStrategy()
{
    delete ui;
}

void FormScanStrategy::ShowToWindow(void)
{
    dGrid.SetRowCount(LocalData.PageNumb);
    dGrid.SetColumnCount(LocalData.LayerNumb);
    for(int r=0;r<LocalData.PageNumb;r++){
        for(int c=0;c<LocalData.LayerNumb;c++){
            WMultiGrid::CellData *L=dGrid.GetData(r ,c);
            L->Value	=QVariant(LocalData.GetStrategyCode(r,c));
            L->CType	=WMultiGrid::_CType_SpinBox;
            L->MaxValue	=max(LocalData.GetMaxScanStrategy()-1,0);
            L->MinValue	=-1;
            L->Alignment=Qt::AlignVCenter | Qt::AlignRight;
        }
    }

    dGrid.InitialGrid();
    for(int c=0;c<LocalData.LayerNumb;c++){
        dGrid.setColumnWidth(c,40);
        dGrid.SetTopHeader(c, LangSolverGUILib.GetString(FormScanStrategy_LS,LID_12)/*"Layer"*/+QString::number(c));
    }
    for(int r=0;r<LocalData.PageNumb;r++){
        dGrid.SetLeftHeader(r,LangSolverGUILib.GetString(FormScanStrategy_LS,LID_13)/*"Page "*/+QString::number(r));
    }

    cGrid.SetRowCount(LocalData.PageNumb);
    cGrid.SetColumnCount(LocalData.LayerNumb);
    for(int r=0;r<LocalData.PageNumb;r++){
        for(int c=0;c<LocalData.LayerNumb;c++){
            WMultiGrid::CellData *L=cGrid.GetData(r ,c);
            L->Value	=QVariant(LocalData.GetCalcStrategyCode(r,c));
            L->CType	=WMultiGrid::_CType_SpinBox;
            L->MaxValue	=max(LocalData.GetMaxScanStrategy()-1,0);
            L->MinValue	=-1;
            L->Alignment=Qt::AlignVCenter | Qt::AlignRight;
        }
    }

    cGrid.InitialGrid();
    for(int c=0;c<LocalData.LayerNumb;c++){
        cGrid.setColumnWidth(c,40);
        cGrid.SetTopHeader(c, LangSolverGUILib.GetString(FormScanStrategy_LS,LID_12)/*"Layer"*/+QString::number(c));
    }
    for(int r=0;r<LocalData.PageNumb;r++){
        cGrid.SetLeftHeader(r,LangSolverGUILib.GetString(FormScanStrategy_LS,LID_13)/*"Page "*/+QString::number(r));
    }

    ui->SpinBoxMaxStrategyNumb->setValue(LocalData.GetMaxScanStrategy());

    LocalData.ReallocCamAllocInPages();
    aGrid.SetRowCount(LocalData.PageNumb);
    for(int r=0;r<LocalData.PageNumb;r++){
        WMultiGrid::CellData *L=aGrid.GetData(r ,0);
        L->Value	=QVariant(LocalData.GetCameraNo(r));
        L->CType	=WMultiGrid::_CType_SpinBox;
        L->MaxValue	=max(LocalData.TotalCameraNumb-1,0);
        L->MinValue	=-1;
        L->Alignment=Qt::AlignVCenter | Qt::AlignRight;
    }

    aGrid.InitialGrid();

    for(int r=0;r<LocalData.PageNumb;r++){
        aGrid.SetLeftHeader(r,LangSolverGUILib.GetString(FormScanStrategy_LS,LID_15)/*"Page "*/+QString::number(r));
    }

    aGrid.ShowGrid();
    dGrid.ShowGrid();
}

void FormScanStrategy::LoadFromWindow(void)
{
    GetLayersBase()->GetParamGlobal()->CopyStrategyFrom(LocalData);
}

void FormScanStrategy::CopyFromOriginal(LayersBase *src)
{
    LocalData.CopyFrom(*src->GetParamGlobal());
}
void FormScanStrategy::on_OKButton_clicked()
{
    GetLayersBase()->GetParamGlobal()->CopyStrategyFrom(LocalData);
    close();
}

void FormScanStrategy::on_CancelButton_clicked()
{
    close();
}

void FormScanStrategy::on_SpinBoxMaxStrategyNumb_valueChanged(int arg1)
{
    LocalData.SetMaxScanStrategy(ui->SpinBoxMaxStrategyNumb->value());
    for(int r=0;r<LocalData.PageNumb;r++){
        for(int c=0;c<LocalData.LayerNumb;c++){
            WMultiGrid::CellData *L=dGrid.GetData(r ,c);
            L->MaxValue	=max(LocalData.GetMaxScanStrategy()-1,0);
        }
    }
}

void FormScanStrategy::closeEvent ( QCloseEvent * event )
{
    emit	SignalClose();
}

