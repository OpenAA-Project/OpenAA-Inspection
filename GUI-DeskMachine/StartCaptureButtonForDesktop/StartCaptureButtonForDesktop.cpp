#include "StartCaptureButtonForDesktopResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI-DeskMachine\StartCaptureButtonForDesktop\StartCaptureButtonForDesktop.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StartCaptureButtonForDesktop.h"
#include "XPushCmdPacket.h"

#include "XPushCmdPacket.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XCriticalFunc.h"
#include "XGeneralFunc.h"
#include "XAnyData.h"
#include "NextMasterForm.h"
#include "XPushCmdPacket.h"
#include "swap.h"
#include "XAutoMaskingPIPacket.h"
#include "XFormOperator.h"
#include "XExecuteInspectBase.h"
#include "XFileRegistry.h"
#include "XDynamicClassifyPacket.h"
#include "XStatisticPacket.h"
#include <QMessageBox>
#include "XSyncGUI.h"

const	char	*sRoot=/**/"Action";
const	char	*sName=/**/"StartCaptureButtonForDesktop";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button for starting capture");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushedStartCapture		(Base,sRoot,sName);
	(*Base)=new GUICmdRepliedPushStartCapture	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartCaptureButtonForDesktop(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3){
		return(-1);
	}
	Data[0].Type				 =/**/"Master,Target";
	Data[0].VariableNameWithRoute=/**/"ImageType";
	Data[0].Pointer				 =&((StartCaptureButtonForDesktop *)Instance)->ImageType;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"PushedColor";
	Data[1].Pointer				 =&((StartCaptureButtonForDesktop *)Instance)->PushedColor;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"DebugMode";
	Data[2].Pointer				 =&((StartCaptureButtonForDesktop *)Instance)->DebugMode;

	return(3);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/StartCaptureButtonForDesktop.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"PixelInspection"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoMaskingPI"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"AutoAlignment"));
	List.AppendList(new RootNameList(/**/"Basic",/**/"StatisticImager"));
}

//==================================================================================================

