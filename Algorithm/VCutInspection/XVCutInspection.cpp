#include "VCutInspectionResource.h"
/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\Algorithm\VCutInspection\XVCutInspection.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XVCutInspection.h"
#include "VCutInspection.h"
#include "XPointer.h"
#include "XImageProcess.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "swap.h"
#include "XBitImageProcessor.h"
#include "XDisplayBitImage.h"
#include <omp.h>
#include <QColor>
#include "XVCutInspection.h"
#include "XAnyData.h"
#include "xvcutinspectionpacket.h"
#include <QPainter>
#include "XCriticalFunc.h"

VCutInspectionLibrary::VCutInspectionLibrary(int LibType,LayersBase *Base)
:ServiceForLayers(Base)
{
	ThresholdShift	=20;
	ThresholdLevel	=20;
	ThresholdLength	=100;
	GenDynamicMask	=false;
	ExpandGenMask	=0;
}

bool	VCutInspectionLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=10202;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ThresholdShift)==false)
		return false;
	if(::Save(f,ThresholdLevel)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,GenDynamicMask)==false)
		return false;
	if(::Save(f,ExpandGenMask)==false)
		return false;
	return true;
}
bool	VCutInspectionLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ThresholdShift)==false)
		return false;
	if(Ver==10200){
		int	iThresholdLevel;
		if(::Load(f,iThresholdLevel)==false)
			return false;
		ThresholdLevel=iThresholdLevel;
	}
	else{
		if(::Load(f,ThresholdLevel)==false)
			return false;
	}
	if(::Load(f,ThresholdLevel)==false)
		return false;
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,GenDynamicMask)==false)
		return false;
	if(::Load(f,ExpandGenMask)==false)
		return false;
	return true;
}

VCutInspectionLibrary	&VCutInspectionLibrary::operator=(const AlgorithmLibrary &src)
{
	ThresholdShift	=((const VCutInspectionLibrary *)&src)->ThresholdShift;
	ThresholdLevel	=((const VCutInspectionLibrary *)&src)->ThresholdLevel;
	ThresholdLength	=((const VCutInspectionLibrary *)&src)->ThresholdLength;
	GenDynamicMask	=((const VCutInspectionLibrary *)&src)->GenDynamicMask;	
	ExpandGenMask	=((const VCutInspectionLibrary *)&src)->ExpandGenMask	;
	return *this;
}

VCutInspectionThreshold::VCutInspectionThreshold(AlgorithmItemPI *parent)
:AlgorithmThreshold(parent)
{
	ThresholdShift	=20;
	ThresholdLevel	=20;
	ThresholdLength	=100;
	GenDynamicMask	=false;
	ExpandGenMask	=0;
}
void	VCutInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const VCutInspectionThreshold *s=(const VCutInspectionThreshold *)&src;
	ThresholdShift	=s->ThresholdShift;
	ThresholdLevel	=s->ThresholdLevel;
	ThresholdLength	=s->ThresholdLength;
	GenDynamicMask	=s->GenDynamicMask;	
	ExpandGenMask	=s->ExpandGenMask	;
}
bool	VCutInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const VCutInspectionThreshold *s=(const VCutInspectionThreshold *)&src;
	if(ThresholdShift	!=s->ThresholdShift	)	return false;
	if(ThresholdLevel	!=s->ThresholdLevel	)	return false;
	if(ThresholdLength	!=s->ThresholdLength)	return false;
	if(GenDynamicMask	!=s->GenDynamicMask	)	return false;	
	if(ExpandGenMask	!=s->ExpandGenMask	)	return false;
	return true;
}
void	VCutInspectionThreshold::FromLibrary(AlgorithmLibrary *src)
{
	ThresholdShift	=((VCutInspectionLibrary *)src)->ThresholdShift;
	ThresholdLevel	=((VCutInspectionLibrary *)src)->ThresholdLevel;
	ThresholdLength	=((VCutInspectionLibrary *)src)->ThresholdLength;
	GenDynamicMask	=((VCutInspectionLibrary *)src)->GenDynamicMask;	
	ExpandGenMask	=((VCutInspectionLibrary *)src)->ExpandGenMask	;

}
void	VCutInspectionThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
	((VCutInspectionLibrary *)Dest)->ThresholdShift		=ThresholdShift	;
	((VCutInspectionLibrary *)Dest)->ThresholdLevel		=ThresholdLevel	;
	((VCutInspectionLibrary *)Dest)->ThresholdLength	=ThresholdLength ;
	((VCutInspectionLibrary *)Dest)->GenDynamicMask		=GenDynamicMask	;	
	((VCutInspectionLibrary *)Dest)->ExpandGenMask		=ExpandGenMask	;

}
bool	VCutInspectionThreshold::Save(QIODevice *f)
{
	int32	Ver=10202;

	if(::Save(f,Ver)==false)
		return false;
	if(::Save(f,ThresholdShift)==false)
		return false;
	if(::Save(f,ThresholdLevel)==false)
		return false;
	if(::Save(f,ThresholdLength)==false)
		return false;
	if(::Save(f,GenDynamicMask)==false)
		return false;
	if(::Save(f,ExpandGenMask)==false)
		return false;
	return true;
}
bool	VCutInspectionThreshold::Load(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false)
		return false;
	if(::Load(f,ThresholdShift)==false)
		return false;
	if(Ver==10200){
		int	iThresholdLevel;
		if(::Load(f,iThresholdLevel)==false)
			return false;
		ThresholdLevel=iThresholdLevel;
	}
	else{
		if(::Load(f,ThresholdLevel)==false)
			return false;
	}
	if(::Load(f,ThresholdLength)==false)
		return false;
	if(::Load(f,GenDynamicMask)==false)
		return false;
	if(::Load(f,ExpandGenMask)==false)
		return false;
	return true;
}

