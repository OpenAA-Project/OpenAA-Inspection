#include "XShiftMark.h"
#include "XDLLOnly.h"
//#include "XGUI.h"
#include "XPointer.h"
#include "XShiftMarkLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XPieceArchitect.h"
#include "XShiftMarkAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XDrawFunc.h"
#include "XCrossObj.h"
#include "XColorSpace.h"

extern	const	char	*sRoot;
extern	const	char	*sName;

ShiftMarkThreshold::ShiftMarkThreshold(ShiftMarkItem *parent)
:AlgorithmThreshold(parent)
{
	SearchDotEdge	=40;
	SearchDotMarkMin=200;
	SearchDotMarkMax=200;
	NGByLosingMark	=true;
	ThresholdLost	=60;
	EnableMark		=true;
	ColorMatch		=true;
}

void	ShiftMarkThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const ShiftMarkThreshold *s=(const ShiftMarkThreshold *)&src;
	SearchDotEdge	=s->SearchDotEdge	;
	SearchDotMarkMin=s->SearchDotMarkMin;
	SearchDotMarkMax=s->SearchDotMarkMax;
	NGByLosingMark	=s->NGByLosingMark	;
	ThresholdLost	=s->ThresholdLost	;
	EnableMark		=s->EnableMark;
	ColorMatch		=s->ColorMatch;
}
bool	ShiftMarkThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const ShiftMarkThreshold *s=(const ShiftMarkThreshold *)&src;
	if(SearchDotEdge	!=s->SearchDotEdge	)	return false;
	if(SearchDotMarkMin	!=s->SearchDotMarkMin)	return false;
	if(SearchDotMarkMax	!=s->SearchDotMarkMax)	return false;
	if(NGByLosingMark	!=s->NGByLosingMark	)	return false;
	if(ThresholdLost	!=s->ThresholdLost	)	return false;
	if(EnableMark		!=s->EnableMark		)	return false;
	if(ColorMatch		!=s->ColorMatch		)	return false;

	return true;
}
bool	ShiftMarkThreshold::Save(QIODevice *f)
{
	WORD	Ver=ShiftMarkVersion;

	if(::Save(f,Ver)==false)
		return false;

	if(::Save(f,SearchDotEdge)==false)
		return false;
	if(::Save(f,SearchDotMarkMin)==false)
		return false;
	if(::Save(f,SearchDotMarkMax)==false)
		return false;
	if(::Save(f,NGByLosingMark)==false)
		return false;
	if(::Save(f,ThresholdLost)==false)
		return false;
	if(::Save(f,EnableMark)==false)
		return false;
	if(::Save(f,ColorMatch)==false)
		return false;

	return true;
}

bool	ShiftMarkThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return false;

	if(::Load(f,SearchDotEdge)==false)
		return false;
	if(Ver<3){
		SearchDotMarkMin=0;
		if(::Load(f,SearchDotMarkMax)==false)
			return false;
	}
	else{
		if(::Load(f,SearchDotMarkMin)==false)
			return false;
		if(::Load(f,SearchDotMarkMax)==false)
			return false;
	}
	if(::Load(f,NGByLosingMark)==false)
		return false;
	if(::Load(f,ThresholdLost)==false)
		return false;
	if(Ver>=5){
		if(::Load(f,EnableMark)==false)
			return false;
		if(::Load(f,ColorMatch)==false)
			return false;
	}
	else{
		EnableMark=true;
		ColorMatch=true;
	}

	return true;
}

void	ShiftMarkThreshold::FromLibrary(AlgorithmLibrary *src)
{
	ShiftMarkLibrary	*LSrc=dynamic_cast<ShiftMarkLibrary *>(src);
	if(LSrc==NULL)
		return;

	SearchDotEdge	=LSrc->SearchDotEdge	;
	SearchDotMarkMin=LSrc->SearchDotMarkMin	;
	SearchDotMarkMax=LSrc->SearchDotMarkMax	;	
	NGByLosingMark	=LSrc->NGByLosingMark	;
	ThresholdLost	=LSrc->ThresholdLost	;
	EnableMark		=LSrc->EnableMark		;
	ColorMatch		=LSrc->ColorMatch		;
}
void	ShiftMarkThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	ShiftMarkLibrary	*LDst=dynamic_cast<ShiftMarkLibrary *>(Dest);
	if(LDst==NULL)
		return;

	LDst->SearchDotEdge		=SearchDotEdge		;
	LDst->SearchDotMarkMin	=SearchDotMarkMin	;
	LDst->SearchDotMarkMax	=SearchDotMarkMax	;
	LDst->NGByLosingMark	=NGByLosingMark		;
	LDst->ThresholdLost		=ThresholdLost		;
	LDst->EnableMark		=EnableMark			;
	LDst->ColorMatch		=ColorMatch			;
}

//===========================================================================================
ShiftMarkItem::ShiftMarkItem(void)
{
	EdgeVector=NULL;
	MarkVector=NULL;
	MarkDistance=0;
}

ShiftMarkItem::~ShiftMarkItem(void)
{
}

