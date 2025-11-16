#include "CreateManualItemFormResource.h"
#include "PropertyMeasureHolePosForm.h"
#include "XMeasureHolePosPacket.h"
#include "EditLibraryForm.h"
#include "CreateManualItemForm.h"
#include "SelectLibraryDialog.h"
#include "XDisplayImage.h"
#include "XDisplayImagePacket.h"
#include "ModifyItemDialog.h"
#include "XGeneralDialog.h"
#include <QMessageBox>
#include "XGeneralDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMeasureHolePosForm::PropertyMeasureHolePosForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);

	LibFolderID =-1;
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();
	ui.tableWidgetBlockInf->setColumnWidth (0, 30);
	ui.tableWidgetBlockInf->setColumnWidth (1, 80);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMeasureHolePosLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	ColorGenerator	.setParent(ui.frameColorCube);
	ColorGenerator	.Fit(ui.frameColorCube);
	int	tPage=0;
	if(GetLayerNumb(tPage)>=3){
		ui.stackedWidget->setCurrentIndex(0);
	}
	else{
		ui.stackedWidget->setCurrentIndex(1);
	}

	ui.tableWidgetHoleList->setColumnWidth(0,32);
	ui.tableWidgetHoleList->setColumnWidth(1,32);
	ui.tableWidgetHoleList->setColumnWidth(2,100);
	ui.tableWidgetHoleList->setColumnWidth(3,32);

	ShowListGrid();
}

PropertyMeasureHolePosForm::~PropertyMeasureHolePosForm()
{
	if(TempLib!=NULL)
		delete	TempLib;
}

MeasureHolePosBase	*PropertyMeasureHolePosForm::GetMeasureHolePosBase(void)
{
	return (MeasureHolePosBase *)GetLayersBase()->GetAlgorithmBase(/**/"Measure",/**/"MeasureHolePos");
}


void	PropertyMeasureHolePosForm::TransmitDirectly(GUIDirectMessage *packet)
{
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();

	CmdMeasureHolePosDrawModePacket	*DMode=dynamic_cast<CmdMeasureHolePosDrawModePacket	*>(packet);
	if(DMode!=NULL){
		if(ui.toolButtonArea->isChecked()==true)
			DMode->DrawAttr->DMode	=MeasureHolePosDrawAttr::__Mode_Area;
		if(ui.toolButtonHole->isChecked()==true)
			DMode->DrawAttr->DMode	=MeasureHolePosDrawAttr::__Mode_Hole;
		if(ui.toolButtonEdge->isChecked()==true)
			DMode->DrawAttr->DMode	=MeasureHolePosDrawAttr::__Mode_Edge;

		DMode->DrawAttr->NormalColor.setAlpha(BBase->TransparentLevel);
		DMode->DrawAttr->SelectedColor.setAlpha(BBase->TransparentLevel);
		DMode->DrawAttr->ActiveColor.setAlpha(BBase->TransparentLevel);
		return;
	}

	CmdMeasureHolePosDrawEnd	*BlockDEnd=dynamic_cast<CmdMeasureHolePosDrawEnd *>(packet);
	if(BlockDEnd!=NULL){
		CreateManualItemForm	D(GetLayersBase(),NULL);
		if(D.exec()==(int)true){
			IntList PageList;
			/*
			GetLayersBase()->GetLocalPageFromArea(BlockDEnd->Area,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				FlexArea	A=BlockDEnd->Area;
				pdata->ClipMoveAreaFromGlobal(A);
				if(A.GetPatternByte()>0){
					GUICmdSendAddManualMeasureHolePos	Cmd(GetLayersBase(),sRoot,sName,page);
					Cmd.Area=A;
					CmdCreateByteArrayFromMeasureHolePosItemPacket	BCmd(GetLayersBase());
					BCmd.Point=D.BItem;
					BBase->TransmitDirectly(&BCmd);
					Cmd.BItem=BCmd.Buff;
					Cmd.Send(NULL,page,0);
				}
			}
			*/
			GetLayersBase()->GetLocalPageFromVector(BlockDEnd->Vector,PageList);
			for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
				int	page=P->GetValue();
				DataInPage	*pdata=GetLayersBase()->GetPageData(page);
				VectorLineBase	*v=BlockDEnd->Vector->CreateEmpty();
				*v=*BlockDEnd->Vector;
				pdata->ClipMoveVectorFromGlobal(v);

				GUICmdSendAddManualMeasureHolePos	Cmd(GetLayersBase(),sRoot,sName,page);
				Cmd.Vector=v->CreateDup();
					
				CmdCreateByteArrayFromMeasureHolePosItemPacket	BCmd(GetLayersBase());
				BCmd.Point=D.BItem;
				BBase->TransmitDirectly(&BCmd);
				Cmd.BItem=BCmd.Buff;
				Cmd.Send(NULL,page,0);
			}
		}
		ShowListGrid();
	}
	GUICmdMeasureHolePosGetColorMap	*GUICmdMeasureHolePosGetColorMapVar=dynamic_cast<GUICmdMeasureHolePosGetColorMap *>(packet);
	if(GUICmdMeasureHolePosGetColorMapVar!=NULL){
		IntList PageList;
		GetLayersBase()->GetLocalPageFromArea(GUICmdMeasureHolePosGetColorMapVar->Area,PageList);
		for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
			int	page=P->GetValue();
			DataInPage	*pdata=GetLayersBase()->GetPageData(page);
			FlexArea	A=GUICmdMeasureHolePosGetColorMapVar->Area;
			pdata->ClipMoveAreaFromGlobal(A);
			if(A.GetPatternByte()>0){
				CmdReqMeasureHolePosColorMap	RCmd(GetLayersBase(),sRoot,sName,page);
				CmdAckMeasureHolePosColorMap	ACmd(GetLayersBase(),sRoot,sName,page);
				RCmd.Area=A;
				RCmd.Send(page,0,ACmd);

				ColorGenerator.Cube=ACmd.Color;
				ColorGenerator.InitializedDoneCube();
				ColorGenerator.Repaint();
			}
		}
	}
}


