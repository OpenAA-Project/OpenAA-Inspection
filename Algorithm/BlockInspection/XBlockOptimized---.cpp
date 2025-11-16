#include "XTypeDef.h"
#include "XFlexArea.h"
#include "XPointer.h"
#include "XMainSchemeMemory.h"

WORD	CalcCenterBright(unsigned int BrightTable[256])
{
	unsigned int	M=0;
	unsigned int	N=0;
	for(int i=0;i<256;i++){
		M+=i*BrightTable[i];
		N+=BrightTable[i];
	}
	if(N==0)
		return 0;
	return M/N;
}


unsigned int		CalcTableAddL(unsigned int BrightTable[] ,int BrightWidthL)
{
	unsigned int	SumL=0;
	for(int i=0;i<BrightWidthL;i++){
		SumL+=BrightTable[i];
	}
	return SumL;
}
unsigned int		CalcTableAddH(unsigned int BrightTable[] ,int BrightWidthH)
{
	unsigned int	SumH=0;
	int	N=255-BrightWidthH;
	unsigned int	*p=&BrightTable[BrightWidthH+1];
	for(int i=0;i<N;i++){
		SumH+=p[i];
	}
	return SumH;
}

unsigned int		CalcTableRange(unsigned int BrightTable[] ,int BrightWidthL,int BrightWidthH)
{
	unsigned int	Sum=0;
	int	N=BrightWidthH-BrightWidthL;
	unsigned int	*p=&BrightTable[BrightWidthL];
	for(int i=0;i<N;i++){
		Sum+=p[i];
	}
	return Sum;
}

void	IncreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		for(int x=0;x<Numb;x++){
			unsigned int	c=src[x];
			BrightTable[c]++;
		}
	}
}
void	DecreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y	=Appe.GetFLineAbsY  (i)+my;
		int	x1	=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		for(int x=0;x<Numb;x++){
			unsigned	int	c=src[x];
			BrightTable[c]--;
		}
	}
}

void	IncreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		BYTE	*M=DynamicMaskMap[y];
		for(int x=0;x<Numb;x++){
			if(GetBmpBitOnY(M,x+x1)==0){
				unsigned	int	c=src[x];
				BrightTable[c]++;
			}
		}
	}
}
void	DecreaseTable(FlexArea &Appe,unsigned int BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		BYTE	*M=DynamicMaskMap[y];
		for(int x=0;x<Numb;x++){
			if(GetBmpBitOnY(M,x+x1)==0){
				unsigned	int	c=src[x];
				BrightTable[c]--;
			}
		}
	}
}
void MakeBrightList(FlexArea &A,unsigned int BrightTable[256],ImageBuffer &data,int Dx,int Dy
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int ret=0;
	int X;
	BYTE	*p;
	int	LNumb=A.GetFLineLen();
	for(int i=0;i<LNumb;i++){
		int Y=A.GetFLineAbsY(i) +Dy;
		int	N=0;
		if(Y>0 && Y<A.GetMaxLines() && Y<data.GetHeight()){
			BYTE	*M=DynamicMaskMap[Y];
			X=A.GetFLineLeftX(i)+Dx;
			N=A.GetFLineNumb(i);
			if(X<0){
				N-= -X;
				X=0;
			}
			if(N>0 && X<A.GetDotPerLine() && X<data.GetWidth()){
				if(X+N>=A.GetDotPerLine()){
					N=A.GetDotPerLine()-X;
				}
				p=(data.GetY(Y)+X);
				for(int j=0;j<N;j++,p++){
					if(GetBmpBitOnY(M,X+j)==0){
						BrightTable[*p]++;
					}
				}
			}
		}
	}
	
}

//========================================================================================================

WORD	CalcCenterBright(unsigned short BrightTable[256])
{
	unsigned int	M=0;
	unsigned int	N=0;
	for(int i=0;i<256;i++){
		M+=i*BrightTable[i];
		N+=BrightTable[i];
	}
	if(N==0)
		return 0;
	return M/N;
}


unsigned int		CalcTableAddL(unsigned short BrightTable[] ,int BrightWidthL)
{
	unsigned int	SumL=0;
	for(int i=0;i<BrightWidthL;i++){
		SumL+=BrightTable[i];
	}
	return SumL;
}
unsigned int		CalcTableAddH(unsigned short BrightTable[] ,int BrightWidthH)
{
	unsigned int	SumH=0;
	int	N=255-BrightWidthH;
	unsigned short	*p=&BrightTable[BrightWidthH+1];
	for(int i=0;i<N;i++){
		SumH+=p[i];
	}
	return SumH;
}

unsigned int		CalcTableRange(unsigned short BrightTable[] ,int BrightWidthL,int BrightWidthH)
{
	unsigned int	Sum=0;
	int	N=BrightWidthH-BrightWidthL;
	unsigned short	*p=&BrightTable[BrightWidthL];
	for(int i=0;i<N;i++){
		Sum+=p[i];
	}
	return Sum;
}

void	IncreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		for(int x=0;x<Numb;x++){
			unsigned int	c=src[x];
			BrightTable[c]++;
		}
	}
}
void	DecreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y	=Appe.GetFLineAbsY  (i)+my;
		int	x1	=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		for(int x=0;x<Numb;x++){
			unsigned	int	c=src[x];
			BrightTable[c]--;
		}
	}
}

void	IncreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		BYTE	*M=DynamicMaskMap[y];
		for(int x=0;x<Numb;x++){
			if(GetBmpBitOnY(M,x+x1)==0){
				unsigned	int	c=src[x];
				BrightTable[c]++;
			}
		}
	}
}
void	DecreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		BYTE	*M=DynamicMaskMap[y];
		for(int x=0;x<Numb;x++){
			if(GetBmpBitOnY(M,x+x1)==0){
				unsigned	int	c=src[x];
				BrightTable[c]--;
			}
		}
	}
}
void MakeBrightList(FlexArea &A,unsigned short BrightTable[256],ImageBuffer &data,int Dx,int Dy
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int ret=0;
	int X;
	BYTE	*p;
	int	LNumb=A.GetFLineLen();
	for(int i=0;i<LNumb;i++){
		int Y=A.GetFLineAbsY(i) +Dy;
		int	N=0;
		if(Y>0 && Y<A.GetMaxLines() && Y<data.GetHeight()){
			BYTE	*M=DynamicMaskMap[Y];
			X=A.GetFLineLeftX(i)+Dx;
			N=A.GetFLineNumb(i);
			if(X<0){
				N-= -X;
				X=0;
			}
			if(N>0 && X<A.GetDotPerLine() && X<data.GetWidth()){
				if(X+N>=A.GetDotPerLine()){
					N=A.GetDotPerLine()-X;
				}
				p=(data.GetY(Y)+X);
				for(int j=0;j<N;j++,p++){
					if(GetBmpBitOnY(M,X+j)==0){
						BrightTable[*p]++;
					}
				}
			}
		}
	}
	
}
