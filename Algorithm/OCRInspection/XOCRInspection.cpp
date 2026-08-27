/*
 * Copyright (C) 2026
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

//#include "OCRInspectionResource.h"
#include "XOCRInspection.h"
#include "swap.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"
#include "XDisplayBitImage.h"
#include <QMessageBox>
#include <QBuffer>

#include <tesseract/baseapi.h>
#include <leptonica/allheaders.h>


OCRInspectionThreshold::OCRInspectionThreshold(OCRInspectionItem *parent) 
	: AlgorithmThreshold(parent)
{	
	Mergin					=0;

	RegNumber				=0;
	InspectMatching			=false;
	SaveIntoResult			=false;
	OKByFailingRecognition	=false;
	AngleDegree				=0;
	TextOneLine				=true;
	Darker					=true;
	Layer					=-1;
	ThresholdBrightness		=-1;
	ReducedNoiseSize		=-1;
	ShrinkImage				=0;
}

void	OCRInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const OCRInspectionThreshold	*s=dynamic_cast<const OCRInspectionThreshold *>(&src);
	if(s!=NULL){
		Mergin			=((OCRInspectionThreshold *)&src)->Mergin;

		RegNumber		=s->RegNumber;
		InspectMatching	=s->InspectMatching;
		SaveIntoResult	=s->SaveIntoResult;
		OKByFailingRecognition	=s->OKByFailingRecognition;
		CorrectList		=s->CorrectList;
		AngleDegree		=s->AngleDegree;
		Patterns		=s->Patterns;
		TextOneLine		=s->TextOneLine;
		Darker			=s->Darker;
		Layer			=s->Layer;
		ThresholdBrightness	=s->ThresholdBrightness;
		ReducedNoiseSize	=s->ReducedNoiseSize;
		ShrinkImage			=s->ShrinkImage;
	}
}

bool	OCRInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const OCRInspectionThreshold	*s=dynamic_cast<const OCRInspectionThreshold *>(&src);
	if(s!=NULL){
		if(Mergin			!=((OCRInspectionThreshold *)&src)->Mergin		)	return false;

		if(RegNumber		!=s->RegNumber									)	return false;
		if(InspectMatching	!=s->InspectMatching							)	return false;
		if(SaveIntoResult	!=s->SaveIntoResult								)	return false;
		if(OKByFailingRecognition	!=s->OKByFailingRecognition				)	return false;
		if(CorrectList		!=s->CorrectList								)	return false;
		if(AngleDegree		!=s->AngleDegree								)	return false;
		if(Patterns			!=s->Patterns									)	return false;
		if(TextOneLine		!=s->TextOneLine								)	return false;
		if(Darker			!=s->Darker										)	return false;
		if(Layer			!=s->Layer										)	return false;
		if(ThresholdBrightness	!=s->ThresholdBrightness					)	return false;
		if(ReducedNoiseSize		!=s->ReducedNoiseSize						)	return false;
		if(ShrinkImage			!=s->ShrinkImage							)	return false;
		
		return  true;
	}
	return false;
}
	
bool	OCRInspectionThreshold::Save(QIODevice *f)
{
	WORD	Ver=3;

	if(::Save(f,Ver)==false)
		return(false);

	if(::Save(f,Mergin)==false)
		return false;

	if(::Save(f,RegNumber)==false)
		return false;
	if(::Save(f,InspectMatching)==false)
		return false;
	if(::Save(f,SaveIntoResult)==false)
		return false;
	if(::Save(f,OKByFailingRecognition)==false)
		return false;
	if(::Save(f,CorrectList)==false)
		return false;
	if(::Save(f,AngleDegree)==false)
		return false;
	if(::Save(f,Patterns)==false)
		return false;
	if(::Save(f,TextOneLine)==false)
		return false;
	if(::Save(f,Darker)==false)
		return false;
	if(::Save(f,Layer)==false)
		return false;
	if(::Save(f,ThresholdBrightness)==false)
		return false;
	if(::Save(f,ReducedNoiseSize)==false)
		return false;
	if(::Save(f,ShrinkImage)==false)
		return false;	
	return true;
}
	
bool	OCRInspectionThreshold::Load(QIODevice *f)
{
	WORD	Ver;

	if(::Load(f,Ver)==false)
		return(false);

	if(::Load(f,Mergin)==false)
		return false;

	if(::Load(f,RegNumber)==false)
		return false;
	if(::Load(f,InspectMatching)==false)
		return false;
	if(::Load(f,SaveIntoResult)==false)
		return false;
	if(::Load(f,OKByFailingRecognition)==false)
		return false;
	if(::Load(f,CorrectList)==false)
		return false;
	if(Ver>=2){
		if(::Load(f,AngleDegree)==false)
			return false;
		if(::Load(f,Patterns)==false)
			return false;
		if(::Load(f,TextOneLine)==false)
			return false;
		if(::Load(f,Darker)==false)
			return false;
		if(::Load(f,Layer)==false)
			return false;
		if(::Load(f,ThresholdBrightness)==false)
			return false;
		if(::Load(f,ReducedNoiseSize)==false)
			return false;
	}
	if(Ver>=3){
		if(::Load(f,ShrinkImage)==false)
			return false;	
	}
	return true;
}

//===============================================================================================================================
OCRInspectionItem::OCRInspectionItem(void)
{
	XByte	=0;
	XLen	=0;
	YLen	=0;
	Mx=My=0;
	AVector=NULL;
	TmpMap	=NULL;
	TmpMap2	=NULL;
	LW		=0;
	LH		=0;
}

OCRInspectionItem::~OCRInspectionItem(void)
{
	if(TmpMap!=NULL){
		DeleteMatrixBuff(TmpMap,LH);
		TmpMap=NULL;
	}
	if(TmpMap2!=NULL){
		DeleteMatrixBuff(TmpMap2,LH);
		TmpMap2=NULL;
	}
}

void	MakeBrightTable(const QImage &Image,int BrightTable[3][256])
{
	if(Image.format()==QImage::Format_RGB888){
		int	W=Image.width();
		int	H=Image.height();
		for(int y=0;y<H;y++){
			const uchar *p=Image.scanLine(y);
			for(int x=0;x<W;x++){
				int	r=p[0];
				int	g=p[1];
				int	b=p[2];
				BrightTable[0][r]++;
				BrightTable[1][g]++;
				BrightTable[2][b]++;
				p+=3;
			}
		}
	}
	else if(Image.format()==QImage::Format_ARGB32_Premultiplied	
	|| Image.format()==QImage::Format_RGB32
	|| Image.format()==QImage::Format_ARGB32){
		int	W=Image.width();
		int	H=Image.height();
		for(int y=0;y<H;y++){
			const uchar *p=Image.scanLine(y);
			for(int x=0;x<W;x++){
				int	r=p[0];
				int	g=p[1];
				int	b=p[2];
				BrightTable[0][r]++;
				BrightTable[1][g]++;
				BrightTable[2][b]++;
				p+=4;
			}
		}
	}
}

void	CalcCenterLevel(int BrightTable[3][256]
						,int CenterLevel[3]
						,double VariableValue[3]
						,double Adopted)
{
	for(int i=0;i<3;i++){
		int	Total=0;
		qint64	Count=0;
		for(int j=0;j<256;j++){
			Count+=BrightTable[i][j];
		}
		int OmitCount = Count*(1.0-Adopted)/2;
		int	TmpSum=0;
		int LLevel = 0;
		int HLevel = 255;
		for(int j=0;j<256;j++){
			if(TmpSum+BrightTable[i][j]>OmitCount){
				break;
			}
			TmpSum+=BrightTable[i][j];
			LLevel =j;
		}
		TmpSum=0;
		for(int j = 255;j>=0;j--){
			if(TmpSum+BrightTable[i][j]>OmitCount){
				break;
			}
			TmpSum+=BrightTable[i][j];
			HLevel = j;
		}
		CenterLevel[i]=0;
		qint64	AddedSum = 0;
		int AddedCount = 0;	
		for(int j=LLevel;j<HLevel;j++){
			AddedSum +=	BrightTable[i][j]*j;
			AddedCount += BrightTable[i][j];
		}
		double	Average = 0;
		if(AddedCount>0){
			Average = (double)AddedSum/(double)AddedCount;
			CenterLevel[i] = AddedSum/AddedCount;
		}
		for(int j=LLevel;j<HLevel;j++){
			double	d = (double)j-Average;
			VariableValue[i] += d*d*BrightTable[i][j];
		}
		if(AddedCount>0){
			VariableValue[i] /= (double)AddedCount;
		}
		else{
			VariableValue[i] = 0;
		}
	}
}
const	int	XMergin=16;
const	int	YMergin=16;

ExeResult	OCRInspectionItem::ExecuteInitialAfterEdit	(int ExeID,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmItemPI::ExecuteInitialAfterEdit	(ExeID,ThreadNo,Res,EInfo);


	AllocateBuff();

	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);
	Mx=My=0;

	int Len=sqrt(XLen*XLen+YLen*YLen);
	LW		=Len+16*2+2;
	LWByte	= (LW+7)/8;
	LH		=Len+16*2;
	OCRImage = QImage(LW,LH,QImage::Format_RGB32);
	TmpMap	= MakeMatrixBuff(LWByte,LH);
	TmpMap2 = MakeMatrixBuff(LWByte,LH);
	return Ret;
}

void	MakeImageFromBinaryBit(QImage &Dest ,BYTE **BMap ,QRgb c1,QRgb c0,int XLen ,int YLen)
{
	int	DstXLen=Dest.width();
	int	DstYLen=Dest.height();

	int	tXLen=min(XLen,DstXLen);
	int tYLen=min(YLen,DstYLen);
	for(int y=0;y<tYLen;y++){
		QRgb	*d=(QRgb *)Dest.scanLine(y);
		BYTE	*s=BMap[y];
		for(int x=0;x<tXLen;x++){
			if(GetBmpBitOnY(s,x)!=0){
				*d=c1;
			}
			else{
				*d=c0;
			}
			d++;
		}
	}
}


void	OCRInspectionItem::AllocateBuff(void)
{
	int	iYLen		=GetArea().GetHeight()+YMergin*2;
	if(iYLen>=GetMaxLines())
		iYLen = GetMaxLines()-1;
	int	iXLen		=GetArea().GetWidth()+XMergin*2;
	if(iXLen>=GetDotPerLine())
		iXLen = GetDotPerLine()-1;
	int	iXByte		=(XLen+7)/8;

	if(iXLen!=XLen || iYLen!=YLen){
		YLen		=iYLen;
		XLen		=iXLen;
		XByte		=(XLen+7)/8;
		Map = QImage(XLen,YLen,QImage::Format_RGB888);
		Map.fill(Qt::black);
	}
}

ExeResult	OCRInspectionItem::ExecuteProcessing		(int ExeID,int ThreadNo,ResultInItemRoot *Res)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);
	Result.clear();
	Calc(ImageList);
	const OCRInspectionThreshold	*RThr=GetThresholdR();
	if(Result.isEmpty()==false){
		if(RThr->InspectMatching==true){
			if(Match(Result)==true)
				Res->SetError(1);
			else{
				Res->SetError(2);
			}
		}
	}
	else{
		if(RThr->OKByFailingRecognition==true){
			Res->SetError(1);
		}
		else{
			Res->SetError(2);
		}
	}

	if(RThr->SaveIntoResult==true){
		ResultInspection	*R=Res->GetResultInspection();
		if(R!=NULL){
			R->SetInspectionBarcode(Result);
		}
	}

	return _ER_true;
}
bool	OCRInspectionItem::Match(QString &_Result)
{
	const OCRInspectionThreshold	*RThr=GetThresholdR();
	int i;
	for(i=0;i<RThr->CorrectList.count();i++){
		QRegularExpression	E(RThr->CorrectList[i]);
		QRegularExpressionMatch match = E.match(Result);
		if(match.hasMatch()==true){
			return true;
		}
	}
	return false;
}
bool	OCRInspectionItem::Calc(ImagePointerContainer &ImageList)
{
	if(AVector!=NULL){
		Mx=AVector->ShiftX;
		My=AVector->ShiftY;
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
		Mx=V.ShiftX;
		My=V.ShiftY;
	}

	const	OCRInspectionThreshold *RThr = GetThresholdR();
	Result=/**/"";
	OCRInspectionBase		*ABase=(OCRInspectionBase *)GetParentBase();
	if(ABase!=NULL){
		try{
			AllocateBuff();
			//QImage	Map(XLen,YLen,QImage::Format_RGB888);
			MakeImage(Map,Mx,My,ImageList);

			Map.save("TestOCRMap.png","PNG");

			int  BrightTable[3][256];
			memset(BrightTable,0,sizeof(BrightTable));
			MakeBrightTable(Map,BrightTable);
			int  CenterLevel[3];
			double VariableValue[3];
			CalcCenterLevel(BrightTable,CenterLevel,VariableValue,0.8);

			int  CurrentLayer=RThr->Layer;
			if(CurrentLayer<0){
				if(VariableValue[0]>VariableValue[1] && VariableValue[0]>VariableValue[2]){
					CurrentLayer=0;
				}
				else if(VariableValue[1]>VariableValue[2]){
					CurrentLayer=1;
				}
				else{
					CurrentLayer=2;
				}
			}
			QRgb	CenterColor = qRgb(CenterLevel[0],CenterLevel[1],CenterLevel[2]);
			OCRImage.fill(CenterColor);

			int	ThresholdBrightness = RThr->ThresholdBrightness;
			int SrcCx=XLen/2;
			int SrcCy=YLen/2;
			int DstCx = LW/2;
			int DstCy = LH/2;

			double	Angle = RThr->AngleDegree*M_PI/180.0;
			double	cosA = cos(Angle);
			double	sinA = sin(Angle);
			for(int y=0;y<LH;y++){
				QRgb *Dst = (QRgb *)OCRImage.scanLine(y);
				for(int x=0;x<LW;x++){
					int	SrcX = (int)(cosA*(x-DstCx)+sinA*(y-DstCy)+SrcCx);
					int	SrcY = (int)(-sinA*(x-DstCx)+cosA*(y-DstCy)+SrcCy);
					if(0<=SrcX && SrcX<XLen && 0<=SrcY && SrcY<YLen){
						QRgb	p=Map.pixel(SrcX,SrcY);
						Dst[x] = p;
					}
				}
			}
			if(RThr->ThresholdBrightness>0){
				
				MatrixBuffClear	(TmpMap ,0 ,LWByte,LH);
				for(int y=0;y<LH;y++){
					QRgb *s = (QRgb *)OCRImage.scanLine(y);
					BYTE *d = TmpMap[y];
					for(int x = 0;x<LW;x++,s++){
						if(CurrentLayer==0){
							if((RThr->Darker==true  && qRed(*s)<RThr->ThresholdBrightness)
							|| (RThr->Darker==false && qRed(*s)>RThr->ThresholdBrightness)){
								SetBmpBitOnY1(d,x);
							}
						}
						else if(CurrentLayer==1){
							if((RThr->Darker==true  && qGreen(*s)<RThr->ThresholdBrightness)
							|| (RThr->Darker==false  && qGreen(*s)>RThr->ThresholdBrightness)){
								SetBmpBitOnY1(d,x);
							}
						} 
						else if(CurrentLayer==2){
							if((RThr->Darker==true  && qBlue(*s)<RThr->ThresholdBrightness)
							|| (RThr->Darker==false  && qBlue(*s)>RThr->ThresholdBrightness)){
								SetBmpBitOnY1(d,x);
							}
						}
					}
				}
				if(RThr->ReducedNoiseSize>0){
					::FatArea (TmpMap,TmpMap2 ,LWByte,LH);
					::ThinArea(TmpMap,TmpMap2 ,LWByte,LH);
					::ThinArea(TmpMap,TmpMap2 ,LWByte,LH);
					::FatArea (TmpMap,TmpMap2 ,LWByte,LH);

					PureFlexAreaListContainer FPack;
					PickupFlexArea(TmpMap ,LWByte ,LW,LH ,FPack);
					MatrixBuffClear	(TmpMap ,0 ,LWByte,LH);
					for(PureFlexAreaList *f=FPack.GetFirst();f!=NULL;f=f->GetNext()){
						if(f->GetPatternByte()>RThr->ReducedNoiseSize){
							f->MakeBitData(TmpMap ,LW,LH);
						}
					}
					if(RThr->ShrinkImage>0){
						for(int k=0;k<RThr->ShrinkImage;k++){
							::ThinArea(TmpMap,TmpMap2 ,LWByte,LH);
						}
					}
					if(RThr->ShrinkImage<0){
						for(int k=0;k<-RThr->ShrinkImage;k++){
							::FatArea(TmpMap,TmpMap2 ,LWByte,LH);
						}
					}

					::FatArea (TmpMap,TmpMap2 ,LWByte,LH);
				}
				MakeImageFromBinaryBit(OCRImage ,TmpMap ,qRgb(0,0,0),qRgb(255,255,255),LW,LH);
			}

			ABase->GetOCR(OCRImage,RThr,Result);
		}
		catch(...){}
		
	}

	return true;
}

