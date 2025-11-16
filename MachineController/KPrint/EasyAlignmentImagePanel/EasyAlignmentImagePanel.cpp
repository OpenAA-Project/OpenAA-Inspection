/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\EasyAlignmentImagePanel\EasyAlignmentImagePanel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "EasyAlignmentImagePanel.h"
#include "XCrossObj.h"
#include "ImageControlTools.h"
//#include "XAlignmentFlexArea.h"
#include "XAlignmentLarge.h"
#include "XGeneralFunc.h"
#include "ImagePanelTools.h"
#include "SelectPages.h"
#include "XAlgorithmBase.h"
#include "XDisplayImagePacket.h"
#include "CartonMenuForm.h"
#include "XParamCustomized.h"
#include "PropertyAlignmentLargePacket.h"
#include "EasyPropertyAlignmentForm.h"
#include "XIntegrationSimpleImagePanelCommon.h"
#include "XDotColorMatchingLibrary.h"
#include "XCriticalFunc.h"

const	char	*sRoot=/**/"KidaPrint";
const	char	*sName=/**/"EasyAlignmentImagePanel";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"EasyAlignmentImagePanel");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	Q_INIT_RESOURCE(DisplayImage);
	Q_INIT_RESOURCE(IntegrationLib);

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
	EasyAlignmentImagePanel	*B=new EasyAlignmentImagePanel(Base,parent);
	//B->Initial(sRoot,sName);

	return(B);
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	int	N=((EasyAlignmentImagePanel *)Instance)->SetPropertyInDLL(Data ,maxDataDim);
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
	return(new QIcon(QPixmap(/**/":Resources/EasyAlignmentImagePanel.png")));
}

DEFFUNCEX	void	DLL_EntryAlgorithm(LayersBase *Base,RootNameListContainer &List)
{
	List.AppendList(new RootNameList(/**/"Basic",/**/"DotColorMatching"));
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

EasyAlignmentImagePanel::EasyAlignmentImagePanel(LayersBase *Base ,QWidget *parent)
:IntegrationAlgoSimpleImagePanel(Base,/**/"Basic",/**/"AlignmentLarge",parent)
{
	SetMode(mtFrameDraw::fdPoly);
	UseSelectionDialog=true;
	LastTimeToMakeImage	=0;
}
void	EasyAlignmentImagePanel::Prepare(void)
{
	IntegrationAlgoSimpleImagePanel::Prepare();
}

AlgorithmDrawAttr	*EasyAlignmentImagePanel::CreateDrawAttrPointer(void)
{
	CmdEasyAlignmentDrawModePacket	DrawMode(GetLayersBase());

	AlignmentLargeDrawAttr	*A=new AlignmentLargeDrawAttr();
	EasyPropertyAlignmentForm	*GProp=GetEasyPropertyAlignment();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
		for(ListPhasePageLayerItem *L=DrawMode.AreaIDList.GetFirst();L!=NULL;L=L->GetNext()){
			ReqAlignmentLargeAreaList	*k=new ReqAlignmentLargeAreaList;
			k->AreaID	=L->Data.ItemID;
			k->GlobalPage	=L->Data.Page;
			k->Layer		=L->Data.Layer;
			A->AList.AppendList(k);
		}
	}
	if(DrawMode.AreaPriority.GetCount()>=2){
		DrawMode.AreaPriority.Remove(-1);
	}

	A->DrawMode				=AlignmentLargeDrawAttr::_AreaMode;
	A->DrawKind				=AlignmentLargeDrawAttr::_Point;
	A->Priority				=DrawMode.AreaPriority;
	return A;
}

EasyPropertyAlignmentForm	*EasyAlignmentImagePanel::GetEasyPropertyAlignment(void)
{
	GUIFormBase *GUIRet[100];
	int	n;
	n=GetLayersBase()->EnumGUIInst(/**/"KidaPrint",/**/"EasyPropertyAlignment",GUIRet ,100);
	for(int i=0;i<n;i++){
		EasyPropertyAlignmentForm	*GUI=dynamic_cast<EasyPropertyAlignmentForm *>(GUIRet[i]);
		if(GUI!=NULL){
			if(n==1){
				return GUI;
			}
			if(GUI->SlaveNo==GetSlaveNo()){
				return GUI;
			}
		}
	}
	return NULL;
}

