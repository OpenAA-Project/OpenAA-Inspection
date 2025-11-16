#include "BrightHistgramFormResource.h"
#include "PropertyAreaShaderForm.h"
#include "XAreaShaderPacket.h"
#include "XDisplayImage.h"
#include "XGeneralFunc.h"
#include "CreateManualItemForm.h"
#include "XDisplayImagePacket.h"
#include "XPropertyAreaShaderPacket.h"
#include "BrightHistgramForm.h"
#include "EditLibrary.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyAreaShaderForm::PropertyAreaShaderForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	LibFolderID =-1;
	AreaShaderBase	*BBase=GetAreaShaderBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui.tableWidgetLibList->setColumnWidth (0, 30);
	ui.tableWidgetLibList->setColumnWidth (1, 80);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (0, 30);
	ui.tableWidgetGeneratedLibList	->setColumnWidth (1, 80);	

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempAreaShaderLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
}

PropertyAreaShaderForm::~PropertyAreaShaderForm()
{

}

AreaShaderBase	*PropertyAreaShaderForm::GetAreaShaderBase(void)
{
	return (AreaShaderBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AreaShader");
}

void	PropertyAreaShaderForm::BuildForShow(void)
{
	ShowAreaGrid();
}

void	PropertyAreaShaderForm::TransmitDirectly(GUIDirectMessage *packet)
{
	AreaShaderBase	*BBase=GetAreaShaderBase();

	CmdAreaShaderDrawEnd	*AreaShaderDEnd=dynamic_cast<CmdAreaShaderDrawEnd *>(packet);
	if(AreaShaderDEnd!=NULL){
		if(ui.tabWidget->currentIndex()==0){
			if(TempLib->GetLibID()>=0){
				//GlobalPickupArea+=BlockDEnd->Area;
				AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(TempLib->GetLibrary());
				BrightHistgramForm	D(AreaShaderDEnd->Area,AreaShaderDEnd->ImagePanelPoint
										,ALib->PickupColorL,ALib->PickupColorH,this);
				D.Reflect(ALib->PickupColorL,ALib->PickupColorH);
				if(D.exec()==(int)true){
					ALib->PickupColorL	=D.PickupL;
					ALib->PickupColorH	=D.PickupH;
				}
			}
		}
		else{
			CreateManualItemForm	D(GetLayersBase(),this);
			if(D.exec()==(int)true){
				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(AreaShaderDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=AreaShaderDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						GUICmdSendAddManualAreaShader	Cmd(GetLayersBase(),sRoot,sName,page);
						Cmd.Area		=A;
						Cmd.LayerList	=AreaShaderDEnd->LayerList;
						Cmd.CellSize	=D.CellSize;
						Cmd.AdoptRate	=D.AdoptRate;
						Cmd.Fixed		=D.Fixed;
						Cmd.Average		=D.Average;
						Cmd.Sigma		=D.Sigma;		//•W€•Î·
						Cmd.SendOnly(GetLayersBase()->GetGlobalPageFromLocal(page),0);
					}
				}
			}
			ShowAreaGrid();
		}
		return;
	}
	CmdAreaShaderDrawAttr	*CmdAreaShaderDrawAttrVar=dynamic_cast<CmdAreaShaderDrawAttr *>(packet);
	if(CmdAreaShaderDrawAttrVar!=NULL){
		if(ui.tabWidget->currentIndex()==0){
			CmdAreaShaderDrawAttrVar->Point->Generated=true;
		}
		else{
			CmdAreaShaderDrawAttrVar->Point->Generated=false;
		}
		return;
	}
}

void	iSetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}
void	PropertyAreaShaderForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendAreaShaderList	**BmpReceiver=new GUICmdSendAreaShaderList*[GetParamGlobal()->PageNumb];
	GUICmdReqAreaShaderList		**BmpRequester=new GUICmdReqAreaShaderList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendAreaShaderList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqAreaShaderList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}

	AreaShaderInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page])==true
		&& BmpReceiver[page]->IsReceived()==true){
			AreaShaderInfo+=BmpReceiver[page]->AreaShaderInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=AreaShaderInfo.GetNumber();
	ui.tableWidgetAreaShader->setRowCount(Numb);
	AreaShaderListForPacket **LTable=new AreaShaderListForPacket*[Numb];
	int	n=0;
	for(AreaShaderListForPacket *L=AreaShaderInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}

	ui.tableWidgetAreaShader->setUpdatesEnabled(false);
	//#pragma omp parallel                             
	//{                                                
	//	#pragma omp for
		for(int i=0;i<N;i++){
			AreaShaderListForPacket *L=LTable[i];

			iSetDataToTable(ui.tableWidgetAreaShader ,0,i,QString::number(L->Page));
			iSetDataToTable(ui.tableWidgetAreaShader ,1,i,QString::number(L->Layer));
			iSetDataToTable(ui.tableWidgetAreaShader ,2,i
						,QString(/**/"(")
						+QString::number(L->x1)+QString(/**/",")+QString::number(L->y1)
						+QString(/**/")-(")
						+QString::number(L->x2)+QString(/**/",")+QString::number(L->y2)
						+QString(/**/")"));
		}
	//}
	delete	[]LTable;
	ui.tableWidgetAreaShader->setUpdatesEnabled(true);

	ReEntrant=false;
}



