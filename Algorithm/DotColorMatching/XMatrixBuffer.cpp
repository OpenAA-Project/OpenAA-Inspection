#include "XMatrixBuffer.h"
#include <memory.h>

BMatrix::BMatrix(void)
{
	YPoint	=NULL;
	AllPoint=NULL;
	XLen	=-1;
	YLen	=-1;
}
BMatrix::BMatrix(int xlen ,int ylen)
	:XLen(xlen),YLen(ylen)
{
	YPoint	=new struct	LinePoint[YLen];
	memset(YPoint,0,sizeof(struct LinePoint)*YLen);
	AllPoint=NULL;
}
BMatrix::BMatrix(const BMatrix &src)
{
	XLen	=src.XLen;
	YLen	=src.YLen;
	AllPoint=NULL;
	if(YLen>0){
		YPoint	=new struct	LinePoint[YLen];
		if(src.AllPoint!=NULL){
			int	TotalByte=0;
			for(int y=0;y<YLen;y++){
				if(src.YPoint[y].ConstantBrightness==false){
					TotalByte+=XLen;
				}
			}
			AllPoint=new BYTE[TotalByte];
			memcpy(AllPoint,src.AllPoint,TotalByte);
		}
		BYTE	*p=AllPoint;
		for(int y=0;y<YLen;y++){
			YPoint[y].ConstantBrightness=src.YPoint[y].ConstantBrightness	;
			YPoint[y].ConstantColor		=src.YPoint[y].ConstantColor		;
			if(YPoint[y].ConstantBrightness==false){
				YPoint[y].XPoint=p;
				p+=XLen;
			}
			else{
				YPoint[y].XPoint=NULL;
			}
		}
	}
	else{
		YPoint	=NULL;
	}
}
BMatrix::~BMatrix(void)
{
	if(AllPoint!=NULL){
		delete	[]AllPoint;
		AllPoint=NULL;
	}
	if(YPoint!=NULL){
		delete	[]YPoint;
		YPoint=NULL;
	}
}

BMatrix	&BMatrix::operator=(const BMatrix &src)
{
	if(AllPoint!=NULL){
		delete	[]AllPoint;
		AllPoint=NULL;
	}
	if(YPoint!=NULL){
		delete	[]YPoint;
		YPoint=NULL;
	}
	XLen	=src.XLen;
	YLen	=src.YLen;
	AllPoint=NULL;
	if(YLen>0){
		YPoint	=new struct	LinePoint[YLen];
		if(src.AllPoint!=NULL){
			int	TotalByte=0;
			for(int y=0;y<YLen;y++){
				if(src.YPoint[y].ConstantBrightness==false){
					TotalByte+=XLen;
				}
			}
			AllPoint=new BYTE[TotalByte];
			memcpy(AllPoint,src.AllPoint,TotalByte);
		}
		BYTE	*p=AllPoint;
		for(int y=0;y<YLen;y++){
			YPoint[y].ConstantBrightness=src.YPoint[y].ConstantBrightness	;
			YPoint[y].ConstantColor		=src.YPoint[y].ConstantColor		;
			if(YPoint[y].ConstantBrightness==false){
				YPoint[y].XPoint=p;
				p+=XLen;
			}
			else{
				YPoint[y].XPoint=NULL;
			}
		}
	}
	else{
		YPoint	=NULL;
	}
	return *this;
}
bool	BMatrix::AllocHead(int xlen ,int ylen)
{
	if(XLen!=xlen || YLen!=ylen){
		if(YPoint!=NULL){
			delete	[]YPoint;
		}
		XLen=xlen;
		YLen=ylen;
		YPoint	=new struct	LinePoint[YLen];
	}
	memset(YPoint,0,sizeof(struct LinePoint)*YLen);
	if(AllPoint!=NULL){
		delete	[]AllPoint;
	}
	AllPoint=NULL;
	return true;
}
bool	BMatrix::AllocHead(void)
{
	if(XLen>0 && YLen>0){
		if(YPoint!=NULL){
			delete	[]YPoint;
		}
		YPoint	=new struct	LinePoint[YLen];
		memset(YPoint,0,sizeof(struct	LinePoint)*YLen);
		if(AllPoint!=NULL){
			delete	[]AllPoint;
		}
		AllPoint=NULL;
		return true;
	}
	else
	if(XLen>=0 && YLen>=0){
		if(YPoint!=NULL){
			delete	[]YPoint;
		}
		YPoint	=NULL;
		if(AllPoint!=NULL){
			delete	[]AllPoint;
		}
		AllPoint=NULL;
		return true;
	}
	return false;
}

bool	BMatrix::SetConstantBrightness(int y ,int Color)
{
	if(YPoint!=NULL && 0<=y && y<YLen){
		if(Color>=0){
			YPoint[y].ConstantBrightness=true;
			YPoint[y].ConstantColor		=Color;
		}
		else{
			YPoint[y].ConstantBrightness=false;
		}
		return true;
	}
	return false;
}

