/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\Sequence\SimulateSequence.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "SimulateSequence.h"
#include "ui_SimulateSequence.h"
#include "XSequence.h"
#include "XGeneralFunc.h"
#include "XPIOButton.h"
#include "ThreadSequence.h"
#include "XIODefine.h"
#include "XWaveEdit.h"
#include "XTimeConvert.h"
#include "XGeneralFunc.h"
#include "SeqLib/SeqLib/InputIntDialog.h"
#include "SeqLib/SeqLib/InputFloatDialog.h"
#include "SeqLib/SeqLib/InputBoolDialog.h"
#include "SeqLib/SeqLib/InputStringDialog.h"
#include "XDataInLayer.h"
#include "XExecuteInspectBase.h"
#include "ShowCOMForm.h"

SimulateSequence::SimulateSequence(SeqControl *seq ,QWidget *parent, Qt::WindowFlags flags) :
    QWidget(parent)
    ,BaseParent(seq)
    ,ui(new Ui::SimulateSequence)
{
    ui->setupUi(this);

    ui->SeqGrid->setColumnWidth ( 0, 20);
    ui->SeqGrid->setColumnWidth ( 1, 40);
    ui->SeqGrid->setColumnWidth ( 2, 30);
    ui->SeqGrid->setColumnWidth ( 3, 66);
    ui->SeqGrid->setColumnWidth ( 4, 66);
    ui->SeqGrid->setColumnWidth ( 5, 66);
    ui->SeqGrid->setColumnWidth ( 6, 66);
    ui->SeqGrid->setColumnWidth ( 7, 66);

    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,0, 28);
    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,1, 12);
    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,2, 12);
    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,3, 12);
    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,4, 12);
    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,5, 12);
    ::SetColumnWidthInTable(ui->tableWidgetCOMReg ,6, 12);

    BaseParent->HaltThread();
    ui->SGridSeq->setSelectionMode(QAbstractItemView::SingleSelection);
    ShowSeqList();

    QList<QTableWidgetItem *> Qi=ui->SGridSeq->selectedItems ();
    if(Qi.isEmpty()==false){
        QTableWidgetItem * SIndex=Qi.first();
        if(SIndex!=NULL){
            int	N=ui->SGridSeq->row(SIndex);
            ShowSequence(N);
            ViewAll(N);
        }
    }
    else{
        ShowSequence(0);
        ViewAll(0);
    }

    for(Sequence *s=BaseParent->Seq.GetFirst();s!=NULL;s=s->GetNext()){
        s->ClearBreak();
        s->SetDebugMode(true);
        }
    BaseParent->RestartThread();

    ui->ShowButton->setVisible(false);
    DLLVarOperand   *v=BaseParent->DLLVarOpe.GetFirst();
    if(v!=NULL){
        if(v->IsDebugMode()==true){
            ui->ShowButton->setVisible(true);
        }
    }
    ComCount=BaseParent->CommOpe.GetCount();
    if(ComCount==0){
        ShowCOMFormList=NULL;
    }
    else{
        ShowCOMFormList =new ShowCOMForm*[ComCount];
        for(int i=0;i<ComCount;i++){
            ShowCOMFormList[i]=NULL;
        }
    }
}

SimulateSequence::~SimulateSequence()
{
    delete ui;
    if(ShowCOMFormList!=NULL){
        for(int i=0;i<ComCount;i++){
            if(ShowCOMFormList[i]!=NULL){
                ShowCOMFormList[i]->deleteLater();
            }
        }
        delete  []ShowCOMFormList;
    }
}

