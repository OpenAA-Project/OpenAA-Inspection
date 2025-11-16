#include "PropertyMatchShiftRotationForm.h"
#include "ui_PropertyMatchShiftRotationForm.h"
#include "XPropertyMatchShiftRotationPacket.h"
#include "EditPartDialog.h"
#include "SelectItemDialog.h"
#include "XDatabaseLoader.h"
#include "EditLibraryDialog.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"
#include "XRememberer.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

PropertyMatchShiftRotationForm::PropertyMatchShiftRotationForm(LayersBase *Base,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::PropertyMatchShiftRotationForm)
{
    ui->setupUi(this);
   // LangSolver.SetUI(this);

	LibFolderID			=-1;

	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	LibType=-1;
	if(BBase!=NULL)	
		LibType=BBase->GetLibType();

	ui->tableWidgetPartList			->setColumnWidth (0, 60);
	ui->tableWidgetPartList			->setColumnWidth (1, 60);
	ui->tableWidgetPartList			->setColumnWidth (3, 240);

	ui->tableWidgetMarkList	->setColumnWidth (0, 60);
	ui->tableWidgetMarkList	->setColumnWidth (1, 240);

	TempLib=NULL;
	if(BBase!=NULL){
		CmdCreateTempMatchShiftRotationLibraryPacket	Packet(GetLayersBase());
		BBase->TransmitDirectly(&Packet);
		TempLib=Packet.Point;
	}
	if(TempLib!=NULL){
		TempLib->SetLibID(-1);
	}
	ShowAreaGrid();
	int	LibFolderID=ControlRememberer::GetInt(objectName()+/**/"\\LibFolderID",-1);
	if(LibFolderID>=0){
		QString	FolderName=GetLayersBase()->GetLibFolderName(LibFolderID);
		SetLibFolder(LibFolderID,FolderName);
	}
	InstallIgnoreKeyForChild();
}

PropertyMatchShiftRotationForm::~PropertyMatchShiftRotationForm()
{
    delete ui;

	if(TempLib!=NULL)
		delete	TempLib;
	TempLib=NULL;
}

MatchShiftRotationBase	*PropertyMatchShiftRotationForm::GetMatchShiftRotationBase(void)
{
	return (MatchShiftRotationBase *)GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"MatchShiftRotation");
}


