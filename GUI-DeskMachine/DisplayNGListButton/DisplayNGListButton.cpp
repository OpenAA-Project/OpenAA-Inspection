#include "DisplayNGListButtonResource.h"
#include "DisplayNGListButton.h"
#include "XGeneralFunc.h"
#include "XGeneralDialog.h"
#include "XSequenceLocal.h"
#include "XResult.h"
#include "XResultDLLManager.h"
#include "XFileRegistry.h"
#include "ListHistoryButtonPacket.h"
#include "XPixelInspectionPacket.h"
#include "DisplayThumbnailImagePacket.h"



char	*sRoot=/**/"Button";
char	*sName=/**/"DisplayNGListButton";

const	char	*LayersBase::GetLanguageSolutionFileName(void)
{
	return NULL;
}

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button Display NGList");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqNGList	(Base,sRoot,sName);
	(*Base)=new GUICmdSendNGList(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new DisplayNGListButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<10){
		return(-1);
	}
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"TargetImagePanelName";
	Data[0].Pointer				 =&((DisplayNGListButton *)Instance)->TargetImagePanelName;
	Data[1].Type				 =/**/"QStringList";
	Data[1].VariableNameWithRoute=/**/"RelatedPanel";
	Data[1].Pointer				 =&((DisplayNGListButton *)Instance)->RelatedPanel;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"BlinkNG";
	Data[2].Pointer				 =&((DisplayNGListButton *)Instance)->BlinkNG;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"PopupFormX";
	Data[3].Pointer				 =&((DisplayNGListButton *)Instance)->PopupFormX;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"PopupFormY";
	Data[4].Pointer				 =&((DisplayNGListButton *)Instance)->PopupFormY;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"PopupFormWidth";
	Data[5].Pointer				 =&((DisplayNGListButton *)Instance)->PopupFormWidth;
	Data[6].Type				 =/**/"int32";
	Data[6].VariableNameWithRoute=/**/"PopupFormHeight";
	Data[6].Pointer				 =&((DisplayNGListButton *)Instance)->PopupFormHeight;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"AnytimeShow";
	Data[7].Pointer				 =&((DisplayNGListButton *)Instance)->AnytimeShow;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"Popup";
	Data[8].Pointer				 =&((DisplayNGListButton *)Instance)->Popup;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"LocationInForm";
	Data[9].Pointer				 =&((DisplayNGListButton *)Instance)->LocationInForm;
	Data[10].Type				 ="QStringList";
	Data[10].VariableNameWithRoute="RelatedTabSheets";
	Data[10].Pointer			 =&((DisplayNGListButton *)Instance)->RelatedTabSheets;

	return(11);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/DisplayNGListButton.png")));
}

//=========================================================================================================

DisplayNGListButton::DisplayNGListButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
// ,NGListWindow(Base,parent)
{
	//言語対応
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/DisplayNGListImage.bmp",	//日本語
		/**/":Resources/DisplayNGListImage-en.bmp",	//English
		/**/":Resources/DisplayNGListImage-en.bmp",	//簡体中文
		/**/":Resources/DisplayNGListImage-en.bmp",	//繁体中文
		/**/":Resources/DisplayNGListImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	NGListWindow=new NGListForm(Base,this);
//	NGListWindow=new NGListForm(Base,0);
	NGListWindow->SetImagePanelName(TargetImagePanelName);
	BlinkNG	=false;
	resize(176,74);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));

	connect(NGListWindow->GetNGList(),SIGNAL(SignalKeyEnter())			,this,SLOT(SlotNGListKeyEnter()));
	connect(NGListWindow->GetNGList(),SIGNAL(SignalKeyLR())				,this,SLOT(SlotExecGeneralInfo2()));
	connect(NGListWindow->GetNGList(),SIGNAL(SignalKeyLRReverse())		,this,SLOT(SlotExecGeneralInfo2Reverse()));
	connect(NGListWindow->GetNGList(),SIGNAL(SignalKeyDeleteRepeat())	,this,SLOT(SlotKeyDeleteRepeat()));
	connect(NGListWindow->GetNGList(),SIGNAL(SignalKeyDelete())			,this,SLOT(SlotKeyDelete()));

	pGeneralTabSheet=NULL;

	PopupFormX		=0;
	PopupFormY		=0;
	PopupFormWidth	=250;
	PopupFormHeight	=250;
	AnytimeShow		=false;
	Popup			=true;
	LocationInForm	=true;

	pDisplayTargetImagePanel=NULL;
	NGImageWidth=NGImageHeight=NGImageBevel=0;

	//キーボード入力
	SetKeyGrab(true);

	//Sequence.dat GeneralInfo1 GeneralInfo2
	Param=NULL;

	//WaitTime
	WaitTime=0;
	GetParamGUI()->SetParam(&WaitTime, /**/"DisplayNGListButton",/**/"WaitTime",LangSolver.GetString(DisplayNGListButton_LS,LID_0)/*"Wait time for NG List move (millisecond)"*/);

	ErrorGroupData	=NULL;
	ErrorGroupNumber=NULL;
	ErrorGroupTable	=NULL;

