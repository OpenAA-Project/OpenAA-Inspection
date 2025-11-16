/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PieceProperty\PiecePropertyForm.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PiecePropertyFormResource.h"
#include "PiecePropertyForm.h"
#include "XDLLOnly.h"
#include "XDataInLayer.h"
#include <QImage>
#include <QDir>
#include "XDatabaseLoader.h"
#include "XPiecePacket.h"
#include "XGUI.h"
#include "InputSearchAreaDialog.h"
#include "XDisplayImage.h"
#include <QMessageBox>

extern	const	char	*sRoot;
extern	const	char	*sName;

QSqlPieceMasterModel::QSqlPieceMasterModel(PiecePropertyForm *parentForm ,QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentForm=parentForm;
}
QString QSqlPieceMasterModel::selectStatement () const
{
	QString	ret;
	if(ParentForm->CategoryID==-1){
		ret=QString(/**/"SELECT MASTERCODE,MASTERNAME FROM MASTERDATA WHERE MASTERTYPE>0 ORDER BY MASTERCODE;");
	}
	else{
		ret=QString(/**/"SELECT MASTERCODE,MASTERNAME FROM MASTERDATA WHERE MASTERTYPE>0 and CATEGORYID=")
			+QString::number(ParentForm->CategoryID)
			+QString(/**/" ORDER BY MASTERCODE;");
	}
	return ret;
}

QSqlPieceMasterModelAuto::QSqlPieceMasterModelAuto(PiecePropertyForm *parentForm ,QObject * parent, QSqlDatabase db)
:QSqlTableModel(parent, db)
{
	ParentForm=parentForm;
}
QString QSqlPieceMasterModelAuto::selectStatement () const
{
	QString	ret;
	if(ParentForm->CategoryIDAuto==-1){
		ret=QString(/**/"SELECT MASTERCODE,MASTERNAME FROM MASTERDATA WHERE MASTERTYPE>0 ORDER BY MASTERCODE;");
	}
	else{
		ret=QString(/**/"SELECT MASTERCODE,MASTERNAME FROM MASTERDATA WHERE MASTERTYPE>0 and CATEGORYID=")
			+QString::number(ParentForm->CategoryIDAuto)
			+QString(/**/" ORDER BY MASTERCODE;");
	}
	return ret;
}