GUIFormBase	*PropertyMatchShiftRotationForm::GetImagePanel(void)
{
	GUIFormBase	*GForm=GetLayersBase()->FindByName(/**/"Inspection",/**/"MatchShiftRotationImagePanel",/**/"");
	return GForm;
}
void	PropertyMatchShiftRotationForm::RepaintImage(void)
{
	GUIFormBase	*GForm=GetImagePanel();
	if(GForm!=NULL){
		GForm->repaint();
	}
}
void	PropertyMatchShiftRotationForm::Prepare(void)
{
	//_heapchk();
}
void	PropertyMatchShiftRotationForm::ShowAreaGrid(void)
{
	static	volatile	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	if(GetLayersBase()->IsValidData()==false)
		return;

	ReEntrant=true;

	int	CurrentRow=ui->tableWidgetPartList->currentRow();
	int	CurrentAreaID=-1;
	if(CurrentRow>=0){
		MatchShiftRotationAreaList *a=AreaList[CurrentRow];
		if(a!=NULL){
			CurrentAreaID=a->AreaID;
		}
	}

	QString	EmitterRoot=sRoot;
	QString	EmitterName=sName;
	GUICmdSendMatchShiftRotationAreaList	**BmpReceiver=new GUICmdSendMatchShiftRotationAreaList*[GetLayersBase()->GetPageNumb()];
	GUICmdReqMatchShiftRotationAreaList	**BmpRequester=new GUICmdReqMatchShiftRotationAreaList*[GetLayersBase()->GetPageNumb()];
	int	N=0;
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		BmpReceiver[N]=new GUICmdSendMatchShiftRotationAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		BmpRequester[N]=new GUICmdReqMatchShiftRotationAreaList(GetLayersBase(),EmitterRoot,EmitterName,globalPage);
		N++;
	}
	AreaList.RemoveAll();
	for(int n=0;n<N;n++){
		if(BmpRequester[n]->Send(BmpRequester[n]->GetGlobalPage(),0,*BmpReceiver[n])==true){
			AreaList+=BmpReceiver[n]->Area;
		}
	}

	for(int i=0;i<N;i++){
		delete	BmpRequester[i];
		delete	BmpReceiver[i];
	}
	delete	[]BmpRequester;
	delete	[]BmpReceiver;

	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	ui->tableWidgetPartList->setRowCount(AreaList.GetNumber());
	N=0;
	for(MatchShiftRotationAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),N++){
		::SetDataToTable(ui->tableWidgetPartList ,0 ,N ,QString::number(a->GlobalPage)	,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		::SetDataToTable(ui->tableWidgetPartList ,1 ,N ,QString::number(a->AreaID)		,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
		QString	s=a->AreaName;
		if(s.isEmpty()==true)
			s=QString::number(a->XSize)+ QString(/**/",")+ QString::number(a->YSize);
		::SetDataToTable(ui->tableWidgetPartList ,2 ,N ,s		,Qt::ItemIsSelectable | Qt::ItemIsEnabled);
	}
	if(CurrentAreaID<0 && AreaList.GetCount()>0){
		ui->tableWidgetPartList->setCurrentCell(0,0);
	}
	else{
		int	Row=0;
		for(MatchShiftRotationAreaList *a=AreaList.GetFirst();a!=NULL;a=a->GetNext(),Row++){
			if(a->AreaID==CurrentAreaID){
				ui->tableWidgetPartList->setCurrentCell(Row,0);
				break;
			}
		}
	}


	ReEntrant=false;
}
void	PropertyMatchShiftRotationForm::ShowInEdit(void)
{
	ShowMatchShiftRotationInfoList();
}
void	PropertyMatchShiftRotationForm::StartPage(void)
{
}
void	PropertyMatchShiftRotationForm::BuildForShow(void)
{
	StartPage();
	ShowAreaGrid();
}
void	PropertyMatchShiftRotationForm::SetupLibFolder(int _LibFolderID,int originalLibFolder)
{
	LibFolderID=_LibFolderID;
}
void	PropertyMatchShiftRotationForm::TransmitDirectly(GUIDirectMessage *packet)
{
	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	CmdMatchShiftRotationDrawModePacket	*BDrawModePacket=dynamic_cast<CmdMatchShiftRotationDrawModePacket *>(packet);
	if(BDrawModePacket!=NULL){
		if(ui->toolButtonPart->isChecked()==true)
			BDrawModePacket->DrawArea=true;
		else
			BDrawModePacket->DrawArea=false;

		if(ui->toolButtonMark->isChecked()==true)
			BDrawModePacket->DrawMark=true;
		else 
			BDrawModePacket->DrawMark=false;

		IntList	Rows;
		::GetSelectedRows(ui->tableWidgetPartList,Rows);
		BDrawModePacket->SelectedArea.RemoveAll();
		for(IntClass *v=Rows.GetFirst();v!=NULL;v=v->GetNext()){
			MatchShiftRotationAreaList	*A=AreaList.GetItem(v->GetValue());
			if(A!=NULL){
				BDrawModePacket->SelectedArea.Add(A->AreaID);
			}
		}
		return;
	}
	CmdMatchShiftRotationDrawEnd	*MatchShiftRotationDEnd=dynamic_cast<CmdMatchShiftRotationDrawEnd *>(packet);
	if(MatchShiftRotationDEnd!=NULL){
		IntList	PageList;
		int	PageN=GetLayersBase()->GetLocalPageFromArea(MatchShiftRotationDEnd->Area ,PageList);
		if(PageN<=0)
			return;
		if(ui->toolButtonPart->isChecked()==true && ui->toolButtonMark->isChecked()==false){
			EditPartDialog	D(GetLayersBase(),this);
			if(D.exec()==true){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create MatchShiftRotation area");

				for(IntClass *PList=PageList.GetFirst();PList!=NULL;PList=PList->GetNext()){
					int	LocalPage=PList->GetValue();
					int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(LocalPage);

					FlexArea	A=MatchShiftRotationDEnd->Area;
					GetLayersBase()->GetPageData(LocalPage)->ClipMoveAreaFromGlobal(A);				

					GUICmdReqMatchShiftRotationPutArea	DNewMsg(GetLayersBase(),sRoot,sName,globalPage);
					DNewMsg.Area			=A;
					DNewMsg.AreaName		=D.AreaName;
					DNewMsg.GlobalPage		=globalPage;
					DNewMsg.LibID			=D.MatchShiftRotationLibID;
					DNewMsg.Send(NULL,globalPage ,0);
				}
				ShowAreaGrid();
				for(int r=0;r<ui->tableWidgetPartList->rowCount();r++){
					for(int c=0;c<ui->tableWidgetPartList->columnCount();c++){
						QTableWidgetItem	*p=ui->tableWidgetPartList->item(r,c);
						p->setSelected(false);
					}
				}
			}
		}
		else if(ui->toolButtonMark->isChecked()==true && ui->tableWidgetPartList->currentRow()>=0){
			int	Row=ui->tableWidgetPartList->currentRow();
			MatchShiftRotationAreaList	*A=AreaList.GetItem(Row);
			int	AreaID=A->AreaID;

			SelectItemDialog	D(GetLayersBase(),NULL);
			if(D.exec()==(int)true && D.MatchShiftRotationLibID>=0){
				GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Create manual MatchShiftRotation");

				IntList PageList;
				GetLayersBase()->GetLocalPageFromArea(MatchShiftRotationDEnd->Area,PageList);
				for(IntClass *P=PageList.GetFirst();P!=NULL;P=P->GetNext()){
					int	page=P->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(page);
					FlexArea	A=MatchShiftRotationDEnd->Area;
					pdata->ClipMoveAreaFromGlobal(A);
					if(A.GetPatternByte()>0){
						int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
						GUICmdSendAddManualMatchShiftRotation	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
						Cmd.Area	=A;
						Cmd.AreaID	=AreaID;
						Cmd.LibID	=D.MatchShiftRotationLibID;
						Cmd.ItemName=D.ItemName;
						Cmd.SendOnly(GlobalPage,0);
					}
				}
				ShowMatchShiftRotationInfoList();
			}
		}
		return;
	}
	/*
	CmdIsModeItemEditingPacket	*CmdIsModeItemEditingPacketVar=dynamic_cast<CmdIsModeItemEditingPacket *>(packet);
	if(CmdIsModeItemEditingPacketVar!=NULL){
		if(ui->toolButtonAlignmrntFlexAreaArea->isChecked()==true && ui->toolButtonOutline->isChecked()==false)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_AreaMode;
		else if(ui->toolButtonOutline->isChecked()==true)
			CmdIsModeItemEditingPacketVar->ItemMode=CmdIsModeItemEditingPacket::_ItemMode;
		return;
	}
	GUICmdMatchShiftRotationReflectChangeItems	*ReDrawMode=dynamic_cast<GUICmdMatchShiftRotationReflectChangeItems *>(packet);
	if(ReDrawMode!=NULL){
		ShowAreaGrid();
		//CreateAndShowPointGrid();
		return;
	}
	GUICmdReqMatchShiftRotationSetMode	*GUICmdReqMatchShiftRotationSetModeVar=dynamic_cast<GUICmdReqMatchShiftRotationSetMode *>(packet);
	if(GUICmdReqMatchShiftRotationSetModeVar!=NULL){
		ui->toolButtonAlignmrntFlexAreaArea	->setChecked(GUICmdReqMatchShiftRotationSetModeVar->ModeFlexAreaArea);
		ui->toolButtonOutline				->setChecked(GUICmdReqMatchShiftRotationSetModeVar->ModeOutline);
		return;
	}
	GUICmdReqMatchShiftRotationSetCurrentArea	*GUICmdReqMatchShiftRotationSetCurrentAreaVar=dynamic_cast<GUICmdReqMatchShiftRotationSetCurrentArea *>(packet);
	if(GUICmdReqMatchShiftRotationSetCurrentAreaVar!=NULL){
		for(int row=0;row<AreaList.GetCount();row++){
			if(AreaList[row]->AreaID==GUICmdReqMatchShiftRotationSetCurrentAreaVar->AreaID
			&& AreaList[row]->GlobalPage==GUICmdReqMatchShiftRotationSetCurrentAreaVar->GlobalPage){
				ui->tableWidgetArea->setCurrentCell(row,0);
				ui->tableWidgetArea->setCurrentCell(row,1);
			}
		}
		return;
	}
	CmdGetCurrentAreaIDPacket	*CmdGetCurrentAreaIDPacketVar=dynamic_cast<CmdGetCurrentAreaIDPacket *>(packet);
	if(CmdGetCurrentAreaIDPacketVar!=NULL){
		int	Row=ui->tableWidgetArea->currentRow();
		if(Row>=0){
			MatchShiftRotationAreaList	*a=AreaList[Row];
			if(a!=NULL){
				CmdGetCurrentAreaIDPacketVar->AreaID	=a->AreaID;
			}
		}
		return;
	}
	*/
}

bool	PropertyMatchShiftRotationForm::SaveContent(QIODevice *f)
{
	WORD	Ver=1;
	if(::Save(f,Ver)==false)
		return false;

	return true;
}
bool	PropertyMatchShiftRotationForm::LoadContent(QIODevice *f)
{
	WORD	Ver;
	if(::Load(f,Ver)==false)
		return false;

	return true;
}
void	PropertyMatchShiftRotationForm::SelectModeType(int ModeType)
{
	if(ModeType==0)
		ui->toolButtonPart->setChecked(true);
	else if(ModeType==1)
		ui->toolButtonMark->setChecked(true);
}
void	PropertyMatchShiftRotationForm::GenerateAreaFromMask(int ItemLibID)
{
	GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Generate Area with Item automatically");
	
	GetLayersBase()->ClearAllAckFlag();
	GetLayersBase()->ShowProcessingForm("Generating items from mask"
										,false,SelectedLibList.GetCount()*(7+7));
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdGenerateMatchShiftRotationFromMask	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.ItemLibID	=ItemLibID;
		Cmd.Send(NULL,GlobalPage,0);
	}
	GetLayersBase()->WaitAllAcknowledged(60*20);
	GetLayersBase()->CloseProcessingForm();
}

