/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
** This file is provided as is with no warranty
**
** This file is C:\Regulus64v5\OpenSource\DisplayImage\SelectPasteForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "DisplayImageResource.h"
#include "XTypeDef.h"
#include "SelectPasteForm.h"
#include "ui_SelectPasteForm.h"
#include "XDataInLayer.h"
#include "XGeneralFunc.h"
#include "XDisplayImage.h"
#include "Regulus64Version.h"
#include "XAlert.h"
#include "XDisplayImagePacket.h"
#include "SelectColorDialog.h"
#include <typeinfo>
#include "XDataInLayerToDisplayImage.h"

SelectPasteForm::SelectPasteForm(DisplayImageWithAlgorithm *parentPanel ,LayersBase *base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(base)
    ,ui(new Ui::SelectPasteForm)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Window | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

    LangDISolver.SetLanguage(base->GetLanguagePackageData(),base->GetLanguageCode());
    LangDISolver.SetUI(this);

    ParentPanel	=parentPanel;
    RetMode		=-1;
    ui->GridPaste->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->GridPaste->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->comboBoxPastedLayer->clear();
    ui->comboBoxPastedLayer->addItem(LangDISolver.GetString(SelectPasteForm_LS,LID_50)/*"Same Layer"*/,(int)-1);
    for(int layer=0;layer<GetLayersBase()->GetMaxLayerNumb();layer++){
        //QString s=LangDISolver.GetString(SelectPasteForm_LS,LID_51)/*"Layer "*/;
        //s=s+QString::number(layer);
        QString	s=GetParamGlobal()->GetLayerName(layer);
        ui->comboBoxPastedLayer->addItem(s,layer);
    }
    CreateList();
    ShowList();

    IntList	LayerList;
    parentPanel->GetActiveLayerList(LayerList);
    if(LayerList.GetCount()==1){
        int	CurrentLayer=LayerList.GetFirst()->GetValue();
        ui->comboBoxPastedLayer	->setCurrentIndex(CurrentLayer+1);
    }
    if(GetLayersBase()->GetMaxLayerNumb()==1){
        ui->label				->setVisible(false);
        ui->comboBoxPastedLayer	->setVisible(false);
    }

    InstallOperationLog(this);

    AlgorithmBase	*ABase=ParentPanel->GetAlgorithmBase();
    if(ABase->GetModel()==Model_PLI){
        ui->stackedWidgetLayerType->setCurrentIndex(0);
    }
    else if(ABase->GetModel()==Model_PI){
        ui->stackedWidgetLayerType->setCurrentIndex(1);
    }
    else{
        ui->stackedWidgetLayerType->setCurrentIndex(0);
    }
}

SelectPasteForm::~SelectPasteForm()
{
    delete ui;
}

void	SelectPasteForm::CreateList(void)
{
    CreateList(GetLayersBase(),Lists);
}

void	SelectPasteForm::CreateList(LayersBase *Base,NPListPack<CopiedList> &HLists)
{
    GUICmdReqCopiedList		**CmdRequester	=new GUICmdReqCopiedList*[Base->GetPageNumb()];
    GUICmdSendCopiedList	**CmdSender		=new GUICmdSendCopiedList*[Base->GetPageNumb()];
    for(int page=0;page<Base->GetPageNumb();page++){
        CmdRequester[page]	=new GUICmdReqCopiedList (Base,/**/"ANY",/**/"ANY",-1);
        CmdSender[page]		=new GUICmdSendCopiedList(Base,/**/"ANY",/**/"ANY",-1);
    }
    for(int page=0;page<Base->GetPageNumb();page++){
        CmdRequester[page]->Send(Base->GetGlobalPageFromLocal(page)
                            ,0,*CmdSender[page]);
    }
    HLists.RemoveAll();
    for(int page=0;page<Base->GetPageNumb();page++){
        if(CmdSender[page]->IsReceived()==true){
            for(CopiedList *s=CmdSender[page]->Lists.GetFirst();s!=NULL;s=s->GetNext()){
                CopiedList *L;
                for(L=HLists.GetFirst();L!=NULL;L=L->GetNext()){
                    if(L->GetCopiedTime()==s->GetCopiedTime()){
                        break;
                    }
                }
                if(L==NULL){
                    L=new CopiedList();
                    *L=*s;
                    HLists.AppendList(L);
                }
            }
        }
    }
    for(int page=0;page<Base->GetPageNumb();page++){
        delete	CmdRequester[page];
        delete	CmdSender[page];
    }
    delete	[]CmdRequester;
    delete	[]CmdSender;
    bool	Changed;
    do{
        Changed=false;
        for(CopiedList *L=HLists.GetFirst();L!=NULL;L=L->GetNext()){
            CopiedList *M=L->GetNext();
            if(M==NULL){
                break;
            }
            if(L->GetCopiedTime()<M->GetCopiedTime()){
                HLists.Swap(L,M);
                Changed=true;
            }
        }
    }while(Changed==true);
}