ShiftMarkItem &ShiftMarkItem::operator=(const AlgorithmItemRoot &src)
{
	AlgorithmItemPI::operator=(src);
	CopyThreshold(*((ShiftMarkItem *)&src));

	const ShiftMarkItem	*ASrc=dynamic_cast<const ShiftMarkItem *>(&src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((ShiftMarkBase *)GetParentBase())->OmitZoneDot;
		EdgePoint	=ASrc->EdgePoint;
		MarkPoint	=ASrc->MarkPoint;
	}
	return *this;
}
VectorLineBase	*ShiftMarkItem::CreateVectorBase(void)
{
	VectorLineDouble	*R=new VectorLineDouble();
	R->AppendItemBase(R->CreateItem());
	R->AppendItemBase(R->CreateItem());
	return R;
}

void	ShiftMarkItem::CopyThreshold(ShiftMarkItem &src)
{
	GetThresholdW()->CopyFrom(*((ShiftMarkThreshold *)src.GetThresholdR()));
}

void	ShiftMarkItem::CopyThresholdOnly(ShiftMarkItem &src)
{
	GetThresholdW()->CopyFrom(*((ShiftMarkThreshold *)src.GetThresholdR()));
}

bool    ShiftMarkItem::Save(QIODevice *file)
{
	if(AlgorithmItemPI::Save(file)==false)
		return false;

	if(EdgePoint.Save(file)==false)
		return false;
	if(MarkPoint.Save(file)==false)
		return false;

	if(EdgeArea.Save(file)==false)
		return false;
	if(MarkArea.Save(file)==false)
		return false;
	return true;
}
bool    ShiftMarkItem::Load(QIODevice *file,LayersBase *LBase)
{
	if(AlgorithmItemPI::Load(file,LBase)==false)
		return false;

	if(EdgePoint.Load(file)==false)
		return false;
	if(MarkPoint.Load(file)==false)
		return false;
	
	if(GetLoadedVersion()>=4){
		if(EdgeArea.Load(file)==false)
			return false;
		if(MarkArea.Load(file)==false)
			return false;

		ImageBuffer *MasterImageList[1000];
		GetMasterBuffList(MasterImageList);
		MatchMovePoint(false,MasterImageList);
	}
	return true;
}

void	ShiftMarkItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndepenShiftMarkItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			CopyThresholdOnly(*((ShiftMarkItem *)Data));
		}
	}
	else if(Command==SetIndepenShiftMarkItemDataCommand_All){
		if(GetLibID()==((ShiftMarkItem *)Data)->GetLibID()){
			CopyThresholdOnly(*((ShiftMarkItem *)Data));
		}
	}
	//else if(Command==SetIndepenShiftMarkItemNameDataCommand_All){
	//	if(GetLibID()==((ShiftMarkItem *)Data)->GetLibID()){
	//		ShiftMarkInPage	*Ly=dynamic_cast<ShiftMarkInPage *>(GetParentInPage());
	//		UndoElement<ShiftMarkInPage>	*UPointer=new UndoElement<ShiftMarkInPage>(Ly,&ShiftMarkInPage::UndoSetIndependentItemNameDataCommand);
	//		::Save(UPointer->GetWritePointer(),GetID());
	//		::Save(UPointer->GetWritePointer(),GetItemName());
	//		GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);
	//
	//		ShiftMarkItem *src=(ShiftMarkItem *)Data;
	//		SetItemName(src->GetItemName());
	//	}
	//}
}

