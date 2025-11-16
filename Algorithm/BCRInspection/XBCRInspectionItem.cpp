#include "BCRInspectionResource.h"
#include "swap.h"
#include "XBCRInspection.h"
#include "DTKBarReader.h"
#include "DTKImage.h"
#include "fftw3.h"
#include "XCriticalFunc.h"

//==================================================================================

BCRInspectionThreshold::BCRInspectionThreshold(BCRInspectionItem *parent) 
	: AlgorithmThreshold(parent)
{
	CheckType			=0;
	QuilityGrade		=10;
	BarcodeOrientation	=0;
	BarcodeType			=0;
	BarcodeIsOnlyDigit	=true;
}
	
void	BCRInspectionThreshold::CopyFrom(const AlgorithmThreshold &src)
{
	const BCRInspectionThreshold	*s=dynamic_cast<const BCRInspectionThreshold *>(&src);
	CheckType			=s->CheckType;
	QuilityGrade		=s->QuilityGrade;
	GradeList			=s->GradeList;
	BarcodeOrientation	=s->BarcodeOrientation;
	BarcodeType			=s->BarcodeType;
	BarcodeIsOnlyDigit	=s->BarcodeIsOnlyDigit;
}
	
bool	BCRInspectionThreshold::IsEqual(const AlgorithmThreshold &src)	const 
{
	const BCRInspectionThreshold	*s=dynamic_cast<const BCRInspectionThreshold *>(&src);
	if(CheckType		==s->CheckType
	&& QuilityGrade		==s->QuilityGrade
	&& GradeList		==s->GradeList
	&& BarcodeOrientation==s->BarcodeOrientation
	&& BarcodeType		==s->BarcodeType
	&& BarcodeIsOnlyDigit==s->BarcodeIsOnlyDigit){
		return true;
	}
	return false;
}
	
bool	BCRInspectionThreshold::Save(QIODevice *f)
{
	int	Ver=1;

	int	d=(Ver<<8);
	if(::Save(f,d			)==false)	return false;

	if(::Save(f,CheckType	)==false)	return false;
	if(::Save(f,QuilityGrade)==false)	return false;
	if(GradeList.Save(f)	==false)	return false;
	if(::Save(f,BarcodeOrientation	)==false)	return false;
	if(::Save(f,BarcodeType			)==false)	return false;
	if(::Save(f,BarcodeIsOnlyDigit	)==false)	return false;
	return true;
}
	
bool	BCRInspectionThreshold::Load(QIODevice *f)
{
	int	Ver;

	int	d;
	if(::Load(f,d			)==false)	return false;

	Ver=d>>8;
	if(Ver==0){
		CheckType=d;
		//if(::Load(f,CheckType	)==false)	return false;
		if(::Load(f,QuilityGrade)==false)	return false;
		if(GradeList.Load(f)	==false)	return false;
	}
	else if(Ver==1){
		if(::Load(f,CheckType	)==false)	return false;
		if(::Load(f,QuilityGrade)==false)	return false;
		if(GradeList.Load(f)	==false)	return false;
		if(::Load(f,BarcodeOrientation	)==false)	return false;
		if(::Load(f,BarcodeType			)==false)	return false;
		if(::Load(f,BarcodeIsOnlyDigit	)==false)	return false;
	}
	return true;
}
	
//==================================================================================

BCRInspectionItem::BCRInspectionItem(void)
{	
	BCRType=0;
	AVector=NULL;

	for(int i=0;i<4;i++){
		FFT_in[i]	=NULL;
		FFT_out[i]	=NULL;
		FFTLen[i]	=0;
		FPlan[i]	=NULL;
	}
}

BCRInspectionItem::~BCRInspectionItem(void)
{
	for(int i=0;i<4;i++){
		if(FFT_in[i]!=NULL)
			fftw_free(FFT_in[i]);
		if(FFT_out[i]!=NULL)
			fftw_free(FFT_out[i]);

		if(FPlan[i]!=NULL){
			fftw_free(FPlan[i]);
		}

		FFT_in[i]	=NULL;
		FFT_out[i]	=NULL;
		FFTLen[i]	=0;
		FPlan[i]	=NULL;
	}
}