void	OCRInspectionItem::MakeImage(QImage &Map,int mx,int my,ImagePointerContainer &ImageList)
{
	int	X1 = GetArea().GetMinX()+mx-XMergin;
	int	Y1 = GetArea().GetMinY()+my-YMergin;
	int	X2 = GetArea().GetMaxX()+mx+XMergin;
	int	Y2 = GetArea().GetMaxY()+my+YMergin;

	if(X1<0)			X1 = 0;
	if(Y1<0)			Y1 = 0;
	if(X2>=GetDotPerLine())	X1 -= X2-GetDotPerLine();
	if(Y2>=GetMaxLines())	Y1 -= Y2-GetMaxLines();


	QColor	Col=ImageList.GetAverageColor(GetArea(),mx,my);
	Map.fill(Col.rgb());

	int	N=GetArea().GetFLineLen();
	if(ImageList.GetCount()>=3){
		for(int i=0;i<N;i++){
			int	LeftX	=GetArea().GetFLineLeftX(i);
			int	Y		=GetArea().GetFLineAbsY(i);
			int Numb	=GetArea().GetFLineNumb(i);
			BYTE	*R=ImageList[0]->GetY(Y+my);
			BYTE	*G=ImageList[1]->GetY(Y+my);
			BYTE	*B=ImageList[2]->GetY(Y+my);

			BYTE	*d=((BYTE *)Map.scanLine(Y-Y1))+(LeftX-X1)*3;
			for(int n=0;n<Numb;n++){
				int	X=LeftX+n;
				d[0]=R[X+mx];
				d[1]=G[X+mx];
				d[2]=B[X+mx];
				d+=3;
			}
		}
	}
	else{
		for(int i=0;i<N;i++){
			int	LeftX	=GetArea().GetFLineLeftX(i);
			int	Y		=GetArea().GetFLineAbsY(i);
			int Numb	=GetArea().GetFLineNumb(i);
			BYTE	*R=ImageList[0]->GetY(Y+my);
			BYTE	*d=((BYTE *)Map.scanLine(Y-Y1))+(LeftX-X1)*3;
			for(int n=0;n<Numb;n++){
				int	X=LeftX+n;
				d[0]=R[X+mx];
				d[1]=R[X+mx];
				d[2]=R[X+mx];
				d+=3;
			}
		}
	}
	//ImageList.MakeImage(Map ,-X1 ,-Y1);
}