void	PropertyMeasureHolePosForm::ShowLibList(void)
{
	ui.tableWidgetBlockInf->setRowCount(0);
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	if(BBase!=NULL){
		CmdGetMeasureHolePosLibraryListPacket	Packet(GetLayersBase());
		Packet.LibFolderID=LibFolderID;
		BBase->TransmitDirectly(&Packet);
		LibList	=Packet.AList;
		int	row=0;
		ui.tableWidgetBlockInf->setRowCount(Packet.AList.GetNumber());
		for(AlgorithmLibraryList *a=Packet.AList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			QTableWidgetItem *W;
			W=ui.tableWidgetBlockInf->item ( row, 0);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetBlockInf->setItem ( row, 0,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);			
			}
			W->setText(QString::number(a->GetLibID()));

			W=ui.tableWidgetBlockInf->item ( row, 1);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetBlockInf->setItem ( row, 1,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			W->setText(a->GetLibName());

			W=ui.tableWidgetBlockInf->item ( row, 2);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetBlockInf->setItem ( row, 2,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			//W->setText(QString::number(a->MinDiameter));

			W=ui.tableWidgetBlockInf->item ( row, 3);
			if(W==NULL){
				W=new QTableWidgetItem();
				ui.tableWidgetBlockInf->setItem ( row, 3,W);
				W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
			}
			//W->setText(QString::number(a->MaxDiameter));
		}
	}
}
void	iSetDataToTable(QTableWidget *W ,int col ,int row ,const QVariant &value)
{
	W->model()->setData(W->model()->index(row,col),value);
}

int	SortFuncLTable(const void *a ,const void *b)
{
	HolePosListForPacket	*ai=((HolePosListForPacket **)a)[0];
	HolePosListForPacket	*bi=((HolePosListForPacket **)b)[0];

	bool	aok;
	double	An=ai->ItemName.toDouble(&aok);
	bool	bok;
	double	Bn=bi->ItemName.toDouble(&bok);
	if(aok==true && bok==true){
		if(An>Bn)
			return 1;
		if(An<Bn)
			return -1;
		return 0;
	}
	if(ai->ItemName>bi->ItemName)
		return 1;
	if(ai->ItemName<bi->ItemName)
		return -1;
	return 0;
}

void	PropertyMeasureHolePosForm::ShowListGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;
	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendItemList	**BmpReceiver=new GUICmdSendItemList*[GetParamGlobal()->PageNumb];
	GUICmdReqItemList	**BmpRequester=new GUICmdReqItemList*[GetParamGlobal()->PageNumb];
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		BmpReceiver[page]=new GUICmdSendItemList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[page]=new GUICmdReqItemList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
	}

	ListInfo.RemoveAll();
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		if(BmpRequester[page]->Send(BmpRequester[page]->GetGlobalPage(),0,*BmpReceiver[page],60000)==true
		&& BmpReceiver[page]->IsReceived()==true){
			ListInfo+=BmpReceiver[page]->ListInfo;
		}
	}
	for(int page=0;page<GetParamGlobal()->PageNumb;page++){
		delete	BmpRequester[page];
		delete	BmpReceiver[page];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	int	N=0;
	int	Numb=ListInfo.GetNumber();
	ui.tableWidgetHoleList->setRowCount(Numb);
	HolePosListForPacket **LTable=new HolePosListForPacket*[Numb];
	int	n=0;
	for(HolePosListForPacket *L=ListInfo.GetFirst();L!=NULL;L=L->GetNext(),N++){
		LTable[N]=L;
	}
	while(ListInfo.GetFirst()!=NULL){
		HolePosListForPacket *M=ListInfo.GetFirst();
		ListInfo.RemoveList(M);
	}

	QSort(LTable,N,sizeof(HolePosListForPacket *),SortFuncLTable);

	ui.tableWidgetHoleList->setUpdatesEnabled(false);
	for(int i=0;i<N;i++){
		HolePosListForPacket *L=LTable[i];
		ListInfo.AppendList(L);

		iSetDataToTable(ui.tableWidgetHoleList ,0,i ,QString::number(L->Page));
		iSetDataToTable(ui.tableWidgetHoleList ,1,i ,QString::number(L->ItemID));
		iSetDataToTable(ui.tableWidgetHoleList ,2,i ,L->ItemName);
		iSetDataToTable(ui.tableWidgetHoleList ,3,i ,QString::number(L->SearchDot));
		}
	ui.tableWidgetHoleList->setUpdatesEnabled(true);
	delete	[]LTable;

	ReEntrant=false;
}

