/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyRasterImagePanel\EasyRasterImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyRasterImagePanel.h"
#include "XCrossObj.h"
//#include "ImageControlTools.h"
#include "XRaster.h"
#include "XGeneralFunc.h"
//#include "ImagePanelTools.h"
//#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include <QIcon>
#include <QPixmap>
#include <QColor>
#include "XGUIDLL.h"
#include "XIntegrationBase.h"
#include "EasyPropertyRasterForm.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyRasterImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyRasterImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

	(*Base)	=new IntegrationCmdMove		(Base,sRoot,sName);
	(*Base)	=new IntegrationCmdSelect	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
	Q_CLEANUP_RESOURCE(DisplayImage);
	Q_CLEANUP_RESOURCE(IntegrationLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	EasyRasterImagePanel	*B=new EasyRasterImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyRasterImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
	if(N<0)
		return -1;
	//Data[N].Type				  =/**/"QString";
	//Data[N].VariableNameWithRoute=/**/"ImageControlToolsName";
	//Data[N].Pointer			  =&((EasyMaskingImagePanel *)Instance)->ImageControlToolsName;
	//N++;
	return(N);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/EasyRasterImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"Raster"));
}
DEFFUNCEX	int32	DLL_RegistMacroFunction(ExportFuncForMacro Functions[],int MaxBuffer)
{
	int32	ret=DisplayImageWithAlgorithm::RegistMacroFunction(Functions,MaxBuffer);
	return ret;
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

//====================================================================================

EasyRasterImagePanel::EasyRasterImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"Raster",parent)
{
	OnMoving=false;
	SetMode(mtFrameDraw::fdPoly);

	connect(this,SIGNAL(SignalModeChanged()),this,SLOT(SlotModeChanged()));

	Timer.setSingleShot(false);
	Timer.setInterval(300);
	connect(&Timer,SIGNAL(timeout()),this,SLOT(SlotTimeout()));
	ShowElementMode=false;
	Timer.start();
}
void	EasyRasterImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyRasterImagePanel::CreateDrawAttrPointer(void)
{
	RasterDrawAttr	*RAttr=new RasterDrawAttr(
											 Qt::green		,128
											,Qt::red		,128
											,Qt::cyan		,80
											);
	EasyPropertyRasterForm	*AccessForm=GetPropertyForm();
	if(AccessForm!=NULL){
		CmdRasterDrawAttr	Cmd(GetLayersBase());
		AccessForm->TransmitDirectly(&Cmd);
		RAttr->DrawMode.AlignmentMode	=false;
		RAttr->DrawMode.DrawPickUpArea	=Cmd.DrawPickUpArea;
		if(ShowElementMode==true){
			RAttr->DrawMode.CurrentElementGlobalPage=0;
			RAttr->DrawMode.CurrentElementID	=Cmd.CurrentElementID;
		}
		else{
			RAttr->DrawMode.CurrentElementGlobalPage=-1;
		}
	}
	return RAttr;
}
void	EasyRasterImagePanel::SlotTimeout()
{
	if(IsShown()==true){
		ShowElementMode=!ShowElementMode;
		Repaint();
	}
}
void	EasyRasterImagePanel::SlotCanvasMouseMove (int globalX ,int globalY)
{
	if(IsMoveMode()==true){
		if(OnMoving==true){
			int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
			IntegrationCmdMove	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.GlobalDx=globalX-LastPosX;
			RCmd.GlobalDy=globalY-LastPosY;
			RCmd.Send(NULL,SlaveNo,0);
			LastPosX=globalX;
			LastPosY=globalY;
		}
	}
	else{
		IntegrationAlgoSimpleImagePanel::SlotCanvasMouseMove (globalX ,globalY);
	}
}
void	EasyRasterImagePanel::SlotJustMouseLPress(int globalX ,int globalY)
{
	if(IsMoveMode()==true){
		if(OnMoving==false){
			OnMoving=true;
			int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
			IntegrationCmdSelect	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.SelectMode=true;
			RCmd.Send(NULL,SlaveNo,0);

			LastPosX=globalX;
			LastPosY=globalY;
		}
		else{
			LastPosX=globalX;
			LastPosY=globalY;
		}
	}
	//else{
	//	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseLDown (globalX ,globalY);
	//}
}
void	EasyRasterImagePanel::SlotJustMouseLRelease(int globalX ,int globalY)
{
	if(IsMoveMode()==true){
		if(OnMoving==true){
			OnMoving=false;
			int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
			IntegrationCmdSelect	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
			RCmd.SelectMode=false;
			RCmd.Send(NULL,SlaveNo,0);
		}
	}
	//else{
	//	IntegrationAlgoSimpleImagePanel::SlotCanvasMouseRDown (globalX ,globalY);
	//}

}

