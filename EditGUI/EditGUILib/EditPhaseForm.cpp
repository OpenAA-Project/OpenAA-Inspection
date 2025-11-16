#include "EditGUILibResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\EditPhaseForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "XTypeDef.h"

#include "EditPhaseForm.h"
#include "ui_EditPhaseForm.h"

#include "XGeneralDialog.h"
#include "Regulus64Version.h"
#include "XDataInLayer.h"
#include "XFilterManager.h"
#include "FilterInPhaseForm.h"
#include "XFilterInstance.h"

void	PhaseGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    //if(col==1){
    //	PageDataInOnePhase	*P=EParent->GetLayersBase()->GetPageDataPhase(row);
    //	P->SetFromSourcePhase(value.toInt());
    //}
}
void	PhaseGrid::GetValue(int row ,int col,QVariant &value)
{
    //if(col==1){
    //	PageDataInOnePhase	*P=EParent->GetLayersBase()->GetPageDataPhase(row);
    //	value.setValue(P->GetFromSourcePhase());
    //}
}

EditPhaseForm::EditPhaseForm(LayersBase *base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
	,aGrid(this)
    ,ui(new Ui::EditPhaseForm)
{
    ui->setupUi(this);
    OldPhaseIndex=0;

    aGrid.setParent(ui->frame);
    aGrid.SetColumnCount(3);
    connect(&aGrid,SIGNAL(SignalClickedXYButton(int,int)),this,SLOT(SlotClickedXYButton(int,int)));
    connect(ui->pushButtonCopy,SIGNAL(clicked()),this,SLOT(on_pushButtonCopy_clicked()));
    connect(ui->pushButtonPaste,SIGNAL(clicked()),this,SLOT(on_pushButtonPaste_clicked()));
    ui->pushButtonPaste->setEnabled(false);

    SetGrid();
}

EditPhaseForm::~EditPhaseForm()
{
    delete ui;
}

void	EditPhaseForm::SetGrid(void)
{
    aGrid.InitialGrid();
    aGrid.SetRowCount(GetLayersBase()->GetPageNumb());
    aGrid.move(0,0);
    aGrid.resize(ui->frame->width(),ui->frame->height());
    for(int r=0;r<GetLayersBase()->GetPageNumb();r++){
        WMultiGrid::CellData *L0=aGrid.GetData(r ,0);
        PageDataInOnePhase	*P=GetLayersBase()->GetPageDataPhase(OldPhaseIndex);
        FilterInstanceContainer	*F=P->GetFilterContainer(r);
        L0->Value	=QString(/**/"Count :")+QString::number(F->GetCount());
        L0->CType	=WMultiGrid::_CType_PushButton;
        L0->Alignment=Qt::AlignVCenter | Qt::AlignCenter;

//		WMultiGrid::CellData *L1=aGrid.GetData(r ,1);
//		L1->CType	=WMultiGrid::_CType_SpinBox;
//		L1->Alignment=Qt::AlignVCenter | Qt::AlignCenter;
//		L1->Value	=P->GetFromSourcePhase();
    }

    aGrid.SetTopHeader(0, QString(/**/"Filter"));
    aGrid.SetTopHeader(1, QString(/**/"Source"));
    aGrid.SetTopHeader(2, QString(/**/""));

    for(int r=0;r<GetLayersBase()->GetPhaseNumb();r++){
        aGrid.SetLeftHeader(r,QString::number(r+1));
    }

    aGrid.ShowGrid();

    aGrid.setColumnWidth(0,70);
    aGrid.setColumnWidth(1,60);
    aGrid.setColumnWidth(2,60);

    ui->comboBoxPhase->clear();
    for(int phase=0;phase<GetPhaseNumb();phase++){
        ui->comboBoxPhase->addItem(QString(/**/"Phase ")+QString::number(phase));
    }
}

void EditPhaseForm::closeEvent ( QCloseEvent * event )
{
    emit	SignalClose();
}

void	EditPhaseForm::SlotClickedXYButton( int row ,int col)
{
    if(col==0){
        int	PhaseNo=ui->comboBoxPhase->currentIndex();
        FilterInPhaseForm	D(GetLayersBase(),PhaseNo,row,this);
        D.exec();
    }
}

void EditPhaseForm::on_comboBoxPhase_currentIndexChanged(int index)
{
    aGrid.ShowGrid();

    PageDataInOnePhase	*P=GetLayersBase()->GetPageDataPhase(OldPhaseIndex);
    P->SetFromSourcePhase(ui->spinBoxSource->value());

    int	PhaseNo=ui->comboBoxPhase->currentIndex();
    if(PhaseNo>=0){
        P=GetLayersBase()->GetPageDataPhase(PhaseNo);
        ui->spinBoxSource->setValue(P->GetFromSourcePhase());
        OldPhaseIndex=PhaseNo;
    }
}

void EditPhaseForm::on_pushButtonCopy_clicked()
{
    int	Row=aGrid.currentIndex().row();
    if(Row<0)
        return;
    int	PhaseNo=ui->comboBoxPhase->currentIndex();
    if(PhaseNo>=0){
        FilterInstanceContainer	*f=GetLayersBase()->GetPageDataPhase(PhaseNo)->GetFilterContainer(Row);
        QBuffer	Buff;
        Buff.open(QIODevice::WriteOnly);
        f->Save(&Buff);
        CopiedBuff=Buff.buffer();
        ui->pushButtonPaste->setEnabled(true);
    }
}

void EditPhaseForm::on_pushButtonPaste_clicked()
{
    int	Row=aGrid.currentIndex().row();
    if(Row<0)
        return;
    int	PhaseNo=ui->comboBoxPhase->currentIndex();
    if(PhaseNo>=0){
        FilterInstanceContainer	*f=GetLayersBase()->GetPageDataPhase(PhaseNo)->GetFilterContainer(Row);
        QBuffer	Buff(&CopiedBuff);
        Buff.open(QIODevice::ReadOnly);
        f->Load(&Buff);
    }
}

void EditPhaseForm::on_pushButtonOK_clicked()
{
    close();
}

void EditPhaseForm::on_pushButtonSaveFilter_clicked()
{
    GetLayersBase()->SaveFilterDef();
}
