/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationShowSavedImage\IntegrationShowSavedImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationShowSavedImage.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "swap.h"
#include <omp.h>
#include "IntegrationShowHistoryLoadImageForm.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowSavedImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show saved image");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationShowSavedImage(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"ShownMachineCode";
	Data[0].Pointer				 =&((IntegrationShowSavedImage *)Instance)->ShownMachineCode;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"ShownPhase";
	Data[1].Pointer				 =&((IntegrationShowSavedImage *)Instance)->ShownPhase;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowMaster";
	Data[2].Pointer				 =&((IntegrationShowSavedImage *)Instance)->ShowMaster;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"EnableToColorizeFor3Layers";
	Data[3].Pointer				 =&((IntegrationShowSavedImage *)Instance)->EnableToColorizeFor3Layers;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowSavedImage.png")));
}

//==================================================================================================================
	
IntegrationShowSavedImage::IntegrationShowSavedImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Img=NULL;
	ShownMachineCode	=0;
	ShownPhase			=-1;
	ShowMaster			=true;
	CurrentInspection	=NULL;
	CurrentNG			=NULL;
	EnableToColorizeFor3Layers	=true;

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
IntegrationShowSavedImage::~IntegrationShowSavedImage(void)
{
	if(Img!=NULL){
		delete	Img;
		Img=NULL;
	}
}

void	IntegrationShowSavedImage::Prepare(void)
{
}
void	IntegrationShowSavedImage::ResizeAction()
{
	if(Img!=NULL){
		delete	Img;
	}
	Img=new QImage(width(),height(),QImage::Format_ARGB32);
}
void	IntegrationShowSavedImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqNGPositionInPanel	*CmdReqNGPositionInPanelVar=dynamic_cast<CmdReqNGPositionInPanel *>(packet);
	if(CmdReqNGPositionInPanelVar!=NULL){
		EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(ShownMachineCode);
		if(m!=NULL){
			int	CurrentPhase=0;
			int	CurrentPage=0;
			if(CurrentInspection!=NULL){
				for(int phase=0;phase<m->GetPhaseNumb();phase++){
					NGPointInAllPage	*Ph=CurrentInspection->NGPointAllPhases.GetItem(phase);
					if(Ph!=NULL){
						for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
							int	page=Pg->Page;
							for(NGPoint *P=Pg->NPListPack<NGPoint>::GetFirst();P!=NULL;P=P->GetNext()){
								if(P==CmdReqNGPositionInPanelVar->NG){
									CurrentPage=page;
									CurrentPhase=phase;
								}
							}
						}
					}
				}
				XYData	*XY=m->GetOutlineOffset(CurrentPhase,CurrentPage);
				int	AreaX1,AreaY1,AreaX2,AreaY2;
				m->GetXY(AreaX1,AreaY1,AreaX2,AreaY2);

				double	Zx=((double)width())/(double)(AreaX2-AreaX1);
				double	Zy=((double)height())/((double)(AreaY2-AreaY1)*m->GetPhaseNumb());
				ZoomRate=min(Zx,Zy);
				int	Cx,Cy;
				CmdReqNGPositionInPanelVar->NG->GetTargetCenter(Cx,Cy);
				int	x1=(Cx+XY->x)*ZoomRate;
				int	y1=(Cy+XY->y+CurrentPhase*(AreaY2-AreaY1))*ZoomRate;
				QPoint	Local1(x1,y1);
				QPoint	G1=mapToGlobal(Local1);
				CmdReqNGPositionInPanelVar->WorldX1	=G1.x();
				CmdReqNGPositionInPanelVar->WorldY1	=G1.y();
				CmdReqNGPositionInPanelVar->WorldX2	=G1.x();
				CmdReqNGPositionInPanelVar->WorldY2	=G1.y();
				CmdReqNGPositionInPanelVar->Found=true;
			}
			else{
				CmdReqNGPositionInPanelVar->Found=false;
			}
		}
		return;
	}
}

void IntegrationShowSavedImage::paintEvent ( QPaintEvent * event )
{
	if(Img!=NULL){
		Img->fill(Qt::black);
	}
	QPainter	Pnt(this);

	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(ShownMachineCode);
	if(m!=NULL){
		for(int phase=0;phase<m->GetPhaseNumb();phase++){
			PaintInPhase(Pnt,phase,m);
		}
	}
}