StartCaptureButtonForDesktop::StartCaptureButtonForDesktop(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent)
{
	//言語対応
	FileRegistry	*FRegistry=new FileRegistry(/**/"./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt(/**/"Language",0);

	QString ImageBmpFile[5]={
		/**/":Resources/StartCaptureImageForDesktop.bmp",		//日本語
		/**/":Resources/StartCaptureImageForDesktop-en.bmp",	//English
		/**/":Resources/StartCaptureImageForDesktop-en.bmp",	//簡体中文
		/**/":Resources/StartCaptureImageForDesktop-en.bmp",	//繁体中文
		/**/":Resources/StartCaptureImageForDesktop-en.bmp"		//Korean
	};
///	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));	//D-20110322
	Button.setImageBmpColored(QImage(ImageBmpFile[LanguageCode]));

	ImageType=/**/"Master";
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"StartCaptureButtonForDesktop");
	Button.setAutoExclusive(true);
//	Button.setCheckable(true);	//D-20090910
	Button.setCheckable(false);	//A-20090910
	PushedColor=Qt::red;
	DebugMode=false;
	resize(176,74);
	connect(&Button		,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(&DUp		,SIGNAL(finished(int)),		this,SLOT(NextMasterFormFinished(int)));
	connect(&EditLibForm,SIGNAL(finished(int)),		this,SLOT(EditLibFormFinished(int)));
	connect(this		,SIGNAL(SignalResize()),	this,SLOT(ResizeAction()));
	SetKeyGrab(true);
	ClickOn=0;
	CurrentMasterCounter=-1;
	NextMasterFlag=false;
	ImageReadStateCounter=0;
	ReTeachingFlag=false;
	EditLibFormEnable=false;
	StartResister=false;
	SyncMode=false;

	BlickTimer.setInterval(300);
	BlickTimer.setSingleShot(false);
	BlickTimer.start();
	ExecuteType=_None;
	BlinkingMode	=false;
	connect(&BlickTimer,SIGNAL(timeout()),this,SLOT(SlotBlickTimer()));

	EditLibForm	.SetLayersBase(Base);
	DUp			.SetLanguageCode(LanguageCode);
	EditLibForm	.SetLanguageCode(LanguageCode);
}

StartCaptureButtonForDesktop::~StartCaptureButtonForDesktop(void)
{
}

void	StartCaptureButtonForDesktop::Prepare(void)
{
	Button.setPressedColor(PushedColor);
	ResizeAction();

	//デバッグモード
	if(DebugMode==true){
		DUp.resize(DUp.width(),262);
		EditLibForm.SetDebug(true);
	}
	else{
		DUp.resize(DUp.width(),195);
		EditLibForm.SetDebug(false);
	}
}

void	StartCaptureButtonForDesktop::ResizeAction()
{
	Button.resize(width(),height());
}

void	StartCaptureButtonForDesktop::BuildForShow(void)
{
}

void	StartCaptureButtonForDesktop::SlotBlickTimer()
{
	static	bool	ReEntrant=false;
	static	bool	FirstTime=true;

	if(ReEntrant==true)
		return;
	ReEntrant=true;

	if(FirstTime==true){
		BuildForShow();
	}
	FirstTime=false;

	if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL){
		ReEntrant=false;
		return;
	}
	SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();

	//デバッグモード
	if(DebugMode==true){
		if(ExecuteType==_OnMasterScanning2){
			//ダイアログの表示
			if(CurrentMasterCounter==-1){
				NextMasterFlag=false;
				DUp.SetNextMasterFlag(NextMasterFlag);
				DUp.SetMasterCounter(CurrentMasterCounter,false);
			}
			else if(CurrentMasterCounter>0){
				NextMasterFlag=true;
				DUp.SetNextMasterFlag(NextMasterFlag);
				DUp.SetMasterCounter(CurrentMasterCounter-1,true);
			}

			if(BlinkingMode==false){
				Button.DrawPressedColor();
				BlinkingMode=true;
			}
			else{
				Button.DrawNormalColor();
				BlinkingMode=false;
			}
			//EditLibraryFormの登録色の点滅処理
			if(EditLibFormEnable==true){
				EditLibForm.Update(BlinkingMode);
			}
			if(CurrentMasterCounter==2){
				if(EditLibForm.result()!=QDialog::Rejected){
					ReEntrant=false;
					return;
				}
				EditLibFormEnable=false;
			}
			else{
				if(CurrentMasterCounter==-1){
					//マスター画像の読み込み
					FormOperator	F((QWidget *)GetLayersBase()->GetMainWidget());
					F.ButtonPush(/**/"MainForm",/**/"LoadMaster");
					CurrentMasterCounter=0;
				}
				else{
					//ターゲット画像の読み込み
					FormOperator	F((QWidget *)GetLayersBase()->GetMainWidget());
					F.ButtonPush(/**/"MainForm",/**/"LoadTarget");
				}
			}
///			//ExecuteInitialAfterEditを発行
///			if(CurrentMasterCounter==2){
///				NPListPack<GUICmdPacketDim>	GUICmdDim;
///				GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
///				GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
///				for(int page=0;page<GetPageNumb();page++){
///					CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
///					CmdReq [page]->CurrentMasterCounter=CurrentMasterCounter;
///					CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
///					GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
///				}
///				GetLayersBase()->PacketSender(GUICmdDim);
///			}
///			else{
				//CurrentMasterCounterのセット
				GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter);
///			}

			////ExecuteScanningを実行
			//if(CurrentMasterCounter==0){
			//	GetLayersBase()->ExecuteScanning(GetLayersBase()->GetEntryPoint());
			//}

			if(CurrentMasterCounter>0){
				//Execute***を実行
				if(CurrentMasterCounter>1){
					GetLayersBase()->ExecuteStartByInspection	(GetLayersBase()->GetEntryPoint());
				}
				GetLayersBase()->ExecutePreAlignment		(GetLayersBase()->GetEntryPoint());
				GetLayersBase()->ExecuteAlignment			(GetLayersBase()->GetEntryPoint());
				GetLayersBase()->ExecutePreScanning			(GetLayersBase()->GetEntryPoint());
				GetLayersBase()->ExecuteScanning			(GetLayersBase()->GetEntryPoint());
				GetLayersBase()->ExecutePostScanning		(GetLayersBase()->GetEntryPoint());
			}

			//CmdGenerateAutoMaskForDesktopを発行
			if(CurrentMasterCounter==1){
				GetLayersBase()->ShowProcessingForm("Generating mask automatically");
				GetLayersBase()->AddMaxProcessing(0,0);

				NPListPack<GUICmdPacketDim>	GUICmdDim2;
				GUICmdReqGenerateAutoMaskForDesktop		*CmdReq2[100];
				GUICmdSendGenerateAutoMaskForDesktop	*CmdSend2[100];
				for(int page=0;page<GetPageNumb();page++){
					CmdReq2 [page]=new GUICmdReqGenerateAutoMaskForDesktop(GetLayersBase(),sRoot,sName,page);
					CmdSend2[page]=new GUICmdSendGenerateAutoMaskForDesktop(GetLayersBase(),sRoot,sName,page);
					GUICmdDim2.AppendList(new GUICmdPacketDim(CmdReq2[page],CmdSend2[page],page,0));
				}
				GetLayersBase()->PacketSender(GUICmdDim2);
				NextMasterFlag=true;
/*
				//ExecuteInitialAfterEditを発行
				NPListPack<GUICmdPacketDim>	GUICmdDim;
				GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
				GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
				for(int page=0;page<GetPageNumb();page++){
					CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
					CmdReq [page]->CurrentMasterCounter=CurrentMasterCounter;
					CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
					GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
				}
				GetLayersBase()->PacketSender(GUICmdDim);
				GetLayersBase()->CloseProcessingForm();
*/
				EditLibForm.pushButtonUpdateClicked();
			}

			if(CurrentMasterCounter==1){
				EditLibForm.Execute();
				//PropertyDynamicClassifyFormにTransmitDirectlyしてGenerateしてやる
				GUIFormBase	*PropertyDCForm=NULL;
				PropertyDCForm=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
				if(PropertyDCForm!=NULL){
					CmdDynamicClassifyGenerate	CmdDCGenerate(GetLayersBase());
					PropertyDCForm->TransmitDirectly(&CmdDCGenerate);
				}
				EditLibForm.setResult(QDialog::Accepted);
				EditLibForm.show();
				CurrentMasterCounter++;
				EditLibFormEnable=true;
			}
			else{
				DUp.SetNextMasterFlag(NextMasterFlag);
				if(DUp.exec()==QDialog::Rejected){
					CurrentMasterCounter++;
					ImageType=/**/"Target";
					SlotClicked (false);
				}
				else{
					GetLayersBase()->ShowProcessingForm ("");
					NPListPack<GUICmdPacketDim>	GUICmdDimFin;
					GUICmdReqExecuteInitialAfterEdit	*CmdReqFin[100];
					GUICmdSendExecuteInitialAfterEdit	*CmdSendFin[100];
					for(int page=0;page<GetPageNumb();page++){
						CmdReqFin [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
						CmdReqFin [page]->CurrentMasterCounter=99999999;
						CmdSendFin[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
						GUICmdDimFin.AppendList(new GUICmdPacketDim(CmdReqFin[page],CmdSendFin[page],page,0));
					}
					GetLayersBase()->PacketSender(GUICmdDimFin,GetParamGlobal()->MaxWaitingCommMilisec);
					ExecuteType=_AfterMasterScanning;
					GetLayersBase()->CloseProcessingForm();
				}
			}
		}
		ReEntrant=false;
		return;
	}

	if(ExecuteType==_None){
		Button.DrawNormalColor();
	}
	else if(ExecuteType==_OnMasterScanning1){
		//ダイアログの表示
		if(CurrentMasterCounter==-1){
			NextMasterFlag=true;
			DUp.SetNextMasterFlag(NextMasterFlag);
			DUp.SetMasterCounter(CurrentMasterCounter,false);
///			GetLayersBase()->GetParamGlobal()->CaptureInBackground=false;
		}
		else if(CurrentMasterCounter==1){
			NextMasterFlag=false;
			DUp.SetNextMasterFlag(NextMasterFlag);
			DUp.SetMasterCounter(CurrentMasterCounter,false);
			//GeneralInfo0
			Param->GeneralInfo0=2;
///			GetLayersBase()->GetParamGlobal()->CaptureInBackground=true;
		}
		else if(CurrentMasterCounter>1){
			NextMasterFlag=true;
			DUp.SetNextMasterFlag(NextMasterFlag);
			DUp.SetMasterCounter(CurrentMasterCounter-1,true);
		}

		//EditLibraryFormの表示
		if(EditLibFormEnable==false && StartResister==false && CurrentMasterCounter==2 && ReTeachingFlag==false){
			DUp.hide();
			EditLibForm.Execute();
			//PropertyDynamicClassifyFormにTransmitDirectlyしてGenerateしてやる
			GUIFormBase	*PropertyDCForm=NULL;
			PropertyDCForm=GetLayersBase()->FindByName(/**/"Button" ,/**/"PropertyDynamicClassifyForm" ,/**/"");
			if(PropertyDCForm!=NULL){
				CmdDynamicClassifyGenerate	CmdDCGenerate(GetLayersBase());
				PropertyDCForm->TransmitDirectly(&CmdDCGenerate);
			}
			EditLibFormEnable=true;
			EditLibForm.show();
		}
		else{
			EditLibFormEnable=false;
			DUp.show();
		}

		if(BlinkingMode==false){
			Button.DrawPressedColor();
			BlinkingMode=true;
		}
		else{
			Button.DrawNormalColor();
			BlinkingMode=false;
		}
		if(EditLibFormEnable==true || (Param!=NULL && Param->StartScanOnly==true)){
			ExecuteType=_OnMasterScanning2;
		}
	}
	else if(ExecuteType==_OnMasterScanning2){
		if(BlinkingMode==false){
			Button.DrawPressedColor();
			BlinkingMode=true;
		}
		else{
			Button.DrawNormalColor();
			BlinkingMode=false;
		}
		//EditLibraryFormの登録色の点滅処理
		if(EditLibFormEnable==true){
			EditLibForm.Update(BlinkingMode);
		}
		//ExecuteInspectStateの取得
		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetState()==ExecuteInspectBase::_EI_OnTransmit){
			DUp.ui.prgImageReadState->setMaximum(100);
			DUp.ui.prgImageReadState->setTextVisible(true);
			ImageReadStateCounter++;
			DUp.ui.prgImageReadState->setValue(ImageReadStateCounter*10);

			//GeneralInfo0
			if(Param->GeneralInfo0!=2){
				Param->GeneralInfo0=1;
			}
		}
/*
		//CaptureStartCounterで判断してみる
		if(Param->CaptureStartCounter==2){
			ReEntrant=false;
			return;
		}
*/
		if(EditLibFormEnable==false && (Param!=NULL && Param->StartScanOnly==false)){
			DUp.ui.prgImageReadState->setValue(100);

			if(CurrentMasterCounter==-1){
				CurrentMasterCounter=0;
			}
/*
			//ExecuteInitialAfterEditを発行
			if(CurrentMasterCounter==2){
				NPListPack<GUICmdPacketDim>	GUICmdDim;
				GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
				GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
				for(int page=0;page<GetPageNumb();page++){
					CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
					CmdReq [page]->CurrentMasterCounter=CurrentMasterCounter+1;
					CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
					GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
				}
				GetLayersBase()->PacketSender(GUICmdDim);
			}
*/
			////ExecuteScanningを実行
			//if(CurrentMasterCounter==0){
			//	//CurrentMasterCounterのセット
			//	GetLayersBase()->GetAnyData()->Set("CurrentMasterCounter",CurrentMasterCounter);
			//	GetLayersBase()->ExecuteScanning(GetLayersBase()->GetEntryPoint());
			//}

			//CurrentMasterCounterのセット
			GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter+1);

			//CmdGenerateAutoMaskForDesktopを発行
			if(CurrentMasterCounter==1){
				GetLayersBase()->ShowProcessingForm("Generating mask area");
				GetLayersBase()->AddMaxProcessing(0,0);

				NPListPack<GUICmdPacketDim>	GUICmdDim2;
				GUICmdReqGenerateAutoMaskForDesktop		*CmdReq2[100];
				GUICmdSendGenerateAutoMaskForDesktop	*CmdSend2[100];
				for(int page=0;page<GetPageNumb();page++){
					CmdReq2 [page]=new GUICmdReqGenerateAutoMaskForDesktop(GetLayersBase(),sRoot,sName,page);
					CmdSend2[page]=new GUICmdSendGenerateAutoMaskForDesktop(GetLayersBase(),sRoot,sName,page);
					GUICmdDim2.AppendList(new GUICmdPacketDim(CmdReq2[page],CmdSend2[page],page,0));
				}
				GetLayersBase()->PacketSender(GUICmdDim2);
/*
				//ExecuteInitialAfterEditを発行
				NPListPack<GUICmdPacketDim>	GUICmdDim;
				GUICmdReqExecuteInitialAfterEdit	*CmdReq[100];
				GUICmdSendExecuteInitialAfterEdit	*CmdSend[100];
				for(int page=0;page<GetPageNumb();page++){
					CmdReq [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
					CmdReq [page]->CurrentMasterCounter=CurrentMasterCounter+1;
					CmdSend[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
					GUICmdDim.AppendList(new GUICmdPacketDim(CmdReq[page],CmdSend[page],page,0));
				}
				GetLayersBase()->PacketSender(GUICmdDim);
				GetLayersBase()->CloseProcessingForm();
*/
				EditLibForm.pushButtonUpdateClicked();
			}

			//何枚目かの表示
//			if(CurrentMasterCounter>0){
//				DUp.SetMasterCounter(CurrentMasterCounter,true);
//			}
			CurrentMasterCounter++;
			if(CurrentMasterCounter==2 && ReTeachingFlag==false){
				ExecuteType=_OnMasterScanning1;
			}
			else{
				ImageType=/**/"Target";
				SlotClicked(false);
			}

			//ProgressBarの更新
			DUp.ui.prgImageReadState->setValue(0);
			ImageReadStateCounter=0;
			DUp.ui.prgImageReadState->setTextVisible(false);
			DUp.ui.prgImageReadState->setMaximum(0);
			DUp.ui.prgImageReadState->repaint();

//			//GeneralInfo0
//			Param->GeneralInfo0=0;
		}
	}
	else if(ExecuteType==_AfterMasterScanning){
		Button.DrawNormalColor();
	}
	ReEntrant=false;
}

