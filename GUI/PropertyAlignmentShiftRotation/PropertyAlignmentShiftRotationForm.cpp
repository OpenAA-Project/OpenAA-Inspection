#include "PropertyAlignmentShiftRotationForm.h"
#include "ui_PropertyAlignmentShiftRotationForm.h"
#include "XGeneralFunc.h"
#include "SelectLibFolderDialog.h"
#include "XPacketAlignmentShiftRotation.h"
#include "EditAngleRangeDialog.h"
#include "ImageControlTools.h"
#include "XDisplayImagePacket.h"
#include "AlignmentShiftRotationLibraryDialog.h"

extern	const	char	*sRoot;
extern	const	char	*sName;
PropertyAlignmentShiftRotationForm::PropertyAlignmentShiftRotationForm(LayersBase *Base,QWidget *parent)
    : GUIFormBase(Base,parent),
     ui(new Ui::PropertyAlignmentShiftRotationForm)
{
    ui->setupUi(this);
	//LangSolver.SetUI(this);

	
	::SetColumnWidthInTable(ui->tableWidgetLibList,0,30);
	::SetColumnWidthInTable(ui->tableWidgetLibList,1,60);

	::SetColumnWidthInTable(ui->tableWidgetGeneratedLibList,0,30);
	::SetColumnWidthInTable(ui->tableWidgetGeneratedLibList,1,60);
	
	::SetColumnWidthInTable(ui->tableWidgetItemList,0,10);
	::SetColumnWidthInTable(ui->tableWidgetItemList,1,10);
	::SetColumnWidthInTable(ui->tableWidgetItemList,2,10);
	::SetColumnWidthInTable(ui->tableWidgetItemList,3,30);
	::SetColumnWidthInTable(ui->tableWidgetItemList,4,30);
	InstallIgnoreKeyForChild();

}

PropertyAlignmentShiftRotationForm::~PropertyAlignmentShiftRotationForm()
{
    delete ui;
}

AlignmentShiftRotationBase	*PropertyAlignmentShiftRotationForm::GetAlignmentShiftRotationBase(void)
{
	AlignmentShiftRotationBase *BBase=(AlignmentShiftRotationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AlignmentShiftRotation");
	return BBase;

}

void PropertyAlignmentShiftRotationForm::on_toolButtonAlignmentShiftRotationItem_clicked()
{

}


void PropertyAlignmentShiftRotationForm::on_toolButtonVHLineGroup_clicked()
{

}


void PropertyAlignmentShiftRotationForm::on_comboBoxAngle_currentIndexChanged(int index)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentShiftRotationImagePanel" ,/**/"");
	if(GProp!=NULL)
		GProp->Repaint();
}


void PropertyAlignmentShiftRotationForm::on_pushButtonEditLibFolder_clicked()
{
	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	SelectLibFolderDialog	D(BBase->GetLibType(),GetLayersBase(),this);
	if(D.exec()==(int)true){
		SetLibFolder(D.SelectedLibFolderID,D.SelectedFolderName);
	}
}

void	PropertyAlignmentShiftRotationForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	ShowLibList();
}
void PropertyAlignmentShiftRotationForm::on_tableWidgetLibList_cellDoubleClicked(int row, int column)
{
	on_pushButtonSetFrom_clicked();
}


void PropertyAlignmentShiftRotationForm::on_tableWidgetGeneratedLibList_cellDoubleClicked(int row, int column)
{
	on_pushButtonGetBack_clicked();
}


void PropertyAlignmentShiftRotationForm::on_pushButtonEditLibrary_clicked()
{
	AlignmentShiftRotationLibraryDialog	D(GetLayersBase(),this);
	D.Initial(GetAlignmentShiftRotationBase());
	D.exec();
}