PiecePropertyForm::PiecePropertyForm(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	LangSolver.SetUI(this);

	PieceGridTable	=NULL;

	MasterCategory=new MasterCategoryForm(GetLayersBase(),ui.frameCategory);
	connect(MasterCategory,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategory(int,QString,QString)));

	if(GetLayersBase()->IsDatabaseOk()==true){
		QSqlPieceMasterModel *MModel = new QSqlPieceMasterModel(this,this,GetLayersBase()->GetDatabase());
		MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
		MModel->select();
//		MModel->removeColumn(0); // don't show the ID
		MModel->setHeaderData(0, Qt::Horizontal, LangSolver.GetString(PiecePropertyForm_LS,LID_3)/*"MasterID"*/);
		MModel->setHeaderData(2, Qt::Horizontal, LangSolver.GetString(PiecePropertyForm_LS,LID_4)/*"Name"*/);

		ui.tableViewMList->setModel(MModel);
		ui.tableViewMList->move(0,0);
		ui.tableViewMList->resize(ui.frameGrid->width(),ui.frameGrid->height());
		ui.tableViewMList->setColumnWidth (0, 40);
		ui.tableViewMList->setColumnWidth (1, 120);
		ui.tableViewMList->show();
	}
	ui.tablePieceArrange->setColumnWidth(0,40);
	ui.tablePieceArrange->setColumnWidth(1,50);
	ui.tablePieceArrange->setColumnWidth(2,50);
	ui.tablePieceArrange->setColumnWidth(3,140);
	ui.tablePieceArrange->setColumnWidth(4,45);
	ui.tablePieceArrange->setColumnWidth(5,45);

	AlgorithmArea.setParent(ui.frameAlgorithmBase);
	AlgorithmArea.move(0,0);
	AlgorithmArea.resize(ui.frameAlgorithmBase->width(),ui.frameAlgorithmBase->height());
	AlgorithmButtonNumb=GetLayersBase()->GetLogicDLLBase()->GetNumber()+1;
	AlgorithmButtons	=new AlgorithmToolButton*[AlgorithmButtonNumb];
	AlgorithmFrame.resize(AlgorithmButtonNumb*(100+4)+4,30);
	AlgorithmArea.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	AlgorithmArea.setWidget(&AlgorithmFrame);
	int	n=0;
	AlgorithmToolButton	*BNone=new AlgorithmToolButton(&AlgorithmFrame);
	BNone->setCheckable(true);
	BNone->setAutoExclusive(true);
	BNone->setText(LangSolver.GetString(PiecePropertyForm_LS,LID_5)/*"Area"*/);
	BNone->move(4+n*104,4);
	BNone->resize(96,21);
	BNone->DLLRoot	=/**/"";
	BNone->DLLName	=/**/"";
	AlgorithmButtons[n]=BNone;
	connect(BNone,SIGNAL(clicked(bool)),this,SLOT(SlotAlgorithmToolBottonClicked(bool)));
	n++;

	for(LogicDLL *L=GetLayersBase()->GetLogicDLLBase()->GetFirst();L!=NULL;L=L->GetNext(),n++){
		AlgorithmToolButton	*B=new AlgorithmToolButton(&AlgorithmFrame);
		B->setCheckable(true);
		B->setAutoExclusive(true);
		B->setText(L->GetDLLName());
		B->move(4+n*104,4);
		B->resize(96,21);
		B->DLLRoot	=L->GetDLLRoot();
		B->DLLName	=L->GetDLLName();
		AlgorithmButtons[n]=B;
		connect(B,SIGNAL(clicked(bool)),this,SLOT(SlotAlgorithmToolBottonClicked(bool)));
	}
	if(n!=0)
		AlgorithmButtons[0]->setChecked(true);

	MasterCategoryAuto=new MasterCategoryForm(GetLayersBase(),ui.frameCategoryAuto);
	connect(MasterCategoryAuto,SIGNAL(SelectCategory(int,QString,QString)),this,SLOT(SlotSelectCategoryAuto(int,QString,QString)));

	if(GetLayersBase()->IsDatabaseOk()==true){
		QSqlPieceMasterModelAuto *MModel = new QSqlPieceMasterModelAuto(this,this,GetLayersBase()->GetDatabase());
		MModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
		MModel->select();
//		MModel->removeColumn(0); // don't show the ID
		MModel->setHeaderData(0, Qt::Horizontal, LangSolver.GetString(PiecePropertyForm_LS,LID_3)/*"MasterID"*/);
		MModel->setHeaderData(2, Qt::Horizontal, LangSolver.GetString(PiecePropertyForm_LS,LID_4)/*"Name"*/);

		MListViewAuto = new QTableView(ui.frameGridAuto);
		MListViewAuto->setModel(MModel);
		MListViewAuto->move(0,0);
		MListViewAuto->resize(ui.frameGridAuto->width(),ui.frameGridAuto->height());
		connect(MListViewAuto,SIGNAL(clicked(const QModelIndex &)),this,SLOT(SlotMListViewAutoClicked ( const QModelIndex &)));
		MListViewAuto->setColumnWidth (0, 40);
		MListViewAuto->setColumnWidth (1, 120);
		MListViewAuto->setSelectionMode(QAbstractItemView::SingleSelection);
		MListViewAuto->setSelectionBehavior(QAbstractItemView::SelectRows);
		MListViewAuto->show();
	}
	ui.tableWidgetAutoCurrent->setColumnWidth(0,40);
	ui.tableWidgetAutoCurrent->setColumnWidth(1,120);

	ui.tableWidgetAutoResult->setColumnWidth(0,40);
	ui.tableWidgetAutoResult->setColumnWidth(1,50);
	ui.tableWidgetAutoResult->setColumnWidth(2,50);
	ui.tableWidgetAutoResult->setColumnWidth(3,50);

	ui.tabWidget->setCurrentIndex(0);
}

PiecePropertyForm::~PiecePropertyForm()
{
	delete	[]AlgorithmButtons;

	if(PieceGridTable!=NULL){
		delete	[]PieceGridTable;
		PieceGridTable=NULL;
	}
}

void	PiecePropertyForm::SlotSelectCategory(int _CategoryID ,QString FolderName ,QString Remark)
{
	CategoryID=_CategoryID;

	QSqlPieceMasterModel	*M=dynamic_cast<QSqlPieceMasterModel *>(ui.tableViewMList->model());
	if(M!=NULL)
		M->select();
	
	//MListView->repaint();
}

