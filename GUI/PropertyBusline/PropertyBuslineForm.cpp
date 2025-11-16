#include "PropertyBuslineFormResource.h"
#include "PropertyBuslineForm.h"
#include "ui_PropertyBuslineForm.h"
#include "EditLibraryDialog.h"
#include "SelectLibraryDialog.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "XGeneralFunc.h"
#include "XBuslinePacket.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyBuslineForm::PropertyBuslineForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyBuslineForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	BuslineBase	*BBase=GetBuslineBase();
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
		CmdCreateTempBuslineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyBuslineForm::~PropertyBuslineForm()
{
    delete ui;
}
BuslineBase	*PropertyBuslineForm::GetBuslineBase(void)
{
	return (BuslineBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"Busline");
}

void	PropertyBuslineForm::TransmitDirectly(GUIDirectMessage *packet)
{
	BuslineBase	*BBase=GetBuslineBase();
	CmdBuslineDrawPacket	*BDrawModePacket=dynamic_cast<CmdBuslineDrawPacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonGenerate->isChecked()==true)
			BDrawModePacket->DMode=BuslineDrawAttr::__Mode_ItemArea;
		else if(ui->toolButtonTest->isChecked()==true)
			BDrawModePacket->DMode=BuslineDrawAttr::__Mode_PickupArea;
		else if(ui->toolButtonTestOpen->isChecked()==true)
			BDrawModePacket->DMode=BuslineDrawAttr::__Mode_TestOpen;
		else if(ui->toolButtonTestShort->isChecked()==true)
			BDrawModePacket->DMode=BuslineDrawAttr::__Mode_TestShort;
		return;
	}
	CmdBuslineDrawEnd	*BlockDEnd=dynamic_cast<CmdBuslineDrawEnd *>(packet);
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

void	PropertyBuslineForm::BuildForShow(void)
{
}

void PropertyBuslineForm::on_toolButtonGenerate_clicked()
{

}

void PropertyBuslineForm::on_toolButtonTest_clicked()
{

}

void PropertyBuslineForm::on_pushButtonEditLibFolder_clicked()
{
	BuslineBase	*BBase=GetBuslineBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}
void	PropertyBuslineForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void	PropertyBuslineForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	BuslineBase	*BBase=GetBuslineBase();
	if(BBase!=NULL){
		CmdGetBuslineLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyBuslineForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	BuslineBase	*BBase=GetBuslineBase();
	if(BBase!=NULL){
		CmdCreateTempBuslineLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadBuslineLibraryPacket	Packet(GetLayersBase());
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

void PropertyBuslineForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyBuslineForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadBuslineLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		BuslineBase	*BBase=GetBuslineBase();
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

void PropertyBuslineForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyBuslineForm::on_pushButtonSetFrom_clicked()
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

void PropertyBuslineForm::on_pushButtonGetBack_clicked()
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

void PropertyBuslineForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyBuslineForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyBuslineForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();
}

void PropertyBuslineForm::on_ButtonLibSave_clicked()
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
	CmdUpdateBuslineLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	BuslineBase	*BBase=GetBuslineBase();
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

void	PropertyBuslineForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(data.GetLibrary());
	ui->EditMinWidth			->setValue(ALib->MinWidth);
	ui->EditMinGap				->setValue(ALib->MinGap);
	ui->lineEditMinArea			->setText(QString::number(ALib->MinArea));
	ui->lineEditMaxArea			->setText(QString::number(ALib->MaxArea));
	ui->EditMinSize				->setValue	(ALib->MinSize);
	ui->checkBoxDarkside		->setChecked(ALib->Darkside);
	ui->checkBoxCompareToMaster	->setChecked(ALib->CompareToMaster);
	ui->checkBoxAutoBinarize	->setChecked(ALib->AutoBinarize);
	ui->checkBoxReduceNoise		->setChecked(ALib->ReduceNoise);
	ui->EditBinarizedLength		->setValue	(ALib->BinarizedLength);
	ui->EditReferredBrightness	->setValue	(ALib->ReferredBrightness);
	ui->EditSearchDotToMaster	->setValue	(ALib->SearchDotToMaster);
}

void	PropertyBuslineForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	BuslineLibrary	*ALib=dynamic_cast<BuslineLibrary *>(data.GetLibrary());
	ALib->MinWidth				=ui->EditMinWidth			->value();
	ALib->MinGap				=ui->EditMinGap				->value();
	ALib->MinArea				=ui->lineEditMinArea		->text().toLongLong();
	ALib->MaxArea				=ui->lineEditMaxArea		->text().toLongLong();
	ALib->MinSize				=ui->EditMinSize			->value();
	ALib->Darkside				=ui->checkBoxDarkside		->isChecked();
	ALib->CompareToMaster		=ui->checkBoxCompareToMaster->isChecked();
	ALib->AutoBinarize			=ui->checkBoxAutoBinarize	->isChecked();
	ALib->ReduceNoise			=ui->checkBoxReduceNoise	->isChecked();
	ALib->BinarizedLength		=ui->EditBinarizedLength	->value();
	ALib->ReferredBrightness	=ui->EditReferredBrightness	->value();
	ALib->SearchDotToMaster		=ui->EditSearchDotToMaster	->value();
}

