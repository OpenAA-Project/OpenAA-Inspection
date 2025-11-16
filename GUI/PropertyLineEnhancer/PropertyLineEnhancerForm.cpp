#include "PropertyLineEnhancerResource.h"
#include "PropertyLineEnhancerForm.h"
#include "XLineEnhancer.h"
#include "XDatabaseLoader.h"
#include "XDisplayImagePacket.h"
//#include "XLineEnhancerPacket.h"
#include "EditLibraryMono.h"
#include "XGeneralFunc.h"
#include "EditLibraryColor.h"
#include <QMessageBox>
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyLineEnhancerForm::PropertyLineEnhancerForm(LayersBase *Base,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	LibFolderID =-1;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempLineEnhancerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
}

PropertyLineEnhancerForm::~PropertyLineEnhancerForm()
{

}

LineEnhancerBase	*PropertyLineEnhancerForm::GetLineEnhancerBase(void)
{
	return (LineEnhancerBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"LineEnhancer");
}


void PropertyLineEnhancerForm::on_pushButtonEditLibrary_clicked()
{
//	DisplayImage	*DProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"LineEnhancerImagePanel" ,/**/"");
//	IntList LayerList;
//	DProp->GetActiveLayerList(IntList &LayerList);

	if(GetLayerNumb(0)>=3 && GetLineEnhancerBase()->ModeOneLayer==-1){
		EditLibraryColor				D(GetLayersBase(),this);
		D.exec();
	}
	else{
		EditLibraryMono				D(GetLayersBase(),this);
		D.exec();
	}
}

void PropertyLineEnhancerForm::on_pushButtonEditLibFolder_clicked()
{
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyLineEnhancerForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}


void	PropertyLineEnhancerForm::BuildForShow(void)
{
}

void	PropertyLineEnhancerForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		CmdGetLineEnhancerLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetLibList->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetLibList->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));
			W=ui.tableWidgetLibList->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetLibList->setItem ( row, 1,W);
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

void	PropertyLineEnhancerForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	LineEnhancerBase	*BBase=GetLineEnhancerBase();
	if(BBase!=NULL){
		CmdCreateTempLineEnhancerLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadLineEnhancerLibraryPacket	Packet(GetLayersBase());
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
	ui.tableWidgetGeneratedLibList->setRowCount(SelectedLibList.GetNumber());
	for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		QTableWidgetItem *W;
		W=ui.tableWidgetGeneratedLibList->item ( row, 0);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetGeneratedLibList->setItem ( row, 0,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(QString::number(a->GetLibID()));
		W=ui.tableWidgetGeneratedLibList->item ( row, 1);
		if(W==NULL){
			W=new QTableWidgetItem();
			ui.tableWidgetGeneratedLibList->setItem ( row, 1,W);
			W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		}
		W->setText(a->GetLibName());
	}
}
bool	PropertyLineEnhancerForm::SaveContent(QIODevice *f)
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
bool	PropertyLineEnhancerForm::LoadContent(QIODevice *f)
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

void PropertyLineEnhancerForm::on_tableWidgetLibList_doubleClicked(QModelIndex)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyLineEnhancerForm::on_tableWidgetGeneratedLibList_doubleClicked(QModelIndex)
{
	on_pushButtonGetBack_clicked();
}

void PropertyLineEnhancerForm::on_pushButtonSetFrom_clicked()
{
	int	r=ui.tableWidgetLibList->currentRow();
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

void PropertyLineEnhancerForm::on_pushButtonGetBack_clicked()
{
	int	r=ui.tableWidgetGeneratedLibList->currentRow();
	if(r<0)
		return;
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		SelectedLibList.RemoveList(a);
		delete	a;
		ShowSelectedLibList();
	}
}

void PropertyLineEnhancerForm::on_ButtonGenerateLibs_clicked()
{
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_0)/*"Generating items"*/,GetLayersBase()->GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCreateLineEnhancer	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.SelectedLibList=SelectedLibList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();

}

void PropertyLineEnhancerForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_6)/*"Library error"*/
											, LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_7)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyLineEnhancerForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadLineEnhancerLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		LineEnhancerBase	*BBase=GetLineEnhancerBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_8)/*"Library error"*/
											, LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_9)/*"Not loaded this library record"*/);
			}
		}
	}
}