////////// test
	NGcount_Phase0 = 0;
}
DisplayNGListButton::~DisplayNGListButton(void)
{
	if(ErrorGroupData!=NULL){
		delete	[]ErrorGroupData;
		ErrorGroupData=NULL;
	}
	if(ErrorGroupNumber!=NULL){
		delete	[]ErrorGroupNumber;
		ErrorGroupNumber=NULL;
	}
	if(ErrorGroupTable!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			delete	[]ErrorGroupTable[phase];
		}
		delete	[]ErrorGroupTable;
		ErrorGroupTable=NULL;
	}
}
void	DisplayNGListButton::Prepare(void)
{
	if(ErrorGroupData!=NULL){
		delete	[]ErrorGroupData;
	}
	ErrorGroupData	=new ErrorGroupPack[GetPhaseNumb()];

	int	ColCount=((NGListWindow->WidthPageNumber>0)?1:0)
				+((NGListWindow->WidthPosition>0)?1:0)
				+((NGListWindow->WidthLocationName>0)?1:0)
				+((NGListWindow->WidthCause>0)?1:0);
	NGListWindow->GetNGList()->setColumnCount(ColCount);
	NGListWindow->GetNGList()->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

	if(AnytimeShow==true){
		SlotClicked(true);
	}

	ResizeAction();
}

void	DisplayNGListButton::ResizeAction()
{
	Button.resize(width(),height());
}

void	DisplayNGListButton::SlotNGListKeyEnter()
{
	if(NGListWindow->GetNGList()->currentRow()==-1){
		return;
	}
	//サムネイル表示時、拡大画面を出す
	GUIFormBase	*DTImageForm=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayThumbnailImage" ,/**/"");
	if(DTImageForm!=NULL){
		CmdShowThumbnailDialog	CmdShowThumDialog(GetLayersBase());
		CmdShowThumDialog.CurrentRow=NGListWindow->GetNGList()->currentRow();
		DTImageForm->TransmitDirectly(&CmdShowThumDialog);
	}
}

static	int	ErrorGroupTableFunc(const void *a ,const void *b)
{
	ErrorGroup	*am=((ErrorGroup **)a)[0];
	ErrorGroup	*bm=((ErrorGroup **)b)[0];
	if(am->GetPieceAreaNumber()<bm->GetPieceAreaNumber())
		return -1;
	if(am->GetPieceAreaNumber()>bm->GetPieceAreaNumber())
		return 1;

	int aCx, aCy;
	am->GetCenter(aCx, aCy);
	int bCx, bCy;
	bm->GetCenter(bCx, bCy);

	if(aCy>bCy)
		return 1;
	if(aCy<bCy)
		return -1;

	if(aCx>bCx)
		return 1;
	if(aCx<bCx)
		return -1;
	return 0;
}
void	DisplayNGListButton::LoadNGColorInPlayer(void)
{
	if(pGeneralTabSheet==NULL){
		int		NGSize;
		QColor	NGSizeColor;
		if(ExecCmdPixelNGSize(NGSize,NGSizeColor)==true){
			for(int i=0;i<RelatedTabSheets.count();i++){
				QString	str=RelatedTabSheets.value(i);
				GUIFormBase	*r=GetFormByName(str);
				if(r==NULL)
					continue;
				GeneralTabSheet	*pGeneralTabSheet=dynamic_cast<GeneralTabSheet *>(r);
				if(pGeneralTabSheet!=NULL){
					pGeneralTabSheet->SetNGSizeColor(NGSizeColor);
					NGListWindow	->SetGeneralTabSheet(pGeneralTabSheet);
					NGListWindow	->SetNGSize(NGSize);
				}
			}
		}
	}
}