void IntegrationShowSavedImage::PaintInPhase(QPainter &Pnt ,int phase ,EachMaster *m)
{
	if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
		if(m!=NULL && 0<=phase && phase<m->GetPhaseNumb()){
			int	AreaX1,AreaY1,AreaX2,AreaY2;
			m->GetXY(AreaX1,AreaY1,AreaX2,AreaY2);
			int	CurrentPage=-1;

			if(CurrentNG!=NULL && CurrentInspection!=NULL){
				NGPointInAllPage	*Ph=CurrentInspection->NGPointAllPhases.GetItem(phase);
				if(Ph!=NULL){
					for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
						int	page=Pg->Page;
						for(NGPoint *P=Pg->NPListPack<NGPoint>::GetFirst();P!=NULL;P=P->GetNext()){
							if(P==CurrentNG){
								CurrentPage=page;
							}
						}
					}
				}
			}

			double	Zx=((double)width())/((double)(AreaX2-AreaX1));
			double	Zy=((double)height())/((double)(AreaY2-AreaY1)*m->GetPhaseNumb());
			ZoomRate=min(Zx,Zy);

			if(CurrentPage<0){
				XYData	XY0;
				for(int page=0;page<m->GetPageNumb();page++){
					XYData	*XY=m->GetOutlineOffset(phase,page);
					XY->y+=phase*(AreaY2-AreaY1);
					if(page>0){
						if(XY0==*XY)
							continue;
					}
					else{
						XY0=*XY;
					}
					ImageBuffer	*IBuff[100];
					for(int Layer=0;Layer<m->GetLayerNumb(phase,page);Layer++){
						if(ShowMaster==true)
							IBuff[Layer]=m->GetMasterImage(phase,page,Layer);
						else
							IBuff[Layer]=m->GetTargetImage(phase,page,Layer);
					}

					m->DrawImage(Img,*XY
							,phase,page
							,IBuff
							,ZoomRate,-AreaX1,-AreaY1
							,EnableToColorizeFor3Layers);
				}
			}
			else{
					XYData	*XY=m->GetOutlineOffset(phase,CurrentPage);
					XY->y+=phase*(AreaY2-AreaY1);
					ImageBuffer	*IBuff[100];
					for(int Layer=0;Layer<m->GetLayerNumb(phase,CurrentPage);Layer++){
						if(ShowMaster==true)
							IBuff[Layer]=m->GetMasterImage(phase,CurrentPage,Layer);
						else
							IBuff[Layer]=m->GetTargetImage(phase,CurrentPage,Layer);
					}
					m->DrawImage(Img,*XY
							,phase,CurrentPage
							,IBuff
							,ZoomRate,-AreaX1,-AreaY1
							,EnableToColorizeFor3Layers);
			}
			

			Pnt.drawImage(0,0,*Img);

			if(CurrentInspection!=NULL){
				NGPointInAllPage	*Ph=CurrentInspection->NGPointAllPhases.GetItem(phase);
				if(Ph!=NULL){
					for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
						int	page=Pg->Page;
						if(CurrentPage==page){
							Pnt.setPen(Qt::red);
						}
						else{
							Pnt.setPen(Qt::darkRed);
						}
						XYData	*XY=m->GetOutlineOffset(phase,page);
						for(NGPoint *P=Pg->NPListPack<NGPoint>::GetFirst();P!=NULL;P=P->GetNext()){
							int	Cx,Cy;
							P->GetTargetCenter(Cx,Cy);
							int	X=Cx+XY->x;
							int	Y=Cy+XY->y+phase*(AreaY2-AreaY1);
							int	tx=X*ZoomRate;
							int	ty=Y*ZoomRate;
							if(0<=tx && tx<width() && 0<=ty && ty<height()){
								Pnt.drawArc(tx-10,ty-10,20,20,0,5760);
							}
						}
					}
				}
			}
		}
	}
}
void	IntegrationShowSavedImage::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdLoadedImage	*CmdLoadedImageVar=dynamic_cast<CmdLoadedImage *>(v);
	if(CmdLoadedImageVar!=NULL){
		CurrentInspection	=CmdLoadedImageVar->Pointer;
		if(CurrentInspection->FileName.isEmpty()==true)
			CurrentInspection->FileName=CmdLoadedImageVar->Pointer->RemarkData;
		ShownMachineCode	=CmdLoadedImageVar->Pointer->GetMaster()->GetMachineCode();
		CurrentNG=NULL;
		BroadcastRepaintAll();
		return;
	}
	CmdShowNGPoint	*CmdShowNGPointVar=dynamic_cast<CmdShowNGPoint *>(v);
	if(CmdShowNGPointVar!=NULL){
		CurrentNG	=CmdShowNGPointVar->NG;
		EmitRepaint();
		return;
	}
}
void	IntegrationShowSavedImage::StartLot	(void)
{
	CurrentInspection=NULL;
	CurrentNG		=NULL;
}