void	PiecePropertyForm::SlotSelectCategoryAuto(int _CategoryID ,QString FolderName ,QString Remark)
{
	CategoryIDAuto=_CategoryID;

	QSqlPieceMasterModelAuto	*M=dynamic_cast<QSqlPieceMasterModelAuto *>(MListViewAuto->model());
	if(M!=NULL)
		M->select();
	
	//MListView->repaint();
}

void	PiecePropertyForm::SlotMListViewAutoClicked ( const QModelIndex & index ) 
{
	int	r=index.row();
	QSqlPieceMasterModelAuto	*M=dynamic_cast<QSqlPieceMasterModelAuto *>(MListViewAuto->model());
	if(M!=NULL){
		QModelIndex Q=M->index(r,0);
		int	MasterCode=M->data(Q).toInt();
		QImage	*Img=GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterTopview(GetLayersBase()->GetDatabase(),MasterCode);
		if(Img==NULL)
			return;
		QImage	TmpImage=Img->scaled(ui.labelTopviewAuto->width(),ui.labelTopviewAuto->height());
		ui.labelTopviewAuto->setPixmap(QPixmap::fromImage(TmpImage));
		delete	Img;
	}
}

void	PiecePropertyForm::ShowInEdit(void)
{
	BuildForShow();
}

void	PiecePropertyForm::BuildForShow(void)
{
	if(PieceGridTable!=NULL)
		delete	[]PieceGridTable;
	PieceGridTable=new PieceGridContainer[GetPageNumb()];

	int	RowCount=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqPieceGrid	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
		GUICmdSendPieceGrid	ACmd(GetLayersBase(),sRoot,sName,GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			PieceGridTable[page]=ACmd.PieceGridInfo;
			RowCount	+=ACmd.PieceGridInfo.GetCount();
		}
	}
	AlgorithmBase	*L=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PieceArrange");
	if(L==NULL)
		return;
	ui.tablePieceArrange->setRowCount(RowCount);
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(PieceGridList *Piece=PieceGridTable[page].GetFirst();Piece!=NULL;Piece=Piece->GetNext()){
			::SetDataToTable(ui.tablePieceArrange ,0 ,Row ,QString::number(page));
			::SetDataToTable(ui.tablePieceArrange ,1 ,Row ,QString::number(Piece->PieceID));
			::SetDataToTable(ui.tablePieceArrange ,2 ,Row ,QString::number(Piece->MasterCode));

			GetReqMasterNamePacket	ReqMasterNameCmd(GetLayersBase());
			ReqMasterNameCmd.MasterCode	=Piece->MasterCode;
			L->TransmitDirectly(&ReqMasterNameCmd);
			::SetDataToTable(ui.tablePieceArrange ,3 ,Row ,ReqMasterNameCmd.MasterName);

			Row++;
		}
	}
}

void	PiecePropertyForm::SlotAlgorithmToolBottonClicked(bool checked)
{
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
}


void PiecePropertyForm::on_toolButtonCutPiece_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PiecePanel" ,/**/"");
	if(GProp!=NULL){
		CmdPieceSetCutPacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}

void PiecePropertyForm::on_toolButtonArrange_clicked()
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PiecePanel" ,/**/"");
	if(GProp!=NULL){
		CmdPieceSetArrangePacket	Da(GetLayersBase());
		GProp->TransmitDirectly(&Da);
	}
}

int	PiecePropertyForm::GetSelectedMasterCode(void)
{
	if(ui.tableViewMList->currentIndex().isValid()==true){
		int	r=ui.tableViewMList->currentIndex().row();
		QSqlPieceMasterModel	*M=dynamic_cast<QSqlPieceMasterModel *>(ui.tableViewMList->model());
		if(M!=NULL){
			QModelIndex Q=M->index(r,0);
			return M->data(Q).toInt();
		}
	}
	return -1;
}

