/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\EditParameter\EditParameter\EditParameter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EditParameterResource.h"

#include "EditParameter.h"
#include "ui_EditParameter.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include <QFile>
#include <QDir>
#include <QFileDialog>
#include <QListWidget>
#include <QListWidgetItem>
#include "FormScanStrategy.h"
#include "FormCommSetting.h"
#include "XDatabase.h"
#include "XDatabaseLoader.h"
#include "EditSyncGUIForm.h"
#include "EditPhaseForm.h"
#include "FormDirectionOnEachPage.h"
#include "EditGUILibResource.h"
#include "ShareMasterDataForm.h"
#include "XDatabase.h"
#include "XDLLType.h"
#include "swap.h"
#include "mtTBarGraph.h"
#include "XDataInExe.h"
#include "XShadowControlInterface.h"
#include "XShadowTree.h"
#include "Regulus64System.h"
#include "XAlgorithmInterfaceDLL.h"
#include "XAlgorithmBase.h"
#include "ComponentParameterDialog.h"
#include "EditEachPageLocalDialog.h"

extern	int	LanguageCode;
extern	LangSolverNew	LangSolverGUILib;


EditParameter::EditParameter(LayersBase *base
                             ,ParamComm	*ParamCommData
                             ,QWidget *parent) :
    QMainWindow(parent),ServiceForLayers(base)
    ,ui(new Ui::EditParameter)
    ,WOutlineOffsetGrid(this)
{
    ui->setupUi(this);

    LangEPSolver.SetLanguage(base->GetLanguagePackageData(),LanguageCode);
    LangEPSolver.SetUI(this);
    LangSolverGUILib.SetLanguage(base->GetLanguagePackageData(),LanguageCode);

    ui->tabWidget->setCurrentIndex(0);

    //--------------------------------------------------------------------

    WTab = new WEditParameterTab(GetLayersBase()->GetParamGlobal() ,-1,ui->frameGlobalParam);

    GlobalParamLoadedFileName=GetLayersBase()->GetParamGlobal()->GetSavedFileName();
    ui->lineEditGlobalParam->setText(GlobalParamLoadedFileName);
    QFile	F(GetLayersBase()->GetParamGlobal()->GetSavedFileName());
    if(F.open(QIODevice::ReadOnly)==true){
        if(WTab->Load(&F)==true){
            WTab->ShowToWindow();
        }
    }
    //--------------------------------------------------------------------
    WStrategy=new FormScanStrategy(GetLayersBase(),ui->frameFormStrategy);
    ui->lineEditStrategy->setText(GlobalParamLoadedFileName);

    //--------------------------------------------------------------------
    WCommSetting	=new FormCommSetting(GetLayersBase(),ui->frameFormComm);
    CommParamLoadedFileName=ParamCommData->GetSavedFileName();
    ui->lineEditComm->setText(CommParamLoadedFileName);
    QFile	Fc(ParamCommData->GetSavedFileName());
    if(Fc.open(QIODevice::ReadOnly)==true){
        GetParamComm()->LoadParam(&Fc);
        WCommSetting->Show();
    }

    //--------------------------------------------------------------------
    ui->lineEditOutlineOffsetParam->setText(GlobalParamLoadedFileName);
    OutlineOffset=NULL;
    LastPhase=-1;

    WOutlineOffsetGrid.setParent(ui->frameOutlineOffsetGrid);
    WOutlineOffsetGrid.SetColumnCount(3);
    WOutlineOffsetGrid.move(0,0);
    WOutlineOffsetGrid.resize(ui->frameOutlineOffsetGrid->width(),ui->frameOutlineOffsetGrid->height());
    WOutlineOffsetGrid.SetTopHeader(0, QString(/**/"Page"));
    WOutlineOffsetGrid.SetTopHeader(1, QString(/**/"X Pos"));
    WOutlineOffsetGrid.SetTopHeader(2, QString(/**/"Y Pos"));
    WOutlineOffsetGrid.setColumnWidth(0,70);
    WOutlineOffsetGrid.setColumnWidth(1,60);
    WOutlineOffsetGrid.setColumnWidth(2,60);

    //--------------------------------------------------------------------
    ui->tableWidgetTransfer->setColumnWidth(0,240);
    ui->tableWidgetTransfer->setColumnWidth(1,240);
	ui->tableWidgetTransfer->setColumnWidth(2,70);

    //--------------------------------------------------------------------
    ui->tableWidgetFilter->setColumnWidth(0,70);
    ui->tableWidgetFilter->setColumnWidth(1,240);

    ui->lineEditFilter->setText(GlobalParamLoadedFileName);
    FilterFileNames=GetLayersBase()->GetParamGlobal()->FilterBankFileNames;
    LoadAndShowFilter();

    WEditSyncGUIForm=NULL;
    WEditPhaseForm	=NULL;
    WFormDirectionOnEachPage=NULL;
    //--------------------------------------------------------------------
    WShareMasterDataForm	=new ShareMasterDataForm(GetLayersBase(),ui->frameFormShareMaster);
    WShareMasterDataForm->show();

    //--------------------------------------------------------------------
    WEditScanPhaseNumber	=new EditScanPhaseNumber(GetLayersBase(),ui->frameScanPhase);
    WEditScanPhaseNumber->show();

    ExecuteAfterGlobalParam();

    //--------------------------------------------------------------------
    WEditSyncGUIForm		=new EditSyncGUIForm(GetLayersBase(),ui->frameFormSyncGUI);

    //--------------------------------------------------------------------
    GetLayersBase()->LoadFilterDef();
    WEditPhaseForm			=new EditPhaseForm(GetLayersBase(),ui->frameFormPhase);

    //--------------------------------------------------------------------
    WFormDirectionOnEachPage=new FormDirectionOnEachPage(GetLayersBase(),ui->frameFormImageDir);
    ui->lineEditImageDir->setText(GlobalParamLoadedFileName);
	
	//--------------------------------------------------------------------

	LoadShowShadow();

	//--------------------------------------------------------------------
    {
        QString APath=GetLayersBase()->GetSystemPath()
                   +QDir::separator()
                   +QString(DefAlgorithmPath);
        QDir    cd(APath);
        QStringList nameFilters;
        nameFilters.append(QString("*.")+ComponentExtName);
        AlgorithmFileNames=cd.entryList(nameFilters);
        ui->listWidgetAlgorithmList->addItems(AlgorithmFileNames);
        DLL=NULL;
        DLLInst=NULL;
    }

	InitialImageTable();
    connect(ui->bgRedBrightnessGraph,SIGNAL(SignalChanged(void))	,this,SLOT(SlotChanged(void)));
}