void PropertyMatchShiftRotationForm::ShowMatchShiftRotationInfoList(void)
{
	int	Row=ui->tableWidgetPartList->currentRow();
	if(Row<0)
		return;
	MatchShiftRotationAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;

	ItemInfos.RemoveAll();

	int	GlobalPage=A->GlobalPage;
	GUICmdReqMatchShiftRotationItemPack		CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
	CmdReq.AreaID	=A->AreaID;
	GUICmdAckMatchShiftRotationItemPack		CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
	if(CmdReq.Send(GlobalPage,0,CmdSend)==true){
		ItemInfos=CmdSend.Items;
	}

	int	N=ItemInfos.GetNumber();
	ui->tableWidgetMarkList->setRowCount(N);

	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	int	row=0;
	for(MatchShiftRotationItemList *a=ItemInfos.GetFirst();a!=NULL;a=a->GetNext(),row++){
		::SetDataToTable(ui->tableWidgetMarkList ,0 ,row ,QString::number(a->Data.ItemID));
		::SetDataToTable(ui->tableWidgetMarkList ,1 ,row ,QString(/**/"(") +QString::number(a->Data.x1)+QString(/**/",")+QString::number(a->Data.y1)+QString(/**/")")
														 +QString(/**/"-(")+QString::number(a->Data.x2)+QString(/**/",")+QString::number(a->Data.y2)+QString(/**/")"));
	}
}

