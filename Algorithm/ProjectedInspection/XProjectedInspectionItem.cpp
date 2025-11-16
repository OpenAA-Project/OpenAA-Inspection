/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\ProjectedInspection\XProjectedInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ProjectedInspectionFormResource.h"
#include "XProjectedInspection.h"
#include "XGeneralFunc.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XProjectedInspectionLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "swap.h"
#include "XAlignmentCommon.h"
#include "XAlgorithmDLL.h"
#include "XDisplaySimPanel.h"
#include "XProjectedInspectionAlgoPacket.h"
#include "XCrossObj.h"

extern	const	char	*sRoot;
extern	const	char	*sName;


ProjectedInspectionThreshold::ProjectedInspectionThreshold(ProjectedInspectionItem *parent)
:AlgorithmThreshold(parent)
{
	Angle=90;
	ExcludeDynamicMask	=true;
	TransitWidth		=4;
	OKWidthDiffereceL	=5;
	OKWidthDiffereceH	=5;
	UseAbsolute			=true;
	CircleMode			=false;
	EvenLength			=99999999;
	PartialSwingAngle	=25.0*2*M_PI/360;
}

void	ProjectedInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ProjectedInspectionThreshold *s=(const ProjectedInspectionThreshold *)&src;
	Angle				=s->Angle				;
	ExcludeDynamicMask	=s->ExcludeDynamicMask	;
	TransitWidth		=s->TransitWidth		;
	OKWidthDiffereceL	=s->OKWidthDiffereceL	;
	OKWidthDiffereceH	=s->OKWidthDiffereceH	;
	UseAbsolute			=s->UseAbsolute			;
	CircleMode			=s->CircleMode			;
	EvenLength			=s->EvenLength			;
	PartialSwingAngle	=s->PartialSwingAngle	;
}
bool	ProjectedInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ProjectedInspectionThreshold *s=(const ProjectedInspectionThreshold *)&src;
	if(Angle				!=s->Angle				)	return false;
	if(ExcludeDynamicMask	!=s->ExcludeDynamicMask	)	return false;
	if(TransitWidth			!=s->TransitWidth		)	return false;
	if(OKWidthDiffereceL	!=s->OKWidthDiffereceL	)	return false;
	if(OKWidthDiffereceH	!=s->OKWidthDiffereceH	)	return false;
	if(UseAbsolute			!=s->UseAbsolute		)	return false;
	if(CircleMode			!=s->CircleMode			)	return false;
	if(EvenLength			!=s->EvenLength			)	return false;
	if(PartialSwingAngle	!=s->PartialSwingAngle	)	return false;
	return true;
}
bool	ProjectedInspectionThreshold::Save(QIODevice *f)
{
	WORD	Ver=ProjectedInspectionVersion;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,Angle)==false)
		return false;
	if(::Save(f,ExcludeDynamicMask)==false)
		return false;
    if(::Save(f,TransitWidth)==false)
		return false;
    if(::Save(f,OKWidthDiffereceL)==false)
		return false;
    if(::Save(f,OKWidthDiffereceH)==false)
		return false;
    if(::Save(f,UseAbsolute)==false)
		return false;
    if(::Save(f,CircleMode)==false)
		return false;
    if(::Save(f,EvenLength)==false)
		return false;
	if(::Save(f,PartialSwingAngle)==false)
		return false;

	return true;
}
bool	ProjectedInspectionThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,Angle)==false)
		return false;
	if(::Load(f,ExcludeDynamicMask)==false)
		return false;
    if(::Load(f,TransitWidth)==false)
		return false;
    if(::Load(f,OKWidthDiffereceL)==false)
		return false;
    if(::Load(f,OKWidthDiffereceH)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,UseAbsolute)==false)
			return false;
	}
    if(::Load(f,CircleMode)==false)
		return false;
	if(Ver>=3){
		if(::Load(f,EvenLength)==false)
			return false;
	}
 	if(Ver>=4){
		if(::Load(f,PartialSwingAngle)==false)
			return false;
	}

	return true;
}

void	ProjectedInspectionThreshold::FromLibrary(AlgorithmLibrary *src)
{
	ProjectedInspectionLibrary	*LSrc=dynamic_cast<ProjectedInspectionLibrary *>(src);
	if(LSrc==NULL)
		return;
	Angle				=LSrc->Angle;
	ExcludeDynamicMask	=LSrc->ExcludeDynamicMask;
	TransitWidth		=LSrc->TransitWidth;
	OKWidthDiffereceL	=LSrc->OKWidthDiffereceL	;
	OKWidthDiffereceH	=LSrc->OKWidthDiffereceH	;
	UseAbsolute			=LSrc->UseAbsolute			;
	CircleMode			=LSrc->CircleMode			;
	EvenLength			=LSrc->EvenLength			;
	PartialSwingAngle	=LSrc->PartialSwingAngle	;
}
void	ProjectedInspectionThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	ProjectedInspectionLibrary	*LDst=dynamic_cast<ProjectedInspectionLibrary *>(Dest);
	if(LDst==NULL)
		return;
	
	LDst->Angle					=Angle;
	LDst->ExcludeDynamicMask	=ExcludeDynamicMask;
	LDst->TransitWidth			=TransitWidth;
	LDst->OKWidthDiffereceL		=OKWidthDiffereceL	;
	LDst->OKWidthDiffereceH		=OKWidthDiffereceH	;
	LDst->UseAbsolute			=UseAbsolute		;
	LDst->CircleMode			=CircleMode			;
	LDst->EvenLength			=EvenLength			;
	LDst->PartialSwingAngle		=PartialSwingAngle	;
}

//====================================================================================================
//====================================================================================================


ProjectedInspectionItem::ProjectedInspectionItem(void)
{
	ProjectedData	=NULL;
	BlockVDim		=NULL;
	ProjectedDots	=NULL;
	ProjectedResult	=NULL;
	ProjectedSize	=NULL;
	ProjectedThreH	=NULL;
	ProjectedThreL	=NULL;
	ProjectedDataLen=0;
	AllocatedBlockVDimNumb=0;
}
ProjectedInspectionItem::~ProjectedInspectionItem(void)
{
	Release();
}