EditParameter::~EditParameter()
{
    delete ui;
    delete	WTab;
}

void	EditParameter::ExecuteAfterGlobalParam(void)
{
    ui->lineEditGlobalParam			->setText(GlobalParamLoadedFileName);
    ui->lineEditStrategy				->setText(GlobalParamLoadedFileName);
    ui->lineEditOutlineOffsetParam	->setText(GlobalParamLoadedFileName);
    ui->lineEditPhase				->setText(GlobalParamLoadedFileName);
    ui->lineEditImageDir				->setText(GlobalParamLoadedFileName);

    QString	Msg;
    GetLayersBase()->InitialDatabaseLoader(Msg);
    GetLayersBase()->InitialCreatePages(false);

    if(WTab!=NULL)
        WTab->ShowToWindow();
    if(WStrategy!=NULL){
        WStrategy->CopyFromOriginal(GetLayersBase());
        WStrategy->ShowToWindow();
    }
    FilterFileNames=GetLayersBase()->GetParamGlobal()->FilterBankFileNames;
    LoadAndShowFilter();
    if(WEditSyncGUIForm!=NULL)
        WEditSyncGUIForm->SetFileNameFromGlobalParam();

    GetLayersBase()->LoadFilterDef();
    if(WEditPhaseForm!=NULL)
        WEditPhaseForm->SetGrid();
    if(WFormDirectionOnEachPage!=NULL){
        WFormDirectionOnEachPage->CopyFromOriginal(GetLayersBase());
        WFormDirectionOnEachPage->ShowGrid();
    }
    if(WEditScanPhaseNumber!=NULL){
        WEditScanPhaseNumber->Show();
    }
	ShowTransfer();
}

void EditParameter::on_CancelButton_clicked()
{
    close();
}

void EditParameter::on_SaveButton_clicked()
{
    QString	 fileName=GetLayersBase()->LGetSaveFileName (NULL, WTab->GetDataText(), QString(), QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        QFile	F(fileName);
        if(F.open(QIODevice::WriteOnly)==true){
            WTab->LoadFromWindow();
            WStrategy->LoadFromWindow();
            GetLayersBase()->GetParamGlobal()->FilterBankFileNames=FilterFileNames;
            WFormDirectionOnEachPage->LoadFromWindow();

            WTab->Save(&F);
        }
    }
}

void EditParameter::on_LoadButton_clicked()
{
    QString	 fileName=GetLayersBase()->LGetOpenFileName(NULL, WTab->GetDataText(), QString(), QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        GlobalParamLoadedFileName=fileName;

        QFile	F(fileName);
        if(F.open(QIODevice::ReadOnly)==true){
            WTab->Load(&F);
            ExecuteAfterGlobalParam();
            GetLayersBase()->LoadFilterDef();
        }
        ui->lineEditFilter->setText(GetLayersBase()->GetFilterDefFileName());
    }
}

void EditParameter::on_UpdateDefaultButton_clicked()
{
    //QString	FileName=WTab->GetParamBase()->GetSavedFileName();
    //QFile	F(FileName);
    QFile	F(GlobalParamLoadedFileName);
    if(F.open(QIODevice::WriteOnly)==true){
        WTab->LoadFromWindow();
        WStrategy->LoadFromWindow();
        GetLayersBase()->GetParamGlobal()->FilterBankFileNames=FilterFileNames;
        WFormDirectionOnEachPage->LoadFromWindow();

        WTab->Save(&F);
    }
}

//================================================================================

void EditParameter::on_pushButtonLoadFileStrategy_clicked()
{
    on_LoadButton_clicked();
}

void EditParameter::on_pushButtonOverWriteFileStrategy_clicked()
{
    on_UpdateDefaultButton_clicked();
}

void EditParameter::on_pushButtonSaveFileStrategy_clicked()
{
    on_SaveButton_clicked();
}
//================================================================================

void EditParameter::on_pushButtonLoadFileComm_clicked()
{
    QString	 fileName=GetLayersBase()->LGetOpenFileName(NULL
                                    , /**/"Load Comm param file", QString()
                                    , QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        CommParamLoadedFileName=fileName;
        ui->lineEditComm->setText(CommParamLoadedFileName);
        QFile	Fc(fileName);
        if(Fc.open(QIODevice::ReadOnly)==true){
            GetParamComm()->LoadParam(&Fc);
            WCommSetting->Show();
        }
    }
}

