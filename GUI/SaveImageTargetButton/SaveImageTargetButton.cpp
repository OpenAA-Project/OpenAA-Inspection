/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveImageTargetButton\SaveImageTargetButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SaveImageTargetButtonResource.h"
#include "SaveImageTargetButton.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
//#include <zlib.h>
#include "XGeneralStocker.h"
#include "XMainSchemeMemory.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"SaveImageTargetButton";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Save Target Image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqSaveTargetImage (Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSaveTargetImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SaveImageTargetButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<8)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((SaveImageTargetButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((SaveImageTargetButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((SaveImageTargetButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((SaveImageTargetButton *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileNameForSaving";
	Data[4].Pointer				 =&((SaveImageTargetButton *)Instance)->FileNameForSaving;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowProcessingWindow";
	Data[5].Pointer				 =&((SaveImageTargetButton *)Instance)->ShowProcessingWindow;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"SaveInBackground";
	Data[6].Pointer				 =&((SaveImageTargetButton *)Instance)->SaveInBackground;
	Data[7].Type				 =/**/"int32";
	Data[7].VariableNameWithRoute=/**/"UseLayer";
	Data[7].Pointer				 =&((SaveImageTargetButton *)Instance)->UseLayer;

	return(8);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SaveImageTargetButton.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	SaveImageTargetButton	*V=dynamic_cast<SaveImageTargetButton *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SaveImage(FileName,CmdReqSaveImage::_SaveTargetImage);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save PIX from Target");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

//==================================================================================================
SaveImageTargetButton::SaveImageTargetButton(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent),ThreadSaveInst(Base->GetMainWidget(),Base,this)
{
	ShowProcessingWindow	=true;
	SaveInBackground		=false;
	UseLayer	=-1;

	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"SaveTarget");
	Msg=/**/"Save Target";
	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

SaveImageTargetButton::~SaveImageTargetButton(void)
{
	ThreadSaveInst.Terminated=true;
	ThreadSaveInst.wait(500);
}

void	SaveImageTargetButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	if(SaveInBackground==true){
		ThreadSaveInst.start();
	}
}

void	SaveImageTargetButton::BuildForShow(void)
{
	if(SaveInBackground==true){
		ThreadSaveInst.Allocate();
	}
}

void	SaveImageTargetButton::ResizeAction()
{
	Button.resize(width(),height());
}

void SaveImageTargetButton::SlotClicked (bool checked)
{
	QString	FileName;
	if(FileNameForSaving.isEmpty()==true){
		FileName=GetLayersBase()->LGetSaveFileName (this
													, LangSolver.GetString(SaveImageTargetButton_LS,LID_0)/*"Save Target Image file"*/
													,QString()
													,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	}
	else{
		FileName=FileNameForSaving;
	}
	if(FileName.isEmpty()==true)
		return;
	SaveImage(FileName,CmdReqSaveImage::_SaveTargetImage);
}
void	SaveImageTargetButton::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqSaveImage	*CmdReqSaveImageVar=dynamic_cast<CmdReqSaveImage *>(packet);
	if(CmdReqSaveImageVar!=NULL){
		int	tUseLayer=UseLayer;
		UseLayer=CmdReqSaveImageVar->UseLayer;
		CmdReqSaveImageVar->Success=SaveImage(CmdReqSaveImageVar->FileName,CmdReqSaveImageVar->UsageImageMode);
		UseLayer=tUseLayer;
		return;
	}
	CmdReqSaveImageWithGeneralStocker	*CmdReqSaveImageWithGeneralStockerVar=dynamic_cast<CmdReqSaveImageWithGeneralStocker *>(packet);
	if(CmdReqSaveImageWithGeneralStockerVar!=NULL){
		QVariantList	ArgV;
		QVariantList	RetV;
		GetLayersBase()->GetGeneralStocker()->GetData(/**/"GetFolder",RetV,ArgV);
		if(RetV.count()>0){
			QString	FileName=RetV[0].toString();
			CmdReqSaveImageWithGeneralStockerVar->Success=SaveImage(FileName,CmdReqSaveImage::_SaveTargetImage);
		}
		return;
	}
}