bool	EasyRasterImagePanel::IsMoveMode(void)
{
	EasyPropertyRasterForm	*AccessForm=GetPropertyForm();
	if(AccessForm!=NULL){
		IntegrationCmdReqMoveMode	RCmd(GetLayersBase());
		AccessForm->TransmitDirectly(&RCmd);
		return RCmd.MoveMode;
	}
	return false;
}
EasyPropertyRasterForm	*EasyRasterImagePanel::GetPropertyForm(void)
{
	GUIFormBase *GUIFormRet[100];
	int	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyRaster" ,GUIFormRet,100);
	if(n==1){
		return ((EasyPropertyRasterForm *)GUIFormRet[0]);
	}
	EachMaster	*ThisM=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(ThisM==NULL)
		return NULL;
	int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
	EasyPropertyRasterForm	*AccessForm=NULL;
	for(int i=0;i<n;i++){
		if(((EasyPropertyRasterForm *)GUIFormRet[i])->SlaveNo==SlaveNo){
			AccessForm=((EasyPropertyRasterForm *)GUIFormRet[i]);
			break;
		}
	}
	return AccessForm;
}

void	EasyRasterImagePanel::SlotModeChanged  ()
{
	EasyPropertyRasterForm	*AccessForm=GetPropertyForm();
	if(AccessForm!=NULL){
		IntegrationCmdSetMoveMode	RCmd(GetLayersBase());
		RCmd.MoveMode=false;
		AccessForm->TransmitDirectly(&RCmd);
	}
	if(OnMoving==true){
		OnMoving=false;
		int	SlaveNo=GetLayersBase()->GetIntegrationBasePointer()->GetIntegrationSlaveNoFromMachineCode(MachineCode);
		IntegrationCmdSelect	RCmd(GetLayersBase(),sRoot,sName,SlaveNo);
		RCmd.SelectMode=false;
		RCmd.Send(NULL,SlaveNo,0);
	}
}
void	EasyRasterImagePanel::DrawEndAfterOperationAddItem(FlexArea &ResultArea,QByteArray &SomethingData)
{
	if(GetEditMode()==true)
		return;
	EachMaster	*m=GetLayersBase()->GetIntegrationBasePointer()->FindMaster(MachineCode);
	if(m==NULL)
		return;
	if(m->GetPhaseNumb()<=0 || m->GetPageNumb()<=0)
		return;
	int	Phase=m->GetCurrentPhase();
	if(Phase<0)
		return;

	EasyPropertyRasterForm	*RForm=GetPropertyForm();
	if(RForm!=NULL){
		IntegrationCmdReqAddArea	Cmd(GetLayersBase());
		Cmd.AddedArea=ResultArea;
		RForm->TransmitDirectly(&Cmd);
	}
}

void	EasyRasterImagePanel::DrawImage(QImage &Image
							,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &_AlgoDLLRoot ,QString &_AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)
{
	IntegrationAlgoSimpleImagePanel::DrawImage(Image 
							,ZoomRate ,MovX ,MovY 
							,Phase ,LayerList
							,DrawAtterData
							,_AlgoDLLRoot ,_AlgoDLLName
							,tOnSelection
							,tOnMoving
							,tSelectionDx,tSelectionDy);
	EasyPropertyRasterForm	*RForm=GetPropertyForm();
	if(RForm!=NULL){
		IntegrationCmdReqRegColorElementID	RCmd(GetLayersBase());
		RForm->TransmitDirectly(&RCmd);

		if(RCmd.CurrentElementID>=0){
			AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(_AlgoDLLRoot ,_AlgoDLLName);
			if(Ab!=NULL){
				AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
				if(Ah!=NULL){
					RasterDrawAttr	*Attr=(RasterDrawAttr *)CreateDrawAttrPointer();
					Attr->DrawMode.CurrentElementGlobalPage=0;
					Attr->DrawMode.CurrentElementID	=RCmd.CurrentElementID;
					for(int page=0;page<GetPageNumb();page++){
						AlgorithmInPageRoot	*Ap=Ah->GetPageData(page);
						Ap->Draw(Image, LayerList ,MovX ,MovY ,ZoomRate ,Attr);
					}
					if(Attr!=NULL){
						delete	Attr;
					}
				}
			}
		}
	}
}
//=================================================================================================

IntegrationCmdMove::IntegrationCmdMove(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdMove::Load(QIODevice *f)
{
	if(::Load(f,GlobalDx)==false)
		return false;
	if(::Load(f,GlobalDy)==false)
		return false;
	return true;
}
bool	IntegrationCmdMove::Save(QIODevice *f)
{
	if(::Save(f,GlobalDx)==false)
		return false;
	if(::Save(f,GlobalDy)==false)
		return false;
	return true;
}

void	IntegrationCmdMove::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)Form;
		W->ExecuteMove(GlobalDx,GlobalDy);
	}
}

IntegrationCmdSelect::IntegrationCmdSelect(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo)
	:IntegrationCmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),SlaveNo)
{
}
bool	IntegrationCmdSelect::Load(QIODevice *f)
{
	if(::Load(f,SelectMode)==false)
		return false;

	return true;
}
bool	IntegrationCmdSelect::Save(QIODevice *f)
{
	if(::Save(f,SelectMode)==false)
		return false;

	return true;
}

void	IntegrationCmdSelect::Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUIFormBase	*Form=GetLayersBase()->FindByName(/**/"Inspection",/**/"RasterImagePanel",/**/"");
	if(Form!=NULL){
		DisplayImageWithAlgorithm	*W=(DisplayImageWithAlgorithm *)Form;
		if(SelectMode==true){
			W->SlotSelectAll();
		}
		else{
			W->ExecuteReleaseAllSelection();
		}
	}
}