void PropertyAreaShaderForm::on_tableWidgetAreaShader_clicked(const QModelIndex &MIndex)
{
	int	Row=MIndex.row();
	if(Row<0){
		return;
	}
	AreaShaderListForPacket *L=AreaShaderInfo.GetItem(Row);
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(L->Page);
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AreaShaderImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,L->Layer,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
	ui.spinBoxCellSize			->setValue	(L->CellSize);
	ui.doubleSpinBoxAdoptRate	->setValue	(L->AdoptRate);
	ui.checkBoxFixed			->setChecked(L->Fixed);
	ui.doubleSpinBoxAverage		->setValue	(L->Average);
	ui.doubleSpinBoxSigma		->setValue	(L->Sigma);
}

//==============================================================================


void PropertyAreaShaderForm::on_pushButtonEditLibFolder_clicked()
{
	AreaShaderBase	*BBase=GetAreaShaderBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void	PropertyAreaShaderForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}

void	PropertyAreaShaderForm::ShowLibList(void)
{
	ui.tableWidgetLibList->setRowCount(0);
	AreaShaderBase	*BBase=GetAreaShaderBase();
	if(BBase!=NULL){
		CmdGetAreaShaderLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyAreaShaderForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	AreaShaderBase	*BBase=GetAreaShaderBase();
	if(BBase!=NULL){
		CmdCreateTempAreaShaderLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadAreaShaderLibraryPacket	Packet(GetLayersBase());
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
void PropertyAreaShaderForm::on_tableWidgetLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());
		CmdLoadAreaShaderLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaShaderBase	*BBase=GetAreaShaderBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}
void PropertyAreaShaderForm::SetLayersFromLib(IntList &LayerList)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AreaShaderImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->SetActiveLayerList(LayerList);
		}
	}
}

void PropertyAreaShaderForm::on_tableWidgetLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSetFrom_clicked();
}

void PropertyAreaShaderForm::on_tableWidgetGeneratedLibList_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=SelectedLibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadAreaShaderLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		AreaShaderBase	*BBase=GetAreaShaderBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				SetLayersFromLib(TempLib->GetAdaptedPickLayers());
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL	, /**/"Library error"
											, /**/"Not loaded this library record");
			}
		}
	}
}

void PropertyAreaShaderForm::on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index)
{
	on_pushButtonGetBack_clicked();
}

void PropertyAreaShaderForm::on_pushButtonSetFrom_clicked()
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

void PropertyAreaShaderForm::on_pushButtonGetBack_clicked()
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

void PropertyAreaShaderForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}

void PropertyAreaShaderForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void PropertyAreaShaderForm::on_ButtonPickupTest_clicked()
{
	if(TempLib==NULL)
		return;

	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyAreaShaderForm_LS,LID_0)/*"Pickup Test"*/);

	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AreaShaderImagePanel" ,/**/"");
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

void PropertyAreaShaderForm::on_ButtonPickupClearTest_clicked()
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdTestClear	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.Send(NULL,GlobalPage,0);
	}
}

void PropertyAreaShaderForm::on_pushButtonEditLibrary_clicked()
{
	EditLibrary	D(GetLayersBase(),this);
	D.exec();
}

void PropertyAreaShaderForm::on_ButtonGenerateLibs_clicked()
{
	IntList LayerList;
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AreaShaderImagePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImage	*di=dynamic_cast<DisplayImage *>(GProp);
		if(di!=NULL){
			di->GetActiveLayerList(LayerList);
		}
	}

	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm(LangSolver.GetString(PropertyAreaShaderForm_LS,LID_1)/*"Generating items"*/,GetLayersBase()->GetPageNumb());
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdCreateAreaShader	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.SelectedLibList=SelectedLibList;
		RCmd.LayerList		=LayerList;
		RCmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyAreaShaderForm::on_ButtonLibSave_clicked()
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
	CmdUpdateAreaShaderLibraryPacket	Packet(GetLayersBase());
	Packet.Point=TempLib;
	AreaShaderBase	*BBase=GetAreaShaderBase();
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

void	PropertyAreaShaderForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());

	AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(data.GetLibrary());
	ui.EditMinDot		->setValue(ALib->MinDot);
	ui.EditMaxDot		->setValue(ALib->MaxDot);
	ui.EditMinSize		->setValue(ALib->MinSize);
	ui.EditMaxSize		->setValue(ALib->MaxSize);
	ui.EditShrinkDot	->setValue(ALib->ShrinkDot);
	ui.EditPriority		->setValue(ALib->Priority);
}

void	PropertyAreaShaderForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	AreaShaderLibrary	*ALib=dynamic_cast<AreaShaderLibrary *>(data.GetLibrary());
	ALib->MinDot		=ui.EditMinDot		->value();
	ALib->MaxDot		=ui.EditMaxDot		->value();
	ALib->MinSize		=ui.EditMinSize		->value();
	ALib->MaxSize		=ui.EditMaxSize		->value();
	ALib->ShrinkDot		=ui.EditShrinkDot	->value();
	ALib->Priority		=ui.EditPriority	->value();
}
void PropertyAreaShaderForm::on_tabWidget_currentChanged(int index)
{
	ShowAreaGrid();
}