void	PropertyLineEnhancerForm::TransmitDirectly(GUIDirectMessage *packet)
{
	LineEnhancerBase	*BBase=GetLineEnhancerBase();

	GUICmdReqLineEnhancerDrawMode	*GUICmdReqLineEnhancerDrawModeVar=dynamic_cast<GUICmdReqLineEnhancerDrawMode *>(packet);
	if(GUICmdReqLineEnhancerDrawModeVar!=NULL){
		if(ui.radioButtonPickupArea->isChecked()==true)
			GUICmdReqLineEnhancerDrawModeVar->DrawingArea=LineEnhancerDrawAttr::_Pickup;
		if(ui.radioButtonBlock->isChecked()==true)
			GUICmdReqLineEnhancerDrawModeVar->DrawingArea=LineEnhancerDrawAttr::_Block;
		if(ui.radioButtonCalc->isChecked()==true)
			GUICmdReqLineEnhancerDrawModeVar->DrawingArea=LineEnhancerDrawAttr::_Calc;
		if(ui.radioButtonMatching->isChecked()==true)
			GUICmdReqLineEnhancerDrawModeVar->DrawingArea=LineEnhancerDrawAttr::_Matching;
		return;
	}
	GUICmdSetLineEnhancerDrawMode	*GUICmdSetLineEnhancerDrawModeVar=dynamic_cast<GUICmdSetLineEnhancerDrawMode *>(packet);
	if(GUICmdSetLineEnhancerDrawModeVar!=NULL){
		if(GUICmdSetLineEnhancerDrawModeVar->DrawingArea==LineEnhancerDrawAttr::_Pickup)
			ui.radioButtonPickupArea->setChecked(true);
		if(GUICmdSetLineEnhancerDrawModeVar->DrawingArea==LineEnhancerDrawAttr::_Block)
			ui.radioButtonBlock->setChecked(true);
		if(GUICmdSetLineEnhancerDrawModeVar->DrawingArea==LineEnhancerDrawAttr::_Calc)
			ui.radioButtonCalc->setChecked(true);
		if(GUICmdSetLineEnhancerDrawModeVar->DrawingArea==LineEnhancerDrawAttr::_Matching)
			ui.radioButtonMatching->setChecked(true);
	}

	/*
	CmdBlockDrawEnd	*BlockDEnd=dynamic_cast<CmdBlockDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		if(ui.toolButtonLibrary->isChecked()==true){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=BlockDEnd->Area;
				BrightHistogramForm	D(BlockDEnd->Area,BlockDEnd->ImagePanelPoint,TempLib->PickupL,TempLib->PickupH,this);
				D.Reflect(TempLib->PickupL,TempLib->PickupH);
				if(D.exec()==(int)true){
					TempLib->PickupL	=D.PickupL;
					TempLib->PickupH	=D.PickupH;
				}
			}
		}
		else if(ui.toolButtonCreateBlock->isChecked()==true){
			CreateManualBlockForm	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.BItem->GetLibID()>=0){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=BlockDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualBlock	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area=A;
						CmdCreateByteArrayFromBlockItemPacket	BCmd;
						BCmd.Point=D.BItem;
						BBase->TransmitDirectly(&BCmd);
						Cmd.BItem=BCmd.Buff;
						Cmd.SendOnly(page,0);
					}
				}
				ShowBlockInfoList();
			}
		}
	}
	*/
}
void PropertyLineEnhancerForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyLineEnhancerForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyLineEnhancerForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_1)/*"Pickup Test"*/);

	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdPickupTestList	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.LibPoint	=TempLib;
		Cmd.SendOnly(GlobalPage,0);
	}

	GetLayersBase()->CloseProcessingForm();
}

void PropertyLineEnhancerForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}


void PropertyLineEnhancerForm::on_radioButtonPickupArea_toggled(bool)
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancerDrawAttr::_Pickup;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
}

void PropertyLineEnhancerForm::on_radioButtonBlock_toggled(bool)
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancerDrawAttr::_Block;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
}

void PropertyLineEnhancerForm::on_radioButtonCalc_toggled(bool)
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancerDrawAttr::_Calc;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
}

void PropertyLineEnhancerForm::on_radioButtonMatching_toggled(bool)
{
	BroadcastShowInEdit();
	if(GetLayersBase()->GetParamComm()->Mastered==true && GetLayersBase()->GetParamComm()->ConnectedPCNumb!=0){
		for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
			GUICmdSetDrawing	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
			Cmd.DrawingArea	=LineEnhancerDrawAttr::_Matching;
			Cmd.InstName	=GetName();
			Cmd.Send(NULL,GlobalPage,0);
		}
	}
}

void	PropertyLineEnhancerForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(data.GetLibrary());
	ui.EditMinDot			->setValue(ALib->MinDot);
	ui.EditMaxDot			->setValue(ALib->MaxDot);
	ui.EditMinSize			->setValue(ALib->MinSize);
	ui.EditMaxSize			->setValue(ALib->MaxSize);
	ui.EditLimitDot			->setValue(ALib->LimitDot);
	ui.EditShrinkDot		->setValue(ALib->ShrinkDot);
	ui.EditPriority			->setValue(ALib->Priority);
	ui.EditStepDot			->setValue(ALib->StepDot);
	ui.EditSearchBlockWidth	->setValue(ALib->SearchBlockWidth);
}

void	PropertyLineEnhancerForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	LineEnhancerLibrary	*ALib=dynamic_cast<LineEnhancerLibrary *>(data.GetLibrary());
	ALib->MinDot			=ui.EditMinDot			->value();
	ALib->MaxDot			=ui.EditMaxDot			->value();
	ALib->MinSize			=ui.EditMinSize			->value();
	ALib->MaxSize			=ui.EditMaxSize			->value();
	ALib->LimitDot			=ui.EditLimitDot		->value();
	ALib->ShrinkDot			=ui.EditShrinkDot		->value();
	ALib->Priority			=ui.EditPriority		->value();
	ALib->StepDot			=ui.EditStepDot			->value();
	ALib->SearchBlockWidth	=ui.EditSearchBlockWidth->value();
}

void PropertyLineEnhancerForm::on_ButtonLibSave_clicked()
{
	if(TempLib->GetLibID()<0)
		return;
	GetLibraryFromWindow(*TempLib);
	if(TempLib->GetLibName()==/**/""){
		QMessageBox::StandardButton ret=QMessageBox::warning ( NULL	, LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_10)/*"Warning"*/
																	, LangSolver.GetString(PropertyLineEnhancerForm_LS,LID_11)/*"No Library Name"*/
																	, QMessageBox::Ok | QMessageBox::Cancel);
		if(ret!=QMessageBox::Ok)
			return;
	}
	CmdUpdateLineEnhancerLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	LineEnhancerBase	*BBase=GetLineEnhancerBase();
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