void SimulateSequence::ShowSequence(int tabindex)
{
    int k=tabindex;
    if(k<0)
        return;
    Sequence *s=GetSeq(k);
    if(s==NULL)
        return;
    if(s->GetLatestFlag()==true)
        ui->CheckBoxFlag->setChecked(true);
    else
        ui->CheckBoxFlag->setChecked(false);

    int SLineNumb=s->GetSLineNumb();
    if(ui->SeqGrid->rowCount()-1!=SLineNumb){
        ui->SeqGrid->setRowCount(SLineNumb+1);
        }

    SetDataToTable(ui->SeqGrid ,0,0,/**/"L");
    SetDataToTable(ui->SeqGrid ,1,0,/**/"Line");
    SetDataToTable(ui->SeqGrid ,2,0,/**/"Flag");
    SetDataToTable(ui->SeqGrid ,3,0,/**/"Command");
    SetDataToTable(ui->SeqGrid ,4,0,/**/"OP1");
    SetDataToTable(ui->SeqGrid ,5,0,/**/"OP2");
    SetDataToTable(ui->SeqGrid ,6,0,/**/"OP3");
    SetDataToTable(ui->SeqGrid ,7,0,/**/"OP4");

    for(int i=0;i<SLineNumb;i++){
        SetDataToTable(ui->SeqGrid,0,i+1,/**/"");
        if(s->GetSLine(i)->LNumber>=0)
            SetDataToTable(ui->SeqGrid ,1,i+1 ,s->GetSLine(i)->LNumber);
        else
            SetDataToTable(ui->SeqGrid ,1,i+1 ,/**/"");

        QString	A=s->GetSLine(i)->eFlag.GetFlagString();
        SetDataToTable(ui->SeqGrid ,2,i+1,A);
        A=s->GetSLine(i)->GetName();
        SetDataToTable(ui->SeqGrid ,3,i+1,A);


        switch(s->GetSLine(i)->GetOpCount()){
            case 0:
                SetDataToTable(ui->SeqGrid ,4,i+1,/**/"");
                SetDataToTable(ui->SeqGrid ,5,i+1,/**/"");
                SetDataToTable(ui->SeqGrid ,6,i+1,/**/"");
                SetDataToTable(ui->SeqGrid ,7,i+1,/**/"");
                break;
            case 1:
                SetDataToTable(ui->SeqGrid ,4,i+1,s->GetSLine(i)->Op1->GetName());
                SetDataToTable(ui->SeqGrid ,5,i+1,/**/"");
                SetDataToTable(ui->SeqGrid ,6,i+1,/**/"");
                SetDataToTable(ui->SeqGrid ,7,i+1,/**/"");
                break;
            case 2:
                SetDataToTable(ui->SeqGrid ,4,i+1,s->GetSLine(i)->Op1->GetName());
                SetDataToTable(ui->SeqGrid ,5,i+1,s->GetSLine(i)->Op2->GetName());
                SetDataToTable(ui->SeqGrid ,6,i+1,/**/"");
                SetDataToTable(ui->SeqGrid ,7,i+1,/**/"");
                break;
            case 3:
                SetDataToTable(ui->SeqGrid ,4,i+1,s->GetSLine(i)->Op1->GetName());
                SetDataToTable(ui->SeqGrid ,5,i+1,s->GetSLine(i)->Op2->GetName());
                SetDataToTable(ui->SeqGrid ,6,i+1,s->GetSLine(i)->Op3->GetName());
                SetDataToTable(ui->SeqGrid ,7,i+1,/**/"");
                break;
            case 4:
                SetDataToTable(ui->SeqGrid ,4,i+1,s->GetSLine(i)->Op1->GetName());
                SetDataToTable(ui->SeqGrid ,5,i+1,s->GetSLine(i)->Op2->GetName());
                SetDataToTable(ui->SeqGrid ,6,i+1,s->GetSLine(i)->Op3->GetName());
                SetDataToTable(ui->SeqGrid ,7,i+1,s->GetSLine(i)->Op4->GetName());
                break;
            }
        }

    for(int i=0;i<SLineNumb;i++){
        SetDataToTable(ui->SeqGrid ,0,i+1,/**/"");
        }
    if(s->NowOnSubroutine==false)
        SetDataToTable(ui->SeqGrid ,0,s->GetNowLine()+1,/**/">");
    else
        SetDataToTable(ui->SeqGrid ,0,s->GetNowLine()+1,/**/"X");
}