int	PiecePropertyForm::GetSelectedMasterCodeAuto(void)
{
	if(MListViewAuto->currentIndex().isValid()==true){
		int	r=MListViewAuto->currentIndex().row();
		QSqlPieceMasterModelAuto	*M=dynamic_cast<QSqlPieceMasterModelAuto *>(MListViewAuto->model());
		if(M!=NULL){
			QModelIndex Q=M->index(r,0);
			return M->data(Q).toInt();
		}
	}
	return -1;
}
void	PiecePropertyForm::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdCheckPiecePropertyButtonPacket	*CmdCheckPiecePropertyButtonPacketVar=dynamic_cast<CmdCheckPiecePropertyButtonPacket *>(packet);
	if(CmdCheckPiecePropertyButtonPacketVar!=NULL){
		if(ui.toolButtonCutPiece->isChecked()==true)
			CmdCheckPiecePropertyButtonPacketVar->Mode=CmdCheckPiecePropertyButtonPacket::ModeCutArea;
		else if(ui.toolButtonArrange->isChecked()==true)
			CmdCheckPiecePropertyButtonPacketVar->Mode=CmdCheckPiecePropertyButtonPacket::ModeArrange;
		else
			CmdCheckPiecePropertyButtonPacketVar->Mode=CmdCheckPiecePropertyButtonPacket::ModeNone;
		return;
	}
	CmdPieceSelectedAlgorithm	*CmdPieceSelectedAlgorithmVar=dynamic_cast<CmdPieceSelectedAlgorithm *>(packet);
	if(CmdPieceSelectedAlgorithmVar!=NULL){
		for(int i=0;i<AlgorithmButtonNumb;i++){
			if(AlgorithmButtons[i]->isChecked()==true){
				CmdPieceSelectedAlgorithmVar->DLLRoot=AlgorithmButtons[i]->DLLRoot;
				CmdPieceSelectedAlgorithmVar->DLLName=AlgorithmButtons[i]->DLLName;
				break;
			}
		}
		IntList		Rows;
		::GetSelectedRows(ui.tablePieceArrange ,Rows);
		for(IntClass *a=Rows.GetFirst();a!=NULL;a=a->GetNext()){
			int L=a->GetValue();
			PieceGridList	*c=GetPieceGridListFromRow(L);
			ListPageID	*d=new ListPageID();
			d->Page	=c->Page;
			d->ID	=c->PieceID;
			CmdPieceSelectedAlgorithmVar->SelectedLines.AppendList(d);
		}
		return;
	}
	CmdPieceSelectedMaster	*CmdPieceSelectedMasterVar=dynamic_cast<CmdPieceSelectedMaster *>(packet);
	if(CmdPieceSelectedMasterVar!=NULL){
		CmdPieceSelectedMasterVar->MasterCode=GetSelectedMasterCode();
		return;
	}
	CmdCreatePiecePacket	*CmdCreatePiecePacketVar=dynamic_cast<CmdCreatePiecePacket *>(packet);
	if(CmdCreatePiecePacketVar!=NULL){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
		if(Ab==NULL)
			return;
		PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(Ab);
		if(MBase==NULL)
			return;		
		int	SelectedMasterCode=GetSelectedMasterCode();
		if(SelectedMasterCode>=0){
			if(ui.toolButtonStartMatrixArrange->isChecked()==false){
				CmdReflectionAttrPack	CmdR(GetLayersBase());
				Ab->TransmitDirectly(&CmdR);
				for(int page=0;page<GetPageNumb();page++){
					DataInPage	*P=GetLayersBase()->GetPageData(page);
					if(P->IsOverlapped(CmdCreatePiecePacketVar->Area)==true){
						FlexArea	area=CmdCreatePiecePacketVar->Area;
						area.MoveToNoClip(-P->GetOutlineOffset()->x ,-P->GetOutlineOffset()->y);
						FlexArea	CheckArea=area;
						P->ClipAreaLocal(CheckArea);
						if(CheckArea.IsNull()==false){
							GUICmdAddPiece	SCmd(GetLayersBase(),sRoot,sName);
							SCmd.MasterCode=SelectedMasterCode;
							SCmd.Area=area;
							SCmd.ReflectionData=CmdR.ReflectionData;
							SCmd.Send(NULL,page,0);					
						}
					}
				}
			}
			else{
				int		X1,Y1,X2,Y2;
				CmdCreatePiecePacketVar->Area.GetXY(X1,Y1,X2,Y2);
				int	DCountX=ui.spinBoxAutoCountX->value();
				int	DCountY=ui.spinBoxAutoCountY->value();
				if(DCountX==0 || DCountY==0)
					return;
				int	CellX=(X2-X1)/DCountX;
				int	CellY=(Y2-Y1)/DCountY;
				CmdReflectionAttrPack	CmdR(GetLayersBase());
				Ab->TransmitDirectly(&CmdR);
				for(int y=0;y<DCountY;y++){
					for(int x=0;x<DCountX;x++){
						FlexArea	BaseArea;
						BaseArea.SetRectangle(X1+CellX*x	  ,Y1+CellY*y		
											, X1+CellX*(x+1)-1,Y1+CellY*(y+1)-1);
						for(int page=0;page<GetPageNumb();page++){
							DataInPage	*P=GetLayersBase()->GetPageData(page);
							if(P->IsOverlapped(BaseArea)==true){
								FlexArea	area=BaseArea;
								area.MoveToNoClip(-P->GetOutlineOffset()->x ,-P->GetOutlineOffset()->y);
								FlexArea	CheckArea=area;
								P->ClipAreaLocal(CheckArea);
								if(CheckArea.IsNull()==false){
									GUICmdAddPiece	SCmd(GetLayersBase(),sRoot,sName);
									SCmd.MasterCode=SelectedMasterCode;
									SCmd.Area=area;
									SCmd.ReflectionData=CmdR.ReflectionData;
									SCmd.Send(NULL,page,0);
								}
							}
						}
					}
				}
				ui.toolButtonStartMatrixArrange->setChecked(false);
			}
		}
	}
	GetCountPacket	*GetCountPacketVar=dynamic_cast<GetCountPacket *>(packet);
	if(GetCountPacketVar!=NULL){
		GetCountPacketVar->EnabledCountMode	=ui.toolButtonStartMatrixArrange->isChecked();
		GetCountPacketVar->CountX			=ui.spinBoxAutoCountX->value();
		GetCountPacketVar->CountY			=ui.spinBoxAutoCountY->value();
		return;
	}
	CancelCountPacket	*CancelCountPacketVar=dynamic_cast<CancelCountPacket *>(packet);
	if(CancelCountPacketVar!=NULL){
		ui.toolButtonStartMatrixArrange->setChecked(false);
		return;
	}
}

