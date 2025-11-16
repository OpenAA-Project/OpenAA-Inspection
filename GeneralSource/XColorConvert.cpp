#include "XColorConvert.h"
#include "XGeneralFunc.h"
#include "XMatrix.h"
#include "swap.h"
#include "XInterpolation.h"
#include <omp.h>

double	GetColorDistancce(const QColor &col1,const QColor &col2)
{
	int	d1=col1.red()-col2.red();
	int	d2=col1.green()-col2.green();
	int	d3=col1.blue()-col2.blue();
	return sqrt(d1*d1+d2*d2+d3*d3);
}
double	GetColorDistancce(const QRgb &col1,const QRgb &col2)
{
	int	d1=qRed	 (col1)-qRed  (col2);
	int	d2=qGreen(col1)-qGreen(col2);
	int	d3=qBlue (col1)-qBlue (col2);
	return sqrt(d1*d1+d2*d2+d3*d3);
}


ColorProfile::ColorProfile(const ColorProfile &src)
{
	ID		=src.ID;
	Name	=src.Name;
	SrcColor =src.SrcColor;
	DstColor =src.DstColor;
}
ColorProfile::ColorProfile(const QColor &_SrcColor,const QColor &_DstColor)
{
	ID		=-1;
	SrcColor=_SrcColor;
	DstColor=_DstColor;
}

ColorProfile	&ColorProfile::operator=(const ColorProfile &src)
{
	ID		=src.ID;
	Name	=src.Name;
	SrcColor =src.SrcColor;
	DstColor =src.DstColor;
	return *this;
}

bool	ColorProfile::Save(QIODevice *f)
{
	if(::Save(f,ID		)==false)	{	return	false;	}
	if(::Save(f,Name	)==false)	{	return	false;	}
	if(::Save(f,SrcColor)==false)	{	return	false;	}
	if(::Save(f,DstColor)==false)	{	return	false;	}
	return true;
}
bool	ColorProfile::Load(QIODevice *f)
{
	if(::Load(f,ID		)==false)	{	return	false;	}
	if(::Load(f,Name	)==false)	{	return	false;	}
	if(::Load(f,SrcColor)==false)	{	return	false;	}
	if(::Load(f,DstColor)==false)	{	return	false;	}
	return true;
}

ColorProfileContainer::ColorProfileContainer(const ColorProfileContainer &src)
{
	for(ColorProfile *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ColorProfile	*d=new ColorProfile();
		*d=*s;
		AppendList(d);
	}
}

ColorProfile	*ColorProfileContainer::Create(void)
{
	return new ColorProfile();
}
	
ColorProfile	*ColorProfileContainer::GetClosedSrcColor(const QColor &col)	const
{
	ColorProfile	*Closed=NULL;
	double			MinL=99999999;
	for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext()){
		double	D=GetColorDistancce(col,s->SrcColor);
		if(D<MinL){
			MinL=D;
			Closed=s;
		}
	}
	return Closed;
}
	
ColorProfile	*ColorProfileContainer::GetClosedDstColor(const QColor &col)	const
{
	ColorProfile	*Closed=NULL;
	double			MinL=99999999;
	for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext()){
		double	D=GetColorDistancce(col,s->DstColor);
		if(D<MinL){
			MinL=D;
			Closed=s;
		}
	}
	return Closed;
}

