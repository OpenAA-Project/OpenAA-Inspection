#include "PropertyRasterInspectionForm.h"
#include "ui_PropertyRasterInspectionForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyRasterInspectionPacket.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XRasterInspection.h"
#include "XRasterInspectionLibrary.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "EditLibraryDialog.h"
#include "XGeneralFunc.h"
#include "XStandardCommand.h"
#include <QMessageBox>
#include "XRememberer.h"

extern	const   char	*sRoot;
extern	const   char	*sName;

PropertyRasterInspectionForm::PropertyRasterInspectionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyRasterInspectionForm)
{
    ui->setupUi(this);

	ModeShowPDF=0;
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);

	if(BBase!=NULL){
		CmdCreateTempRasterInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	LLib->SetLibID(-1);

	::SetColumnWidthInTable(ui->tableWidgetList ,0, 17);
	::SetColumnWidthInTable(ui->tableWidgetList ,1, 17);
	::SetColumnWidthInTable(ui->tableWidgetList ,2, 17);
	::SetColumnWidthInTable(ui->tableWidgetList ,3, 32);
	::SetColumnWidthInTable(ui->tableWidgetList ,4, 17);

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyRasterInspectionForm::~PropertyRasterInspectionForm()
{
    delete ui;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}
RasterInspectionBase	*PropertyRasterInspectionForm::GetRasterInspectionBase(void)
{
	return (RasterInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"RasterInspection");
}

void PropertyRasterInspectionForm::on_pushButtonEditLibrary_clicked()
{
    EditLibraryDialog   D(GetLayersBase());
    D.exec();
	ShowLibList();
	ShowSelectedLibList();
}


void	PropertyRasterInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdRasterInspectionDrawAttr	*CmdRasterInspectionDrawAttrVar=dynamic_cast<CmdRasterInspectionDrawAttr *>(packet);
	if(CmdRasterInspectionDrawAttrVar!=NULL){
		if(ModeShowPDF==0){
			CmdRasterInspectionDrawAttrVar->ModeShowPDF			=false;
			CmdRasterInspectionDrawAttrVar->ModeShowItemImage	=false;
		}
		else if(ModeShowPDF==1){
			CmdRasterInspectionDrawAttrVar->ModeShowPDF			=true;
			CmdRasterInspectionDrawAttrVar->ModeShowItemImage	=false;
		}
		else if(ModeShowPDF==2){
			CmdRasterInspectionDrawAttrVar->ModeShowPDF			=false;
			CmdRasterInspectionDrawAttrVar->ModeShowItemImage	=true;
		}
		return;
	}
    CmdRasterInspectionDrawEnd  *CmdRasterInspectionDrawEndVar=dynamic_cast<CmdRasterInspectionDrawEnd *>(packet);
    if(CmdRasterInspectionDrawEndVar!=NULL){
        if(ui->toolButtonDrawMode->isChecked()==false){
			int	Row=ui->tableWidgetGeneratedLibList->currentRow();
			if(Row>=0){
				AlgorithmLibraryList	*L=SelectedLibList[Row];
				if(L!=NULL){
 					GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual RasterInspection");
					IntList PageList;
					GetLayersBase()->GetLocalPageFromArea(CmdRasterInspectionDrawEndVar->Area,PageList);
					for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
						int	page=P->GetValue();
						DataInPage	*pdata=GetLayersBase()->GetPageData(page);
						FlexArea	A=CmdRasterInspectionDrawEndVar->Area;
						pdata->ClipMoveAreaFromGlobal(A);
						if(A.GetPatternByte()>0){
							int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
							GUICmdSendAddManualRasterInspection	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
							Cmd.Area=A;
							Cmd.LibID=L->GetLibID();
							Cmd.SendOnly(GlobalPage,0);
						}
					}
					ShowList();
				}
			}
		}
        else{
			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(CmdRasterInspectionDrawEndVar->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=CmdRasterInspectionDrawEndVar->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdReqReferencePDFData	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
					GUICmdAckReferencePDFData	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
					RCmd.Area=A;
					if(RCmd.Send(GlobalPage,0,ACmd)==true){
						RasterInspectionBase	*ABase=GetRasterInspectionBase();
						if(ABase!=NULL){
							CmdRasterShowReferencePDF	Cmd(GetLayersBase());
							Cmd.RData=ACmd.Data;
							Cmd.Deletable=false;
							ABase->TransmitDirectly(&Cmd);
							GUICmdSendReferencePDFData	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
							SCmd.Data=Cmd.RData;
							SCmd.Send(NULL,GlobalPage,0);
						}
					}
				}
			}
        }
    }
}
void	PropertyRasterInspectionForm::ShowInEdit(void)
{
}
void	PropertyRasterInspectionForm::BuildForShow(void)
{
	ShowLibList();
	ShowList();
}
void	PropertyRasterInspectionForm::StartPage	(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
	ShowList();
}
void PropertyRasterInspectionForm::on_pushButtonReferencePDF_clicked()
{
    RasterInspectionBase	*ABase=GetRasterInspectionBase();
	if(ABase!=NULL){
		CmdRasterShowReferencePDFList	Cmd(GetLayersBase());
		ABase->TransmitDirectly(&Cmd);
	}
}


void PropertyRasterInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyRasterInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyRasterInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	if(BBase!=NULL){
		CmdGetRasterInspectionLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui->tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui->tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui->tableWidgetLibList->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());
		}
	}
}

void	PropertyRasterInspectionForm::ShowSelectedLibList(void)
{
	int	row=0;
	ui->tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui->tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui->tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui->tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}

void	PropertyRasterInspectionForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}
void	PropertyRasterInspectionForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

bool	PropertyRasterInspectionForm::SaveContent(QIODevice *f)
{
	WORD	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,LibType)==false)
		return false;
	if(LibList.Save(f)==false)
		return false;
	if(SelectedLibList.Save(f)==false)
		return false;
	if(::Save(f,LibFolderID)==false)
		return false;

	return true;
}
bool	PropertyRasterInspectionForm::LoadContent(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,LibType)==false)
		return false;
	if(LibList.Load(f)==false)
		return false;
	if(SelectedLibList.Load(f)==false)
		return false;
	if(::Load(f,LibFolderID)==false)
		return false;

	ShowLibList();
	ShowSelectedLibList();

	QString FolderName;
	int ParentID;
	int NumberInFolder;
	if(GetLayersBase()->GetDatabaseLoader()->S_LibFolderFindData(GetLayersBase()->GetDatabase(),LibFolderID ,FolderName ,ParentID ,NumberInFolder)==true){
		SetLibFolder(LibFolderID ,FolderName);
	}
	return true;
}

void PropertyRasterInspectionForm::ShowList(void)
{
	RasterInspectionBase	*BBase=GetRasterInspectionBase();
	if(BBase==NULL)
		return;
	AlgorithmLibraryContainer	*LibC=BBase->GetLibraryContainer();

	ui->tableWidgetList->setRowCount(0);
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqRasterInspectionInfoList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendRasterInspectionInfoList	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			int	Row=ui->tableWidgetList->rowCount();
			ui->tableWidgetList->setRowCount(Row+SCmd.ItemIDList.GetCount());
			for(ListPhasePageLayerLibID *L=SCmd.ItemIDList.GetFirst();L!=NULL;L=L->GetNext(),Row++){
				::SetDataToTable(ui->tableWidgetList, 0, Row, QString::number(L->Data.Phase));
				::SetDataToTable(ui->tableWidgetList, 1, Row, QString::number(L->Data.Page));
				::SetDataToTable(ui->tableWidgetList, 2, Row, QString::number(L->Data.LibID));
	
				QString	LibName=LibC->GetLibraryName(L->Data.LibID);
				::SetDataToTable(ui->tableWidgetList, 3, Row, LibName);
				::SetDataToTable(ui->tableWidgetList, 4, Row, QString::number(L->ItemIDs.GetCount()));
			}
		}
	}
}

void PropertyRasterInspectionForm::on_pushButtonSetFrom_clicked()
{
	int	r=ui->tableWidgetLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==a->GetLibID())
			return;
	}
	SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	ShowSelectedLibList();
}


void PropertyRasterInspectionForm::on_pushButtonGetBack_clicked()
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}


void PropertyRasterInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}


void PropertyRasterInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}


void PropertyRasterInspectionForm::on_toolButtonDrawMode_clicked()
{
	if(ui->toolButtonDrawMode->isChecked()==true){
		ui->toolButtonDrawMode->setText("Reference");
	}
	else{
		ui->toolButtonDrawMode->setText("Inspection");
	}
}


void PropertyRasterInspectionForm::on_toolButtonShowPDF_clicked()
{
	ModeShowPDF++;
	if(ModeShowPDF>=3)
		ModeShowPDF=0;
	switch(ModeShowPDF){
		case 0:	ui->toolButtonShowPDF->setText("No PDF");		break;
		case 1:	ui->toolButtonShowPDF->setText("Show PDF");		break;
		case 2:	ui->toolButtonShowPDF->setText("Show Item PDF");break;
	}
	BroadcastRepaintAll();
}


void PropertyRasterInspectionForm::on_pushButtonGenerate_clicked()
{
	if(LLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate DotColorMatchings automatically");
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Generating items",GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateRasterInspection	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.Send(NULL,GlobalPage,0);
	}
	ShowList();
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}


void PropertyRasterInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}


void PropertyRasterInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