void PiecePropertyForm::on_tablePieceArrange_doubleClicked(QModelIndex)
{
	int	row=ui.tablePieceArrange->currentRow();
	LayersBase	*LBase=GetLayersBase();
	AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
	if(Ab==NULL)
		return;
	PieceGridList	*Piece=GetPieceGridListFromRow(row);
	if(Piece==NULL)
		return;
	PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(Ab);
	if(MBase==NULL)
		return;
	/*
	CmdReflectionAttrPack	CmdR(GetLayersBase());
	CmdR.ReflectionData	=Piece->ReflectionData;
	Ab->TransmitDirectly(&CmdR);
	Piece->ReflectionData=CmdR.ReflectionData;
	*/

	QString	GUIFileName=MBase->PieceGUIFile;
	if(GUIFileName.isEmpty()==true){
		GUIFileName=LBase->GetGUIFileName();
	}
	QString	ProgFile=MBase->EditorPathFile;
	if(ProgFile.isEmpty()==true){
		ProgFile=QCoreApplication::applicationFilePath ();
	}
	QDir::setCurrent(GetLayersBase()->GetUserPath());

	QString ParamFileName;
	QString PixFileName;
	CmdPieceCreateTempFiles		PMa(GetLayersBase());
	MBase->TransmitDirectly(&PMa);
	ParamFileName	=PMa.ParamFileName;

	QFile	createdGlobalParam(ParamFileName);
	if(createdGlobalParam.open(QIODevice::ReadWrite)==false){
		QString	Msg=ParamFileName
					+QString(" : Can not create temporary file");
		QMessageBox::critical (NULL, "Error", Msg );
		return;
	}
	bool	ret=GetLayersBase()->CreatePartialData(0,0,1000,1000
												,&createdGlobalParam ,NULL);
	if(ret==false)
		return;
	createdGlobalParam.close();

	QStringList Arguments;
	Arguments.append(QString(/**/"A")+LBase->GetSystemPath());
	Arguments.append(QString(/**/"G")+GUIFileName);
	Arguments.append(QString(/**/"S")+ParamFileName);
	Arguments.append(QString(/**/"W")+QString::number(LBase->GetWorkerID()));
	Arguments.append(QString(/**/"M")+QString::number(Piece->MasterCode));
	Arguments.append(QString(/**/"B")+QString::number(LBase->GetBootingLevel()+1));
	Arguments.append(QString(/**/"Duplicate"));
	Arguments.append(QString(/**/"NoCamDevice"));
	Arguments.append(QString(/**/"NoSequence"));
	Arguments.append(QString(/**/"NDM"));
	Arguments.append(QString(/**/"-R"));
	Arguments.append(QString(/**/"SetNumThreads1"));
	QProcess::startDetached( ProgFile, Arguments) ;
}