ColorProfileContainer	&ColorProfileContainer::operator=(const ColorProfileContainer &src)
{
	RemoveAll();
	for(ColorProfile *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ColorProfile	*d=new ColorProfile();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

void	ColorProfileContainer::MergeBySource(const ColorProfileContainer &src)
{
	for(ColorProfile *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ColorProfile *m;
		for(m=GetFirst();m!=NULL;m=m->GetNext()){
			if(s->SrcColor==m->SrcColor){
				break;
			}
		}
		if(m==NULL){
			ColorProfile	*d=new ColorProfile(*s);
			AppendList(d);
		}
	}
}
void	ColorProfileContainer::MergeBySource(const QColor &PDFColor ,const QColor &ImgColor)
{
	ColorProfile *m;
	for(m=GetFirst();m!=NULL;m=m->GetNext()){
		if(PDFColor==m->SrcColor){
			break;
		}
	}
	if(m==NULL){
		ColorProfile	*d=new ColorProfile(PDFColor,ImgColor);
		AppendList(d);
	}
}

int32	GetColorLen(const QColor &s1,const QColor &s2)
{
	int	d1=s1.red()  -s2.red();
	int	d2=s1.green()-s2.green();
	int	d3=s1.blue() -s2.blue();
	return d1*d1+d2*d2+d3*d3;
}

struct ColorProfileTable
{	
	int32			ColorLen;
	ColorProfile	*CPoint;
};

int	FuncDimColorSort(const void *a, const void *b)
{
	struct ColorProfileTable	*pa=(struct ColorProfileTable *)a;
	struct ColorProfileTable	*pb=(struct ColorProfileTable *)b;
	return pa->ColorLen-pb->ColorLen;
}

QColor	ColorProfileContainer::AssignToSrcBy1(const QColor &dCol)	const
{
	int	N=GetCount();
	if(N<1){
		return dCol;
	}

	ColorProfile	*s=GetClosedDstColor(dCol);

	double	Zr=(dCol.red()	<5)?1.0:(double)s->DstColor.red()	/(double)dCol.red()	;
	double	Zg=(dCol.green()<5)?1.0:(double)s->DstColor.green()	/(double)dCol.green();
	double	Zb=(dCol.blue()	<5)?1.0:(double)s->DstColor.blue()	/(double)dCol.blue();

	return QColor(Clipping((int)(s->SrcColor.red()*Zr),0,255)
				, Clipping((int)(s->SrcColor.green()*Zg),0,255)
				, Clipping((int)(s->SrcColor.blue()*Zb),0,255));
}


QColor	ColorProfileContainer::AssignToSrcBy4(const QColor &dCol)	const
{
	int	N=GetCount();
	if(N<4){
		return dCol;
	}
	struct ColorProfileTable	DDim[30000];
	struct ColorProfileTable	*DimPoint;
	if(N>30000){
		DimPoint=new struct ColorProfileTable[N];
	}
	else{
		DimPoint=DDim;
	}

	int	n=0;
	for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext(),n++){
		DimPoint[n].ColorLen=GetColorLen(s->DstColor,dCol);
		DimPoint[n].CPoint=s;
	}
	QSort(DimPoint,n,sizeof(struct ColorProfileTable),FuncDimColorSort);
	if(DimPoint[0].ColorLen==0){
		QColor	Ret=DimPoint[0].CPoint->SrcColor;
		if(DimPoint!=DDim){
			delete	[]DimPoint;
		}
		return Ret;
	}
	if(DimPoint[0].ColorLen<8 && DimPoint[1].ColorLen>=8){
		int	dR=DimPoint[0].CPoint->SrcColor.red()  -DimPoint[0].CPoint->DstColor.red();
		int	dG=DimPoint[0].CPoint->SrcColor.green()-DimPoint[0].CPoint->DstColor.green();
		int	dB=DimPoint[0].CPoint->SrcColor.blue() -DimPoint[0].CPoint->DstColor.blue();
		QColor	Ret(Clipping(dCol.red()+dR,0,255),Clipping(dCol.green()+dG,0,255),Clipping(dCol.blue()+dB,0,255));
		if(DimPoint!=DDim){
			delete	[]DimPoint;
		}
		return Ret;
	}
	if(DimPoint[3].ColorLen>=400 && DimPoint[2].ColorLen>=400 && DimPoint[1].ColorLen>=400){
		int	dR=DimPoint[0].CPoint->SrcColor.red()  -DimPoint[0].CPoint->DstColor.red();
		int	dG=DimPoint[0].CPoint->SrcColor.green()-DimPoint[0].CPoint->DstColor.green();
		int	dB=DimPoint[0].CPoint->SrcColor.blue() -DimPoint[0].CPoint->DstColor.blue();
		QColor	Ret(Clipping(dCol.red()+dR,0,255),Clipping(dCol.green()+dG,0,255),Clipping(dCol.blue()+dB,0,255));
		if(DimPoint!=DDim){
			delete	[]DimPoint;
		}
		return Ret;
	}
	if(DimPoint[3].ColorLen>=400 && DimPoint[2].ColorLen>=400){
		int	dR1=DimPoint[0].CPoint->SrcColor.red()  -DimPoint[0].CPoint->DstColor.red();
		int	dG1=DimPoint[0].CPoint->SrcColor.green()-DimPoint[0].CPoint->DstColor.green();
		int	dB1=DimPoint[0].CPoint->SrcColor.blue() -DimPoint[0].CPoint->DstColor.blue();
		int	dR2=DimPoint[1].CPoint->SrcColor.red()  -DimPoint[1].CPoint->DstColor.red();
		int	dG2=DimPoint[1].CPoint->SrcColor.green()-DimPoint[1].CPoint->DstColor.green();
		int	dB2=DimPoint[1].CPoint->SrcColor.blue() -DimPoint[1].CPoint->DstColor.blue();
		double	L=hypot(DimPoint[0].ColorLen,DimPoint[1].ColorLen);

		int	r=dCol.red  ()+dR1*DimPoint[1].ColorLen/L+dR2*DimPoint[0].ColorLen/L;
		int	g=dCol.green()+dG1*DimPoint[1].ColorLen/L+dG2*DimPoint[0].ColorLen/L;
		int	b=dCol.blue ()+dB1*DimPoint[1].ColorLen/L+dB2*DimPoint[0].ColorLen/L;
		QColor	Ret(Clipping(r,0,255),Clipping(g,0,255),Clipping(b,0,255));
		if(DimPoint!=DDim){
			delete	[]DimPoint;
		}
		return Ret;
	}
	if(DimPoint[3].ColorLen>=400){
		int	dR1=DimPoint[0].CPoint->SrcColor.red()  -DimPoint[0].CPoint->DstColor.red();
		int	dG1=DimPoint[0].CPoint->SrcColor.green()-DimPoint[0].CPoint->DstColor.green();
		int	dB1=DimPoint[0].CPoint->SrcColor.blue() -DimPoint[0].CPoint->DstColor.blue();
		int	dR2=DimPoint[1].CPoint->SrcColor.red()  -DimPoint[1].CPoint->DstColor.red();
		int	dG2=DimPoint[1].CPoint->SrcColor.green()-DimPoint[1].CPoint->DstColor.green();
		int	dB2=DimPoint[1].CPoint->SrcColor.blue() -DimPoint[1].CPoint->DstColor.blue();
		int	dR3=DimPoint[2].CPoint->SrcColor.red()  -DimPoint[2].CPoint->DstColor.red();
		int	dG3=DimPoint[2].CPoint->SrcColor.green()-DimPoint[2].CPoint->DstColor.green();
		int	dB3=DimPoint[2].CPoint->SrcColor.blue() -DimPoint[2].CPoint->DstColor.blue();
		double	q1=DimPoint[0].ColorLen;
		double	q2=DimPoint[1].ColorLen;
		double	q3=DimPoint[2].ColorLen;
		double	L=sqrt(q1*q1+q2*q2+q3*q3);
		double	L1=sqrt(q2*q2+q3*q3);
		double	L2=sqrt(q1*q1+q3*q3);
		double	L3=sqrt(q1*q1+q2*q2);

		int	r=dCol.red  ()+dR1*L1/L+dR2*L2/L+dR3*L3/L;
		int	g=dCol.green()+dG1*L1/L+dG2*L2/L+dG3*L3/L;
		int	b=dCol.blue ()+dB1*L1/L+dB2*L2/L+dB3*L3/L;
		QColor	Ret(Clipping(r,0,255),Clipping(g,0,255),Clipping(b,0,255));
		if(DimPoint!=DDim){
			delete	[]DimPoint;
		}
		return Ret;
	}

	struct ColorProfileTable	Dim4[4];
	Dim4[0]=DimPoint[0];
	Dim4[1]=DimPoint[1];
	Dim4[2]=DimPoint[2];
	Dim4[3]=DimPoint[3];

	Matrix<double>	Dst(4,4);
	Matrix<double>	Src(4,4);
	Matrix<double>	P(4,4);
	// P*Dst=Src
	Matrix<double>	D(4,1);
	Matrix<double>	S(4,1);
	// P*D=S

	Dst.Set(0,0,Dim4[0].CPoint->DstColor.red());
	Dst.Set(1,0,Dim4[0].CPoint->DstColor.green());
	Dst.Set(2,0,Dim4[0].CPoint->DstColor.blue());
	Dst.Set(3,0,1.0);
	Dst.Set(0,1,Dim4[1].CPoint->DstColor.red());
	Dst.Set(1,1,Dim4[1].CPoint->DstColor.green());
	Dst.Set(2,1,Dim4[1].CPoint->DstColor.blue());
	Dst.Set(3,1,1.0);
	Dst.Set(0,2,Dim4[2].CPoint->DstColor.red());
	Dst.Set(1,2,Dim4[2].CPoint->DstColor.green());
	Dst.Set(2,2,Dim4[2].CPoint->DstColor.blue());
	Dst.Set(3,2,1.0);
	Dst.Set(0,3,Dim4[3].CPoint->DstColor.red());
	Dst.Set(1,3,Dim4[3].CPoint->DstColor.green());
	Dst.Set(2,3,Dim4[3].CPoint->DstColor.blue());
	Dst.Set(3,3,1.0);

	Src.Set(0,0,Dim4[0].CPoint->SrcColor.red());
	Src.Set(1,0,Dim4[0].CPoint->SrcColor.green());
	Src.Set(2,0,Dim4[0].CPoint->SrcColor.blue());
	Src.Set(3,0,1.0);
	Src.Set(0,1,Dim4[1].CPoint->SrcColor.red());
	Src.Set(1,1,Dim4[1].CPoint->SrcColor.green());
	Src.Set(2,1,Dim4[1].CPoint->SrcColor.blue());
	Src.Set(3,1,1.0);
	Src.Set(0,2,Dim4[2].CPoint->SrcColor.red());
	Src.Set(1,2,Dim4[2].CPoint->SrcColor.green());
	Src.Set(2,2,Dim4[2].CPoint->SrcColor.blue());
	Src.Set(3,2,1.0);
	Src.Set(0,3,Dim4[3].CPoint->SrcColor.red());
	Src.Set(1,3,Dim4[3].CPoint->SrcColor.green());
	Src.Set(2,3,Dim4[3].CPoint->SrcColor.blue());
	Src.Set(3,3,1.0);
	P=Src/Dst;

	D.Set(0,0,dCol.red());
	D.Set(1,0,dCol.green());
	D.Set(2,0,dCol.blue());
	D.Set(3,0,1.0);
	S=P*D;
	if(DimPoint!=DDim){
		delete	[]DimPoint;
	}
	return QColor(Clipping((int)S.Get(0,0),0,255),Clipping((int)S.Get(1,0),0,255),Clipping((int)S.Get(2,0),0,255));
}

ColorProfileContainerWithTable::ColorProfileContainerWithTable(void)
{
	ColTable=new QRgb[256*256*256];
}
ColorProfileContainerWithTable::ColorProfileContainerWithTable(const ColorProfileContainerWithTable &src)
	:ColorProfileContainer(src)
{
	ColTable=new QRgb[256*256*256];
	memcpy(ColTable,src.ColTable,256*256*256);
}
ColorProfileContainerWithTable::~ColorProfileContainerWithTable(void)
{
	if(ColTable!=NULL){
		delete	[]ColTable;
		ColTable=NULL;
	}
}

ColorProfileContainerWithTable	&ColorProfileContainerWithTable::operator=(const ColorProfileContainerWithTable &src)
{
	ColorProfileContainer::operator=(src);
	memcpy(ColTable,src.ColTable,256*256*256);
	return *this;
}

ColorProfileContainerWithTable	&ColorProfileContainerWithTable::operator=(const ColorProfileContainer &src)
{
	ColorProfileContainer::operator=(src);
	MakeTable();
	return *this;
}

#define	IndexRGB(r,g,b)	(((r)<<16)+((g)<<8)+(b))


class ColorProfilePointer : public NPList<ColorProfilePointer>
{
public:
	ColorProfile	*Point;

	ColorProfilePointer(ColorProfile *p)	{	Point=p;	}
};


void	ColorProfileContainerWithTable::MakeTable(void)
{
	int	N=GetCount();

	if(N>=2000){
		double	*sX=new double[N];
		double	*dY=new double[N];
		int	i=0;
		for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext(),i++){
			sX[i]=s->SrcColor.red();
			dY[i]=s->DstColor.red();
		}
		double RA,RB,RC;
		MakeInterpolatedLine(sX ,dY ,N
							 ,RA,RB,RC);

		i=0;
		for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext(),i++){
			sX[i]=s->SrcColor.green();
			dY[i]=s->DstColor.green();
		}
		double GA,GB,GC;
		MakeInterpolatedLine(sX ,dY ,N
							 ,GA,GB,GC);

		i=0;
		for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext(),i++){
			sX[i]=s->SrcColor.blue();
			dY[i]=s->DstColor.blue();
		}
		double BA,BB,BC;
		MakeInterpolatedLine(sX ,dY ,N
							 ,BA,BB,BC);

			for(int r=0;r<256;r++){
				for(int g=0;g<256;g++){
					for(int b=0;b<256;b++){
						int	dr=(RB!=0)?-(RA*r+RC)/RB:0;
						int	dg=(GB!=0)?-(GA*g+GC)/GB:0;
						int	db=(BB!=0)?-(BA*b+BC)/BB:0;
						ColTable[IndexRGB(r,g,b)]=qRgb(Clipping(dr,0,255),Clipping(dg,0,255),Clipping(db,0,255));
					}
				}
			}
		
		delete	[]sX;
		delete	[]dY;
		return;


		//int	DivD=8;
		//int	SearchLen=64;
		//NPListPack<ColorProfilePointer>	PList[32][32][32];
		//for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext()){
		//	int	r=s->SrcColor.red();
		//	int	g=s->SrcColor.green();
		//	int	b=s->SrcColor.blue();
		//	int	MinR=max(0  ,r-SearchLen);
		//	int	MaxR=min(255,r+SearchLen);
		//	int	MinG=max(0  ,g-SearchLen);
		//	int	MaxG=min(255,g+SearchLen);
		//	int	MinB=max(0  ,b-SearchLen);
		//	int	MaxB=min(255,b+SearchLen);
		//	int	MinPR=MinR/DivD;
		//	int	MaxPR=MaxR/DivD;
		//	int	MinPG=MinG/DivD;
		//	int	MaxPG=MaxG/DivD;
		//	int	MinPB=MinB/DivD;
		//	int	MaxPB=MaxB/DivD;
		//	for(int kr=MinPR;kr<=MaxPR;kr++){
		//		for(int kg=MinPG;kg<=MaxPG;kg++){
		//			for(int kb=MinPB;kb<=MaxPB;kb++){
		//				PList[kr][kg][kb].AppendList(new ColorProfilePointer(s));
		//			}
		//		}
		//	}
		//}
		//#pragma omp parallel
		//{
		//	#pragma omp for	
		//	for(int r=0;r<256;r++){
		//		for(int g=0;g<256;g++){
		//			for(int b=0;b<256;b++){
		//				int32	MinD=99999999;
		//				QColor	SrcColor(r,g,b);
		//				ColorProfilePointer *MinS=NULL;
		//				for(ColorProfilePointer *s=PList[r/DivD][g/DivD][b/DivD].GetFirst();s!=NULL;s=s->GetNext()){
		//					int32	d=GetColorLen(s->Point->SrcColor,SrcColor);
		//					if(d<MinD){
		//						MinD=d;
		//						MinS=s;
		//					}
		//				}
		//				if(MinS!=NULL){
		//					int	dr=MinS->Point->DstColor.red  ()-MinS->Point->SrcColor.red();
		//					int	dg=MinS->Point->DstColor.green()-MinS->Point->SrcColor.green();
		//					int	db=MinS->Point->DstColor.blue ()-MinS->Point->SrcColor.blue();
		//
		//					ColTable[IndexRGB(r,g,b)]=qRgb(Clipping((int)(r+dr),0,255),Clipping((int)(g+dg),0,255),Clipping((int)(b+db),0,255));
		//				}
		//			}
		//		}
		//	}
		//}


		/*
						ColorProfile	*s=CList[IndexRGB(r,g,b)];
						if(s!=NULL){
							ColTable[IndexRGB(r,g,b)]=s->DstColor.rgb();
						}
						else{
							QColor	SrcColor(r,g,b);
							ColorProfile	*SDim[10000];
							bool	Found=false;
							for(int L=1;L<64;L++){
								int				SNumb=0;
								int	kr,kg,kb;
								int	MaxKr=min(r+L,255);
								int	MinKr=max(r-L,0);
								int	MaxKg=min(g+L,255);
								int	MinKg=max(g-L,0);
								int	MaxKb=min(b+L,255);
								int	MinKb=max(b-L,0);


		ColorProfile	**CList=new ColorProfile*[256*256*256];
		memset(CList,0,sizeof(ColorProfile*)*256*256*256);

		for(ColorProfile *s=GetFirst();s!=NULL;s=s->GetNext()){
			int	r=s->SrcColor.red();
			int	g=s->SrcColor.green();
			int	b=s->SrcColor.blue();
			CList[IndexRGB(r,g,b)]=s;
		}

		#pragma omp parallel
		{
			#pragma omp for	
			for(int r=0;r<256;r++){
				for(int g=0;g<256;g++){
					for(int b=0;b<256;b++){
						ColorProfile	*s=CList[IndexRGB(r,g,b)];
						if(s!=NULL){
							ColTable[IndexRGB(r,g,b)]=s->DstColor.rgb();
						}
						else{
							QColor	SrcColor(r,g,b);
							ColorProfile	*SDim[10000];
							bool	Found=false;
							for(int L=1;L<64;L++){
								int				SNumb=0;
								int	kr,kg,kb;
								int	MaxKr=min(r+L,255);
								int	MinKr=max(r-L,0);
								int	MaxKg=min(g+L,255);
								int	MinKg=max(g-L,0);
								int	MaxKb=min(b+L,255);
								int	MinKb=max(b-L,0);

								kr=r-L;
								if(0<=kr){
									for(kg=MinKg;kg<=MaxKg;kg++){
										for(kb=MinKb;kb<=MaxKb;kb++){
											s=CList[IndexRGB(kr,kg,kb)];
											if(s!=NULL){
												SDim[SNumb]=s;
												SNumb++;
											}
										}
									}
								}
								kr=r+L;
								if(kr<256){
									for(kg=MinKg;kg<=MaxKg;kg++){
										for(kb=MinKb;kb<=MaxKb;kb++){
											s=CList[IndexRGB(kr,kg,kb)];
											if(s!=NULL){
												SDim[SNumb]=s;
												SNumb++;
											}
										}
									}
								}
								kg=g-L;
								if(0<=kg){
									for(kr=MinKr;kr<=MaxKr;kr++){
										for(kb=MinKb;kb<=MaxKb;kb++){
											s=CList[IndexRGB(kr,kg,kb)];
											if(s!=NULL){
												SDim[SNumb]=s;
												SNumb++;
											}
										}
									}
								}
								kg=g+L;
								if(kg<256){
									for(kr=MinKr;kr<=MaxKr;kr++){
										for(kb=MinKb;kb<=MaxKb;kb++){
											s=CList[IndexRGB(kr,kg,kb)];
											if(s!=NULL){
												SDim[SNumb]=s;
												SNumb++;
											}
										}
									}
								}
								kb=b-L;
								if(0<=kb){
									for(kr=MinKr;kr<=MaxKr;kr++){
										for(kg=MinKg;kg<=MaxKg;kg++){
											s=CList[IndexRGB(kr,kg,kb)];
											if(s!=NULL){
												SDim[SNumb]=s;
												SNumb++;
											}
										}
									}
								}
								kb=b+L;
								if(kb<256){
									for(kr=MinKr;kr<=MaxKr;kr++){
										for(kg=MinKg;kg<=MaxKg;kg++){
											s=CList[IndexRGB(kr,kg,kb)];
											if(s!=NULL){
												SDim[SNumb]=s;
												SNumb++;
											}
										}
									}
								}

								if(SNumb!=0){
									double	Len=0;
									for(int i=0;i<SNumb;i++){
										Len+=GetColorLen(SDim[i]->SrcColor,SrcColor);
									}
									Len=sqrt(Len);
									double	mr=0;
									double	mg=0;
									double	mb=0;
									for(int i=0;i<SNumb;i++){
										int	dr=SDim[i]->DstColor.red  ()-SDim[i]->SrcColor.red();
										int	dg=SDim[i]->DstColor.green()-SDim[i]->SrcColor.green();
										int	db=SDim[i]->DstColor.blue ()-SDim[i]->SrcColor.blue();
										double	dL=sqrt(GetColorLen(SDim[i]->SrcColor,SrcColor));
										mr += dr*dL/Len;
										mg += dg*dL/Len;
										mb += db*dL/Len;
									}
									ColTable[IndexRGB(r,g,b)]=qRgb(Clipping((int)(r+mr),0,255),Clipping((int)(g+mg),0,255),Clipping((int)(b+mb),0,255));
									Found=true;
									break;
								}
							}
							if(Found==false){
								ColTable[IndexRGB(r,g,b)]=qRgb(r,g,b);
							}
						}
					}
				}
			}
		}
		delete	[]CList;
		*/
	}
	else{
		#pragma omp parallel
		{
			#pragma omp for	
			for(int r=0;r<256;r++){
				for(int g=0;g<256;g++){
					for(int b=0;b<256;b++){
						QColor	c=AssignToSrcBy4(QColor(r,g,b));
						ColTable[(r<<16)+(g<<8)+b]=c.rgb();
					}
				}
			}
		}
	}
}

