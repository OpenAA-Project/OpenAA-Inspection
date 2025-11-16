#include "XTypeDef.h"
#include <cmath>
#include "XMapBuffer.h"
#include "XPointer.h"
#include "swap.h"
#include "XGeneralFunc.h"

MapBufferBase::MapBufferBase(void)
{
	MapFormat	=_BitMap;
	Map=NULL;
	XByte=0;
	YLen=0;
}
MapBufferBase::MapBufferBase(int xbyte ,int ylen)
{
	MapFormat=_BitMap;
	XByte	=xbyte;
	YLen	=ylen;
	Map	=MakeMatrixBuff(XByte,YLen);
}
MapBufferBase::MapBufferBase(int xlen ,int ylen,EnumMapFormat e)
{
	MapFormat=e;

	if(MapFormat==_BitMap)
		XByte	=(xlen+7)/8;
	else if(MapFormat==_ByteMap)
		XByte	=xlen;
	else if(MapFormat==_WordMap)
		XByte	=2*xlen;
	else if(MapFormat==_DWordMap)
		XByte	=4*xlen;
	YLen	=ylen;
	Map	=MakeMatrixBuff(XByte,YLen);
}
MapBufferBase::MapBufferBase(BYTE **bitmap,int xbyte ,int ylen,EnumMapFormat e)
//delete bitmap in this instance
{
	MapFormat=e;
	XByte	=xbyte;
	YLen	=ylen;
	Map	=bitmap;
}

MapBufferBase::MapBufferBase(const MapBufferBase &src)
{
	MapFormat=src.MapFormat;
	XByte	=src.XByte;
	YLen	=src.YLen;
	Map		=MakeMatrixBuff(XByte,YLen);
}
MapBufferBase::~MapBufferBase(void)
{
	if(Map!=NULL){
		DeleteMatrixBuff(Map,YLen);
		Map=NULL;
	}
	XByte=0;
	YLen=0;
}

int	MapBufferBase::GetXLen(void)const 
{
	if(MapFormat==_BitMap)
		return XByte*8;	
	else
	if(MapFormat==_ByteMap)
		return XByte;	
	else
	if(MapFormat==_WordMap)
		return XByte/2;	
	else
	if(MapFormat==_DWordMap)
		return XByte/4;	
	return 0;
}

void	MapBufferBase::Copy(const MapBufferBase &src)
{
	if(XByte!=src.XByte || YLen!=src.YLen || MapFormat!=src.MapFormat){
		if(Map!=NULL){
			DeleteMatrixBuff(Map,YLen);
			Map=NULL;
		}
		XByte=src.XByte;
		YLen=src.YLen;
		Map=MakeMatrixBuff(XByte,YLen);
	}
	MapFormat=src.MapFormat;
	MatrixBuffCopy(Map,XByte,YLen
				, (const BYTE **)src.Map ,src.XByte ,src.YLen);
}

bool	MapBufferBase::CopyPartial(const MapBufferBase &Src ,int SrcX1 ,int SrcY1 ,int SrcX2 ,int SrcY2
									,int DstX1 ,int DstY1)
{
	if(MapFormat!=Src.MapFormat)
		return false;
	if(SrcX1<0)
		SrcX1=0;
	if(SrcY1<0)
		SrcY1=0;
	if(SrcX1>=Src.GetXLen()){
		return false;
	}
	if(SrcY1>=Src.GetYLen()){
		return false;
	}
	if(SrcX2>=Src.GetXLen()){
		SrcX2=Src.GetXLen();
	}
	if(SrcY2>=Src.GetYLen()){
		SrcY2=Src.GetYLen();
	}
	if(DstX1>=GetXLen()){
		return false;
	}
	if(DstY1>=GetYLen()){
		return false;
	}
	int	SYNumb=SrcY2-SrcY1;
	int	SXNumb=SrcX2-SrcX1;
	if(MapFormat==_BitMap){
		for(int y=0;y<SYNumb;y++){
			int	Y=DstY1+y;
			if(0<=Y && Y<GetYLen()){
				for(int x=0;x<SXNumb;x++){
					int	X=DstX1+x;
					if(0<=X && X<GetXLen()){
						if(Src.GetBit(SrcX1+x,SrcY1+y)==0){
							ClearBit(X,Y);
						}
						else{
							SetBit(X,Y);
						}
					}
				}
			}
		}
	}
	else
	if(MapFormat==_ByteMap){
		for(int y=0;y<SYNumb;y++){
			int	Y=DstY1+y;
			if(0<=Y && Y<GetYLen()){
				for(int x=0;x<SXNumb;x++){
					int	X=DstX1+x;
					if(0<=X && X<GetXLen()){
						SetByte(X,Y,Src.GetByte(SrcX1+x,SrcY1+y));
					}
				}
			}
		}
	}
	else
	if(MapFormat==_WordMap){
		for(int y=0;y<SYNumb;y++){
			int	Y=DstY1+y;
			if(0<=Y && Y<GetYLen()){
				for(int x=0;x<SXNumb;x++){
					int	X=DstX1+x;
					if(0<=X && X<GetXLen()){
						SetWord(X,Y,Src.GetWord(SrcX1+x,SrcY1+y));
					}
				}
			}
		}
	}
	else
	if(MapFormat==_DWordMap){
		for(int y=0;y<SYNumb;y++){
			int	Y=DstY1+y;
			if(0<=Y && Y<GetYLen()){
				for(int x=0;x<SXNumb;x++){
					int	X=DstX1+x;
					if(0<=X && X<GetXLen()){
						SetDWord(X,Y,Src.GetDWord(SrcX1+x,SrcY1+y));
					}
				}
			}
		}
	}
	else{
		return false;
	}
	return true;
}