IntList	HDbgSlotList;

void	StartCaptureButtonForDesktop::SlotClicked (bool checked)
{
	if(GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1)==99999999){
		//確認メッセージ
		QMessageBox MsgBox;
		QFont font1;
		font1.setPointSize(12);
		font1.setBold(true);
		font1.setWeight(75);
		MsgBox.setFont	(font1);
		MsgBox.setText	(LangSolver.GetString(StartCaptureButtonForDesktop_LS,LID_92)/*"Do you want re-teaching?"*/);	//新しく学習データを登録し直しますか？
		MsgBox.addButton(LangSolver.GetString(StartCaptureButtonForDesktop_LS,LID_93)/*"Yes"*/		,QMessageBox::AcceptRole);	//はい
		MsgBox.addButton(LangSolver.GetString(StartCaptureButtonForDesktop_LS,LID_94)/*"Cancel"*/	,QMessageBox::RejectRole);	//キャンセル
//		MsgBox.addButton("キャンセル"	,QMessageBox::DestructiveRole);
		MsgBox.setWindowFlags(Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint);
		int Ret=MsgBox.exec();

		if(Ret==QMessageBox::AcceptRole){	//はい
			//学習基板の登録から再始動
			CurrentMasterCounter=2;
			//CurrentMasterCounterのセット
			GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter);
			ReTeachingFlag		=true;
			//StatisticImagerのInitialAlloc()を実行する
			int	globalPage=GetLayersBase()->GetGlobalPageFromLocal(0);
			GUICmdReqExecuteInitialAlloc	Cmd		(GetLayersBase(),sRoot,sName,globalPage);
			GUICmdSendExecuteInitialAlloc	AckCmd	(GetLayersBase(),sRoot,sName,globalPage);
			if(Cmd.Send(globalPage ,0,AckCmd)==false){
				SetError(Error_Comm , /**/"Send error :GUICmdReqExecuteInitialAlloc",ErrorCodeList::_Alart);
				return;
			}
			ImageType=/**/"Target";
		}
		else if(Ret==QMessageBox::RejectRole){	//キャンセル
			return;
		}
	}