//================================================================================
VCutBand::VCutBand(void)
{	
	AVector=NULL;	
	BList=NULL;	
	Parent	=NULL;

	Px=Py=0;
	Ux=Uy=0;
	Vx=Vy=0;	//V?J?b?g?u?u?I?P?E?x?N?g??
	WLen=0;		//V?J?b?g?d?????E?!?O?e?u?u?I?o???h?I?・?3
	StackedLen=0;	//V?J?b?g?u?u?I?・?3

	ResultDifference=0;		//?≫?e???E?I?l
	ResMx=ResMy=0;
	ResImageX1=0;
	ResImageY1=0;
	ResImageX2=0;
	ResImageY2=0;

	MidAvr	=0;
	ResultU1=ResultU2=0;
}

VCutBand::~VCutBand(void)
{
	if(BList!=NULL){
		delete	[]BList;
	}
	BList=NULL;
}

void	VCutBand::SetParent(VCutInspectionItem *parent)
{
	Parent=parent;
}
int		VCutBand::GetDotPerLine(void)
{
	return Parent->GetDotPerLine();
}
int		VCutBand::GetMaxLines(void)
{
	return Parent->GetMaxLines();
}

void	VCutBand::GetCenter(int &cx,int &cy)
{
	cx=Px+Ux*WLen/2+Vx*StackedLen/2;
	cy=Py+Uy*WLen/2+Vy*StackedLen/2;
}
void	VCutBand::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	QPainter	Pnt(&pnt);

	Draw(Pnt, movx ,movy ,ZoomRate ,Attr);
}

void	VCutBand::Draw(QPainter &Pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	Pnt.setPen(Qt::yellow);

	int	x1=(Px+movx)*ZoomRate;
	int	y1=(Py+movy)*ZoomRate;
	int	x2=(Px+Ux*WLen+movx)*ZoomRate;
	int	y2=(Py+Uy*WLen+movy)*ZoomRate;
	int	x3=(Px+Ux*WLen+Vx*StackedLen+movx)*ZoomRate;
	int	y3=(Py+Uy*WLen+Vy*StackedLen+movy)*ZoomRate;
	int	x4=(Px+Vx*StackedLen+movx)*ZoomRate;
	int	y4=(Py+Vy*StackedLen+movy)*ZoomRate;

	Pnt.drawLine(x1,y1,x2,y2);
	Pnt.drawLine(x2,y2,x3,y3);
	Pnt.drawLine(x3,y3,x4,y4);
	Pnt.drawLine(x4,y4,x1,y1);

	int	ImageX1=min(min(x1,x2),min(x3,x4));
	int	ImageY1=min(min(y1,y2),min(y3,y4));
	int	ImageX2=max(max(x1,x2),max(x3,x4));
	int	ImageY2=max(max(y1,y2),max(y3,y4));

	if(ImageX1<2000 && ImageY1<2000 && ImageX2>0 && ImageY2>0){
		double	Z=1.0/ZoomRate;
		for(int y=ImageY1;y<=ImageY2;y++){
			for(int x=ImageX1;x<=ImageX2;x++){
				int	X=x*Z-movx-ResImageX1;
				int	Y=y*Z-movy-ResImageY1;
				if(ResultBitImage.GetBit(X,Y)!=0){
					Pnt.drawPoint(x,y);
				}
			}
		}
	}
}

void	VCutBand::MakeResultVCutMap(MapBuffer &BitMap)
{
	for(int y=0;y<ResultBitImage.GetYLen();y++){
		int	XLen=ResultBitImage.GetXByte()<<3;
		for(int x=0;x<XLen;x++){
			if(ResultBitImage.GetBit(x,y)!=0){
				BitMap.SetBit(Px+ResMx+x,Py+ResMy+y);
			}
		}
	}
}
void	VCutBand::MakeFlexArea(void)
{
	XYClassContainer P;
	P.Add(Px+Ux*WLen/2,Py+Uy*WLen/2);
	P.Add(Px+Ux*WLen/2+Vx*StackedLen,Py+Uy*WLen/2+Vy*StackedLen);
	P.Add(Px-Ux*WLen/2+Vx*StackedLen,Py-Uy*WLen/2+Vy*StackedLen);
	P.Add(Px-Ux*WLen/2,Py-Uy*WLen/2);

	const VCutInspectionThreshold	*RThr=Parent->GetThresholdR(NULL);
	Area.MakeConvexPolygon(P);
	int	ExpandGenMask	=RThr->ExpandGenMask;
	int	MinX=Area.GetMinX()-ExpandGenMask-18;
	int	MinY=Area.GetMinY()-ExpandGenMask-8;
	int	MaxX=Area.GetMaxX()+ExpandGenMask+18;
	int	MaxY=Area.GetMaxY()+ExpandGenMask+8;
	MaskArea=Area;
	MaskArea.MoveToNoClip(-MinX,-MinY);

	int	SDotPerLine	=MaxX-MinX;
	int	SMaxLines	=MaxY-MinY;
	int	SXByte=(SDotPerLine+7)/8;
	BYTE	**TmpMap=MakeMatrixBuff(SXByte,SMaxLines);
	MatrixBuffClear	(TmpMap ,0 ,SXByte,SMaxLines);
	BYTE	**TmpBmp1=MakeMatrixBuff(SXByte,SMaxLines);

	MaskArea.MakeBitData(TmpMap,0,0,SDotPerLine,SMaxLines);
	Parent->GetLayersBase()->FatAreaN(TmpMap
				,TmpBmp1
				,SXByte, SMaxLines
				,ExpandGenMask);
	MaskArea.BuildFromRaster(TmpMap ,SXByte, SMaxLines ,MinX,MinY);

	DeleteMatrixBuff(TmpMap ,SMaxLines);
	DeleteMatrixBuff(TmpBmp1,SMaxLines);
}
void	VCutBand::MakeDynamicMask(int mx ,int my)
{
	const VCutInspectionThreshold	*RThr=Parent->GetThresholdR(NULL);
	if(RThr->GenDynamicMask==true){
		BYTE	**DynamicBmp=Parent->GetDataInPage()->GetDynamicMaskingMap();
		int		DotPerLine	=Parent->GetDotPerLine();
		int		MaxLines	=Parent->GetMaxLines();
		MaskArea.MakeBitData(DynamicBmp
                        ,mx,my
						,DotPerLine, MaxLines);
	}
}