void EditParameter::on_pushButtonOverWriteFileComm_clicked()
{
    QFile	F(CommParamLoadedFileName);
    if(F.open(QIODevice::WriteOnly)==true){
        WCommSetting->LoadFromWindow();
        GetParamComm()->SaveParam(&F);
    }
}

void EditParameter::on_pushButtonSaveFileComm_clicked()
{
    QString	 fileName=GetLayersBase()->LGetSaveFileName (NULL
                                        , /**/"Save Comm param file"
                                        , QString()
                                        , QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        QFile	F(fileName);
        if(F.open(QIODevice::WriteOnly)==true){
            WCommSetting->LoadFromWindow();
            GetParamComm()->SaveParam(&F);
        }
    }
}
//================================================================================

void	OutlineOffsetGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    int	Phase=EParent->GetCurrentPhaseInOutlineOffset();
    if(Phase>=0){
        OutlineOffsetInPage	p=EParent->OutlineOffset->GetData(Phase,row);
        if(col==1){
            bool	ok;
            p.Dx=value.toInt(&ok);
            if(ok==false)
                return;
        }
        if(col==2){
            bool	ok;
            p.Dy=value.toInt(&ok);
            if(ok==false)
                return;
        }
        EParent->OutlineOffset->SetData(Phase,row,p);
    }
}

void	OutlineOffsetGrid::GetValue(int row ,int col,QVariant &value)
{
    if(col==0){
        value=QVariant(QString(/**/"Page ")+QString::number(row+1));
    }
    else{
        int	Phase=EParent->GetCurrentPhaseInOutlineOffset();
        if(Phase>=0){
            OutlineOffsetInPage	p=EParent->OutlineOffset->GetData(Phase,row);

            if(col==1){
                value=(int)p.Dx;
            }
            else if(col==2){
                value=(int)p.Dy;
            }
        }
    }
}

void EditParameter::on_pushButtonOutlineOffsetParam_clicked()
{
    QString	 fileName=GetLayersBase()->LGetOpenFileName(NULL, WTab->GetDataText(), QString(), QString(/**/"dat(*.dat);;AllFile(*.*)"));
    if(fileName.isEmpty()==false){
        GlobalParamLoadedFileName=fileName;
        QFile	F(fileName);
        if(F.open(QIODevice::ReadOnly)==true){
            WTab->Load(&F);
            ExecuteAfterGlobalParam();
        }
        ui->lineEditFilter->setText(GetLayersBase()->GetFilterDefFileName());
    }
}

int		EditParameter::GetCurrentPhaseInOutlineOffset(void)
{
    int	Phase=ui->comboBoxOutlineOffsetPhase->currentIndex();
    return Phase;
}

