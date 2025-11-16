/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShiftImage\ButtonShiftImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonShiftImage.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "ShiftImageDialog.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ShiftImage";

static	bool	MacroShiftX(GUIFormBase *Instance ,QStringList &Args);
static	bool	MacroShiftY(GUIFormBase *Instance ,QStringList &Args);

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to shift image");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqShiftImage	(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonShiftImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonShiftImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonShiftImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonShiftImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonShiftImage *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShiftImage.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=0;

	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShiftY";
		Functions[ret].ArgName.append(/**/"MasterImage(true/false)");
		Functions[ret].ArgName.append(/**/"TargetImage(true/false)");
		Functions[ret].ArgName.append(/**/"X1");
		Functions[ret].ArgName.append(/**/"X2");
		Functions[ret].ArgName.append(/**/"ShiftY");
		Functions[ret].Explain.append(/**/"Shift vertial band");
		Functions[ret].DLL_ExcuteMacro	=MacroShiftY;
		ret++;
	}
	if(MaxBuffer>ret){
		Functions[ret].FuncName	=/**/"ShiftX";
		Functions[ret].ArgName.append(/**/"MasterImage(true/false)");
		Functions[ret].ArgName.append(/**/"TargetImage(true/false)");
		Functions[ret].ArgName.append(/**/"Y1");
		Functions[ret].ArgName.append(/**/"Y2");
		Functions[ret].ArgName.append(/**/"ShiftX");
		Functions[ret].Explain.append(/**/"Shift horizontal band");
		Functions[ret].DLL_ExcuteMacro	=MacroShiftX;
		ret++;
	}
	return ret;
}


static	bool	MacroShiftY(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonShiftImage	*V=dynamic_cast<ButtonShiftImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	bool	ok;
	bool	ModeMasterImage=false;
	bool	ModeTargetImage=false;
	if(Args[0].toUpper()==/**/"TRUE"){
		ModeMasterImage=true;
	}
	if(Args[1].toUpper()==/**/"TRUE"){
		ModeTargetImage=true;
	}

	int	X1=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	X2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	ShiftY=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExeShiftY(ModeMasterImage,ModeTargetImage,X1,X2,ShiftY);

	return true;
}

static	bool	MacroShiftX(GUIFormBase *Instance ,QStringList &Args)
{
	ButtonShiftImage	*V=dynamic_cast<ButtonShiftImage *>(Instance);
	if(V==NULL){
		return false;
	}
	if(Args.count()<3){
		return false;
	}
	bool	ModeMasterImage=false;
	bool	ModeTargetImage=false;
	if(Args[0].toUpper()==/**/"TRUE"){
		ModeMasterImage=true;
	}
	if(Args[1].toUpper()==/**/"TRUE"){
		ModeTargetImage=true;
	}
	bool	ok;
	int	Y1=Args[2].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	Y2=Args[3].toInt(&ok);
	if(ok==false){
		return false;
	}
	int	ShiftX=Args[4].toInt(&ok);
	if(ok==false){
		return false;
	}
	V->ExeShiftX(ModeMasterImage,ModeTargetImage,Y1,Y2,ShiftX);

	return true;
}


