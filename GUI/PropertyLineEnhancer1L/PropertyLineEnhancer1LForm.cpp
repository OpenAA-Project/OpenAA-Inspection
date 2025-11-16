#include "PropertyLineEnhancer1LFormResource.h"
#include "PropertyLineEnhancer1LForm.h"
#include "ui_PropertyLineEnhancer1LForm.h"
#include "XLineEnhancer1L.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
#include "EditLibrary.h"
#include "XGeneralFunc.h"
#include "XPropertyLineEnhancer1LPacket.h"
#include "BrightHistgramForm.h"
#include "ManualInputLineEnhancerL1Dialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyLineEnhancer1LForm::PropertyLineEnhancer1LForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyLineEnhancer1LForm)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetLibList->setColumnWidth (0, 30);
	ui->tableWidgetLibList->setColumnWidth (1, 80);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui->tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyLineEnhancer1LForm::~PropertyLineEnhancer1LForm()
{
    delete ui;
}
LineEnhancer1LBase	*PropertyLineEnhancer1LForm::GetLineEnhancer1LBase(void)
{
	return (LineEnhancer1LBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer1L");
}

void PropertyLineEnhancer1LForm::on_pushButtonEditLibFolder_clicked()
{
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyLineEnhancer1LForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyLineEnhancer1LForm::BuildForShow(void)
{
}

void	PropertyLineEnhancer1LForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	if(BBase!=NULL){
		CmdGetLineEnhancer1LLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyLineEnhancer1LForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
	if(BBase!=NULL){
		CmdCreateTempLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
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
void PropertyLineEnhancer1LForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				if(ui->radioButtonPickupArea->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				if(ui->radioButtonBlock->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedGenLayers());
				if(ui->radioButtonCalc->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedGenLayers());
				if(ui->radioButtonMatching->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedGenLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}
void PropertyLineEnhancer1LForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"LineEnhancer1LImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}
void PropertyLineEnhancer1LForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyLineEnhancer1LForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				if(ui->radioButtonPickupArea->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				if(ui->radioButtonBlock->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedGenLayers());
				if(ui->radioButtonCalc->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedGenLayers());
				if(ui->radioButtonMatching->isChecked()==true)
					SetLayersFromLib(TempLib->GetAdaptedGenLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyLineEnhancer1LForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyLineEnhancer1LForm::on_pushButtonSetFrom_clicked()
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

void PropertyLineEnhancer1LForm::on_pushButtonGetBack_clicked()
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
void	PropertyLineEnhancer1LForm::TransmitDirectly(GUIDirectMessage *packet)
{
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();

	GUICmdReqLineEnhancer1LDrawMode	*GUICmdReqLineEnhancer1LDrawModeVar=dynamic_cast<GUICmdReqLineEnhancer1LDrawMode *>(packet);
	if(GUICmdReqLineEnhancer1LDrawModeVar!=NULL){
		if(ui->radioButtonPickupArea->isChecked()==true)
			GUICmdReqLineEnhancer1LDrawModeVar->DrawingArea=LineEnhancer1LDrawAttr::_Pickup;
		if(ui->radioButtonBlock->isChecked()==true)
			GUICmdReqLineEnhancer1LDrawModeVar->DrawingArea=LineEnhancer1LDrawAttr::_Block;
		if(ui->radioButtonCalc->isChecked()==true)
			GUICmdReqLineEnhancer1LDrawModeVar->DrawingArea=LineEnhancer1LDrawAttr::_Calc;
		if(ui->radioButtonMatching->isChecked()==true)
			GUICmdReqLineEnhancer1LDrawModeVar->DrawingArea=LineEnhancer1LDrawAttr::_Matching;
		return;
	}
	GUICmdSetLineEnhancer1LDrawMode	*GUICmdSetLineEnhancer1LDrawModeVar=dynamic_cast<GUICmdSetLineEnhancer1LDrawMode *>(packet);
	if(GUICmdSetLineEnhancer1LDrawModeVar!=NULL){
		if(GUICmdSetLineEnhancer1LDrawModeVar->DrawingArea==LineEnhancer1LDrawAttr::_Pickup)
			ui->radioButtonPickupArea->setChecked(true);
		if(GUICmdSetLineEnhancer1LDrawModeVar->DrawingArea==LineEnhancer1LDrawAttr::_Block)
			ui->radioButtonBlock->setChecked(true);
		if(GUICmdSetLineEnhancer1LDrawModeVar->DrawingArea==LineEnhancer1LDrawAttr::_Calc)
			ui->radioButtonCalc->setChecked(true);
		if(GUICmdSetLineEnhancer1LDrawModeVar->DrawingArea==LineEnhancer1LDrawAttr::_Matching)
			ui->radioButtonMatching->setChecked(true);
		return;
	}

	CmdLineEnhancer1LExecuteDrawEnd	*BlockDEnd=dynamic_cast<CmdLineEnhancer1LExecuteDrawEnd *>(packet);
	if(BlockDEnd!=NULL){	
		if(ui->radioButtonPickupArea->isChecked()==true){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=BlockDEnd->Area;
				LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(TempLib->GetLibrary());
				BrightHistgramForm	D(BlockDEnd->Area,BlockDEnd->ImagePanelPoint
									  ,ALib->PickupColorL,ALib->PickupColorH,this);
				D.Reflect(ALib->PickupColorL,ALib->PickupColorH);
				if(D.exec()==(int)true){
					ALib->PickupColorL	=D.PickupL;
					ALib->PickupColorH	=D.PickupH;
				}
			}
		}
		else if(ui->radioButtonCalc->isChecked()==true){
			ManualInputLineEnhancerL1Dialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual LineEnhancer1L");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualLineEnhancer1L	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						Cmd.LibID	=D.BItem->GetLibID();
						Cmd.LayerList=BlockDEnd->LayerList;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
			//ShowDotMatchingInfoList();
			}
		}
	}
}

void PropertyLineEnhancer1LForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyLineEnhancer1LForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyLineEnhancer1LForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyLineEnhancer1LForm_LS,LID_2)/*"Pickup Test"*/);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"LineEnhancer1LImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LayerList=LayerList;
		Cmd.LibPoint	=TempLib;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyLineEnhancer1LForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyLineEnhancer1LForm::on_ButtonGenerateLibs_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"LineEnhancer1LImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyLineEnhancer1LForm_LS,LID_3)/*"Generating items"*/,GetLayersBase()->GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCreateLineEnhancer1L	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.SelectedLibList=SelectedLibList;
		RCmd.LayerList		=LayerList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyLineEnhancer1LForm::on_radioButtonPickupArea_clicked()
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancer1LDrawAttr::_Pickup;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
	SetLayersFromLib(TempLib->GetAdaptedPickLayers());
}

void PropertyLineEnhancer1LForm::on_radioButtonBlock_clicked()
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancer1LDrawAttr::_Block;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
	SetLayersFromLib(TempLib->GetAdaptedGenLayers());
}

void PropertyLineEnhancer1LForm::on_radioButtonCalc_clicked()
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancer1LDrawAttr::_Calc;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
	SetLayersFromLib(TempLib->GetAdaptedGenLayers());
}

