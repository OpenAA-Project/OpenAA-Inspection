#include "MakeShadingResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\MakeShading\MakeShading.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "MakeShading.h"
#include "XGeneralFunc.h"
#include <QIcon>
#include <QPixmap>
#include "XDataInLayer.h"
#include "FilterLineShading.h"
#include "MakeShadingProcessForm.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"MakeShading";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to make shading table");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdMakeShadingPushAndClearFilter	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdMakeShadingPopFilter			(Base,QString(sRoot),QString(sName));
	(*Base)=new	GUICmdMakeShadingRegist				(Base,QString(sRoot),QString(sName));
	(*Base)=new	GUICmdReqMakeShadingInfo			(Base,QString(sRoot),QString(sName));
	(*Base)=new	GUICmdAckMakeShadingInfo			(Base,QString(sRoot),QString(sName));
	(*Base)=new	GUICmdSetMakeShadingInfo			(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new MakeShading(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}
DEFFUNCEX	void	DLL_AssociateGUI(RootNameListContainer &List)
{
	List.Add(/**/"Camera",/**/"ChangeQuickProperty");
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((MakeShading *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((MakeShading *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((MakeShading *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((MakeShading *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/MakeShading.png")));
}

//==================================================================================================


MakeShading::MakeShading(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"MakeShading");
	Msg								=/**/"Make Shading";
	Window							=NULL;
	LineShadingData					=NULL;
	MakeShadingInfoStructDimInPage	=NULL;

	resize(60,25);
	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

MakeShading::~MakeShading(void)
{
	delete	Window;
	Window=NULL;
	if(LineShadingData!=NULL){
		delete	[]LineShadingData;
		LineShadingData=NULL;
	}
	if(MakeShadingInfoStructDimInPage!=NULL){
		delete	[]MakeShadingInfoStructDimInPage;
		MakeShadingInfoStructDimInPage=NULL;
	}
}

void	MakeShading::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
	Reallocate(GetPhaseNumb(), GetPageNumb(),GetLayersBase()->GetMaxLayerNumb());
}
bool	MakeShading::Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)
{
	if(LineShadingData!=NULL){
		delete	[]LineShadingData;
		LineShadingData=NULL;
	}
	LineShadingData=new QByteArray[newPageNumb];
	return true;
}
void	MakeShading::ResizeAction()
{
	Button.resize(width(),height());
}

void MakeShading::SlotClicked (bool checked)
{
	if(Window!=NULL){
		delete	Window;
	}
	if(MakeShadingInfoStructDimInPage!=NULL){
		delete	[]MakeShadingInfoStructDimInPage;
	}
	MakeShadingInfoStructDimInPage=new MakeShadingInfoStruct[GetPageNumb()];
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqMakeShadingInfo	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		GUICmdAckMakeShadingInfo	ACmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		if(RCmd.Send(GlobalPage,0,ACmd)==true){
			MakeShadingInfoStructDimInPage[page]=ACmd.MakeShadingInfoStructData;
		}
	}

	Window=new MakeShadingProcessForm(GetLayersBase(),this);
	Window->show();
}


void	MakeShading::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1,"Setting"
										,"Make Shading"
										,this);
	p->SetMenuNumber(288);
	Info.AppendList(p);
}
void	MakeShading::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}

void	MakeShading::PushAndClearFilter(void)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeShadingPushAndClearFilter	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
}
void	MakeShading::PopFilter(void)
{
	for(int page=0;page<GetLayersBase()->GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdMakeShadingPopFilter	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
		RCmd.Send(NULL,GlobalPage,0);
	}
}
void	MakeShading::RegistShading(int page,FlexArea &ShadingArea ,double FValue[3])
{
	int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
	GUICmdMakeShadingRegist	RCmd(GetLayersBase(),QString(sRoot),QString(sName),GlobalPage);
	DataInPage	*pdata=GetLayersBase()->GetPageData(page);
	FlexArea	A=ShadingArea;
	pdata->ClipMoveAreaFromGlobal(A);
	RCmd.ShadingArea=A;

	for(int i=0;i<3;i++){
		RCmd.FValue[i]=FValue[i];
	}
	RCmd.MinX=MakeShadingInfoStructDimInPage[page].MinX;
	RCmd.MaxX=MakeShadingInfoStructDimInPage[page].MaxX;
	RCmd.Send(NULL,GlobalPage,0);
}

//================================================================================================

GUICmdMakeShadingPushAndClearFilter::GUICmdMakeShadingPushAndClearFilter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMakeShadingPushAndClearFilter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	QBuffer	LineShadingBuff;
	LineShadingBuff.open(QIODevice::ReadWrite);

	FilterInstanceContainer	*FilterInst=GetLayersBase()->GetCurrentPageDataPhase()->GetFilterContainer(localPage);
	for(FilterInstanceList *F=FilterInst->GetFirst();F!=NULL;F=F->GetNext()){
		if(F->GetFilterName()==/**/"LineShading"){
			F->Save(&LineShadingBuff);
			CmdFilterLineShadingClear	Cmd(GetLayersBase());
			F->TransmitDirectly(&Cmd);
		}
		else{
			F->SetEnabled(false);
		}
	}
	MakeShading	*f=(MakeShading	*)GetLayersBase()->FindByName(/**/"Button",/**/"MakeShading",/**/"");
	if(f!=NULL){
		f->LineShadingData[localPage]=LineShadingBuff.buffer();
	}
}

GUICmdMakeShadingPopFilter::GUICmdMakeShadingPopFilter(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}

void	GUICmdMakeShadingPopFilter::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	MakeShading	*f=(MakeShading	*)GetLayersBase()->FindByName(/**/"Button",/**/"MakeShading",/**/"");
	if(f!=NULL){
		QBuffer	LineShadingBuff(&f->LineShadingData[localPage]);

		LineShadingBuff.open(QIODevice::ReadWrite);

		FilterInstanceContainer	*FilterInst=GetLayersBase()->GetCurrentPageDataPhase()->GetFilterContainer(localPage);
		for(FilterInstanceList *F=FilterInst->GetFirst();F!=NULL;F=F->GetNext()){
			if(F->GetFilterName()==/**/"LineShading"){
				F->Load(&LineShadingBuff);
			}
			else{
				F->SetEnabled(true);
			}
		}
	}
}