MapBufferBase	&MapBufferBase::operator&=(const MapBufferBase &src)
{
	if(src.MapFormat==_BitMap){
		if(Map==NULL && src.Map!=NULL){
			XByte	=src.XByte;
			YLen	=src.YLen;
			MapFormat=_BitMap;
			Map	=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(Map ,0 ,XByte,YLen);
			return *this;
		}
		if(src.Map==NULL){
			return *this;
		}
		MatrixBuffAnd	(Map ,(const BYTE **)src.Map ,min(XByte,src.XByte) ,min(YLen,src.YLen));
	}
	return *this;
}
MapBufferBase	&MapBufferBase::operator|=(const MapBufferBase &src)
{
	if(src.MapFormat==_BitMap){
		if(Map==NULL && src.Map!=NULL){
			Copy(src);
			return *this;
		}
		if(src.Map==NULL){
			return *this;
		}
		MatrixBuffOr(Map ,(const BYTE **)src.Map ,min(XByte,src.XByte) ,min(YLen,src.YLen));
	}
	return *this;
}
MapBufferBase	&MapBufferBase::operator^=(const MapBufferBase &src)
{
	if(src.MapFormat==_BitMap){
		if(Map==NULL && src.Map!=NULL){
			XByte	=src.XByte;
			YLen	=src.YLen;
			MapFormat=_BitMap;
			Map	=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(Map ,0 ,XByte,YLen);
		}
		if(src.Map==NULL){
			return *this;
		}
		MatrixBuffXor	(Map ,(const BYTE **)src.Map ,min(XByte,src.XByte) ,min(YLen,src.YLen));
	}
	return *this;
}

void	MapBufferBase::Not(void)
{
	if(MapFormat==_BitMap){
		MatrixBuffNot	(Map,XByte ,YLen);
	}
}
void	MapBufferBase::AndNot(const MapBufferBase &src)
{
	if(src.MapFormat==_BitMap){
		if(Map==NULL && src.Map!=NULL){
			XByte	=src.XByte;
			YLen	=src.YLen;
			MapFormat=_BitMap;
			Map	=MakeMatrixBuff(XByte,YLen);
			MatrixBuffClear(Map ,0 ,XByte,YLen);
			return;
		}
		if(src.Map==NULL){
			return;
		}
		MatrixBuffNotAnd	(Map ,(const BYTE **)src.Map ,min(XByte,src.XByte) ,min(YLen,src.YLen));
	}
}
void	MapBufferBase::MoveFrom(MapBufferBase &src)
{
	if(Map!=NULL){
		DeleteMatrixBuff(Map,YLen);
		Map=NULL;
	}
	MapFormat=src.MapFormat;
	Map		=src.Map;
	XByte	=src.XByte;
	YLen	=src.YLen;
	src.Map		=NULL;
	src.XByte	=0;
	src.YLen	=0;
}

void	MapBufferBase::Set(BYTE **bitmap,int xbyte ,int ylen,EnumMapFormat e)
{
	if(Map!=NULL){
		DeleteMatrixBuff(Map,YLen);
		Map=NULL;
	}
	MapFormat=e;
	Map		=bitmap;
	XByte	=xbyte;
	YLen	=ylen;
}