//=========================================================================================

VCutInspectionItem::VCutInspectionItem(void)
{
	InspectedBands=NULL;
	BandNumb	=0;
}
VCutInspectionItem::~VCutInspectionItem(void)
{
	if(InspectedBands!=NULL){
		delete	[]InspectedBands;
		InspectedBands=NULL;
	}
}
void	VCutInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	VCutInspectionDrawAttr	*a=dynamic_cast<VCutInspectionDrawAttr	*>(Attr);
	if(a!=NULL && BandZone.IsNull()==false){
		QRgb	ac=qRgba(0,128,128,100);
		BandZone.DrawAlpha(0,0,&pnt ,ac	,ZoomRate ,movx ,movy);
	}
	for(int i=0;i<BandNumb;i++){
		InspectedBands[i].Draw(pnt, movx ,movy ,ZoomRate ,Attr);
	}
	//AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	DrawVector(GetVector(),pnt, movx ,movy ,ZoomRate ,Attr);
}
void	VCutInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL){
		for(int i=0;i<BandNumb;i++){
			int	cx,cy;
			InspectedBands[i].GetCenter(cx,cy);
			int	kx=(cx+MovX)*ZoomRate;
			int	ky=(cy+MovY)*ZoomRate;
			if(OnlyNG==false || (OnlyNG==true && Res->IsOk()==false)){
				InspectedBands[i].Draw(PData, MovX+InspectedBands[i].ResMx ,MovY+InspectedBands[i].ResMy ,ZoomRate ,NULL);
				if( ZoomRate>1.0){
					if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
						QRect	rect(0,0,IData.width(),IData.height());
						PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
							,Qt::AlignLeft | Qt::AlignTop
							//,QString("Ly:")+QString::number((int)GetParent()->GetLayer())
							,QString(/**/" Dif:")+QString::number(InspectedBands[i].ResultDifference,'f',3)
							,&rect);
					}
				}
			}
		}
	}
	DrawVector(GetVector(),IData, MovX ,MovY ,ZoomRate ,NULL);
}


VectorLineBase	*VCutInspectionItem::CreateVectorBase(void)
{
	return new VectorLineDouble();
}
void	VCutInspectionItem::CopyArea(VCutInspectionItem &src)
{
	SetArea(src.GetArea());
	SetVector(src.GetVector());
}

void	VCutInspectionItem::CopyThresholdOnly(VCutInspectionItem *src)
{
	const VCutInspectionThreshold	*RThr=src->GetThresholdR(GetLayersBase());
	GetThresholdW()->ThresholdShift	=RThr->ThresholdShift	;
	GetThresholdW()->ThresholdLevel	=RThr->ThresholdLevel	;
	GetThresholdW()->ThresholdLength=RThr->ThresholdLength	;
	GetThresholdW()->GenDynamicMask	=RThr->GenDynamicMask	;
	GetThresholdW()->ExpandGenMask	=RThr->ExpandGenMask	;
}