XDateTime	SelectPasteForm::GetTopCopiedData(LayersBase *Base
                                            ,QString &AlgoRoot ,QString &AlgoName)
{
    NPListPack<CopiedList> HLists;
    CreateList(Base,HLists);
    CopiedList	*c=HLists.GetFirst();
    XDateTime   Ret;
    if(c!=NULL){
        AlgoRoot	=c->GetAlgoRoot();
        AlgoName	=c->GetAlgoName();
        Ret=c->GetCopiedTime();
    }
    return Ret;
}

void	SelectPasteForm::ShowList(void)
{
    ui->GridPaste->setRowCount(Lists.GetNumber());
    for(int i=0;i<ui->GridPaste->rowCount();i++){
        CopiedList	*L=Lists.GetItem(i);
        if(L!=NULL){
            QTableWidgetItem	*w;
            w=new QTableWidgetItem(L->GetCopiedTime().toString(/**/"yyyy/MM/dd hh:mm:ss"));
            ui->GridPaste->setItem (i, 0, w);
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            w=new QTableWidgetItem(QString::number(L->GetCounts()));
            ui->GridPaste->setItem (i, 1, w);
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            w=new QTableWidgetItem(L->GetAlgoRoot());
            ui->GridPaste->setItem (i, 2, w);
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            w=new QTableWidgetItem(L->GetAlgoName());
            ui->GridPaste->setItem (i, 3, w);
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);

            w=new QTableWidgetItem(L->GetRemark());
            ui->GridPaste->setItem (i, 4, w);
            w->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
    }
}

void SelectPasteForm::LoadPasteSameAlgorithm(LayersBase *Base,DisplayImageWithAlgorithm *Panel,const XDateTime &d,int PastedLayer)
{
    //int	PastedLayer=-1;
    QString emitterRoot;
    QString emitterName;
    Panel->GetIdentity(emitterRoot ,emitterName);
    for(int page=0;page<Base->GetPageNumb();page++){
        GUICmdReqSelectCopied	Cmd(Base,emitterRoot ,emitterName,-1);
        Cmd.SelectTimeIndex=d;
        Cmd.Mode=GUICmdReqSelectCopied::_PurePaste;
        Cmd.InstName=Panel->GetName();
        Cmd.PastedLayer=PastedLayer;
        Cmd.Send(NULL,Base->GetGlobalPageFromLocal(page),0);
    }
}

void SelectPasteForm::on_GridPaste_clicked(const QModelIndex &index)
{
    int	Row=ui->GridPaste->currentRow();
    if(Row<0)
        return;
    CopiedList	*L=Lists.GetItem(Row);
    if(L==NULL){
        return;
    }
    if(ParentPanel==NULL){
        return;
    }
    AlgorithmBase	*ABase=ParentPanel->GetAlgorithmBase();
    if(ABase==NULL){
        return;
    }
    QString	AlgoRoot,AlgoName;
    ABase->GetAlgorithmRootName(AlgoRoot,AlgoName);
    if(L->GetAlgoRoot()!=AlgoRoot || L->GetAlgoName()!=AlgoName){
        ui->ButtonPasteSameAlgoPos				->setEnabled(false);
        ui->ButtonPasteSameAlgoPosToSelectedLayer->setEnabled(false);
    }
    else{
        ui->ButtonPasteSameAlgoPos				->setEnabled(true);
        ui->ButtonPasteSameAlgoPosToSelectedLayer->setEnabled(true);
    }
}