Sequence    *SimulateSequence::GetSeq(int TabIndex)
{
    int N=0;
    for(Sequence *s=BaseParent->Seq.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->GetSType()==SequenceStock::_Subroutine)
            continue;
        if(N==TabIndex){
            if(s->NowOnSubroutine==true
            && s->SubroutineCall!=NULL){
                Sequence *t=s->SubroutineCall;
                while(t->NowOnSubroutine==true
                   && t->SubroutineCall!=NULL){
                    t=t->SubroutineCall;
                    }
                return(t);
                }
            return(s);
            }
        N++;
        }
    return(NULL);
}


void SimulateSequence::ShowSeqList(void)
{
    int Numb=0;
    for(Sequence *s=BaseParent->Seq.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->GetSType()==SequenceStock::_Subroutine)
            continue;
        if(s->NowOnSubroutine==true
        && s->SubroutineCall!=NULL){
            Sequence *t=s->SubroutineCall;
            while(t->NowOnSubroutine==true
               && t->SubroutineCall!=NULL){
                t=t->SubroutineCall;
                }
            Numb++;
            }
        else{
            Numb++;
            }
        }
    ui->SGridSeq->setRowCount(Numb);

    int N=0;
    for(Sequence *s=BaseParent->Seq.GetFirst();s!=NULL;s=s->GetNext()){
        if(s->GetSType()==SequenceStock::_Subroutine)
            continue;
        if(s->NowOnSubroutine==true
        && s->SubroutineCall!=NULL){
            Sequence *t=s->SubroutineCall;
            while(t->NowOnSubroutine==true
               && t->SubroutineCall!=NULL){
                t=t->SubroutineCall;
                }
            SetDataToTable(ui->SGridSeq ,0 ,N ,N+1);
            SetDataToTable(ui->SGridSeq ,1 ,N ,QString(s->GetSeqName())
                                             +QString(/**/" - ")
                                             +QString(t->GetSeqName()));
            N++;
            }
        else{
            //SetDataToTable(ui->SGridSeq ,0 ,N ,N+1);
            SetDataToTable(ui->SGridSeq ,0 ,N ,s->GetSeqName());
            N++;
            }
        }

}

void SimulateSequence::ShowIO(void)
{
    int L=0;

    int R=0;
    for(IOOperand *s=BaseParent->IOOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->IOGrid->setColumnWidth ( 0, 60);
    ui->IOGrid->setColumnWidth ( 1, 60);
    QStringList	Label;
    Label<</**/"I/O Name";
    Label<</**/"Value";
    ui->IOGrid->setHorizontalHeaderLabels(Label);

    ui->IOGrid->setRowCount(R);
    L=0;
    for(IOOperand *s=BaseParent->IOOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->IOGrid ,0,L,s->GetName());
        }
    L=0;
    for(IOOperand *s=BaseParent->IOOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->IOGrid ,1,L,s->GetNumeric());
        }

}

void SimulateSequence::ShowSystemReg(void)
{
    int L=0;

    int R=0;
    for(SpecialOperand *s=BaseParent->SpecialOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridSystemReg->setColumnWidth ( 0, 60);
    ui->SGridSystemReg->setColumnWidth ( 1, 60);
    ui->SGridSystemReg->setColumnWidth ( 2, 300);
    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    Label<</**/"Explain";
    ui->SGridSystemReg->setHorizontalHeaderLabels(Label);
    ui->SGridSystemReg->setRowCount(R);
    L=0;
    for(SpecialOperand *s=BaseParent->SpecialOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemReg,0,L,s->GetName());
    }
    L=0;
    for(SpecialOperand *s=BaseParent->SpecialOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemReg,1,L,s->GetNumeric());
    }

    L=0;
    SeqLocalParam	*Lp=BaseParent->LocalParamPointer;
    for(SpecialOperand *s=BaseParent->SpecialOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        int	ID=s->GetID();
        QString	C=Lp->GetExplainSpecialOperand(ID);
        SetDataToTable(ui->SGridSystemReg,2,L,C);
    }
}

