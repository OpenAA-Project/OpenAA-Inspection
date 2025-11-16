#include "PropertyHoughInspectionFormResource.h"
#include "PropertyHoughInspectionForm.h"
#include "ui_PropertyHoughInspectionForm.h"
#include "EditLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XHoughInspectionPacket.h"
#include "SelectLibraryDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyHoughInspectionForm::PropertyHoughInspectionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyHoughInspectionForm)
{
    ui->setupUi(this);

	LibFolderID =-1;
	HoughBase	*BBase=GetHoughBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	ui->tableWidgetItemList->setColumnWidth (0, 50);
	ui->tableWidgetItemList->setColumnWidth (1, 50);
	ui->tableWidgetItemList->setColumnWidth (2, 50);
	ui->tableWidgetItemList->setColumnWidth (3, 120);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempHoughLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyHoughInspectionForm::~PropertyHoughInspectionForm()
{
    delete ui;
}

HoughBase	*PropertyHoughInspectionForm::GetHoughBase(void)
{
	return (HoughBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Hough");
}

void	PropertyHoughInspectionForm::TransmitDirectly(GUIDirectMessage *packet)
{
	HoughBase	*BBase=GetHoughBase();
	CmdHoughDrawPacket	*BDrawModePacket=dynamic_cast<CmdHoughDrawPacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonGenerate->isChecked()==true)
			BDrawModePacket->DMode=HoughDrawAttr::__Mode_ItemArea;
		else if(ui->toolButtonTest->isChecked()==true)
			BDrawModePacket->DMode=HoughDrawAttr::__Mode_PickupArea;
		return;
	}
	CmdHoughDrawEnd	*BlockDEnd=dynamic_cast<CmdHoughDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui->toolButtonGenerate->isChecked()==true){
			SelectLibraryDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.SelectedID>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Block");

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
	}
}

void	PropertyHoughInspectionForm::BuildForShow(void)
{
}

void PropertyHoughInspectionForm::on_pushButtonEditLibFolder_clicked()
{
	HoughBase	*BBase=GetHoughBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyHoughInspectionForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void	PropertyHoughInspectionForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		CmdGetHoughLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyHoughInspectionForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		CmdCreateTempHoughLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadHoughLibraryPacket	Packet(GetLayersBase());
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

void PropertyHoughInspectionForm::on_tableWidgetLibList_clicked(const QModelIndex &index)
{

}

void PropertyHoughInspectionForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyHoughInspectionForm::on_pushButtonSetFrom_clicked()
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

void PropertyHoughInspectionForm::on_pushButtonGetBack_clicked()
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

void PropertyHoughInspectionForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyHoughInspectionForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyHoughInspectionForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadHoughLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		HoughBase	*BBase=GetHoughBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyHoughInspectionForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyHoughInspectionForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyHoughInspectionForm::on_toolButtonGenerate_clicked()
{

}

void PropertyHoughInspectionForm::on_toolButtonTest_clicked()
{

}

void PropertyHoughInspectionForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL	, /**/"Warning"
																	, /**/"No Library Name"
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateHoughLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	HoughBase	*BBase=GetHoughBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Packet);
	}
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetLibID()==TempLib->GetLibID()){
			a->SetLibName(TempLib->GetLibName());
		}
	}
	ShowLibList();
	ShowSelectedLibList();
}

void	PropertyHoughInspectionForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(data.GetLibrary());
	ui->EditZoneWidth				->setValue	(ALib->ZoneWidth);
	ui->EditMaxIsolation			->setValue	(ALib->MaxIsolation);
	ui->EditBinarizedLength			->setValue	(ALib->BinarizedLength);
	ui->EditMinPixels				->setValue	(ALib->MinPixels);
	ui->EditNGLength				->setValue	(ALib->NGLength);
	ui->EditPickupL					->setValue	(ALib->PickupL);
	ui->EditPickupH					->setValue	(ALib->PickupH);
	ui->checkBoxRemoveDynamicMask	->setChecked(ALib->RemoveDynamicMask);
	ui->EditReducedSize				->setValue	(ALib->ReducedSize);
	ui->EditMaxLineCount			->setValue	(ALib->MaxLineCount);
	ui->EditMinNGWidth				->setValue	(ALib->MinNGWidth);
	ui->EditMaxNGWidth				->setValue	(ALib->MaxNGWidth);
}

void	PropertyHoughInspectionForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	HoughLibrary	*ALib=dynamic_cast<HoughLibrary *>(data.GetLibrary());
	ALib->ZoneWidth			=ui->EditZoneWidth		->value();
	ALib->MaxIsolation		=ui->EditMaxIsolation	->value();
	ALib->BinarizedLength	=ui->EditBinarizedLength->value();
	ALib->MinPixels			=ui->EditMinPixels		->value();
	ALib->NGLength			=ui->EditNGLength		->value();
	ALib->PickupL			=ui->EditPickupL		->value();
	ALib->PickupH			=ui->EditPickupH		->value();
	ALib->RemoveDynamicMask	=ui->checkBoxRemoveDynamicMask	->isChecked();
	ALib->ReducedSize		=ui->EditReducedSize	->value();
	ALib->MaxLineCount		=ui->EditMaxLineCount	->value();
	ALib->MinNGWidth		=ui->EditMinNGWidth		->value();
	ALib->MaxNGWidth		=ui->EditMaxNGWidth		->value();
}
void	PropertyHoughInspectionForm::CommandGenerateBlocks(int LibID ,int X1,int Y1,int X2,int Y2)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Block");

	IntList PageList;
	FlexArea	Area;
	Area.SetRectangle(X1,Y1,X2,Y2);
	GetLayersBase()->GetLocalPageFromArea(Area,PageList);
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"HoughImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*BPanel=dynamic_cast<DisplayImage *>(GProp);
		if(BPanel!=NULL){
			BPanel->GetActiveLayerList(LayerList);
		}
	}
	for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
		int	page=P->GetValue();
		DataInPage	*pdata=GetLayersBase()->GetPageData(page);
		FlexArea	A=Area;
		pdata->ClipMoveAreaFromGlobal(A);
		if(A.GetPatternByte()>0){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSendAddManualBlock	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
			Cmd.Area=A;
			Cmd.LibID=LibID;
			Cmd.LayerList=LayerList;
			Cmd.SendOnly(GlobalPage,0);
		}
	}
}
void PropertyHoughInspectionForm::on_tableWidgetItemList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	HoughListForPacket	*Item=HoughItemList.GetItem(Row);
	if(Item!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"HoughImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdDrawImageActivate	ACmd(GetLayersBase(),Item->Page,Item->Layer,Item->ItemID);
			GProp->TransmitDirectly(&ACmd);
		}
	}
}

void PropertyHoughInspectionForm::on_tableWidgetItemList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	HoughListForPacket	*Item=HoughItemList.GetItem(Row);
	if(Item!=NULL){
	}
}
