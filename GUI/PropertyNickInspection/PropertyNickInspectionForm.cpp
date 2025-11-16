#include "PropertyNickInspectionResource.h"
#include "PropertyNickInspectionForm.h"
#include "ui_PropertyNickInspectionForm.h"
#include "PropertyNickInspectionForm.h"
#include "ui_PropertyNickInspectionForm.h"
#include "EditNickInspectionDialog.h"
#include "SelectLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XNickInspectionPacket.h"
#include "XPropertyNickInspectionCommon.h"
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyNickInspectionForm::PropertyNickInspectionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyNickInspectionForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	NickInspectionBase	*BBase=GetNickInspectionBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	ui->tableWidgetItemList->setColumnWidth (0, 64);
	ui->tableWidgetItemList->setColumnWidth (1, 250);
	ui->tableWidgetItemList->setColumnWidth (2, 64);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempNickInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyNickInspectionForm::~PropertyNickInspectionForm()
{
    delete ui;
}

NickInspectionBase	*PropertyNickInspectionForm::GetNickInspectionBase(void)
{
	return (NickInspectionBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"NickInspection");
}

void	PropertyNickInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	NickInspectionBase	*BBase=GetNickInspectionBase();
	CmdNickInspectionDrawPacket	*BDrawModePacket=dynamic_cast<CmdNickInspectionDrawPacket *>(packet);
	if(BDrawModePacket!=NULL){
		return;
	}
	CmdNickInspectionDrawEnd	*BlockDEnd=dynamic_cast<CmdNickInspectionDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		SelectLibraryDialog	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true && D.SelectedID>=0){
			GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual NickInspection");

			IntList PageList;
			GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=BlockDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
					GUICmdSendAddManualBlock	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
					Cmd.Area=A;
					Cmd.LibID=D.SelectedID;
					Cmd.LayerList=BlockDEnd->LayerList;
					Cmd.SendOnly(GlobalPage,0);
				}
			}
		}
	}
	CmdSelectNickInspectionLibraryDialog	*CmdSelectNickInspectionLibraryDialogVar=dynamic_cast<CmdSelectNickInspectionLibraryDialog *>(packet);
	if(CmdSelectNickInspectionLibraryDialogVar!=NULL){
		SelectLibraryDialog	D(GetLayersBase(),NULL);
		if(D.exec()==QDialog::Accepted){
			CmdSelectNickInspectionLibraryDialogVar->LibID=D.SelectedID;
		}
		return;
	}

}

void	PropertyNickInspectionForm::BuildForShow(void)
{
}

void PropertyNickInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	NickInspectionBase	*BBase=GetNickInspectionBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyNickInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void	PropertyNickInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	NickInspectionBase	*BBase=GetNickInspectionBase();
	if(BBase!=NULL){
		CmdGetNickInspectionLibraryListPacket	Packet(GetLayersBase());
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

struct	AlgorithmLibraryListClass
{
	AlgorithmLibraryList	*a;
};

void	PropertyNickInspectionForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	NickInspectionBase	*BBase=GetNickInspectionBase();
	if(BBase!=NULL){
		CmdCreateTempNickInspectionLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadNickInspectionLibraryPacket	Packet(GetLayersBase());
			Packet.Point=SLib;
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
void PropertyNickInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyNickInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyNickInspectionForm::on_pushButtonSetFrom_clicked()
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

void PropertyNickInspectionForm::on_pushButtonGetBack_clicked()
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

void PropertyNickInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyNickInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyNickInspectionForm::on_pushButtonEditLibrary_clicked()
{
	EditNickInspectionDialog	D(GetLayersBase(),this);
	D.exec();

}

void PropertyNickInspectionForm::ShowItemList(void)
{
	NickInspectionItemList.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUIReqNickInspectionListForPacketPack	RCmd(GetLayersBase(),sRoot,sName,page);
		GUIAckNickInspectionListForPacketPack	SCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,SCmd);
		NickInspectionListForPacket *a;
		while((a=SCmd.Data.GetFirst())!=NULL){
			SCmd.Data.RemoveList(a);
			for(NickInspectionListForPacket *t=NickInspectionItemList.GetFirst();t!=NULL;t=t->GetNext()){
				if(t->LibID==a->LibID){
					t->ItemCount+=a->ItemCount;
					delete	a;
					a=NULL;
					break;
				}
			}
			if(a!=NULL){
				NickInspectionItemList.AppendList(a);
			}
		}
	}
	NickInspectionBase	*NBase=GetNickInspectionBase();
	ui->tableWidgetItemList->setRowCount(NickInspectionItemList.GetCount());
	int	Row=0;
	for(NickInspectionListForPacket *a=NickInspectionItemList.GetFirst();a!=NULL;a=a->GetNext()){

		CmdGetNickInspectionLibraryNamePacket	RCmd(GetLayersBase());
		RCmd.LibID=a->LibID;
		NBase->TransmitDirectly(&RCmd);

		::SetDataToTable(ui->tableWidgetItemList,0,Row ,QString::number(a->LibID));
		::SetDataToTable(ui->tableWidgetItemList,1,Row ,RCmd.LibName);
		::SetDataToTable(ui->tableWidgetItemList,2,Row ,QString::number(a->ItemCount));
		Row++;
	}
}

void PropertyNickInspectionForm::on_ButtonGenerateLibs_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqGenerateNickInspectionItems	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		for(AlgorithmLibraryList *c=SelectedLibList.GetFirst();c!=NULL;c=c->GetNext()){
			RCmd.LibList.Add(c->GetLibID());
		}
		RCmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyNickInspectionForm::on_tableWidgetItemList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	NickInspectionListForPacket	*Item=NickInspectionItemList.GetItem(Row);
	if(Item!=NULL){
	}
}