void  SimulateSequence::ShowCOM(void)
{
   int L=0;

    int R=0;
    for(CommOperand *s=BaseParent->CommOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->tableWidgetCOMReg->setRowCount(R);
    L=0;
    for(CommOperand *s=BaseParent->CommOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->tableWidgetCOMReg ,0,L,s->GetName());
        SetDataToTable(ui->tableWidgetCOMReg ,1,L,QString::number(s->CommPort));
        SetDataToTable(ui->tableWidgetCOMReg ,2,L,QString::number(s->BPS));
        SetDataToTable(ui->tableWidgetCOMReg ,3,L,QString::number(s->Character));
        SetDataToTable(ui->tableWidgetCOMReg ,4,L,QString::number(s->Parity));
        SetDataToTable(ui->tableWidgetCOMReg ,5,L,QString::number(s->Stopbit));
        SetDataToTable(ui->tableWidgetCOMReg ,6,L,(s->IsOpened()==true)?"Open":"Close");
    }
}

void SimulateSequence::ShowQReg(void)
{
    int L=0;

    int R=0;
    for(SpecialStringOperand *s=BaseParent->SpecialStringOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridSystemQReg->setColumnWidth ( 0, 60);
    ui->SGridSystemQReg->setColumnWidth ( 1, 60);
    ui->SGridSystemQReg->setColumnWidth ( 2, 300);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    Label<</**/"Explain";
    ui->SGridSystemQReg->setHorizontalHeaderLabels(Label);
    ui->SGridSystemQReg->setRowCount(R);
    L=0;
    for(SpecialStringOperand *s=BaseParent->SpecialStringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemQReg,0,L,s->GetName());
        }
    L=0;
    for(SpecialStringOperand *s=BaseParent->SpecialStringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemQReg,1,L,s->GetString());
    }

    L=0;
    SeqLocalParam	*Lp=BaseParent->LocalParamPointer;
    for(SpecialStringOperand *s=BaseParent->SpecialStringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        int	ID=s->GetID();
        SetDataToTable(ui->SGridSystemQReg,2,L,Lp->GetExplainSpecialStringOperand(ID));
    }
}

void SimulateSequence::ShowRReg(void)
{
    int L=0;

    int R=0;
    for(SpecialFloatOperand *s=BaseParent->SpecialFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridSystemRReg->setColumnWidth ( 0, 60);
    ui->SGridSystemRReg->setColumnWidth ( 1, 100);
    ui->SGridSystemRReg->setColumnWidth ( 2, 240);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    Label<</**/"Explain";
    ui->SGridSystemRReg->setHorizontalHeaderLabels(Label);
    ui->SGridSystemRReg->setRowCount(R);
    L=0;
    for(SpecialFloatOperand *s=BaseParent->SpecialFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemRReg,0,L,s->GetName());
        }
    L=0;
    for(SpecialFloatOperand *s=BaseParent->SpecialFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemRReg,1,L,s->GetString());
    }

    L=0;
    SeqLocalParam	*Lp=BaseParent->LocalParamPointer;
    for(SpecialFloatOperand *s=BaseParent->SpecialFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        int	ID=s->GetID();
        SetDataToTable(ui->SGridSystemRReg,2,L,Lp->GetExplainSpecialFloatOperand(ID));
    }
}

void SimulateSequence::ShowWReg(void)
{
    int L=0;

    int R=0;
    for(WordOperand *s=(WordOperand *)BaseParent->WordOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridWReg->setColumnWidth ( 0, 60);
    ui->SGridWReg->setColumnWidth ( 1, 60);
    ui->SGridWReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridWReg->setHorizontalHeaderLabels(Label);

    L=0;
    for(WordOperand *s=(WordOperand *)BaseParent->WordOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridWReg,0,L,s->GetName());
        }
    L=0;
    for(WordOperand *s=(WordOperand *)BaseParent->WordOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridWReg,1,L,s->GetNumeric());
        }
}