void SelectPasteForm::on_ButtonPasteSameAlgoPosToSelectedLayer_clicked()
{
    if(ui->GridPaste->selectedRanges().count()==0){
        return;
    }
    int	LayerIndex=ui->comboBoxPastedLayer->currentIndex ();
    int	PastedLayer=-1;
    if(LayerIndex>=0){
        QVariant q=ui->comboBoxPastedLayer->itemData (LayerIndex);
        PastedLayer=q.toInt();
    }
    QTableWidgetSelectionRange	Q=ui->GridPaste->selectedRanges().first();
    int	Index=Q.topRow();
    CopiedList	*L=Lists.GetItem(Index);
    if(L==NULL){
        return;
    }
    LoadPasteSameAlgorithm(GetLayersBase(),ParentPanel,L->GetCopiedTime(),PastedLayer);

    RetMode=16;
    emit	SignalClose();
}

void SelectPasteForm::on_ButtonPasteSameAlgoPos_clicked()
{
    if(ui->GridPaste->selectedRanges().count()==0){
        return;
    }
    int	LayerIndex=ui->comboBoxPastedLayer->currentIndex ();
    if(LayerIndex>=0){
        QVariant q=ui->comboBoxPastedLayer->itemData (LayerIndex);
    }
    QTableWidgetSelectionRange	Q=ui->GridPaste->selectedRanges().first();
    int	Index=Q.topRow();
    CopiedList	*L=Lists.GetItem(Index);
    if(L==NULL){
        return;
    }
    LoadPasteSameAlgorithm(GetLayersBase(),ParentPanel,L->GetCopiedTime());

    RetMode=6;
    emit	SignalClose();
}

void SelectPasteForm::on_pushButtonCutOnShape_clicked()
{
    if(ui->GridPaste->selectedRanges().count()==0){
        return;
    }
    QTableWidgetSelectionRange	Q=ui->GridPaste->selectedRanges().first();
    int	Index=Q.topRow();
    CopiedList	*L=Lists.GetItem(Index);
    if(L==NULL){
        return;
    }
    QString emitterRoot;
    QString emitterName;
    ParentPanel->GetIdentity(emitterRoot ,emitterName);

    for(int page=0;page<GetPageNumb();page++){
        GUICmdReqSelectCopied	Cmd(GetLayersBase(),emitterRoot ,emitterName,-1);
        Cmd.SelectTimeIndex=L->GetCopiedTime();
        Cmd.Mode=GUICmdReqSelectCopied::_CutByShape;
        Cmd.InstName=ParentPanel->GetName();
        Cmd.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
    }
    RetMode=5;
    emit	SignalClose();
}

void SelectPasteForm::on_ButtonFixedPasteByShape_clicked()
{
    int	LayerIndex=ui->comboBoxPastedLayer->currentIndex ();
    int	PastedLayer=-1;
    if(LayerIndex>=0 && ui->stackedWidgetLayerType->currentIndex()==0){
        QVariant q=ui->comboBoxPastedLayer->itemData (LayerIndex);
        PastedLayer=q.toInt();
    }
    else if(ui->stackedWidgetLayerType->currentIndex()==1){
        if(ui->toolButtonAdoptLayer0->isChecked()==true){
            PastedLayer=0;
        }
    }
    if(ui->GridPaste->selectedRanges().count()==0){
        return;
    }
    QTableWidgetSelectionRange	Q=ui->GridPaste->selectedRanges().first();
    int	Index=Q.topRow();
    CopiedList	*L=Lists.GetItem(Index);
    if(L==NULL){
        return;
    }
    QString emitterRoot;
    QString emitterName;
    ParentPanel->GetIdentity(emitterRoot ,emitterName);

    for(int page=0;page<GetPageNumb();page++){
        GUICmdReqSelectCopied	Cmd(GetLayersBase(),emitterRoot ,emitterName,-1);
        Cmd.SelectTimeIndex=L->GetCopiedTime();
        Cmd.Mode=GUICmdReqSelectCopied::_ShapedPaste;
        Cmd.InstName=ParentPanel->GetName();
        Cmd.PastedLayer	=PastedLayer;
        Cmd.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
    }
    ParentPanel->ExecutePasteShape(L->GetAlgoRoot(),L->GetAlgoName());
    ParentPanel->SetPastedLayer(PastedLayer);
    ParentPanel->SetMaskPaint(100);
    RetMode=3;
    emit	SignalClose();
}