void	DisplayNGListButton::ShowInPlayer(int64 shownInspectionID)
{
/////////// test
	if(GetLayersBase()->GetPhaseNumb()>1){
		testPhase(shownInspectionID); // phase function
		return;
	}
///////////
	//Sequence.dat GeneralInfo1 GeneralInfo2
	if(Param==NULL){
		Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	}

	//RelatedTabSheets
	LoadNGColorInPlayer();

	for(int phase=0;phase<GetPhaseNumb();phase++){
		ErrorGroupData[phase].RemoveAll();
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqNGList		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.ShownInspectionID=shownInspectionID;
		CmdReq.ShowCause	=(NGListWindow->WidthCause>0)?true:false;
		GUICmdSendNGList	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				for(ErrorGroup *e=CmdAck.ErrorGroupData[phase].GetFirst();e!=NULL;e=e->GetNext()){
					e->SetPage(page);
				}
				ErrorGroupData[phase]+=CmdAck.ErrorGroupData[phase];
			}
		}
	}
	int	LNumb=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		LNumb+=ErrorGroupData[phase].GetNumber();
	}
	/*
	ErrorGroupData.RemoveAll();
	for(int page=0;page<GetPageNumb();page++){
		GUICmdReqNGList		CmdReq(GetLayersBase(),sRoot,sName,page);
		CmdReq.ShownInspectionID=shownInspectionID;
		CmdReq.ShowCause=(NGListWindow->WidthCause>0)?true:false;
		GUICmdSendNGList	CmdAck(GetLayersBase(),sRoot,sName,page);
		if(CmdReq.Send(page ,0,CmdAck)==true){
			for(ErrorGroup *e=CmdAck.ErrorGroupData.GetFirst();e!=NULL;e=e->GetNext()){
				e->SetPage(page);
			}
			ErrorGroupData+=CmdAck.ErrorGroupData;
			NGPointCount   =CmdAck.NGPointCount;
		}
	}
	int	LNumb=ErrorGroupData.GetNumber();
	*/

	NGListWindow->ConnectItemSelectionChanged(false);	//itemSelectionChangedを切る
	NGListWindow->GetNGList()->setRowCount(LNumb);
	//NGListWindow->GetNGList()->setCurrentCell(0,0);
	NGListWindow->GetNGList()->clearSelection();
	NGListWindow->ConnectItemSelectionChanged(true);	//itemSelectionChangedを復活
	//WidthLineNumber;
	int	N=0;
	if(NGListWindow->WidthPageNumber>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( N, new QTableWidgetItem(/**/"Pg"));
		NGListWindow->GetNGList()->setColumnWidth (N, NGListWindow->WidthPageNumber);
		N++;
	}
	if(NGListWindow->WidthPosition>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( N, new QTableWidgetItem(/**/"Position"));
		NGListWindow->GetNGList()->setColumnWidth (N, NGListWindow->WidthPosition);
		N++;
	}
	if(NGListWindow->WidthLocationName>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( N, new QTableWidgetItem(/**/"Location"));
		NGListWindow->GetNGList()->setColumnWidth (N, NGListWindow->WidthLocationName);
		N++;
	}
	if(NGListWindow->WidthCause>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( N, new QTableWidgetItem(/**/"Cause"));
		NGListWindow->GetNGList()->setColumnWidth (N, NGListWindow->WidthCause);
		N++;
	}

	//NG画像サイズ
	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();

	//ErrorGroupNumber
	if(ErrorGroupNumber!=NULL){
		delete []ErrorGroupNumber;
	}
	//ErrorGroupTable
	if(ErrorGroupTable!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			delete	[]ErrorGroupTable[phase];
		}
		delete	[]ErrorGroupTable;
	}
	ErrorGroupNumber=new int[GetPhaseNumb()];
	ErrorGroupTable	=new ErrorGroup**[GetPhaseNumb()];

	int	row=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
	//	for(ErrorGroup *e=ErrorGroupData[phase].GetFirst();e!=NULL;e=e->GetNext(),row++){

		ErrorGroupNumber[phase]=ErrorGroupData[phase].GetCount();
		ErrorGroupTable[phase]=new ErrorGroup*[ErrorGroupNumber[phase]];
		int	n=0;
		for(ErrorGroup *e=ErrorGroupData[phase].GetFirst();e!=NULL;e=e->GetNext()){
			ErrorGroupTable[phase][n]=e;
			n++;
		}
		QSort(ErrorGroupTable[phase],ErrorGroupNumber[phase],sizeof(ErrorGroupTable[0]),ErrorGroupTableFunc);

		for(n=0;n<ErrorGroupNumber[phase];n++,row++){
			ErrorGroup *e=ErrorGroupTable[phase][n];

			int	ex1,ey1,ex2,ey2;
			e->GetXY(ex1,ey1,ex2,ey2);
			QTableWidgetItem *W;
			int	N=0;
			if(NGListWindow->WidthPageNumber>0){
				W=NGListWindow->GetNGList()->item ( row, N);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, N,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(QString::number(e->GetPage()));
				N++;
			}
			if(NGListWindow->WidthPosition>0){
				W=NGListWindow->GetNGList()->item ( row, N);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, N,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(QString::number((ex1+ex2)>>1) + QString(/**/",") +QString::number((ey1+ey2)>>1));
				N++;
			}
			if(NGListWindow->WidthLocationName>0){
				W=NGListWindow->GetNGList()->item ( row, N);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, N,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(e->GetName());
				N++;
			}
			if(NGListWindow->WidthCause>0){
				W=NGListWindow->GetNGList()->item ( row, N);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, N,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(e->GetCause());
				N++;
			}
		}

		//DisplayThumbnailImageへデータの受け渡し
		GUIFormBase	*DTImageForm=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayThumbnailImage" ,/**/"");
		if(DTImageForm!=NULL){
			CmdSetNGInformation	CmdSetNGInfo(GetLayersBase());
			CmdSetNGInfo.ErrorGroupTableCount	=ErrorGroupNumber[phase];
			CmdSetNGInfo.ErrorGroupTable		=new ErrorGroup*[ErrorGroupNumber[phase]];
			for(int i=0;i<ErrorGroupNumber[phase];i++){
				CmdSetNGInfo.ErrorGroupTable[i]=ErrorGroupTable[phase][i];
			}
			CmdSetNGInfo.NGWidth				=RBase->NGImageWidth;
			CmdSetNGInfo.NGHeight				=RBase->NGImageHeight;
			DTImageForm->TransmitDirectly(&CmdSetNGInfo);
			DTImageForm->repaint();
		}