void ProjectedInspectionItem::Release(void)
{
	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
		ProjectedData	=NULL;
	}
	if(BlockVDim!=NULL){
		delete	[]BlockVDim;
		BlockVDim	=NULL;
	}
	if(ProjectedDots!=NULL){
		ProjectedDots	=NULL;
		ProjectedDots	=NULL;
	}
	if(ProjectedResult!=NULL){
		ProjectedResult	=NULL;
		ProjectedResult	=NULL;
	}
	if(ProjectedSize!=NULL){
		ProjectedSize	=NULL;
		ProjectedSize	=NULL;
	}
	if(ProjectedThreH!=NULL){
		ProjectedThreH	=NULL;
		ProjectedThreH	=NULL;
	}
	if(ProjectedThreL!=NULL){
		ProjectedThreL	=NULL;
		ProjectedThreL	=NULL;
	}
	ProjectedDataLen=0;
}

AlgorithmItemPLI	&ProjectedInspectionItem::operator=(const AlgorithmItemRoot &src)
{
	const ProjectedInspectionItem	*s=dynamic_cast<const ProjectedInspectionItem *>(&src);
	if(s!=NULL){
		return operator=(*s);
	}
	return *this;
}
ProjectedInspectionItem &ProjectedInspectionItem::operator=(ProjectedInspectionItem &src)
{
	AlgorithmItemPLI::operator=(src);
	CopyThreshold(src);

	SCos				=src.SCos				;
	SSin				=src.SSin				;
	MasterCx			=src.MasterCx			;
	MasterCy			=src.MasterCy			;
	LMinD				=src.LMinD				;
	LMaxD				=src.LMaxD				;
	MinD				=src.MinD				;
	MaxD				=src.MaxD				;
	ProjectedDataLen	=src.ProjectedDataLen	;

	AVector	=src.AVector;

	if(ProjectedDots!=NULL){
		delete	[]ProjectedDots;
		ProjectedDots=NULL;
	}
	if(src.ProjectedDots!=NULL){
		ProjectedDots	=new int[ProjectedDataLen];
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedDots[i]=src.ProjectedDots[i];
		}
	}

	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
		ProjectedData=NULL;
	}
	if(src.ProjectedData!=NULL){
		ProjectedData	=new double[ProjectedDataLen];
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedData[i]=src.ProjectedData[i];
		}
	}
	if(BlockVDim!=NULL){
		delete	[]BlockVDim;
		BlockVDim=NULL;
	}
	if(src.BlockVDim!=NULL){
		AllocatedBlockVDimNumb=src.AllocatedBlockVDimNumb;
		BlockVDim	=new double[AllocatedBlockVDimNumb];
		for(int i=0;i<AllocatedBlockVDimNumb;i++){
			BlockVDim[i]=src.BlockVDim[i];
		}
	}	

	if(ProjectedResult!=NULL){
		delete	[]ProjectedResult;
		ProjectedResult=NULL;
	}
	if(src.ProjectedResult!=NULL){
		ProjectedResult	=new BYTE[ProjectedDataLen];
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedResult[i]=src.ProjectedResult[i];
		}
	}

	if(ProjectedSize!=NULL){
		delete	[]ProjectedSize;
		ProjectedSize=NULL;
	}
	if(src.ProjectedSize!=NULL){
		ProjectedSize	=new double[ProjectedDataLen];
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedSize[i]=src.ProjectedSize[i];
		}
	}

	if(ProjectedThreH!=NULL){
		delete	[]ProjectedThreH;
		ProjectedThreH=NULL;
	}
	if(src.ProjectedThreH!=NULL){
		ProjectedThreH	=new double[ProjectedDataLen];
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedThreH[i]=src.ProjectedThreH[i];
		}
	}

	if(ProjectedThreL!=NULL){
		delete	[]ProjectedThreL;
		ProjectedThreL=NULL;
	}
	if(src.ProjectedThreL!=NULL){
		ProjectedThreL	=new double[ProjectedDataLen];
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedThreL[i]=src.ProjectedThreL[i];
		}
	}
	return *this;
}