void SimulateSequence::ShowBReg(void)
{
    int L;
    int R=0;
    for(BitOperand *s=(BitOperand *)BaseParent->BitOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridBReg->setColumnWidth ( 0, 60);
    ui->SGridBReg->setColumnWidth ( 1, 60);
    ui->SGridBReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridBReg->setHorizontalHeaderLabels(Label);

    L=0;
    for(BitOperand *s=(BitOperand *)BaseParent->BitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridBReg,0,L,s->GetName());
        }
    L=0;
    for(BitOperand *s=(BitOperand *)BaseParent->BitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridBReg,1,L,s->GetNumeric());
        }
}

void SimulateSequence::ShowCReg(void)
{
    int R=0;
    for(StringOperand *s=(StringOperand *)BaseParent->StringOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridCReg->setColumnCount (3);
    ui->SGridCReg->setColumnWidth ( 0, 60);
    ui->SGridCReg->setColumnWidth ( 1, 80);
    ui->SGridCReg->setColumnWidth ( 2, 80);
    ui->SGridCReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    Label<</**/"Hex";
    ui->SGridCReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(StringOperand *s=(StringOperand *)BaseParent->StringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridCReg,0,L,s->GetName());
        }
    L=0;
    for(StringOperand *s=(StringOperand *)BaseParent->StringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        QByteArray  A=s->GetString();
        SetDataToTable(ui->SGridCReg,1,L,QString(A));
        QString HexStr;
        for(int i=0;i<A.count();i++){
            unsigned char   t=A[i];
            HexStr+=QString::number(t,16);
            if((i+1)<A.count()){
                HexStr+=QString(",");
            }
        }
        SetDataToTable(ui->SGridCReg,2,L,HexStr);
    }
}

void SimulateSequence::ShowFReg(void)
{
    int R=0;
    for(FloatOperand *s=(FloatOperand *)BaseParent->FloatOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridFReg->setColumnWidth ( 0, 60);
    ui->SGridFReg->setColumnWidth ( 1, 60);
    ui->SGridFReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridFReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(FloatOperand *s=(FloatOperand *)BaseParent->FloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridFReg,0,L,s->GetName());
        }
    L=0;
    for(FloatOperand *s=(FloatOperand *)BaseParent->FloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridFReg,1,L,s->GetString());
        }
}

void SimulateSequence::ShowGReg(void)
{
    int R=0;
    for(GroupOperand *s=(GroupOperand *)BaseParent->GroupOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridGReg->setColumnWidth ( 0, 60);
    ui->SGridGReg->setColumnWidth ( 1, 60);
    ui->SGridGReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridGReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(GroupOperand *s=(GroupOperand *)BaseParent->GroupOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridGReg,0,L,s->GetName());
        }
    L=0;
    for(GroupOperand *s=(GroupOperand *)BaseParent->GroupOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridGReg,1,L,s->GetNumeric());
        }
}

void SimulateSequence::ShowPReg(void)
{
    int R=0;
    for(SpecialBitOperand *s=(SpecialBitOperand *)BaseParent->SpecialBitOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridSystemBReg->setColumnWidth ( 0, 60);
    ui->SGridSystemBReg->setColumnWidth ( 1, 60);
    ui->SGridSystemBReg->setColumnWidth ( 2, 300);
    ui->SGridSystemBReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    Label<</**/"Explain";
    ui->SGridSystemBReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(SpecialBitOperand *s=(SpecialBitOperand *)BaseParent->SpecialBitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemBReg,0,L,s->GetName());
        }
    L=0;
    for(SpecialBitOperand *s=(SpecialBitOperand *)BaseParent->SpecialBitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridSystemBReg,1,L,s->GetNumeric());
    }

    L=0;
    SeqLocalParam	*Lp=BaseParent->LocalParamPointer;
    for(SpecialBitOperand *s=(SpecialBitOperand *)BaseParent->SpecialBitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        int	ID=s->GetID();
        SetDataToTable(ui->SGridSystemBReg,2,L,Lp->GetExplainSpecialBitOperand(ID));
    }

}