bool SaveImageTargetButton::SaveImage(QString FileName,CmdReqSaveImage::UsageImage TypeOfImage)
{
	if(SaveInBackground!=true){
		QFile	WFile(FileName);
		if(WFile.open(QIODevice::WriteOnly)==false)
			return false;

		if(SaveImageV3(&WFile,ShowProcessingWindow)==false){
			return false;
		}
	}
	else{
		if(ThreadSaveInst.Saved==true)
			return false;
		ThreadSaveInst.FileName	=FileName;
		ThreadSaveInst.UseLayer=UseLayer;
		if(ThreadSaveInst.CopyFrom(TypeOfImage)==false){
			return false;
		}
	}
	return true;
}
bool SaveImageTargetButton::SaveImage(QIODevice *f ,bool iShowProcessingWindow)
{
	int	PhaseNumb=GetPhaseNumb();
	if(GetParamGlobal()->CommonTargetBetweenPhases==true)
		PhaseNumb=1;
	int	Ver=2;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,(int)PhaseNumb)==false)
		return false;
	if(::Save(f,(int)GetPageNumb())==false)
		return false;
	if(UseLayer<0){
		if(::Save(f,(int)GetLayerNumb(0))==false)
			return false;
	}
	else{
		int	LayerNumb=1;
		if(::Save(f,LayerNumb)==false)
			return false;
	}
	if(::Save(f,(int)GetDotPerLine(0))==false)
		return false;
	if(::Save(f,(int)GetMaxLines(0))==false)
		return false;
	if(::Save(f,(int)100)==false)
		return false;

	int	YCountBase=100;
	if(iShowProcessingWindow==true){
		GetLayersBase()->ShowProcessingForm (LangSolver.GetString(SaveImageTargetButton_LS,LID_3)/*"Save PIX image from target buffer"*/);
		GetLayersBase()->SetMaxProcessing(GetPhaseNumb()*((GetMaxLines(0)+YCountBase-1)/YCountBase));
	}
	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	YCount=YCountBase;
			for(int TopY=0;TopY<GetMaxLines(page);TopY+=YCount){
				if(TopY+YCount>GetMaxLines(page))
					YCount=GetMaxLines(page)-TopY;
				if(UseLayer<0){
					for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
						GUICmdReqSaveTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Phase	=phase;
						RCmd.Layer	=Layer;
						RCmd.TopY	=TopY;
						RCmd.YCount	=YCount;
						GUICmdSendSaveTargetImage	SCmd(GetLayersBase() ,sRoot,sName,page);
						if(RCmd.Send(page ,0,SCmd)==true){
							f->write(SCmd.Data);
						}
					}
				}
				else if(UseLayer<GetLayerNumb(page)){
					GUICmdReqSaveTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					RCmd.Phase	=phase;
					RCmd.Layer	=UseLayer;
					RCmd.TopY	=TopY;
					RCmd.YCount	=YCount;
					GUICmdSendSaveTargetImage	SCmd(GetLayersBase() ,sRoot,sName,page);
					if(RCmd.Send(page ,0,SCmd)==true){
						f->write(SCmd.Data);
					}
				}
				if(iShowProcessingWindow==true){
					GetLayersBase()->StepProcessing(page);
				}
			}
		}
	}
	if(iShowProcessingWindow==true){
		GetLayersBase()->CloseProcessingForm ();
	}
	return true;
}

bool SaveImageTargetButton::SaveImageV3(QIODevice *f ,bool iShowProcessingWindow)
{
	int	PhaseNumb=GetPhaseNumb();
	if(GetParamGlobal()->CommonTargetBetweenPhases==true)
		PhaseNumb=1;
	int	Ver=3;
	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,(int)PhaseNumb)==false)
		return false;

	for(int phase=0;phase<PhaseNumb;phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		if(::Save(f,(int)Ph->GetPageNumb())==false)
			return false;
		for(int page=0;page<Ph->GetPageNumb();page++){
			DataInPage *Dp=Ph->GetPageData(page);
			if(::Save(f,(int)Dp->GetLayerNumb())==false)
				return false;
			if(::Save(f,(int)Dp->GetDotPerLine())==false)
				return false;
			if(::Save(f,(int)Dp->GetMaxLines())==false)
				return false;
		}
	}

	for(int phase=0;phase<PhaseNumb;phase++){
		PageDataInOnePhase	*Ph=GetLayersBase()->GetPageDataPhase(phase);
		for(int page=0;page<Ph->GetPageNumb();page++){
			DataInPage *Dp=Ph->GetPageData(page);

			int	YCountBase=100;
			if(iShowProcessingWindow==true){
				GetLayersBase()->ShowProcessingForm (LangSolver.GetString(SaveImageTargetButton_LS,LID_3)/*"Save PIX image from target buffer"*/);
				GetLayersBase()->SetMaxProcessing(GetPhaseNumb()*((GetMaxLines(0)+YCountBase-1)/YCountBase));
			}
			int	YCount=YCountBase;
			for(int TopY=0;TopY<Dp->GetMaxLines();TopY+=YCount){
				if(TopY+YCount>Dp->GetMaxLines())
					YCount=Dp->GetMaxLines()-TopY;
				if(UseLayer<0){
					for(int Layer=0;Layer<Dp->GetLayerNumb();Layer++){
						GUICmdReqSaveTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Phase	=phase;
						RCmd.Layer	=Layer;
						RCmd.TopY	=TopY;
						RCmd.YCount	=YCount;
						GUICmdSendSaveTargetImage	SCmd(GetLayersBase() ,sRoot,sName,page);
						if(RCmd.Send(page ,0,SCmd)==true){
							f->write(SCmd.Data);
						}
					}
				}
				else if(UseLayer<Dp->GetLayerNumb()){
					GUICmdReqSaveTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					RCmd.Phase	=phase;
					RCmd.Layer	=UseLayer;
					RCmd.TopY	=TopY;
					RCmd.YCount	=YCount;
					GUICmdSendSaveTargetImage	SCmd(GetLayersBase() ,sRoot,sName,page);
					if(RCmd.Send(page ,0,SCmd)==true){
						f->write(SCmd.Data);
					}
				}
				if(iShowProcessingWindow==true){
					GetLayersBase()->StepProcessing(page);
				}
			}
		}
	}
	if(iShowProcessingWindow==true){
		GetLayersBase()->CloseProcessingForm ();
	}
	return true;
}
void	SaveImageTargetButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(SaveImageTargetButton_LS,LID_1)/*"FILE"*/,LangSolver.GetString(SaveImageTargetButton_LS,LID_2)/*"Save TargetImage(PIX)"*/,this);
	p->SetMenuNumber(5030);
	Info.AppendList(p);
}
void	SaveImageTargetButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
//===========================================================================================
ThreadSave::ThreadSave(QObject *obj,LayersBase *base,SaveImageTargetButton *parent)
	:QThread(obj),ServiceForLayers(base),Parent(parent)
{
	IBuffer=NULL;
	Saved	=false;
	Terminated	=false;
}
ThreadSave::~ThreadSave(void)
{
	if(IBuffer!=NULL)
		delete[]IBuffer;
	IBuffer=NULL;
}

