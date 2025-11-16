#include "XLineMatching.h"
#include "swap.h"

LineMatchingX::LineMatchingX(void)
{
	LineData=NULL;
	LineLen=0;
}

LineMatchingX::LineMatchingX(const LineMatchingX &src)
{
	LineLen	=src.LineLen;
	XNumb	=src.XNumb;
	SkipX	=src.SkipX;
	SkipY	=src.SkipY;
	LeftX	=src.LeftX;
	Y		=src.Y;
	AA		=src.AA;
	A		=src.A;
	LineData=new BYTE[LineLen];
	memcpy(LineData,src.LineData,LineLen);
}

LineMatchingX::~LineMatchingX(void)
{
	if(LineData!=NULL){
		delete	[]LineData;
		LineData=NULL;
		LineLen=0;
	}
}

bool	LineMatchingX::Initial(int _LeftX ,int _LineLen,int _Y
							,ImageBuffer &SrcImage
							,int skipx ,int skipy)
{
	LeftX	=_LeftX;
	LineLen	=_LineLen;
	Y		=_Y;
	SkipX	=(skipx>=1)?skipx:1;
	SkipY	=(skipy>=1)?skipy:1;
	if(LineData!=NULL){
		delete	[]LineData;
	}
	LineData=new BYTE[LineLen];

	if(Y<0 || SrcImage.GetHeight()<=Y
	|| LeftX<0 || SrcImage.GetWidth()<(LeftX+LineLen)){
		return false;
	}

	BYTE	*s=SrcImage.GetY(Y);
	AA=0;
	A=0;
	XNumb=0;
	for(int x=0;x<LineLen;x+=SkipX,XNumb++){
		BYTE	a=s[LeftX+x];
		LineData[XNumb]=a;
		AA+=a*a;
		A+=a;
	}

	return true;
}
LineMatchingX	&LineMatchingX::operator=(const LineMatchingX &src)
{
	LineLen	=src.LineLen;
	XNumb	=src.XNumb;
	SkipX	=src.SkipX;
	SkipY	=src.SkipY;
	LeftX	=src.LeftX;
	Y		=src.Y;
	AA		=src.AA;
	A		=src.A;
	if(LineData!=NULL){
		delete	[]LineData;
	}
	LineData=new BYTE[LineLen];
	memcpy(LineData,src.LineData,LineLen);
	return *this;
}
double	LineMatchingX::GetVarSrc(void)
{
	double	AvrA=((double)A)/XNumb;
	double	V=(AA-AvrA*AvrA*XNumb)/XNumb;
	return V;
}

float	LineMatchingX::SearchMax(int SearchX ,int SearchY
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy)
{
	int	X1=max(LeftX-SearchX+dx,0);
	int	X2=min(LeftX+SearchX+dx,DstImage.GetWidth()-1);
	int	Y1=max(Y-SearchY+dy,0);
	int	Y2=min(Y+SearchY+dy,DstImage.GetHeight()-1);

	return SearchMaxRaw(X1,Y1 ,X2 ,Y2
					,DstImage,dx ,dy
					,MaxDx ,MaxDy);
}

float	LineMatchingX::SearchMax(int x1,int y1 ,int x2 ,int y2
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy)
{
	int	X1=max(x1,0);
	int	X2=min(x2,DstImage.GetWidth()-1);
	int	Y1=max(y1,0);
	int	Y2=min(y2,DstImage.GetHeight()-1);

	return SearchMaxRaw(X1,Y1 ,X2 ,Y2
								,DstImage,dx ,dy
								,MaxDx ,MaxDy);
}

float	LineMatchingX::SearchMaxRaw(int X1,int Y1 ,int X2 ,int Y2
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy)
{
	double	MaxD=0;
	int		LMaxDx=0;
	int		LMaxDy=0;
	if(SkipX==1){
		for(int y=Y1;y<=Y2;y+=SkipY){
			int		BB;
			int		B;
			int		x=X1;
			int		AB=Calc1stSkip1(x,y,DstImage,BB ,B);
			double	d=CalcCoef(AB ,BB ,B);
			if(d>MaxD){
				MaxD=d;
				LMaxDx=X1;
				LMaxDy=y;
			}
			for(x+=SkipX;x<=X2;x+=SkipX){
				int		AB=CalcRightStepSkip1(x,y,DstImage,BB ,B);
				double	d=CalcCoef(AB ,BB ,B);
				if(d>MaxD){
					MaxD=d;
					LMaxDx=X1;
					LMaxDy=y;
				}
			}
		}
	}
	else{
		for(int y=Y1;y<=Y2;y+=SkipY){
			int		BB;
			int		B;
			int		x=X1;
			int		AB=Calc1st(x,y,DstImage,BB ,B);
			double	d=CalcCoef(AB ,BB ,B);
			if(d>MaxD){
				MaxD=d;
				LMaxDx=X1;
				LMaxDy=y;
			}
			for(x+=SkipX;x<=X2;x+=SkipX){
				int		AB=CalcRightStep(x,y,DstImage,BB ,B);
				double	d=CalcCoef(AB ,BB ,B);
				if(d>MaxD){
					MaxD=d;
					LMaxDx=X1;
					LMaxDy=y;
				}
			}
		}
	}
	MaxDx=LMaxDx-LeftX;
	MaxDy=LMaxDy-Y;
	return MaxD;
}