void PropertyLineEnhancer1LForm::on_radioButtonMatching_clicked()
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancer1LDrawAttr::_Matching;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
	SetLayersFromLib(TempLib->GetAdaptedGenLayers());
}

void	PropertyLineEnhancer1LForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui->EditLibID->setText(/**/"");
	else
		ui->EditLibID->setText(QString::number(data.GetLibID()));
	ui->EditLibName	->setText(data.GetLibName());

	LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(data.GetLibrary());
	ui->EditSourceLayer		->setValue(ALib->SourceLayer);
	ui->EditMinDot			->setValue(ALib->MinDot);
	ui->EditMaxDot			->setValue(ALib->MaxDot);
	ui->EditMinSize			->setValue(ALib->MinSize);
	ui->EditMaxSize			->setValue(ALib->MaxSize);
	ui->EditLimitDot		->setValue(ALib->LimitDot);
	ui->EditShrinkDot		->setValue(ALib->ShrinkDot);
	ui->EditPriority		->setValue(ALib->Priority);
	ui->EditStepDot			->setValue(ALib->StepDot);
	ui->EditSearchBlockWidth->setValue(ALib->SearchBlockWidth);
}

void	PropertyLineEnhancer1LForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui->EditLibName	->text());

	LineEnhancer1LLibrary	*ALib=dynamic_cast<LineEnhancer1LLibrary *>(data.GetLibrary());
	ALib->SourceLayer		=ui->EditSourceLayer	->value();
	ALib->MinDot			=ui->EditMinDot			->value();
	ALib->MaxDot			=ui->EditMaxDot			->value();
	ALib->MinSize			=ui->EditMinSize		->value();
	ALib->MaxSize			=ui->EditMaxSize		->value();
	ALib->LimitDot			=ui->EditLimitDot		->value();
	ALib->ShrinkDot			=ui->EditShrinkDot		->value();
	ALib->Priority			=ui->EditPriority		->value();
	ALib->StepDot			=ui->EditStepDot		->value();
	ALib->SearchBlockWidth	=ui->EditSearchBlockWidth->value();
}

void PropertyLineEnhancer1LForm::on_ButtonLibSave_clicked()
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
	CmdUpdateLineEnhancer1LLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancer1LBase	*BBase=GetLineEnhancer1LBase();
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

void PropertyLineEnhancer1LForm::on_pushButtonEditLibrary_clicked()
{
	EditLibrary	D(GetLayersBase(),this);
	D.exec();
}