void	ThreadSave::Allocate(void)
{
	if(IBuffer!=NULL)
		delete[]IBuffer;
	int	LayerNumb=GetLayersBase()->GetMaxLayerNumb();
	IBuffer=new ImageBuffer[GetPhaseNumb()*GetPageNumb()*LayerNumb];
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
				ImageBuffer	*d=GetImageBuffer(phase , page ,Layer);
				d-> Set(page,ImageBufferOther ,GetDotPerLine(page), GetMaxLines(page));
			}
		}
	}
}
ImageBuffer	*ThreadSave::GetImageBuffer(int phase , int page ,int layer)
{
	int	LayerNumb=GetLayerNumb(page);
	return &IBuffer[phase*GetPageNumb()*LayerNumb + page*LayerNumb + layer];
}

bool	ThreadSave::CopyFrom(CmdReqSaveImage::UsageImage TypeOfImage)
{
	if(Saved==true)
		return false;
	int	PhaseNumb=GetPhaseNumb();
	if(GetParamGlobal()->CommonTargetBetweenPhases==true)
		PhaseNumb=1;
	if(GetLayersBase()->IsLocalCamera()==true){
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<GetPageNumb();page++){
				for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
					DataInLayer	*L=GetLayersBase()->GetPageDataPhase(phase)->GetPageData(page)->GetLayerData(Layer);
					ImageBuffer	*s;
					if(TypeOfImage==CmdReqSaveImage::_SaveRawImage && GetParamGlobal()->AllocRawTargetBuffForNGImage==true)
						s=&L->GetRawTargetBuff();
					else if(TypeOfImage==CmdReqSaveImage::_SaveCamImage && GetParamGlobal()->AllocCamTargetBuffer==true)
						s=&L->GetCamTargetBuff();
					else
						s=&L->GetTargetBuff();
					ImageBuffer	*d=GetImageBuffer(phase , page ,Layer);
					*d=*s;
					if(Terminated==true){
						return false;
					}
				}
			}
		}
	}
	else{
		int	YCountBase=100;
		for(int phase=0;phase<PhaseNumb;phase++){
			for(int page=0;page<GetPageNumb();page++){
				int	YCount=YCountBase;
				for(int TopY=0;TopY<GetMaxLines(page);TopY+=YCount){
					if(TopY+YCount>GetMaxLines(page))
						YCount=GetMaxLines(page)-TopY;
					for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
						GUICmdReqSaveTargetImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Phase	=phase;
						RCmd.Layer	=Layer;
						RCmd.TopY	=TopY;
						RCmd.YCount	=YCount;
						GUICmdSendSaveTargetImage	SCmd(GetLayersBase() ,sRoot,sName,page);
						if(RCmd.Send(page ,0,SCmd)==true){
							ImageBuffer	*d=GetImageBuffer(phase , page ,Layer);
							BYTE	*Src=(BYTE *)SCmd.Data.data();
							for(int y=TopY;y<TopY+YCount;y++){
				                memcpy(d->GetY(y),Src,GetDotPerLine(page));
					            Src+=GetDotPerLine(page);
							}
						}
					}
					if(Terminated==true){
						return false;
					}
				}
			}
		}
	}
	Saved=true;
	return true;
}