void PropertyMeasureHolePosForm::on_tableWidgetBlockInfo_clicked(const QModelIndex &Index)
{
	int	r=Index.row();
	AlgorithmLibraryList	*a=LibList.GetItem(r);
	if(a!=NULL){
		TempLib->SetLibID(a->GetLibID());

		CmdLoadMeasureHolePosLibraryPacket	Packet(GetLayersBase());
		Packet.Point=TempLib;
		MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
		if(BBase!=NULL){
			BBase->TransmitDirectly(&Packet);
			if(Packet.Success==true){
				ShowLibrary(*TempLib);
			}
			else{
				QMessageBox::critical(NULL, LangSolver.GetString(PropertyMeasureHolePosForm_LS,LID_2)/*"Library error"*/, LangSolver.GetString(PropertyMeasureHolePosForm_LS,LID_3)/*"Not loaded this library record"*/);
			}
		}
	}
}

void PropertyMeasureHolePosForm::on_pushButtonNColor_clicked()
{

}

void	PropertyMeasureHolePosForm::BuildForShow(void)
{
}

void	PropertyMeasureHolePosForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui.labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}


void	PropertyMeasureHolePosForm::ShowLibrary(AlgorithmLibraryLevelContainer &data)
{
	if(data.GetLibID()<0)
		ui.EditLibID->setText(/**/"");
	else
		ui.EditLibID->setText(QString::number(data.GetLibID()));
	ui.EditLibName	->setText(data.GetLibName());
	int	tPage=0;
	MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(data.GetLibrary());
	if(GetLayerNumb(tPage)>=3){
		ColorGenerator.Cube=ALib->HoleColor;
		ColorGenerator.InitializedDoneCube();
		ColorGenerator.Repaint();
	}
	else{
		int	ColL,ColH;
		ALib->HoleColor.GetMonoColorRange(ColL,ColH);
		ui.EditPickupL	->setValue(ColL);
		ui.EditPickupH	->setValue(ColH);
	}

	ui.doubleSpinBoxDiaPrecision	->setValue(ALib->DiaPrecision);
	ui.doubleSpinBoxPosPrecision	->setValue(ALib->PosPrecision);
	ui.spinBoxNoiseSize				->setValue(ALib->NoiseSize);
	ui.spinBoxBandWidth				->setValue(ALib->BandWidth);
	ui.EditSearchDot				->setValue(ALib->SearchDot);
}