void	PropertyMatchShiftRotationForm::SetLibFolder(int _LibFolderID ,const QString &LinFolderName)
{
	ui->labelLibFolderName->setText(LinFolderName);
	LibFolderID=_LibFolderID;
	//ShowLibList();
}

void PropertyMatchShiftRotationForm::on_tableWidgetPartList_clicked(const QModelIndex &index)
{
	ShowMatchShiftRotationInfoList();
}

void PropertyMatchShiftRotationForm::on_tableWidgetPartList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetPartList->currentRow();
	if(Row<0)
		return;
	MatchShiftRotationAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;
	
	EditPartDialog	D(GetLayersBase(),this);
	D.MatchShiftRotationLibID=A->LibID;
	D.AreaName	=A->AreaName;
	D.Reflect();
	int	Ret=D.exec();
	if(Ret==(int)true){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Update MatchShiftRotation area");

		int	globalPage=A->GlobalPage;

		GUICmdReqModifyMatchShiftRotationAreaInfo	DUpdateMsg(GetLayersBase(),sRoot,sName,globalPage);
		DUpdateMsg.AreaID			=A->AreaID;
		DUpdateMsg.AreaName		=D.AreaName;
		DUpdateMsg.LibID			=D.MatchShiftRotationLibID;
		DUpdateMsg.Send(NULL,globalPage ,0);
		ShowAreaGrid();
		for(int r=0;r<ui->tableWidgetPartList->rowCount();r++){
			for(int c=0;c<ui->tableWidgetPartList->columnCount();c++){
				QTableWidgetItem	*p=ui->tableWidgetPartList->item(r,c);
				p->setSelected(false);
			}
		}
	}
	else if(Ret==10){
		int	GlobalPage=A->GlobalPage;
		GUICmdDeleteArea	Cmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		Cmd.AreaID	=A->AreaID;
		Cmd.SendOnly(GlobalPage,0);
		ShowAreaGrid();
	}
}
	