void SimulateSequence::ShowLanvar(void)
{
    /*
    int L=0;

    int R=0;
    for(LanvarOperand *s=(LanvarOperand *)BaseParent->LanvarOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    L=0;
    LanGrid->setRowCount(R+1);
    LanGrid->item(0,0)->setText("Reg Name");
    LanGrid->item(1,0)->setText("");
    L++;
    for(LanvarOperand *s=(LanvarOperand *)BaseParent->LanvarOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        LanGrid->item(0,L)->setText(s->GetName());
        }
    L=1;
    for(LanvarOperand *s=(LanvarOperand *)BaseParent->LanvarOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        LanGrid->item(1,L)->setText(s->GetString(false));
        }
    */
}

void SimulateSequence::ShowFIFO(void)
{
    int R=0;
    for(FifoOperand *s=(FifoOperand *)BaseParent->FifoOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridFifo->setColumnWidth ( 0, 60);
    ui->SGridFifo->setColumnWidth ( 1, 60);
    ui->SGridFifo->setRowCount(R);

    QStringList	Label;
    Label<</**/"FIFO Name";
    Label<</**/"Stacked";
    ui->SGridFifo->setHorizontalHeaderLabels(Label);

    int L=0;
    for(FifoOperand *s=(FifoOperand *)BaseParent->FifoOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridFifo,0,L,s->GetName());
        }
    L=0;
    for(FifoOperand *s=(FifoOperand *)BaseParent->FifoOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridFifo,1,L,s->GetStackedNumb());
        }
}

void SimulateSequence::ShowLBReg(int TabIndex)
{
    int k=TabIndex;
    if(k<0)
        return;
    Sequence *ms=GetSeq(k);
    if(ms==NULL)
        return;
    int R=0;
    for(LocalBitOperand *s=(LocalBitOperand *)ms->LocalRegs.LocalBitOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridLBReg->setColumnWidth ( 0, 60);
    ui->SGridLBReg->setColumnWidth ( 1, 60);
    ui->SGridLBReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridLBReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(LocalBitOperand *s=(LocalBitOperand *)ms->LocalRegs.LocalBitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLBReg,0,L,s->GetName());
        }
    L=0;
    for(LocalBitOperand *s=(LocalBitOperand *)ms->LocalRegs.LocalBitOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLBReg,1,L,s->GetNumeric());
        }
}

void SimulateSequence::ShowLWReg(int TabIndex)
{
    int k=TabIndex;
    if(k<0)
        return;
    Sequence *ms=GetSeq(k);
    if(ms==NULL)
        return;
    int R=0;
    for(LocalWordOperand *s=(LocalWordOperand *)ms->LocalRegs.LocalWordOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridLWReg->setColumnWidth ( 0, 60);
    ui->SGridLWReg->setColumnWidth ( 1, 60);
    ui->SGridLWReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridLWReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(LocalWordOperand *s=(LocalWordOperand *)ms->LocalRegs.LocalWordOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLWReg,0,L,s->GetName());
        }
    L=0;
    for(LocalWordOperand *s=(LocalWordOperand *)ms->LocalRegs.LocalWordOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLWReg,1,L,s->GetNumeric());
        }
}