void	ShiftMarkItem::SetRefereneFrom(AlgorithmItemRoot *src,int OffsetX ,int OffsetY)
{
	AlgorithmItemPI::SetRefereneFrom(src,OffsetX ,OffsetY);
	ShiftMarkItem	*ASrc=dynamic_cast<ShiftMarkItem *>(src);
	if(ASrc!=NULL){
		int	OmitZoneDot=((ShiftMarkBase *)GetParentBase())->OmitZoneDot;
		GetArea()	.ClipArea(OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		
		ASrc->InitialEdgeMark();	
		EdgePoint	=ASrc->EdgePoint;
		MarkPoint	=ASrc->MarkPoint;
		//EdgePoint.MoveToClip(OffsetX,OffsetY
		//					,OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
		//MarkPoint.MoveToClip(OffsetX,OffsetY
		//					,OmitZoneDot,OmitZoneDot,GetDotPerLine()-OmitZoneDot,GetMaxLines()-OmitZoneDot);
	
		EdgeArea=ASrc->EdgeArea;
		MarkArea=ASrc->MarkArea;
		//EdgeArea.MoveTo(OffsetX,OffsetY);
		//MarkArea.MoveTo(OffsetX,OffsetY);

		ImageBuffer *MasterImageList[1000];
		GetTargetBuffList(MasterImageList);
		if(MatchMovePoint(true,MasterImageList)==true){
			EdgePoint.MoveToNoClip(OffsetX,OffsetY);
			MarkPoint.MoveToNoClip(OffsetX,OffsetY);
		}
	}
}

bool	ShiftMarkItem::MatchMovePoint(bool UseAlignment,ImageBuffer *ImageList[])
{
	int	mex=0,mey=0;
	double	eRotation=0;
	int	mmx=0,mmy=0;
	double	mRotation=0;
	if(UseAlignment==true){
		AlignmentPacket2D	V;
		int	cx,cy;
		EdgePoint.GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mex=V.ShiftX;
		mey=V.ShiftY;
		eRotation=V.Rotation;
	}
	if(UseAlignment==true){
		AlignmentPacket2D	V;
		int	cx,cy;
		MarkPoint.GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mmx=V.ShiftX;
		mmy=V.ShiftY;
		mRotation=V.Rotation;
	}

	int	ItemDx=0,ItemDy=0;
	if(UseAlignment==true){
		AlignmentPacket2D	V;
		int	cx,cy;
		GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		ItemDx=V.ShiftX;
		ItemDy=V.ShiftY;
		mRotation=V.Rotation;
	}

	double	MinD=99999999;
	FlexAreaColorRotatedImage *MinE=NULL;
	for(FlexAreaColorRotatedImage *e=EdgeArea.GetFirst();e!=NULL;e=e->GetNext()){
		double	d=fabs(e->GetAngleRadian()-eRotation);
		if(d<MinD){
			MinD=d;
			MinE=e;
		}
	}
	MinD=99999999;
	FlexAreaColorRotatedImage *MinM=NULL;
	for(FlexAreaColorRotatedImage *m=MarkArea.GetFirst();m!=NULL;m=m->GetNext()){
		double	d=fabs(m->GetAngleRadian()-mRotation);
		if(d<MinD){
			MinD=d;
			MinM=m;
		}
	}
	VectorLineBase	*L=GetVector();
	if(MinE!=NULL && MinM!=NULL && L!=NULL){
		VectorItemBase	*p1=L->GetFirstItem();
		VectorItemBase	*p2=L->GetLastItem();
		double	x1=p1->GetX();
		double	y1=p1->GetY();
		double	x2=p2->GetX();
		double	y2=p2->GetY();
		double	Len=hypot(x2-x1,y2-y1);
		if(Len>0){
			const	ShiftMarkThreshold	*RThr=GetThresholdR();

			double	Vx=-(y2-y1)/Len;
			double	Vy= (x2-x1)/Len;

			double	Vex=Vx*cos(eRotation)-Vy*sin(eRotation);
			double	Vey=Vx*sin(eRotation)+Vy*cos(eRotation);

			int	SearchDotEdge=RThr->SearchDotEdge;

			double	MaxD=0;
			int		MEPosLen=0;
			int		EDx=0;
			int		EDy=0;

			for(int L=-SearchDotEdge;L<=SearchDotEdge;L++){
				int	dx=Vex*L;
				int	dy=Vey*L;

				double	D=MinE->GetCoef(mex+dx ,mey+dy ,ImageList ,GetLayerNumb(),true);
				if(D>MaxD){
					EDx=mex+dx;
					EDy=mey+dy;
					MaxD=D;
				}
			}
			EdgePoint.MoveToNoClip(EDx-ItemDx,EDy-ItemDy);

			int	MinSearch=hypot(MarkPoint.GetWidth(),MarkPoint.GetHeight());
			int	SearchDotMark=RThr->SearchDotMarkMax;
			double	Vmx=Vx*cos(mRotation)-Vy*sin(mRotation);
			double	Vmy=Vx*sin(mRotation)+Vy*cos(mRotation);
			ResultMatchMark=0;
			double	ThresholdLost=RThr->ThresholdLost/100.0;
			double	CurrentMPos=-1;
			bool	FoundMark=false;
			int		MDx=0;
			int		MDy=0;
			for(int L=-MinSearch;L<=SearchDotMark;L++){
				int	dx=Vmx*(L+MEPosLen);
				int	dy=Vmy*(L+MEPosLen);

				double	D=MinM->GetCoef(mex+dx ,mey+dy ,ImageList ,GetLayerNumb(),true);
				if(D>ResultMatchMark){
					MDx=mex+dx;
					MDy=mey+dy;
					ResultMatchMark=D;
					CurrentMPos=L;						
				}
			}
			MarkPoint.MoveToNoClip(MDx-ItemDx,MDy-ItemDy);
			InitialEdgeMark();
			return true;
		}
	}
	return false;
}
void	ShiftMarkItem::MasterImageHasChanged(void)
{

}
void	ShiftMarkItem::CopyArea(ShiftMarkItem &src)
{
	SetVector(src.GetVector());
	EdgePoint=src.EdgePoint;
	MarkPoint=src.MarkPoint;
}

static	int	Mergin=8;

ExeResult	ShiftMarkItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
												,ResultInItemRoot *Res
												,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID ,ThreadNo,Res,EInfo);

	int	ecx,ecy;
	EdgePoint.GetCenter(ecx,ecy);
	EdgeVector=(AlignmentPacket2D *)GetAlignmentPointer(ecx,ecy);
	if(EdgeVector!=NULL){
		EdgeVector->Set(this);
	}
	int	mcx,mcy;
	MarkPoint.GetCenter(mcx,mcy);
	MarkVector=(AlignmentPacket2D *)GetAlignmentPointer(mcx,mcy,false);
	if(MarkVector!=NULL){
		MarkVector->Set(this);
	}
	InitialEdgeMark();

	ImageBuffer *ImageList[1000];
	GetMasterBuffList(ImageList);
	MoveCenterPosition(0,0,0,0,ImageList);
	//InitialEdgeMark();

	ImagePointerContainer MasterImageList;
	GetMasterBuffList(MasterImageList);
	MarkColor	=GetMarkEdgePointColor(MarkPoint,MasterImageList
									,0,0,-3);
	PaperColor	=GetMarkEdgePointColor(MarkPoint,MasterImageList
									,0,0,3);
	BackColor	=GetMarkEdgePointColor(EdgePoint,MasterImageList
									,0,0,-5);

	if(Ret!=_ER_true){
		return Ret;
	}
	return _ER_true;
}