void	EasyAlignmentImagePanel::MakeDataToAddItem(FlexArea &GlobalArea ,QByteArray &Data)
{
	bool	AreaMode=false;
	XAlignmentLargeArea::_EnumPriority	AreaPriority=XAlignmentLargeArea::_EnumPriority::_PriorityGlobal;
	ListPhasePageLayerItemPack		AreaIDList;
	EasyPropertyAlignmentForm	*GUI=GetEasyPropertyAlignment();
	bool	AlignmentCharacterMode=false;
	if(GUI!=NULL){
		CmdReqAreaMode	RCmd(GetLayersBase());
		GUI->TransmitDirectly(&RCmd);
		AreaMode	=RCmd.AreaMode;
		AreaIDList	=RCmd.AreaIDList;
		AreaPriority=(XAlignmentLargeArea::_EnumPriority)RCmd.AreaPriority.GetFirst()->GetValue();
		AlignmentCharacterMode=RCmd.CharacterMode;
	}

	CartonMenuForm	*GProp=(CartonMenuForm *)GetLayersBase()->FindByName(/**/"KidaPrint" ,/**/"CartonMenu" ,/**/"");
	if(GProp!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::WriteOnly);

		::Save(&Buff,AreaMode);
		int32	iAreaPriority=(int32)AreaPriority;
		::Save(&Buff,iAreaPriority);
		AreaIDList.Save(&Buff);
		::Save(&Buff,GProp->Param.GeneratePartialAlignment	);
		::Save(&Buff,GProp->Param.AlignmntSearchAreaDot	);
		::Save(&Buff,GProp->Param.AlignmntSearchAreaDot2);
		::Save(&Buff,GProp->Param.AlignmntSearchAreaDotMiddle);
		if(GProp->Param.AlignmntSearchAreaDotY!=0)
			::Save(&Buff,GProp->Param.AlignmntSearchAreaDotY);
		else
			::Save(&Buff,GProp->Param.AlignmntSearchAreaDot	);
		if(GProp->Param.AlignmntSearchAreaDot2Y!=0)
			::Save(&Buff,GProp->Param.AlignmntSearchAreaDot2Y);
		else
			::Save(&Buff,GProp->Param.AlignmntSearchAreaDot2);
		if(GProp->Param.AlignmntSearchAreaDotMiddleY!=0)
			::Save(&Buff,GProp->Param.AlignmntSearchAreaDotMiddleY);
		else
			::Save(&Buff,GProp->Param.AlignmntSearchAreaDotMiddle);

		int32	SearchAround=GProp->Param.AlignmntSearchAreaDot/5;
		::Save(&Buff,SearchAround);
		IntList		InspectionLibs;
		if(GetSlaveNo()==0){
			if(GProp->ParamInMaster.Slave0LibID.GetCount()!=0){
				InspectionLibs.Merge(GProp->ParamInMaster.Slave0LibID);
			}
			else{
				InspectionLibs.Add(GProp->Param.DotColorMatchLibPattern1);
				InspectionLibs.Add(GProp->Param.DotColorMatchLibFlat1);
			}
		}
		else
		if(GetSlaveNo()==1){
			if(GProp->ParamInMaster.Slave1LibID.GetCount()!=0){
				InspectionLibs.Merge(GProp->ParamInMaster.Slave1LibID);
			}
			else{
				InspectionLibs.Add(GProp->Param.DotColorMatchLibPattern1);
				InspectionLibs.Add(GProp->Param.DotColorMatchLibFlat1);
			}
		}
		else
		if(GetSlaveNo()==2){
			if(GProp->ParamInMaster.Slave2LibID.GetCount()!=0){
				InspectionLibs.Merge(GProp->ParamInMaster.Slave2LibID);
			}
			else{
				InspectionLibs.Add(GProp->Param.DotColorMatchLibPattern1);
				InspectionLibs.Add(GProp->Param.DotColorMatchLibFlat1);
			}
		}
		InspectionLibs.Save(&Buff);
		::Save(&Buff,GProp->Param.AlignmntJudgeWithBrDif);
		::Save(&Buff,GProp->Param.AlignmentUseCharacterMode);
		::Save(&Buff,AlignmentCharacterMode);

		Data=Buff.buffer();
	}
}
void	EasyAlignmentImagePanel::CreateCallInfoInSelect(QByteArray &RetData)
{
	bool	AreaMode=false;
	XAlignmentLargeArea::_EnumPriority	AreaPriority=XAlignmentLargeArea::_EnumPriority::_PriorityGlobal;
	ListPhasePageLayerItemPack		AreaIDList;
	EasyPropertyAlignmentForm	*GUI=GetEasyPropertyAlignment();
	if(GUI!=NULL){
		CmdReqAreaMode	RCmd(GetLayersBase());
		GUI->TransmitDirectly(&RCmd);
		AreaMode	=RCmd.AreaMode;
		AreaIDList	=RCmd.AreaIDList;
		AreaPriority=(XAlignmentLargeArea::_EnumPriority)RCmd.AreaPriority.GetFirst()->GetValue();
	}
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,AreaMode);
	int32	d=(int32)AreaPriority;
	::Save(&Buff,d);
	AreaIDList.Save(&Buff);
	RetData=Buff.buffer();
	RedrawMode=true;
}
void	EasyAlignmentImagePanel::AddItemInAlgorithm(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &Area ,QByteArray &Data,QByteArray &SomethingData)
{
	QBuffer	Buff(&Data);
	Buff.open(QIODevice::ReadOnly);
	bool	AreaMode;
	bool	GeneratePartialAlignment;
	int32	AlignmntSearchAreaDot;
	int32	AlignmntSearchAreaDot2;
	int32	AlignmntSearchAreaDotMiddle;
	int32	AlignmntSearchAreaDotY;
	int32	AlignmntSearchAreaDot2Y;
	int32	AlignmntSearchAreaDotMiddleY;
	int32	SearchAround;
	int32	iAreaPriority;
	IntList	InspectionLibs;
	bool	AlignmntJudgeWithBrDif;
	bool	CharacterMode;
	XAlignmentLargeArea::_EnumPriority	AreaPriority;
	ListPhasePageLayerItemPack		AreaIDList;

	::Load(&Buff,AreaMode);
	::Load(&Buff,iAreaPriority);
	AreaIDList.Load(&Buff);
	AreaPriority	=(XAlignmentLargeArea::_EnumPriority)iAreaPriority;
	::Load(&Buff,GeneratePartialAlignment);
	::Load(&Buff,AlignmntSearchAreaDot);
	::Load(&Buff,AlignmntSearchAreaDot2);
	::Load(&Buff,AlignmntSearchAreaDotMiddle);
	::Load(&Buff,AlignmntSearchAreaDotY);
	::Load(&Buff,AlignmntSearchAreaDot2Y);
	::Load(&Buff,AlignmntSearchAreaDotMiddleY);
	::Load(&Buff,SearchAround);
	InspectionLibs.Load(&Buff);
	::Load(&Buff,AlignmntJudgeWithBrDif);
	bool	AlignmentUseCharacterMode;
	::Load(&Buff,AlignmentUseCharacterMode);
	::Load(&Buff,CharacterMode);

	if(AreaMode==true){
		AddPutAlignmentLargeAreaPacket		Cmd(GetLayersBase());
		Cmd.MasterNo	=0;
		Cmd.Page		=0;
		Cmd.Layer		=0;
		Cmd.Area		=Area;
		Cmd.Priority	=AreaPriority;
		if(GeneratePartialAlignment==true && AreaPriority==XAlignmentLargeArea::_PriorityMiddle){
			AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(DefLibTypeDotColorMatchingInspect);
			AlgorithmLibraryContainer	*C=ABase->GetLibraryContainer();
			AlgorithmLibraryLevelContainer	DestLib(ABase);
			for(IntClass *c=InspectionLibs.GetFirst();c!=NULL;c=c->GetNext()){
				C->GetLibrary(c->GetValue(),DestLib);
				Cmd.LimitedLib.Add(DefLibTypeDotColorMatchingInspect,DestLib);
			}
		}
		if(APage!=NULL){
			APage->TransmitDirectly(&Cmd);
		}
	}
	else{
		AddAlignmentMarkPacket	Cmd(GetLayersBase());
		Cmd.Area		=Area;
		if(GeneratePartialAlignment==true && AreaPriority==XAlignmentLargeArea::_PriorityMiddle){
			Cmd.MoveDotX	=AlignmntSearchAreaDotMiddle;
			Cmd.MoveDotY	=AlignmntSearchAreaDotMiddleY;
			Cmd.MoveDotX2	=AlignmntSearchAreaDotMiddle;
			Cmd.MoveDotY2	=AlignmntSearchAreaDotMiddleY;
		}
		else{
			Cmd.MoveDotX	=AlignmntSearchAreaDot;
			Cmd.MoveDotY	=AlignmntSearchAreaDotY;
			Cmd.MoveDotX2	=AlignmntSearchAreaDot2;
			Cmd.MoveDotY2	=AlignmntSearchAreaDot2Y;
		}
		Cmd.Priority	=AreaPriority;
		Cmd.SearchAround=SearchAround;
		//Cmd.GroupID		=0;
		Cmd.GroupNumber		=0;
		Cmd.UsageGlobal		=false;
		Cmd.JudgeWithBrDif	=AlignmntJudgeWithBrDif;
		Cmd.AlignmentUseCharacterMode	=AlignmentUseCharacterMode;
		Cmd.CharacterMode	=CharacterMode;
		Cmd.AreaIDList		=AreaIDList;
		Cmd.UseLayer		=-1;
		Cmd.ThresholdColor	=-1;
		if(APage!=NULL)
			APage->TransmitDirectly(&Cmd);
	}
}