//==================================================================================================
ButtonShiftImage::ButtonShiftImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Msg=/**/"Shift Image";

	setObjectName(QString::fromUtf8(/**/"ButtonShiftImageObj"));
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonShiftImage");
	Button.setCheckable(false);

	resize(100,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonShiftImage::~ButtonShiftImage(void)
{
}
void	ButtonShiftImage::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonShiftImage::ResizeAction()
{
	Button.resize(width(),height());
}


void ButtonShiftImage::SlotClicked (bool checked)
{
	ShiftImageDialog	D(GetLayersBase());
	int	Ret=D.exec();
	if(Ret==1){
		ExeShiftY(D.ModeMasterImage,D.ModeTargetImage
				 ,D.StartPos,D.EndPos,D.ShiftN);
		BroadcastRepaintAll();
	}
	else if(Ret==2){
		ExeShiftX(D.ModeMasterImage,D.ModeTargetImage
				 ,D.StartPos,D.EndPos,D.ShiftN);
		BroadcastRepaintAll();
	}
}
	
void	ButtonShiftImage::ExeShiftY(bool ModeMasterImage,bool ModeTargetImage
									,int StartPos,int EndPos,int ShiftY)
{
	int X1,Y1;
	int X2,Y2;
	int	Page1=GetLayersBase()->GetLocalMatrixFromGlobal(StartPos ,0 ,X1 ,Y1);
	int	Page2=GetLayersBase()->GetLocalMatrixFromGlobal(EndPos ,0 ,X2 ,Y2);
	if(0<=Page1 && 0<=Page2 && Page1==Page2){
		int	Page=Page1;
		GUICmdReqShiftImage	RCmd(GetLayersBase(),sRoot,sName,Page);
		RCmd.ModeY		=true;
		RCmd.StartPos	=X1;
		RCmd.EndPos		=X2;
		RCmd.ShiftN		=ShiftY;
		RCmd.ModeMasterImage	=ModeMasterImage;
		RCmd.ModeTargetImage	=ModeTargetImage;
		RCmd.Send(NULL,Page,0);
	}
}
	
void	ButtonShiftImage::ExeShiftX(bool ModeMasterImage,bool ModeTargetImage
									,int StartPos,int EndPos,int ShiftX)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdReqShiftImage	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.ModeY		=false;
		RCmd.StartPos	=StartPos	;
		RCmd.EndPos		=EndPos	;
		RCmd.ShiftN		=ShiftX	;
		RCmd.ModeMasterImage	=ModeMasterImage;
		RCmd.ModeTargetImage	=ModeTargetImage;
		RCmd.Send(NULL,globalPage,0);
	}
}

//===============================================================
GUICmdReqShiftImage::GUICmdReqShiftImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdReqShiftImage::Load(QIODevice *f)
{
	if(::Load(f,ModeY)==false)				return false;
	if(::Load(f,ModeMasterImage)==false)	return false;
	if(::Load(f,ModeTargetImage)==false)	return false;
	if(::Load(f,StartPos)==false)			return false;
	if(::Load(f,EndPos)==false)				return false;
	if(::Load(f,ShiftN)==false)				return false;

	return true;
}
bool	GUICmdReqShiftImage::Save(QIODevice *f)
{
	if(::Save(f,ModeY)==false)				return false;
	if(::Save(f,ModeMasterImage)==false)	return false;
	if(::Save(f,ModeTargetImage)==false)	return false;
	if(::Save(f,StartPos)==false)			return false;
	if(::Save(f,EndPos)==false)				return false;
	if(::Save(f,ShiftN)==false)				return false;

	return true;
}

void	GUICmdReqShiftImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	DataInPage	*Dp=GetLayersBase()->GetPageData(localPage);
	if(Dp!=NULL){
		for(int Layer=0;Layer<Dp->GetLayerNumb();Layer++){
			DataInLayer	*Lp=Dp->GetLayerData(Layer);
			if(ModeMasterImage==true){
				ImageBuffer	*P=Lp->GetMasterBuffPointer();
				Shift(Lp,P);
			}
			if(ModeTargetImage==true){
				ImageBuffer	*P=Lp->GetTargetBuffPointer();
				Shift(Lp,P);
			}
		}
	}
}

void	GUICmdReqShiftImage::Shift(DataInLayer	*Lp,ImageBuffer *P)
{
	if(ModeY==true){
		if(ShiftN<0){
			int	YN=Lp->GetMaxLines()+ShiftN;
			for(int y=0;y<YN;y++){
				BYTE	*D=P->GetY(y);
				BYTE	*S=P->GetY(y-ShiftN);
				for(int x=StartPos;x<=EndPos;x++){
					D[x]=S[x];
				}
			}
		}
		else if(ShiftN>0){
			int	YN=Lp->GetMaxLines()-ShiftN;
			for(int y=0;y<YN;y++){
				BYTE	*S=P->GetY(YN-y-1);
				BYTE	*D=P->GetY(YN-y+ShiftN-1);
				for(int x=StartPos;x<=EndPos;x++){
					D[x]=S[x];
				}
			}
		}
	}
	else{
		if(ShiftN<0){
			int	XN=Lp->GetDotPerLine()+ShiftN;
			for(int y=StartPos;y<=EndPos;y++){
				BYTE	*D=P->GetY(y);
				for(int x=0;x<XN;x++){						
					D[x]=D[x-ShiftN];
				}
			}
		}
		else if(ShiftN>0){
			int	XN=Lp->GetDotPerLine()-ShiftN;
			for(int y=StartPos;y<=EndPos;y++){
				BYTE	*D=P->GetY(y);
				for(int x=0;x<XN;x++){						
					D[XN-x-1]=D[XN-x+ShiftN-1];
				}
			}
		}
	}
}