///		delete	[]ErrorGroupTable;
	}
///	NGListWindow->SetErrorGroupData(ErrorGroupData);
	NGListWindow->SetNGCount(row);
	NGListWindow->SetNGPointCount(NGPointCount);

	//TargetImagePanel
	if(pDisplayTargetImagePanel==NULL){
		GUIFormBase	*pDisplayTargetImagePanelBase=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelName);
		if(pDisplayTargetImagePanelBase!=NULL){
			pDisplayTargetImagePanel=dynamic_cast<DisplayImage *>(pDisplayTargetImagePanelBase);
			if(pDisplayTargetImagePanel!=NULL){
				NGListWindow->SetDisplayImage(pDisplayTargetImagePanel);
				DisplayWidth	=pDisplayTargetImagePanel->width()-34;
				DisplayHeight	=pDisplayTargetImagePanel->height()-32;
				DisplayRatio	=(double)DisplayWidth/DisplayHeight;
			}
		}
	}
	else if(DisplayWidth!=pDisplayTargetImagePanel->width()-34 || DisplayHeight!=pDisplayTargetImagePanel->height()-32){
		DisplayWidth	=pDisplayTargetImagePanel->width()-34;
		DisplayHeight	=pDisplayTargetImagePanel->height()-32;
		DisplayRatio	=(double)DisplayWidth/DisplayHeight;
	}
	//NG画像サイズ
