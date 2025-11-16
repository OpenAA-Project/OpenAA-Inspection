/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditGUI\EditGUILib\EditOutlineOffset.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "EditOutlineOffset.h"
#include "ui_EditOutlineOffset.h"
#include "XDataInExe.h"
#include "XGeneralDialog.h"
#include "EditOutlineOffsetAddDialog.h"


void	OutlineOffsetGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    DataInPage *PData=EParent->GetLayersBase()->GetPageData(row);
    if(PData!=NULL){
        if(col==1){
            if(PData->GetOutlineOffsetLoaded()->x!=value.toInt()){
                PData->GetOutlineOffsetLoaded()->x=value.toInt();
                EParent->ChangeValue();
            }
        }
        else if(col==3){
            if(PData->GetOutlineOffsetLoaded()->y!=value.toInt()){
                PData->GetOutlineOffsetLoaded()->y=value.toInt();
                EParent->ChangeValue();
            }
        }
    }
}

void	OutlineOffsetGrid::GetValue(int row ,int col,QVariant &value)
{
    DataInPage *PData=EParent->GetLayersBase()->GetPageData(row);
    if(PData!=NULL){
        if(col==0){
            value=QVariant(LangSolverGUILib.GetString(EditOutlineOffset_LS,LID_0)/*"Cam "*/+QString::number(row+1));
        }
        if(col==1){
            value=(int)PData->GetOutlineOffsetLoaded()->x;
        }
        else if(col==3){
            value=(int)PData->GetOutlineOffsetLoaded()->y;
        }
    }
}

EditOutlineOffset::EditOutlineOffset(LayersBase *Base ,int _ParentWindowHeight ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,aGrid(this)
    ,ui(new Ui::EditOutlineOffset)
{
    ui->setupUi(this);
    LangSolverGUILib.SetUI(this);

    ParentWindowHeight=_ParentWindowHeight;
    aGrid.setParent(ui->frameGrid);
    aGrid.SetColumnCount(5);
    connect(&aGrid,SIGNAL(ChangedValue()),this,SLOT(ChangeValue()));
    connect(&aGrid,SIGNAL(SignalClickedXYButton( int ,int )),this,SLOT(SlotClickedXYButton( int ,int )));
    SetGrid();
}

EditOutlineOffset::~EditOutlineOffset()
{
    delete ui;
}

void	EditOutlineOffset::SetGrid(void)
{
    aGrid.InitialGrid();
    aGrid.SetRowCount(GetLayersBase()->GetPageNumb());
    aGrid.move(0,0);
    aGrid.resize(ui->frameGrid->width(),ui->frameGrid->height());
    for(int r=0;r<GetLayersBase()->GetPageNumb();r++){
        WMultiGrid::CellData *L0=aGrid.GetData(r ,0);
        L0->Value	=QVariant(LangSolverGUILib.GetString(EditOutlineOffset_LS,LID_1)/*"Cam "*/+QString::number(r+1));
        L0->CType	=WMultiGrid::_CType_Label;
        L0->MaxValue	=9999;
        L0->MinValue	=0;
        L0->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        DataInPage *PData=GetLayersBase()->GetPageData(r);
        WMultiGrid::CellData *L1=aGrid.GetData(r ,1);
        L1->Value	=(int)PData->GetOutlineOffsetLoaded()->x;
        L1->CType	=WMultiGrid::_CType_SpinBox;
        L1->MaxValue	=9999999;
        L1->MinValue	=-9999999;
        L1->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        WMultiGrid::CellData *LB1=aGrid.GetData(r ,2);
        LB1->Value	=QString(/**/"+");
        LB1->CType	=WMultiGrid::_CType_PushButton;
        LB1->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        WMultiGrid::CellData *L2=aGrid.GetData(r ,3);
        L2->Value	=(int)PData->GetOutlineOffsetLoaded()->y;
        L2->CType	=WMultiGrid::_CType_SpinBox;
        L2->MaxValue	=9999999;
        L2->MinValue	=-9999999;
        L2->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        WMultiGrid::CellData *LB2=aGrid.GetData(r ,4);
        LB2->Value	=QString(/**/"+");
        LB2->CType	=WMultiGrid::_CType_PushButton;
        LB2->Alignment=Qt::AlignVCenter | Qt::AlignRight;

    }

    aGrid.SetTopHeader(0, LangSolverGUILib.GetString(EditOutlineOffset_LS,LID_2)/*"Camera"*/);
    aGrid.SetTopHeader(1, LangSolverGUILib.GetString(EditOutlineOffset_LS,LID_3)/*"X Pos"*/);
    aGrid.SetTopHeader(2, /**/"");
    aGrid.SetTopHeader(3, LangSolverGUILib.GetString(EditOutlineOffset_LS,LID_4)/*"Y Pos"*/);
    aGrid.SetTopHeader(4, /**/"");

    for(int r=0;r<GetLayersBase()->GetPageNumb();r++){
        aGrid.SetLeftHeader(r,QString::number(r+1));
    }

    aGrid.ShowGrid();

    aGrid.setColumnWidth(0,70);
    aGrid.setColumnWidth(1,60);
    aGrid.setColumnWidth(2,32);
    aGrid.setColumnWidth(3,60);
    aGrid.setColumnWidth(4,32);

    int	H=aGrid.rowHeight(0)+aGrid.lineWidth();
    int	gH=H*(GetLayersBase()->GetPageNumb()+1)+4+aGrid.lineWidth();
    int	WindowHeight=gH+ui->frameGrid->geometry().top()+8+ui->frame->height();
    if(ParentWindowHeight>0 && ParentWindowHeight<WindowHeight){
        WindowHeight=ParentWindowHeight;
    }
    resize(width(),WindowHeight);
    ui->frameGrid->resize(ui->frameGrid->width(),WindowHeight-ui->frame->height() - ui->frameGrid->geometry().top());
    aGrid.resize(aGrid.width(),WindowHeight-ui->frame->height() - ui->frameGrid->geometry().top());
    ui->frame->move(0,height()-ui->frame->height());
}

void EditOutlineOffset::on_pushButton_clicked()
{
    GeneralDialog	*d=dynamic_cast<GeneralDialog *>(parent());
    if(d!=NULL){
        d->close();
    }
    else{
        close();
    }
}

void	EditOutlineOffset::ChangeValue(void)
{
    emit	ChangedValue();
}

void EditOutlineOffset::SlotClickedXYButton( int row ,int col)
{
    if(col==2 || col==4){
        EditOutlineOffsetAddDialog	D;
        if(D.exec()==(int)true){
            for(int r=row;r<GetLayersBase()->GetPageNumb();r++){
                DataInPage *PData=GetLayersBase()->GetPageData(r);
                if(col==2){
                    PData->GetOutlineOffsetLoaded()->x+=D.AddedOffset;
                }
                if(col==4){
                    PData->GetOutlineOffsetLoaded()->y+=D.AddedOffset;
                }
            }
            aGrid.ShowGrid();
            ChangeValue();
        }
    }
}