void PiecePropertyForm::on_pushButtonUpdate_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdUpdateParts	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.Send(NULL,page,0);
	}
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
}

void PiecePropertyForm::on_pushButtonExecuteAlignment_clicked()
{
	InputSearchAreaDialog	D(GetLayersBase());
	if(D.exec()==true){
		GetLayersBase()->ClearAllAckFlag();
		GetLayersBase()->ShowProcessingForm (LangSolver.GetString(PiecePropertyForm_LS,LID_0)/*"Execute alignment in Piece"*/);
		for(int page=0;page<GetPageNumb();page++){
			GUICmdExecuteAlignmentPiece	Da(GetLayersBase(),sRoot,sName,page);
			Da.SearchDot	=D.SearchDot;
			Da.Send(NULL,page,0);
		}
		GetLayersBase()->WaitAllAcknowledged(60*10);
		GetLayersBase()->CloseProcessingForm ();
	}
}


void PiecePropertyForm::on_pushButtonAutoPopLoad_clicked()
{
	int	Index=GetSelectedMasterCodeAuto();
	if(Index>=0){
		IntClass	*c;
		for(c=AutoSelectedMasterList.GetFirst();c!=NULL;c=c->GetNext()){
			if(c->GetValue()==Index){
				break;
			}
		}
		if(c==NULL){
			AutoSelectedMasterList.Add(Index);
			ShowAutoCurrentGrid();
		}
	}
}

void PiecePropertyForm::on_pushButtonPushBask_clicked()
{
	int	Row=ui.tableWidgetAutoCurrent->currentRow();
	if(Row<0){
		return;
	}
	IntClass	*c=AutoSelectedMasterList.GetItem(Row);
	if(c!=NULL){
		AutoSelectedMasterList.RemoveList(c);
		delete	c;
		ShowAutoCurrentGrid();
	}
}

void PiecePropertyForm::ShowAutoCurrentGrid(void)
{
	int	RowCount=AutoSelectedMasterList.GetCount();
	ui.tableWidgetAutoCurrent->setRowCount(RowCount);
	for(int row=0;row<RowCount;row++){
		SetDataToTable(ui.tableWidgetAutoCurrent ,0,row ,AutoSelectedMasterList[row]);
		int32		MachineID;
		XDateTime	RegTime;
		QString		MasterName;
		QString		Remark;
		int32		Version;
		XDateTime	LastEditTime;
		int32		CategoryID;
		int16		MasterType;
		int32		iLibFolderID;
		int32 		iThresholdLevelID;
		int32 		iThresholdLevelParentID;
	
		GetLayersBase()->GetDatabaseLoader()->G_SQLGetMasterInfo(
										GetLayersBase()->GetDatabase()
										,AutoSelectedMasterList[row]
										,MachineID
										,RegTime
										,MasterName ,Remark
										,Version
										,LastEditTime
										,CategoryID
										,MasterType
										,iLibFolderID
										,iThresholdLevelID
										,iThresholdLevelParentID);
		SetDataToTable(ui.tableWidgetAutoCurrent ,1,row ,MasterName);
	}
}

void PiecePropertyForm::on_tableWidgetAutoCurrent_doubleClicked(QModelIndex)
{
	on_pushButtonPushBask_clicked();
}

void PiecePropertyForm::on_pushButtonAutoExecute_clicked()
{
	for(int page=0;page<GetPageNumb();page++){
		GUICmdExecuteAutoAlignment	RCmd(GetLayersBase(),sRoot,sName,page);
		RCmd.AutoSelectedMasterList=AutoSelectedMasterList;
		RCmd.Send(NULL,page,0);
	}
	//BroadcastDirectly(GUIFormBase::_BC_Show ,GetLayersBase()->GetCurrentInspectIDForDisplay());
	BroadcastShowInEdit();
}


void PiecePropertyForm::on_pushButtonStartAutoSearch_clicked()
{

}

void PiecePropertyForm::on_tableWidgetAutoSearch_clicked(const QModelIndex &index)
{

}