void	ShiftMarkItem::InitialEdgeMark(void)
{

	ImageBuffer *MasterImageList[1000];
	GetMasterBuffList(MasterImageList);
	ShiftMarkBase	*ABase=tGetParentBase();

	double	MaxAngleRadian=ABase->MaxRotationDegree/360.0*2*M_PI;
	int		ELen=max(EdgePoint.GetWidth(),EdgePoint.GetHeight());
	int		MLen=max(MarkPoint.GetWidth(),MarkPoint.GetHeight());

	int	MaxPointLen=max(ELen,MLen);
	double	DivRadian=2.5/(double)MaxPointLen;
	int	AngleCount=2*MaxAngleRadian/DivRadian+1;

	EdgeArea.RemoveAll();
	MarkArea.RemoveAll();
	for(int i=0;i<AngleCount;i++){
		FlexAreaColorRotatedImage	*E=new FlexAreaColorRotatedImage();
		E->Set(EdgePoint,MasterImageList 
						,-MaxAngleRadian+DivRadian*i
						,GetLayerNumb());
		E->InitialCoef();
		EdgeArea.AppendList(E);

		FlexAreaColorRotatedImage	*M=new FlexAreaColorRotatedImage();
		M->Set(MarkPoint,MasterImageList 
						,-MaxAngleRadian+DivRadian*i
						,GetLayerNumb());
		M->InitialCoef();
		MarkArea.AppendList(M);
	}

	int	Cx,Cy;
	MarkPoint.GetCenter(Cx,Cy);
	VectorLineBase	*L=GetVector();
	if(L!=NULL){
		VectorItemBase	*p1=L->GetFirstItem();
		VectorItemBase	*p2=L->GetLastItem();
		double	x1=p1->GetX();
		double	y1=p1->GetY();
		double	x2=p2->GetX();
		double	y2=p2->GetY();
		double	Len=hypot(x2-x1,y2-y1);
		if(Len>0){
			double	Hx=x2-x1;
			double	Hy=y2-y1;
			double	Vx=-Hy/Len;
			double	Vy=Hx/Len;
			double	Px,Py;
			EdgePoint.GetCenter(Px,Py);
			double	Qx,Qy;
			MarkPoint.GetCenter(Qx,Qy);
			double	M=Vx*Hy-Vy*Hx;
			if(fabs(M)>0){
				double	BLen=((Qx-Px)*Hy-(Qy-Py)*Hx)/M;
				MarkDistance=fabs(BLen);
			}
			else{
				MarkDistance	=::GetLengthLine2Point(x1,y1,x2,y2 ,(double)Cx,(double)Cy);
			}
		}
	}
}

int	DbgID=7036;
int	DbgLayer=1;
int	DbgNumer=0;

static	int	DbgY=4132;

QColor	ShiftMarkItem::GetMarkEdgePointColor(FlexArea &PointArea,ImagePointerContainer &ImageList
											,int dx,int dy ,double Vt)
{
	int	cx,cy;
	PointArea.GetCenter(cx,cy);
	int	W=PointArea.GetWidth();
	int	H=PointArea.GetHeight();
	int	AreaLen=hypot(W,H)/2;

	VectorLineBase	*L=GetVector();
	if(L!=NULL){
		VectorItemBase	*p1=L->GetFirstItem();
		VectorItemBase	*p2=L->GetLastItem();
		double	x1=p1->GetX();
		double	y1=p1->GetY();
		double	x2=p2->GetX();
		double	y2=p2->GetY();
		double	Len=hypot(x2-x1,y2-y1);

		if(Len>0){
			double	Hx=(x2-x1)/Len;
			double	Hy=(y2-y1)/Len;
			double	Vx=-Hy;
			double	Vy=Hx;

			int	SumR=0;
			int	SumG=0;
			int	SumB=0;
			int	N=0;
			for(int k=-AreaLen;k<=AreaLen;k++){
				int	px=cx+Hx*k+Vx*Vt+dx;
				int	py=cy+Hy*k+Vy*Vt+dy;
				QRgb	d=ImageList.GetColorRgb(px ,py);
				SumR+=qRed	(d);
				SumG+=qGreen(d);
				SumB+=qBlue	(d);
				N++;
			}
			return QColor(SumR/N,SumG/N,SumB/N);
		}
	}
	return Qt::black;
}

static	double	GetColorDistance(const QColor &d1,const QColor &d2)
{
	int	dR=d1.red()-d2.red();
	int	dG=d1.green()-d2.green();
	int	dB=d1.blue()-d2.blue();
	return sqrt(dR*dR+dG*dG+dB*dB);
}

