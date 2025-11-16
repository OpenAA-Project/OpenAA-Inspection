#include "PropertyMultiSpectralForm.h"
#include "ui_PropertyMultiSpectralForm.h"
#include "EditMultiSpectralLibraryDialog.h"
#include "XMultiSpectral.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XPropertyMultiSpectralPacket.h"
#include "XMultiSpectral.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "XStandardCommand.h"
#include <QMessageBox>
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMultiSpectralForm::PropertyMultiSpectralForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyMultiSpectralForm)
{
    ui->setupUi(this);

	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);

	if(BBase!=NULL){
		CmdCreateTempMultiSpectralLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	LLib->SetLibID(-1);

	::SetColumnWidthInTable(ui->tableWidgetList ,0, 15);
	::SetColumnWidthInTable(ui->tableWidgetList ,1, 15);
	::SetColumnWidthInTable(ui->tableWidgetList ,2, 15);
	::SetColumnWidthInTable(ui->tableWidgetList ,3, 15);

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyMultiSpectralForm::~PropertyMultiSpectralForm()
{
    delete ui;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}

MultiSpectralBase	*PropertyMultiSpectralForm::GetMultiSpectralBase(void)
{
	return (MultiSpectralBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MultiSpectral");
}

void	PropertyMultiSpectralForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdMultiSpectralDrawAttr	*CmdMultiSpectralDrawAttrVar=dynamic_cast<CmdMultiSpectralDrawAttr *>(packet);
	if(CmdMultiSpectralDrawAttrVar!=NULL){
		//CmdMultiSpectralDrawAttrVar->ModeShowItems=ui->toolButtonDrawPartialArea->isChecked();

		return;
	}
	GUICmdMultiSpectralDrawEnd	*GUICmdMultiSpectralDrawEndVar=dynamic_cast<GUICmdMultiSpectralDrawEnd *>(packet);
	if(GUICmdMultiSpectralDrawEndVar!=NULL){
		int	Row=ui->tableWidgetGeneratedLibList->currentRow();
		if(Row>=0){
			AlgorithmLibraryList *aLib=SelectedLibList.GetItem(Row);
			if(aLib!=NULL){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual MultiSpectralUsageAreaItem");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(GUICmdMultiSpectralDrawEndVar->Area, PageList);
				for(IntClass *P=PageList.GetFirst();P != NULL;P=P->GetNext()) {
					int	page=P->GetValue();
					DataInPage *pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=GUICmdMultiSpectralDrawEndVar->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte() > 0) {
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddMultiSpectralUsageAreaItem	Cmd(GetLayersBase(), sRoot, sName, GlobalPage);
						Cmd.LocalArea=A;
						Cmd.LibID=aLib->GetLibID();
						Cmd.SendOnly(GlobalPage, 0);
					}
				}
			}
		}
		else{
			QMessageBox::warning(NULL,"Warning"
								,"Select library");
		}
		return;
	}
}

void	PropertyMultiSpectralForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
	ShowList();
}
void	PropertyMultiSpectralForm::BuildForShow(void)
{
	ShowLibList();
	ShowList();
}
void PropertyMultiSpectralForm::on_pushButtonEditLibFolder_clicked()
{
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyMultiSpectralForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyMultiSpectralForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	if(BBase!=NULL){
		CmdGetMultiSpectralLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyMultiSpectralForm::ShowSelectedLibList(void)
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
void PropertyMultiSpectralForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}


void PropertyMultiSpectralForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBackAll_clicked();
}


void PropertyMultiSpectralForm::on_pushButtonSetFrom_clicked()
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


void PropertyMultiSpectralForm::on_pushButtonGetBack_clicked()
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


void PropertyMultiSpectralForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}


void PropertyMultiSpectralForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}


void PropertyMultiSpectralForm::on_pushButtonEditLibrary_clicked()
{
	EditMultiSpectralLibraryDialog	D(GetLayersBase(),this);
	D.exec();
	ShowLibList();
	ShowSelectedLibList();
	//if(LLib!=NULL){
	//	CmdLoadMultiSpectralLibraryPacket	Packet(GetLayersBase());
	//	Packet.Point=LLib;
	//	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	//	if(BBase!=NULL){
	//		BBase->TransmitDirectly(&Packet);
	//		if(Packet.Success==true){
	//			ShowLibrary(*LLib);
	//		}
	//	}
	//}
}
void	PropertyMultiSpectralForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}
void	PropertyMultiSpectralForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	if(BBase!=NULL){
		CmdGetLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}

bool	PropertyMultiSpectralForm::SaveContent(QIODevice *f)
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
bool	PropertyMultiSpectralForm::LoadContent(QIODevice *f)
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

void PropertyMultiSpectralForm::ShowList(void)
{
	MultiSpectralBase	*BBase=GetMultiSpectralBase();
	if(BBase==NULL)
		return;
	AlgorithmLibraryContainer	*LibC=BBase->GetLibraryContainer();

	//ui->tableWidgetList->setRowCount(0);
	//for(int phase=0;phase<GetPhaseNumb();phase++){
	//	for(int page=0;page<GetPageNumb();page++){
	//		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	//		GUICmdReqMultiSpectralInfoList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//		GUICmdSendMultiSpectralInfoList	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//		RCmd.Phase=phase;
	//		if(RCmd.Send(GlobalPage,0,SCmd)==true){
	//			int	Row=ui->tableWidgetList->rowCount();
	//			ui->tableWidgetList->setRowCount(Row+SCmd.ItemIDList.GetCount());
	//			for(ListPhasePageLayerLibID *L=SCmd.ItemIDList.GetFirst();L!=NULL;L=L->GetNext(),Row++){
	//				::SetDataToTable(ui->tableWidgetList, 0, Row, QString::number(L->Data.Phase));
	//				::SetDataToTable(ui->tableWidgetList, 1, Row, QString::number(L->Data.Page));
	//				::SetDataToTable(ui->tableWidgetList, 2, Row, QString::number(L->Data.LibID));
	//
	//				QString	LibName=LibC->GetLibraryName(L->Data.LibID);
	//				::SetDataToTable(ui->tableWidgetList, 3, Row, LibName);
	//				::SetDataToTable(ui->tableWidgetList, 4, Row, QString::number(L->ItemIDs.GetCount()));
	//			}
	//		}
	//	}
	//}
}