void EditParameter::on_pushButtonConnectOutlineOffset_clicked()
{
    LocalDatabaseBasicClass	*KDatabase=new LocalDatabaseBasicClass(GetLayersBase()->GetDatabaseLoader(false)
                                                                    ,GetParamGlobal()->LocalDatabase_FileName
                                                                    ,GetParamGlobal()->LocalDatabase_HostName
                                                                    ,GetParamGlobal()->LocalDatabase_Port
                                                                    ,GetParamGlobal()->TransDatabaseIP
                                                                    ,GetParamGlobal()->TransDatabasePort);

    if(KDatabase->IsExistDatabase()==false){
        QMessageBox Q( /**/"Error"
                    , LangEPSolver.GetString(EditParameter_LS,LID_13)/*"No database file"*/, QMessageBox::Critical
                    , QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
        Q.exec();
        return;
    }
    if(GetLayersBase()->OpenDatabase(*KDatabase)==false){
        QMessageBox Q( /**/"Error"
                    , LangEPSolver.GetString(EditParameter_LS,LID_14)/*"Could not open database"*/, QMessageBox::Critical
                    , QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
        Q.exec();
        return;
    }
    GetLayersBase()->LoadLevelFolderContainerFromDB();
    
    ui->pushButtonConnectOutlineOffset->setEnabled(false);

    QString	S=QString(/**/"SELECT MACHINEID,NAME FROM MACHINE");
    QSqlQuery query(S ,*GetLayersBase()->GetDataBase());
    int	L=0;
    while(query.next ()==true){
        MachineList	*m=new MachineList();
        m->MachineID	=query.value(query.record().indexOf(/**/"MACHINEID"	)).toInt();
        m->MachineName	=query.value(query.record().indexOf(/**/"NAME"	)).toString();
        MachineContainer.AppendList(m);
        ui->tableWidgetMachine->setRowCount(L+1);
        SetDataToTable(ui->tableWidgetMachine ,0,L,m->MachineID);
        SetDataToTable(ui->tableWidgetMachine ,1,L,m->MachineName);
        L++;
    }
    OutlineOffset=new OutlineOffsetInBlob(GetLayersBase());
    OutlineOffset->Initial();
}

void EditParameter::on_tableWidgetMachine_clicked(const QModelIndex &index)
{
    int	Row=ui->tableWidgetMachine->currentRow();
    if(Row<0)
        return;
    MachineList	*m=MachineContainer.GetItem(Row);
    if(m==NULL)
        return;
    if(GetLayersBase()->GetDatabaseLoader()->G_SQLLoadOutlineOfset(*GetLayersBase()->GetDataBase()
                                                                    ,m->MachineID
                                                                    ,OutlineOffset)==true){

    }
    else{
        QMessageBox Q( /**/"Error"
                    , LangEPSolver.GetString(EditParameter_LS,LID_15)/*"Invalid Outline Offset data"*/, QMessageBox::Critical
                    , QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
        Q.exec();
        if(OutlineOffset!=NULL){
            delete	OutlineOffset;
        }
        OutlineOffset=new OutlineOffsetInBlob(GetLayersBase());
        OutlineOffset->Initial();
    }
    ui->comboBoxOutlineOffsetPhase->clear();
    int phase;
    for(phase=0;phase<OutlineOffset->GetPhaseCount();phase++){
        ui->comboBoxOutlineOffsetPhase->addItem(QString::number(phase));
    }
    for(;phase<GetPhaseNumb();phase++){
        ui->comboBoxOutlineOffsetPhase->addItem(QString::number(phase));
    }

    SetOutlineOffsetGrid();
    ui->comboBoxOutlineOffsetPhase->setCurrentIndex(0);
}

void EditParameter::on_comboBoxOutlineOffsetPhase_currentIndexChanged(int index)
{
    if(OutlineOffset!=NULL){
        SetOutlineOffsetGrid();
        int	Phase=GetCurrentPhaseInOutlineOffset();
        LastPhase=Phase;
    }
}

void	EditParameter::SetOutlineOffsetGrid(void)
{
    WOutlineOffsetGrid.InitialGrid();
    int	Phase=GetCurrentPhaseInOutlineOffset();
    if(Phase<0)
        return;
    int	PageCount=OutlineOffset->GetPageCount(Phase);
    if(PageCount<=0){
        OutlineOffset->Reallocate();
        PageCount=OutlineOffset->GetPageCount(Phase);
    }
    WOutlineOffsetGrid.SetRowCount(PageCount);

    for(int r=0;r<PageCount;r++){
        OutlineOffsetInPage	p=OutlineOffset->GetData(Phase,r);

        WMultiGrid::CellData *L0=WOutlineOffsetGrid.GetData(r ,0);
        L0->Value	=QVariant(QString(/**/"Page ")+QString::number(r+1));
        L0->CType	=WMultiGrid::_CType_Label;
        L0->MaxValue	=9999;
        L0->MinValue	=0;
        L0->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        WMultiGrid::CellData *L1=WOutlineOffsetGrid.GetData(r ,1);
        L1->Value	=(int)p.Dx;
        L1->CType	=WMultiGrid::_CType_SpinBox;
        L1->MaxValue	=9999999;
        L1->MinValue	=-9999999;
        L1->Alignment=Qt::AlignVCenter | Qt::AlignRight;

        WMultiGrid::CellData *L2=WOutlineOffsetGrid.GetData(r ,2);
        L2->Value	=(int)p.Dy;
        L2->CType	=WMultiGrid::_CType_SpinBox;
        L2->MaxValue	=9999999;
        L2->MinValue	=-9999999;
        L2->Alignment=Qt::AlignVCenter | Qt::AlignRight;
    }

    for(int r=0;r<PageCount;r++){
        WOutlineOffsetGrid.SetLeftHeader(r,QString::number(r+1));
    }

    WOutlineOffsetGrid.ShowGrid();
}

void EditParameter::on_pushButtonUpdateOutlineOffset_clicked()
{
    int	Row=ui->tableWidgetMachine->currentRow();
    if(Row<0)
        return;
    MachineList	*m=MachineContainer.GetItem(Row);
    if(m==NULL)
        return;
    if(GetLayersBase()->GetDatabaseLoader()->G_SQLSaveOutlineOfset(*GetLayersBase()->GetDataBase()
                                                                    ,m->MachineID
                                                                    ,OutlineOffset)==false){
        QMessageBox Q( /**/"Error"
                    , LangEPSolver.GetString(EditParameter_LS,LID_16)/*"Could not update"*/, QMessageBox::Critical
                    , QMessageBox::Ok , QMessageBox::NoButton, QMessageBox::NoButton);
        Q.exec();
        return;
    }
}
void EditParameter::on_pushButtonOutlineOffsetUseCurrent_clicked()
{
    OutlineOffset=new OutlineOffsetInBlob(GetLayersBase());
    OutlineOffset->Initial();
    ui->comboBoxOutlineOffsetPhase->clear();
    for(int phase=0;phase<OutlineOffset->GetPhaseCount();phase++){
        ui->comboBoxOutlineOffsetPhase->addItem(QString::number(phase));
    }
    SetOutlineOffsetGrid();
}

void EditParameter::on_pushButtonOutlineOffsetTileX_clicked()
{
    int	Phase=GetCurrentPhaseInOutlineOffset();
    if(Phase<0)
        return;
    int	PageCount=OutlineOffset->GetPageCount(Phase);

    for(int r=0;r<PageCount;r++){
        OutlineOffsetInPage	p=OutlineOffset->GetData(Phase,r);
        p.Dx=r*GetDotPerLine(r);
        OutlineOffset->SetData(Phase,r,p);
    }
    SetOutlineOffsetGrid();
}

void EditParameter::on_pushButtonTileY_clicked()
{
    int	Phase=GetCurrentPhaseInOutlineOffset();
    if(Phase<0)
        return;
    int	PageCount=OutlineOffset->GetPageCount(Phase);

    for(int r=0;r<PageCount;r++){
        OutlineOffsetInPage	p=OutlineOffset->GetData(Phase,r);
        p.Dy=r*GetMaxLines(r);
        OutlineOffset->SetData(Phase,r,p);
    }
    SetOutlineOffsetGrid();
}

//================================================================================
void EditParameter::ShowTransfer(void)
{
	int	N=GetParamGlobal()->GetRemoteTransferCount();
	ui->tableWidgetTransfer->setRowCount(N);
	for(int Row=0;Row<N;Row++){
		RemoteTransferList	*L=GetParamGlobal()->GetRemoteTransfer(Row);
		::SetDataToTable(ui->tableWidgetTransfer, 0, Row, L->Name					,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetTransfer, 1, Row, L->IPAddress				,Qt::ItemIsEditable);
		::SetDataToTable(ui->tableWidgetTransfer, 2, Row, QString::number(L->Port)	,Qt::ItemIsEditable);
	}
}

void	EditParameter::GetTransferFromWindow(void)
{
	int	N=ui->tableWidgetTransfer->rowCount();
	for(int Row=0;Row<N;Row++){
		RemoteTransferList	*L=GetParamGlobal()->GetRemoteTransfer(Row);
		if(L!=NULL){
			L->Name		=::GetDataToTable(ui->tableWidgetTransfer, 0, Row);
			L->IPAddress=::GetDataToTable(ui->tableWidgetTransfer, 1, Row);
			L->Port		=::GetDataToTable(ui->tableWidgetTransfer, 2, Row).toInt();
		}
	}
}

//================================================================================

void EditParameter::on_pushButtonLoadFilesFilter_clicked()
{
    QStringList FileList=GetLayersBase()->LGetOpenFileNames (0
                                        , LangEPSolver.GetString(EditParameter_LS,LID_9)/*"Filter file names"*/
                                        , LangEPSolver.GetString(EditParameter_LS,LID_10)/*""*/
                                        , /**/"Filter(*.dll *.so)");
    for(int i=0;i<FileList.count();i++){
        FilterFileNames.append(FileList.value(i));
        LoadAndShowFilter();
    }
}

void EditParameter::LoadAndShowFilter(void)
{
    ui->tableWidgetFilter->setRowCount(FilterFileNames.count());

    for(int r=0;r<FilterFileNames.count();r++){
        QTableWidgetItem *W;
        W=ui->tableWidgetFilter->item ( r, 0);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetFilter->setItem ( r, 0,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(LangEPSolver.GetString(EditParameter_LS,LID_12)/*"Filter "*/+QString::number(r+1));

        W=ui->tableWidgetFilter->item ( r, 1);
        if(W==NULL){
            W=new QTableWidgetItem();
            ui->tableWidgetFilter->setItem ( r, 1,W);
            W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
        }
        W->setText(FilterFileNames.value(r));
    }
}

void EditParameter::on_pushButtonOverWriteFileFilter_clicked()
{
    on_UpdateDefaultButton_clicked();
}

void EditParameter::on_pushButtonSaveFileFilter_clicked()
{
    on_SaveButton_clicked();
}

void EditParameter::on_pushButtonFilterUp_clicked()
{
    int	Index=ui->tableWidgetFilter->currentRow();
    if(Index>0){
        Swap(FilterFileNames,Index,Index-1);
        LoadAndShowFilter();
    }
}

void EditParameter::on_pushButtonFilterDown_clicked()
{
    int	Index=ui->tableWidgetFilter->currentRow();
    if((Index+1)<ui->tableWidgetFilter->rowCount()){
        Swap(FilterFileNames,Index,Index+1);
        LoadAndShowFilter();
    }
}

void EditParameter::on_pushButtonFilterDelete_clicked()
{
    int	Index=ui->tableWidgetFilter->currentRow();
    if(Index>=0){
        FilterFileNames.removeAt(Index);
        LoadAndShowFilter();
    }
}
//================================================================================

void EditParameter::on_pushButtonLoadFileImageDir_clicked()
{
    on_LoadButton_clicked();
}

void EditParameter::on_pushButtonOverWriteFileImageDir_clicked()
{
    on_UpdateDefaultButton_clicked();
}

void EditParameter::on_pushButtonSaveFileImageDir_clicked()
{
    on_SaveButton_clicked();
}


void EditParameter::on_pushButtonOverWriteScanPhase_clicked()
{
    on_UpdateDefaultButton_clicked();
}

void EditParameter::on_pushButtonSaveFileScanPhase_clicked()
{
    on_SaveButton_clicked();
}

//================================================================================
#define	CamDepth	256

void EditParameter::InitialImageTable(void)
{
    ui->comboBoxPhase->clear();
    for(int i=0;i<GetLayersBase()->GetPhaseNumb();i++){
        ui->comboBoxPhase->addItem(QString(/**/"Phase-")+QString::number(i));
    }
    ui->comboBoxPage->clear();
    for(int i=0;i<GetLayersBase()->GetPageNumb();i++){
        ui->comboBoxPage->addItem(QString(/**/"Page-")+QString::number(i));
    }
    int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
    ui->comboBoxLayer->clear();
    for(int i=0;i<LayerNumb;i++){
        ui->comboBoxLayer->addItem(QString(/**/"Layer-")+QString::number(i)+QString(/**/" ")+GetParamGlobal()->GetLayerName(i));
    }

    for(int x=1;x<CamDepth;x++){
        ImageTable[x]=x;
    }
    ShowImageTable(0,0,0);
}

void EditParameter::ShowImageTable(int Phase ,int Page ,int Layer)
{
    if(Phase<0 || Page<0 || Layer<0
    || GetLayersBase()==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)==NULL)
        return;
    DataInLayer	*Ly=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer);
    for(int x=0;x<CamDepth;x++){
        ui->bgRedBrightnessGraph->SetYData(x,Ly->CData.RBrightTable[x]);		//RedGraph
    }
}
void EditParameter::on_comboBoxPhase_currentIndexChanged(int index)
{
    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    ShowImageTable(Phase ,Page ,Layer);
}

void EditParameter::on_comboBoxPage_currentIndexChanged(int index)
{
    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    ShowImageTable(Phase ,Page ,Layer);
}

void EditParameter::on_comboBoxLayer_currentIndexChanged(int index)
{
    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    ShowImageTable(Phase ,Page ,Layer);
}

void EditParameter::on_cbRedGraphType_currentIndexChanged(int index)
{

}

void EditParameter::on_pbRedUpdate_clicked()
{
    //Acquisition of value
    RedFirstPoint	=ui->sbRedFirstPoint			->value();
    RedSecondPoint	=ui->sbRedSecondPoint		->value();
    RedFirstX		=ui->sbRedFirstXCoordinates	->value();
    RedFirstY		=ui->sbRedFirstYCoordinates	->value();
    RedSecondX		=ui->sbRedSecondXCoordinates	->value();
    RedSecondY		=ui->sbRedSecondYCoordinates	->value();

    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    if(GetLayersBase()==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)==NULL)
        return;

    DataInLayer	*Ly=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer);
    int	gIndex=ui->cbRedGraphType->currentIndex();
    if(gIndex==Default){
    }
    //Straight Line
    else if(gIndex==StraightLine){
        //Error processing
        if(RedSecondX-RedFirstX<=0){
            QMessageBox::critical(this, tr("Error"),tr("Coordinates are not correct!"));
            return;
        }
        //Inclination:(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX)
        for(int x=0;x<=RedFirstX;x++)
            Ly->CData.RBrightTable[x]=max(0,RedFirstY);
        int RedB=RedFirstY-(RedFirstX*(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX));
        for(int x=RedFirstX+1;x<RedSecondX;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=x*(RedSecondY-RedFirstY)/(RedSecondX-RedFirstX)+RedB;
            }
        }
        for(int x=RedSecondX;x<CamDepth;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=RedSecondY;
            }
        }
    }
    //Hight Pass
    else if(gIndex==HightPass){
        for(int x=0;x<RedFirstPoint;x++)
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=0;
            }
        for(int x=RedFirstPoint;x<CamDepth;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=255;
            }
        }
    }
    //Low Pass
    else if(gIndex==LowPass){
        for(int x=0;x<RedFirstPoint;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=255;
            }
        }
        for(int x=RedFirstPoint;x<CamDepth;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=0;
            }
        }
    }
    //UpDown Pass
    else if(gIndex==UpDownPass){
        for(int x=0;x<RedFirstPoint;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=0;
            }
        }
        for(int x=RedFirstPoint;x<RedSecondPoint;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=255;
            }
        }
        for(int x=RedSecondPoint;x<CamDepth;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=0;
            }
        }
    }
    //DownUp Pass
    else if(gIndex==DownUpPass){
        for(int x=0;x<RedFirstPoint;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=255;
            }
        }
        for(int x=RedFirstPoint;x<RedSecondPoint;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=0;
            }
        }
        for(int x=RedSecondPoint;x<CamDepth;x++){
            if(0<=x && x<CamDepth){
                Ly->CData.RBrightTable[x]=255;
            }
        }
    }
    //Shigmoid Curve
    else if(gIndex==ShigmoidCurve){
        for(int x=0;x<CamDepth;x++){
            Ly->CData.RBrightTable[x]=256/(1+exp((double)(RedFirstPoint-x)));
        }
    }
    //Logarithm
    else if(gIndex==Logarithm){
        for(int x=1;x<CamDepth;x++){
            Ly->CData.RBrightTable[x]=46*log((double)x);
        }
        Ly->CData.RBrightTable[255]=255;
    }
    ShowImageTable(Phase ,Page ,Layer);
}