GUICmdMakeShadingRegist::GUICmdMakeShadingRegist(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdMakeShadingRegist::Load(QIODevice *f)
{
	if(ShadingArea.Load(f)==false){
		return false;
	}
	if(f->read((char *)FValue,sizeof(FValue))!=sizeof(FValue)){
		return false;
	}
	if(::Load(f,MinX)==false)
		return false;
	if(::Load(f,MaxX)==false)
		return false;
	return true;
}
bool	GUICmdMakeShadingRegist::Save(QIODevice *f)
{
	if(ShadingArea.Save(f)==false){
		return false;
	}
	if(f->write((const char *)FValue,sizeof(FValue))!=sizeof(FValue)){
		return false;
	}
	if(::Save(f,MinX)==false)
		return false;
	if(::Save(f,MaxX)==false)
		return false;
	return true;
}

void	GUICmdMakeShadingRegist::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	FilterInstanceContainer	*FilterInst=GetLayersBase()->GetCurrentPageDataPhase()->GetFilterContainer(localPage);
	for(FilterInstanceList *F=FilterInst->GetFirst();F!=NULL;F=F->GetNext()){
		if(F->GetFilterName()==/**/"LineShading"){
			CmdFilterLineShadingRegist	Cmd(GetLayersBase());
			Cmd.ShadingArea=ShadingArea;
			for(int i=0;i<sizeof(FValue)/sizeof(FValue[0]);i++){
				Cmd.FValue[i]=FValue[i];
			}
			Cmd.MinX=MinX;
			Cmd.MaxX=MaxX;
			F->TransmitDirectly(&Cmd);
		}
	}
	MakeShading	*f=(MakeShading	*)GetLayersBase()->FindByName(/**/"Button",/**/"MakeShading",/**/"");
	if(f!=NULL){
		f->LineShadingData[localPage].clear();
	}
	GetLayersBase()->SaveFilterDef();
}