void PropertyAlignmentShiftRotationForm::on_tableWidgetItemList_itemSelectionChanged()
{
	int	Row=ui->tableWidgetItemList->currentRow();
	AlignmentShiftRotationItemList *a=ItemList[Row];
	if(a!=NULL){
		ui->comboBoxAngle->clear();
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(a->Data.Page);
		GUICmdReqAlignmentShiftRotationItemAngleList	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendAlignmentShiftRotationItemAngleList	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		RCmd.Phase=a->Data.Phase;
		RCmd.ItemID=a->Data.ItemID;
		if(RCmd.Send(GlobalPage,0,SCmd)==true){
			for(DoubleClass *a=SCmd.AngleList.GetFirst();a!=NULL;a=a->GetNext()){
				ui->comboBoxAngle->addItem(QString::number(a->GetValue(),'f',4));
			}
			ui->comboBoxAngle->setCurrentIndex(0);
		}
		DataInPage	*P=GetLayersBase()->GetPageData(a->Data.Page);
		if(P!=NULL){
			CmdDrawImageRectPacket	Cmd( GetLayersBase()
										,a->Data.x1+P->GetOutlineOffset()->x,a->Data.y1+P->GetOutlineOffset()->y
										,a->Data.x2+P->GetOutlineOffset()->x,a->Data.y2+P->GetOutlineOffset()->y);
			GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"AlignmentShiftRotationImagePanel" ,/**/"");
			if(GProp!=NULL)
				GProp->TransmitDirectly(&Cmd);
			CmdDrawImageActivate	ACmd(GetLayersBase(),a->Data.Page,0,a->Data.ItemID);
			if(GProp!=NULL)
				GProp->TransmitDirectly(&ACmd);
		}
	}
}


void PropertyAlignmentShiftRotationForm::on_pushButtonSetFrom_clicked()
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


void PropertyAlignmentShiftRotationForm::on_pushButtonGetBack_clicked()
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


void PropertyAlignmentShiftRotationForm::on_pushButtonSetFromAll_clicked()
{
	SelectedLibList.RemoveAll();
	for(AlgorithmLibraryList *a=LibList.GetFirst();a!=NULL;a=a->GetNext()){
		SelectedLibList.AppendList(new AlgorithmLibraryList(LibType,a->GetLibID(),a->GetLibName()));
	}
	ShowSelectedLibList();
}


void PropertyAlignmentShiftRotationForm::on_pushButtonGetBackAll_clicked()
{
	SelectedLibList.RemoveAll();
	ShowSelectedLibList();
}

