#include "XRaster.h"
#include "XRasterLibrary.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <limits.h>
#include "swap.h"
#include "XCrossObj.h"
#include <stdlib.h>
#include <omp.h>
#include "XImageProcess.h"
#include <float.h>
#include "XImageExpand.h"
#include "XpdfWidget.h"


QColor	NegaColor(0,0,0,0);

//============================================================================

RasterPDFItem::RasterPDFItem(void)
{
	Widget=new XpdfWidget();
}

RasterPDFItem::~RasterPDFItem(void)
{
	delete	Widget;
	Widget=NULL;
}

void	RasterPDFItem::MakeImage(BYTE **Image ,int dx ,int dy ,int XByte ,int YLen)
{
}

bool	RasterPDFItem::LoadPDF(RasterFileLayer *f,const QByteArray &Data)
{
	SetFileLayer(f);
	//Widget->loadFile(FileName);
	PDFDoc=Data;
	if(Widget->loadMem(PDFDoc.data(),PDFDoc.size())==XpdfWidget::pdfOk){

		Widget->forceRedraw();
		RasterBase	*ABase=(RasterBase *)GetParentBase();
		double	PgSizeX=Widget->getPageWidth(0);
		double	PgSizeY=Widget->getPageHeight(0);
		if(PgSizeX==0.0 && PgSizeY==0.0){
			ABase->SetPdfXYmm(PgSizeX,PgSizeY);
			PgSizeX=PgSizeX/25.4*72.0;
			PgSizeY=PgSizeY/25.4*72.0;
		}
		double	PointX=PgSizeX/((double)GetDotPerLine());
		double	dpizX=PointX/72.0*25.4*1000000.0/((double)GetParamGlobal()->ResolutionXNano);
		double	PointY=PgSizeY/((double)GetDotPerLine());
		double	dpizY=PointY/72.0*25.4*1000000.0/((double)GetParamGlobal()->ResolutionYNano);
		Widget->setGeometry(0,0,GetDotPerLine(),GetMaxLines());
		double	Z=min(dpizX,dpizY);
		Widget->setZoom(Z);

		double	DPI=25.4*1000000.0/(double)GetParamGlobal()->ResolutionXNano;
		int	pg=Widget->getCurrentPage();
		BaseImage=Widget->convertPageToImage (pg, DPI).convertToFormat(QImage::Format_ARGB32);

		//QImage	Dest(BaseImage.width(),BaseImage.height(),QImage::Format_ARGB32);
		//::TransformImage(Dest, BaseImage, TransformParam);
		//TransImage=Dest;

		AreaX1=0;
		AreaY1=0;
		AreaX2=BaseImage.width();
		AreaY2=BaseImage.height();
		return true;
	}
	return false;
}

struct	RasterPDFItemSaveLoadStruct
{
	double	OrgPosX1,OrgPosY1;
	double	OrgPosX2,OrgPosY2;

	double	PosX1,PosY1;
	double	PosX2,PosY2;
	double	ZoomAperture;
};

bool	RasterPDFItem::Save(QIODevice *f)
{
	if(RasterItemAbstract::Save(f)==false)
		return false;

	bool	OpenedPDF=false;
	if(Widget->hasOpenDocument()==true){
		OpenedPDF=true;
	}
	if(::Save(f,OpenedPDF)==false)
		return false;

	if(OpenedPDF==true){
		QString	FileName=/**/"TmpPDF.$$$";
		if(Widget->saveAs(FileName)==XpdfWidget::pdfOk){
			QFile	TmpFile(FileName);
			if(TmpFile.open(QIODevice::ReadOnly)==true){
				QByteArray	Data=TmpFile.readAll();
				if(::Save(f,Data)==false){
					return false;
				}
			}
		}
		QFile::remove(FileName);
	}

	return true;
}

bool	RasterPDFItem::SaveOnlyShape(QIODevice *f)
{
	return true;
}
bool	RasterPDFItem::Load(QIODevice *f,LayersBase *LBase)
{
	if(RasterItemAbstract::Load(f,LBase)==false)
		return false;
	bool	OpenedPDF=false;
	if(::Load(f,OpenedPDF)==false)
		return false;

	XpdfWidget::ErrorCode	PDFResult;
	if(OpenedPDF==true){
		if(::Load(f,PDFDoc)==false){
			return false;
		}
		PDFResult=Widget->loadMem (PDFDoc.data(), PDFDoc.size());
		//if(PDFResult!=XpdfWidget::pdfOk ){
		//	return false;
		//}
	}
	return true;
}

bool	RasterPDFItem::LoadOnlyShape(QIODevice *f)
{
	MakeXY();
	SetCurrentSize();

	return true;
}

void	RasterPDFItem::CopyFrom(AlgorithmItemRoot *src)
{
	RasterItemAbstract::CopyFrom(src);
	RasterPDFItem	*s=dynamic_cast<RasterPDFItem *>(src);
	if(s!=NULL){
	}
}


double	RasterPDFItem::GetAreaSize(bool EnableClip , bool &Clipped
										,double ClipX1,double ClipY1,double ClipX2 ,double ClipY2)
{
	if(ClipX2<=-1)
		ClipX2=GetDotPerLine();
	if(ClipY2<=-1)
		ClipY2=GetMaxLines();
	return 0;
}
QString	RasterPDFItem::GetMessage(void)
{
	return QString("PDF");
}

bool	RasterPDFItem::GetCenter(double &cx ,double &cy)const
{
	GetArea().GetCenter(cx,cy);
	return true;
}

