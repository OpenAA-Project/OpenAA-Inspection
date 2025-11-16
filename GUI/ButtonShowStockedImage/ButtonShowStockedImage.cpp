/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonShowStockedImage\ButtonShowStockedImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "ButtonShowStockedImage.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "ShowListDialog.h"
#include "XGUIDLL.h"
#include "XMacroFunction.h"
#include "XCriticalFunc.h"
#include "XDateTime.h"
#include "XLogOutImage.h"

static	const	char	*sRoot=/**/"Button";
static	const	char	*sName=/**/"ShowStockedImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show stocked images for debug");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdPushImage	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonShowStockedImage(Base,parent));
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
	Data[0].Pointer				 =&((ButtonShowStockedImage *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonShowStockedImage *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonShowStockedImage *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonShowStockedImage *)Instance)->CFont;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"AllocatedCount";
	Data[4].Pointer				 =&((ButtonShowStockedImage *)Instance)->AllocatedCount;


	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonShowStockedImage.png")));
}

//==================================================================================================
ImageBufferWithInfo::ImageBufferWithInfo(LayersBase *Base)
{
	Set(0,ImageBufferOther ,Base->GetDotPerLine(Page), Base->GetMaxLines(Page));

	Phase	=0;
	Page	=0;
	Layer	=0;
	Mastered=false;
	ID		=0;
	ComputerMilisec=0;
}
ImageBufferWithInfo &ImageBufferWithInfo::operator=(ImageBuffer &src)
{
	ImageBuffer::operator=(src);
	return *this;
}
int	ImageBufferWithInfoPointer::Compare(ImageBufferWithInfoPointer &src)
{
	return Point->ID - src.Point->ID;
}
int	ImageBufferWithInfoPointerContainer::Compare(ImageBufferWithInfoPointerContainer &src)
{
	ImageBufferWithInfoPointer	*Fd=NPListPack<ImageBufferWithInfoPointer>::GetFirst();
	ImageBufferWithInfoPointer	*Fs=src.NPListPack<ImageBufferWithInfoPointer>::GetFirst();
	if(Fs!=NULL && Fd!=NULL){
		return Fd->Point->ID-Fs->Point->ID;
	}
	return 0;
}

ButtonShowStockedImage::ButtonShowStockedImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonShowStockedImage");
	Msg=/**/"Show stocked image";
	CharColor	=Qt::black;
	BackColor	=Qt::lightGray;
	AllocatedCount	=20;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonShowStockedImage::~ButtonShowStockedImage(void)
{
}

void	ButtonShowStockedImage::ReadyParam(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();

	StockImages.RemoveAll();
	for(int i=0;i<AllocatedCount;i++){
		ImageBufferWithInfo	*L=new ImageBufferWithInfo(GetLayersBase());
		StockImages.AppendList(L);
	}
}

void	ButtonShowStockedImage::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonShowStockedImage::SlotClicked (bool checked)
{
	ShowListDialog	D(this,GetLayersBase());
	D.exec();
}

void	ButtonShowStockedImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdPushImage	*CmdPushImageVar=dynamic_cast<CmdPushImage *>(packet);
	if(CmdPushImageVar!=NULL){
		if(CmdPushImageVar->Page>=0){
			int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),CmdPushImageVar->Page);
			GUICmdPushImage	RCmd(GetLayersBase(),sRoot,sName,globalPage);
			RCmd.Phase	=CmdPushImageVar->Phase;
			RCmd.Page	=CmdPushImageVar->Page;
			RCmd.Layer	=CmdPushImageVar->Layer;
			RCmd.Send(NULL,globalPage,0);
		}
		else{
			for(int page=0;page<GetPageNumb();page++){
				int	globalPage=GetParamComm()->GetGlobalPageFromLocal(*GetParamGlobal(),page);
				GUICmdPushImage	RCmd(GetLayersBase(),sRoot,sName,globalPage);
				RCmd.Phase	=CmdPushImageVar->Phase;
				RCmd.Page	=CmdPushImageVar->Page;
				RCmd.Layer	=CmdPushImageVar->Layer;
				RCmd.Send(NULL,globalPage,0);
			}
		}
		return;
	}
}