void PropertyMatchShiftRotationForm::on_tableWidgetMarkList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetPartList->currentRow();
	if(Row<0)
		return;
	MatchShiftRotationAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;
	int	RowI=ui->tableWidgetMarkList->currentRow();

	MatchShiftRotationItemList *a=ItemInfos[RowI];
	if(a==NULL)
		return;

	int	GlobalPage=A->GlobalPage;
	GUICmdReqMatchShiftItemImages	CmdReq (GetLayersBase(),sRoot,sName,GlobalPage);
	CmdReq.AreaID	=A->AreaID;
	CmdReq.ItemID	=a->Data.ItemID;
	GUICmdSendMatchShiftItemImages	CmdSend(GetLayersBase(),sRoot,sName,GlobalPage);
	if(CmdReq.Send(GlobalPage,0,CmdSend)==true){
		CurrentPatterns=CmdSend.Patterns;
		ShowPatternList();
	}
}

void	PropertyMatchShiftRotationForm::ShowPatternList(void)
{
	ui->listWidgetAngleList->clear();
	for(FlexAreaImageList *s=CurrentPatterns.GetFirst();s!=NULL;s=s->GetNext()){
		FlexAreaImageListCoeffAngle	*src=dynamic_cast<FlexAreaImageListCoeffAngle *>(s);
		if(src!=NULL){
			ui->listWidgetAngleList->addItem(QString::number(src->Angle,'f',5));
		}
	}
}

