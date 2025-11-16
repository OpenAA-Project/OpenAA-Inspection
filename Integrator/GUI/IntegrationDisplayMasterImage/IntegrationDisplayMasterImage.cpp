/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Integrator\GUI\IntegrationDisplayMasterImage\IntegrationDisplayMasterImage.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
#include "IntegrationDisplayMasterImage.h"
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"
#include "XIntegrationBase.h"
#include "swap.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"DisplayMasterImage";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Display master image in Integration");
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
	return(new IntegrationDisplayMasterImage(Base,parent));
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
	Data[0].VariableNameWithRoute=/**/"MachineCode";
	Data[0].Pointer				 =&((IntegrationDisplayMasterImage *)Instance)->MachineCode;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowNGPoint";
	Data[1].Pointer				 =&((IntegrationDisplayMasterImage *)Instance)->ShowNGPoint;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationDisplayMasterImage.png")));
}

//==================================================================================================

IntegrationDisplayMasterImage::IntegrationDisplayMasterImage(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	MachineCode=-1;
	CurrentPhase=0;
	CurrentInspection=NULL;
	ShowNGPoint	=true;
	ZoomRate	=1.0;
	Image		=NULL;
	CurrentImagePoint	=NULL;
	PhaseNumb	=0;
	resize(100,100);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationDisplayMasterImage::~IntegrationDisplayMasterImage(void)
{
	if(Image!=NULL){
		for(int phase=0;phase<PhaseNumb;phase++){
			delete	Image[phase];
		}
		delete	[]Image;
		Image=NULL;
	}
}

void	IntegrationDisplayMasterImage::StartLot(void)
{
	CurrentInspection=NULL;
	CurrentNGPoint	 =NULL;
	CurrentImagePoint=NULL;
	EmitRepaint();
	return;
}

void	IntegrationDisplayMasterImage::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	CmdLoadedMasterData	*CmdLoadedMasterDataVar=dynamic_cast<CmdLoadedMasterData *>(v);
	CmdUpdatedMasterImage	*CmdUpdatedMasterImageVar=dynamic_cast<CmdUpdatedMasterImage *>(v);
	if(CmdLoadedMasterDataVar!=NULL || CmdUpdatedMasterImageVar!=NULL){
		EachMaster	*f=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
		if(f!=NULL){
			MakeImage(f);
		}
		CurrentInspection=NULL;
		CurrentNGPoint	 =NULL;
		CurrentImagePoint=NULL;
		return;
	}
	CmdLoadedImage	*CmdLoadedImageVar=dynamic_cast<CmdLoadedImage *>(v);
	if(CmdLoadedImageVar!=NULL){
		CurrentInspection=CmdLoadedImageVar->Pointer;
		return;
	}
	CmdShowNGPoint	*CmdShowNGPointVar=dynamic_cast<CmdShowNGPoint *>(v);
	if(CmdShowNGPointVar!=NULL){
		CurrentNGPoint	 =NULL;
		CurrentImagePoint=NULL;
		if(CmdShowNGPointVar->Master!=NULL
		&& CmdShowNGPointVar->Master->GetMachineCode()==MachineCode){
			if(CmdShowNGPointVar->NGImage!=NULL){
				CurrentNGPoint	 =CmdShowNGPointVar->NG;
				CurrentImagePoint=CmdShowNGPointVar->NGImage;
				CurrentInspection=CmdShowNGPointVar->Result;
			}
		}
		EmitRepaint();
		return;
	}
	CmdSelectResult	*CmdSelectResultVar=dynamic_cast<CmdSelectResult *>(v);
	if(CmdSelectResultVar!=NULL){
		CurrentInspection=NULL;
		if(GetLayersBase()->GetIntegrationBasePointer()!=NULL){
			EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
			if(m!=NULL){
				for(InspectionList *L=m->GetCurrentInspection().GetFirst();L!=NULL;L=L->GetNext()){
					if(L->ID==CmdSelectResultVar->ResultID){
						CurrentInspection=L;
						break;
					}
				}
			}
		}
		EmitRepaint();
		return;
	}
	CmdClearMasterData	*CmdClearMasterDataVar=dynamic_cast<CmdClearMasterData *>(v);
	if(CmdClearMasterDataVar!=NULL){
		if(Image!=NULL){
			for(int phase=0;phase<PhaseNumb;phase++){
				delete	Image[phase];
			}
			delete	[]Image;
			Image=NULL;
		}
		CurrentInspection=NULL;
		CurrentImagePoint=NULL;
		CurrentNGPoint	 =NULL;
		EmitRepaint();
		return;
	}
	CmdReqUpdateCurrentInspection	*CmdReqUpdateCurrentInspectionVar=dynamic_cast<CmdReqUpdateCurrentInspection *>(v);
	if(CmdReqUpdateCurrentInspectionVar!=NULL){
		if(CmdReqUpdateCurrentInspectionVar->SlaveNo==GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode)){
			EachMaster *m=GetLayersBase()->GetIntegrationBasePointer()->MasterDatas[CmdReqUpdateCurrentInspectionVar->SlaveNo];
			CurrentInspection=m->GetCurrentInspection().GetLast();
			EmitRepaint();
		}
		return;
	}
	CmdChangeLotID	*CmdChangeLotIDVar=dynamic_cast<CmdChangeLotID *>(v);
	if(CmdChangeLotIDVar!=NULL){
		CurrentInspection=NULL;
		CurrentImagePoint=NULL;
		CurrentNGPoint	 =NULL;
		EmitRepaint();
		return;
	}

}