void	VCutInspectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			VCutInspectionInPage	*Pg=dynamic_cast<VCutInspectionInPage *>(GetParentInPage());
			UndoElement<VCutInspectionInPage>	*UPointer=new UndoElement<VCutInspectionInPage>(Pg,&VCutInspectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			VCutInspectionItem *src=(VCutInspectionItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((VCutInspectionItem *)Data)->GetLibID()){
			VCutInspectionInPage	*Pg=dynamic_cast<VCutInspectionInPage *>(GetParentInPage());
			UndoElement<VCutInspectionInPage>	*UPointer=new UndoElement<VCutInspectionInPage>(Pg,&VCutInspectionInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			VCutInspectionItem *src=(VCutInspectionItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
}

void	VCutInspectionItem::MakebandZone(void)
{
	VectorItemBase	*L=GetVector()->GetFirstItem();
	if(L==NULL)
		return;

	VectorItemDouble	*v1=(VectorItemDouble *)(L);
	if(v1==NULL)
		return;
	VectorItemDouble	*v2=(VectorItemDouble *)(v1->GetNext());
	if(v2==NULL)
		return;
	double	px1=v1->GetX();
	double	py1=v1->GetY();
	double	px2=v2->GetX();
	double	py2=v2->GetY();

	double	vx=px2-px1;
	double	vy=py2-py1;
	double	m=sqrt(vx*vx+vy*vy);
	if(m<1.0)
		return;
	double	hux=vy/m;
	double	huy=-vx/m;
	double	Mul=GetThresholdR()->ThresholdShift;

	XYClassArea PolyArea;
	XYClassArea area;

	PolyArea.AppendList(new XYClass(px1+hux*Mul,py1+huy*Mul));
	PolyArea.AppendList(new XYClass(px1-hux*Mul,py1-huy*Mul));
	PolyArea.AppendList(new XYClass(px2-hux*Mul,py2-huy*Mul));
	PolyArea.AppendList(new XYClass(px2+hux*Mul,py2+huy*Mul));
	PolyArea.AppendList(new XYClass(px1+hux*Mul,py1+huy*Mul));
 
    XYClass *d;
	int x1;
    int y1;
	int x2;
    int y2;
	int x,y;
    int lastx=99999999 ,lasty=99999999;
	for(XYClass *c=PolyArea.NPListPack<XYClass>::GetFirst();c!=NULL;c=c->GetNext()){
		d=c->GetNext();
		if(d==NULL){
			d=PolyArea.NPListPack<XYClass>::GetFirst();
		}
        x1=c->x;
	    y1=c->y;
		x2=d->x;
        y2=d->y;

		int dx=x2-x1;
		int dy=y2-y1;
        if(abs(dx)>abs(dy)){
	        if(dx>0){
		        for(x=0;x<dx;x++){
			        y=x*dy/dx+y1;
				    if(lastx!=x1+x || lasty!=y){
					    lastx=x1+x;
						lasty=y;
                        area.AppendList(new XYClass(lastx,lasty));
	                    }
		            }
			    }
            else{
	            for(x=0;x>dx;x--){
		            y=x*dy/dx+y1;
			        if(lastx!=x1+x || lasty!=y){
				        lastx=x1+x;
					    lasty=y;
						area.AppendList(new XYClass(lastx,lasty));
                        }
	                }
		        }
			}
        else{
	        if(dy>0){
		        for(y=0;y<dy;y++){
			        x=y*dx/dy+x1;
				    if(lastx!=x || lasty!=y1+y){
					    lastx=x;
						lasty=y1+y;
                        area.AppendList(new XYClass(lastx,lasty));
	                    }
		            }
			    }
            else if(dy!=0){
	            for(y=0;y>dy;y--){
		            x=y*dx/dy+x1;
			        if(lastx!=x || lasty!=y1+y){
				        lastx=x;
					    lasty=y1+y;
						area.AppendList(new XYClass(lastx,lasty));
                        }
	                }
		        }
			else if(lastx!=x1 || lasty!=y1){
				area.AppendList(new XYClass(x1,y1));
                lastx=x1;
	            lasty=y1;
		        }
			}
		if(PolyArea.NPListPack<XYClass>::GetFirst()==d){
	        break;
		}
	}
	area.TransTo(BandZone);

	if(InspectedBands!=NULL){
		delete	[]InspectedBands;
		InspectedBands=NULL;
	}

	int	H=GetThresholdR()->ThresholdLength/2;
	BandNumb=m/H;
	int	StartH=(m-H*BandNumb)/2;
	InspectedBands=new VCutBand[BandNumb];
	FlexArea	BandArea;
	for(int i=0;i<BandNumb;i++){
		InspectedBands[i].SetParent(this);
		double	ux=vx/m;
		double	uy=vy/m;
		InspectedBands[i].SetV(ux,uy,H);
		InspectedBands[i].SetP(px1+ux*(i*H+StartH)-hux*Mul,py1+uy*(i*H+StartH)-huy*Mul);
		InspectedBands[i].SetU(hux,huy,Mul*2+1);

		InspectedBands[i].MakeFlexArea();
		BandArea+=InspectedBands[i].Area;
	}
	SetArea(BandArea);
}


ExeResult	VCutInspectionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	GetCenter(MasterX,MasterY);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterX,MasterY);
	if(AVector!=NULL)
		AVector->Set(this);

	if(InspectedBands==NULL){
		MakebandZone();
	}
	for(int i=0;i<BandNumb;i++){
		InspectedBands[i].ExecuteInitialAfterEdit(EInfo);
	}
	return _ER_true;
}
ExeResult	VCutInspectionItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
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
		Parent->GetAlignmentForProcessing(V);
		mx=V.ShiftX;
		my=V.ShiftY;
	}

	bool	Ok=true;
	if(GetParamGlobal()->CalcSingleThread==false && BandNumb>1){
		#pragma omp parallel                             
		{                                                
			#pragma omp for
				for(int i=0;i<BandNumb;i++){
					ResultPosList	*R;
					if((R=InspectedBands[i].ExecuteProcessing(mx,my))!=NULL){
						Ok=false;
						#pragma omp critical
						{
							Res->AddPosList(R);
						}
					}
				}
		}
	}
	else{
		for(int i=0;i<BandNumb;i++){
			ResultPosList	*R;
			if((R=InspectedBands[i].ExecuteProcessing(mx,my))!=NULL){
				Ok=false;
				Res->AddPosList(R);
			}
		}
	}

	Res->SetAlignedXY(mx,my);
	if(Ok==true){
		Res->SetItemSearchedXY(0,0);
		Res->SetResult1(0);
		Res->SetResult2(0);
		Res->SetError(1);	//OK
	}
	else{
		Res->SetItemSearchedXY(0,0);
		Res->SetResult1(0);
		Res->SetResult2(0);
		Res->SetError(2);	//OK
	}
	return _ER_true;
}
void	VCutInspectionItem::MakeResultVCutMap(MapBuffer &BitMap)
{
	for(int i=0;i<BandNumb;i++){
		InspectedBands[i].MakeResultVCutMap(BitMap);
	}
}