void	ProjectedInspectionItem::CopyThreshold(ProjectedInspectionItem &src)
{
	GetThresholdW()->CopyFrom(*((ProjectedInspectionThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

void	ProjectedInspectionItem::CopyThresholdOnly(ProjectedInspectionItem &src)
{
	GetThresholdW()->CopyFrom(*((ProjectedInspectionThreshold *)src.GetThresholdR()));
	SetInvertLogic(src.GetInvertLogic());
}

bool    ProjectedInspectionItem::Save(QIODevice *file)
{
	if(AlgorithmItemPLI::Save(file)==false)
		return false;

	WORD	Ver=1;
	if(::Save(file,Ver)==false)
		return false;

	if(::Save(file,SCos		)==false)
		return false;
	if(::Save(file,SSin		)==false)
		return false;
	if(::Save(file,MasterCx	)==false)
		return false;
	if(::Save(file,MasterCy	)==false)
		return false;
	if(::Save(file,LMinD	)==false)
		return false;	
	if(::Save(file,LMaxD	)==false)
		return false;	
	if(::Save(file,MinD	)==false)
		return false;	
	if(::Save(file,MaxD	)==false)
		return false;	
	if(::Save(file,ProjectedDataLen	)==false)
		return false;

	if(ProjectedDataLen!=0){
		if(file->write((const char *)ProjectedData,sizeof(double)*ProjectedDataLen)!=sizeof(double)*ProjectedDataLen)
			return false;
		if(file->write((const char *)ProjectedDots,sizeof(int)*ProjectedDataLen)!=sizeof(int)*ProjectedDataLen)
			return false;
	}
	return true;
}
bool    ProjectedInspectionItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPLI::Load(file,LBase)==false)
		return false;

	WORD	Ver;
	if(::Load(file,Ver)==false)
		return false;
	if(::Load(file,SCos		)==false)
		return false;
	if(::Load(file,SSin		)==false)
		return false;
	if(::Load(file,MasterCx	)==false)
		return false;
	if(::Load(file,MasterCy	)==false)
		return false;
	if(::Load(file,LMinD	)==false)
		return false;	
	if(::Load(file,LMaxD	)==false)
		return false;	
	if(::Load(file,MinD	)==false)
		return false;	
	if(::Load(file,MaxD	)==false)
		return false;	
	if(::Load(file,ProjectedDataLen	)==false)
		return false;

	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
		ProjectedData=NULL;
	}
	if(ProjectedDots!=NULL){
		delete	[]ProjectedDots;
		ProjectedDots=NULL;
	}
	if(ProjectedDataLen!=0){
		ProjectedDots=new int	[ProjectedDataLen];
		ProjectedData=new double[ProjectedDataLen];

		if(file->read((char *)ProjectedData,sizeof(double)*ProjectedDataLen)!=sizeof(double)*ProjectedDataLen)
			return false;
		if(file->read((char *)ProjectedDots,sizeof(int)*ProjectedDataLen)!=sizeof(int)*ProjectedDataLen)
			return false;
	}
	return true;
}

void	ProjectedInspectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetParent()->GetLayer()==Layer && GetID()==Data->GetID()){
			ProjectedInspectionInLayer	*Ly=dynamic_cast<ProjectedInspectionInLayer *>(GetParentInLayer());
			UndoElement<ProjectedInspectionInLayer>	*UPointer=new UndoElement<ProjectedInspectionInLayer>(Ly,&ProjectedInspectionInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ProjectedInspectionItem *src=(ProjectedInspectionItem *)Data;
			CopyThresholdOnly(*src);
			SetItemName(src->GetItemName());
			SetLibID(src->GetLibID());
			//CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((ProjectedInspectionItem *)Data)->GetLibID()){
			ProjectedInspectionInLayer	*Ly=dynamic_cast<ProjectedInspectionInLayer *>(GetParentInLayer());
			UndoElement<ProjectedInspectionInLayer>	*UPointer=new UndoElement<ProjectedInspectionInLayer>(Ly,&ProjectedInspectionInLayer::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ProjectedInspectionItem *src=(ProjectedInspectionItem *)Data;
			CopyThresholdOnly(*src);
			SetLibID(src->GetLibID());
			//CenterBright=CalcCenterBright(GetMasterBuff(),0,0);
		}
	}
	else if(Command==SetIndependentItemNameDataCommand_All){
		if(GetLibID()==((ProjectedInspectionItem *)Data)->GetLibID()){
			ProjectedInspectionInLayer	*Ly=dynamic_cast<ProjectedInspectionInLayer *>(GetParentInLayer());
			UndoElement<ProjectedInspectionInLayer>	*UPointer=new UndoElement<ProjectedInspectionInLayer>(Ly,&ProjectedInspectionInLayer::UndoSetIndependentItemNameDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			::Save(UPointer->GetWritePointer(),GetItemName());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			ProjectedInspectionItem *src=(ProjectedInspectionItem *)Data;
			SetItemName(src->GetItemName());
		}
	}
}

void	ProjectedInspectionItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPLI::SetRefereneFrom(src,OffsetX ,OffsetY);
	ProjectedInspectionItem	*ASrc=dynamic_cast<ProjectedInspectionItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((ProjectedInspectionBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
	}
}



double    ProjectedInspectionItem::GetLinePointFoot(double Cx,double Cy ,double px ,double py ,double &X ,double &Y)


/*      点から下ろした直線への足の座標を求める

	直線	SSin*(x-Cx)-SCos*(y-Cy)=0
	(px ,py)に点座標        を入れる

	(X ,Y) に足の座標を入れる
*/
{
	double	t=-(px-Cx)*SSin+(py-Cy)*SCos;

	X=-t*SSin+Cx;
	Y= t*SCos+Cy;

	return t;
}

ExeResult	ProjectedInspectionItem::ExecuteInitialAfterEdit(int ExeID ,int ThreadNo
															,ResultInItemRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPLI::ExecuteInitialAfterEdit	(ExeID ,ThreadNo,Res,EInfo);
	
	int	cx,cy;

	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	const ProjectedInspectionThreshold	*RThr=GetThresholdR();
	SCos	=cos(RThr->Angle*2*M_PI/360.0);
	SSin	=sin(RThr->Angle*2*M_PI/360.0);

	if(ProjectedData!=NULL){
		delete	[]ProjectedData;
	}
	if(BlockVDim!=NULL){
		delete	[]BlockVDim;
	}
	if(ProjectedDots!=NULL){
		delete	[]ProjectedDots;
	}
	if(ProjectedResult!=NULL){
		delete	[]ProjectedResult;
	}
	if(ProjectedSize!=NULL){
		delete	[]ProjectedSize;
	}
	if(ProjectedThreH!=NULL){
		delete	[]ProjectedThreH;
	}
	if(ProjectedThreL!=NULL){
		delete	[]ProjectedThreL;
	}
	if(RThr->CircleMode==true && GetArea().GetShape().Kind==BlockShape::_sRingArc){
		double	sCosS=cos(GetArea().GetShape().Shape.bsRingArc.StartAngle);
		double	sSinS=sin(GetArea().GetShape().Shape.bsRingArc.StartAngle);
		double	eCosS=cos(GetArea().GetShape().Shape.bsRingArc.EndAngle);
		double	eSinS=sin(GetArea().GetShape().Shape.bsRingArc.EndAngle);
		int	Rx=max(GetArea().GetShape().Shape.bsRingArc.Rx1,GetArea().GetShape().Shape.bsRingArc.Rx2);
		int	Ry=max(GetArea().GetShape().Shape.bsRingArc.Ry1,GetArea().GetShape().Shape.bsRingArc.Ry2);
		double	A=((double)Rx)/((double)Ry);
		double	s1=GetSita(sCosS,sSinS*A);
		double	s2=GetSita(eCosS,eSinS*A);
		double	Angle=::DiffSita(s1,s2);
		if(Angle<0.0001){
			Angle=2*M_PI;
		}
		ProjectedDataLen	=(Rx+Ry)*Angle*0.5;

		MasterCx=GetArea().GetShape().Shape.bsRingArc.Cx;
		MasterCy=GetArea().GetShape().Shape.bsRingArc.Cy;
	}
	else if(RThr->CircleMode==true && GetArea().GetShape().Kind==BlockShape::_sRing){
		int	Rx=max(GetArea().GetShape().Shape.bsRing.Rx1,GetArea().GetShape().Shape.bsRing.Rx2);
		int	Ry=max(GetArea().GetShape().Shape.bsRing.Ry1,GetArea().GetShape().Shape.bsRing.Ry2);
		double	A=((double)Rx)/((double)Ry);
		ProjectedDataLen	=(Rx+Ry)*M_PI;

		MasterCx=GetArea().GetShape().Shape.bsRing.Cx;
		MasterCy=GetArea().GetShape().Shape.bsRing.Cy;
	}
	else{
		GetArea().GetCenter(MasterCx,MasterCy);	//(Cx,Cy)を通る傾きAngleの直線	SSin*(x-Cx)-SCos*(y-Cy)=0

		//_CrtCheckMemory();

		MinD=99999999;
		MaxD=-99999999;
		int	N=GetArea().GetFLineLen();
		for(int i=0;i<N;i++){
			int	Y=GetArea().GetFLineAbsY(i);
			int	X1=GetArea().GetFLineLeftX(i);
			int	X2=GetArea().GetFLineRightX(i);
			for(int X=X1;X<X2;X++){
				double mX ,mY;
				double	t=GetLinePointFoot(MasterCx,MasterCy ,X ,Y ,mX ,mY);
				if(t<MinD){
					MinD=t;
				}
				if(MaxD<t){
					MaxD=t;
				}
			}
		}
		LMinD=floor(MinD);
		LMaxD=ceil(MaxD);

		ProjectedDataLen	=LMaxD-LMinD;
	}
	ProjectedDots	=new int	[ProjectedDataLen];
	ProjectedData	=new double	[ProjectedDataLen];
	ProjectedResult	=new BYTE	[ProjectedDataLen];
	ProjectedSize	=new double	[ProjectedDataLen];
	ProjectedThreH	=new double	[ProjectedDataLen];
	ProjectedThreL	=new double	[ProjectedDataLen];
	AllocatedBlockVDimNumb	=10000;
	BlockVDim		=new double[AllocatedBlockVDimNumb];
	return Ret;
}

ExeResult	ProjectedInspectionItem::ExecuteStartByInspection(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	for(int i=0;i<ProjectedDataLen;i++){
		ProjectedData[i]=0.0;
		ProjectedDots[i]=0;
		ProjectedResult[i]=0;
		ProjectedSize[i]=0.0;
	}

	ResetProcessDone();
	return _ER_true;
}

ExeResult	ProjectedInspectionItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	int	mx,my;
	if(AVector!=NULL){
		mx=AVector->ShiftX;
		my=AVector->ShiftY;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}
	const ProjectedInspectionThreshold	*RThr=GetThresholdR();
	ImageBuffer		&IBuff=GetTargetBuff();
	short	Error=1;
	DWORD	Result1=0;
	int	Rx1=0;
	int	Ry1=0;
	int	Rx2=0;
	int	Ry2=0;
	double	StartAngle	=0;
	BlockNumb=(ProjectedDataLen+RThr->EvenLength-1)/RThr->EvenLength;
	if(BlockNumb>AllocatedBlockVDimNumb){
		AllocatedBlockVDimNumb=BlockNumb;
		delete	[]BlockVDim;
		BlockVDim=new double[AllocatedBlockVDimNumb];
	}

	if(RThr->CircleMode==true
	&& (GetArea().GetShape().Kind==BlockShape::_sRingArc || GetArea().GetShape().Kind==BlockShape::_sRing)){
		if(GetArea().GetShape().Kind==BlockShape::_sRingArc){
			Rx1=max(GetArea().GetShape().Shape.bsRingArc.Rx1,GetArea().GetShape().Shape.bsRingArc.Rx2);
			Ry1=max(GetArea().GetShape().Shape.bsRingArc.Ry1,GetArea().GetShape().Shape.bsRingArc.Ry2);
			Rx2=min(GetArea().GetShape().Shape.bsRingArc.Rx1,GetArea().GetShape().Shape.bsRingArc.Rx2);
			Ry2=min(GetArea().GetShape().Shape.bsRingArc.Ry1,GetArea().GetShape().Shape.bsRingArc.Ry2);
			StartAngle	=GetArea().GetShape().Shape.bsRingArc.StartAngle;
		}
		else if(GetArea().GetShape().Kind==BlockShape::_sRing){
			Rx1=max(GetArea().GetShape().Shape.bsRing.Rx1,GetArea().GetShape().Shape.bsRing.Rx2);
			Ry1=max(GetArea().GetShape().Shape.bsRing.Ry1,GetArea().GetShape().Shape.bsRing.Ry2);
			Rx2=min(GetArea().GetShape().Shape.bsRing.Rx1,GetArea().GetShape().Shape.bsRing.Rx2);
			Ry2=min(GetArea().GetShape().Shape.bsRing.Ry1,GetArea().GetShape().Shape.bsRing.Ry2);
		}
		double	LN=min((Rx1-Rx2),(Ry1-Ry2));
		double	ds=RThr->PartialSwingAngle;
		double	H=atan(3.0/LN);
		int	DsNumb=ceil(ds/H);
		if(DsNumb!=0)
			H=ds/DsNumb;

		#pragma omp parallel                             
		{                                                
			#pragma omp for
			for(int B=0;B<BlockNumb;B++){

				double	AvrRing[1000];
				int		AvNumb=0;
				{
					int i=B*RThr->EvenLength+RThr->EvenLength/2;
					if(i>=ProjectedDataLen)
						i=B*RThr->EvenLength;
					double	s=2*((double)i)/((double)(Rx1+Ry1));
					double	a=StartAngle+s;
					double	CosS=cos(a);
					double	SinS=sin(a);
					int	Px1=Rx1*CosS;
					int	Py1=Ry1*SinS;
					int	Px2=Rx2*CosS;
					int	Py2=Ry2*SinS;
					double	L=hypot(Px1-Px2,Py1-Py2);
					
					for(int j=0;j<L && AvNumb<1000;j++,AvNumb++){
						AvrRing[AvNumb]=0;
						int	ANumb=0;
						for(int t=0;t<RThr->EvenLength;t++){
							i=B*RThr->EvenLength+t;
							if(i>=ProjectedDataLen)
								break;
							s=2*((double)i)/((double)(Rx1+Ry1));
							a=StartAngle+s;
							CosS=cos(a);
							SinS=sin(a);

							int	Px=MasterCx+(Rx2+j)*CosS+mx;
							int	Py=MasterCy+(Ry2+j)*SinS+my;
							if(0<=Py && Py<GetMaxLines()
							&& 0<=Px && Px<GetDotPerLine()){
								int	c=IBuff.GetY(Py)[Px];
								AvrRing[AvNumb]+=c;
								ANumb++;
							}
						}
						if(ANumb!=0){
							AvrRing[AvNumb]/=ANumb;
						}
					}
				}
				double	MaxAvrRing=0;
				for(int r=0;r<AvNumb;r++){
					if(MaxAvrRing<AvrRing[r]){
						MaxAvrRing=AvrRing[r];
					}
				}
				if(MaxAvrRing>0){
					for(int r=0;r<AvNumb;r++){
						AvrRing[r]=MaxAvrRing/AvrRing[r];
					}
				}

				double	MaxV=0;
				int		MaxVAngle=0;
				double	MsMaxAdded=0;
				int		MsMinAngle=0;
				double	MsMinV=99999999;
				for(int L=-DsNumb;L<=DsNumb;L++){
					double	g=H*L;
					double	M=0;
					double	MM=0;
					double	MsAddedV=0;
					int	MNumb=0;
					for(int t=0;t<RThr->EvenLength;t++){
						int i=B*RThr->EvenLength+t;
						if(i>=ProjectedDataLen)
							break;
						double	s=2*((double)i)/((double)(Rx1+Ry1));
						double	a=StartAngle+s;
						double	CosS=cos(a);
						double	SinS=sin(a);
						int	Px1=Rx1*CosS;
						int	Py1=Ry1*SinS;
						int	Px2=Rx2*CosS;
						int	Py2=Ry2*SinS;
						
						double	L=hypot(Px1-Px2,Py1-Py2);
						int		Ln=L;
						int		Ln2=Ln/2;
						int		PxCenter=(Px1+Px2)/2;
						int		PyCenter=(Py1+Py2)/2;
						double	pCosS=cos(a+g);
						double	pSinS=sin(a+g);
						double	m=0;
						double	mm=0;
						int		numb=0;
						for(int r=0;r<AvNumb && r<Ln;r++){
							int j=-(Ln-Ln2)+r;
							int	Px=MasterCx+PxCenter+j*pCosS+mx;
							int	Py=MasterCy+PyCenter+j*pSinS+my;
							if(0<=Py && Py<GetMaxLines()
							&& 0<=Px && Px<GetDotPerLine()){
								int	c=IBuff.GetY(Py)[Px]*AvrRing[r];
								m+=c;
								mm+=c*c;
								numb++;
							}
						}
						
						if(numb!=NULL){
							m=m/numb;
							double	MsV=mm/numb-m*m;
							M+=m;
							MM+=m*m;
							MsAddedV+=MsV;
							MNumb++;
						}
					}
					if(MNumb!=0){
						MsAddedV/=MNumb;
						double	V=(MM-M*M/MNumb)/MNumb;
						double	Vs=V/MsAddedV;
						if(MsMaxAdded<Vs){
							MsMaxAdded=Vs;
							MaxV=V;
							MaxVAngle=L;
						}
						if(MsMinV>MsAddedV){
							MsMinV=MsAddedV;
							MsMinAngle=L;
						}
					}
				}
				BlockVDim[B]=sqrt(MaxV);
				double	g=H*MaxVAngle;
				for(int t=0;t<RThr->EvenLength;t++){
					int i=B*RThr->EvenLength+t;
					if(i>=ProjectedDataLen)
						break;
					double	s=2*((double)i)/((double)(Rx1+Ry1));
					double	a=StartAngle+s;
					double	CosS=cos(a);
					double	SinS=sin(a);
					int	Px1=Rx1*CosS;
					int	Py1=Ry1*SinS;
					int	Px2=Rx2*CosS;
					int	Py2=Ry2*SinS;
					
					double	L=hypot(Px1-Px2,Py1-Py2);
					int		Ln=L;
					int		Ln2=Ln/2;
					int		PxCenter=(Px1+Px2)/2;
					int		PyCenter=(Py1+Py2)/2;
					double	pCosS=cos(a+g);
					double	pSinS=sin(a+g);
					double	m=0;
					int		numb=0;
					for(int j=-(Ln-Ln2);j<Ln2;j++){
						int	Px=MasterCx+PxCenter+j*pCosS+mx;
						int	Py=MasterCy+PyCenter+j*pSinS+my;
						if(0<=Py && Py<GetMaxLines()
						&& 0<=Px && Px<GetDotPerLine()){
							ProjectedDots[i]++;
							ProjectedData[i]+=IBuff.GetY(Py)[Px];
						}
					}
				}
			}
		}
		ExecuteAverateTable();
		MakeThreshold();
		ExecuteJudgement();

		for(int i=0;i<ProjectedDataLen;i++){
			if(ProjectedResult[i]>0){
				double	s=2*((double)i)/((double)(Rx1+Ry1));
				double	a=StartAngle+s;

				double	CosS=cos(a);
				double	SinS=sin(a);
				int	Px=(Rx1+Rx2)*CosS/2;
				int	Py=(Ry1+Ry2)*SinS/2;

				ResultPosList	*r=new ResultPosList(MasterCx+Px,MasterCy+Py,0,0);
				r->result		=0x10000;
				r->SetResult(a);
				r->NGSize		=ProjectedSize[i];
				Res->SetAlignedXY(mx,my);
				Res->AddPosList(r);
				Error=2;
			}
		}
	}
	else{
		int	N=GetArea().GetFLineLen();
		for(int i=0;i<N;i++){
			int	Y=GetArea().GetFLineAbsY(i);
			int	iY=Y+my;
			if(iY<0 || GetMaxLines()<=iY){
				continue;
			}
			int	X1=GetArea().GetFLineLeftX(i);
			int	X2=GetArea().GetFLineRightX(i);
			for(int X=X1;X<X2;X++){
				double mX ,mY;
				int	iX=X+mx;
				if(iX<0 || GetDotPerLine()<=iX){
					continue;
				}
				double	t=GetLinePointFoot(MasterCx,MasterCy ,X ,Y ,mX ,mY);
				int	d=t-LMinD;
				if(0<=d && d<ProjectedDataLen){
					ProjectedDots[d]++;
					ProjectedData[d]+=IBuff.GetY(iY)[iX];
				}
			}
		}
		BlockNumb=0;
		ExecuteAverateTable();
		MakeThreshold();
		ExecuteJudgement();

		for(int i=0;i<ProjectedDataLen;i++){
			if(ProjectedResult[i]>0){
				double	tn=i+MinD;
				ResultPosList	*r=new ResultPosList(MasterCx+tn*SCos,MasterCy-tn*SSin,0,0);
				r->result		=0x10000;
				r->SetResult(tn);
				r->NGSize		=ProjectedSize[i];
				Res->SetAlignedXY(mx,my);
				Res->AddPosList(r);
				Error=2;
			}
		}
	}
	Res->SetError(Error);
	Res->SetResult1(Result1);

	SetProcessDone();
	return _ER_true;
}