ExeResult	ShiftMarkItem::ExecuteProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	AlgorithmItemPI::ExecutePreProcessing	(ExeID ,ThreadNo,Res);

	if(GetID()==DbgID)
		DbgNumer++;

	if(CanBeProcessing()==false)
		return _ER_ReqRetryLater;

	int	mex,mey;
	double	eRotation=0;
	int	mmx,mmy;
	double	mRotation=0;
	if(EdgeVector!=NULL){
		mex		=EdgeVector->ShiftX;
		mey		=EdgeVector->ShiftY;
		eRotation=EdgeVector->Rotation;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		EdgePoint.GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mex=V.ShiftX;
		mey=V.ShiftY;
		eRotation=V.Rotation;
	}
	if(MarkVector!=NULL){
		mmx		=MarkVector->ShiftX;
		mmy		=MarkVector->ShiftY;
		mRotation=MarkVector->Rotation;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		MarkPoint.GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mmx=V.ShiftX;
		mmy=V.ShiftY;
		mRotation=V.Rotation;
	}

	ShiftMarkBase	*ABase	=tGetParentBase();
	double	tRotation=0;
	if(fabs(eRotation)>=fabs(mRotation)){
		tRotation=eRotation;
	}
	else{
		tRotation=mRotation;
	}

	double	MinD=99999999;
	FlexAreaColorRotatedImage *MinE=NULL;
	for(FlexAreaColorRotatedImage *e=EdgeArea.GetFirst();e!=NULL;e=e->GetNext()){
		double	d=fabs(e->GetAngleRadian()-tRotation);
		if(d<MinD){
			MinD=d;
			MinE=e;
		}
	}
	MinD=99999999;
	FlexAreaColorRotatedImage *MinM=NULL;
	for(FlexAreaColorRotatedImage *m=MarkArea.GetFirst();m!=NULL;m=m->GetNext()){
		double	d=fabs(m->GetAngleRadian()-tRotation);
		if(d<MinD){
			MinD=d;
			MinM=m;
		}
	}
	VectorLineBase	*L=GetVector();
	if(MinE!=NULL && MinM!=NULL && L!=NULL){
		VectorItemBase	*p1=L->GetFirstItem();
		VectorItemBase	*p2=L->GetLastItem();
		double	x1=p1->GetX();
		double	y1=p1->GetY();
		double	x2=p2->GetX();
		double	y2=p2->GetY();
		double	Len=hypot(x2-x1,y2-y1);
		if(Len>0){
			const	ShiftMarkThreshold	*RThr=GetThresholdR();
			if(RThr->EnableMark==true){
				ImageBuffer *TargetImageList[1000];
				GetTargetBuffList(TargetImageList);

				double	Vx=-(y2-y1)/Len;
				double	Vy= (x2-x1)/Len;

				double	Vex=Vx*cos(tRotation)-Vy*sin(tRotation);
				double	Vey=Vx*sin(tRotation)+Vy*cos(tRotation);

				int	SearchDotEdge=RThr->SearchDotEdge;

				double	MaxD=0;
				int		MEPosLen=0;

				for(int L=-SearchDotEdge;L<=SearchDotEdge;L++){
					int	dx=Vex*L;
					int	dy=Vey*L;

					//double	D=MinE->GetCoef(mex+dx ,mey+dy ,TargetImageList ,GetLayerNumb(),true);
					double	D=MinE->GetVar(mex+dx ,mey+dy ,TargetImageList ,GetLayerNumb(),true);
					if(D>MaxD){
						ResultEMx=mex+dx;
						ResultEMy=mey+dy;
						MaxD=D;
						MEPosLen=L;
					}
				}
				double ecx,ecy;
				MinE->GetCenter(ecx,ecy);
				double mcx,mcy;
				MinM->GetCenter(mcx,mcy);
				double	EMx=mcx-ecx;
				double	EMy=mcy-ecy;
				double	mmcx=EMx*cos(tRotation)-EMy*sin(tRotation);
				double	mmcy=EMx*sin(tRotation)+EMy*cos(tRotation);
				double	dmcx=mmcx-EMx;
				double	dmcy=mmcy-EMy;

				int	MinSearch=hypot(MarkPoint.GetWidth(),MarkPoint.GetHeight());
				int	SearchDotMark=RThr->SearchDotMarkMax;
				double	Vmx=Vx*cos(tRotation)-Vy*sin(tRotation);
				double	Vmy=Vx*sin(tRotation)+Vy*cos(tRotation);
				ResultMatchMark=0;
				double	ThresholdLost=RThr->ThresholdLost/100.0;
				double	CurrentMPos=-1;
				bool	FoundMark=false;
				ResultMMx=0;
				ResultMMy=0;
				for(int L=-MinSearch;L<=SearchDotMark;L++){
					int	dx=dmcx+Vmx*(L+MEPosLen);
					int	dy=dmcy+Vmy*(L+MEPosLen);

					//double	D=MinM->GetCoef(mex+dx ,mey+dy ,TargetImageList ,GetLayerNumb(),true);
					double	D=MinM->GetVar(mex+dx ,mey+dy ,TargetImageList ,GetLayerNumb(),true);
					if(D>ResultMatchMark){
						ResultMMx=mex+dx;
						ResultMMy=mey+dy;
						ResultMatchMark=D;
						CurrentMPos=L;
						
					}
				}
				if(ResultMatchMark>=ThresholdLost){
					FoundMark=true;
				}
				ResultMPos=MarkDistance+CurrentMPos;
				if(ResultMPos<RThr->SearchDotMarkMin){
					if(RThr->ColorMatch==true){
						ImagePointerContainer ImageList;
						GetTargetBuffList(ImageList);
						QColor	CCol	=GetMarkEdgePointColor(MarkPoint,ImageList
																,ResultMMx,ResultMMy,-1);
						double	MasterH,MasterS,MasterV;
						::RGB2HSV(MasterH,MasterS,MasterV,(int)MarkColor.red() ,(int)MarkColor.green(),(int)MarkColor.blueF());
						double	TargetH,TargetS,TargetV;
						::RGB2HSV(TargetH,TargetS,TargetV,(int)CCol.red() ,(int)CCol.green(),(int)CCol.blueF());
						double	DifH=MasterH-TargetH;
						if(DifH<0)
							DifH+=360;
						if(DifH>180)
							DifH-=360;
						DifH=abs(DifH);

						double	ColLenMark =GetColorDistance(CCol,MarkColor);
						double	ColLenPaper=GetColorDistance(CCol,PaperColor);
						double	ColLenBack =GetColorDistance(CCol,BackColor);
						if(DifH>ABase->DiffColorH || ColLenMark>=ColLenPaper || ColLenMark>=ColLenBack){
							FoundMark=false;
						}
					}
					else{
						FoundMark=false;
					}
				}
				if(RThr->SearchDotMarkMax<floor(ResultMPos)){
					FoundMark=false;
				}

				ResultMarkAngle=tRotation;
				Res->SetAlignedXY(ResultMMx,ResultMMy);
				Res->SetResult1(ResultMPos);
				Res->SetResultDouble(ResultMatchMark);

				if(FoundMark==true){
					if(RThr->NGByLosingMark==true){
						Res->SetError(1);	//OK
					}
					else{
						Res->SetError(2);	//NG
					}
				}
				else{
					if(RThr->NGByLosingMark==true){
						Res->SetError(2);	//NG
					}
					else{
						Res->SetError(1);	//OK
					}
				}
			}
		}
	}

	ExeResult	Ret=_ER_true;

	return Ret;
}