//================================================================================

void	VCutInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	AddVCutInspectionAreaPacket	*AddVCutInspectionAreaVar=dynamic_cast<AddVCutInspectionAreaPacket*>(packet);
	if(AddVCutInspectionAreaVar!=NULL){
		AlgorithmLibraryLevelContainer	*Lib=GetParentBase()->FindOrLoadLibFromManagedCacheLib(AddVCutInspectionAreaVar->LibID);
		if(Lib!=NULL && AddVCutInspectionAreaVar->Vector!=NULL){
			VCutInspectionLibrary	*ALib=dynamic_cast<VCutInspectionLibrary *>(Lib->GetLibrary());
			for(VectorItemBase *v=AddVCutInspectionAreaVar->Vector->GetFirstItem();v!=NULL;v=v->GetNext()){
				VectorItemBase *w=v->GetNext();
				if(w==NULL)
					break;
				double	Len=hypot(v->GetX()-w->GetX(),v->GetY()-w->GetY());
				int	N=(Len+ALib->ThresholdLength-1)/ALib->ThresholdLength;
				if(N==0)
					N=1;
				double	UnitLen=Len/N;
				double	Lx=(w->GetX()-v->GetX())/Len;
				double	Ly=(w->GetY()-v->GetY())/Len;
				for(int i=0;i<N;i++){
					double	Hx1=v->GetX()+Lx*UnitLen*i		-Lx*ALib->ThresholdShift;
					double	Hy1=v->GetY()+Ly*UnitLen*i		-Ly*ALib->ThresholdShift;
					double	Hx2=v->GetX()+Lx*UnitLen*(i+1)	+Lx*ALib->ThresholdShift;
					double	Hy2=v->GetY()+Ly*UnitLen*(i+1)	+Ly*ALib->ThresholdShift;
					VectorLineDouble	*V=new VectorLineDouble();
					V->AppendItemBase(new VectorItemDouble(Hx1,Hy1));
					V->AppendItemBase(new VectorItemDouble(Hx2,Hy2));

					VCutInspectionItem	*Item=(VCutInspectionItem *)CreateItem(0);
					Item->SetVector(V);
					Item->SetLibID(AddVCutInspectionAreaVar->LibID);
					Item->SetManualCreated(true);

					Item->CopyThresholdFromLibrary(Lib);

					Item->GetThresholdW()->ThresholdLength	=AddVCutInspectionAreaVar->ThresholdLength;
					Item->GetThresholdW()->ThresholdLevel	=AddVCutInspectionAreaVar->ThresholdLevel;
					Item->GetThresholdW()->ThresholdShift	=AddVCutInspectionAreaVar->ThresholdShift;
					Item->MakebandZone();
					AppendItem(Item);
				}
			}
		}
		return;
	}
	CmdMakeResultVCutMapPacket	*MakeResultVCutMapPacket=dynamic_cast<CmdMakeResultVCutMapPacket*>(packet);
	if(MakeResultVCutMapPacket!=NULL){
		MakeResultVCutMap(VCutMapBuffer);
		MakeResultVCutMapPacket->BmpMap=VCutMapBuffer.GetBitMap();
		return;
	}
}
ExeResult	VCutInspectionInPage::ExecuteInitialAfterEdit	(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	IndexDynamicMaskMap		=GetDataInPage()->GetDynamicMaskingMap();
	IndexDynamicMaskMapXByte=GetDataInPage()->GetDynamicMaskMapXByte();
	IndexDynamicMaskMapYLen	=GetDataInPage()->GetDynamicMaskMapYLen();

	return AlgorithmInPagePI::ExecuteInitialAfterEdit	(ExeID ,Res,EInfo);
}

void	VCutInspectionInPage::MakeResultVCutMap(MapBuffer &BitMap)
{
	BitMap.Alloc((GetDotPerLine()+7)/8 ,GetMaxLines());
	for(AlgorithmItemPI	*v=GetFirstData();v!=NULL;v=v->GetNext()){
		VCutInspectionItem	*Item=dynamic_cast<VCutInspectionItem *>(v);
		Item->MakeResultVCutMap(BitMap);
	}
}