void	PropertyAlignmentShiftRotationForm::ShowLibList(void)
{
	ui->tableWidgetLibList->setRowCount(0);
	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	if(BBase!=NULL){
		CmdGetAlignmentShiftRotationLibraryListPacket	Packet(GetLayersBase());
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

void	PropertyAlignmentShiftRotationForm::ShowSelectedLibList(void)
{
	struct	AlgorithmLibraryListClass	DDim[100];

	AlignmentShiftRotationBase	*BBase=GetAlignmentShiftRotationBase();
	if(BBase!=NULL){
		CmdCreateTempAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		AlgorithmLibraryLevelContainer	*SLib=Packet.Point;

		int	row=0;
		for(AlgorithmLibraryList *a=SelectedLibList.GetFirst();a!=NULL;a=a->GetNext(),row++){
			DDim[row].a=a;
			SLib->SetLibID(a->GetLibID());

			CmdLoadAlignmentShiftRotationLibraryPacket	Packet(GetLayersBase());
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
void	PropertyAlignmentShiftRotationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdAlignmentShiftRotationDrawModePacket *CmdAlignmentShiftRotationDrawModePacketVar = dynamic_cast<CmdAlignmentShiftRotationDrawModePacket *>(packet);
	if(CmdAlignmentShiftRotationDrawModePacketVar!=NULL){
		if(ui->toolButtonAlignmentShiftRotationItem->isChecked()==true){
			CmdAlignmentShiftRotationDrawModePacketVar->DrawModeArea = true;
		}
		else{
			CmdAlignmentShiftRotationDrawModePacketVar->DrawModeArea = false;
		}
		if(ui->toolButtonVHLineGroup->isChecked()==true){
			int	Row=ui->tableWidgetItemList->currentRow();
			AlignmentShiftRotationItemList *a=ItemList[Row];
			int	Index=ui->comboBoxAngle->currentIndex();
			if(a!=NULL && Index>=0){
				CmdAlignmentShiftRotationDrawModePacketVar->DrawModeHVLines = true;
				CmdAlignmentShiftRotationDrawModePacketVar->HVLinesPage		=a->Data.Page;
				CmdAlignmentShiftRotationDrawModePacketVar->HVLinesPhase	=a->Data.Phase;
				CmdAlignmentShiftRotationDrawModePacketVar->HVLinesItemID	=a->Data.ItemID;
				CmdAlignmentShiftRotationDrawModePacketVar->HVLinesPage		=a->Data.Page;
				CmdAlignmentShiftRotationDrawModePacketVar->HVLinesAngleIndex=Index;
			}
			else{
				CmdAlignmentShiftRotationDrawModePacketVar->DrawModeHVLines = false;
			}
		}
		else{
			CmdAlignmentShiftRotationDrawModePacketVar->DrawModeHVLines = false;
		}
		return;
	}
	CmdAlignmentShiftRotationDrawEnd *CmdAlignmentShiftRotationDrawEndVar = dynamic_cast<CmdAlignmentShiftRotationDrawEnd *>(packet);
	if(CmdAlignmentShiftRotationDrawEndVar!=NULL){
		int	Row=ui->tableWidgetGeneratedLibList->currentRow();
		if(Row>=0){
			AlgorithmLibraryList	*a=SelectedLibList.GetItem(Row);
			if(a!=NULL){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create AlignmentProjection point");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(CmdAlignmentShiftRotationDrawEndVar->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=CmdAlignmentShiftRotationDrawEndVar->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdAddAlignmentShiftRotation	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area=A;
						Cmd.LibID	=a->GetLibID();
						Cmd.Send(NULL,GlobalPage,0);
					}
				}
			}
			ShowItemList();
		}
		return;
	}
}
void	PropertyAlignmentShiftRotationForm::BuildForShow(void)
{
	ShowItemList();
}
void	PropertyAlignmentShiftRotationForm::StartPage	(void)
{
}
void	PropertyAlignmentShiftRotationForm::ShowInEdit	(void)
{
}

void	PropertyAlignmentShiftRotationForm::ShowItemList(void)
{
	ItemList.RemoveAll();
	for(int Page=0;Page<GetPageNumb();Page++){
		for(int Phase=0;Phase<GetPhaseNumb();Phase++){
			int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(Page);
			GUICmdReqAlignmentShiftRotationItemList		RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			GUICmdSendAlignmentShiftRotationItemList	SCmd(GetLayersBase(),sRoot,sName,GlobalPage);
			RCmd.Phase=Phase;
			if(RCmd.Send(GlobalPage,0,SCmd)==true){
				ItemList.AddMove(SCmd.ItemList);
			}
		}
	}

	int	row=0;
	ui->tableWidgetItemList->setRowCount(ItemList.GetNumber());
	for(AlignmentShiftRotationItemList *a=ItemList.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetItemList, 0, row, QString::number(a->Data.Page));
		::SetDataToTable(ui->tableWidgetItemList, 1, row, QString::number(a->Data.ItemID));
		::SetDataToTable(ui->tableWidgetItemList, 2, row, QString::number(a->Data.LibID));

		QString  LibName = GetAlignmentShiftRotationBase()->GetLibraryName(a->Data.LibID);
		::SetDataToTable(ui->tableWidgetItemList, 3, row, LibName);

		QString  CenterStr = QString::number(a->Data.CenterX) 
							+ QString(",")
							+ QString::number(a->Data.CenterY);
		::SetDataToTable(ui->tableWidgetItemList, 4, row, CenterStr);
	}
}