void	RasterPDFItem::MakeAutoRasterReference(BYTE **MaskMap,int XByte,int YLen 
												,int ColorMergin 
												,int MinItemArea
												,int ShrinkSize)
{
	int	XLen=XByte*8;
	AlgorithmInPagePI	*APage=GetParent();
	
	BYTE	**TmpBuff=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear	(TmpBuff,0,XByte,YLen);

	for(int y=0;y<YLen;y++){
		BYTE	*m=MaskMap[y];
		for(int x=0;x<XLen;x++){
			if(GetBmpBitOnY(m,x)!=0){
				QRgb	c=PickRgb(x,y);
				FlexArea	Area;

				PourFromImage(Area
							,MaskMap
							,x,y
							,TmpBuff,XByte,YLen
							,c,ColorMergin);
				Area.ThinAreaN(ShrinkSize);
				if(Area.GetPatternByte()>=MinItemArea){
					RasterReferenceItem	*Item=new RasterReferenceItem();
					Item->SetArea(Area);
					APage->AppendItem(Item);
				}
				Area.MakeNotBitData(MaskMap,XLen,YLen);
				Area.MakeNotBitData(TmpBuff,XLen,YLen);
			}
		}
	}
	DeleteMatrixBuff(TmpBuff,YLen);
}

struct	PourFromQImageStructColorN
{
	RasterItemAbstract	*Item;
	BYTE	R,G,B;
	int		ColorMergin;
	BYTE	**TmpBuff;
	BYTE	**Mask;
	int		DotPerLine;
	int		XByte;
	int		YLen;
	int		MaxBuffSize;
	int		ReEntCounter;
	int		BandMinY;
	int		BandMaxY;
	int		BandCount;
	struct   FlexLine	*BuffLines;
	int		NLen;
	int		AllocatedBuffLines;
};

#define	_GetColorDifference(R,G,B,Col)	hypot3(R-qRed(Col),G-qGreen(Col),B-qBlue(Col))

static	void	PickPours(int StartX,int StartY,struct	PourFromQImageStructColorN &PData)
{
	if(PData.NLen>=PData.MaxBuffSize)
		return;
	BYTE	*m=PData.Mask[StartY];
	BYTE	*B=PData.TmpBuff[StartY];
	int	X1;
	for(X1=StartX-1;X1>=0;X1--){
		if(GetBmpBitOnY(m,X1)!=0 && GetBmpBitOnY(B,X1)==0){
			QRgb	c=PData.Item->PickRgb(X1,StartY);
			if(_GetColorDifference(PData.R,PData.G,PData.B,c)<=PData.ColorMergin){
				continue;
			}
		}
		break;
	}
	X1++;
	int	X2;
	for(X2=StartX+1;X2<PData.YLen;X2++){
		if(GetBmpBitOnY(m,X2)!=0 || GetBmpBitOnY(B,X2)==0){
			QRgb	c=PData.Item->PickRgb(X2,StartY);
			if(_GetColorDifference(PData.R,PData.G,PData.B,c)<=PData.ColorMergin){
				continue;
			}
		}
		break;
	}
	X2--;
	PData.BuffLines[PData.NLen]._Set(X1,X2,StartY);
	for(int x=X1;x<=X2;x++){
		SetBmpBitOnY1(B,x);
	}
	PData.NLen++;

	if(0<StartY){
		m=PData.Mask[StartY-1];
		B=PData.TmpBuff[StartY-1];
		for(int x=X1;x<=X2;x++){
			if(GetBmpBitOnY(m,x)!=0 && GetBmpBitOnY(B,x)==0){
				QRgb	c=PData.Item->PickRgb(x,StartY-1);
				if(_GetColorDifference(PData.R,PData.G,PData.B,c)<=PData.ColorMergin){
					PickPours(x,StartY-1,PData);
				}
			}
		}
	}
	if((StartY+1)<PData.YLen){
		m=PData.Mask[StartY+1];
		B=PData.TmpBuff[StartY+1];
		for(int x=X1;x<=X2;x++){
			if(GetBmpBitOnY(m,x)!=0 && GetBmpBitOnY(B,x)==0){
				QRgb	c=PData.Item->PickRgb(x,StartY+1);
				if(_GetColorDifference(PData.R,PData.G,PData.B,c)<=PData.ColorMergin){
					PickPours(x,StartY+1,PData);
				}
			}
		}
	}
}


void	RasterPDFItem::PourFromImage(FlexArea &area
									,BYTE **Mask
									,int StartX, int StartY
									,BYTE **TmpBuff,int XByte,int YLen
									,QRgb Col ,int ColorMergin)
{
	const int	MaxBuffCount=100000;
	struct   FlexLine	BuffLines[MaxBuffCount];

	struct	PourFromQImageStructColorN	PData;
	PData.Item			=this;
	PData.DotPerLine	=GetDotPerLine();
	PData.XByte			=XByte;
	PData.YLen			=YLen;
	PData.MaxBuffSize	=MaxBuffCount;
	PData.TmpBuff		=TmpBuff;
	PData.Mask			=Mask;
	PData.R				=qRed(Col);
	PData.G				=qGreen(Col);
	PData.B				=qBlue(Col);
	PData.ColorMergin	=ColorMergin;
	PData.BuffLines		=BuffLines;
	PData.NLen			=0;
	PData.ReEntCounter	=0;

	PickPours(StartX,StartY,PData);

	struct FlexLine	*FL=new struct FlexLine[PData.NLen];
	memcpy(FL,BuffLines,sizeof(struct FlexLine)*PData.NLen);

	area.SetFLine(FL,PData.NLen);
	//Restruct();
}