void	VCutInspectionInPage::UndoSetIndependentItemDataCommand(QIODevice *f)
{
	int	ItemID;
	if(::Load(f,ItemID)==false)
		return;
	AlgorithmItemRoot	*Item=SearchIDItem(ItemID);
	if(Item!=NULL){
		VCutInspectionItem	*BI=(VCutInspectionItem *)Item;
		BI->GetThresholdW()->Load(f);
	}
}
//================================================================================
VCutInspectionBase::VCutInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorVCut		=Qt::green;
	ColorSelected	=Qt::yellow;
	ColorActive 	=Qt::red;
	NegColorVCut	=Qt::darkRed;
	NegColorSelected=Qt::darkYellow;
	TransparentLevel=80;
	ExpandPixelForResult	=2;

	SetParam(&ColorVCut					, /**/"Color" ,/**/"ColorVCut" 			,LangSolver.GetString(XVCutInspection_LS,LID_2)/*"Color for VCut"*/);
	SetParam(&ColorSelected				, /**/"Color" ,/**/"ColorSelected" 		,LangSolver.GetString(XVCutInspection_LS,LID_3)/*"Color for Selected VCut"*/);
	SetParam(&ColorActive				, /**/"Color" ,/**/"ColorActive"		,LangSolver.GetString(XVCutInspection_LS,LID_4)/*"Color for Active VCut"*/);
	SetParam(&NegColorVCut				, /**/"Color" ,/**/"NegColorVCut"		,LangSolver.GetString(XVCutInspection_LS,LID_5)/*"Color for Negative VCut"*/);
	SetParam(&NegColorSelected			, /**/"Color" ,/**/"NegColorSelected"	,LangSolver.GetString(XVCutInspection_LS,LID_6)/*"Color for Selected Negative VCut"*/);
	SetParam(&TransparentLevel			, /**/"Color" ,/**/"TransparentLevel"	,LangSolver.GetString(XVCutInspection_LS,LID_7)/*"Color for Transparent display level"*/);
	SetParam(&ExpandPixelForResult		, /**/"Setting"	,/**/"ExpandPixelForResult"	,LangSolver.GetString(XVCutInspection_LS,LID_8)/*"Expansion bit for result"*/);
}

AlgorithmDrawAttr	*VCutInspectionBase::CreateDrawAttr(void)
{
	return new VCutInspectionDrawAttr();
}

void	VCutInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdGetVCutInspectionLibraryListPacket	*AListPacket=dynamic_cast<CmdGetVCutInspectionLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID 
				,AListPacket->AList);
		}
		return;
	}
//	CmdGetAutoMaskingPILibraryNamePacket	*ANamePacket=dynamic_cast<CmdGetAutoMaskingPILibraryNamePacket *>(packet);
//	if(ANamePacket!=NULL){
// 	   if(GetLibraryContainer()!=NULL){
//			GetLibraryContainer()->GetLibraryNames(ANamePacket->AList);
// 	   }
//		return;
//	}
	CmdInsertVCutInspectionLibraryPacket	*BInsLib=dynamic_cast<CmdInsertVCutInspectionLibraryPacket *>(packet);
	if(BInsLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BInsLib->Point->SetDataVersion(VCutInspectionVersion);
			GetLibraryContainer()->SaveNew(*BInsLib->Point);
		}
		return;
	}
	CmdUpdateVCutInspectionLibraryPacket	*BUpdLib=dynamic_cast<CmdUpdateVCutInspectionLibraryPacket *>(packet);
	if(BUpdLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BUpdLib->Point->SetDataVersion(VCutInspectionVersion);
			GetLibraryContainer()->Update(*BUpdLib->Point);
		}
		return;
	}
	CmdLoadVCutInspectionLibraryPacket	*BLoadLib=dynamic_cast<CmdLoadVCutInspectionLibraryPacket *>(packet);
	if(BLoadLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			BLoadLib->Success=GetLibraryContainer()->Load(*BLoadLib->Point);
		}
		return;
	}
	CmdCreateTempVCutInspectionLibraryPacket	*BCreateLib=dynamic_cast<CmdCreateTempVCutInspectionLibraryPacket *>(packet);
	if(BCreateLib!=NULL){
		BCreateLib->Point=new AlgorithmLibraryLevelContainer(this);
		return;
	}
	CmdClearVCutInspectionLibraryPacket	*CmdClearAutoMaskingPILibraryPacketVar=dynamic_cast<CmdClearVCutInspectionLibraryPacket *>(packet);
	if(CmdClearAutoMaskingPILibraryPacketVar!=NULL){
		CmdClearAutoMaskingPILibraryPacketVar->Point->Clear();
		return;
	}
	CmdDeleteVCutInspectionLibraryPacket	*BDeleteLib=dynamic_cast<CmdDeleteVCutInspectionLibraryPacket *>(packet);
	if(BDeleteLib!=NULL){
		if(GetLibraryContainer()!=NULL){
			GetLibraryContainer()->Delete(BDeleteLib->Point->GetLibID());
		}
		return;
	}
}