void SelectPasteForm::on_ButtonFixedPasteForImage_clicked()
{
    if(ui->GridPaste->selectedRanges().count()==0){
        return;
    }
    QTableWidgetSelectionRange	Q=ui->GridPaste->selectedRanges().first();
    int	Index=Q.topRow();
    CopiedList	*L=Lists.GetItem(Index);
    if(L==NULL){
        return;
    }
    QString emitterRoot;
    QString emitterName;
    ParentPanel->GetIdentity(emitterRoot ,emitterName);

    SelectColorDialog	D(GetLayersBase(),this);
    if(D.exec()==(int)true){
        for(int page=0;page<GetPageNumb();page++){
            GUICmdReqSelectCopied	Cmd(GetLayersBase(),emitterRoot ,emitterName,-1);
            Cmd.SelectTimeIndex=L->GetCopiedTime();
            Cmd.Mode=GUICmdReqSelectCopied::_PasteForImage;
            Cmd.InstName=ParentPanel->GetName();
            Cmd.PastedLayer	=0;
            Cmd.Color		=D.Color;
            Cmd.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
        }
        ParentPanel->ExecutePasteShape(L->GetAlgoRoot(),L->GetAlgoName());

        RetMode=4;
        emit	SignalClose();
    }
}

void SelectPasteForm::on_pushButtonSave_clicked()
{
    IntList	RowList;
    QList<QTableWidgetItem *> Q=ui->GridPaste->selectedItems ();
    if(Q.count()==0){
        return;
    }

    QString FileName=GetLayersBase()->LGetSaveFileName (0
													,LangDISolver.GetString(SelectPasteForm_LS,LID_57)/*"Save Paste-File"*/
													,QString()
													, /**/"PasteFile(*.psi)");
    if(FileName.isEmpty()==true){
        return;
    }
    QFile	F(FileName);
    if(F.open(QIODevice::WriteOnly)==false){
        return;
    }

    for(int i=0;i<Q.count();i++){
        QTableWidgetItem *item=Q.value(i);
        if(item->column()!=0){
            continue;
        }
        int	RowIndex=item->row();
        RowList.Add(RowIndex);
    }

    SaveLine(&F,RowList);
}

bool SelectPasteForm::SaveLine(QIODevice *f,IntList	&RowList)
{
    int32	FileID=FileIDPasteData;
    if(::Save(f,FileID)==false){
        return false;
    }

    int32	N=RowList.GetCount();
    if(::Save(f,N)==false){
        return false;
    }

    for(IntClass *d=RowList.GetFirst();d!=NULL;d=d->GetNext()){
        int	RowIndex=d->GetValue();
        CopiedList	*L=Lists.GetItem(RowIndex);
        if(L==NULL){
            continue;
        }

        int32	PageNumb=GetPageNumb();
        if(::Save(f,PageNumb)==false){
            return false;
        }
        for(int32 page=0;page<GetPageNumb();page++){
            GUICmdReqCopiedForSave		ReqCmd(GetLayersBase(),/**/"ANY" ,/**/"ANY",-1);
            GUICmdAckCopiedForSave		AckCmd(GetLayersBase(),/**/"ANY" ,/**/"ANY",-1);
            ReqCmd.SelectTimeIndex=L->GetCopiedTime();
            if(ReqCmd.Send(page ,0,AckCmd)==true){
                if(::Save(f,page)==false){
                    return false;
                }
                if(::Save(f,AckCmd.Buff)==false){
                    return false;
                }
            }
        }
    }
    return true;
}
void SelectPasteForm::on_pushButtonLoad_clicked()
{
    QString FileName=GetLayersBase()->LGetOpenFileName (0
                                    , LangDISolver.GetString(SelectPasteForm_LS,LID_63)/*"Load Paste-File"*/
                                    , QString(),/**/"PasteFile(*.psi)");
    if(FileName.isEmpty()==true){
        return;
    }

    QFile	F(FileName);
    if(F.open(QIODevice::ReadOnly)==false){
        return;
    }
    if(LoadLine(&F)==true){
        CreateList();
        ShowList();
    }
}

bool SelectPasteForm::LoadLine(QIODevice *f)
{
    int32	FileID;
    if(::Load(f,FileID)==false){
        return false;
    }
    if(FileID!=FileIDPasteData){
        Alert(LangDISolver.GetString(SelectPasteForm_LS,LID_65)/*"Mismatch file type"*/);
        return false;
    }
    int32	N;
    if(::Load(f,N)==false){
        return false;
    }
    for(int i=0;i<N;i++){
        int32	PageNumb;
        if(::Load(f,PageNumb)==false){
            return false;
        }
        for(int kpage=0;kpage<PageNumb;kpage++){
            int32	page;
            if(::Load(f,page)==false){
                break;
            }
            GUICmdSendCopiedForLoad		SendCmd(GetLayersBase(),/**/"ANY" ,/**/"ANY",-1);
            if(::Load(f,SendCmd.Buff)==false){
                break;
            }
            SendCmd.Send(NULL,GetLayersBase()->GetGlobalPageFromLocal(page),0);
        }
    }
    return true;
}
void SelectPasteForm::on_CancelButton_clicked()
{
    RetMode=-1;
    emit	SignalClose();
}