void	ProjectedInspectionItem::ExecuteAverateTable(void)
{
	for(int i=0;i<ProjectedDataLen;i++){
		if(ProjectedDots[i]!=0){
			ProjectedData [i]=ProjectedData [i]/ProjectedDots[i];
			//ProjectedDataL[i]=ProjectedDataL[i]/ProjectedDots[i];
			//ProjectedDataH[i]=ProjectedDataH[i]/ProjectedDots[i];
		}
	}
}
void	ProjectedInspectionItem::MakeThreshold(void)
{
	const ProjectedInspectionThreshold	*RThr=GetThresholdR();
	if(RThr->UseAbsolute==true){
		for(int i=0;i<ProjectedDataLen;i++){
			ProjectedThreH[i]	=RThr->OKWidthDiffereceH;
			ProjectedThreL[i]	=RThr->OKWidthDiffereceL;
		}
	}
	else{
		int	R=RThr->EvenLength;
		int	i;
		double	AddedD=0;
		for(i=0;i<ProjectedDataLen && i<R;i++){
			int	B=i/RThr->EvenLength;
			double	BAv=0;
			int	BAvNumb=0;
			if(B<BlockNumb){
				BAv=BlockVDim[B];
				BAvNumb++;
			}
			if(0<=B-1 && B-1<BlockNumb){
				BAv+=BlockVDim[B-1];
				BAvNumb++;
			}
			if(B+1<BlockNumb){
				BAv+=BlockVDim[B+1];
				BAvNumb++;
			}
			if(BAvNumb!=0)
				BAv=BAv/BAvNumb;

			AddedD+=ProjectedData[i];

			double	Avr=AddedD/(i+1);
			ProjectedThreH[i]	=Avr+RThr->OKWidthDiffereceH*(1.0+BAv);
			ProjectedThreL[i]	=Avr-RThr->OKWidthDiffereceL*(1.0+BAv);
		}
		if(R<=i){
			for(;i<ProjectedDataLen-R;i++){
				int	B=i/RThr->EvenLength;
				double	BAv=0;
				int	BAvNumb=0;
				if(B<BlockNumb){
					BAv=BlockVDim[B];
					BAvNumb++;
				}
				if(0<=B-1 && B-1<BlockNumb){
					BAv+=BlockVDim[B-1];
					BAvNumb++;
				}
				if(B+1<BlockNumb){
					BAv+=BlockVDim[B+1];
					BAvNumb++;
				}
				if(BAvNumb!=0)
					BAv=BAv/BAvNumb;

				AddedD=0;
				int	AddedN=0;
				for(int j=-R;j<R;j++){
					AddedN++;
					AddedD+=ProjectedData[i+j];
				}
				if(AddedN>0){
					double	Avr=AddedD/AddedN;
					ProjectedThreH[i]	=Avr+RThr->OKWidthDiffereceH*(1.0+BAv);
					ProjectedThreL[i]	=Avr-RThr->OKWidthDiffereceL*(1.0+BAv);
				}
				else{
					ProjectedThreH[i]	=0;
					ProjectedThreL[i]	=0;
				}
			}
			for(;i<ProjectedDataLen;i++){
				int	B=i/RThr->EvenLength;
				double	BAv=0;
				int	BAvNumb=0;
				if(B<BlockNumb){
					BAv=BlockVDim[B];
					BAvNumb++;
				}
				if(0<=B-1 && B-1<BlockNumb){
					BAv+=BlockVDim[B-1];
					BAvNumb++;
				}
				if(B+1<BlockNumb){
					BAv+=BlockVDim[B+1];
					BAvNumb++;
				}
				if(BAvNumb!=0)
					BAv=BAv/BAvNumb;

				AddedD=0;
				int	AddedN=0;
				for(int j=-R;j<R && (i+j)<ProjectedDataLen;j++){
					AddedN++;
					AddedD+=ProjectedData[i+j];
				}
				if(AddedN>0){
					double	Avr=AddedD/AddedN;
					ProjectedThreH[i]	=Avr+RThr->OKWidthDiffereceH*(1.0+BAv);
					ProjectedThreL[i]	=Avr-RThr->OKWidthDiffereceL*(1.0+BAv);
				}
				else{
					ProjectedThreH[i]	=0;
					ProjectedThreL[i]	=0;
				}
			}
		}
	}
}
void	ProjectedInspectionItem::ExecuteJudgement(void)
{
	const ProjectedInspectionThreshold	*RThr=GetThresholdR();
	for(int i=0;i<ProjectedDataLen;i++){
		if(ProjectedData[i]>=ProjectedThreH[i]){
			int	j;
			for(j=i+1;j<ProjectedDataLen;j++){
				if(ProjectedData[j]<ProjectedThreH[j]){
					int	DLen=j-i;
					if(DLen>=RThr->TransitWidth){
						ProjectedResult[i]=1;
						ProjectedSize[i]=DLen;
						break;
					}
				}
			}
			i=j;
		}
	}
	for(int i=0;i<ProjectedDataLen;i++){
		if(ProjectedData[i]<=ProjectedThreL[i]){
			int	j;
			for(j=i+1;j<ProjectedDataLen;j++){
				if(ProjectedData[j]>ProjectedThreL[j]){
					int	DLen=j-i;
					if(DLen>=RThr->TransitWidth){
						ProjectedResult[i]=2;
						ProjectedSize[i]=DLen;
						break;
					}
				}
			}
			i=j;
		}
	}
}

