/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\FormCommSetting.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "FormCommSetting.h"
#include "ui_FormCommSetting.h"
#include "XDataInLayer.h"
#include <swap.h>
#include "FormCommErrorListDialog.h"

void	ConnectionGrid::selectRowX(int row)
{
    RootParent->ShowLocalCameraGrid();
}

void	ConnectionGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    if(col==0){
        RootParent->LocalData.GetConnection(row)->PartnerID=value.toInt();
    }
    else if(col==1){
        RootParent->LocalData.GetConnection(row)->IPAddress=value.toString();
    }
    else if(col==2){
        RootParent->LocalData.GetConnection(row)->CameraNumb=value.toInt();
        RootParent->LocalData.GetConnection(row)->ReallocGlobalCameraNo();
        emit	ChangedData();
        //RootParent->ShowLocalCameraGrid();
    }
}

void	ConnectionGrid::GetValue(int row ,int col,QVariant &value)
{
    if(col==0){
        value=QVariant(RootParent->LocalData.GetConnection(row)->PartnerID);
    }
    else if(col==1){
        value=QVariant(RootParent->LocalData.GetConnection(row)->IPAddress);
    }
    else if(col==2){
        value=QVariant(RootParent->LocalData.GetConnection(row)->CameraNumb);
    }
}
void	GlobalCameraNoGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    int	r=RootParent->GetConnectionIndex();
    if(r>=0){
        RootParent->LocalData.GetConnection(r)->SetGlobalCameraNo(row ,value.toInt());
    }
}
void	GlobalCameraNoGrid::GetValue(int row ,int col,QVariant &value)
{
    int	r=RootParent->GetConnectionIndex();
    if(r>=0){
        value=RootParent->LocalData.GetConnection(r)->GetGlobalCameraNo(row);
    }
    else{
        value=0;
    }
}

FormCommSetting::FormCommSetting(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::FormCommSetting)
    ,TmpLocalData(Base),LocalData(TmpLocalData),dGrid(this),aGrid(this),BeforeInitialized(false)
{
    ui->setupUi(this);
    LangSolverGUILib.SetUI(this);

    connect(&dGrid,SIGNAL(activated (const QModelIndex &))	,this,SLOT(on_ConnectionSelected(const QModelIndex &)));
    connect(&dGrid,SIGNAL(ChangedData()),this,SLOT(ChangedData()),Qt::QueuedConnection);

    aGrid.setParent(ui->frameCameraMap);

    Show();

    BeforeInitialized=true;
}

FormCommSetting::FormCommSetting(LayersBase *Base ,ParamComm *RefData ,QWidget *parent)
    : QWidget(parent)
    ,ServiceForLayers(Base)
    ,ui(new Ui::FormCommSetting)
    ,TmpLocalData(Base)
    ,LocalData(*RefData)
    ,dGrid(this),aGrid(this)
{
    ui->setupUi(this);
    LangSolverGUILib.SetUI(this);
    BeforeInitialized=false;

    connect(&dGrid,SIGNAL(activated (const QModelIndex &))	,this,SLOT(on_ConnectionSelected(const QModelIndex &)));
    connect(&dGrid,SIGNAL(ChangedData()),this,SLOT(ChangedData()),Qt::QueuedConnection);

    aGrid.setParent(ui->frameCameraMap);

    Show();

    BeforeInitialized=true;
}

FormCommSetting::~FormCommSetting()
{
    delete ui;
}

void	FormCommSetting::Show(void)
{
    LocalData.CopyFrom(*GetLayersBase()->GetParamComm());
    LocalData.ReallocConnection();
    dGrid.setParent(ui->frameAccessInfo);

    ui->CheckBoxMastered		->setChecked(LocalData.Mastered		);
    ui->SpinBoxMaxSlaveNumb	->setValue(LocalData.ConnectedPCNumb);
    ui->SpinBoxSlaveID		->setValue(LocalData.ThisComputerID	);

    aGrid.SetColumnCount(1);

    on_CheckBoxMastered_stateChanged(0);
    if(LocalData.ConnectedPCNumb!=0){
        dGrid.selectRow(0);
        SetGrid();
    }
}