void	ShiftMarkItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	ShiftMarkDrawAttr	*BAttr=dynamic_cast<ShiftMarkDrawAttr *>(Attr);
	if(BAttr!=NULL){
		QRgb	ECol=qRgba(0,255,0,128);
		EdgePoint.DrawAlpha(0,0,&pnt,ECol,ZoomRate,movx ,movy);

		QRgb	MCol=qRgba(255,255,0,128);
		MarkPoint.DrawAlpha(0,0,&pnt,MCol,ZoomRate,movx ,movy);

		Attr->LineWidth=3;
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);


		VectorLineBase	*L=GetVector();
		if(L!=NULL){
			VectorItemBase	*p1=L->GetFirstItem();
			VectorItemBase	*p2=L->GetLastItem();
			double	x1=p1->GetX();
			double	y1=p1->GetY();
			double	x2=p2->GetX();
			double	y2=p2->GetY();
			double	Len=hypot(x2-x1,y2-y1);
			if(Len>0){
				const	ShiftMarkThreshold	*RThr=GetThresholdR();
				double	Vx=-(y2-y1)/Len;
				double	Vy= (x2-x1)/Len;

				//double	Vex=Vx*cos(eRotation)-Vy*sin(eRotation);
				//double	Vey=Vx*sin(eRotation)+Vy*cos(eRotation);

				int	SearchDotEdge=RThr->SearchDotEdge;

				int	Cx=(x1+x2)/2;
				int	Cy=(y1+y2)/2;
				int	VPx=Cx+Vx*SearchDotEdge;
				int	VPy=Cy+Vy*SearchDotEdge;

				QPainter	LPnt(&pnt);
				LPnt.setPen(QPen(Qt::red));

				DrawArrow(Cx ,Cy ,VPx ,VPy
						,LPnt , movx , movy ,ZoomRate ,15);

				LPnt.setPen(QPen(Qt::cyan));
				int	PCx,PCy;
				int	PWidth,PHeight;
				int	x1	;
				int	y1	;
				int	x2	;
				int	y2	;
				int	gcx	;
				int	gcy	;

				EdgePoint.GetCenter(PCx,PCy);
				PWidth	=EdgePoint.GetWidth();
				PHeight	=EdgePoint.GetHeight();
				x1	=(PCx-PWidth/2 -30+movx)*ZoomRate;
				y1	=(PCy-PHeight/2-30+movy)*ZoomRate;
				x2	=(PCx+PWidth/2 +30+movx)*ZoomRate;
				y2	=(PCy+PHeight/2+30+movy)*ZoomRate;
				gcx	=(PCx+movx)*ZoomRate;
				gcy	=(PCy+movy)*ZoomRate;
				LPnt.drawLine(x1,gcy,x2,gcy);
				LPnt.drawLine(gcx,y1,gcx,y2);

				MarkPoint.GetCenter(PCx,PCy);
				PWidth	=MarkPoint.GetWidth();
				PHeight	=MarkPoint.GetHeight();
				x1=(PCx-PWidth/2 -30+movx)*ZoomRate;
				y1=(PCy-PHeight/2-30+movy)*ZoomRate;
				x2=(PCx+PWidth/2 +30+movx)*ZoomRate;
				y2=(PCy+PHeight/2+30+movy)*ZoomRate;
				gcx=(PCx+movx)*ZoomRate;
				gcy=(PCy+movy)*ZoomRate;
				LPnt.drawLine(x1,gcy,x2,gcy);
				LPnt.drawLine(gcx,y1,gcx,y2);
			}
		}
	}
	else{
		AlgorithmItemPI::Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}