void	ProjectedInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ProjectedInspectionDrawAttr	*BAttr=dynamic_cast<ProjectedInspectionDrawAttr *>(Attr);
	if(BAttr!=NULL){
		ProjectedInspectionDrawAttr	TmpAttr(GetLayersBase());
		TmpAttr=*BAttr;
		AlgorithmItemPLI::DrawArea(GetArea(),pnt, movx ,movy ,ZoomRate ,&TmpAttr);
	}
	else{
		AlgorithmItemPLI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
void	ProjectedInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		if(Res->IsOk()==false || OnlyNG==false){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY()
							,&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
			if(Res->IsOk()==false && ZoomRate>1.0){
				int	cx,cy;
				GetArea().GetCenter(cx,cy);
				int	kx=(cx+MovX)*ZoomRate;
				int	ky=(cy+MovY)*ZoomRate;
				if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
					QRect	rect(0,0,IData.width(),IData.height());
					PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
						,Qt::AlignLeft | Qt::AlignTop
						//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
						,GetParamGlobal()->GetLayerName((int)GetParent()->GetLayer())
						+QString(/**/" Sft(")+QString::number((int)Res->GetTotalShiftedX())+QString(/**/",")+QString::number((int)Res->GetTotalShiftedY())+QString(/**/")")
						+QString(/**/" ID:")+QString::number((int)GetID())
						,&rect);
					if(Res->GetError()==2){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"N: L=")+QString::number(Res->GetResult1()) +QString(/**/" H=")+QString::number(Res->GetResult2())
							,&rect);
					}
					else if(Res->GetError()==3){
						PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							,QString(/**/"B: L=")+QString::number(Res->GetResult1()) +QString(/**/" H=")+QString::number(Res->GetResult2())
							,&rect);
					}
				}
			}
		}
		const ProjectedInspectionThreshold	*RThr=GetThresholdR();
		if(RThr->CircleMode==false){
			int	Cx,Cy;
			GetArea().GetCenter(Cx,Cy);
			Cx+=Res->GetTotalShiftedX();
			Cy+=Res->GetTotalShiftedY();
			int	W=GetArea().GetWidth();
			int	H=GetArea().GetHeight();
			QPen	Pen(Qt::yellow);
			Pen.setWidth(3);
			PData.setPen(Pen);
			PjDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
						,Cx-ProjectedDataLen/2,Cy+H/2
						,Cx+ProjectedDataLen/2,Cy+H/2);
			PjDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
						,Cx-ProjectedDataLen/2,Cy+H/2
						,Cx-ProjectedDataLen/2,Cy+H/2-128);
			Pen.setWidth(1);
			PData.setPen(Pen);
			for(int y=10;y<128;y+=10){
				PjDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
							,Cx-ProjectedDataLen/2  ,Cy+H/2-y
							,Cx-ProjectedDataLen/2+7,Cy+H/2-y);
			}
			PData.setPen(Qt::green);
			int	Len=ProjectedDataLen*ZoomRate;
			int	LastYPos=ProjectedData[0];
			for(int x=1;x<Len;x++){
				int	i=x/ZoomRate;
				if(i>=ProjectedDataLen)
					break;
				int	YPos=ProjectedData[i];
				PjDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
							,Cx-ProjectedDataLen/2+(x-1)/ZoomRate,Cy+H/2-LastYPos
							,Cx-ProjectedDataLen/2+x/ZoomRate	 ,Cy+H/2-YPos);
				LastYPos=YPos;
			}
			PData.setPen(Qt::red);
			LastYPos=ProjectedThreH[0];
			for(int x=1;x<Len;x++){
				int	i=x/ZoomRate;
				if(i>=ProjectedDataLen)
					break;
				int	YPos=ProjectedThreH[i];
				PjDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
							,Cx-ProjectedDataLen/2+(x-1)/ZoomRate,Cy+H/2-LastYPos
							,Cx-ProjectedDataLen/2+x/ZoomRate	 ,Cy+H/2-YPos);
				LastYPos=YPos;
			}

			PData.setPen(Qt::darkRed);
			LastYPos=ProjectedThreL[0];
			for(int x=1;x<Len;x++){
				int	i=x/ZoomRate;
				if(i>=ProjectedDataLen)
					break;
				int	YPos=ProjectedThreL[i];
				PjDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
							,Cx-ProjectedDataLen/2+(x-1)/ZoomRate,Cy+H/2-LastYPos
							,Cx-ProjectedDataLen/2+x/ZoomRate	 ,Cy+H/2-YPos);
				LastYPos=YPos;
			}
		}
		else{
			double	StartAngle;
			double	EndAngle;
			int	Rx1=0;
			int	Ry1=0;
			int	Rx2=0;
			int	Ry2=0;
			if(GetArea().GetShape().Kind==BlockShape::_sRingArc){
				StartAngle	=GetArea().GetShape().Shape.bsRingArc.StartAngle;
				EndAngle	=GetArea().GetShape().Shape.bsRingArc.EndAngle;
				Rx1=max(GetArea().GetShape().Shape.bsRingArc.Rx1,GetArea().GetShape().Shape.bsRingArc.Rx2);
				Ry1=max(GetArea().GetShape().Shape.bsRingArc.Ry1,GetArea().GetShape().Shape.bsRingArc.Ry2);
				Rx2=min(GetArea().GetShape().Shape.bsRingArc.Rx1,GetArea().GetShape().Shape.bsRingArc.Rx2);
				Ry2=min(GetArea().GetShape().Shape.bsRingArc.Ry1,GetArea().GetShape().Shape.bsRingArc.Ry2);
			}
			else if(GetArea().GetShape().Kind==BlockShape::_sRing){
				StartAngle	=0;
				EndAngle	=2*M_PI;
				Rx1=max(GetArea().GetShape().Shape.bsRing.Rx1,GetArea().GetShape().Shape.bsRing.Rx2);
				Ry1=max(GetArea().GetShape().Shape.bsRing.Ry1,GetArea().GetShape().Shape.bsRing.Ry2);
				Rx2=min(GetArea().GetShape().Shape.bsRing.Rx1,GetArea().GetShape().Shape.bsRing.Rx2);
				Ry2=min(GetArea().GetShape().Shape.bsRing.Ry1,GetArea().GetShape().Shape.bsRing.Ry2);
			}
			double	Angle=::DiffSita(StartAngle,EndAngle);
			if(Angle<0.0001){
				Angle=2*M_PI;
			}
			int	RxN=Rx1+10;
			int	RyN=Ry1+10;
			double	CosS=cos(StartAngle);
			double	SinS=sin(StartAngle);

			int	Cx,Cy;
			Cx=MasterCx+Res->GetTotalShiftedX();
			Cy=MasterCy+Res->GetTotalShiftedY();

			QPen	Pen(Qt::yellow);
			Pen.setWidth(3);
			PData.setPen(Pen);
			NDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
						,Cx+RxN*CosS		,Cy+RyN*SinS
						,Cx+(RxN+128)*CosS	,Cy+(RyN+128)*SinS);

			double	ms=2*M_PI-EndAngle;
			double	SpanAngle=Angle*16*360/(2*M_PI);
			PData.drawArc((Cx-RxN+MovX)*ZoomRate,(Cy-RyN+MovY)*ZoomRate ,2*RxN*ZoomRate,2*RyN*ZoomRate
						,ms*16*360/(2*M_PI)
						,SpanAngle);

			Pen.setWidth(1);
			PData.setPen(Pen);
			for(int y=10;y<128;y+=10){
				double	Ax=Cx+(RxN+y)*CosS;
				double	Ay=Cy+(RyN+y)*SinS;
				if(y==50 || y==100){
					NDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
							,Ax-15*SinS	,Ay+15*CosS
							,Ax+15*SinS	,Ay-15*CosS);
				}
				else{
					NDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
							,Ax-10*SinS	,Ay+10*CosS
							,Ax+10*SinS	,Ay-10*CosS);
				}
			}

			PData.setPen(Qt::green);
			int	Len=ProjectedDataLen*ZoomRate;
			double	LastTx=0;
			double	LastTy=0;
			for(int x=0;x<Len;x++){
				int	i=x/ZoomRate;
				if(i>=ProjectedDataLen)
					break;
				double	s=2*((double)i)/((double)(Rx1+Ry1));
				double	a=StartAngle+s;
				double	aCosS=cos(a);
				double	aSinS=sin(a);
				double	YPos=ProjectedData[i]/2;
				double	tx=Cx+(RxN+YPos)*aCosS;
				double	ty=Cy+(RyN+YPos)*aSinS;
				if(x!=0){
					NDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
								,tx,ty ,LastTx,LastTy);
				}
				LastTx=tx;
				LastTy=ty;
			}
			PData.setPen(Qt::red);
			for(int x=0;x<Len;x++){
				int	i=x/ZoomRate;
				if(i>=ProjectedDataLen)
					break;
				double	s=2*((double)i)/((double)(Rx1+Ry1));
				double	a=StartAngle+s;
				double	aCosS=cos(a);
				double	aSinS=sin(a);
				double	YPos=ProjectedThreH[i]/2;
				double	tx=Cx+(RxN+YPos)*aCosS;
				double	ty=Cy+(RyN+YPos)*aSinS;
				if(x!=0){
					NDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
								,tx,ty ,LastTx,LastTy);
				}
				LastTx=tx;
				LastTy=ty;
			}

			PData.setPen(Qt::darkRed);
			for(int x=0;x<Len;x++){
				int	i=x/ZoomRate;
				if(i>=ProjectedDataLen)
					break;
				double	s=2*((double)i)/((double)(Rx1+Ry1));
				double	a=StartAngle+s;
				double	aCosS=cos(a);
				double	aSinS=sin(a);
				double	YPos=ProjectedThreL[i]/2;
				double	tx=Cx+(RxN+YPos)*aCosS;
				double	ty=Cy+(RyN+YPos)*aSinS;
				if(x!=0){
					NDrawLine(*Res,PData ,MovX ,MovY ,ZoomRate
								,tx,ty ,LastTx,LastTy);
				}
				LastTx=tx;
				LastTy=ty;
			}
		}
	}
}
void	ProjectedInspectionItem::PjDrawLine(ResultInItemRoot &Res,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,int x1, int y1 ,int x2, int y2)
{
	int	Cx,Cy;
	GetArea().GetCenter(Cx,Cy);
	Cx+=Res.GetTotalShiftedX();
	Cy+=Res.GetTotalShiftedY();
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();

	int	X1= (x1-Cx)*SCos+(y1-Cy)*SSin+Cx;
	int	Y1=-(x1-Cx)*SSin+(y1-Cy)*SCos+Cy;
	int	X2= (x2-Cx)*SCos+(y2-Cy)*SSin+Cx;
	int	Y2=-(x2-Cx)*SSin+(y2-Cy)*SCos+Cy;
	PData.drawLine((X1+MovX)*ZoomRate,(Y1+MovY)*ZoomRate
				  ,(X2+MovX)*ZoomRate,(Y2+MovY)*ZoomRate);
}

void	ProjectedInspectionItem::NDrawLine(ResultInItemRoot &Res,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,double x1, double y1 ,double x2, double y2)
{
	PData.drawLine((x1+MovX)*ZoomRate,(y1+MovY)*ZoomRate
				  ,(x2+MovX)*ZoomRate,(y2+MovY)*ZoomRate);
}