void	EasyAlignmentImagePanel::SelectItem(int Phase
											,IntList &LayerList
											,FlexArea &Area
											,SelectedItemsInfoContainer &RetSelectedContainer
											,QByteArray &SomethingData)
{
	QBuffer	Buff(&SomethingData);
	Buff.open(QIODevice::ReadWrite);
	bool	AreaMode=false;
	XAlignmentLargeArea::_EnumPriority	AreaPriority;
	::Load(&Buff,AreaMode);
	int32	d;
	::Load(&Buff,d);
	AreaPriority=(XAlignmentLargeArea::_EnumPriority)d;
	ListPhasePageLayerItemPack		AreaIDList;
	AreaIDList.Load(&Buff);

	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		AlgorithmBase	*Ab=GetLayersBase()->GetAlgorithmBase(AlgoDLLRoot ,AlgoDLLName);
		if(Ab!=NULL){
			AlgorithmInPageInOnePhase	*Ah=Ab->GetPageDataPhase(Phase);
			if(Ah!=NULL){
				IntList	PageList;
				GetLayersBase()->GetLocalPageFromArea(Area,PageList);
				for(IntClass *v=PageList.GetFirst();v!=NULL;v=v->GetNext()){
					int	Page=v->GetValue();
					DataInPage	*pdata=GetLayersBase()->GetPageData(Page);
					AlignmentLargeInPage	*Ap=(AlignmentLargeInPage *)Ah->GetPageData(Page);
					if(Ap!=NULL && pdata!=NULL){
						FlexArea	A=Area;
						pdata->ClipMoveAreaFromGlobal(A);
						if(A.GetPatternByte()>0){
							if(AreaMode==false){
								SelectAlignmentPoints	RCmd(GetLayersBase());
								RCmd.Area=A;
								Ap->TransmitDirectly(&RCmd);

								AlgorithmItemPointerListContainer ItemPointers;
								Ap->GetSelectedItems(ItemPointers);
								for(AlgorithmItemPointerList *t=ItemPointers.GetFirst();t!=NULL;t=t->GetNext()){
									SelectedItemsInfo	*p=new SelectedItemsInfo();
									p->Phase=Phase;
									p->Page	=Page;
									p->Layer=t->GetItem()->GetLayer();
									p->ItemID	=t->GetItem()->GetID();
									p->ItemName	=t->GetItem()->GetItemName();
									AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(p->Layer);
									if(AL!=NULL){
										CmdReqAreaPriority	PCmd(GetLayersBase());
										PCmd.ItemID=p->ItemID;
										AL->TransmitDirectly(&PCmd);
										//p->Comment	=t->GetItem()->GetComment();
										switch(PCmd.AreaPriority){
											case XAlignmentLargeArea::_PriorityNone		:	p->Comment	=/**/"None";	break;
											case XAlignmentLargeArea::_PriorityHigh		:	p->Comment	=/**/"High";	break;
											case XAlignmentLargeArea::_PriorityMiddle	:	p->Comment	=/**/"Middle";	break;
											case XAlignmentLargeArea::_PriorityLow		:	p->Comment	=/**/"Low";		break;
											case XAlignmentLargeArea::_PriorityGlobal	:	p->Comment	=/**/"Global";	break;
										}
									}
									else{
										p->Comment	=t->GetItem()->GetComment(_TypeItemComment_Normal);
									}
									p->SomethingData	=SomethingData;
									RetSelectedContainer.AppendList(p);
								}
							}
							else{
								if(AreaIDList.IsEmpty()==true){
									for(int layer=0;layer<GetLayerNumb(Page);layer++){
										AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(layer);
										for(XAlignmentLargeArea *a=AL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
											if(a->Area.CheckOverlap(&A)==true
											&& a->Priority==AreaPriority){
												a->Selected=true;
											}
										}
									}
								}
								else{
									for(ListPhasePageLayerItem *k=AreaIDList.GetFirst();k!=NULL;k=k->GetNext()){
										AlignmentLargeInLayer	*AL=(AlignmentLargeInLayer *)Ap->GetLayerData(k->Data.Layer);
										if(AL!=NULL){
											for(XAlignmentLargeArea *a=AL->Areas.GetFirst();a!=NULL;a=a->GetNext()){
												if(a->Area.CheckOverlap(&A)==true
												&& a->AreaID==k->Data.ItemID
												&& a->Priority==AreaPriority){
													a->Selected=true;
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}
void	EasyAlignmentImagePanel::CreateCallInfoInDelete(QByteArray &RetData)
{
	bool	AreaMode=false;
	XAlignmentLargeArea::_EnumPriority	AreaPriority=XAlignmentLargeArea::_EnumPriority::_PriorityGlobal;

	EasyPropertyAlignmentForm	*GUI=GetEasyPropertyAlignment();
	if(GUI!=NULL){
		CmdReqAreaMode	RCmd(GetLayersBase());
		GUI->TransmitDirectly(&RCmd);
		AreaMode	=RCmd.AreaMode;
		AreaPriority=(XAlignmentLargeArea::_EnumPriority)RCmd.AreaPriority.GetFirst()->GetValue();
	}
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,AreaMode);
	int32	d=(int32)AreaPriority;
	::Save(&Buff,d);
	RetData=Buff.buffer();
}

void	EasyAlignmentImagePanel::DelSelectedItemsInAlgorithm(int SlaveNo
															,AlgorithmInPageRoot *APage 
															,IntList &LayerList
															,QByteArray &SomethingData)
{
	QBuffer	Buff(&SomethingData);
	Buff.open(QIODevice::ReadWrite);
	bool	AreaMode=false;
	::Load(&Buff,AreaMode);
	int32	d;
	::Load(&Buff,d);
	XAlignmentLargeArea::_EnumPriority	AreaPriority=(XAlignmentLargeArea::_EnumPriority)d;

	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
		CmdClickPointButton	Cmd1(GetLayersBase());
		f->TransmitDirectly(&Cmd1);
		if(AreaMode==false){
			APage->DeleteSelectedItems(LayerList);
		}
		else{
			for(int layer=0;layer<APage->GetLayerNumb();layer++){
				AlignmentLargeInLayer	*AL=dynamic_cast<AlignmentLargeInLayer *>(APage->GetLayerData(layer));
				if(AL!=NULL){
					RemoveSelectedAlignmentLargeAreaPacket	Cmd(GetLayersBase());
					AL->TransmitDirectly(&Cmd);
				}
			}
		}
		CmdClickAreaButton	Cmd2(GetLayersBase());
		f->TransmitDirectly(&Cmd2);
	}
}
void	EasyAlignmentImagePanel::CreateCallInfoInCut(QByteArray &RetData)
{
	bool	AreaMode=false;
	XAlignmentLargeArea::_EnumPriority	AreaPriority=XAlignmentLargeArea::_EnumPriority::_PriorityGlobal;

	EasyPropertyAlignmentForm	*GUI=GetEasyPropertyAlignment();
	if(GUI!=NULL){
		CmdReqAreaMode	RCmd(GetLayersBase());
		GUI->TransmitDirectly(&RCmd);
		AreaMode	=RCmd.AreaMode;
		AreaPriority=(XAlignmentLargeArea::_EnumPriority)RCmd.AreaPriority.GetFirst()->GetValue();
	}
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	::Save(&Buff,AreaMode);
	int32	d=(int32)AreaPriority;
	::Save(&Buff,d);
	RetData=Buff.buffer();
}

void	EasyAlignmentImagePanel::CutItemInAlgorithm	(int SlaveNo,AlgorithmInPageRoot *APage ,IntList &LayerList ,FlexArea &LocalArea ,QByteArray &SomethingData)
{
	QBuffer	Buff(&SomethingData);
	Buff.open(QIODevice::ReadWrite);
	bool	AreaMode=false;
	::Load(&Buff,AreaMode);
	int32	d;
	::Load(&Buff,d);
	XAlignmentLargeArea::_EnumPriority	AreaPriority=(XAlignmentLargeArea::_EnumPriority)d;

	if(AreaMode==true){
		CmdReqCutAreaWithPriority	RCmd(GetLayersBase());
		RCmd.AreaPriority	=AreaPriority;
		RCmd.AreaToCut		=LocalArea;
		APage->TransmitDirectly(&RCmd);
	}
	else{
		CmdReqCutPointWithPriority	RCmd(GetLayersBase());
		RCmd.AreaPriority	=AreaPriority;
		RCmd.AreaToCut		=LocalArea;
		APage->TransmitDirectly(&RCmd);
	}
}


void	EasyAlignmentImagePanel::DrawImage(QImage &Image ,double ZoomRate ,int MovX ,int MovY 
							,int Phase ,IntList &LayerList
							,QByteArray	&DrawAtterData
							,QString &AlgoDLLRoot ,QString &AlgoDLLName
							,bool tOnSelection
							,bool tOnMoving
							,int tSelectionDx,int tSelectionDy)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		DWORD	t=::GetComputerMiliSec();
		if(t-LastTimeToMakeImage>5000){
			GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
			CmdClickPointButton	Cmd1(GetLayersBase());
			f->TransmitDirectly(&Cmd1);
			LastTimeToMakeImage=t;
		}
	}
	IntegrationAlgoSimpleImagePanel::DrawImage(Image ,ZoomRate ,MovX ,MovY 
							,Phase ,LayerList
							,DrawAtterData
							,AlgoDLLRoot ,AlgoDLLName
							,tOnSelection
							,tOnMoving
							,tSelectionDx,tSelectionDy);
}

void	EasyAlignmentImagePanel::ExecuteMoveItems(const QString &AlgoDLLRoot ,const QString &AlgoDLLName ,int GlobalDx ,int GlobalDy)
{
	if(GetLayersBase()->GetParamComm()->GetConnectedPCNumb()==0){
		GUIFormBase	*f=GetLayersBase()->FindByName(/**/"Button",/**/"PropertyAlignmentLargeForm",/**/"");
		CmdClickPointButton	Cmd1(GetLayersBase());
		f->TransmitDirectly(&Cmd1);

		IntegrationAlgoSimpleImagePanel::ExecuteMoveItems(AlgoDLLRoot ,AlgoDLLName ,GlobalDx ,GlobalDy);
	}
}

void	EasyAlignmentImagePanel::MakeCopyToSlaveInfo(QByteArray &RetInfo)
{
	IntList	AreaPriority;
	CmdEasyAlignmentDrawModePacket	DrawMode(GetLayersBase());
	EasyPropertyAlignmentForm	*GProp=GetEasyPropertyAlignment();
	if(GProp!=NULL){
		GProp->TransmitDirectly(&DrawMode);
		AreaPriority=DrawMode.AreaPriority;

		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		AreaPriority.Save(&Buff);
		RetInfo=Buff.buffer();
	}
}

bool	EasyAlignmentImagePanel::LoadCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot	*Ap,QByteArray &RetData)
{
	IntList	AreaPriority;
	QBuffer	Buff(&InfoData);
	Buff.open(QIODevice::ReadWrite);
	AreaPriority.Load(&Buff);

	CmdReqAlignmentLargeSavePointByPriority	Cmd(GetLayersBase());
	Cmd.AreaPriority=AreaPriority;
	Cmd.SavedBuff.open(QIODevice::ReadWrite);
	Ap->TransmitDirectly(&Cmd);
	RetData=Cmd.SavedBuff.buffer();
	return true;
}

bool	EasyAlignmentImagePanel::SaveCopyToSlaveInfo(QByteArray &InfoData,AlgorithmInPageRoot *Ap,TransformBase	*Param,bool ClearBeforeCopy)
{
	CmdReqAlignmentLargeLoadPointByPriority	Cmd(GetLayersBase());;
	Cmd.Buff	=InfoData;
	Cmd.Param	=Param;
	Cmd.ClearBeforeCopy=ClearBeforeCopy;
	Ap->TransmitDirectly(&Cmd);
	return true;
}
