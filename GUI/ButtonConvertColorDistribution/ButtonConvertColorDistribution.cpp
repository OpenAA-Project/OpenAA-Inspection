/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonConvertColorDistribution\ButtonConvertColorDistribution.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ButtonConvertColorDistribution.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "XDataAlgorithm.h"
#include "XAlgorithmBase.h"
#include "XDoubleClass.h"
#include "swap.h"
#include <QIcon>
#include <QPixmap>
#include <QStringList>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ConvertColorDistribution";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to convert Color Distribution");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdConvertColorDistribution		(Base,sRoot,sName);
	//(*Base)=new GUICmdReqButtonClearMasterInfoPhase(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonConvertColorDistribution(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ButtonConvertColorDistribution *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonConvertColorDistribution *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonConvertColorDistribution *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonConvertColorDistribution *)Instance)->CFont;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ChangeMasterImage";
	Data[4].Pointer				 =&((ButtonConvertColorDistribution *)Instance)->ChangeMasterImage;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonConvertColorDistribution.png")));
}

//==================================================================================================
ButtonConvertColorDistribution::ButtonConvertColorDistribution(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonConvertColorDistribution");
	Msg=/**/"Convert Color";
	ChangeMasterImage=true;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonConvertColorDistribution::~ButtonConvertColorDistribution(void)
{
}

void	ButtonConvertColorDistribution::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	Button.setChecked(GetLayersBase()->IsEnableFilter());
	ResizeAction();
}

void	ButtonConvertColorDistribution::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonConvertColorDistribution::SlotClicked (bool checked)
{
	for(int page=0;page<GetPageNumb();page++){
		int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
		GUICmdConvertColorDistribution	RCmd(GetLayersBase(),sRoot,sName,globalPage);
		RCmd.ChangeMasterImage=ChangeMasterImage;
		RCmd.Send(NULL,globalPage,0);
	}
}

//============================================================================================

GUICmdConvertColorDistribution::GUICmdConvertColorDistribution(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}

bool	GUICmdConvertColorDistribution::Load(QIODevice *f)
{
	if(::Load(f,ChangeMasterImage)==false)	return false;
	return true;
}
bool	GUICmdConvertColorDistribution::Save(QIODevice *f)
{
	if(::Save(f,ChangeMasterImage)==false)	return false;
	return true;
}

void	GUICmdConvertColorDistribution::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{

	DataInPage *Pg=GetLayersBase()->GetPageData(localPage);
	ImagePointerContainer SrcImages;
	ImagePointerContainer DstImages;
	if(ChangeMasterImage==true){
		Pg->GetMasterImages		(DstImages);
		Pg->GetTargetImages		(SrcImages);
	}
	else{
		Pg->GetTargetImages		(DstImages);
		Pg->GetMasterImages		(SrcImages);
	}
	ConstMapBufferListContainer MaskMap;
	if(Pg->GetReflectionMap(_Reflection_Mask,MaskMap,NULL,NULL)==true){
		ConstMapBuffer Map;
		MaskMap.BindOr(Map);
		DoubleList	SrcAvr;
		DoubleList	SrcV;
		DoubleList	DstAvr;
		DoubleList	DstV;
		const BYTE	**MaskBitmap=Map.GetBitMap();

		FlexArea	MaskArea;
		MaskArea.BuildFromRaster((uchar **)MaskBitmap ,Map.GetXByte() ,Map.GetYLen(),0,0);

		int	XSize=100;
		int	YSize=100;
		int	XNum=(MaskArea.GetWidth ()+XSize-1)/XSize;
		int	YNum=(MaskArea.GetHeight()+YSize-1)/YSize;

		for(int yn=0;yn<YNum;yn++){
			for(int xn=0;xn<XNum;xn++){
				int	X1=xn*XSize+MaskArea.GetMinX();
				int	Y1=yn*YSize+MaskArea.GetMinY();
				int	X2=X1+XSize;
				int	Y2=Y1+YSize;
				int	XMergin=XSize+200;
				int	YMergin=YSize+300;
				MakeAvrV(SrcImages,MaskBitmap,SrcAvr,SrcV,X1-XMergin,Y1-YMergin,X2+XMergin,Y2+YMergin,true);
				MakeAvrV(DstImages,MaskBitmap,DstAvr,DstV,X1-XMergin,Y1-YMergin,X2+XMergin,Y2+YMergin,true);

				DoubleList	DifV  =SrcV/DstV;
				Convert(DstImages,MaskBitmap,SrcAvr,DstAvr,DifV,X1,Y1,X2,Y2);
			}
		}
	}
}

void	GUICmdConvertColorDistribution::MakeAvrV(const ImagePointerContainer &Images 
												,const BYTE	**MaskBitmap,DoubleList &Avr,DoubleList &V
												,int X1,int Y1,int X2,int Y2
												,bool SmoothMode)
{
	Avr.RemoveAll();
	V.RemoveAll();
	for(ImagePointerList *L=Images.GetFirst();L!=NULL;L=L->GetNext()){
		ImageBuffer *Img=L->GetImage();
		double	AvrC=0;
		double	VC=0;
		int		XLen=Img->GetWidth();
		int		YLen=Img->GetHeight();
		int		Numb=0;
		int		W=2;
		int		WN=2*W+1;
		for(int y=max(Y1,W);y<(YLen-W) && y<Y2;y++){
			int	iAvrC=0;
			int	iVC=0;
			BYTE	*d[100];
			BYTE	*s[100];
			for(int i=0;i<WN;i++){
				d[i]=Img->GetY(y-(i-W));
				s[i]=(BYTE *)MaskBitmap[y-(i-W)];
			}
			for(int x=max(X1,W);x<(XLen-W) &&x<X2;x++){
				int	C=0;
				int	tn=0;
				for(int i=0;i<WN;i++){
					int	iW=i-W;
					for(int j=0;j<WN;j++){
						int	jW=j-W;
						if(GetBmpBitOnY(s[i],x-jW)!=0){
							C=(d[i])[x-jW];
							tn++;
						}
					}
				}
				if(tn>0){
					C/=tn;
					iAvrC+=C;
					iVC	 +=C*C;
					Numb++;
				}
			}
			AvrC+=iAvrC;
			VC  +=iVC;
		}
		if(Numb!=0){
			double	AvrM=AvrC/Numb;
			Avr.Add(AvrM);
			double	Vm=(VC-AvrM*AvrM*Numb)/Numb;
			V.Add(sqrt(Vm));
		}
	}
}

void	GUICmdConvertColorDistribution::Convert(const ImagePointerContainer &Images ,const BYTE	**MaskBitmap
												,DoubleList &SrcAvr,DoubleList &DstAvr,DoubleList &DifV
												,int X1,int Y1,int X2,int Y2)
{
	DoubleList	DifAvr=SrcAvr-DstAvr;
	int	n=0;
	for(ImagePointerList *L=Images.GetFirst();L!=NULL;L=L->GetNext(),n++){
		ImageBuffer *Img=L->GetImage();
		double	AvrS=SrcAvr[n];
		double	AvrD=DstAvr[n];
		double	Z	=DifV[n];
		int		XLen=Img->GetWidth();
		int		YLen=Img->GetHeight();
		for(int y=Y1;y<YLen && y<Y2;y++){
			BYTE	*d=Img->GetY(y);
			const	BYTE	*s=MaskBitmap[y];
			for(int x=X1;x<XLen && x<X2;x++){
				if(GetBmpBitOnY(s,x)!=0){
					d[x]=Clipping((int)(AvrS+(d[x]-AvrD)*Z),0,255);
				}
			}
		}
	}
}