bool ThreadSave::SaveImage(QString hFileName,CmdReqSaveImage::UsageImage TypeOfImage)
{
	QFile	WFile(hFileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	if(Parent->SaveImageV3(&WFile,false)==false)
		return false;
	/*
	int	PhaseNumb=GetPhaseNumb();
	if(GetParamGlobal()->CommonTargetBetweenPhases==true)
		PhaseNumb=1;
	int	Ver=2;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)PhaseNumb)==false)
		return false;
	if(::Save(&WFile,(int)GetPageNumb())==false)
		return false;
	if(UseLayer<0){
		if(::Save(&WFile,(int)GetLayerNumb(0))==false)
			return false;
	}
	else{
		int	LayerNumb=1;
		if(::Save(&WFile,LayerNumb)==false)
			return false;
	}
	if(::Save(&WFile,(int)GetDotPerLine(-1))==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines(-1))==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	int	YCountBase=100;
	QByteArray    Data;
	Data.resize(YCountBase*GetDotPerLine(-1));

	for(int phase=0;phase<PhaseNumb;phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	YCount=YCountBase;
			for(int TopY=0;TopY<GetMaxLines(page);TopY+=YCount){
				if(TopY+YCount>GetMaxLines(page))
					YCount=GetMaxLines(page)-TopY;
				Data.resize(YCount*GetDotPerLine(page));
				if(UseLayer<0){
					for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
						ImageBuffer	*s=GetImageBuffer(phase , page ,Layer);
						BYTE	*Dest=(BYTE *)Data.data();
						for(int y=TopY;y<TopY+YCount;y++){
							memcpy(Dest,s->GetY(y),GetDotPerLine(page));
							Dest+=GetDotPerLine(page);
						}
						if(WFile.write(Data)!=Data.size()){
							return false;
						}
						if(Terminated==true){
							return false;
						}
					}
				}
				else if(UseLayer<GetLayerNumb(page)){
					ImageBuffer	*s=GetImageBuffer(phase , page ,UseLayer);
					BYTE	*Dest=(BYTE *)Data.data();
					for(int y=TopY;y<TopY+YCount;y++){
						memcpy(Dest,s->GetY(y),GetDotPerLine(page));
						Dest+=GetDotPerLine(page);
					}
					if(WFile.write(Data)!=Data.size()){
						return false;
					}
					if(Terminated==true){
						return false;
					}
				}
			}
		}
	}
	*/
	return true;
}
void  ThreadSave::run()
{
	while(Terminated==false){
		if(Saved==true){
			SaveImage(FileName,CurrentTypeOfImage);
			Saved=false;
		}
		GSleep(100);
	}
}

//===========================================================================================


GUICmdReqSaveTargetImage::GUICmdReqSaveTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	TypeOfImage=CmdReqSaveImage::_SaveTargetImage;
}

bool	GUICmdReqSaveTargetImage::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	BYTE	d;
	if(::Load(f,d)==false)
		return false;
	TypeOfImage=(CmdReqSaveImage::UsageImage)d;
	return true;
}
bool	GUICmdReqSaveTargetImage::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	BYTE	d=(BYTE)TypeOfImage;
	if(::Save(f,d)==false)
		return false;

	return true;
}

void	GUICmdReqSaveTargetImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSaveTargetImage	*SendBack=GetSendBack(GUICmdSendSaveTargetImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	DataInLayer	*L=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		SendBack->Data.resize(YCount*L->GetDotPerLine());

		ImageBuffer	*s;
		if(TypeOfImage==CmdReqSaveImage::_SaveRawImage && GetParamGlobal()->AllocRawTargetBuffForNGImage==true)
			s=&L->GetRawTargetBuff();
		else if(TypeOfImage==CmdReqSaveImage::_SaveCamImage && GetParamGlobal()->AllocCamTargetBuffer==true)
			s=&L->GetCamTargetBuff();
		else
			s=&L->GetTargetBuff();

		BYTE	*Dest=(BYTE *)SendBack->Data.data();
		for(int y=TopY;y<TopY+YCount;y++){
			memcpy(Dest,s->GetY(y),L->GetDotPerLine());
			Dest+=L->GetDotPerLine();
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSaveTargetImage::GUICmdSendSaveTargetImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSaveTargetImage::Load(QIODevice *f)
{
	Data=f->readAll();
	return true;
}
bool	GUICmdSendSaveTargetImage::Save(QIODevice *f)
{
	f->write(Data);
	return true;
}

void	GUICmdSendSaveTargetImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