void SelectPasteForm::on_pushButtonDelete_clicked()
{
    QList<QTableWidgetItem *> Q=ui->GridPaste->selectedItems ();
    if(Q.count()==0){
        return;
    }
    for(int i=0;i<Q.count();i++){
        QTableWidgetItem *item=Q.value(i);
        if(item->column()!=0){
            continue;
        }
        int	RowIndex=item->row();
        CopiedList	*L=Lists.GetItem(RowIndex);
        if(L==NULL){
            continue;
        }

        for(int32 page=0;page<GetPageNumb();page++){
            GUICmdReqCopiedForDelete		ReqCmd(GetLayersBase(),/**/"ANY" ,/**/"ANY",-1);
            ReqCmd.SelectTimeIndex=L->GetCopiedTime();
            ReqCmd.Send(NULL,page ,0);
        }
    }
    CreateList();
    ShowList();
}

//===========================================================================================

SelectPasteForm::CopiedList	&SelectPasteForm::CopiedList::operator=(CopiedList &src)
{
    CopiedTime	=src.CopiedTime;
    Counts		=src.Counts;
    AlgoRoot	=src.AlgoRoot;
    AlgoName	=src.AlgoName;
    Remark		=src.Remark;
    return *this;
}
bool	SelectPasteForm::CopiedList::Save(QIODevice *f)
{
    if(::Save(f,CopiedTime)==false){
        return false;
    }
    if(::Save(f,Counts)==false){
        return false;
    }
    if(::Save(f,AlgoRoot)==false){
        return false;
    }
    if(::Save(f,AlgoName)==false){
        return false;
    }
    if(::Save(f,Remark)==false){
        return false;
    }
    return true;
}
bool	SelectPasteForm::CopiedList::Load(QIODevice *f)
{
    if(::Load(f,CopiedTime)==false){
        return false;
    }
    if(::Load(f,Counts)==false){
        return false;
    }
    if(::Load(f,AlgoRoot)==false){
        return false;
    }
    if(::Load(f,AlgoName)==false){
        return false;
    }
    if(::Load(f,Remark)==false){
        return false;
    }
    return true;
}


//===========================================================================================
//====================================================================================

bool	GUICmdReqCopiedList::Load(QIODevice *f)
{
    return true;
}
bool	GUICmdReqCopiedList::Save(QIODevice *f)
{
    return true;
}

void	GUICmdReqCopiedList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    GUICmdSendCopiedList	*SendBack=GetSendBack(GUICmdSendCopiedList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
    SendBack->MakeLists();
    SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
    CloseSendBack(SendBack);
}

//===========================================================================================

void	GUICmdSendCopiedList::MakeLists(void)
{
    for(ClipboardAlgorithm *L=GetLayersBase()->GetClipboardDatas()->GetFirst();L!=NULL;L=L->GetNext()){
        QString	AlgoRoot,AlgoName;
        L->Base->GetDLLName(AlgoRoot,AlgoName);
        SelectPasteForm::CopiedList	*Dest=new SelectPasteForm::CopiedList(L->GetCreatedTime(),L->Items.GetNumber(),AlgoRoot,AlgoName,L->Remark);
        Lists.AppendList(Dest);
    }
}

bool	GUICmdSendCopiedList::Load(QIODevice *f)
{
    int32	N;
    if(::Load(f,N)==false){
        return false;
    }
    for(int i=0;i<N;i++){
        SelectPasteForm::CopiedList *L=new SelectPasteForm::CopiedList();
        if(L->Load(f)==false){
            delete	L;
            return false;
        }
        Lists.AppendList(L);
    }
    return true;
}
bool	GUICmdSendCopiedList::Save(QIODevice *f)
{
    int32	N=Lists.GetNumber();
    if(::Save(f,N)==false){
        return false;
    }
    for(SelectPasteForm::CopiedList *L=Lists.GetFirst();L!=NULL;L=L->GetNext()){
        if(L->Save(f)==false){
            return false;
        }
    }
    return true;
}