static	int	Clip255(int n,int d)
{
	if(n<0)	return d-20;
	else	return d+20;
}


QString	OCRInspectionItem::OutputResult(ResultPosList *p)
{
	return QString(/**/"OCR=")+Result;
}
	
void	OCRInspectionItem::Draw(QImage &pnt, int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	OCRInspectionDrawAttr	*A=dynamic_cast<OCRInspectionDrawAttr *>(Attr);
	if(A!=NULL){
		AlgorithmItemPI::DrawAlpha(pnt, movx ,movy ,ZoomRate ,Attr);
	}
}
	
void	OCRInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	AlgorithmItemPI::DrawResultItem(Res,IData ,PData ,MovX ,MovY ,ZoomRate,OnlyNG);

	int	cx,cy;
	GetArea().GetCenter(cx,cy);
	int	kx=(cx+MovX+Mx)*ZoomRate;
	int	ky=(cy+MovY+My)*ZoomRate;
	if(0<=kx && (kx+120)<IData.width() && 0<=ky && (ky+40)<IData.height()){
		QRect	rect(0,0,IData.width(),IData.height());
		PData.drawText(kx,ky,IData.width()-kx,IData.height()-ky
			,Qt::AlignLeft | Qt::AlignTop
			,QString(/**/" Sft(")+QString::number(Mx)+QString(/**/",")+QString::number(My)+QString(/**/")")
			,&rect);
		PData.drawText(kx,ky+16,IData.width()-kx,IData.height()-ky
			,Qt::AlignLeft | Qt::AlignTop
			,Result
			,&rect);
	}
}