void	ButtonShowStockedImage::PushImageHPL(int phase ,int page ,int layer ,bool Mastered)
{
	XDateTime	DateTime=XDateTime::currentDateTime();
	int	ID=GetMaxID()+1;
	DWORD	ComputerMilisec=::GetComputerMiliSec();

	ImageBufferWithInfo	*d=GetOldBuffer();
	ImageBuffer	*s=GetImage(phase ,page ,layer ,Mastered);
	if(d!=NULL && s!=NULL){
		*d=*s;
		d->DateTime=DateTime;
		d->ID=ID;
		d->ComputerMilisec=ComputerMilisec;
	}
}
void	ButtonShowStockedImage::PushImagePL (int page ,int layer ,bool Mastered)
{
	XDateTime	DateTime=XDateTime::currentDateTime();
	int	ID=GetMaxID()+1;
	DWORD	ComputerMilisec=::GetComputerMiliSec();

	for(int phase=0;phase<GetPhaseNumb();phase++){
		ImageBufferWithInfo	*d=GetOldBuffer();
		ImageBuffer	*s=GetImage(phase ,page ,layer ,Mastered);
		if(d!=NULL && s!=NULL){
			*d=*s;
			d->DateTime=DateTime;
			d->ID=ID;
			d->ComputerMilisec=ComputerMilisec;
		}
	}
}
void	ButtonShowStockedImage::PushImageHP (int phase ,int page ,bool Mastered)
{
	XDateTime	DateTime=XDateTime::currentDateTime();
	int	ID=GetMaxID()+1;
	DWORD	ComputerMilisec=::GetComputerMiliSec();

	for(int layer=0;layer<GetLayerNumb(page);layer++){
		ImageBufferWithInfo	*d=GetOldBuffer();
		ImageBuffer	*s=GetImage(phase ,page ,layer ,Mastered);
		if(d!=NULL && s!=NULL){
			*d=*s;
			d->DateTime=DateTime;
			d->ID=ID;
			d->ComputerMilisec=ComputerMilisec;
		}
	}
}
void	ButtonShowStockedImage::PushImageP(int page ,bool Mastered)
{
	XDateTime	DateTime=XDateTime::currentDateTime();
	int	ID=GetMaxID()+1;
	DWORD	ComputerMilisec=::GetComputerMiliSec();

	for(int phase=0;phase<GetPhaseNumb();phase++){
		for(int layer=0;layer<GetLayerNumb(page);layer++){
			ImageBufferWithInfo	*d=GetOldBuffer();
			ImageBuffer	*s=GetImage(phase ,page ,layer ,Mastered);
			if(d!=NULL && s!=NULL){
				*d=*s;
				d->DateTime=DateTime;
				d->ID=ID;
				d->ComputerMilisec=ComputerMilisec;
			}
		}
	}
}
ImageBufferWithInfo	*ButtonShowStockedImage::GetOldBuffer(void)
{
	int	OldID=99999999;
	ImageBufferWithInfo	*OldBuff=NULL;
	for(ImageBufferWithInfo *L=StockImages.GetFirst();L!=NULL;L=L->GetNext()){
		if(OldID>L->ID){
			OldID=L->ID;
			OldBuff=L;
		}
	}
	return OldBuff;
}
ImageBuffer	*ButtonShowStockedImage::GetImage(int phase ,int page ,int layer ,bool Mastered)
{
	PageDataInOnePhase	*H=GetLayersBase()->GetPageDataPhase(phase);
	if(H==NULL)
		return NULL;
	DataInPage	*P=H->GetPageData(page);
	if(P==NULL)
		return NULL;
	DataInLayer	*L=P->GetLayerData(layer);
	if(L==NULL)
		return NULL;
	if(Mastered==true)
		return &L->GetMasterBuff();
	else
		return &L->GetTargetBuff();
}

int		ButtonShowStockedImage::GetMaxID(void)
{
	int	MaxID=0;
	for(ImageBufferWithInfo *L=StockImages.GetFirst();L!=NULL;L=L->GetNext()){
		if(MaxID<L->ID){
			MaxID=L->ID;
		}
	}
	return MaxID;
}

void	ButtonShowStockedImage::MakeList(NPListPack<ImageBufferWithInfoPointerContainer> &List)
{
	for(int ID=GetMaxID();ID>0;ID--){
		ImageBufferWithInfoPointerContainer	*H=new ImageBufferWithInfoPointerContainer();
		for(ImageBufferWithInfo *L=StockImages.GetFirst();L!=NULL;L=L->GetNext()){
			if(ID==L->ID){
				ImageBufferWithInfoPointer	*k=new ImageBufferWithInfoPointer(L);
				H->AppendList(k);
			}
		}
		if(H->GetCount()>0){
			List.AppendList(H);
		}
		else{
			delete	H;
			break;
		}
	}
}
//==================================================================================================
GUICmdPushImage::GUICmdPushImage(LayersBase *Base ,const QString &emitterRoot ,const QString &emitterName,int globalPage)
:GUICmdPacketBase(Base,emitterRoot,emitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdPushImage::Load(QIODevice *f)
{
	if(::Load(f,Phase	)==false)	return false;
	if(::Load(f,Page	)==false)	return false;
	if(::Load(f,Layer	)==false)	return false;
	if(::Load(f,Mastered)==false)	return false;
	return true;
}
bool	GUICmdPushImage::Save(QIODevice *f)
{
	if(::Save(f,Phase	)==false)	return false;
	if(::Save(f,Page	)==false)	return false;
	if(::Save(f,Layer	)==false)	return false;
	if(::Save(f,Mastered)==false)	return false;
	return true;
}

void	GUICmdPushImage::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	if((Page<0 && localPage==0) || Page>=0){
		CmdPushImage	RCmd(GetLayersBase());
		RCmd.Phase		=Phase;
		RCmd.Page		=Page;
		RCmd.Layer		=Layer;
		RCmd.Mastered	=Mastered;
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"ShowStockedImage",/**/"");
		if(f!=NULL){
			f->TransmitDirectly(&RCmd);
		}
	}
}