//	if(checked==true){	//D-20090910
//		Button.setColor(PushedColor);

//		CurrentMasterCounter=0;
//		ui.labelCurrentCount->setText(QString::number(CurrentMasterCounter));

		//デバッグモード
		if(DebugMode==true){
			ExecuteType=_OnMasterScanning2;
			return;
		}

		ExecuteType=_OnMasterScanning1;

		GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->StartAllCamera();
		SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
		if(checked==true && Param!=NULL){
			Param->CaptureMode=2;
		}

		int	CStrategic=max(GetLayersBase()->GetCurrentStrategicNumber(),GetLayersBase()->GetCurrentStrategicNumberForSeq());
		IntList		SList;
		GetParamGlobal()->GetStrategyPage (CStrategic ,SList);
		if(GetParamGlobal()->GetMaxScanStrategy()<=1 || CStrategic==0){
			GetLayersBase()->ExecuteStartByScanOnly(GetLayersBase()->GetEntryPoint());
		}

		if((GetParamGlobal()->DebugLevel & 0x04)!=0){
			HDbgSlotList.AppendList(new IntClass(CStrategic));
		}

		GUICmdPushedStartCapture		*Cmd[100];
		GUICmdRepliedPushStartCapture	*Reply[100];
/*
		for(int page=0;page<GetPageNumb();page++){
			Cmd[page]	=new GUICmdPushedStartCapture(GetLayersBase(),sRoot,sName,page);
			Cmd[page]->ImageType=ImageType;
			Cmd[page]->StrategicNumber		=CStrategic;
			Reply[page]	=new GUICmdRepliedPushStartCapture(GetLayersBase(),sRoot,sName,page);
		}
		for(int page=0;page<GetPageNumb();page++){
			Cmd[page]->Send(page ,0,*Reply[page]);
		}
		bool	ReadyAll;
		do{
			ReadyAll=true;
			for(int page=0;page<GetPageNumb();page++){
				if(Reply[page]->IsReceived()==false){
					ReadyAll=false;
				}
			}
		}while(ReadyAll==false);
*/
		int	N=0;
		for(IntClass *s=SList.GetFirst();s!=NULL;s=s->GetNext(),N++){
			int page=s->GetValue();
			Cmd[N]	=new GUICmdPushedStartCapture(GetLayersBase(),sRoot,sName,page);
			Cmd[N]->ImageType=ImageType;
			Cmd[N]->StrategicNumber		=CStrategic;
			Reply[N]	=new GUICmdRepliedPushStartCapture(GetLayersBase(),sRoot,sName,page);
		}
		for(int i=0;i<N;i++){
			Cmd[i]->Send(Cmd[i]->GetGlobalPage() ,0,*Reply[i]);
		}
		bool	ReadyAll;
		do{
			ReadyAll=true;
			for(int i=0;i<N;i++){
				if(Reply[i]->IsReceived()==false){
					ReadyAll=false;
				}
			}
		}while(ReadyAll==false);

		if(Param!=NULL){
			Param->ReadyForScan=true;
		}

		for(int page=0;page<GetPageNumb();page++){
			delete	Cmd[page]	;
			delete	Reply[page]	;
		}
		Button.Cancel();


		if(GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()!=ExecuteInspectBase::_CaptureOnlyMaster){
			GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoMasterCaptureOnly();
		}

		if(SyncMode==false){
			if(GetLayersBase()->GetSyncGUIData()->GetConnectedCount()!=0){
				QBuffer	Buff;
				Buff.open(QIODevice::ReadWrite);
				TxSync(Buff.buffer());
			}
		}