void	ShiftMarkItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		//if(Res.IsOk()==false || OnlyNG==false){
		if(GetLayersBase()->GetCurrentPhase()==GetPhaseCode()){
			QRgb	ECol=qRgba(0,255,0,128);
			EdgePoint.DrawAlpha(0,0,&IData,ECol,ZoomRate,MovX ,MovY);
			QRgb	MCol=qRgba(255,255,0,128);
			MarkPoint.DrawAlpha(0,0,&IData,MCol,ZoomRate,MovX ,MovY);

			QRgb	ResECol=qRgba(255,100,0,128);
			EdgePoint.DrawAlpha(ResultEMx,ResultEMy,&IData,ResECol,ZoomRate,MovX ,MovY);
			QRgb	ResMCol=qRgba(255,0,0,128);
			MarkPoint.DrawAlpha(ResultMMx,ResultMMy,&IData,ResMCol,ZoomRate,MovX ,MovY);

			AlgorithmItemPI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);

			VectorLineBase	*L=GetVector();
			if(L!=NULL){
				VectorItemBase	*p1=L->GetFirstItem();
				VectorItemBase	*p2=L->GetLastItem();
				double	x1=p1->GetX();
				double	y1=p1->GetY();
				double	x2=p2->GetX();
				double	y2=p2->GetY();

				QPen	MasterLinePen(Qt::green);
				MasterLinePen.setWidth(3);
				PData.setPen(MasterLinePen);
				PData.drawLine((x1+MovX)*ZoomRate,(y1+MovY)*ZoomRate
							  ,(x2+MovX)*ZoomRate,(y2+MovY)*ZoomRate);

				QPen	TargetLinePen(Qt::red);
				TargetLinePen.setWidth(3);
				PData.setPen(TargetLinePen);
				PData.drawLine((x1+MovX+ResultMMx)*ZoomRate,(y1+MovY+ResultMMy)*ZoomRate
							  ,(x2+MovX+ResultMMx)*ZoomRate,(y2+MovY+ResultMMy)*ZoomRate);

			}
			int	Cx,Cy;
			MarkPoint.GetCenter(Cx,Cy);
			PData.setPen(Qt::red);
			PData.drawText((Cx+MovX)*ZoomRate,(Cy+MovY)*ZoomRate+16*1,QString(/**/"Mark shift=")+QString::number(ResultMPos,'f',1));
			PData.drawText((Cx+MovX)*ZoomRate,(Cy+MovY)*ZoomRate+16*2,QString(/**/"Mark Match=")+QString::number(ResultMatchMark,'f',3));
			PData.drawText((Cx+MovX)*ZoomRate,(Cy+MovY)*ZoomRate+16*3,QString(/**/"Mark Angle=")+QString::number(ResultMarkAngle*360/(2*M_PI),'f',3));
		}
	}
}

void	ShiftMarkItem::MoveForAlignment(void)
{
	int	mex,mey;
	double	eRotation=0;
	int	mmx,mmy;
	double	mRotation=0;
	if(EdgeVector!=NULL){
		mex		=EdgeVector->ShiftX;
		mey		=EdgeVector->ShiftY;
		eRotation=EdgeVector->Rotation;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		EdgePoint.GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mex=V.ShiftX;
		mey=V.ShiftY;
		eRotation=V.Rotation;
	}
	if(MarkVector!=NULL){
		mmx		=MarkVector->ShiftX;
		mmy		=MarkVector->ShiftY;
		mRotation=MarkVector->Rotation;
	}
	else{
		AlignmentPacket2D	V;
		int	cx,cy;
		MarkPoint.GetCenter(cx,cy);
		V.PosXOnTarget=cx;
		V.PosYOnTarget=cy;
		V.ShiftX=0;
		V.ShiftY=0;
		GetAlignmentForProcessing(V);
		mmx=V.ShiftX;
		mmy=V.ShiftY;
		mRotation=V.Rotation;
	}
	//EdgePoint.MoveToNoClip(mex,mey);
	//MarkPoint.MoveToNoClip(mmx,mmy);

	VectorLineBase	*L=GetVector();
	if(L!=NULL){
		VectorItemBase	*p1=L->GetFirstItem();
		VectorItemBase	*p2=L->GetLastItem();
		double	x1=p1->GetX();
		double	y1=p1->GetY();
		double	x2=p2->GetX();
		double	y2=p2->GetY();
		AlignmentPacket2D	V;

		{
			AlignmentPacket2D	V;
			V.PosXOnTarget=x1;
			V.PosYOnTarget=y1;
			V.ShiftX=0;
			V.ShiftY=0;
			GetAlignmentForProcessing(V);
			p1->MoveTo(V.ShiftX ,V.ShiftY);
		}
		{
			AlignmentPacket2D	V;
			V.PosXOnTarget=x2;
			V.PosYOnTarget=y2;
			V.ShiftX=0;
			V.ShiftY=0;
			GetAlignmentForProcessing(V);
			p2->MoveTo(V.ShiftX ,V.ShiftY);
		}

		ImageBuffer *ImageList[1000];
		GetTargetBuffList(ImageList);
		MoveCenterPosition(mex,mey,eRotation,mRotation,ImageList);
	}
}