void SimulateSequence::ShowLFReg(int TabIndex)
{
    int k=TabIndex;
    if(k<0)
        return;
    Sequence *ms=GetSeq(k);
    if(ms==NULL)
        return;
    int R=0;
    for(LocalFloatOperand *s=(LocalFloatOperand *)ms->LocalRegs.LocalFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridLFReg->setColumnWidth ( 0, 60);
    ui->SGridLFReg->setColumnWidth ( 1, 60);
    ui->SGridLFReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridLFReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(LocalFloatOperand *s=(LocalFloatOperand *)ms->LocalRegs.LocalFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLFReg,0,L,s->GetName());
        }
    L=0;
    for(LocalFloatOperand *s=(LocalFloatOperand *)ms->LocalRegs.LocalFloatOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        char	buff[100];
        sprintf(buff,/**/"%lf",(double)s->GetFloat());
        QString e=QString::fromLatin1(buff);
        SetDataToTable(ui->SGridLFReg,1,L,e);
        }
}

void SimulateSequence::ShowLCReg(int TabIndex)
{
    int k=TabIndex;
    if(k<0)
        return;
    Sequence *ms=GetSeq(k);
    if(ms==NULL)
        return;

    int R=0;
    for(LocalStringOperand *s=(LocalStringOperand *)ms->LocalRegs.LocalStringOpe.GetFirst();s!=NULL;s=s->GetNext(),R++);

    ui->SGridLCReg->setColumnWidth ( 0, 60);
    ui->SGridLCReg->setColumnWidth ( 1, 60);
    ui->SGridLCReg->setRowCount(R);

    QStringList	Label;
    Label<</**/"Reg Name";
    Label<</**/"Value";
    ui->SGridLCReg->setHorizontalHeaderLabels(Label);

    int L=0;
    for(LocalStringOperand *s=(LocalStringOperand *)ms->LocalRegs.LocalStringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLCReg,0,L,s->GetName());
        }
    L=0;
    for(LocalStringOperand *s=(LocalStringOperand *)ms->LocalRegs.LocalStringOpe.GetFirst();s!=NULL;s=s->GetNext(),L++){
        SetDataToTable(ui->SGridLCReg,1,L,s->GetString());
        }
}

void SimulateSequence::ViewAll(int TabIndex)
{
    ShowIO();
    ShowSystemReg();
    ShowWReg();
    ShowBReg();
    ShowCReg();
    ShowGReg();
    ShowPReg();
    ShowQReg();
    ShowLanvar();
    ShowFReg();
    ShowFIFO();
    ShowLWReg(TabIndex);
    ShowLBReg(TabIndex);
    ShowLCReg(TabIndex);
    ShowLFReg(TabIndex);
    ShowSequence(TabIndex);
    ShowCOM();
    //ui->SeqGrid->repaint();
}

void SimulateSequence::on_SGridSystemReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()!=1)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    SpecialOperand *s=(SpecialOperand *)BaseParent->SpecialOpe.GetItem(NRow);
    if(s!=NULL){
        InputIntDialog	D(s->GetNumeric(),this);
        if(D.exec()==(int)true){
            s->SetData(D.Value);
            ShowSystemReg();
        }
    }
}

void SimulateSequence::on_SGridSystemBReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()!=1)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    SpecialBitOperand *s=(SpecialBitOperand *)BaseParent->SpecialBitOpe.GetItem(NRow);
    if(s!=NULL){
        InputBoolDialog	D((s->GetNumeric()==1)?true:false,this);
        if(D.exec()==(int)true){
            s->SetData((D.Value==true)?1:0);
            ShowPReg();
        }
    }
}

void SimulateSequence::on_SGridSystemQReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()!=1)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    SpecialStringOperand *s=(SpecialStringOperand *)BaseParent->SpecialStringOpe.GetItem(NRow);
    if(s!=NULL){
        InputStringDialog	D(s->GetString(),this);
        if(D.exec()==(int)true){
            s->SetData(D.Value);
            ShowQReg();
        }
    }
}

void SimulateSequence::on_SGridSystemRReg_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridWReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()==0)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    WordOperand *s=(WordOperand *)BaseParent->WordOpe.GetItem(NRow);
    if(s!=NULL){
        InputIntDialog	D(s->GetNumeric(),this);
        if(D.exec()==(int)true){
            s->SetData(D.Value);
            ShowWReg();
        }
    }
}