ExeResult	BCRInspectionItem::ExecuteInitialAfterEdit	(int ExeID ,int ThreadNo
														,ResultInItemRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	int	cx,cy;
	GetCenter(cx,cy);
	AVector=(AlignmentPacket2D *)GetAlignmentPointer(cx,cy);
	if(AVector!=NULL)
		AVector->Set(this);

	int	x1,y1,x2,y2;
	GetArea().GetXY(x1,y1,x2,y2);

	FFTLen[0]=y2-y1;
	FFTLen[1]=x2-x1;
	FFTLen[2]=hypot(x2-x1,y2-y1);
	FFTLen[3]=hypot(x2-x1,y2-y1);

	for(int i=0;i<4;i++){
		if(FFT_in[i]!=NULL)
			fftw_free(FFT_in[i]);
		if(FFT_out[i]!=NULL)
			fftw_free(FFT_out[i]);

		FFT_in[i]	=(fftw_complex*)fftw_malloc( sizeof(fftw_complex)*FFTLen[i] );
		FFT_out[i]	=(fftw_complex*)fftw_malloc( sizeof(fftw_complex)*FFTLen[i] );

		FPlan[i]=fftw_plan_dft_1d( FFTLen[i], FFT_in[i], FFT_out[i], FFTW_FORWARD, FFTW_ESTIMATE );
	}

	return _ER_true;
}

ExeResult	BCRInspectionItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
	ImagePointerContainer ImageList;
	GetTargetBuffList(ImageList);

	const	BCRInspectionThreshold	*H=GetThresholdR();
	if(H->CheckType==0){
		Calc2D(ImageList);
		ResultInspection	*R=Res->GetResultInspection();
		if(R!=NULL){
			R->SetInspectionBarcode(Result);
		}
	}
	else if(H->CheckType==1){
		CheckQuality(ImageList,Res);
	}
	else if(H->CheckType==2){
		if(Calc1D(ImageList)==true){
			Res->SetAlignedXY(ResultMx,ResultMy);
			Res->SetResultMessage(Result);
			Res->SetError(1);
		}
		else{
			Res->SetAlignedXY(ResultMx,ResultMy);
			Res->SetResultMessage(/**/"");
			Res->SetError(2);
		}
		ResultInspection	*R=Res->GetResultInspection();
		if(R!=NULL){
			R->SetInspectionBarcode(Result);
		}
	}
	return _ER_true;
}

void	BCRInspectionItem::DrawResultItem(ResultInItemRoot *Res,QImage &IData ,QPainter &PData ,int MovX ,int MovY ,double ZoomRate,bool OnlyNG)
{
	if(Res==NULL){
		Res=GetCurrentResult();
	}
	if(Res!=NULL && GetPhaseCode()==GetLayersBase()->GetCurrentPhase()){
		if(GetThresholdR()->CheckType==0){
			QColor	c=Qt::yellow;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);

			int	Cx,Cy;
			GetArea().GetCenter(Cx,Cy);
			int	X=(Cx+MovX)*ZoomRate;
			int	Y=(Cy+MovY)*ZoomRate;
			PData.drawText(X,Y,QString("Barcode-2D: ")
							  +Result);
		}
		else
		if(GetThresholdR()->CheckType==1){
			QColor	c=Qt::red;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);

			int	Cx,Cy;
			GetArea().GetCenter(Cx,Cy);
			int	X=(Cx+MovX)*ZoomRate;
			int	Y=(Cy+MovY)*ZoomRate;
			PData.drawText(X,Y,QString(LangSolver.GetString(XBCRInspection_LS,LID_12)/*"Quarily: "*/)
							  +QString::number(Res->GetResultDouble(),'f',3));
			ResultPosList	*R=Res->GetPosListFirst();
			if(R!=NULL){
				PData.drawText(X,Y+16,QString(LangSolver.GetString(XBCRInspection_LS,LID_13)/*"Grade: "*/)
									 +R->Message);
			}
		}
		else
		if(GetThresholdR()->CheckType==2){
			QColor	c=Qt::cyan;
			c.setAlpha(100);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);

			int	Cx,Cy;
			GetArea().GetCenter(Cx,Cy);
			int	X=(Cx+MovX)*ZoomRate;
			int	Y=(Cy+MovY)*ZoomRate;
			PData.drawText(X,Y,QString("Barcode-1D: ")
							  +Result);
		}	
		else{
			QColor	c=Qt::yellow;
			c.setAlpha(60);
			GetArea().Draw(Res->GetTotalShiftedX(),Res->GetTotalShiftedY(),&IData ,c.rgba()
							,ZoomRate ,MovX ,MovY);
		}
	}
}
void	BCRInspectionItem::CopyThresholdOnly(BCRInspectionItem *src)
{
	const BCRInspectionThreshold	*R=src->GetThresholdR(GetLayersBase());
	BCRInspectionThreshold	*W=GetThresholdW();

	W->CheckType			=R->CheckType;
	W->QuilityGrade			=R->QuilityGrade;
	W->GradeList			=R->GradeList;
	W->BarcodeOrientation	=R->BarcodeOrientation;
	W->BarcodeType			=R->BarcodeType;
	W->BarcodeIsOnlyDigit	=R->BarcodeIsOnlyDigit;
}