//	}						//D-20090910
//	else{					//D-20090910
//		ExecuteType=_None;	//D-20090910
//	}						//D-20090910
}

void StartCaptureButtonForDesktop::NextMasterFormFinished(int result)
{
	//デバッグモード
	if(DebugMode==true){
		return;
	}

	//GeneralInfo0
	SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	Param->GeneralInfo0=3;

	//撮像のキャンセル指示
	GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GoHalt();

	if(result==QDialog::Accepted){
		GetLayersBase()->ShowProcessingForm ("Next master");
		NPListPack<GUICmdPacketDim>	GUICmdDimFin;
/*
		GUICmdReqExecuteInitialAfterEdit	*CmdReqFin[100];
		GUICmdSendExecuteInitialAfterEdit	*CmdSendFin[100];
		for(int page=0;page<GetPageNumb();page++){
			CmdReqFin [page]=new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,page);
			CmdReqFin [page]->CurrentMasterCounter=99999999;
			CmdSendFin[page]=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,page);
			GUICmdDimFin.AppendList(new GUICmdPacketDim(CmdReqFin[page],CmdSendFin[page],page,0));
		}
*/
		GUICmdReqExecuteInitialAfterEdit	*CmdReqFin;
		GUICmdSendExecuteInitialAfterEdit	*CmdSendFin;
		CmdReqFin =new GUICmdReqExecuteInitialAfterEdit (GetLayersBase(),sRoot,sName,0);
		CmdReqFin ->CurrentMasterCounter=99999999;
		CmdSendFin=new GUICmdSendExecuteInitialAfterEdit(GetLayersBase(),sRoot,sName,0);
		GUICmdDimFin.AppendList(new GUICmdPacketDim(CmdReqFin,CmdSendFin,0,0));
		GetLayersBase()->PacketSender(GUICmdDimFin,GetParamGlobal()->MaxWaitingCommMilisec);
		ExecuteType=_AfterMasterScanning;
//		CurrentMasterCounter--;
//		GetLayersBase()->GetAnyData()->Set("CurrentMasterCounter",CurrentMasterCounter);
		GetLayersBase()->CloseProcessingForm();
	}
	else{
		ExecuteType=_AfterMasterScanning;
		CurrentMasterCounter=-1;
	}

//	//GeneralInfo0
//	Param->GeneralInfo0=0;
}