int	LineMatchingX::Calc1st(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	BB=0;
	B=0;
	int	AB=0;
	BYTE	*s=LineData;
	BYTE	*d=DstImage.GetY(Y);
	for(int x=0;x<LineLen;x+=SkipX){
		BYTE	a=*s++;
		BYTE	b=d[X+x];
		BB	+=b*b;
		B	+=b;
		AB	+=a*b;
	}
	return AB;
}
int		LineMatchingX::Calc1stSkip1		(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	BB=0;
	B=0;
	int	AB=0;
	BYTE	*s=LineData;
	BYTE	*d=DstImage.GetY(Y);
	for(int x=0;x<LineLen;x++){
		BYTE	a=*s++;
		BYTE	b=d[X+x];
		BB	+=b*b;
		B	+=b;
		AB	+=a*b;
	}
	return AB;
}

int	LineMatchingX::CalcRightStep(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	int	AB=0;
	BYTE	*s=LineData;
	BYTE	*d=DstImage.GetY(Y);

	BYTE	a;
	BYTE	b=d[X-SkipX];
	BB-=b*b;
	B-=b;
	for(int x=0;x<LineLen;x+=SkipX){
		a=*s++;
		b=d[X+x];
		AB	+=a*b;
	}
	BB+=b*b;
	B +=b;

	return AB;
}
int		LineMatchingX::CalcRightStepSkip1	(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	int	AB=0;
	BYTE	*s=LineData;
	BYTE	*d=DstImage.GetY(Y);

	BYTE	a;
	BYTE	b=d[X-SkipX];
	BB-=b*b;
	B-=b;
	for(int x=0;x<LineLen;x++){
		a=*s++;
		b=d[X+x];
		AB	+=a*b;
	}
	BB+=b*b;
	B +=b;

	return AB;
}

float	LineMatchingX::CalcCoef(int AB ,int BB ,int B)
{
	float	AvrA=((float)A)/(float)XNumb;
	float	AvrB=((float)B)/(float)XNumb;

	float	D=(AA-XNumb*AvrA*AvrA)*(BB-XNumb*AvrB*AvrB);
	if(D<=0.0)
		return 0;
	return (AB-XNumb*AvrA*AvrB)/sqrt(D);
}

//================================================================================


LineMatchingY::LineMatchingY(void)
{
	LineData=NULL;
	LineLen=0;
}
LineMatchingY::LineMatchingY(const LineMatchingY &src)
{
	LineLen	=src.LineLen;
	YNumb	=src.YNumb;
	SkipX	=src.SkipX;
	SkipY	=src.SkipY;
	LeftX	=src.LeftX;
	Y		=src.Y;
	AA		=src.AA;
	A		=src.A;
	LineData=new BYTE[LineLen];
	memcpy(LineData,src.LineData,LineLen);
}
LineMatchingY::~LineMatchingY(void)
{
	if(LineData!=NULL){
		delete	[]LineData;
		LineData=NULL;
		LineLen=0;
	}
}

bool	LineMatchingY::Initial(int _LeftX ,int _LineLen,int _Y
							,ImageBuffer &SrcImage
							,int skipx ,int skipy)
{
	LeftX	=_LeftX;
	LineLen	=_LineLen;
	Y		=_Y;
	SkipX	=(skipx>=1)?skipx:1;
	SkipY	=(skipy>=1)?skipy:1;
	if(LineData!=NULL){
		delete	[]LineData;
	}
	LineData=new BYTE[LineLen];

	if(Y<0 || SrcImage.GetHeight()<=(Y+LineLen)
	|| LeftX<0 || SrcImage.GetWidth()<LeftX){
		return false;
	}

	AA=0;
	A=0;
	YNumb=0;
	for(int y=0;y<LineLen;y+=SkipY,YNumb++){
		BYTE	*s=SrcImage.GetY(Y+y);
		BYTE	a=s[LeftX];
		LineData[YNumb]=a;
		AA+=a*a;
		A+=a;
	}

	return true;
}
LineMatchingY	&LineMatchingY::operator=(const LineMatchingY &src)
{
	LineLen	=src.LineLen;
	YNumb	=src.YNumb;
	SkipX	=src.SkipX;
	SkipY	=src.SkipY;
	LeftX	=src.LeftX;
	Y		=src.Y;
	AA		=src.AA;
	A		=src.A;
	if(LineData!=NULL){
		delete	[]LineData;
	}
	LineData=new BYTE[LineLen];
	memcpy(LineData,src.LineData,LineLen);
	return *this;
}

double	LineMatchingY::GetVarSrc(void)
{
	double	AvrA=((double)A)/YNumb;
	double	V=(AA-AvrA*AvrA*YNumb)/YNumb;
	return V;
}