void	FormCommSetting::SetGrid(void)
{
    if(ui->CheckBoxMastered->isChecked()==true){
        dGrid.SetColumnCount(3);
    }
    else{
        dGrid.SetColumnCount(2);
        if(LocalData.GetConnection(0)!=NULL){
            ui->SpinBoxThisCamCount->setValue(LocalData.GetConnection(0)->CameraNumb);
        }
    }
    dGrid.SetRowCount(LocalData.ConnectedPCNumb);
    dGrid.move(0,0);
    dGrid.resize(ui->frameAccessInfo->width(),ui->frameAccessInfo->height());
    for(int r=0;r<LocalData.ConnectedPCNumb;r++){
        WMultiGrid::CellData *L=dGrid.GetData(r ,0);
        L->Value	=QVariant(LocalData.GetConnection(r)->PartnerID);
        L->CType	=WMultiGrid::_CType_SpinBox;
        L->MaxValue	=9999;
        L->MinValue	=0;
        L->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        WMultiGrid::CellData *M=dGrid.GetData(r ,1);
        M->Value	=QVariant(LocalData.GetConnection(r)->IPAddress);
        M->CType	=WMultiGrid::_CType_LineEdit;
        M->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        if(ui->CheckBoxMastered->isChecked()==true){
            WMultiGrid::CellData *C=dGrid.GetData(r ,2);
            C->Value	=QVariant(LocalData.GetConnection(r)->CameraNumb);
            C->CType	=WMultiGrid::_CType_SpinBox;
            C->MaxValue	=9999;
            C->MinValue	=0;
            M->Alignment=Qt::AlignVCenter | Qt::AlignRight;
        }
    }

    dGrid.InitialGrid();
    dGrid.setColumnWidth(0,60);
    dGrid.SetTopHeader(0, LangSolverGUILib.GetString(FormCommSetting_LS,LID_5)/*"PartnerID"*/);
    dGrid.setColumnWidth(1,88);
    dGrid.SetTopHeader(1, LangSolverGUILib.GetString(FormCommSetting_LS,LID_6)/*"IPAddress"*/);
    if(ui->CheckBoxMastered->isChecked()==true){
        dGrid.setColumnWidth(2,40);
        dGrid.SetTopHeader(2, LangSolverGUILib.GetString(FormCommSetting_LS,LID_7)/*"CameraCount"*/);
    }

    for(int r=0;r<LocalData.ConnectedPCNumb;r++){
        dGrid.SetLeftHeader(r,LangSolverGUILib.GetString(FormCommSetting_LS,LID_8)/*"PC "*/+QString::number(r));
    }

    ShowLocalCameraGrid();
}

void	FormCommSetting::ShowLocalCameraGrid(void)
{
    int	PCIndex=GetConnectionIndex();
    if(PCIndex<0)
        return;

    ConnectionInfo	*q=LocalData.GetConnection(PCIndex);
    ui->labelForPC->setText(LangSolverGUILib.GetString(FormCommSetting_LS,LID_9)/*"Camera map in PC"*/+QString::number(PCIndex));
    aGrid.move(0,0);
    aGrid.resize(ui->frameCameraMap->width(),ui->frameCameraMap->height());
    if(q!=NULL){
        aGrid.SetRowCount(q->CameraNumb);
        for(int r=0;r<q->CameraNumb;r++){
            WMultiGrid::CellData *L=aGrid.GetData(r ,0);
            L->Value	=QVariant(q->GetGlobalCameraNo(r));
            L->CType	=WMultiGrid::_CType_SpinBox;
            L->MaxValue	=99999999;	//max(GetLayersBase()->GetParamGlobal()->TotalCameraNumb-1,0);
            L->MinValue	=0;
            L->Alignment=Qt::AlignVCenter | Qt::AlignRight;
        }
    }
    else{
        aGrid.SetRowCount(0);
    }

    aGrid.InitialGrid();
    aGrid.setColumnWidth(0,88);
    aGrid.SetTopHeader(0, LangSolverGUILib.GetString(FormCommSetting_LS,LID_10)/*"Global Camera"*/);

    if(q!=NULL){
        for(int r=0;r<q->CameraNumb;r++){
            aGrid.SetLeftHeader(r,LangSolverGUILib.GetString(FormCommSetting_LS,LID_11)/*"Cam "*/+QString::number(r));
        }
    }
}

void FormCommSetting::on_SpinBoxThisCamCount_valueChanged(int n)
{
    if(LocalData.GetConnection(0)!=NULL){
        LocalData.GetConnection(0)->CameraNumb=n;
    }
    ShowLocalCameraGrid();
}

void FormCommSetting::on_CheckBoxMastered_stateChanged(int arg1)
{
    static	bool	ReEntrant=false;

    if(ReEntrant==true){
        return;
    }
    ReEntrant=true;
    if(ui->CheckBoxMastered->isChecked()==true){
        ui->frameForSlave->setVisible(false);
    }
    else{
        ui->frameForSlave->setVisible(true);
    }
    SetGrid();
    ReEntrant=false;
}

void FormCommSetting::on_OKButton_clicked()
{
    LoadFromWindow();
    close();
}

void FormCommSetting::on_CancelButton_clicked()
{
    close();
}

void FormCommSetting::on_SpinBoxMaxSlaveNumb_valueChanged(int arg1)
{
    if(BeforeInitialized==true){
        LocalData.ConnectedPCNumb=ui->SpinBoxMaxSlaveNumb	->value();
        LocalData.ReallocConnection();
        SetGrid();
    }
}

void FormCommSetting::LoadFromWindow(void)
{
    LocalData.Mastered		=ui->CheckBoxMastered	->isChecked();
    LocalData.ThisComputerID=ui->SpinBoxSlaveID		->value();
    GetLayersBase()->GetParamComm()->CopyFrom(LocalData);
}

void FormCommSetting::closeEvent ( QCloseEvent * event )
{
    emit	SignalClose();
}

void	FormCommSetting::ChangedData()
{
    ShowLocalCameraGrid();
}

int		FormCommSetting::GetConnectionIndex()
{
	return(dGrid.GetSelectedRow());
}

void FormCommSetting::on_pushButtonShowCommError_clicked()
{
    FormCommErrorListDialog D(GetLayersBase());
    D.exec();
}