void	BCRInspectionItem::SetIndependentItemData(int32 Command,int32 LocalPage,int32 Layer,AlgorithmItemRoot *Data,IntList &EdittedMemberID,QByteArray &Something,QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			BCRInspectionItem *src=(BCRInspectionItem *)Data;
			CopyThresholdOnly(src);
		}
	}
}

bool	BCRInspectionItem::Calc2D(ImagePointerContainer &ImageList)
{
	Result=/**/"";
	BCRInspectionBase		*ABase=(BCRInspectionBase *)GetParentBase();
	if(ABase!=NULL){
		int	W=GetArea().GetWidth();
		int	H=GetArea().GetHeight();

		int	IdealSize=ABase->IdealSize;
		double	Wz=(double)W/(double)IdealSize;
		double	Hz=(double)H/(double)IdealSize;
		double	Z=min(Wz,Hz);
		if(Z<1.0)
			Z=1.0;
		double	ZoomRate=1.0/Z;
	
		try{
			QImage	Img(W*ZoomRate,H*ZoomRate,QImage::Format_RGB32);
			MakeImage(Img,ZoomRate,GetLayerNumb(),0,ImageList);
			Img.save(/**/"TmpBCR.bmp",/**/"BMP");
		}
		catch(...){}
		const	BCRInspectionThreshold	*RThr=GetThresholdR();
		ABase->GetBCR2D(RThr->BarcodeIsOnlyDigit
						,/**/"TmpBCR.bmp",Result);

		if(Result.isEmpty()==true && GetLayerNumb()>1){
			for(int L=0;L<GetLayerNumb();L++){
				QImage	Img(W*ZoomRate,H*ZoomRate,QImage::Format_RGB32);
				MakeImage(Img,ZoomRate,1,L,ImageList);
				Img.save(/**/"TmpBCRR.bmp",/**/"BMP");
				ABase->GetBCR2D(RThr->BarcodeIsOnlyDigit
								,/**/"TmpBCRR.bmp",Result);
				if(Result.isEmpty()==false)
					break;
				RMakeImage(Img,ZoomRate,1,L,ImageList);
				Img.save(/**/"TmpBCRR.bmp",/**/"BMP");
				ABase->GetBCR2D(RThr->BarcodeIsOnlyDigit
								,/**/"TmpBCRR.bmp",Result);
				if(Result.isEmpty()==false)
					break;
			}
		}
	}

	return true;
}