void	GUICmdSendCopiedList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//====================================================================================

bool	GUICmdReqCopiedForSave::Load(QIODevice *f)
{
    if(::Load(f,SelectTimeIndex)==false){
        return false;
    }
    return true;
}
bool	GUICmdReqCopiedForSave::Save(QIODevice *f)
{
    if(::Save(f,SelectTimeIndex)==false){
        return false;
    }
    return true;
}

void	GUICmdReqCopiedForSave::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    LayersBase	*Base=GetLayersBase();
    GUICmdAckCopiedForSave	*SendBack=GetSendBack(GUICmdAckCopiedForSave,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
    int32	N=0;
    for(ClipboardAlgorithm *L=Base->GetClipboardDatas()->GetFirst();L!=NULL;L=L->GetNext()){
        if(L->GetCreatedTime()==SelectTimeIndex){
            N++;
        }
    }
    QBuffer	FBuff(&SendBack->Buff);
    FBuff.open(QIODevice::WriteOnly);
    ::Save(&FBuff,N);
    ::Save(&FBuff,SelectTimeIndex);
    for(ClipboardAlgorithm *L=Base->GetClipboardDatas()->GetFirst();L!=NULL;L=L->GetNext()){
        if(L->GetCreatedTime()==SelectTimeIndex){
            L->Save(localPage,&FBuff);
        }
    }
    SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
    CloseSendBack(SendBack);
}

bool	GUICmdAckCopiedForSave::Load(QIODevice *f)
{
    if(::Load(f,Buff)==false){
        return false;
    }
    return true;
}
bool	GUICmdAckCopiedForSave::Save(QIODevice *f)
{
    if(::Save(f,Buff)==false){
        return false;
    }
    return true;
}

void	GUICmdAckCopiedForSave::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

//===========================================================================================

bool	GUICmdReqCopiedForDelete::Load(QIODevice *f)
{
    if(::Load(f,SelectTimeIndex)==false){
        return false;
    }
    return true;
}
bool	GUICmdReqCopiedForDelete::Save(QIODevice *f)
{
    if(::Save(f,SelectTimeIndex)==false){
        return false;
    }
    return true;
}

void	GUICmdReqCopiedForDelete::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
ReTry:;
    for(ClipboardAlgorithm *L=GetLayersBase()->GetClipboardDatas()->GetFirst();L!=NULL;L=L->GetNext()){
        if(L->GetCreatedTime()==SelectTimeIndex){
            GetLayersBase()->GetClipboardDatas()->RemoveList(L);
            SpecifiedBroadcasterDeletePasted	Packet;
            Packet.DeletedPointer=L;
            GetLayersBase()->GetMainWidget()->BroadcastSpecifiedDirectly(&Packet);
            delete	L;
            goto	ReTry;
        }
    }
}
//---------------------------------------------------------------------------------------------------------

bool	GUICmdSendCopiedForLoad::Load(QIODevice *f)
{
    if(::Load(f,Buff)==false){
        return false;
    }
    return true;
}
bool	GUICmdSendCopiedForLoad::Save(QIODevice *f)
{
    if(::Save(f,Buff)==false){
        return false;
    }
    return true;
}

void	GUICmdSendCopiedForLoad::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
    int	N=0;
    LayersBase	*Base=GetLayersBase();
    QBuffer	FBuff(&Buff);
    FBuff.open(QIODevice::ReadOnly);
    ::Load(&FBuff,N);
    XDateTime	SelectTimeIndex;
    ::Load(&FBuff,SelectTimeIndex);
    for(int i=0;i<N;i++){
        ClipboardAlgorithm *L=NULL;
        if(localPage!=0){
            for(ClipboardAlgorithm *h=Base->GetClipboardDatas()->GetFirst();h!=NULL;h=h->GetNext()){
                if(h->GetCreatedTime()==SelectTimeIndex){
                    L=h;
                    break;
                }
            }
        }
        if(L==NULL){
            L=new ClipboardAlgorithm(SelectTimeIndex,GetLayersBase());
            if(L->Load(localPage,&FBuff)==false){
                break;
            }
            Base->GetClipboardDatas()->AppendList(L,false);
        }
        else{
            if(L->Load(localPage,&FBuff)==false){
                break;
            }
        }
    }
}