bool	ColorProfileContainerWithTable::Save(QIODevice *f)
{
	if(ColorProfileContainer::Save(f)==false){
		return false;
	}

	int	TableByte=sizeof(ColTable[0])*256*256*256;
	if(f->write((const char *)ColTable,TableByte)!=TableByte){
		return false;
	}
	return true;
}
bool	ColorProfileContainerWithTable::Load(QIODevice *f)
{
	if(ColorProfileContainer::Load(f)==false){
		return false;
	}

	int	TableByte=sizeof(ColTable[0])*256*256*256;
	if(f->read((char *)ColTable,TableByte)!=TableByte){
		return false;
	}
	return true;
}


//===============================================================================================

//ColorCount::ColorCount(const ColorCount &src)
//{
//	Color	=src.Color;
//	Count	=src.Count;
//}
//
//ColorCount	&ColorCount::operator=(const ColorCount &src)
//{
//	Color	=src.Color;
//	Count	=src.Count;
//	return *this;
//}

ColorCountContainer::ColorCountContainer(void)
{
	memset(BListR,0,sizeof(BListR));
	memset(BListG,0,sizeof(BListG));
	memset(BListB,0,sizeof(BListB));
}
ColorCountContainer::ColorCountContainer(const ColorCountContainer &src)
{
	memcpy(BListR,src.BListR,sizeof(BListR));
	memcpy(BListG,src.BListG,sizeof(BListG));
	memcpy(BListB,src.BListB,sizeof(BListB));

	//for(ColorCount *s=src.GetFirst();s!=NULL;s=s->GetNext()){
	//	ColorCount *d=new ColorCount(*s);
	//	AppendList(d);
	//}
}