void EditParameter::on_pushButtonCopy_clicked()
{
    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    if(Phase<0 || Page<0 || Layer<0
    || GetLayersBase()==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)==NULL)
        return;

    DataInLayer	*Ly=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer);
    for(int x=0;x<CamDepth;x++){
        ImageTable[x]=Ly->CData.RBrightTable[x];
    }
}

void EditParameter::on_pushButtonPaste_clicked()
{
    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    if(Phase<0 || Page<0 || Layer<0
    || GetLayersBase()==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)==NULL)
        return;

    DataInLayer	*Ly=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer);
    for(int x=0;x<CamDepth;x++){
        Ly->CData.RBrightTable[x]=ImageTable[x];
    }
    ShowImageTable(Phase ,Page ,Layer);
}

void EditParameter::on_pushButtonOverWriteImageTable_clicked()
{
    GetLayersBase()->SaveAttrDefault();
}
void	EditParameter::SlotChanged(void)
{
    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    if(Phase<0 || Page<0 || Layer<0
    || GetLayersBase()==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)==NULL)
        return;

    DataInLayer	*Ly=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)->GetLayerData(Layer);
    for(int x=0;x<CamDepth;x++){
        Ly->CData.RBrightTable[x]	=ui->bgRedBrightnessGraph->GetYData(x);
    }
}