//=================================================================================
GUICmdReqMakeShadingInfo::GUICmdReqMakeShadingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdReqMakeShadingInfo::Load(QIODevice *f)
{
	if(::Load(f,Phase)==false)
		return false;
	return true;
}
bool	GUICmdReqMakeShadingInfo::Save(QIODevice *f)
{
	if(::Save(f,Phase)==false)
		return false;
	return true;
}

void	GUICmdReqMakeShadingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdAckMakeShadingInfo	*SendBack=GetSendBack(GUICmdAckMakeShadingInfo,GetLayersBase(),EmitterRoot,EmitterName,localPage);
	SendBack->MakeShadingInfoStructData.MinX=0;
	SendBack->MakeShadingInfoStructData.MaxX=GetDotPerLine(localPage);

	FilterInstanceContainer	*FilterInst=GetLayersBase()->GetCurrentPageDataPhase()->GetFilterContainer(localPage);
	if(FilterInst!=NULL){
		FilterInstanceList	*F=FilterInst->Search(/**/"LineShading");
		if(F!=NULL){
			FilterLineShading	*Filter=dynamic_cast<FilterLineShading *>(F->GetFilterHandle());
			if(Filter!=NULL){
				SendBack->MakeShadingInfoStructData.Phase=GetLayersBase()->GetCurrentPhase();
				if(Filter->FValue!=NULL){
					for(int Layer=0;Layer<Filter->LayerNumb && Layer<3;Layer++){
						SendBack->MakeShadingInfoStructData.FValue[Layer]=Filter->FValue[Layer];
					}
				}
				SendBack->MakeShadingInfoStructData.MinX=Filter->MinX;
				SendBack->MakeShadingInfoStructData.MaxX=Filter->MaxX;
			}
		}
	}

	SendBack->Send(this,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdAckMakeShadingInfo::GUICmdAckMakeShadingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdAckMakeShadingInfo::Load(QIODevice *f)
{
	if(f->read((char *)&MakeShadingInfoStructData,sizeof(MakeShadingInfoStructData))!=sizeof(MakeShadingInfoStructData)){
		return false;
	}
	return true;
}
bool	GUICmdAckMakeShadingInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&MakeShadingInfoStructData,sizeof(MakeShadingInfoStructData))!=sizeof(MakeShadingInfoStructData)){
		return false;
	}
	return true;
}
GUICmdSetMakeShadingInfo::GUICmdSetMakeShadingInfo(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}
bool	GUICmdSetMakeShadingInfo::Load(QIODevice *f)
{
	if(f->read((char *)&MakeShadingInfoStructData,sizeof(MakeShadingInfoStructData))!=sizeof(MakeShadingInfoStructData)){
		return false;
	}

	return true;
}
bool	GUICmdSetMakeShadingInfo::Save(QIODevice *f)
{
	if(f->write((const char *)&MakeShadingInfoStructData,sizeof(MakeShadingInfoStructData))!=sizeof(MakeShadingInfoStructData)){
		return false;
	}
	return true;
}
void	GUICmdSetMakeShadingInfo::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	FilterInstanceContainer	*FilterInst=GetLayersBase()->GetCurrentPageDataPhase()->GetFilterContainer(localPage);
	if(FilterInst!=NULL){
		FilterInstanceList	*F=FilterInst->Search(/**/"LineShading");
		if(F!=NULL){
			FilterLineShading	*Filter=dynamic_cast<FilterLineShading *>(F->GetFilterHandle());
			if(Filter!=NULL){
				if(Filter->FValue!=NULL){
					for(int Layer=0;Layer<Filter->LayerNumb && Layer<3;Layer++){
						Filter->FValue[Layer]=MakeShadingInfoStructData.FValue[Layer];
					}
					Filter->MinX=MakeShadingInfoStructData.MinX;
					Filter->MaxX=MakeShadingInfoStructData.MaxX;
				}
			}
		}
	}
}