ColorCountContainer	&ColorCountContainer::operator=(const ColorCountContainer &src)
{
	memcpy(BListR,src.BListR,sizeof(BListR));
	memcpy(BListG,src.BListG,sizeof(BListG));
	memcpy(BListB,src.BListB,sizeof(BListB));

	//for(ColorCount *s=src.GetFirst();s!=NULL;s=s->GetNext()){
	//	ColorCount *d=new ColorCount(*s);
	//	AppendList(d);
	//}
	return *this;
}
void	ColorCountContainer::IncreaseCount(const QRgb &col)
{
	int	R=qRed	(col);
	int	G=qGreen(col);
	int	B=qBlue	(col);

	BListR[R]++;
	BListG[G]++;
	BListB[B]++;
}
ColorCountList::ColorCountList(const QRgb &col)
{
	IndexColor=col;
}
ColorCountList::ColorCountList(const ColorCountList &src)
{
	IndexColor		=src.IndexColor;
	ColorContainer	=src.ColorContainer;
	DestColor		=src.DestColor;
}

ColorCountList	&ColorCountList::operator=(const ColorCountList &src)
{
	IndexColor		=src.IndexColor;
	ColorContainer	=src.ColorContainer;
	DestColor		=src.DestColor;
	return *this;
}

void	ColorCountList::IncreaseCount(const QRgb &col)
{
	ColorContainer.IncreaseCount(col);
}
void	ColorCountList::MakeDestColor(void)
{
	int	R=MakeCenterBrightness(ColorContainer.BListR,0.3,0.3);
	int	G=MakeCenterBrightness(ColorContainer.BListG,0.3,0.3);
	int	B=MakeCenterBrightness(ColorContainer.BListB,0.3,0.3);

	DestColor=qRgb(R,G,B);
}