void EditParameter::on_pushButtonLoadAgainImageTable_clicked()
{
    GetLayersBase()->LoadAttrDefault();

    int	Phase	=ui->comboBoxPhase	->currentIndex();
    int	Page	=ui->comboBoxPage	->currentIndex();
    int	Layer	=ui->comboBoxLayer	->currentIndex();
    if(Phase<0 || Page<0 || Layer<0
    || GetLayersBase()==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)==NULL
    || GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(Page)==NULL)
        return;

    ShowImageTable(Phase ,Page ,Layer);
}

void EditParameter::resizeEvent(QResizeEvent *e)
{
	ui->frameBottom->setGeometry(0,height()-ui->frameBottom->height(),width(),ui->frameBottom->height());
	ui->CancelButton->move((width()-ui->CancelButton->width())/2,6);
	ui->tabWidget->resize(width()-20,height()-10-ui->frameBottom->height());

	ui->frameGlobalParam->resize(ui->tabWidget->width()-20,ui->tabWidget->height()-100);
	int	WB=(ui->tabWidget->width()-(ui->pushButtonEachPage->width()+ui->SaveButton->width()+ui->UpdateDefaultButton->width()+ui->LoadButton->width()))/5;
	ui->pushButtonEachPage->move(WB
						        ,ui->tabWidget->height()-60);
	ui->SaveButton          ->move(WB+ui->pushButtonEachPage->width()+WB
						        ,ui->tabWidget->height()-60);
	ui->UpdateDefaultButton->move(WB+ui->pushButtonEachPage->width()+WB+ui->SaveButton->width()+WB
								  ,ui->tabWidget->height()-60);
	ui->LoadButton->move(WB+ui->pushButtonEachPage->width()+WB+ui->SaveButton->width()+WB+ui->UpdateDefaultButton->width()+WB
						 ,ui->tabWidget->height()-60);
	WTab->resize(ui->frameGlobalParam->width(),ui->frameGlobalParam->height()-30);
}