void StartCaptureButtonForDesktop::EditLibFormFinished(int result)
{
	//デバッグモード
	if(DebugMode==true){
		return;
	}

	//撮像許可
	StartResister=true;
	ImageType=/**/"Target";
	SlotClicked(false);

	DUp.show();
}

void StartCaptureButtonForDesktop::keyPressEvent ( QKeyEvent * event )
{
	if(event->key()==Qt::Key_F5){
		//SlotClicked(true);
		Button.Exec();
	}
}
void StartCaptureButtonForDesktop::RxSync(QByteArray &f)
{
	SyncMode=true;
	SlotClicked(true);
	SyncMode=false;
}

void StartCaptureButtonForDesktop::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqAutoPCBHoleAlignerShowPasteCreateWithShape	*CmdReqPCBHoleAlignShowPasteVar=dynamic_cast<CmdReqAutoPCBHoleAlignerShowPasteCreateWithShape *>(packet);
	if(CmdReqPCBHoleAlignShowPasteVar!=NULL){
		SetHoleGerberButton(CmdReqPCBHoleAlignShowPasteVar->LibID,CmdReqPCBHoleAlignShowPasteVar->FromOtherAlgorithmIndex);
		return;
	}
}

IntList	HDbgScanMaster;

bool StartCaptureButtonForDesktop::OnIdle(void)
{
	static	bool	IsExecuteInspection=false;

	GUIFormBase::OnIdle();
	if(GetLayersBase()==NULL || GetLayersBase()->GetEntryPoint()==NULL || GetLayersBase()->GetEntryPoint()->GetExecuteInspect()==NULL)
		return true;
	SeqControlParam	*Param=(SeqControlParam *)GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetSeqParam();
	if(Param->StartScanOnly==true){	
		//SlotClicked (true);
		//Button.setChecked(true);
		//Param->StartScanOnly=false;
	}
	if(Param->ExecuteScanMaster==true){
		ClickOn++;
		if((GetParamGlobal()->DebugLevel & 0x04)!=0){
			HDbgScanMaster.AppendList(new IntClass(ClickOn));
		}
		Param->ExecuteScanMaster=false;
	}
	if(Param->ExecuteInspection==true){
		ClickOn++;
		if((GetParamGlobal()->DebugLevel & 0x04)!=0){
			HDbgScanMaster.AppendList(new IntClass(ClickOn));
		}
		Param->ExecuteInspection=false;
		IsExecuteInspection		=true;
	}
	if(ClickOn!=0 && GetLayersBase()->GetEntryPoint()->GetExecuteInspect()->GetMode()==ExecuteInspectBase::_EI_IDLE){
		if(IsExecuteInspection==true){
			ImageType=/**/"Target";
			SlotClicked(false);
			IsExecuteInspection	=false;
		}
		else{
			SlotClicked(true);
		}
		ClickOn--;
	}
	return true;
}