void SimulateSequence::on_IOGrid_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridBReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()==0)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    BitOperand *s=(BitOperand *)BaseParent->BitOpe.GetItem(NRow);
    if(s!=NULL){
        InputBoolDialog	D((s->GetNumeric()==1)?true:false,this);
        if(D.exec()==(int)true){
            s->SetData((D.Value==true)?1:0);
            ShowBReg();
        }
    }
}

void SimulateSequence::on_SGridFReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()==0)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    FloatOperand *s=(FloatOperand *)BaseParent->FloatOpe.GetItem(NRow);
    if(s!=NULL){
        InputFloatDialog	D(s->GetFloat(),this);
        if(D.exec()==(int)true){
            s->SetFloat(D.Value);
            ShowFReg();
        }
    }
}

void SimulateSequence::on_SGridCReg_doubleClicked(const QModelIndex &index)
{
    if(index.column()==0)
        return;
    int	NRow=index.row();
    if(NRow<0)
        return;

    StringOperand *s=(StringOperand *)BaseParent->StringOpe.GetItem(NRow);
    if(s!=NULL){
        InputStringDialog	D(s->GetString(),this);
        if(D.exec()==(int)true){
            s->SetData(D.Value);
            ShowCReg();
        }
    }
}

void SimulateSequence::on_SGridGReg_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_LanGrid_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridLBReg_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridLWReg_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridLFReg_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridLCReg_doubleClicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SeqGrid_clicked(const QModelIndex &index)
{

}

void SimulateSequence::on_SGridFifo_clicked(const QModelIndex &index)
{
    int	Index=ui->SGridFifo->currentRow();
    FifoOperand *s=(FifoOperand *)BaseParent->FifoOpe[Index];
    if(s!=NULL){
        s->Lock();
        ui->ListBFifo->clear();
        for(FifoClass *f=s->Data.GetFirst();f!=NULL;f=f->GetNext()){
            ui->ListBFifo->addItem(f->Str);
        }
        s->Unlock();
    }
}

void SimulateSequence::on_ViewButton_clicked()
{
    BaseParent->HaltThread();
	QList<QTableWidgetItem *> Qi=ui->SGridSeq->selectedItems ();
	if(Qi.isEmpty()==false){
 		QTableWidgetItem * SIndex=Qi.first();
		if(SIndex!=NULL){
			int	N=ui->SGridSeq->row(SIndex);
			ViewAll(N);
		}
	}
	else
		ViewAll(0);
    BaseParent->RestartThread();
}

void SimulateSequence::on_BreakPointButton_clicked()
{

}

void SimulateSequence::on_GoButton_clicked()
{

}

void SimulateSequence::on_StepButton_clicked()
{

}

void SimulateSequence::on_StopButton_clicked()
{

}

void SimulateSequence::on_ShowButton_clicked()
{
    DLLVarOperand   *v=BaseParent->DLLVarOpe.GetFirst();
    if(v!=NULL){
        if(v->IsDebugMode()==true){
            //v->DLLDebug(Application);
        }
    }
}

void SimulateSequence::on_CloseButton_clicked()
{
    close();
}

void SimulateSequence::on_tableWidgetCOMReg_doubleClicked(const QModelIndex &index)
{
    int Row=ui->tableWidgetCOMReg->currentRow();
    if(Row>=0){
        CommOperand *s=BaseParent->CommOpe.GetItem(Row);
        if(s!=NULL){
            if(ShowCOMFormList!=NULL && Row<ComCount){
                if(ShowCOMFormList[Row]!=NULL){
                    ShowCOMFormList[Row]->show();
                }
                else{
                    ShowCOMFormList[Row]=new ShowCOMForm(s);
                    ShowCOMFormList[Row]->show();
                }
            }
        }
    }
}