bool	VCutInspectionBase::GeneralDataRelease(int32 Command,void *data)
{
	if(Command==VCutReqThresholdReqCommand){
		delete	data;
		return true;
	}
	else if(Command==VCutReqThresholdSendCommand){
		delete	data;
		return true;
	}
	else if(Command==VCutReqTryThresholdCommand){
		delete	data;
		return true;
	}
	else if(Command==VCutSendTryThresholdCommand){
		delete	data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataRelease(Command,data);
	}
}
void	*VCutInspectionBase::GeneralDataCreate(int32 Command ,void *reqData)
{
	if(Command==VCutReqThresholdReqCommand){
		return new VCutThresholdReq();
	}
	else if(Command==VCutReqThresholdSendCommand){
		VCutThresholdSend	*pSend=new VCutThresholdSend();
		if(reqData!=NULL){
			VCutThresholdReq	*req=(VCutThresholdReq *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}
	else if(Command==VCutReqTryThresholdCommand){
		return new VCutReqTryThreshold();
	}
	else if(Command==VCutSendTryThresholdCommand){
		VCutSendTryThreshold	*pSend=new VCutSendTryThreshold();
		if(reqData!=NULL){
			VCutReqTryThreshold	*req=(VCutReqTryThreshold *)reqData;
			pSend->ConstructList(req,this);
		}
		return pSend;
	}

	else{
		return AlgorithmBase::GeneralDataCreate(Command,reqData);
	}
}
bool	VCutInspectionBase::GeneralDataLoad(QIODevice *f,int32 Command,void *data)
{
	if(Command==VCutReqThresholdReqCommand){
		VCutThresholdReq	*p=(VCutThresholdReq *)data;
		return p->Load(f);
	}
	else if(Command==VCutReqThresholdSendCommand){
		VCutThresholdSend	*p=(VCutThresholdSend *)data;
		return p->Load(f);
	}
	else if(Command==VCutReqTryThresholdCommand){
		VCutReqTryThreshold	*p=(VCutReqTryThreshold *)data;
		return p->Load(f,GetLayersBase());
	}
	else if(Command==VCutSendTryThresholdCommand){
		VCutSendTryThreshold	*p=(VCutSendTryThreshold *)data;
		return p->Load(f);
	}
	else{
		return AlgorithmBase::GeneralDataLoad(f,Command,data);
	}
}
bool	VCutInspectionBase::GeneralDataSave(QIODevice *f,int32 Command,void *data)
{
	if(Command==VCutReqThresholdReqCommand){
		VCutThresholdReq	*p=(VCutThresholdReq *)data;
		return p->Save(f);
	}
	else if(Command==VCutReqThresholdSendCommand){
		VCutThresholdSend	*p=(VCutThresholdSend *)data;
		return p->Save(f);
	}
	else if(Command==VCutReqTryThresholdCommand){
		VCutReqTryThreshold	*p=(VCutReqTryThreshold *)data;
		return p->Save(f);
	}
	else if(Command==VCutSendTryThresholdCommand){
		VCutSendTryThreshold	*p=(VCutSendTryThreshold *)data;
		return p->Save(f);
	}
	else{
		return AlgorithmBase::GeneralDataSave(f,Command,data);
	}
}
bool	VCutInspectionBase::GeneralDataReply(int32 Command,void *data)
{
	if(Command==VCutReqThresholdReqCommand){
		VCutThresholdReq	*p=(VCutThresholdReq *)data;
		return true;
	}
	else if(Command==VCutReqThresholdSendCommand){
		VCutThresholdSend	*p=(VCutThresholdSend *)data;
		return true;
	}
	else if(Command==VCutReqTryThresholdCommand){
		VCutReqTryThreshold	*p=(VCutReqTryThreshold *)data;
		return true;
	}
	else if(Command==VCutSendTryThresholdCommand){
		VCutSendTryThreshold	*p=(VCutSendTryThreshold *)data;
		return true;
	}
	else{
		return AlgorithmBase::GeneralDataReply(Command,data);
	}
}


VCutThresholdReq::VCutThresholdReq(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;
}
bool	VCutThresholdReq::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	return true;
}
bool	VCutThresholdReq::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	return true;
}

VCutThresholdSend::VCutThresholdSend(void)
{
	GlobalPage=-1;
	ItemID=-1;
	Mastered=true;
	Dx=0;
	Dy=0;

	CenterBright		=0;
	CenterTargetBright	=0;
}

void	VCutThresholdSend::ConstructList(VCutThresholdReq *reqPacket,VCutInspectionBase *Base)
{
	GlobalPage	=reqPacket->GlobalPage;
	ItemID		=reqPacket->ItemID;
	Mastered	=reqPacket->Mastered;
	Dx			=reqPacket->Dx;
	Dy			=reqPacket->Dy;
	int	localPage=Base->GetLayersBase()->GetLocalPageFromGlobal(GlobalPage);
	AlgorithmInPagePI	*Ap=dynamic_cast<AlgorithmInPagePI *>(Base->GetPageData(localPage));
	if(Ap!=NULL){
		AlgorithmItemRoot	*item	=Ap->SearchIDItem(ItemID);
		if(item!=NULL){
			int	dx=0;
			int	dy=0;
			if(item->GetCurrentResult()!=NULL){
				dx=item->GetCurrentResult()->GetTotalShiftedX();
				dy=item->GetCurrentResult()->GetTotalShiftedY();
			}
			VCutInspectionItem	*BItem=(VCutInspectionItem *)item;
			/*
			if(BItem->CenterBright==0){
				BItem->CenterBright=BItem->CalcCenterBright(BItem->GetMasterBuff(),0,0);
				BItem->CenterTargetBright=BItem->CenterBright;
			}
			CenterBright	=BItem->CenterBright;
			BrightWidthL	=BItem->GetThresholdR(GetLayersBase())->BrightWidthL;
			BrightWidthH	=BItem->GetThresholdR(GetLayersBase())->BrightWidthH;

			int	TmpBrightWidthL=BrightWidthL;
			int	TmpBrightWidthH=BrightWidthH;

			AbsBrightWidthL=CenterBright-TmpBrightWidthL;
			AbsBrightWidthH=CenterBright+TmpBrightWidthH;
			
			int	iAbsBBrightWidthL=AbsBrightWidthL;
			int	iAbsBBrightWidthH=AbsBrightWidthH;
			AbsBrightWidthL	=iAbsBBrightWidthL;
			AbsBrightWidthH	=iAbsBBrightWidthH;
			
			CenterTargetBright=BItem->CalcCenterBright(BItem->GetTargetBuff(),dx,dy);
			*/
		}
		
	}
}