int		ColorCountList::MakeCenterBrightness(int BList[256],double OmitL, double OmitH)
{
	int	Numb=0;
	for(int i=0;i<256;i++){
		Numb+=BList[i];
	}
	if(Numb==0)
		return 0;
	int	NumbL=Numb*OmitL;
	int	NumbH=Numb*OmitH;
	int	L;
	int	NL=0;
	for(L=0;L<256;L++){
		if(NL+BList[L]>NumbL){
			break;
		}
		NL+=BList[L];
	}
	int	H;
	int	NH=0;
	for(H=255;H>0;H--){
		if(NH+BList[H]>NumbH){
			break;
		}
		NH+=BList[H];
	}
	int64	Col		=0;
	int		ColNumb	=0;
	for(int i=L;i<=H;i++){
		Col		+=((int64)BList[i])*i;
		ColNumb	+=BList[i];
	}
	if(ColNumb<20){
		ColNumb	=0;
		Col		=0;
		for(int i=0;i<256;i++){
			Col		+=((int64)BList[i])*i;
			ColNumb	+=BList[i];
		}
	}
	return Clipping(Col/ColNumb,0,255);
}

ColorCountListContainer::ColorCountListContainer(void)
{
	memset(Point,0,sizeof(Point));
}
ColorCountListContainer::ColorCountListContainer(const ColorCountListContainer &src)
{
	memset(Point,0,sizeof(Point));
	for(ColorCountList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ColorCountList *d=new ColorCountList(*s);
		Append(d);
	}
}

void	ColorCountListContainer::Append(ColorCountList *s)
{
	int	R=qRed	(s->IndexColor);
	int	G=qGreen(s->IndexColor);
	int	B=qBlue	(s->IndexColor);
	Point[R][G][B]=s;
	AppendList(s);
}
ColorCountListContainer	&ColorCountListContainer::operator=(const ColorCountListContainer &src)
{
	for(ColorCountList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		ColorCountList *d=new ColorCountList(*s);
		Append(d);
	}
	return *this;
}

ColorCountList	*ColorCountListContainer::FindIndexColor(const QRgb &indexcol)
{
	int	R=qRed(indexcol);
	int	G=qGreen(indexcol);
	int	B=qBlue(indexcol);
	
	return Point[R][G][B];
}