void	IntegrationDisplayMasterImage::ResizeAction()
{
	EachMaster	*f=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(f!=NULL){
		MakeImage(f);
	}
}
void IntegrationDisplayMasterImage::paintEvent ( QPaintEvent * )
{
	QPainter	Pnt(this);

	bool	Drawn=false;
	Pnt.setPen(Qt::red);
	EachMaster	*m=NULL;
	if(ShowNGPoint==true && CurrentInspection!=NULL 
	&& 0<=CurrentPhase && CurrentPhase<PhaseNumb
	&& GetLayersBase()->GetIntegrationBasePointer()->AvailableIntegrationResource==true){
		m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
		if(m!=NULL){
			for(NGPointInAllPage	*Ph=CurrentInspection->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
				for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
					for(NGPoint *P=Pg->NPListPack<NGPoint>::GetFirst();P!=NULL;P=P->GetNext()){
						if(P->IsNG()==true){
							if(0<=Ph->GetPhase() && Ph->GetPhase()<PhaseNumb){
								CurrentPhase=Ph->GetPhase();
							}
							break;
						}
					}
				}
			}
			if(Image!=NULL && Image[CurrentPhase]!=NULL && CurrentPhase<PhaseNumb){
				if(Image[CurrentPhase]->isNull()==false){
					Pnt.drawImage(0,0,*Image[CurrentPhase]);
					Drawn=true;
				}
			}

			for(NGPointInAllPage	*Ph=CurrentInspection->NGPointAllPhases.GetFirst();Ph!=NULL;Ph=Ph->GetNext()){
				for(NGPointInPage *Pg=Ph->NPListPack<NGPointInPage>::GetFirst();Pg!=NULL;Pg=Pg->GetNext()){
					int	page=Pg->Page;
					if(0<=Ph->GetPhase() && Ph->GetPhase()<PhaseNumb && 0<=page && page<m->GetPageNumb()){
						XYData	*XY=m->GetOutlineOffset(Ph->GetPhase(), Pg->GetPage());
						if(XY!=NULL){
							for(NGPoint *P=Pg->NPListPack<NGPoint>::GetFirst();P!=NULL;P=P->GetNext()){
								if(P->IsNG()==true){

									LayersBase	*LBase=GetLayersBase()->GetShadowTree(P->ShadowLevel ,P->ShadowNumber);

									int	Cx,Cy;
									P->GetMasterCenter(Cx,Cy);
									if(LBase!=NULL){
										LBase->ConvertToTop(Cx,Cy);
									}
									int	X=Cx+XY->x;
									int	Y=Cy+XY->y;
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
	}
	if(Drawn==false && Image!=NULL){
		if(0<=CurrentPhase && CurrentPhase<PhaseNumb && Image[CurrentPhase]!=NULL){
			if(Image[CurrentPhase]->isNull()==false){
				Pnt.drawImage(0,0,*Image[CurrentPhase]);
			}
		}
		else if(Image[0]!=NULL){
			if(Image[0]->isNull()==false){
				Pnt.drawImage(0,0,*Image[0]);
			}
		}
	}
	if(CurrentImagePoint!=NULL && CurrentNGPoint!=NULL){
		int	x1=0;
		int	y1=0;
		int	x2=0;
		int	y2=0;
		LayersBase	*LBase=GetLayersBase()->GetShadowTree(CurrentImagePoint->ShadowLevel ,CurrentImagePoint->ShadowNumber);
		int	Page=CurrentImagePoint->GlobalPage;
		int	OffsetX=0;
		int	OffsetY=0;
		if(m!=NULL){
			XYData	*XY=m->GetOutlineOffset(CurrentPhase,Page);
			OffsetX=XY->x;
			OffsetY=XY->y;
		}
		int	Mx1=CurrentImagePoint->x1+OffsetX;
		int	My1=CurrentImagePoint->y1+OffsetY;
		int	Mx2=CurrentImagePoint->x2+OffsetX;
		int	My2=CurrentImagePoint->y2+OffsetY;

		double	tZoomRate=ZoomRate;
		if(LBase!=NULL){
			LBase->ConvertToTop(Mx1,My1);
			LBase->ConvertToTop(Mx2,My2);
			//tZoomRate=ZoomRate/((double)(Mx2-Mx1))*((double)(CurrentImagePoint->x2-CurrentImagePoint->x1));
			//Šù‚ÉMx,My‚ÍLk‚ª‚©‚©‚Á‚Ä‚¢‚é
		}

		if(CurrentNGPoint==NULL){
			x1=Mx1*tZoomRate;
			y1=My1*tZoomRate;
			x2=Mx2*tZoomRate;
			y2=My2*tZoomRate;
		}
		else{
			x1=(Mx1-CurrentNGPoint->MX-CurrentNGPoint->HX)*tZoomRate;
			y1=(My1-CurrentNGPoint->MY-CurrentNGPoint->HY)*tZoomRate;
			x2=(Mx2-CurrentNGPoint->MX-CurrentNGPoint->HX)*tZoomRate;
			y2=(My2-CurrentNGPoint->MY-CurrentNGPoint->HY)*tZoomRate;
		}

		Pnt.setPen(Qt::red);
		Pnt.drawRect(x1,y1,x2-x1,y2-y1);
	}
}
void	IntegrationDisplayMasterImage::MakeImage(EachMaster *m)
{
	if(Image!=NULL && PhaseNumb>0 && (Image[0]->width()!=width() || Image[0]->height()!=height() || m->GetPhaseNumb()!=PhaseNumb)){
		for(int phase=0;phase<PhaseNumb;phase++){
			delete	Image[phase];
		}
		delete	[]Image;
		Image=NULL;
	}
	if(Image==NULL && m->GetPhaseNumb()>0 && m->GetPageNumb()>0){
		PhaseNumb=m->GetPhaseNumb();
		Image=new QImage*[PhaseNumb];
		for(int phase=0;phase<PhaseNumb;phase++){
			Image[phase]=new QImage(width(),height(),QImage::Format_ARGB32);
		}
	}
	if(Image>0){
		for(int phase=0;phase<PhaseNumb;phase++){
			Image[phase]->fill(Qt::black);
			for(int page=0;page<m->GetPageNumb();page++){
				double	Zx=width()/((double)m->GetDotPerLine(phase,page));
				double	Zy=height()/((double)m->GetMaxLines(phase,page));
				ZoomRate=min(Zx,Zy);
				XYData	*c=m->GetOutlineOffset(phase, page);
				ImageBuffer	*IBuff[100];
				for(int Layer=0;Layer<m->GetLayerNumb(phase,page);Layer++){
					IBuff[Layer]=m->GetMasterImage(phase,page,Layer);
				}
				m->DrawImage(Image[phase],*c
							,phase,page
							,IBuff
							,ZoomRate,0,0);
			}
		}
	}
}

void	IntegrationDisplayMasterImage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqNGPositionInPanel	*CmdReqNGPositionInPanelVar=dynamic_cast<CmdReqNGPositionInPanel *>(packet);
	if(CmdReqNGPositionInPanelVar!=NULL){
		if(CmdReqNGPositionInPanelVar->Master!=NULL && CmdReqNGPositionInPanelVar->Master->GetMachineCode()==MachineCode){
			int	cx,cy;
			NGPoint	*P=CmdReqNGPositionInPanelVar->NG;
			if(P!=NULL){
				P->GetMasterCenter(cx,cy);
				LayersBase	*LBase=GetLayersBase()->GetShadowTree(P->ShadowLevel ,P->ShadowNumber);
				if(LBase!=NULL){
					LBase->ConvertToTop(cx,cy);
				}
				int	OffsetX=0,OffsetY=0;
				if(P->PagePoint!=NULL){
					XYData	*XY=CmdReqNGPositionInPanelVar->Master->GetOutlineOffset(0, P->PagePoint->GetPage());
					OffsetX=XY->x;
					OffsetY=XY->y;
				}
				int	x=(cx+OffsetX)*ZoomRate;
				int	y=(cy+OffsetY)*ZoomRate;
				QPoint	Point=mapToGlobal(QPoint(x,y));
				CmdReqNGPositionInPanelVar->WorldX1=Point.x();
				CmdReqNGPositionInPanelVar->WorldY1=Point.y();
				CmdReqNGPositionInPanelVar->WorldX2=Point.x();
				CmdReqNGPositionInPanelVar->WorldY2=Point.y();
				CmdReqNGPositionInPanelVar->Found=true;
			}
		}
		else{
			CmdReqNGPositionInPanelVar->Found=false;
		}
		return;
	}
}