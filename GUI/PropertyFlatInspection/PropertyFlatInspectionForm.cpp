//#include "PropertyFlatInspectionResource.h"
#include "PropertyFlatInspectionForm.h"
#include "ui_PropertyFlatInspectionForm.h"
#include "XDLLOnly.h"
#include "ImageControlTools.h"
#include "XGUI.h"
#include "XPropertyFlatInspectionPacket.h"
#include "EditFlatInspectionLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XAlgorithmLibrary.h"
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyFlatInspectionForm::PropertyFlatInspectionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyFlatInspectionForm)
{
    ui->setupUi(this);

	//LangSolver.SetUI(this);
	LibFolderID		=-1;
	ItemListWindow	=NULL;

	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ItemListForPageData=NULL;

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList->setColumnWidth (1, 80);

	ui->tableWidget->setColumnWidth (0, 40);
	ui->tableWidget->setColumnWidth (1, 48);
	ui->tableWidget->setColumnWidth (2, 160);
	ui->tableWidget->setColumnWidth (3, 56);

	if(BBase!=NULL){
		CmdCreateTempFlatInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		LLib=Packet.Point;
	}
	else{
		LLib=new AlgorithmLibraryLevelContainer(BBase);
	}
	LLib->SetLibID(-1);

	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyFlatInspectionForm::~PropertyFlatInspectionForm()
{
	//if(ItemListWindow!=NULL){
	//	ItemListWindow->deleteLater();
	//}
    delete ui;
	if(LLib!=NULL)
		delete	LLib;
	LLib=NULL;
}

FlatInspectionBase	*PropertyFlatInspectionForm::GetFlatInspectionBase(void)
{
	return (FlatInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"FlatInspection");
}
void PropertyFlatInspectionForm::on_toolButtonInsoectionArea_clicked()
{

}


void PropertyFlatInspectionForm::on_toolButtonWindowArea_clicked()
{

}


void PropertyFlatInspectionForm::on_toolButtonMasterShapeArea_clicked()
{

}


void PropertyFlatInspectionForm::on_toolButtonAdaptiveArea_clicked()
{

}


void PropertyFlatInspectionForm::on_toolButtonAdaptiveShape_clicked()
{

}


void PropertyFlatInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyFlatInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void PropertyFlatInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}


void PropertyFlatInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}


void PropertyFlatInspectionForm::on_pushButtonSetFrom_clicked()
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

void	PropertyFlatInspectionForm::ClearLibList(void)
{
	on_pushButtonGetBackAll_clicked();
}

void PropertyFlatInspectionForm::on_pushButtonGetBack_clicked()
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


void PropertyFlatInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}


void PropertyFlatInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}


void	PropertyFlatInspectionForm::SetLib(int LibID)
{
	for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
		if(c->GetLibID()==LibID)
			return;
	}
	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	if(BBase!=NULL){
		CmdGetFlatInspectionLibName	Packet(GetLayersBase());
		Packet.LibID=LibID;
		BBase->TransmitDirectly(&Packet);

		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,LibID,Packet.LibName));
		ShowSelectedLibList();
	}
}
void PropertyFlatInspectionForm::on_pushButtonEditLibrary_clicked()
{
	EditFlatInspectionLibraryDialog	D(GetLayersBase(),this);
	D.exec();

	ShowLibList();
	if(LLib!=NULL){
		CmdLoadFlatInspectionLibraryPacket	Packet(GetLayersBase());
		Packet.Point=LLib;
		FlatInspectionBase	*BBase=GetFlatInspectionBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*LLib);
			}
		}
	}
}

void	PropertyFlatInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	if(BBase!=NULL){
		CmdGetFlatInspectionLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui->tableWidgetLibList->setRowCount(LibList.GetNumber());
		for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
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
struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
};
void	PropertyFlatInspectionForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	FlatInspectionBase	*BBase=GetFlatInspectionBase();
	if(BBase!=NULL){
		CmdCreateTempFlatInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		if(LLib!=NULL){
			delete	LLib;
		}
		LLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			LLib->SetLibID(a->GetLibID());
			CmdLoadFlatInspectionLibraryPacket	Packet(GetLayersBase());
			Packet.Point=LLib;
			BBase->TransmitDirectly(&Packet);
		}
		for(;;){
			AlgorithmLibraryList *a=SelectedLibList.GetFirst();
			if(a==NULL)
				break;
			SelectedLibList.RemoveList(a);
		}

		for(int i=0;i<row;i++){
			SelectedLibList.AppendList(DDim[i].a);
		}
	}

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

void	PropertyFlatInspectionForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{

}

void	PropertyFlatInspectionForm::ShowItemList(void)
{
	//ui->tableWidget->setRowCount(0);
	//FlatInspectionBase	*BBase=GetFlatInspectionBase();
	//if(ItemListForPageData!=NULL){
	//	delete	[]ItemListForPageData;
	//	ItemListForPageData=NULL;
	//}
	//ItemListForPageData=new ItemListForPageContainer[GetPageNumb()];
	//
	//if(BBase!=NULL){
	//	int	ListCount=0;
	//	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
	//		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	//		GUICmdReqItemListForPageContainer	ReqCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//		GUICmdAckItemListForPageContainer	AckCmd(GetLayersBase(),sRoot,sName,GlobalPage);
	//
	//		if(ReqCmd.Send(ReqCmd.GetGlobalPage(),0,AckCmd)==true){
	//			ItemListForPageData[page]=AckCmd.ItemListForPageData;
	//			ListCount+=ItemListForPageData[page].GetCount();
	//		}
	//	}
	//	ui->tableWidget->setRowCount(ListCount);
	//	int	Row=0;
	//	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){	
	//		for(ItemListForPage *L=ItemListForPageData[page].GetFirst();L!=NULL;L=L->GetNext()){
	//			::SetDataToTable(ui->tableWidget ,0,Row ,QString::number(page));
	//			::SetDataToTable(ui->tableWidget ,1,Row ,QString::number(L->LibID));
	//			QString	LibName=BBase->GetLibraryContainer()->GetLibraryName(L->LibID);
	//			::SetDataToTable(ui->tableWidget ,2,Row ,LibName);
	//			::SetDataToTable(ui->tableWidget ,3,Row ,QString::number(L->ItemCount));
	//			Row++;
	//		}
	//	}
	//}
}