///	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();
	if(NGImageWidth!=RBase->NGImageWidth || NGImageHeight!=RBase->NGImageHeight || NGImageBevel!=RBase->NGImageBevel){
		double NGImageRatio=(double)RBase->NGImageWidth/RBase->NGImageHeight;
		double ZoomRate;
		if(DisplayRatio>NGImageRatio){
			//表示エリアの方が横長
///			ZoomRate=(double)DisplayHeight/RBase->NGImageHeight;
			ZoomRate=(double)(DisplayHeight-(NGImageBevel<<1))/RBase->NGImageHeight;
		}
		else{
			//表示エリアの方が縦長
///			ZoomRate=(double)DisplayWidth/RBase->NGImageWidth;
			ZoomRate=(double)(DisplayWidth-(NGImageBevel<<1))/RBase->NGImageWidth;
		}
		NGListWindow->SetZoomRate(ZoomRate);
		NGImageWidth	=RBase->NGImageWidth;
		NGImageHeight	=RBase->NGImageHeight;
		NGImageBevel	=RBase->NGImageBevel;
	}

	//RowList
	NGListWindow->GetNGList()->ClearRowList();
	//WaitTime
	NGListWindow->GetNGList()->SetWaitTime(WaitTime);

	if(LNumb>0){
		//NGリストの一行目を表示
		NGListWindow->GetNGList()->selectRow(0);
		NGListWindow->GetNGList()->SetCurrentRowList();

		//Popup対応
		if(Popup==true){
			SlotClicked(true);
		}
	}
	else if(AnytimeShow==false && Popup==true){
		//NGリスト画面を閉じる
		NGListWindow->close();
	}

	//NGリスト行の設定
	if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
		return;
	}
	//GeneralInfo1
	Param->GeneralInfo1=row;

	//GeneralInfo2
	Param->GeneralInfo2=1;
	int Ret=ExecCmdPixelNGDrawMode(false,true);
	if(Ret!=-1){
		Param->GeneralInfo2=Ret;
	}
}
//////////// test
void	DisplayNGListButton::testPhase(int64 shownInspectionID){
	//Sequence.dat GeneralInfo1 GeneralInfo2
	if(Param==NULL){
		Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	}

	//RelatedTabSheets
	if(pGeneralTabSheet==NULL){
		int		NGSize;
		QColor	NGSizeColor;
		if(ExecCmdPixelNGSize(NGSize,NGSizeColor)==true){
			for(int i=0;i<RelatedTabSheets.count();i++){
				QString	str=RelatedTabSheets.value(i);
				GUIFormBase	*r=GetFormByName(str);
				if(r==NULL)
					continue;
				GeneralTabSheet	*pGeneralTabSheet=dynamic_cast<GeneralTabSheet *>(r);
				if(pGeneralTabSheet!=NULL){
					pGeneralTabSheet->SetNGSizeColor(NGSizeColor);
					NGListWindow	->SetGeneralTabSheet(pGeneralTabSheet);
					NGListWindow	->SetNGSize(NGSize);
				}
			}
		}
	}

	for(int phase=0;phase<GetPhaseNumb();phase++){
		ErrorGroupData[phase].RemoveAll();
	}
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqNGList		CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.ShownInspectionID=shownInspectionID;
		CmdReq.ShowCause	=(NGListWindow->WidthCause>0)?true:false;
		GUICmdSendNGList	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			for(int phase=0;phase<GetPhaseNumb();phase++){
				for(ErrorGroup *e=CmdAck.ErrorGroupData[phase].GetFirst();e!=NULL;e=e->GetNext()){
					e->SetPage(page);
				}
				ErrorGroupData[phase]+=CmdAck.ErrorGroupData[phase];
			}
		}
	}
	int	LNumb=0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		LNumb+=ErrorGroupData[phase].GetNumber();
	}

	NGListWindow->ConnectItemSelectionChanged(false);	//itemSelectionChangedを切る
	NGListWindow->GetNGList()->setRowCount(LNumb);
	//NGListWindow->GetNGList()->setCurrentCell(0,0);
	NGListWindow->GetNGList()->clearSelection();
	NGListWindow->ConnectItemSelectionChanged(true);	//itemSelectionChangedを復活
	//WidthLineNumber;
	int	Column=0;
	if(NGListWindow->WidthPageNumber>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( Column, new QTableWidgetItem(/**/"Ph"));
		NGListWindow->GetNGList()->setColumnWidth (Column, NGListWindow->WidthPageNumber);
		Column++;
	}
	if(GetLayersBase()->GetPhaseNumb()>1){
		NGListWindow->GetNGList()->setHorizontalHeaderItem(Column,new QTableWidgetItem(/**/"Pg"));
		NGListWindow->GetNGList()->setColumnWidth (Column, NGListWindow->WidthPageNumber);
		Column++;
	}
	if(NGListWindow->WidthPosition>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( Column, new QTableWidgetItem(/**/"Position"));
		NGListWindow->GetNGList()->setColumnWidth (Column, NGListWindow->WidthPosition);
		Column++;
	}
	if(NGListWindow->WidthLocationName>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( Column, new QTableWidgetItem(/**/"Location"));
		NGListWindow->GetNGList()->setColumnWidth (Column, NGListWindow->WidthLocationName);
		Column++;
	}
	if(NGListWindow->WidthCause>0){
		NGListWindow->GetNGList()->setHorizontalHeaderItem ( Column, new QTableWidgetItem(/**/"Cause"));
		NGListWindow->GetNGList()->setColumnWidth (Column, NGListWindow->WidthCause);
		Column++;
	}

	//NG画像サイズ
	ResultDLLBaseRoot	*RBase=GetLayersBase()->GetResultDLLBase()->GetFirst()->GetDLLPoint();

	//ErrorGroupNumber
	if(ErrorGroupNumber!=NULL){
		delete []ErrorGroupNumber;
	}
	//ErrorGroupTable
	if(ErrorGroupTable!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			delete	[]ErrorGroupTable[phase];
		}
		delete	[]ErrorGroupTable;
	}
	ErrorGroupNumber=new int[GetPhaseNumb()];
	ErrorGroupTable	=new ErrorGroup**[GetPhaseNumb()];

	int CurrentPhase = 0;
	if(ErrorGroupData[1].IsEmpty())
		NGcount_Phase0 = 0;
	else
		CurrentPhase = 1;
	int	row=NGcount_Phase0;
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ErrorGroupNumber[phase]=ErrorGroupData[phase].GetCount();
		ErrorGroupTable[phase]=new ErrorGroup*[ErrorGroupNumber[phase]];
		int	n=0;
		for(ErrorGroup *e=ErrorGroupData[phase].GetFirst();e!=NULL;e=e->GetNext()){
			ErrorGroupTable[phase][n]=e;
			n++;
		}
		for(n=NGcount_Phase0;n<ErrorGroupNumber[phase];n++,row++){
			ErrorGroup *e=ErrorGroupTable[phase][n];
			Column = 0;
			int	ex1,ey1,ex2,ey2;
			e->GetXY(ex1,ey1,ex2,ey2);
			QTableWidgetItem *W;
			if(GetLayersBase()->GetPhaseNumb()>1){
				W=NGListWindow->GetNGList()->item ( row, Column);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, Column,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(QString::number(phase));
				Column++;
			}
			if(NGListWindow->WidthPageNumber>0){
				W=NGListWindow->GetNGList()->item ( row, Column);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, Column,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(QString::number(e->GetPage()));
				Column++;
			}
			if(NGListWindow->WidthPosition>0){
				W=NGListWindow->GetNGList()->item ( row, Column);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, Column,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(QString::number((ex1+ex2)>>1) + QString(/**/",") +QString::number((ey1+ey2)>>1));
				Column++;
			}
			if(NGListWindow->WidthLocationName>0){
				W=NGListWindow->GetNGList()->item ( row, Column);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, Column,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(e->GetName());
				Column++;
			}
			if(NGListWindow->WidthCause>0){
				W=NGListWindow->GetNGList()->item ( row, Column);
				if(W==NULL){
					W=new QTableWidgetItem();
					NGListWindow->GetNGList()->setItem ( row, Column,W);
					W->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
				}
				W->setText(e->GetCause());
				Column++;
			}
		}
		//DisplayThumbnailImageへデータの受け渡し
		GUIFormBase	*DTImageForm=GetLayersBase()->FindByName(/**/"Inspection" ,/**/"DisplayThumbnailImage" ,/**/"");
		if(DTImageForm!=NULL){
			CmdSetNGInformation	CmdSetNGInfo(GetLayersBase());
			CmdSetNGInfo.ErrorGroupTableCount	=ErrorGroupNumber[phase];
			CmdSetNGInfo.ErrorGroupTable		=new ErrorGroup*[ErrorGroupNumber[phase]];
			for(int i=0;i<ErrorGroupNumber[phase];i++){
				CmdSetNGInfo.ErrorGroupTable[i]=ErrorGroupTable[phase][i];
			}
			CmdSetNGInfo.NGWidth				=RBase->NGImageWidth;
			CmdSetNGInfo.NGHeight				=RBase->NGImageHeight;
			DTImageForm->TransmitDirectly(&CmdSetNGInfo);
			DTImageForm->repaint();
		}
	}
	NGListWindow->SetNGCount(row);
	NGListWindow->SetNGPointCount(NGPointCount);

	//TargetImagePanel
	if(pDisplayTargetImagePanel==NULL){
			TargetImagePanelName = /**/"TargetImage";
			if(CurrentPhase==1)
				TargetImagePanelName.append(/**/"2");
		GUIFormBase	*pDisplayTargetImagePanelBase=GetLayersBase()->FindByName(/**/"Inspection",/**/"DisplayTargetImage" ,TargetImagePanelName);
		if(pDisplayTargetImagePanelBase!=NULL){
			pDisplayTargetImagePanel=dynamic_cast<DisplayImage *>(pDisplayTargetImagePanelBase);
			if(pDisplayTargetImagePanel!=NULL){
				NGListWindow->SetDisplayImage(pDisplayTargetImagePanel);
				DisplayWidth	=pDisplayTargetImagePanel->width()-34;
				DisplayHeight	=pDisplayTargetImagePanel->height()-32;
				DisplayRatio	=(double)DisplayWidth/DisplayHeight;
			}
		}
	}
	else if(DisplayWidth!=pDisplayTargetImagePanel->width()-34 || DisplayHeight!=pDisplayTargetImagePanel->height()-32){
		DisplayWidth	=pDisplayTargetImagePanel->width()-34;
		DisplayHeight	=pDisplayTargetImagePanel->height()-32;
		DisplayRatio	=(double)DisplayWidth/DisplayHeight;
	}
	//NG画像サイズ
	if(NGImageWidth!=RBase->NGImageWidth || NGImageHeight!=RBase->NGImageHeight || NGImageBevel!=RBase->NGImageBevel){
		double NGImageRatio=(double)RBase->NGImageWidth/RBase->NGImageHeight;
		double ZoomRate;
		if(DisplayRatio>NGImageRatio){
			//表示エリアの方が横長
			ZoomRate=(double)(DisplayHeight-(NGImageBevel<<1))/RBase->NGImageHeight;
		}
		else{
			//表示エリアの方が縦長
			ZoomRate=(double)(DisplayWidth-(NGImageBevel<<1))/RBase->NGImageWidth;
		}
		NGListWindow->SetZoomRate(ZoomRate);
		NGImageWidth	=RBase->NGImageWidth;
		NGImageHeight	=RBase->NGImageHeight;
		NGImageBevel	=RBase->NGImageBevel;
	}

	//RowList
	NGListWindow->GetNGList()->ClearRowList();
	//WaitTime
	NGListWindow->GetNGList()->SetWaitTime(WaitTime);

	if(LNumb>0){
		//NGリストの一行目を表示
		NGListWindow->GetNGList()->selectRow(0);
		NGListWindow->GetNGList()->SetCurrentRowList();

		//Popup対応
		if(Popup==true){
			SlotClicked(true);
		}
	}
	else if(AnytimeShow==false && Popup==true){
		//NGリスト画面を閉じる
		NGListWindow->close();
	}

	//NGリスト行の設定
	if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
		return;
	}
	//GeneralInfo1
	Param->GeneralInfo1=row;

	//GeneralInfo2
	Param->GeneralInfo2=1;
	int Ret=ExecCmdPixelNGDrawMode(false,true);
	if(Ret!=-1){
		Param->GeneralInfo2=Ret;
	}
	if(CurrentPhase==0)
		NGcount_Phase0 = ErrorGroupData[0].count();
}