void EditParameter::on_pushButtonOverWriteFileTransfer_clicked()
{
	GetTransferFromWindow();
	on_UpdateDefaultButton_clicked();
}

void EditParameter::on_pushButtonTransferPlus_clicked()
{
	RemoteTransferList n;
	GetParamGlobal()->AddRemoteTransfer(n);
	ShowTransfer();
}

void EditParameter::on_pushButtonTransferMinus_clicked()
{
	int	Row=ui->tableWidgetTransfer->currentRow();
	if(Row<0)
		return;
	GetParamGlobal()->RemoveRemoteTransfer(Row);
	ShowTransfer();
}

//================================================================================

void	EditParameter::LoadShowShadow(void)
{
	::SetColumnWidthInTable(ui->tableWidgetShadow ,0, 50);
	::SetColumnWidthInTable(ui->tableWidgetShadow ,1, 50);

	QFile	File(GetLayersBase()->GetParamGlobal()->ShadowTreeDefFileName);
	if(File.open(QIODevice::ReadOnly)==true){
		if(GetLayersBase()->GetParamGlobal()->ShadowParameterData.Load(&File)==true){
			ShowShadow();
		}
	}
}
void	EditParameter::ShowShadow(void)
{
	ui->tableWidgetShadow->setRowCount(GetLayersBase()->GetParamGlobal()->ShadowParameterData.GetCount());
	int	Row=0;
	for(ShadowParameter *a=GetLayersBase()->GetParamGlobal()->ShadowParameterData.GetFirst();a!=NULL;a=a->GetNext(),Row++){
		::SetDataToTable(ui->tableWidgetShadow, 0, Row, a->ShadowControlDLLFileName);
		::SetDataToTable(ui->tableWidgetShadow, 1, Row, a->ShadowGlobalFileName);
	}
}

void EditParameter::on_pushButtonAddShadow_clicked()
{
	ShadowParameter	*a=new ShadowParameter();
	GetLayersBase()->GetParamGlobal()->ShadowParameterData.AppendList(a);
	ShowShadow();
}

void EditParameter::on_pushButtonRemoveShadow_clicked()
{
	int	Row=ui->tableWidgetShadow->currentRow();
	if(Row<0)
		return;
	ShadowParameter	*a=GetLayersBase()->GetParamGlobal()->ShadowParameterData.GetItem(Row);
	if(a!=NULL){
		GetLayersBase()->GetParamGlobal()->ShadowParameterData.RemoveList(a);
		delete	a;
		ShowShadow();
	}
}

void EditParameter::on_pushButtonShadowControlDLLFileName_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr
												, "ShadowControl DLL file name"
												, QString()
												, /**/"DLL file(*.dll)");
	if(FileName.isEmpty()==false){
		ui->lineEditShadowControlDLLFileName->setText(FileName);
	}											
}

void EditParameter::on_pushButtonShadowGlobalFileName_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr
												, "Shadow Global.dat file name"
												, QString()
												, /**/"Dat(*.dat)");
	if(FileName.isEmpty()==false){
		ui->lineEditShadowGlobalFileName->setText(FileName);
	}	
}

void EditParameter::on_pushButtonShadowGUIFileName_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr
												, "ShadowControl GUI file name"
												, QString()
												, /**/"GUI file(*.gui)");
	if(FileName.isEmpty()==false){
		ui->lineEditShadowGUIFileName->setText(FileName);
	}	
}

void EditParameter::on_pushButtonShadowParamFileName_clicked()
{
	QString	FileName=QFileDialog::getOpenFileName(nullptr
												, "Shadow parameter file name"
												, QString()
												, /**/"Dat file(*.dat)");
	if(FileName.isEmpty()==false){
		ui->lineEditShadowParamFileName->setText(FileName);
	}	
}