//============================================================================================================================
bool	GUICmdReqExecuteInitialAfterEdit::Load(QIODevice *f)
{	
	if(::Load(f,CurrentMasterCounter)==false)
		return false;
	return true;	
}
bool	GUICmdReqExecuteInitialAfterEdit::Save(QIODevice *f)
{	
	if(::Save(f,CurrentMasterCounter)==false)
		return false;
	return true;	
}

void	GUICmdReqExecuteInitialAfterEdit::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GetLayersBase()->GetAnyData()->Set(/**/"CurrentMasterCounter",CurrentMasterCounter);
	ExecuteInitialAfterEditInfo EInfo;
	GetLayersBase()->ExecuteInitialAfterEdit	(EInfo);

	GUICmdSendExecuteInitialAfterEdit	*SendBack=GetSendBack(GUICmdSendExecuteInitialAfterEdit,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);

}

//============================================================================================================================
bool	GUICmdReqGenerateAutoMaskForDesktop::Load(QIODevice *f)
{
//	if(::Load(f,CurrentMasterCounter)==false)
//		return false;
	return true;	
}
bool	GUICmdReqGenerateAutoMaskForDesktop::Save(QIODevice *f)
{
//	if(::Save(f,CurrentMasterCounter)==false)
//		return false;
	return true;	
}

void	GUICmdReqGenerateAutoMaskForDesktop::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
//	GetLayersBase()->GetAnyData()->Set("CurrentMasterCounter",CurrentMasterCounter);
//	GetLayersBase()->ExecuteInitialAfterEdit	(GetLayersBase()->GetEntryPoint());

	CmdGenerateAutoMaskingPILibraryPacket	Cmd(GetLayersBase());
	Cmd.LibID=-1;
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoMaskingPI");
	if(MBase!=NULL){
		MBase->TransmitDirectly(&Cmd);
	}

	GUICmdSendGenerateAutoMaskForDesktop	*SendBack=GetSendBack(GUICmdSendGenerateAutoMaskForDesktop,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

//============================================================================================================================
void	GUICmdReqExecuteInitialAlloc::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	CmdExecuteInitialAllocPacket	Cmd(GetLayersBase());
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"StatisticImager");
	if(MBase!=NULL){
		MBase->TransmitDirectly(&Cmd);
	}

	GUICmdSendExecuteInitialAlloc	*SendBack=GetSendBack(GUICmdSendExecuteInitialAlloc,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}