void	DisplayNGListButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSetThumbnailInformation	*CmdSetThumbnailInformationVer=dynamic_cast<CmdSetThumbnailInformation *>(packet);
	if(CmdSetThumbnailInformationVer!=NULL){
		NGListWindow->SetThumbnailCount(CmdSetThumbnailInformationVer->ThumbnailCount);
		return;
	}
	CmdSetCurrentRow	*CmdSetCurrentRowVer=dynamic_cast<CmdSetCurrentRow *>(packet);
	if(CmdSetCurrentRowVer!=NULL){
		int CurrentRow=CmdSetCurrentRowVer->CurrentRow;
		//NGリスト移動
		NGListWindow->GetNGList()->selectRow(CurrentRow);
		return;
	}
/*
	CmdSetCurrentFocus	*CmdSetCurrentFocusVer=dynamic_cast<CmdSetCurrentFocus *>(packet);
	if(CmdSetCurrentFocusVer!=NULL){
		//フォームにフォーカスを持ってくる
		NGListWindow->setFocus(Qt::OtherFocusReason);
		NGListWindow->GetNGList()->setFocus(Qt::OtherFocusReason);
		return;
	}
*/
}

void DisplayNGListButton::keyPressEvent ( QKeyEvent * event )
{
	QCoreApplication::sendEvent(NGListWindow->GetNGList(),event);
	event->accept();
}