bool	PropertyFlatInspectionForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	int	r=ui->tableWidgetGeneratedLibList->currentRow();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		GetFlatInspectionBase()->GetLibraryContainer()->GetLibrary(a->GetLibID() ,data);
		return true;
	}
	return false;
}

void	PropertyFlatInspectionForm::ShowInEdit(void)
{
}
void	PropertyFlatInspectionForm::StartPage(void)
{
	int	MasterID=GetLayersBase()->GetMasterCode();
	if(MasterID>=0 && LibFolderID<0){
		QString		FolderName;
		LibFolderID=GetLayersBase()->GetDatabaseLoader()->S_GetFirstLibFolderByMasterCode(GetLayersBase()->GetDatabase(),MasterID,FolderName);
		ui->labelLibFolderName->setText(FolderName);
	}
}
void	PropertyFlatInspectionForm::BuildForShow(void)
{
	ShowItemList();
}

int		PropertyFlatInspectionForm::GetCurrentLibID(void)
{
	int	Row=ui->tableWidgetGeneratedLibList->currentRow();
	if(Row<0)
		return -1;
	AlgorithmLibraryList	*A=SelectedLibList.GetItem(Row);
	if(A==NULL)
		return -1;
	return A->GetLibID();
}

void	PropertyFlatInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	//FlatInspectionBase	*BBase=GetFlatInspectionBase();
	//CmdFlatInspectionDrawModePacket	*BDrawModePacket=dynamic_cast<CmdFlatInspectionDrawModePacket *>(packet);
	//if(BDrawModePacket!=NULL){
	//	BDrawModePacket->ModeShowArea		=ui->toolButtonShowArea		->isChecked();
	//	BDrawModePacket->ModeShowRotation	=ui->toolButtonShowRotation	->isChecked();
	//	BDrawModePacket->ModeShowDiv		=ui->toolButtonShowDiv		->isChecked();
	//	BDrawModePacket->ModeShowFlat		=ui->toolButtonShowFlat		->isChecked();
	//	BDrawModePacket->ModeShowBackGround	=ui->toolButtonShowBackGround->isChecked();
	//	return;
	//}
	CmdReqFIT_Type	*CmdReqFIT_TypeVar=dynamic_cast<CmdReqFIT_Type *>(packet);
	if(CmdReqFIT_TypeVar!=NULL){
		if(ui->toolButtonInsoectionArea->isChecked()==true)
			CmdReqFIT_TypeVar->FIT_Type=FlatInspectionItem::_FIType_InspectionArea;
		if(ui->toolButtonWindowArea->isChecked()==true)
			CmdReqFIT_TypeVar->FIT_Type=FlatInspectionItem::_FIType_Window;
		if(ui->toolButtonMasterShapeArea->isChecked()==true)
			CmdReqFIT_TypeVar->FIT_Type=FlatInspectionItem::_FIType_MasterArea;
		//if(ui->toolButtonInsoectionArea->isChecked()==true)
		//	Cmd.FIType=FlatInspectionItem::_FIType_InspectionArea;
		if(ui->toolButtonAdaptiveShape->isChecked()==true)
			CmdReqFIT_TypeVar->FIT_Type=FlatInspectionItem::_FIType_SpecialShape;
		if(ui->toolButtonShowMaskMap->isChecked()==true)
			CmdReqFIT_TypeVar->ShowMaskMap=true;
		else
			CmdReqFIT_TypeVar->ShowMaskMap=false;

		return;
	}
	CmdFlatInspectionDrawEnd	*FlatInspectionDEnd=dynamic_cast<CmdFlatInspectionDrawEnd *>(packet);
	if(FlatInspectionDEnd!=NULL){

		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual FlatInspection");

		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(FlatInspectionDEnd->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=FlatInspectionDEnd->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
				GUICmdSendAddManualFlatInspection	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
				Cmd.Area=A;
				if(ui->toolButtonInsoectionArea->isChecked()==true)
					Cmd.FIType=FlatInspectionItem::_FIType_InspectionArea;
				if(ui->toolButtonWindowArea->isChecked()==true)
					Cmd.FIType=FlatInspectionItem::_FIType_Window;
				if(ui->toolButtonMasterShapeArea->isChecked()==true)
					Cmd.FIType=FlatInspectionItem::_FIType_MasterArea;
				//if(ui->toolButtonInsoectionArea->isChecked()==true)
				//	Cmd.FIType=FlatInspectionItem::_FIType_InspectionArea;
				if(ui->toolButtonAdaptiveShape->isChecked()==true)
					Cmd.FIType=FlatInspectionItem::_FIType_SpecialShape;
				Cmd.LibID=GetCurrentLibID();
				if(Cmd.LibID>=0){
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		}
	}
}


bool	PropertyFlatInspectionForm::SaveContent(QIODevice *f)
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
bool	PropertyFlatInspectionForm::LoadContent(QIODevice *f)
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