bool	VCutThresholdSend::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(::Save(f,Mastered)==false)
		return false;
	if(::Save(f,Dx)==false)
		return false;
	if(::Save(f,Dy)==false)
		return false;
	if(::Save(f,CenterBright)==false)
		return false;
	if(::Save(f,CenterTargetBright)==false)
		return false;

	return true;
}
bool	VCutThresholdSend::Load(QIODevice *f)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(::Load(f,Mastered)==false)
		return false;
	if(::Load(f,Dx)==false)
		return false;
	if(::Load(f,Dy)==false)
		return false;
	if(::Load(f,CenterBright)==false)
		return false;
	if(::Load(f,CenterTargetBright)==false)
		return false;

	return true;
}

VCutReqTryThreshold::VCutReqTryThreshold(void)
{
	GlobalPage=-1;
	ItemID=-1;
}
bool	VCutReqTryThreshold::Save(QIODevice *f)
{
	if(::Save(f,GlobalPage)==false)
		return false;
	if(::Save(f,ItemID)==false)
		return false;
	if(Threshold.Save(f)==false)
		return false;
	return true;
}
bool	VCutReqTryThreshold::Load(QIODevice *f,LayersBase *LBase)
{
	if(::Load(f,GlobalPage)==false)
		return false;
	if(::Load(f,ItemID)==false)
		return false;
	if(Threshold.Load(f,LBase)==false)
		return false;
	return true;
}

VCutSendTryThreshold::VCutSendTryThreshold(void)
{
	Result	=new ResultInItemPI();
	NGDot	=0;
	ResultMoveDx	=0;
	ResultMoveDy	=0;
	Error			=0;
}
VCutSendTryThreshold::~VCutSendTryThreshold(void)
{
	if(Result!=NULL){
		delete	Result;
		Result=NULL;
	}
}
bool	VCutSendTryThreshold::Save(QIODevice *f)
{
	if(Result->Save(f)==false)
		return false;
	if(::Save(f,NGDot	)==false)
		return false;
	if(::Save(f,ResultMoveDx	)==false)
		return false;
	if(::Save(f,ResultMoveDy	)==false)
		return false;
	if(::Save(f,Error			)==false)
		return false;
	if(::Save(f,ResultMinDifference	)==false)
		return false;
	return true;
}
bool	VCutSendTryThreshold::Load(QIODevice *f)
{
	if(Result->Load(f)==false)
		return false;
	if(::Load(f,NGDot	)==false)
		return false;
	if(::Load(f,ResultMoveDx	)==false)
		return false;
	if(::Load(f,ResultMoveDy	)==false)
		return false;
	if(::Load(f,Error			)==false)
		return false;
	if(::Load(f,ResultMinDifference	)==false)
		return false;
	return true;
}

void	VCutSendTryThreshold::ConstructList(VCutReqTryThreshold *reqPacket,VCutInspectionBase *Base)
{
	Result->SetAddedData(this,1,sizeof(this));
	VCutInspectionInPage		*BP=(VCutInspectionInPage *)Base->GetPageData(Base->GetLayersBase()->GetLocalPageFromGlobal(reqPacket->GlobalPage));
	if(BP!=NULL){
		VCutInspectionItem		*BI=(VCutInspectionItem *)BP->SearchIDItem(reqPacket->ItemID);
		if(BI!=NULL){
			Base->GetLayersBase()->SetStartInspectionTimeMilisec(::GetComputerMiliSec());
			
			reqPacket->Threshold.SetParent(BI->GetParent());
			//reqPacket->Threshold.GetThresholdW()->CopyFrom((AlgorithmThreshold &)*BI->GetThresholdR(GetLayersBase()));
			reqPacket->Threshold.CopyArea(*BI);
			reqPacket->Threshold.CopyThresholdOnly(BI);
			reqPacket->Threshold.SetLibID(BI->GetLibID());
			reqPacket->Threshold.SetID(BI->GetID());
			ExecuteInitialAfterEditInfo EInfo;
			EInfo.ExecuteInitialAfterEdit_Changed=ExecuteInitialAfterEdit_ChangedAlgorithm;
			reqPacket->Threshold.ExecuteInitialAfterEdit	(0,0,Result,EInfo);
			reqPacket->Threshold.ExecuteStartByInspection	(0,0,Result);
			reqPacket->Threshold.ExecuteProcessing			(0,0,Result);
		}
	}
	Result->SetAddedData(NULL,0);
	NGDot	=Result->GetResult2();
	ResultMoveDx=Result->GetTotalShiftedX();
	ResultMoveDy=Result->GetTotalShiftedY();
	ResultMinDifference=99999999;
	for(ResultPosList *r=Result->GetPosList().GetFirst();r!=NULL;r=r->GetNext()){
		if(r->GetResult1()<ResultMinDifference)
			ResultMinDifference=r->GetResult1();
	}
}