void	MapBufferBase::SetXY(BYTE **bitmap,int xlen  ,int ylen ,EnumMapFormat e)
{
	if(Map!=NULL){
		DeleteMatrixBuff(Map,YLen);
		Map=NULL;
	}
	MapFormat=e;
	Map		=bitmap;

	if(MapFormat==_BitMap)
		XByte	=(xlen+7)/8;
	else if(MapFormat==_ByteMap)
		XByte	=xlen;
	else if(MapFormat==_WordMap)
		XByte	=2*xlen;
	else if(MapFormat==_DWordMap)
		XByte	=4*xlen;

	YLen	=ylen;
}

void	MapBufferBase::Alloc(int xbyte ,int ylen,EnumMapFormat e)
{
	if((XByte!=xbyte || YLen!=ylen) && Map!=NULL){
		DeleteMatrixBuff(Map,YLen);
		Map=NULL;
	}
	MapFormat=e;
	XByte	=xbyte;
	YLen	=ylen;
	if(Map==NULL){
		Map	=MakeMatrixBuff(XByte,YLen);
		MatrixBuffClear(Map ,0 ,XByte,YLen);
	}
}
bool	MapBufferBase::IsEmpty(void)
{
	if(XByte==0 || YLen==0)
		return true;
	for(int y=0;y<YLen;y++){
		BYTE	*m=Map[y];
		for(int x=0;x<XByte;x++){
			if(m[x]!=0){
				return false;
			}
		}
	}
	return true; 			
}

void	MapBufferBase::ClearAll(void)
{
	MatrixBuffClear(Map ,0 ,XByte ,YLen);
}
	
void	MapBufferBase::SetAll(void)
{
	MatrixBuffClear(Map ,0xFF ,XByte ,YLen);
}

bool	MapBufferBase::Save(QIODevice *f)
{
	if(::Save(f,XByte)==false){
		return false;
	}
	if(::Save(f,YLen)==false){
		return false;
	}
	BYTE	e=(BYTE)MapFormat;
	if(::Save(f,e)==false){
		return false;
	}
	for(int y=0;y<YLen;y++){
		if(f->write((const char *)(Map[y]),XByte)!=XByte){
			return false;
		}
	}
	return true;
}
bool	MapBufferBase::Load(QIODevice *f)
{
	int	iYLen;
	int	iXByte;

	if(::Load(f,iXByte)==false){
		return false;
	}
	if(::Load(f,iYLen)==false){
		return false;
	}
	BYTE	e;
	if(::Load(f,e)==false){
		return false;
	}
	MapFormat=(EnumMapFormat)e;

	Alloc(iXByte,iYLen,MapFormat);

	for(int y=0;y<YLen;y++){
		if(f->read((char *)(Map[y]),XByte)!=XByte){
			return false;
		}
	}
	return true;
}

MapBufferList::~MapBufferList(void)
{
	delete	MapPointer;
	MapPointer=NULL;
}

void	MapBufferListContainer::BindOr(MapBuffer &Map)
{
	MapBufferList	*m0=GetFirst();
	if(m0==NULL)
		return;
	MapBuffer	*m=m0->GetMapBuffer();
	if(m==NULL)
		return;

	Map.Alloc(m->GetXLen() ,m->GetYLen(),m->GetFormat());
	Map.Copy(*m);
	for(MapBufferList *t=m0->GetNext();t!=NULL;t=t->GetNext()){
		m=t->GetMapBuffer();
		if(m!=NULL){
			Map |= *m;
		}
	}
}

ConstMapBufferList::~ConstMapBufferList(void)
{
	delete	MapPointer;
	MapPointer=NULL;
}

void	ConstMapBufferListContainer::BindOr(ConstMapBuffer &Map)
{
	ConstMapBufferList	*m0=GetFirst();
	if(m0==NULL)
		return;
	ConstMapBuffer	*m=m0->GetMapBuffer();
	if(m==NULL)
		return;

	Map.Alloc(m->GetXLen() ,m->GetYLen(),m->GetFormat());
	Map.Copy(*m);
	for(ConstMapBufferList *t=m0->GetNext();t!=NULL;t=t->GetNext()){
		m=t->GetMapBuffer();
		if(m!=NULL){
			Map |= *m;
		}
	}
}

void	ConstMapBufferListContainer::BindOr(MapBuffer &Map)
{
	ConstMapBufferList	*m0=GetFirst();
	if(m0==NULL)
		return;
	ConstMapBuffer	*m=m0->GetMapBuffer();
	if(m==NULL)
		return;

	Map.Alloc(m->GetXLen() ,m->GetYLen(),m->GetFormat());
	Map.Copy(*m);
	for(ConstMapBufferList *t=m0->GetNext();t!=NULL;t=t->GetNext()){
		m=t->GetMapBuffer();
		if(m!=NULL){
			Map |= *m;
		}
	}
}