void	ShiftMarkItem::MoveCenterPosition(int mex,int mey,double eRotation,double mRotation
										,ImageBuffer *ImageList[])
{
	VectorLineBase	*L=GetVector();
	if(L!=NULL){
		VectorItemBase	*p1=L->GetFirstItem();
		VectorItemBase	*p2=L->GetLastItem();
		double	x1=p1->GetX();
		double	y1=p1->GetY();
		double	x2=p2->GetX();
		double	y2=p2->GetY();

		double	MinD=99999999;
		FlexAreaColorRotatedImage *MinE=NULL;
		for(FlexAreaColorRotatedImage *e=EdgeArea.GetFirst();e!=NULL;e=e->GetNext()){
			double	d=fabs(e->GetAngleRadian()-eRotation);
			if(d<MinD){
				MinD=d;
				MinE=e;
			}
		}
		MinD=99999999;
		FlexAreaColorRotatedImage *MinM=NULL;
		for(FlexAreaColorRotatedImage *m=MarkArea.GetFirst();m!=NULL;m=m->GetNext()){
			double	d=fabs(m->GetAngleRadian()-mRotation);
			if(d<MinD){
				MinD=d;
				MinM=m;
			}
		}
		if(MinE!=NULL && MinM!=NULL && L!=NULL){
			VectorItemBase	*p1=L->GetFirstItem();
			VectorItemBase	*p2=L->GetLastItem();
			double	x1=p1->GetX();
			double	y1=p1->GetY();
			double	x2=p2->GetX();
			double	y2=p2->GetY();
			double	Len=hypot(x2-x1,y2-y1);
			if(Len>0){
				const	ShiftMarkThreshold	*RThr=GetThresholdR();

				double	Vx=-(y2-y1)/Len;
				double	Vy= (x2-x1)/Len;

				double	Vex=Vx*cos(eRotation)-Vy*sin(eRotation);
				double	Vey=Vx*sin(eRotation)+Vy*cos(eRotation);

				int	SearchDotEdge=RThr->SearchDotEdge;

				double	MaxD=0;
				int		MEPosLen=0;
				int		EDx=0;
				int		EDy=0;

				for(int L=-SearchDotEdge;L<=SearchDotEdge;L++){
					int	dx=Vex*L;
					int	dy=Vey*L;

					//double	D=MinE->GetCoef(mex+dx ,mey+dy ,MasterImageList ,GetLayerNumb(),false);
					double	D=MinE->GetVar(mex+dx ,mey+dy ,ImageList ,GetLayerNumb(),true);
					if(D>MaxD){
						EDx=mex+dx;
						EDy=mey+dy;
						MaxD=D;
					}
				}
				EdgePoint.MoveToNoClip(EDx,EDy);

				int	MinSearch=hypot(MarkPoint.GetWidth(),MarkPoint.GetHeight());
				int	SearchDotMark=RThr->SearchDotMarkMax;
				double	Vmx=Vx*cos(mRotation)-Vy*sin(mRotation);
				double	Vmy=Vx*sin(mRotation)+Vy*cos(mRotation);
				ResultMatchMark=0;
				double	ThresholdLost=RThr->ThresholdLost/100.0;
				double	CurrentMPos=-1;
				bool	FoundMark=false;
				int		MDx=0;
				int		MDy=0;
				for(int L=-MinSearch;L<=SearchDotMark;L++){
					int	dx=Vmx*(L+MEPosLen);
					int	dy=Vmy*(L+MEPosLen);

					//double	D=MinM->GetCoef(mex+dx ,mey+dy ,MasterImageList ,GetLayerNumb(),false);
					double	D=MinM->GetVar(mex+dx ,mey+dy ,ImageList ,GetLayerNumb(),true);
					if(D>ResultMatchMark){
						MDx=mex+dx;
						MDy=mey+dy;
						ResultMatchMark=D;
						CurrentMPos=L;						
					}
				}
				MarkPoint.MoveToNoClip(MDx,MDy);
			}
			InitialEdgeMark();
		}
	}
}

void	ShiftMarkItem::MoveTo(int dx ,int dy)
{
	AlgorithmItemPI::MoveTo(dx ,dy);
	EdgePoint.MoveToNoClip(dx,dy);
	MarkPoint.MoveToNoClip(dx,dy);

	InitialEdgeMark();
}