void EditParameter::on_pushButtonShadowSetting_clicked()
{
	int	Row=ui->tableWidgetShadow->currentRow();
	if(Row<0)
		return;
	QString	ShadowParamFileName=ui->lineEditShadowParamFileName->text();
	if(ShadowParamFileName.isEmpty()==false){
		QString	DLLFileName=ui->lineEditShadowControlDLLFileName	->text();

		ShadowControlInterface	*a=new ShadowControlInterface(Row,GetLayersBase());
		int32 ErrorCode;
		if(a->LoadDLL(DLLFileName,ErrorCode)==true){
			ShadowTree	*s=a->Initial(Row,GetLayersBase()
										,GetLayersBase()->GetParamGlobal()->GetDefaultFileName()
										,/**/"");
			if(s!=NULL){
				{
					QFile	RFile(ShadowParamFileName);
					if(RFile.open(QIODevice::ReadOnly)==true){
						s->LoadShadowParam(&RFile);
					}
					a->ShowSetting(NULL);
				}
				{
					QFile	WFile(ShadowParamFileName);
					if(WFile.open(QIODevice::WriteOnly)==true){
						s->SaveShadowParam(&WFile);
					}
				}
			}
		}
		delete	a;
	}
    else{
           QMessageBox::warning(NULL,"Alert"
                                ,"No ShadowTree param file name");
    }

}

void EditParameter::on_pushButtonUpdateShadow_clicked()
{
	int	Row=ui->tableWidgetShadow->currentRow();
	if(Row<0)
		return;
	ShadowParameter	*a=GetLayersBase()->GetParamGlobal()->ShadowParameterData.GetItem(Row);
	if(a!=NULL){
		a->ShadowGlobalFileName		=ui->lineEditShadowGlobalFileName		->text();
		a->ShadowGUIFileName		=ui->lineEditShadowGUIFileName			->text();
		a->ShadowParamFileName		=ui->lineEditShadowParamFileName		->text();
		a->ShadowControlDLLFileName	=ui->lineEditShadowControlDLLFileName	->text();
        WTab->LoadFromWindow();
		QFile	File(GetLayersBase()->GetParamGlobal()->ShadowTreeDefFileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(GetLayersBase()->GetParamGlobal()->ShadowParameterData.Save(&File)==true){
				ShowShadow();
			}
		}
        else{
            QMessageBox::warning(NULL,"Alert"
                                ,"No ShadowTree-Def file name in ParamGlobal");
        }
	}
}

void EditParameter::on_tableWidgetShadow_itemSelectionChanged()
{
	int	Row=ui->tableWidgetShadow->currentRow();
	if(Row<0)
		return;
	ShadowParameter	*a=GetLayersBase()->GetParamGlobal()->ShadowParameterData.GetItem(Row);
	if(a!=NULL){
		ui->lineEditShadowGlobalFileName	->setText(a->ShadowGlobalFileName	);
		ui->lineEditShadowGUIFileName		->setText(a->ShadowGUIFileName		);
		ui->lineEditShadowParamFileName		->setText(a->ShadowParamFileName	);
		ui->lineEditShadowControlDLLFileName->setText(a->ShadowControlDLLFileName);
	}
}

void EditParameter::on_tableWidgetShadow_doubleClicked(const QModelIndex &index)
{
	on_pushButtonShadowSetting_clicked();
}

//================================================================================

void EditParameter::on_listWidgetAlgorithmList_itemSelectionChanged()
{
    int row=ui->listWidgetAlgorithmList->currentRow();
    QString AlgorithmFile=GetLayersBase()->GetSystemPath()
                            +QDir::separator()
                            +QString(DefAlgorithmPath)
                            +QDir::separator()
                            +AlgorithmFileNames[row];

	if(QLibrary::isLibrary(AlgorithmFile)==true){
        if(DLLInst!=NULL){
            delete  DLLInst;
            DLLInst=NULL;
        }
        if(DLL!=NULL){
            delete  DLL;
            DLL=NULL;
        }
		DLL=new AlgorithmDLLList(GetLayersBase());
		DLL->SetFileName(AlgorithmFile);
		if(DLL->LoadDLL(AlgorithmFile)==true){
		    DLLInst=new LogicDLL(GetLayersBase());
		    DLLInst->Set(DLL);
		    DLLInst->InitialName();
            QString    SavedDir=QDir::currentPath();
            QDir::setCurrent(GetLayersBase()->GetUserPath());
		    DLLInst->InitialAlloc(GetLayersBase());
            QDir::setCurrent(SavedDir);
	        ui->lineEditAlgorithmRoot->setText(DLLInst->GetDLLRoot())	;
	        ui->lineEditAlgorithmName->setText(DLLInst->GetDLLName())	;
        }
    }
}

void EditParameter::on_pushButtonShowAlgorithmParam_clicked()
{
    if(DLLInst!=NULL){
        ParamBase	*P=DLLInst->GetInstance();
        ComponentParameterDialog    D(P,GetLayersBase());
        D.setWindowTitle(QString(/**/"Algorithm Root:")
                         +DLLInst->GetDLLRoot()
                         +QString(/**/" Name:")
                         +DLLInst->GetDLLName());
        if(D.exec()==true){

			QFile	FAlgprithm(GetLayersBase()->GetUserPath()
							  +GetSeparator()
                              +P->GetSavedFileName());
			if(FAlgprithm.open(QIODevice::WriteOnly)==true){
				P->SaveParam(&FAlgprithm);
			}
        }
    }
}

//================================================================================

void EditParameter::on_pushButtonEachPage_clicked()
{
    WTab->LoadFromWindow();
    EditEachPageLocalDialog D(GetLayersBase());
    if(D.exec()==true){
        WTab->ShowToWindow();
    }
}

