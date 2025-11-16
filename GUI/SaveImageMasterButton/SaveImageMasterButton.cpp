/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\SaveImageMasterButton\SaveImageMasterButton.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "SaveImageMasterButtonResource.h"
#include "SaveImageMasterButton.h"
#include <QFileDialog>
#include "XGeneralFunc.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"SaveImageMasterButton";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Save Master Image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqSaveMasterImage (Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdSendSaveMasterImage(Base,QString(sRoot),QString(sName));
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SaveImageMasterButton(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<6)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((SaveImageMasterButton *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((SaveImageMasterButton *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((SaveImageMasterButton *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((SaveImageMasterButton *)Instance)->CFont;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"FileNameForSaving";
	Data[4].Pointer				 =&((SaveImageMasterButton *)Instance)->FileNameForSaving;
	Data[5].Type				 =/**/"int32";
	Data[5].VariableNameWithRoute=/**/"UseLayer";
	Data[5].Pointer				 =&((SaveImageMasterButton *)Instance)->UseLayer;

	return(6);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SaveImageMasterButton.png")));
}

static	bool	MacroSave(GUIFormBase *Instance ,QStringList &Args)
{
	SaveImageMasterButton	*V=dynamic_cast<SaveImageMasterButton *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<1){
		return false;
	}
	QString FileName=Args[0];

	if(FileName.isEmpty()==false){
		return V->SaveImage(FileName);
	}
	return true;
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"Save";
		Functions[ret].ArgName.append(/**/"File path and name");
		Functions[ret].Explain.append(/**/"Save PIX from Master");
		Functions[ret].DLL_ExcuteMacro	=MacroSave;
		ret++;
	}
	return ret;
}

//==================================================================================================
SaveImageMasterButton::SaveImageMasterButton(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"SaveMaster");
	Msg		=/**/"Save Master";
	UseLayer=-1;

	resize(80,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

SaveImageMasterButton::~SaveImageMasterButton(void)
{
}

void	SaveImageMasterButton::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	SaveImageMasterButton::ResizeAction()
{
	Button.resize(width(),height());
}

void SaveImageMasterButton::SlotClicked (bool checked)
{
	QString	FileName;

	if(FileNameForSaving.isEmpty()==true){
		FileName=GetLayersBase()->LGetSaveFileName (this
												, LangSolver.GetString(SaveImageMasterButton_LS,LID_0)/*"Save Master Image file"*/
												,QString()
												,QString(/**/"ImageFile(*.pix);;AllFile(*.*)")) ;
	}
	else{
		FileName=FileNameForSaving;
	}
	if(FileName.isEmpty()==true)
		return;
	SaveImage(FileName);
}

bool SaveImageMasterButton::SaveImage(QString FileName)
{
	QFile	WFile(FileName);
	if(WFile.open(QIODevice::WriteOnly)==false)
		return false;

	int	Ver=2;
	if(::Save(&WFile,Ver)==false)
		return false;
	if(::Save(&WFile,(int)GetPhaseNumb())==false)
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
	if(::Save(&WFile,(int)GetDotPerLine(0))==false)
		return false;
	if(::Save(&WFile,(int)GetMaxLines(0))==false)
		return false;
	if(::Save(&WFile,(int)100)==false)
		return false;

	int	YCountBase=100;

	GetLayersBase()->ShowProcessingForm (LangSolver.GetString(SaveImageMasterButton_LS,LID_3)/*"Save PIX image from master buffer"*/);
	GetLayersBase()->SetMaxProcessing(GetPhaseNumb()*((GetMaxLines(0)+YCountBase-1)/YCountBase));
	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int page=0;page<GetPageNumb();page++){
			int	YCount=YCountBase;
			for(int TopY=0;TopY<GetMaxLines(page);TopY+=YCount){
				if(TopY+YCount>GetMaxLines(page)){
					YCount=GetMaxLines(page)-TopY;
				}
				if(UseLayer<0){
					for(int Layer=0;Layer<GetLayerNumb(page);Layer++){
						GUICmdReqSaveMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
						RCmd.Phase	=phase;
						RCmd.Layer	=Layer;
						RCmd.TopY	=TopY;
						RCmd.YCount	=YCount;
						GUICmdSendSaveMasterImage	SCmd(GetLayersBase() ,sRoot,sName,page);
						if(RCmd.Send(page ,0,SCmd)==true){
							WFile.write(SCmd.Data);
						}
					}
				}
				else if(UseLayer<GetLayerNumb(page)){
					GUICmdReqSaveMasterImage	RCmd(GetLayersBase() ,sRoot,sName,page);
					RCmd.Phase	=phase;
					RCmd.Layer	=UseLayer;
					RCmd.TopY	=TopY;
					RCmd.YCount	=YCount;
					GUICmdSendSaveMasterImage	SCmd(GetLayersBase() ,sRoot,sName,page);
					if(RCmd.Send(page ,0,SCmd)==true){
						WFile.write(SCmd.Data);
					}
				}
				GetLayersBase()->StepProcessing(page);
			}		
		}
	}
	GetLayersBase()->CloseProcessingForm ();
	return true;
}
void	SaveImageMasterButton::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,LangSolver.GetString(SaveImageMasterButton_LS,LID_1)/*"FILE"*/,LangSolver.GetString(SaveImageMasterButton_LS,LID_2)/*"Save MasterImage(PIX)"*/,this);
	p->SetMenuNumber(5010);
	Info.AppendList(p);
}
void	SaveImageMasterButton::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}
GUICmdReqSaveMasterImage::GUICmdReqSaveMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqSaveMasterImage::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	if(::Load(f,TopY)==false)
		return false;
	if(::Load(f,YCount)==false)
		return false;
	if(::Load(f,Layer)==false)
		return false;
	return true;
}
bool	GUICmdReqSaveMasterImage::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	if(::Save(f,TopY)==false)
		return false;
	if(::Save(f,YCount)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	return true;
}

void	GUICmdReqSaveMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendSaveMasterImage	*SendBack=GetSendBack(GUICmdSendSaveMasterImage,GetLayersBase(),EmitterRoot,EmitterName ,localPage);

	DataInLayer	*L=GetLayersBase()->GetPageDataPhase(Phase)->GetPageData(localPage)->GetLayerData(Layer);
	if(L!=NULL){
		SendBack->Data.resize(YCount*L->GetDotPerLine());
		BYTE	*Dest=(BYTE *)SendBack->Data.data();
		for(int y=TopY;y<TopY+YCount;y++){
			memcpy(Dest,L->GetMasterBuff().GetY(y),L->GetDotPerLine());
			Dest+=L->GetDotPerLine();
		}
	}
	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendSaveMasterImage::GUICmdSendSaveMasterImage(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdSendSaveMasterImage::Load(QIODevice *f)
{
	Data=f->readAll();
	return true;
}
bool	GUICmdSendSaveMasterImage::Save(QIODevice *f)
{
	f->write(Data);
	return true;
}

void	GUICmdSendSaveMasterImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}