//=================================================================

void	OCRInspectionInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqOCRList	*CmdReqOCRListVar=dynamic_cast<CmdReqOCRList *>(packet);
	if(CmdReqOCRListVar!=NULL){
		for(AlgorithmItemPI *a=GetFirstData();a!=NULL;a=a->GetNext()){
			OCRInspectionItem	*Item=dynamic_cast<OCRInspectionItem *>(a);
			if(Item!=NULL){
				OCRList	*k=new OCRList();
				k->GlobalPage				=GetLayersBase()->GetGlobalPageFromLocal(GetPage());
				k->ItemID					=Item->GetID();
				k->ItemName					=Item->GetItemName();
				const OCRInspectionThreshold	*RThr=Item->GetThresholdR(GetLayersBase());
				k->Mergin		=RThr->Mergin		;
		
				k->RegNumber				=RThr->RegNumber			;
				k->InspectMatching			=RThr->InspectMatching		;
				k->SaveIntoResult			=RThr->SaveIntoResult		;
				k->OKByFailingRecognition	=RThr->OKByFailingRecognition;
				k->CorrectList				=RThr->CorrectList			;

				k->AngleDegree				=RThr->AngleDegree			;
				k->Patterns					=RThr->Patterns				;
				k->TextOneLine				=RThr->TextOneLine			;
				k->Darker					=RThr->Darker				;
				k->Layer					=RThr->Layer				;
				k->ThresholdBrightness		=RThr->ThresholdBrightness	;
				k->ReducedNoiseSize			=RThr->ReducedNoiseSize		;
				k->ShrinkImage				=RThr->ShrinkImage			;

				Item->GetArea().GetXY(k->x1,k->y1,k->x2,k->y2);
				
				CmdReqOCRListVar->Container->AppendList(k);
			}
		}
		return;
	}
	CmdReqBCodeTest	*CmdReqBCodeTestVar=dynamic_cast<CmdReqBCodeTest *>(packet);
	if(CmdReqBCodeTestVar!=NULL){
		AlgorithmItemRoot	*a=SearchIDItem(CmdReqBCodeTestVar->ItemID);
		if(a!=NULL){
			OCRInspectionItem	*Item=dynamic_cast<OCRInspectionItem *>(a);
			if(Item!=NULL){

				ImagePointerContainer ImageList;
				if(CmdReqBCodeTestVar->Mastered==true){
					Item->GetMasterBuffList(ImageList);
				}
				else{
					Item->GetTargetBuffList(ImageList);
				}
				Item->Calc(ImageList);
				CmdReqBCodeTestVar->Result	=Item->Result;
				CmdReqBCodeTestVar->Mastered=Item->Match(Item->Result);	
			}
		}
		return;
	}
	AddOCRInspectionAreaPacket	*AddOCRInspectionAreaVar=dynamic_cast<AddOCRInspectionAreaPacket *>(packet);
	if(AddOCRInspectionAreaVar!=NULL){
		OCRInspectionItem	*Item=new OCRInspectionItem();
		Item->SetArea(AddOCRInspectionAreaVar->Area);
		Item->SetItemName(AddOCRInspectionAreaVar->ItemName);
		Item->GetThresholdW()->Mergin		=AddOCRInspectionAreaVar->Mergin;

		Item->GetThresholdW()->RegNumber				=AddOCRInspectionAreaVar->RegNumber;
		Item->GetThresholdW()->InspectMatching			=AddOCRInspectionAreaVar->InspectMatching;
		Item->GetThresholdW()->SaveIntoResult			=AddOCRInspectionAreaVar->SaveIntoResult;
		Item->GetThresholdW()->OKByFailingRecognition	=AddOCRInspectionAreaVar->OKByFailingRecognition;
		Item->GetThresholdW()->CorrectList				=AddOCRInspectionAreaVar->CorrectList;

		Item->GetThresholdW()->AngleDegree				=AddOCRInspectionAreaVar->AngleDegree			;
		Item->GetThresholdW()->Patterns					=AddOCRInspectionAreaVar->Patterns				;
		Item->GetThresholdW()->TextOneLine				=AddOCRInspectionAreaVar->TextOneLine			;
		Item->GetThresholdW()->Darker					=AddOCRInspectionAreaVar->Darker				;
		Item->GetThresholdW()->Layer					=AddOCRInspectionAreaVar->Layer					;
		Item->GetThresholdW()->ThresholdBrightness		=AddOCRInspectionAreaVar->ThresholdBrightness	;
		Item->GetThresholdW()->ReducedNoiseSize			=AddOCRInspectionAreaVar->ReducedNoiseSize		;
		Item->GetThresholdW()->ShrinkImage				=AddOCRInspectionAreaVar->ShrinkImage			;

		AppendItem(Item);
		return;
	}
	UpdateOCRInspectionAreaPacket	*UpdateOCRInspectionAreaPacketVar=dynamic_cast<UpdateOCRInspectionAreaPacket *>(packet);
	if(UpdateOCRInspectionAreaPacketVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(UpdateOCRInspectionAreaPacketVar->ItemID);
		Item->SetItemName(UpdateOCRInspectionAreaPacketVar->ItemName);
		Item->GetThresholdW()->Mergin		=UpdateOCRInspectionAreaPacketVar->Mergin;

		Item->GetThresholdW()->RegNumber				=UpdateOCRInspectionAreaPacketVar->RegNumber;
		Item->GetThresholdW()->InspectMatching			=UpdateOCRInspectionAreaPacketVar->InspectMatching;
		Item->GetThresholdW()->SaveIntoResult			=UpdateOCRInspectionAreaPacketVar->SaveIntoResult;
		Item->GetThresholdW()->OKByFailingRecognition	=UpdateOCRInspectionAreaPacketVar->OKByFailingRecognition;
		Item->GetThresholdW()->CorrectList				=UpdateOCRInspectionAreaPacketVar->CorrectList;

		Item->GetThresholdW()->AngleDegree				=UpdateOCRInspectionAreaPacketVar->AngleDegree			;
		Item->GetThresholdW()->Patterns					=UpdateOCRInspectionAreaPacketVar->Patterns				;
		Item->GetThresholdW()->TextOneLine				=UpdateOCRInspectionAreaPacketVar->TextOneLine			;
		Item->GetThresholdW()->Darker					=UpdateOCRInspectionAreaPacketVar->Darker				;
		Item->GetThresholdW()->Layer					=UpdateOCRInspectionAreaPacketVar->Layer				;
		Item->GetThresholdW()->ThresholdBrightness		=UpdateOCRInspectionAreaPacketVar->ThresholdBrightness	;
		Item->GetThresholdW()->ReducedNoiseSize			=UpdateOCRInspectionAreaPacketVar->ReducedNoiseSize		;
		Item->GetThresholdW()->ShrinkImage				=UpdateOCRInspectionAreaPacketVar->ShrinkImage			;
		return;
	}
	DeleteOCRInspectionAreaPacket	*DeleteOCRInspectionAreaPacketVar=dynamic_cast<DeleteOCRInspectionAreaPacket *>(packet);
	if(DeleteOCRInspectionAreaPacketVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(DeleteOCRInspectionAreaPacketVar->ItemID);
		RemoveItem(Item);
		return;
	}
	ReqOCRItemPacket	*ReqOCRItemPacketVar=dynamic_cast<ReqOCRItemPacket *>(packet);
	if(ReqOCRItemPacketVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(ReqOCRItemPacketVar->ItemID);
		ReqOCRItemPacketVar->Area	=Item->GetArea();
		return;
	}

	CmdReqOCRTest	*CmdReqOCRTestVar=dynamic_cast<CmdReqOCRTest *>(packet);
	if(CmdReqOCRTestVar!=NULL){
		OCRInspectionItem	*Item=(OCRInspectionItem *)SearchIDItem(CmdReqOCRTestVar->ItemID);

		ImagePointerContainer ImageList;
		GetTargetBuffList(ImageList);
		Item->Result.clear();
		Item->Calc(ImageList);

		CmdReqOCRTestVar->Result	=Item->Result;
		CmdReqOCRTestVar->OCRImage	=Item->OCRImage;
		return;
	}
	CmdReqOCRResults *CmdReqOCRResultsVar = dynamic_cast<CmdReqOCRResults *>(packet);
	if(CmdReqOCRResultsVar!= NULL) {
		for (AlgorithmItemPI* a = GetFirstData(); a != NULL; a = a->GetNext()) {
			OCRInspectionItem* Item = dynamic_cast<OCRInspectionItem*>(a);
			if (Item != NULL) {
				if(CmdReqOCRResultsVar->ItemName.isEmpty()==true
				|| Item->GetItemName()==CmdReqOCRResultsVar->ItemName){
					CmdReqOCRResultsVar->ResultOCR=Item->Result;
				}
			}
		}
		return;
	}
}