bool	BMatrix::Alloc(void)
{
	int	TotalByte=0;
	for(int y=0;y<YLen;y++){
		if(YPoint[y].ConstantBrightness==false){
			TotalByte+=XLen;
		}
	}
	if(AllPoint!=NULL){
		delete	[]AllPoint;
	}
	AllPoint=new BYTE[TotalByte];

	BYTE	*p=AllPoint;
	for(int y=0;y<YLen;y++){
		if(YPoint[y].ConstantBrightness==false){
			YPoint[y].XPoint=p;
			p+=XLen;
		}
		else{
			YPoint[y].XPoint=NULL;
		}
	}
	return true;
}
void	BMatrix::Copy(BYTE **Buff ,int xlen ,int ylen ,int Threshold)
{
	if(AllocHead(xlen ,ylen)==true){
		for(int y=0;y<YLen;y++){
			BYTE	*p=Buff[y];
			int32	iAvr=0;
			for(int x=0;x<XLen;x++){
				iAvr+=*p;
				p++;
			}
			double	Avr=((double)iAvr)/XLen;
			p=Buff[y];
			double	MaxD=0;
			for(int x=0;x<XLen;x++,p++){
				double	d=fabs(Avr-*p);
				if(d>MaxD){
					MaxD=d;
				}
			}
			if(MaxD<Threshold){
				SetConstantBrightness(y ,(int)Avr);
			}
			else{
				SetConstantBrightness(y ,-1);
			}
		}
		Alloc();
		for(int y=0;y<YLen;y++){
			if(IsConstantColor(y)==NULL){
				memcpy(GetY(y),Buff[y],XLen);
			}
		}
	}
}


//=============================================================================================

BMatrixBrightHL::BMatrixBrightHL(void)
{
	YPoint	=NULL;
	AllPoint=NULL;
	XLen	=-1;
	YLen	=-1;
}

BMatrixBrightHL::BMatrixBrightHL(int xlen ,int ylen)
	:XLen(xlen),YLen(ylen)
{
	YPoint	=new struct	LinePoint[YLen];
	memset(YPoint,0,sizeof(struct LinePoint)*YLen);
	AllPoint=NULL;
}

BMatrixBrightHL::BMatrixBrightHL(const BMatrixBrightHL &src)
{
	XLen	=src.XLen;
	YLen	=src.YLen;
	AllPoint=NULL;
	if(YLen>0){
		YPoint	=new struct	LinePoint[YLen];
		if(src.AllPoint!=NULL){
			int	TotalByte=0;
			for(int y=0;y<YLen;y++){
				if(src.YPoint[y].ConstantBrightness==false){
					TotalByte+=XLen;
				}
			}
			AllPoint=new struct BrightHLStruct[TotalByte];
			memcpy(AllPoint,src.AllPoint,sizeof(struct BrightHLStruct)*TotalByte);
		}
		struct BrightHLStruct	*p=AllPoint;
		for(int y=0;y<YLen;y++){
			YPoint[y].ConstantBrightness=src.YPoint[y].ConstantBrightness	;
			YPoint[y].ConstantColor		=src.YPoint[y].ConstantColor		;
			if(YPoint[y].ConstantBrightness==false){
				YPoint[y].XPoint=p;
				p+=XLen;
			}
			else{
				YPoint[y].XPoint=NULL;
			}
		}
	}
	else{
		YPoint	=NULL;
	}
}
BMatrixBrightHL::~BMatrixBrightHL(void)
{
	if(AllPoint!=NULL){
		delete	[]AllPoint;
		AllPoint=NULL;
	}
	if(YPoint!=NULL){
		delete	[]YPoint;
		YPoint=NULL;
	}
}

BMatrixBrightHL	&BMatrixBrightHL::operator=(const BMatrixBrightHL &src)
{
	XLen	=src.XLen;
	YLen	=src.YLen;
	AllPoint=NULL;
	if(YLen>0){
		YPoint	=new struct	LinePoint[YLen];
		if(src.AllPoint!=NULL){
			int	TotalByte=0;
			for(int y=0;y<YLen;y++){
				if(src.YPoint[y].ConstantBrightness==false){
					TotalByte+=XLen;
				}
			}
			AllPoint=new struct BrightHLStruct[TotalByte];
			memcpy(AllPoint,src.AllPoint,sizeof(struct BrightHLStruct)*TotalByte);
		}
		struct BrightHLStruct	*p=AllPoint;
		for(int y=0;y<YLen;y++){
			YPoint[y].ConstantBrightness=src.YPoint[y].ConstantBrightness	;
			YPoint[y].ConstantColor		=src.YPoint[y].ConstantColor		;
			if(YPoint[y].ConstantBrightness==false){
				YPoint[y].XPoint=p;
				p+=XLen;
			}
			else{
				YPoint[y].XPoint=NULL;
			}
		}
	}
	else{
		YPoint	=NULL;
	}
	return *this;
}
bool	BMatrixBrightHL::AllocHead(int xlen ,int ylen)
{
	if(XLen!=xlen || YLen!=ylen){
		if(YPoint!=NULL){
			delete	[]YPoint;
		}
		XLen=xlen;
		YLen=ylen;
		YPoint	=new struct	LinePoint[YLen];
	}
	memset(YPoint,0,sizeof(struct LinePoint)*YLen);
	if(AllPoint!=NULL){
		delete	[]AllPoint;
	}
	AllPoint=NULL;
	return true;
}
bool	BMatrixBrightHL::AllocHead(void)
{
	if(XLen>0 && YLen>0){
		if(YPoint!=NULL){
			delete	[]YPoint;
		}
		YPoint	=new struct	LinePoint[YLen];
		memset(YPoint,0,sizeof(struct	LinePoint)*YLen);
		if(AllPoint!=NULL){
			delete	[]AllPoint;
		}
		AllPoint=NULL;
		return true;
	}
	else
	if(XLen>=0 && YLen>=0){
		if(YPoint!=NULL){
			delete	[]YPoint;
		}
		YPoint	=NULL;
		if(AllPoint!=NULL){
			delete	[]AllPoint;
		}
		AllPoint=NULL;
		return true;
	}
	return false;
}