bool	BCRInspectionItem::Calc1D(ImagePointerContainer &ImageList)
{
	Result=/**/"";
	BCRInspectionBase		*ABase=(BCRInspectionBase *)GetParentBase();
	if(ABase!=NULL){
		int	W=GetArea().GetWidth();
		int	H=GetArea().GetHeight();

		int	IdealSize=ABase->IdealSize;
		double	Wz=(double)W/(double)IdealSize;
		double	Hz=(double)H/(double)IdealSize;
		double	Z=min(Wz,Hz);
		if(Z<1.0)
			Z=1.0;
		double	ZoomRate=1.0/Z;
	
		try{
			QImage	Img(W*ZoomRate,H*ZoomRate,QImage::Format_RGB32);
			MakeImage(Img,ZoomRate,GetLayerNumb(),0,ImageList);
			Img.save(/**/"TmpBCR.bmp",/**/"BMP");
		}
		catch(...){}
		const	BCRInspectionThreshold	*RThr=GetThresholdR();
		ABase->GetBCR1D(RThr->BarcodeOrientation,RThr->BarcodeType,RThr->BarcodeIsOnlyDigit
						,/**/"TmpBCR.bmp",Result);

		if(Result.isEmpty()==true && GetLayerNumb()>1){
			for(int L=0;L<GetLayerNumb();L++){
				QImage	Img(W*ZoomRate,H*ZoomRate,QImage::Format_RGB32);
				MakeImage(Img,ZoomRate,1,L,ImageList);
				Img.save(/**/"TmpBCRR.bmp",/**/"BMP");
				ABase->GetBCR1D(RThr->BarcodeOrientation,RThr->BarcodeType,RThr->BarcodeIsOnlyDigit
								,/**/"TmpBCRR.bmp",Result);
				if(Result.isEmpty()==false)
					break;
				RMakeImage(Img,ZoomRate,1,L,ImageList);
				Img.save(/**/"TmpBCRR.bmp",/**/"BMP");
				ABase->GetBCR1D(RThr->BarcodeOrientation,RThr->BarcodeType,RThr->BarcodeIsOnlyDigit
								,/**/"TmpBCRR.bmp",Result);
				if(Result.isEmpty()==false)
					break;
			}
		}
	}

	return true;
}

void	BCRInspectionItem::MakeImage(QImage &Img ,double ZoomRate ,int LayerNumb,int LNo,ImagePointerContainer &ImageList)
{
	int	W=Img.width();
	int	H=Img.height();
	double	Z=1.0/ZoomRate;

	int		mx=0;
	int		my=0;
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
	ResultMx=mx;
	ResultMy=my;

	int	MinX=GetArea().GetMinX()+mx;
	int	MinY=GetArea().GetMinY()+my;
	BCRInspectionBase		*ABase=(BCRInspectionBase *)GetParentBase();
	if(ABase==NULL){
		if(LayerNumb>=3){
			ImageBuffer *hR=ImageList[0];
			ImageBuffer *hG=ImageList[1];
			ImageBuffer *hB=ImageList[2];
			for(int y=0;y<H;y++){
				int	Y=y*Z;
				BYTE	*dest=Img.scanLine(y);
				BYTE	*sR=hR->GetY(MinY+Y);
				BYTE	*sG=hG->GetY(MinY+Y);
				BYTE	*sB=hB->GetY(MinY+Y);
				for(int x=0;x<W;x++){
					int	X=x*Z;
					*(dest+0)=sR[MinX+X];
					*(dest+1)=sG[MinX+X];
					*(dest+2)=sB[MinX+X];
					*(dest+3)=0xFF;
					dest+=4;
				}
			}
		}
		else if(LayerNumb>=2){
			ImageBuffer *hR=ImageList[0];
			ImageBuffer *hG=ImageList[1];
			for(int y=0;y<H;y++){
				int	Y=y*Z;
				BYTE	*dest=Img.scanLine(y);
				BYTE	*sR=hR->GetY(MinY+Y);
				BYTE	*sG=hG->GetY(MinY+Y);
				for(int x=0;x<W;x++){
					int	X=x*Z;
					*(dest+0)=sR[MinX+X];
					*(dest+1)=sG[MinX+X];
					*(dest+2)=0;
					*(dest+3)=0xFF;
					dest+=4;
				}
			}
		}
		else if(LayerNumb>=1){
			ImageBuffer *hR=ImageList[LNo];
			for(int y=0;y<H;y++){
				int	Y=y*Z;
				BYTE	*dest=Img.scanLine(y);
				BYTE	*sR=hR->GetY(MinY+Y);
				for(int x=0;x<W;x++){
					int	X=x*Z;
					*(dest+0)=sR[MinX+X];
					*(dest+1)=sR[MinX+X];
					*(dest+2)=sR[MinX+X];
					*(dest+3)=0xFF;
					dest+=4;
				}
			}
		}
	}
	else{
		ImageBuffer *hR=ImageList[ABase->AdotpedLayer];
		for(int y=0;y<H;y++){
			int	Y=y*Z;
			BYTE	*dest=Img.scanLine(y);
			BYTE	*sR=hR->GetY(MinY+Y);
			for(int x=0;x<W;x++){
				int	X=x*Z;
				*(dest+0)=sR[MinX+X];
				*(dest+1)=sR[MinX+X];
				*(dest+2)=sR[MinX+X];
				*(dest+3)=0xFF;
				dest+=4;
			}
		}
	}
}