//=================================================================

OCRInspectionBase::OCRInspectionBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	ColorOCR			=Qt::green;
	ColorSelected		=Qt::yellow;
	ColorActive			=Qt::red;
	TransparentLevel	=120;
	NegColorOCR			=Qt::darkGreen;
	NegColorSelected	=Qt::darkYellow;
	AdotpedLayer		=0;
	OcrApi				=NULL;
	OCRDataPath			="./tessdata";
	OCRLanguage			= "jpn";

	SetParam(&AdotpedLayer		, /**/"Setting"		,/**/"AdotpedLayer"		,"Adotped Layer , -1:Color");	
	SetParam(&OCRDataPath		, /**/"Setting"		,/**/"OCRDataPath"		,"OCR Data Path (./tessdata)");	
	SetParam(&OCRLanguage		, /**/"Setting"		,/**/"OCRLanguage"		,"Language name(jpn)");	
}

OCRInspectionBase::~OCRInspectionBase(void)
{
	if(OcrApi!=NULL){
		OcrApi->End();
        delete OcrApi;
		OcrApi = NULL;
	}
}

AlgorithmDrawAttr	*OCRInspectionBase::CreateDrawAttr(void)
{
	return new OCRInspectionDrawAttr();
}

void	OCRInspectionBase::InitialAfterParamLoaded(void)
{
    OcrApi = new tesseract::TessBaseAPI();
    
    
	char *OCRDataPathCStr = new char[OCRDataPath.length() + 1];
	std::strcpy(OCRDataPathCStr,OCRDataPath.toStdString().c_str());
	char *OCRLanguageCStr = new char[OCRLanguage.length() + 1];
	std::strcpy(OCRLanguageCStr,OCRLanguage.toStdString().c_str());

	QDir::setCurrent(GetLayersBase()->GetSystemPath());
    if (OcrApi->Init(OCRDataPathCStr, OCRLanguageCStr)) { 
        delete OcrApi;
		OcrApi = NULL;
    }

	delete[] OCRDataPathCStr;
	delete[] OCRLanguageCStr;
}