void DisplayNGListButton::keyReleaseEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_Delete){
		if(event->isAutoRepeat()==false){
			//履歴の削除対応
			ExecDeleteListHistory();
		}
		event->accept();
	}
}

void DisplayNGListButton::wheelEvent(QWheelEvent *event)
{
	//サムネイルをページ移動する
	if(event->delta()>0){
		NGListWindow->GetNGList()->ExecKeyPageUp();
	}
	else{
		NGListWindow->GetNGList()->ExecKeyPageDown();
	}
}

void DisplayNGListButton::Next()
{
	if(NGListWindow->GetNGList()->hasFocus()==false){
		if(NGListWindow->GetNGList()->currentIndex().row()+1<NGListWindow->GetNGList()->rowCount()){
			NGListWindow->GetNGList()->selectRow(NGListWindow->GetNGList()->currentIndex().row()+1);
		}
	}
}

void DisplayNGListButton::Previous()
{
	if(NGListWindow->GetNGList()->hasFocus()==false){
		if(NGListWindow->GetNGList()->currentIndex().row()-1>=0){
			NGListWindow->GetNGList()->selectRow(NGListWindow->GetNGList()->currentIndex().row()-1);
		}
	}
}

void DisplayNGListButton::ExecGeneralInfo2()
{
	if(Param==NULL){
		return;
	}
	int Ret=-1;
	if(Param->GeneralInfo2==0){			//赤表示を消す
		Ret=ExecCmdPixelNGDrawMode(false,false);
	}
	else if(Param->GeneralInfo2==1){	//赤丸表示のみ
		Ret=ExecCmdPixelNGDrawMode(false,true);
	}
	else if(Param->GeneralInfo2==2){	//詳細表示のみ
		Ret=ExecCmdPixelNGDrawMode(true,false);
	}
	else if(Param->GeneralInfo2==3){	//両方表示
		Ret=ExecCmdPixelNGDrawMode(true,true);
	}
	if(Ret!=-1){
		Param->GeneralInfo2=Ret;
	}
}

void DisplayNGListButton::ExecGeneralInfo2Reverse()
{
	if(Param==NULL){
		return;
	}
	int Ret=-1;
	if(Param->GeneralInfo2==0){			//詳細表示のみ
		Ret=ExecCmdPixelNGDrawMode(true,false);
	}
	else if(Param->GeneralInfo2==3){	//赤丸表示のみ
		Ret=ExecCmdPixelNGDrawMode(false,true);
	}
	else if(Param->GeneralInfo2==2){	//赤表示を消す
		Ret=ExecCmdPixelNGDrawMode(false,false);
	}
	else if(Param->GeneralInfo2==1){	//両方表示
		Ret=ExecCmdPixelNGDrawMode(true,true);
	}
	if(Ret!=-1){
		Param->GeneralInfo2=Ret;
	}
}

int DisplayNGListButton::ExecCmdPixelNGDrawMode(bool ShowOnlyDetail,bool ShowOnlyCircle)
{
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PixelInspection");
	if(LBase!=NULL){
		CmdPixelNGDrawMode CmdPacket(GetLayersBase());
		CmdPacket.ShowOnlyDetail=ShowOnlyDetail;
		CmdPacket.ShowOnlyCircle=ShowOnlyCircle;
		CmdPacket.GeneralInfo2	=Param->GeneralInfo2;
		LBase->TransmitDirectly(&CmdPacket);
		return CmdPacket.Ret;
	}
	return -1;
}