float	LineMatchingY::SearchMax(int SearchX ,int SearchY
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy)
{
	int	X1=max(LeftX-SearchX+dx,0);
	int	X2=min(LeftX+SearchX+dx,DstImage.GetWidth()-1);
	int	Y1=max(Y-SearchY+dy,0);
	int	Y2=min(Y+SearchY+dy,DstImage.GetHeight()-1);

	return SearchMax(X1,Y1 ,X2 ,Y2
					,DstImage,dx ,dy
					,MaxDx ,MaxDy);
}

float	LineMatchingY::SearchMax(int x1,int y1 ,int x2 ,int y2
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy)
{
	int	X1=max(x1,0);
	int	X2=min(x2,DstImage.GetWidth()-1);
	int	Y1=max(y1,0);
	int	Y2=min(y2,DstImage.GetHeight()-1);

	return SearchMaxRaw(X1,Y1 ,X2 ,Y2
								,DstImage,dx ,dy
								,MaxDx ,MaxDy);
}
float	LineMatchingY::SearchMaxRaw(int X1,int Y1 ,int X2 ,int Y2
								,ImageBuffer &DstImage,int dx ,int dy
								,int &MaxDx ,int &MaxDy)
{
	double	MaxD=0;
	int		LMaxDx=0;
	int		LMaxDy=0;
	if(SkipX==1){
		for(int x=X1;x<=X2;x+=SkipX){
			int		BB;
			int		B;
			int		y=Y1;
			int		AB=Calc1stSkip1(x,y,DstImage,BB ,B);
			double	d=CalcCoef(AB ,BB ,B);
			if(d>MaxD){
				MaxD=d;
				LMaxDx=X1;
				LMaxDy=y;
			}
			for(y+=SkipY;y<=Y2;y+=SkipY){
				int		AB=CalcLowerStepSkip1(x,y,DstImage,BB ,B);
				double	d=CalcCoef(AB ,BB ,B);
				if(d>MaxD){
					MaxD=d;
					LMaxDx=X1;
					LMaxDy=y;
				}
			}
		}
	}
	else{
		for(int x=X1;x<=X2;x+=SkipX){
			int		BB;
			int		B;
			int		y=Y1;
			int		AB=Calc1st(x,y,DstImage,BB ,B);
			double	d=CalcCoef(AB ,BB ,B);
			if(d>MaxD){
				MaxD=d;
				LMaxDx=X1;
				LMaxDy=y;
			}
			for(y+=SkipY;y<=Y2;y+=SkipY){
				int		AB=CalcLowerStep(x,y,DstImage,BB ,B);
				double	d=CalcCoef(AB ,BB ,B);
				if(d>MaxD){
					MaxD=d;
					LMaxDx=X1;
					LMaxDy=y;
				}
			}
		}
	}
	MaxDx=LMaxDx-LeftX;
	MaxDy=LMaxDy-Y;
	return MaxD;
}

int	LineMatchingY::Calc1st(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	BB=0;
	B=0;
	int	AB=0;
	BYTE	*s=LineData;
	for(int y=0;y<LineLen;y+=SkipY){
		BYTE	*d=DstImage.GetY(Y+y);
		BYTE	a=*s++;
		BYTE	b=d[X];
		BB	+=b*b;
		B	+=b;
		AB	+=a*b;
	}
	return AB;
}
int		LineMatchingY::Calc1stSkip1		(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	BB=0;
	B=0;
	int	AB=0;
	BYTE	*s=LineData;
	for(int y=0;y<LineLen;y++){
		BYTE	*d=DstImage.GetY(Y+y);
		BYTE	a=*s++;
		BYTE	b=d[X];
		BB	+=b*b;
		B	+=b;
		AB	+=a*b;
	}
	return AB;
}

int	LineMatchingY::CalcLowerStep(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	int	AB=0;
	BYTE	*s=LineData;
	BYTE	*d=DstImage.GetY(Y-SkipY);

	BYTE	a;
	BYTE	b=d[X];
	BB-=b*b;
	B-=B;
	for(int y=0;y<LineLen;y+=SkipY){
		d=DstImage.GetY(Y+y);
		a=*s++;
		b=d[X];
		AB	+=a*b;
	}
	BB+=b*b;
	B +=b;

	return AB;
}
int		LineMatchingY::CalcLowerStepSkip1	(int X,int Y,ImageBuffer &DstImage,int &BB ,int &B)
{
	int	AB=0;
	BYTE	*s=LineData;
	BYTE	*d=DstImage.GetY(Y-SkipY);

	BYTE	a;
	BYTE	b=d[X];
	BB-=b*b;
	B-=B;
	for(int y=0;y<LineLen;y++){
		d=DstImage.GetY(Y+y);
		a=*s++;
		b=d[X];
		AB	+=a*b;
	}
	BB+=b*b;
	B +=b;

	return AB;
}

float	LineMatchingY::CalcCoef(int AB ,int BB ,int B)
{
	float	AvrA=((float)A)/(float)YNumb;
	float	AvrB=((float)B)/(float)YNumb;

	float	D=(AA-YNumb*AvrA*AvrA)*(BB-YNumb*AvrB*AvrB);
	if(D<=0.0)
		return 0;
	return (AB-YNumb*AvrA*AvrB)/sqrt(D);
}