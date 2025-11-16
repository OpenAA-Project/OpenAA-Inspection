#include <cmath>
#include "XTypeDef.h"
#include "XFlexArea.h"
#include "XPointer.h"
#include "XMainSchemeMemory.h"
#include "swap.h"

#define	CalcExtention	20

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
		int	MaskIndex=x1>>3;
		if(Numb<CalcExtention){
			if(*((unsigned int *)(&M[MaskIndex]))==0){
				for(int x=0;x<Numb;x++){
					unsigned	int	c=src[x];
					BrightTable[c]++;
				}
			}
			else{
				for(int x=0;x<Numb;x++){
					if(GetBmpBitOnY(M,x1+x)==0){
						unsigned	int	c=src[x];
						BrightTable[c]++;
					}
				}
			}
		}
		else{
			int	TopBit=x1&7;
			BYTE	Mask;
			int	LoopN;
			switch(TopBit){
			case 0:
				Mask=0xFF;
				LoopN=min(8,Numb);
				break;
			case 1:
				Mask=0x7F;
				LoopN=min(7,Numb);
				break;
			case 2:
				Mask=0x3F;
				LoopN=min(6,Numb);
				break;
			case 3:
				Mask=0x1F;
				LoopN=min(5,Numb);
				break;
			case 4:
				Mask=0x0F;
				LoopN=min(4,Numb);
				break;
			case 5:
				Mask=0x07;
				LoopN=min(3,Numb);
				break;
			case 6:
				Mask=0x03;
				LoopN=min(2,Numb);
				break;
			case 7:
				Mask=0x01;
				LoopN=min(1,Numb);
				break;
			}
			BYTE	MaskData=M[MaskIndex];
			if((MaskData&Mask)==0){
				for(int x=0;x<LoopN;x++){
					unsigned	int	c=src[x];
					BrightTable[c]++;
				}
			}
			else{
				Mask=0x80>>(x1&7);
				for(int x=0;x<LoopN;x++){
					if((MaskData&Mask)==0){
						unsigned	int	c=src[x];
						BrightTable[c]++;
					}
					Mask>>=1;
				}
			}
			Numb-=LoopN;
			//if(Numb>0){
				src+=LoopN;
				M=&M[MaskIndex+1];
				for(int k=0;k<Numb;k+=8){
					LoopN=min(8,Numb-k);
					if(*M==0){
						for(int x=0;x<LoopN;x++){
							unsigned	int	c=src[x];
							BrightTable[c]++;
						}
					}
					else{
						Mask=0x80;
						MaskData=*M;
						for(int x=0;x<LoopN;x++){
							if((MaskData&Mask)==0){
								unsigned	int	c=src[x];
								BrightTable[c]++;
							}
							Mask>>=1;
						}
					}
					M++;
					src+=LoopN;
				}
			//}
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
		int	MaskIndex=x1>>3;
		if(Numb<CalcExtention){
			if(*((unsigned int *)(&M[MaskIndex]))==0){
				for(int x=0;x<Numb;x++){
					unsigned	int	c=src[x];
					BrightTable[c]--;
				}
			}
			else{
				for(int x=0;x<Numb;x++){
					if(GetBmpBitOnY(M,x1+x)==0){
						unsigned	int	c=src[x];
						BrightTable[c]--;
					}
				}
			}
		}
		else{
			int	TopBit=x1&7;
			BYTE	Mask;
			int	LoopN;
			switch(TopBit){
			case 0:
				Mask=0xFF;
				LoopN=min(8,Numb);
				break;
			case 1:
				Mask=0x7F;
				LoopN=min(7,Numb);
				break;
			case 2:
				Mask=0x3F;
				LoopN=min(6,Numb);
				break;
			case 3:
				Mask=0x1F;
				LoopN=min(5,Numb);
				break;
			case 4:
				Mask=0x0F;
				LoopN=min(4,Numb);
				break;
			case 5:
				Mask=0x07;
				LoopN=min(3,Numb);
				break;
			case 6:
				Mask=0x03;
				LoopN=min(2,Numb);
				break;
			case 7:
				Mask=0x01;
				LoopN=min(1,Numb);
				break;
			}
			int	MaskIndex=x1>>3;
			BYTE	MaskData=M[MaskIndex];
			if((MaskData&Mask)==0){
				for(int x=0;x<LoopN;x++){
					unsigned	int	c=src[x];
					BrightTable[c]--;
					src++;
				}
			}
			else{
				Mask=0x80>>(x1&7);
				for(int x=0;x<LoopN;x++){
					if((MaskData&Mask)==0){
						unsigned	int	c=src[x];
						BrightTable[c]--;
					}
					Mask>>=1;
				}
			}
			Numb-=LoopN;
			//if(Numb>0){
				src+=LoopN;
				M=&M[MaskIndex+1];
				for(int k=0;k<Numb;k+=8){
					LoopN=min(8,Numb-k);
					if(*M==0){
						for(int x=0;x<LoopN;x++){
							unsigned	int	c=src[x];
							BrightTable[c]--;
						}
					}
					else{
						Mask=0x80;
						MaskData=*M;
						for(int x=0;x<LoopN;x++){
							if((MaskData&Mask)==0){
								unsigned	int	c=src[x];
								BrightTable[c]--;
							}
							Mask>>=1;
						}
					}
					M++;
					src+=LoopN;
				}
			//}
		}
	}
}
void MakeBrightList(FlexArea &A,int DotPerLine ,int MaxLines ,unsigned int BrightTable[256],ImageBuffer &data,int Dx,int Dy
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int x1;
	int	LNumb=A.GetFLineLen();
	for(int i=0;i<LNumb;i++){
		int Y=A.GetFLineAbsY(i) +Dy;
		int	Numb=0;
		if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
			x1=A.GetFLineLeftX(i)+Dx;
			Numb=A.GetFLineNumb(i);
			if(x1<0){
				Numb-= -x1;
				x1=0;
			}
			if(Numb>0 && x1<DotPerLine && x1<data.GetWidth()){
				if(x1+Numb>=DotPerLine){
					Numb=DotPerLine-x1;
				}

				BYTE	*src=&data.GetY(Y)[x1];
				BYTE	*M=DynamicMaskMap[Y];

				int	MaskIndex=x1>>3;
				if(Numb<CalcExtention){
					if(*((unsigned int *)(&M[MaskIndex]))==0){
						for(int x=0;x<Numb;x++){
							unsigned	int	c=src[x];
							BrightTable[c]++;
						}
					}
					else{
						for(int x=0;x<Numb;x++){
							if(GetBmpBitOnY(M,x1+x)==0){
								unsigned	int	c=src[x];
								BrightTable[c]++;
							}
						}
					}
				}
				else{
					int	TopBit=x1&7;
					BYTE	Mask;
					int	LoopN;
					switch(TopBit){
					case 0:
						Mask=0xFF;
						LoopN=min(8,Numb);
						break;
					case 1:
						Mask=0x7F;
						LoopN=min(7,Numb);
						break;
					case 2:
						Mask=0x3F;
						LoopN=min(6,Numb);
						break;
					case 3:
						Mask=0x1F;
						LoopN=min(5,Numb);
						break;
					case 4:
						Mask=0x0F;
						LoopN=min(4,Numb);
						break;
					case 5:
						Mask=0x07;
						LoopN=min(3,Numb);
						break;
					case 6:
						Mask=0x03;
						LoopN=min(2,Numb);
						break;
					case 7:
						Mask=0x01;
						LoopN=min(1,Numb);
						break;
					}
					BYTE	MaskData=M[MaskIndex];
					if((MaskData&Mask)==0){
						for(int x=0;x<LoopN;x++){
							unsigned	int	c=src[x];
							BrightTable[c]++;
						}
					}
					else{
						Mask=0x80>>(x1&7);
						for(int x=0;x<LoopN;x++){
							if((MaskData&Mask)==0){
								unsigned	int	c=src[x];
								BrightTable[c]++;
							}
							Mask>>=1;
						}
					}
					Numb-=LoopN;
					//if(Numb>0){
						src+=LoopN;
						M=&M[MaskIndex+1];
						for(int k=0;k<Numb;k+=8){
							LoopN=min(8,Numb-k);
							if(*M==0){
								for(int x=0;x<LoopN;x++){
									unsigned	int	c=src[x];
									BrightTable[c]++;
								}
							}
							else{
								Mask=0x80;
								MaskData=*M;
								for(int x=0;x<LoopN;x++){
									if((MaskData&Mask)==0){
										unsigned	int	c=src[x];
										BrightTable[c]++;
									}
									Mask>>=1;
								}
							}
							M++;
							src+=LoopN;
						}
					//}
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
		int	MaskIndex=x1>>3;
		if(Numb<CalcExtention){
			if(*((unsigned int *)(&M[MaskIndex]))==0){
				for(int x=0;x<Numb;x++){
					unsigned	int	c=src[x];
					BrightTable[c]++;
				}
			}
			else{
				for(int x=0;x<Numb;x++){
					if(GetBmpBitOnY(M,x1+x)==0){
						unsigned	int	c=src[x];
						BrightTable[c]++;
					}
				}
			}
		}
		else{
			int	TopBit=x1&7;
			BYTE	Mask;
			int	LoopN;
			switch(TopBit){
			case 0:
				Mask=0xFF;
				LoopN=min(8,Numb);
				break;
			case 1:
				Mask=0x7F;
				LoopN=min(7,Numb);
				break;
			case 2:
				Mask=0x3F;
				LoopN=min(6,Numb);
				break;
			case 3:
				Mask=0x1F;
				LoopN=min(5,Numb);
				break;
			case 4:
				Mask=0x0F;
				LoopN=min(4,Numb);
				break;
			case 5:
				Mask=0x07;
				LoopN=min(3,Numb);
				break;
			case 6:
				Mask=0x03;
				LoopN=min(2,Numb);
				break;
			case 7:
				Mask=0x01;
				LoopN=min(1,Numb);
				break;
			}
			BYTE	MaskData=M[MaskIndex];
			if((MaskData&Mask)==0){
				for(int x=0;x<LoopN;x++){
					unsigned	int	c=src[x];
					BrightTable[c]++;
				}
			}
			else{
				Mask=0x80>>(x1&7);
				for(int x=0;x<LoopN;x++){
					if((MaskData&Mask)==0){
						unsigned	int	c=src[x];
						BrightTable[c]++;
					}
					Mask>>=1;
				}
			}
			Numb-=LoopN;
			//if(Numb>0){
				src+=LoopN;
				M=&M[MaskIndex+1];
				
				for(int k=0;k<Numb;k+=8){
					LoopN=min(8,Numb-k);
					if(*M==0){
						for(int x=0;x<LoopN;x++){
							unsigned	int	c=src[x];
							BrightTable[c]++;
						}
					}
					else{
						Mask=0x80;
						MaskData=*M;
						for(int x=0;x<LoopN;x++){
							if((MaskData&Mask)==0){
								unsigned	int	c=src[x];
								BrightTable[c]++;
							}
							Mask>>=1;
						}
					}
					M++;
					src+=LoopN;
				}
			//}
		}
	}
}
//static	int	DbgShort;
void	DecreaseTable(FlexArea &Appe,unsigned short BrightTable[],ImageBuffer &IBuff,int mx,int my
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	for(int i=0;i<Appe.GetFLineLen();i++){
		int	y =Appe.GetFLineAbsY  (i)+my;
		int	x1=Appe.GetFLineLeftX (i)+mx;
		int	Numb=Appe.GetFLineNumb(i);

		BYTE	*src=&IBuff.GetY(y)[x1];
		BYTE	*M=DynamicMaskMap[y];
		int	MaskIndex=x1>>3;
		if(Numb<CalcExtention){
			if(*((unsigned int *)(&M[MaskIndex]))==0){
				for(int x=0;x<Numb;x++){
					unsigned	int	c=src[x];
					BrightTable[c]--;
					//if(BrightTable[c]>=0xFFFFu)
					//	DbgShort++;
				}
			}
			else{
				for(int x=0;x<Numb;x++){
					if(GetBmpBitOnY(M,x1+x)==0){
						unsigned	int	c=src[x];
						BrightTable[c]--;
						//if(BrightTable[c]>=0xFFFFu)
						//	DbgShort++;
					}
				}
			}
		}
		else{
			int	TopBit=x1&7;
			BYTE	Mask;
			int	LoopN;
			switch(TopBit){
			case 0:
				Mask=0xFF;
				LoopN=min(8,Numb);
				break;
			case 1:
				Mask=0x7F;
				LoopN=min(7,Numb);
				break;
			case 2:
				Mask=0x3F;
				LoopN=min(6,Numb);
				break;
			case 3:
				Mask=0x1F;
				LoopN=min(5,Numb);
				break;
			case 4:
				Mask=0x0F;
				LoopN=min(4,Numb);
				break;
			case 5:
				Mask=0x07;
				LoopN=min(3,Numb);
				break;
			case 6:
				Mask=0x03;
				LoopN=min(2,Numb);
				break;
			case 7:
				Mask=0x01;
				LoopN=min(1,Numb);
				break;
			}
			BYTE	MaskData=M[MaskIndex];
			if((MaskData&Mask)==0){
				for(int x=0;x<LoopN;x++){
					unsigned	int	c=src[x];
					BrightTable[c]--;
					//if(BrightTable[c]>=0xFFFFu)
					//	DbgShort++;
				}
			}
			else{
				Mask=0x80>>(x1&7);
				for(int x=0;x<LoopN;x++){
					if((MaskData&Mask)==0){
						unsigned	int	c=src[x];
						BrightTable[c]--;
						//if(BrightTable[c]>=0xFFFFu)
						//	DbgShort++;
					}
					Mask>>=1;
				}
			}
			Numb-=LoopN;
			//if(Numb>0){
				src+=LoopN;
				M=&M[MaskIndex+1];
				
				for(int k=0;k<Numb;k+=8){
					LoopN=min(8,Numb-k);
					if(*M==0){
						for(int x=0;x<LoopN;x++){
							unsigned	int	c=src[x];
							BrightTable[c]--;
							//if(BrightTable[c]>=0xFFFFu)
							//	DbgShort++;
						}
					}
					else{
						Mask=0x80;
						MaskData=*M;
						for(int x=0;x<LoopN;x++){
							if((MaskData&Mask)==0){
								unsigned	int	c=src[x];
								BrightTable[c]--;
								//if(BrightTable[c]>=0xFFFFu)
								//	DbgShort++;
							}
							Mask>>=1;
						}
					}
					M++;
					src+=LoopN;
				}
			//}
		}
	}
}
void MakeBrightList(FlexArea &A,int DotPerLine ,int MaxLines ,unsigned short BrightTable[256],ImageBuffer &data,int Dx,int Dy
					,BYTE **DynamicMaskMap,int DynamicMaskMapXByte,int DynamicMaskMapYLen)
{
	int x1;
	int	LNumb=A.GetFLineLen();
	for(int i=0;i<LNumb;i++){
		int Y=A.GetFLineAbsY(i) +Dy;
		int	Numb=0;
		if(Y>0 && Y<MaxLines && Y<data.GetHeight()){
			x1=A.GetFLineLeftX(i)+Dx;
			Numb=A.GetFLineNumb(i);
			if(x1<0){
				Numb-= -x1;
				x1=0;
			}
			if(Numb>0 && x1<DotPerLine && x1<data.GetWidth()){
				if(x1+Numb>=DotPerLine){
					Numb=DotPerLine-x1;
				}

				BYTE	*src=&data.GetY(Y)[x1];
				BYTE	*M=DynamicMaskMap[Y];
				int	MaskIndex=x1>>3;

				if(Numb<CalcExtention){
					if(*((unsigned int *)(&M[MaskIndex]))==0){
						for(int x=0;x<Numb;x++){
							unsigned	int	c=src[x];
							BrightTable[c]++;
						}
					}
					else{
						for(int x=0;x<Numb;x++){
							if(GetBmpBitOnY(M,x1+x)==0){
								unsigned	int	c=src[x];
								BrightTable[c]++;
							}
						}
					}
				}
				else{
					BYTE	Mask;
					int	TopBit=x1&7;
					int	LoopN;
					switch(TopBit){
					case 0:
						Mask=0xFF;
						LoopN=min(8,Numb);
						break;
					case 1:
						Mask=0x7F;
						LoopN=min(7,Numb);
						break;
					case 2:
						Mask=0x3F;
						LoopN=min(6,Numb);
						break;
					case 3:
						Mask=0x1F;
						LoopN=min(5,Numb);
						break;
					case 4:
						Mask=0x0F;
						LoopN=min(4,Numb);
						break;
					case 5:
						Mask=0x07;
						LoopN=min(3,Numb);
						break;
					case 6:
						Mask=0x03;
						LoopN=min(2,Numb);
						break;
					case 7:
						Mask=0x01;
						LoopN=min(1,Numb);
						break;
					}
					BYTE	MaskData=M[MaskIndex];
					if((MaskData&Mask)==0){
						for(int x=0;x<LoopN;x++){
							unsigned	int	c=src[x];
							BrightTable[c]++;
						}
					}
					else{
						Mask=0x80>>(x1&7);
						for(int x=0;x<LoopN;x++){
							if((MaskData&Mask)==0){
								unsigned	int	c=src[x];
								BrightTable[c]++;
							}
							Mask>>=1;
						}
					}
					Numb-=LoopN;
					//if(Numb>0){
						src+=LoopN;
						M=&M[MaskIndex+1];
						
						for(int k=0;k<Numb;k+=8){
							LoopN=min(8,Numb-k);
							if(*M==0){
								for(int x=0;x<LoopN;x++){
									unsigned	int	c=src[x];
									BrightTable[c]++;
								}
							}
							else{
								Mask=0x80;
								MaskData=*M;
								for(int x=0;x<LoopN;x++){
									if((MaskData&Mask)==0){
										unsigned	int	c=src[x];
										BrightTable[c]++;
									}
									Mask>>=1;
								}
							}
							M++;
							src+=LoopN;
						}
					//}
				}
			}
		}
	}
}