void PropertyBuslineForm::ShowItemList(void)
{
	BuslineItemList.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUIReqBuslineListForPacketPack	RCmd(GetLayersBase(),sRoot,sName,page);
		GUIAckBuslineListForPacketPack	SCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(page,0,SCmd);
		BuslineListForPacket *a;
		while((a=SCmd.Data.GetFirst())!=NULL){
			SCmd.Data.RemoveList(a);
			a->Page=page;
			BuslineItemList.AppendList(a);
		}
	}
	ui->tableWidgetItemList->setUpdatesEnabled(false);
	ui->tableWidgetItemList->setRowCount(BuslineItemList.GetCount());
	int	Row=0;
	for(BuslineListForPacket *a=BuslineItemList.GetFirst();a!=NULL;a=a->GetNext()){
		::SetDataToTable(ui->tableWidgetItemList,0,Row ,QString::number(a->ItemID));
		::SetDataToTable(ui->tableWidgetItemList,1,Row ,QString::number(a->Page));
		::SetDataToTable(ui->tableWidgetItemList,2,Row ,QString::number(a->Layer));
		::SetDataToTable(ui->tableWidgetItemList,3,Row ,QString(/**/"(") +QString::number(a->x1)+QString(/**/",")+QString::number(a->y1)+QString(/**/")")
													   +QString(/**/"-(")+QString::number(a->x2)+QString(/**/",")+QString::number(a->y2)+QString(/**/")"));
		Row++;
	}
	ui->tableWidgetItemList->setUpdatesEnabled(true);
}

void PropertyBuslineForm::on_pushButtonGenerateFotTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate areas automatically");

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Basic" ,/**/"BuslineImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyBuslineForm_LS,LID_6)/*"Generating items"*/
										,LayerList.GetCount()*GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqGenerateBuslineItems	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList		=SelectedLibList.GetIDList();
		Cmd.LayerList	=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}


void PropertyBuslineForm::on_tableWidgetItemList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	BuslineListForPacket	*Item=BuslineItemList.GetItem(Row);
	if(Item!=NULL){
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Basic" ,/**/"BuslineImagePanel" ,/**/"");
		if(GProp!=NULL){
			CmdDrawImageActivate	ACmd(GetLayersBase(),Item->Page,Item->Layer,Item->ItemID);
			GProp->TransmitDirectly(&ACmd);
		}
	}
}

void PropertyBuslineForm::on_tableWidgetItemList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetItemList->currentRow();
	if(Row<0)
		return;
	BuslineListForPacket	*Item=BuslineItemList.GetItem(Row);
	if(Item!=NULL){
	}
}

void	PropertyBuslineForm::CommandGenerateBlocks(int LibID ,int X1,int Y1,int X2,int Y2)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual Block");

	IntList PageList;
	FlexArea	Area;
	Area.SetRectangle(X1,Y1,X2,Y2);
	GetLayersBase()->GetLocalPageFromArea(Area,PageList);
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Basic" ,/**/"BuslineImagePanel" ,/**/"");
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
void	PropertyBuslineForm::CommandGenerateBlocksByLib(int LibID)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate areas automatically");

	IntList LayerList;
	GUIFormBase *GProp=GetLayersBase()->FindByName(/**/"Basic",/**/"BuslineImagePanel",/**/"");
	if(GProp!=NULL){
		DisplayImage *di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Generating items by Lib"
										,LayerList.GetCount()*GetLayersBase()->GetPageNumb()*10);
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqGenerateBuslineItems	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibList.Add(LibID);
		Cmd.LayerList=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
	ShowItemList();
}

void PropertyBuslineForm::on_pushButtonTest_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Basic" ,/**/"BuslineImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*BPanel=dynamic_cast<DisplayImage *>(GProp);
		if(BPanel!=NULL){
			BPanel->GetActiveLayerList(LayerList);
		}
	}
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIReqTestMap	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LayerList=LayerList;
		Cmd.Send(NULL,GlobalPage,0);
	}
	if(GProp!=NULL){
		DisplayImage	*BPanel=dynamic_cast<DisplayImage *>(GProp);
		if(BPanel!=NULL){
			BPanel->repaint();
		}
	}
}

void PropertyBuslineForm::on_pushButtonClear_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUIClearMap	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Basic" ,/**/"BuslineImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*BPanel=dynamic_cast<DisplayImage *>(GProp);
		if(BPanel!=NULL){
			BPanel->repaint();
		}
	}
}