void DisplayNGListButton::ExecShowListHistory()
{
	GUIFormBase	*pHistoryButtonBase=GetLayersBase()->FindByName(/**/"List",/**/"HistoryButton" ,/**/"");
	if(pHistoryButtonBase!=NULL){
		CmdListHistoryButtonKeyFunc	CmdKeyFunc(GetLayersBase());
		CmdKeyFunc.KeyDeletePressRepeat	=true;
		pHistoryButtonBase->TransmitDirectly(&CmdKeyFunc);
	}
}

void DisplayNGListButton::ExecDeleteListHistory()
{
	GUIFormBase	*pHistoryButtonBase=GetLayersBase()->FindByName(/**/"List",/**/"HistoryButton" ,/**/"");
	if(pHistoryButtonBase!=NULL){
		CmdListHistoryButtonKeyFunc	CmdKeyFunc(GetLayersBase());
		CmdKeyFunc.KeyDeleteRelease	=true;
		pHistoryButtonBase->TransmitDirectly(&CmdKeyFunc);
	}
}

bool DisplayNGListButton::ExecCmdPixelNGSize(int &NGSize,QColor &NGSizeColor)
{
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"PixelInspection");
	if(LBase!=NULL){
		CmdPixelNGSize CmdPacket(GetLayersBase());
		LBase->TransmitDirectly(&CmdPacket);
		NGSize		=CmdPacket.NGSize;
		NGSizeColor	=CmdPacket.NGSizeColor;
		return true;
	}
	return false;
}

void DisplayNGListButton::SlotClicked (bool checked)
{
//	LogoInQWidget(GetLayersBase(),NGListWindow,sRoot ,sName);
//	GeneralDialog	D(GetLayersBase(),NGListWindow,this,false);

	int x=0,y=0;
	if(LocationInForm==true){
		QWidget *f=parentWidget();
		while(f->parentWidget()!=NULL){
			f=f->parentWidget();
		}
		x+=f->x();
		y+=f->y();
	}
//	D.move(x,y);
//	D.exec();
	NGListWindow->move	(PopupFormX+x,PopupFormY+y);
	NGListWindow->resize(PopupFormWidth,PopupFormHeight);
	NGListWindow->show	();
}

//=======================================================================

GUICmdReqNGList::GUICmdReqNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqNGList::Save(QIODevice *f)
{
	::Save(f,ShownInspectionID);
	::Save(f,ShowCause);
	return(true);
}
bool	GUICmdReqNGList::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	::Load(f,ShowCause);
	return(true);
}

void	GUICmdReqNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGList	*SendBack=GetSendBack(GUICmdSendNGList,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Initial();
	ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
	/*
	if(R!=NULL){
		NGImageContainerInPage	*p=R->GetNGImageInPage(localPage);
		if(p!=NULL){
			SendBack->ErrorGroupData=p->GetErrorGroupData();
			SendBack->NGPointCount	=R->GetNGPointCount();
		}
	}
	*/
	if(R!=NULL){
		for(int phase=0;phase<GetPhaseNumb();phase++){
			NGImageContainerInPhase	*Ph=R->GetNGImageInPhase(phase);
			if(Ph!=NULL){
				NGImageContainerInPage	*p=Ph->GetNGImageInPage(localPage);
				if(p!=NULL){
					SendBack->ErrorGroupData[phase]=p->GetErrorGroupData();
				}
			}
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//=======================================================================
/*
GUICmdSendNGList::GUICmdSendNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendNGList::Load(QIODevice *f)
{
	if(ErrorGroupData.Load(f,GetLayersBase())==false){
		return false;
	}
	return true;
}
bool	GUICmdSendNGList::Save(QIODevice *f)
{
	if(ErrorGroupData.Save(f)==false){
		return false;
	}
	return true;
}
*/

GUICmdSendNGList::GUICmdSendNGList(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	ErrorGroupData=new ErrorGroupPack[GetPhaseNumb()];
}

GUICmdSendNGList::~GUICmdSendNGList(void)
{
	delete	[]ErrorGroupData;
	ErrorGroupData=NULL;
}

void	GUICmdSendNGList::Initial(void)
{
	if(ErrorGroupData!=NULL)
		delete	[]ErrorGroupData;
	ErrorGroupData=new ErrorGroupPack[GetPhaseNumb()];
}

bool	GUICmdSendNGList::Load(QIODevice *f)
{
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	Initial();
	for(int phase=0;phase<N && phase<GetPhaseNumb();phase++){
		if(ErrorGroupData[phase].Load(f,GetLayersBase())==false)
			return false;
	}
	return true;
}
bool	GUICmdSendNGList::Save(QIODevice *f)
{
	int32	N=GetPhaseNumb();

	if(::Save(f,N)==false){
		return false;
	}
	for(int phase=0;phase<N;phase++){
		if(ErrorGroupData[phase].Save(f)==false)
			return false;
	}
	return true;
}

void	GUICmdSendNGList::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