void	PropertyMeasureHolePosForm::GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data)
{
	data.SetLibName(ui.EditLibName	->text());

	MeasureHolePosLibrary	*ALib=dynamic_cast<MeasureHolePosLibrary *>(data.GetLibrary());
	ALib->DiaPrecision	=ui.doubleSpinBoxDiaPrecision	->value();
	ALib->PosPrecision	=ui.doubleSpinBoxPosPrecision	->value();
	ALib->NoiseSize		=ui.spinBoxNoiseSize	->value();
	ALib->BandWidth		=ui.spinBoxBandWidth	->value();
	ALib->SearchDot		=ui.EditSearchDot	->value();
	int	tPage=0;
	if(GetLayerNumb(tPage)>=3){
		ALib->HoleColor	=ColorGenerator.Cube;
	}
	else{
		int	ColL=ui.EditPickupL	->value();
		int	ColH=ui.EditPickupH	->value();
		ALib->HoleColor.SetMonoColorRange(ColL,ColH,ColL,ColH,ColL,ColH);
	}
}

void PropertyMeasureHolePosForm::on_pushButtonCreateNew_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CmdInsertMeasureHolePosLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	ShowLibList();
}

void PropertyMeasureHolePosForm::on_pushButtonUpdate_clicked()
{
	GetLibraryFromWindow(*TempLib);
	CmdUpdateMeasureHolePosLibraryPacket	Cmd(GetLayersBase());
	Cmd.Point=TempLib;
	TempLib->SetLibFolderID(LibFolderID);
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	if(BBase!=NULL){
		BBase->TransmitDirectly(&Cmd);
	}
	ShowLibList();
}

void PropertyMeasureHolePosForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryForm	D(GetLayersBase());
	D.exec();
}

void PropertyMeasureHolePosForm::on_pushButtonCreateNewMono_clicked()
{
	on_pushButtonCreateNew_clicked();
}

void PropertyMeasureHolePosForm::on_pushButtonUpdateMono_clicked()
{
	on_pushButtonUpdate_clicked();
}

void PropertyMeasureHolePosForm::on_pushButtonEditLibFolder_clicked()
{
	MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void PropertyMeasureHolePosForm::on_toolButtonArea_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMeasureHolePosForm::on_toolButtonHole_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMeasureHolePosForm::on_toolButtonEdge_clicked()
{
	BroadcastShowInEdit();
}

void PropertyMeasureHolePosForm::on_tableWidgetHoleList_clicked(const QModelIndex &MIndex)
{
	HolePosListForPacket *L=ListInfo.GetItem(MIndex.row());
	if(L==NULL)
		return;

	DataInPage	*P=GetLayersBase()->GetPageData(GetLayersBase()->GetLocalPageFromGlobal(L->Page));
	if(P!=NULL){
		CmdDrawImageRectPacket	Cmd( GetLayersBase()
									,L->x1+P->GetOutlineOffset()->x,L->y1+P->GetOutlineOffset()->y
									,L->x2+P->GetOutlineOffset()->x,L->y2+P->GetOutlineOffset()->y);
		GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Measure" ,/**/"MeasureHolePosImagePanel" ,/**/"");
		if(GProp!=NULL)
			GProp->TransmitDirectly(&Cmd);
		CmdDrawImageActivate	ACmd(GetLayersBase(),L->Page,0,L->ItemID);
		if(GProp!=NULL)
			GProp->TransmitDirectly(&ACmd);
	}
}

void PropertyMeasureHolePosForm::on_tableWidgetHoleList_doubleClicked(const QModelIndex &index)
{
	QModelIndex	RIndex=ui.tableWidgetHoleList->currentIndex();
	if(RIndex.isValid()==false)
		return;
	int	R=RIndex.row();
	HolePosListForPacket *L=ListInfo.GetItem(R);
	if(L==NULL)
		return;

	GUICmdReqItemThreshold	RCmd(GetLayersBase(),sRoot,sName,L->Page);
	GUICmdSendItemThreshold	SCmd(GetLayersBase(),sRoot,sName,L->Page);
	if(RCmd.Send(RCmd.GetGlobalPage(),0,SCmd,60000)==true
	&& SCmd.IsReceived()==true){
		ModifyItemDialog	DForm(GetLayersBase(),SCmd.ItemName ,SCmd.Thre);
		if(DForm.exec()==true){

			GUICmdSetItemThreshold	rCmd(GetLayersBase(),sRoot,sName,L->Page);
			rCmd.ItemID		=L->ItemID;
			rCmd.ItemName	=DForm.ItemName;
			MeasureHolePosBase	*BBase=GetMeasureHolePosBase();
			if(BBase==NULL)
				return;
			CmdCreateThresholdPacket	PCmd(GetLayersBase());
			BBase->TransmitDirectly(&PCmd);
			rCmd.Thre		=PCmd.Thre;
			rCmd.Send(NULL,L->Page,0);
		}
	}
	ShowListGrid();
}