bool	BMatrixBrightHL::SetConstantBrightness(int y ,struct BMatrixBrightHL::BrightHLStruct *Color)
{
	if(YPoint!=NULL && 0<=y && y<YLen){
		if(Color!=NULL){
			YPoint[y].ConstantBrightness=true;
			YPoint[y].ConstantColor		=*Color;
		}
		else{
			YPoint[y].ConstantBrightness=false;
		}
		return true;
	}
	return false;
}

bool	BMatrixBrightHL::Alloc(void)
{
	int	TotalCount=0;
	for(int y=0;y<YLen;y++){
		if(YPoint[y].ConstantBrightness==false){
			TotalCount+=XLen;
		}
	}
	if(AllPoint!=NULL){
		delete	[]AllPoint;
	}
	AllPoint=new struct BrightHLStruct[TotalCount];

	struct BrightHLStruct	*p=AllPoint;
	for(int y=0;y<YLen;y++){
		if(YPoint[y].ConstantBrightness==false){
			YPoint[y].XPoint=p;
			p+=XLen;
		}
		else{
			YPoint[y].XPoint=NULL;
		}
	}
	return true;
}
void	BMatrixBrightHL::Copy(struct BMatrixBrightHL::BrightHLStruct **Buff ,int xlen ,int ylen ,int Threshold)
{
	if(AllocHead(xlen ,ylen)==true){
		for(int y=0;y<YLen;y++){
			struct BMatrixBrightHL::BrightHLStruct	*p=Buff[y];
			int32	iAvrBrLow[3];
			int32	iAvrBrHigh[3];
			for(int i=0;i<3;i++){
				iAvrBrLow[i]=0;
				iAvrBrHigh[i]=0;
			}
			for(int x=0;x<XLen;x++){
				for(int i=0;i<3;i++){
					iAvrBrLow[i] +=p->BrLow[i];
					iAvrBrHigh[i]+=p->BrHigh[i];
				}
				p++;
			}
			double	AvrBrLow[3];
			double	AvrBrHigh[3];
			for(int i=0;i<3;i++){
				AvrBrLow [i]=((double)iAvrBrLow [i])/XLen;
				AvrBrHigh[i]=((double)iAvrBrHigh[i])/XLen;
			}
			p=Buff[y];
			double	MaxDBrLow[3];
			double	MaxDBrHigh[3];
			for(int i=0;i<3;i++){
				MaxDBrLow [i]=0;
				MaxDBrHigh[i]=0;
			}
			for(int x=0;x<XLen;x++,p++){
				double	d;
				for(int i=0;i<3;i++){
					d=fabs(AvrBrLow[i]-p->BrLow[i]);
					if(d>MaxDBrLow[i]){
						MaxDBrLow[i]=d;
					}
					d=fabs(AvrBrHigh[i]-p->BrHigh[i]);
					if(d>MaxDBrHigh[i]){
						MaxDBrHigh[i]=d;
					}
				}
			}
			if(MaxDBrLow[0]<Threshold
			&& MaxDBrLow[1]<Threshold
			&& MaxDBrLow[2]<Threshold
			&& MaxDBrHigh[0]<Threshold
			&& MaxDBrHigh[1]<Threshold
			&& MaxDBrHigh[2]<Threshold){
				struct BMatrixBrightHL::BrightHLStruct	Avr;
				for(int i=0;i<3;i++){
					Avr.BrLow [i]=AvrBrLow [i];
					Avr.BrHigh[i]=AvrBrHigh[i];
				}
				SetConstantBrightness(y ,&Avr);
			}
			else{
				SetConstantBrightness(y ,NULL);
			}
		}
		Alloc();
		for(int y=0;y<YLen;y++){
			const struct BMatrixBrightHL::BrightHLStruct	*d=GetConstantBrightness(y);
			if(d==NULL){
				memcpy(GetY(y),Buff[y],XLen*sizeof(struct BMatrixBrightHL::BrightHLStruct));
			}
		}
	}
}