void PropertyMatchShiftRotationForm::on_tableWidgetMarkList_doubleClicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetPartList->currentRow();
	if(Row<0)
		return;
	MatchShiftRotationAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;
	int	RowI=ui->tableWidgetMarkList->currentRow();

	MatchShiftRotationItemList *a=ItemInfos[RowI];
	if(a==NULL)
		return;

	SelectItemDialog	D(GetLayersBase(),NULL);
	D.MatchShiftRotationLibID	=a->Data.LibID;
	D.ItemName					=a->ItemName;
	D.Reflect();
	int	Ret=D.exec();
	if(Ret==(int)true && D.MatchShiftRotationLibID>=0){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Update manual MatchShiftRotation");

		int	GlobalPage=A->GlobalPage;
		GUICmdUpdateManualMatchShiftRotation	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.ItemID	=a->Data.ItemID;
		Cmd.LibID	=D.MatchShiftRotationLibID;
		Cmd.ItemName=D.ItemName;
		Cmd.SendOnly(GlobalPage,0);
	
		ShowMatchShiftRotationInfoList();
	}
	else if(Ret==10){
		GetLayersBase()->GetUndoStocker().SetNewTopic(/**/"Update manual MatchShiftRotation");

		int	GlobalPage=A->GlobalPage;
		GUICmdDeleteManualMatchShiftRotation	Cmd(GetLayersBase(),sRoot,sName,GlobalPage);
		Cmd.ItemID	=a->Data.ItemID;
		Cmd.SendOnly(GlobalPage,0);
	
		ShowMatchShiftRotationInfoList();
	}
}

void PropertyMatchShiftRotationForm::on_toolButtonPart_clicked()
{

}

void PropertyMatchShiftRotationForm::on_toolButtonMark_clicked()
{

}

void PropertyMatchShiftRotationForm::on_pushButtonEditLibFolder_clicked()
{
	MatchShiftRotationBase	*BBase=GetMatchShiftRotationBase();
	int		RetSelectedLibFolderID;
	QString RetSelectedFolderName;
	if(ExeSelectLibFolderDialog(BBase->GetLibType(),GetLayersBase(),this
								,RetSelectedLibFolderID
								,RetSelectedFolderName)==true){
		ControlRememberer::SetValue(objectName()+/**/"\\LibFolderID",RetSelectedLibFolderID);
		SetLibFolder(RetSelectedLibFolderID,RetSelectedFolderName);
	}
}

void PropertyMatchShiftRotationForm::on_pushButtonEditLibrary_clicked()
{
	EditLibraryDialog	D(GetLayersBase(),this);
	D.exec();

}

void PropertyMatchShiftRotationForm::on_listWidgetAngleList_clicked(const QModelIndex &index)
{
	int	Row=ui->tableWidgetPartList->currentRow();
	if(Row<0)
		return;
	MatchShiftRotationAreaList	*A=AreaList[Row];;
	if(A==NULL)
		return;
	int	RowI=ui->tableWidgetMarkList->currentRow();

	MatchShiftRotationItemList *a=ItemInfos[RowI];
	if(a==NULL)
		return;
	int	AListRow=ui->listWidgetAngleList->currentRow();
	FlexAreaImageList *s=CurrentPatterns[AListRow];
	int	x1=s->GetMinX();
	int	y1=s->GetMinY();
	s->MoveToNoClip(-x1,-y1);
	FlexAreaImageListCoeffAngle	*src=dynamic_cast<FlexAreaImageListCoeffAngle *>(s);
	if(src!=NULL){
		QImage	Img(src->GetWidth(),src->GetHeight(),QImage::Format_ARGB32);
		QRgb	b=qRgb(0,0,0);
		Img.fill(b);
		src->DrawImage(0,0,&Img
						,1.0,0,0
						,true,true,true);
		//Img.save("Test1.png","PNG");
		QPixmap Pix=QPixmap::fromImage(Img.scaled(ui->labelRotationImage->size(),Qt::KeepAspectRatio));
		//Pix.save("Test2.png","PNG");
		ui->labelRotationImage->setPixmap (Pix);
	}
}