void	OCRInspectionBase::TransmitDirectly(GUIDirectMessage *packet)
{

}


bool	OCRInspectionBase::GetOCR(const QString &FileName ,QString &Result)
{
    QImage image(FileName);
    if (image.isNull()) {
        return false;
    }
	return GetOCR(image ,NULL,Result);
}


bool	OCRInspectionBase::GetOCR(const QImage &Image ,const OCRInspectionThreshold *RThr ,QString &Result)
{
	if(OcrApi!=NULL && RThr!=NULL){
		if(RThr->Patterns.size()>0){
			QByteArray	Array=RThr->Patterns.toLocal8Bit();
			char *fp = Array.data();
			OcrApi->SetVariable("tessedit_char_whitelist", fp); 
		}
		if(RThr->TextOneLine==true){
			OcrApi->SetPageSegMode(tesseract::PSM_SINGLE_LINE);
		}
		else{
			OcrApi->SetPageSegMode(tesseract::PSM_AUTO);
		}
	}

	QImage	image;
	QImage	*pImage;
	if(Image.format() != QImage::Format_RGB888){
		image = Image.convertToFormat(QImage::Format_RGB888);
		pImage=&image;
	}
	else{
		pImage = (QImage *)&Image;
	}

	pImage->save("TestOCR.png","PNG");

	if(OcrApi!=NULL){
		int	XLen=pImage->width();
		int	YLen=pImage->height();
		OcrApi->SetImage(
				pImage->bits(), 
				XLen,          
				YLen,         
				3,                      
				pImage->bytesPerLine()    
			);

		// 4. �����F���̎��s
		char* outText = OcrApi->GetUTF8Text();
		Result = QString::fromUtf8(outText);
		// 5. ���Еt��
		delete[] outText;
		return true;
	}

	return false;
}