static	int	Clip255(int n,int d)
{
	if(n<0)	return d-20;
	else	return d+20;
}

void	BCRInspectionItem::RMakeImage(QImage &Img ,double ZoomRate ,int LayerNumb,int LNo,ImagePointerContainer &ImageList)
{
	BCRInspectionBase		*ABase=(BCRInspectionBase *)GetParentBase();
	int	OffAdd=ABase->FixedValue;
	//int	W=GetArea().GetWidth();
	//int	H=GetArea().GetHeight();
	int	W=Img.width();
	int	H=Img.height();
	int		mx=0;
	int		my=0;
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
	ResultMx=mx;
	ResultMy=my;

	int	MinX=GetArea().GetMinX()+mx;
	int	MinY=GetArea().GetMinY()+my;
	double	Z=1.0/ZoomRate;

	if(LayerNumb>=3){
		ImageBuffer *hR=ImageList[0];
		ImageBuffer *hG=ImageList[1];
		ImageBuffer *hB=ImageList[2];
		for(int y=0;y<H;y++){
			int	Y=y*Z;
			BYTE	*dest=Img.scanLine(y);
			BYTE	*sR=hR->GetY(MinY+Y);
			BYTE	*sG=hG->GetY(MinY+Y);
			BYTE	*sB=hB->GetY(MinY+Y);
			for(int x=0;x<W;x++){
				int	X=x*Z;
				*(dest+0)=255-sR[MinX+X];
				*(dest+1)=255-sG[MinX+X];
				*(dest+2)=255-sB[MinX+X];
				*(dest+3)=0xFF;
				dest+=4;
			}
		}
	}
	else if(LayerNumb>=2){
		ImageBuffer *hR=ImageList[0];
		ImageBuffer *hG=ImageList[1];
		for(int y=0;y<H;y++){
			int	Y=y*Z;
			BYTE	*dest=Img.scanLine(y);
			BYTE	*sR=hR->GetY(MinY+Y);
			BYTE	*sG=hG->GetY(MinY+Y);
			for(int x=0;x<W;x++){
				int	X=x*Z;
				*(dest+0)=255-sR[MinX+X];
				*(dest+1)=255-sG[MinX+X];
				*(dest+2)=0;
				*(dest+3)=0xFF;
				dest+=4;
			}
		}
	}
	else if(LayerNumb>=1){
		ImageBuffer *hR=ImageList[0];
		ImageBuffer *hB=ImageList[2];
		for(int y=0;y<H;y++){
			int	Y=y*Z;
			BYTE	*dest=Img.scanLine(y);
			BYTE	*sR=hR->GetY(MinY+Y);
			BYTE	*sB=hB->GetY(MinY+Y);
			for(int x=0;x<W;x++){
				int	X=x*Z;
				*(dest+0)=Clip255(sR[MinX+X]-sB[MinX+X],OffAdd);
				*(dest+1)=Clip255(sR[MinX+X]-sB[MinX+X],OffAdd);
				*(dest+2)=Clip255(sR[MinX+X]-sB[MinX+X],OffAdd);
				*(dest+3)=0xFF;
				dest+=4;
			}
		}
	}
}

QString	BCRInspectionItem::OutputResult(ResultPosList *p)
{
	return QString(/**/"BCR=")+Result;
}

void	BCRInspectionItem::MoveForAlignment(void)
{
	int		mx=0;
	int		my=0;
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
	MoveTo(mx,my);
}