void PiecePropertyForm::on_pushButtonCopyByAutoSearch_clicked()
{

}

void PiecePropertyForm::on_tableViewMList_clicked(const QModelIndex &index)
{
	int	r=index.row();
	QSqlPieceMasterModel	*M=dynamic_cast<QSqlPieceMasterModel *>(ui.tableViewMList->model());
	if(M!=NULL){
		QModelIndex Q=M->index(r,0);
		int	MasterCode=M->data(Q).toInt();
		QImage	*Img=GetLayersBase()->GetDatabaseLoader()->G_SQLLoadMasterTopview(GetLayersBase()->GetDatabase(),MasterCode);
		if(Img==NULL)
			return;
		QImage	TmpImage=Img->scaled(ui.labelTopview->width(),ui.labelTopview->height());
		ui.labelTopview->setPixmap(QPixmap::fromImage(TmpImage));
		delete	Img;
	}
}

void PiecePropertyForm::on_tableViewMList_doubleClicked(const QModelIndex &index)
{
	int	r=index.row();
	QSqlPieceMasterModel	*M=dynamic_cast<QSqlPieceMasterModel *>(ui.tableViewMList->model());
	if(M!=NULL){
		QModelIndex Q=M->index(r,0);
		int	MasterCode=M->data(Q).toInt();

		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"PieceArrange");
		if(Ab==NULL)
			return;
		PieceArrangeBase	*MBase=dynamic_cast<PieceArrangeBase *>(Ab);
		if(MBase==NULL)
			return;
		QString	GUIFileName=MBase->PieceGUIFile;
		if(GUIFileName.isEmpty()==true){
			GUIFileName=GetLayersBase()->GetGUIFileName();
			}
			
		//QString	ProgFile=QCoreApplication::applicationFilePath ();
		QString	ProgFile=MBase->EditorPathFile;
		if(ProgFile.isEmpty()==true){
			ProgFile=QCoreApplication::applicationFilePath ();
		}
		QDir::setCurrent(GetLayersBase()->GetSystemPath());

		QStringList Arguments;
		Arguments.append(QString(/**/"A")+MBase->TempPath);
		Arguments.append(QString(/**/"G")+GUIFileName);
		Arguments.append(QString(/**/"W")+QString::number(GetLayersBase()->GetWorkerID()));
		Arguments.append(QString(/**/"M")+QString::number(MasterCode));
		Arguments.append(QString(/**/"B")+QString::number(GetLayersBase()->GetBootingLevel()+1));
		Arguments.append(QString(/**/"Duplicate"));
		Arguments.append(QString(/**/"NoCamDevice"));
		Arguments.append(QString(/**/"NoSequence"));
		Arguments.append(QString(/**/"BootSmall"));
		Arguments.append(QString(/**/"NDM"));
		Arguments.append(QString(/**/"-R"));
		Arguments.append(QString(/**/"SetNumThreads1"));
		QProcess::startDetached( ProgFile, Arguments) ;
	}
}

void PiecePropertyForm::on_tablePieceArrange_clicked(const QModelIndex &index)
{
	GUIFormBase	*GProp=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"PiecePanel" ,/**/"");
	if(GProp!=NULL){
		DisplayImageWithAlgorithm	*DImage=dynamic_cast<DisplayImageWithAlgorithm *>(GProp);
		if(DImage!=NULL){
			int	Row=ui.tablePieceArrange->currentRow();
			if(Row<0){
				return;
			}
			PieceGridList	*c=GetPieceGridListFromRow(Row);
			if(c!=NULL){
				DImage->ExecuteReleaseAllSelection();

				int	GlobalPage=c->Page;
				GUICmdReqSelectPiece	RCmd(GetLayersBase(),sRoot,sName,GlobalPage);
				RCmd.PieceID	=c->PieceID;
				RCmd.Send(NULL,GlobalPage,0);
			}
			GProp->Repaint();
		}
	}
}
PieceGridList	*PiecePropertyForm::GetPieceGridListFromRow(int row)
{
	int	Row=0;
	for(int page=0;page<GetPageNumb();page++){
		for(PieceGridList *Piece=PieceGridTable[page].GetFirst();Piece!=NULL;Piece=Piece->GetNext()){
			if(Row==row){
				return Piece;
			}
			Row++;
		}
	}
	return NULL;
}