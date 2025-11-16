/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XColorSpace.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "XTypeDef.h"
#include "XColorSpace.h"
#include "XPointer.h"
#include "XGeneralFunc.h"
#include "XMainSchemeMemory.h"
#define	_USE_MATH_DEFINES
#include <math.h>
#include <omp.h>
#include "swap.h"
//#include <sse2mmx.h>

NPListPack<ColorLogic>	ColorLogicWithTable::ColorLogicTable[256];
QReadWriteLock			ColorLogicWithTable::ColorLogicTableAccessor;
int						ColorLogicWithTable::ColorLogicTableCount=0;

bool	ColorSphere::Calc(BYTE r ,BYTE g ,BYTE b,int Mergin)
{
//	if(  ((int)((((short)r)-((short)qRed  (Center)))*(((short)r)-((short)qRed  (Center)))))
//		+((int)((((short)g)-((short)qGreen(Center)))*(((short)g)-((short)qGreen(Center)))))
//		+((int)((((short)b)-((short)qBlue (Center)))*(((short)b)-((short)qBlue (Center)))))<(Radius+Mergin)*(Radius+Mergin)){
//		return true;
//	}

	/*
	BYTE	aw[4];
	BYTE	bw[4];
	int		m[4];
	aw[0]=r;
	aw[1]=g;
	aw[2]=b;
	aw[3]=Radius;
	bw[0]=qRed  (Center);
	bw[1]=qGreen(Center);
	bw[2]=qBlue (Center);
	bw[3]=-Mergin;
	*/
	int	aw[4];
	int	m[4];
	aw[0]=r;
	aw[1]=g;
	aw[2]=b;
	aw[3]=Mergin;

	for(int i=0;i<4;i++){
		//m[i]=(((short)aw[i])-((short)bw[i]))*(((short)aw[i])-((short)bw[i]));
		m[i]=(aw[i]-CalcTable[i])*(aw[i]-CalcTable[i]);
	}

	if(m[0]+m[1]+m[2]<m[3]){
		return true;
	}

	return false;
}
bool	ColorSphere::Calc(int RGBM[4])
{
	int	m[4];
	/*
	for(int i=0;i<4;i++){
		m[i]=(RGBM[i]-CalcTable[i])*(RGBM[i]-CalcTable[i]);
	}

	if(m[0]+m[1]+m[2]<m[3]){
		return true;
	}
	*/
	/*
	static	int	MulTable[]={1,1,1,-1};
	for(int i=0;i<4;i++){
		m[i]=(RGBM[i]-CalcTable[i])*(RGBM[i]-CalcTable[i]);
	}
	for(int i=0;i<4;i++){
		m[i]=m[i]*MulTable[i];
	}
	int	s=0;
	for(int i=0;i<4;i++){
		s+=m[i];
	}
	if(s<0){
		return true;
	}
	*/
	for(int i=0;i<4;i++){
		m[i]=(RGBM[i]-CalcTable[i])*(RGBM[i]-CalcTable[i]);
	}
	int	s=0;
	for(int i=0;i<3;i++){
		s+=m[i];
	}
	if(s<m[3]){
		return true;
	}

	return false;
}

//#define	NO_INLINE_ASSEMBLER

BYTE	ColorSphere::Calc8(BYTE *r ,BYTE *g ,BYTE *b,int Mergin)
{
#if	defined(NO_INLINE_ASSEMBLER) | !defined(WIN64)
	int	m[8];
	int	rr=(Radius+Mergin)*(Radius+Mergin);
	for(int i=0;i<8;i++){
		m[i]=(r[i]-CalcTable[0])*(r[i]-CalcTable[0]);
	}
	for(int i=0;i<8;i++){
		m[i]+=(g[i]-CalcTable[1])*(g[i]-CalcTable[1]);
	}
	for(int i=0;i<8;i++){
		m[i]+=(b[i]-CalcTable[2])*(b[i]-CalcTable[2]);
	}
	for(int i=0;i<8;i++){
		m[i]-=rr;
	}
	BYTE	ret=0;
	for(int i=0;i<8;i++){
		if(m[i]<0){
			ret |= 0x80>>i;
		}
	}
	return ret;
#else
	short	*TableR=CalcTable16bitR;
	short	*TableG=CalcTable16bitG;
	short	*TableB=CalcTable16bitB;
	static	BYTE	ShuffleTable[]={	7,6,5,4,3,2,1,0,0x80,0x80,0x80,0x80,0x80,0x80,0x80,0x80	};

	int	rr=(Radius+Mergin)*(Radius+Mergin);
	BYTE	bRet;
	__asm{
		push		rax
		push		rbx
		mov			rax,r
		movd		xmm1,qword ptr [rax]	//xmm1=r0,r1,r2,r3,r4,r5,r6,r7,0,0,0,0,0,0,0,0
		pxor		xmm0,xmm0
		mov			rbx,g
		punpcklbw	xmm1,xmm0				//xmm1=r0,0,r1,0,r2,0,r3,0,r4,0,r5,0,r6,0,r7,0
		movd		xmm2,qword ptr [rbx]	//xmm2=g0,g1,g2,g3,g4,g5,g6,g7,0,0,0,0,0,0,0,0
		mov			rax,b
		mov			rbx,TableR
		movd		xmm3,qword ptr [rax]	//xmm3=b0,b1,b2,b3,b4,b5,b6,b7,0,0,0,0,0,0,0,0
		psubw		xmm1,[rbx]				//xmm1=r0-Cr,r1-Cr,r2-Cr,r3-Cr,r4-Cr,r5-Cr,r6-Cr,r7-Cr
		punpcklbw	xmm2,xmm0				//xmm2=g0,0,g1,0,g2,0,g3,0,g4,0,g5,0,g6,0,g7,0
		punpcklbw	xmm3,xmm0				//xmm3=b0,0,b1,0,b2,0,b3,0,b4,0,b5,0,b6,0,b7,0
		mov			rax,TableG
		mov			rbx,TableB
		psubw		xmm2,[rax]				//xmm2=g0-Cg,g1-Cg,g2-Cg,g3-Cg,g4-Cg,g5-Cg,g6-Cg,g7-Cg
		psubw		xmm3,[rbx]				//xmm3=b0-Cb,b1-Cb,b2-Cb,b3-Cb,b4-Cb,b5-Cb,b6-Cb,b7-Cb
		movdqu		xmm4,xmm1				//xmm4=xmm1=r0-Cr,r1-Cr,r2-Cr,r3-Cr,r4-Cr,r5-Cr,r6-Cr,r7-Cr
		punpckhwd	xmm1,xmm2				//xmm1=r4-Cr,g4-Cg,r5-Cr,g5-Cg,r6-Cr,g6-Cg,r7-Cr,g7-Cg
		punpcklwd	xmm4,xmm2				//xmm4=r0-Cr,g0-Cg,r1-Cr,g1-Cg,r2-Cr,g2-Cg,r3-Cr,g3-Cg

		pmaddwd		xmm4,xmm4				//xmm4=(r0-Cr)*(r0-Cr)+(g0-Cg)*(g0-Cg),(r1-Cr)*(r1-Cr)+(g1-Cg)*(g1-Cg),(r2-Cr)*(r2-Cr)+(g2-Cg)*(g2-Cg),(r3-Cr)*(r3-Cr)+(g3-Cg)*(g3-Cg)
		pmaddwd		xmm1,xmm1				//xmm1=(r4-Cr)*(r4-Cr)+(g4-Cg)*(g4-Cg),(r5-Cr)*(r5-Cr)+(g5-Cg)*(g5-Cg),(r6-Cr)*(r6-Cr)+(g6-Cg)*(g6-Cg),(r7-Cr)*(r7-Cr)+(g7-Cg)*(g7-Cg)
		PMULLW		xmm3,xmm3				//xmm3=(b0-Cb)*(b0-Cb),(b1-Cb)*(b1-Cb),(b2-Cb)*(b2-Cb),(b3-Cb)*(b3-Cb),(b4-Cb)*(b4-Cb),(b5-Cb)*(b5-Cb),(b6-Cb)*(b6-Cb),(b7-Cb)*(b7-Cb)
		movd		xmm2,rr					//xmm2=rr,0,0,0
		movdqu		xmm5,xmm3				//xmm5=xmm3
		punpckhwd	xmm3,xmm0				//xmm3=(b4-Cb)*(b4-Cb),(b5-Cb)*(b5-Cb),(b6-Cb)*(b6-Cb),(b7-Cb)*(b7-Cb)
		punpcklwd	xmm5,xmm0				//xmm5=(b0-Cb)*(b0-Cb),(b1-Cb)*(b1-Cb),(b2-Cb)*(b2-Cb),(b3-Cb)*(b3-Cb)
		PUNPCKLDQ	xmm2,xmm2				//xmm2=rr,rr,0,0
		paddd		xmm1,xmm3				//xmm1=(r4-Cr)*(r4-Cr)+(g4-Cg)*(g4-Cg)+(b4-Cb)*(b4-Cb),(r5-Cr)*(r5-Cr)+(g5-Cg)*(g5-Cg)+(b5-Cb)*(b5-Cb),(r6-Cr)*(r6-Cr)+(g6-Cg)*(g6-Cg)+(b6-Cb)*(b6-Cb),(r7-Cr)*(r7-Cr)+(g7-Cg)*(g7-Cg)+(b7-Cb)*(b7-Cb)
		PUNPCKLQDQ	xmm2,xmm2				//xmm2=rr,rr,rr,rr
		paddd		xmm4,xmm5				//xmm4=(r0-Cr)*(r0-Cr)+(g0-Cg)*(g0-Cg)+(b0-Cb)*(b0-Cb),(r1-Cr)*(r1-Cr)+(g1-Cg)*(g1-Cg)+(b1-Cb)*(b1-Cb),(r2-Cr)*(r2-Cr)+(g2-Cg)*(g2-Cg)+(b2-Cb)*(b2-Cb),(r3-Cr)*(r3-Cr)+(g3-Cg)*(g3-Cg)+(b3-Cb)*(b3-Cb)

		PCMPGTD		xmm4,xmm2				//中心と(r,g,b)間の距離の方が(Radius+Mergin)より大きいとき、０
											//xmm4=res0,res1,res2,res3(DWORD)
		PCMPGTD		xmm1,xmm2				//xmm1=res4,res5,res6,res7(DWORD)
		PACKSSDW	xmm4,xmm1				//xmm4=res0,res1,res2,res3,res4,res5,res6,res7(WORD)
		PACKSSWB	xmm4,xmm0				//xmm4=res0,res1,res2,res3,res4,res5,res6,res7,0,0,0,0,0,0,0,0(BYTE)
		/*	SSSE3
		PSHUFB		xmm4,ShuffleTable		//順番の入れ替え
											//xmm4=res7,res6,res5,res4,res3,res2,res1,res0,0,0,0,0,0,0,0,0(BYTE)
		PMOVMSKB	eax,xmm4				//各バイトのBit7を取り出す
		not			al						//反転させる
		mov			bRet,al
		*/
		PMOVMSKB	eax,xmm4				//各バイトのBit7を取り出す
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		shl			al,1
		rcr			ah,1
		not			ah						//反転させる
		mov			bRet,ah

		pop			rbx
		pop			rax
	}

	return bRet;
#endif
}

PreciseColor::PreciseColor(double R, double G ,double B)
{	
	Red=R;
	Green=G;
	Blue=B;
}

PreciseColor& PreciseColor::operator=(const PreciseColor& src)
{
	Red = src.Red;
	Green = src.Green;
	Blue = src.Blue;
	return *this;
}

double	PreciseColor::GetRed(void)
{
	return Red.GetFloat();
}
double	PreciseColor::GetGreen(void)
{
	return Green.GetFloat();
}
double	PreciseColor::GetBlue(void)
{
	return Blue.GetFloat();
}

bool	PreciseColor::Save(QIODevice *f)
{
	if(Red	.Save(f)==false)	return false;
	if(Green.Save(f)==false)	return false;
	if(Blue	.Save(f)==false)	return false;
	return true;
}
bool	PreciseColor::Load(QIODevice *f)
{
	if(Red	.Load(f)==false)	return false;
	if(Green.Load(f)==false)	return false;
	if(Blue	.Load(f)==false)	return false;
	return true;
}
PreciseColorList::PreciseColorList(const PreciseColor &src)
{
	Red=src.Red;
	Green=src.Green;
	Blue=src.Blue;
}

PreciseColorList& PreciseColorList::operator=(const PreciseColorList& src)
{
	PreciseColor::operator=(src);
	return *this;
}
bool	PreciseColorList::Save(QIODevice *f)
{
	if(PreciseColor::Save(f)==false)
		return false;
	return true;
}
bool	PreciseColorList::Load(QIODevice *f)
{
	if(PreciseColor::Load(f)==false)
		return false;
	return true;
}

PreciseColorListConatiner::PreciseColorListConatiner(const PreciseColorListConatiner &src)
{
	for(PreciseColorList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		PreciseColorList	*d=Create();
		*d=*s;
		AppendList(d);
	}
}

PreciseColorListConatiner	&PreciseColorListConatiner::operator=(const PreciseColorListConatiner &src)
{
	RemoveAll();
	for(PreciseColorList *s=src.GetFirst();s!=NULL;s=s->GetNext()){
		PreciseColorList	*d=Create();
		*d=*s;
		AppendList(d);
	}
	return *this;
}

bool	ColorSphere::Calc(double r ,double g ,double b,int Mergin)
{
	if((((int)r)-qRed(Center))*(((int)r)-qRed(Center)) 
	 + (((int)g)-qGreen(Center))*(((int)g)-qGreen(Center))
	 + (((int)b)-qBlue(Center))*(((int)b)-qBlue(Center))<(Radius+Mergin)*(Radius+Mergin)){
		return true;
	}
	return false;
}


ColorPlane::ColorPlane(const ColorPlane &src)
{
	wr = src.wr;
	wg = src.wg;
	wb = src.wb;
	wc = src.wc;
}

bool	ColorPlane::operator==(ColorPlane &src)	const
{
	if(wr==src.wr && wg==src.wg && wb==src.wb && wc==src.wc){
		return true;
	}
	return false;
}

bool	ColorPlane::Save(QIODevice *f)
{
	if(::Save(f,wr)==false){
		return false;
	}
	if(::Save(f,wg)==false){
		return false;
	}
	if(::Save(f,wb)==false){
		return false;
	}
	if(::Save(f,wc)==false){
		return false;
	}
	return true;
}
bool	ColorPlane::Load(QIODevice *f)
{
	if(::Load(f,wr)==false){
		return false;
	}
	if(::Load(f,wg)==false){
		return false;
	}
	if(::Load(f,wb)==false){
		return false;
	}
	if(::Load(f,wc)==false){
		return false;
	}
	return true;
}

ColorPlane	&ColorPlane::operator=(ColorPlane &src)
{
	wr=src.wr;
	wg=src.wg;
	wb=src.wb;
	wc=src.wc;
	return *this;
}

ColorPlane	&ColorPlane::operator=(const ColorPlane &src)
{
	wr=src.wr;
	wg=src.wg;
	wb=src.wb;
	wc=src.wc;
	return *this;
}
void	ColorPlane::Multiply(double m)
{
	wc*=m;
}

void	ColorPlane::ShiftColor(int dR ,int dG ,int dB)
{
}


//=======================================================================
ColorCube::ColorCube(void)
{
	Planes		=NULL;
	PlaneCounts	=0;
}
ColorCube::ColorCube(const ColorCube &src)
{
	if (PlaneCounts > src.PlaneCounts) {
		PlaneCounts = src.PlaneCounts;
		if (Planes != NULL) {
			delete[]Planes;
		}
		Planes = new ColorPlane[PlaneCounts];
	}
	for (int i = 0; i < PlaneCounts; i++) {
		Planes[i] = src.Planes[i];
	}
}

ColorCube::~ColorCube(void)
{
	if(Planes!=NULL)
		delete	[]Planes;
	Planes=NULL;
	PlaneCounts	=0;
}

bool	ColorCube::operator==(const ColorSpace &src)	const
{
	if(GetClassID()!=src.GetClassID()){
		return false;
	}
	const ColorCube	*s=dynamic_cast<const ColorCube *>(&src);
	if(s!=NULL){
		if(PlaneCounts!=s->PlaneCounts){
			return false;
		}
		for(int i=0;i<PlaneCounts;i++){
			if(Planes[i]==s->Planes[i]){
				continue;
			}
			return false;
		}
		return true;
	}
	return false;
}

bool	ColorCube::Save(QIODevice *f)
{
	if(::Save(f,PlaneCounts)==false){
		return false;
	}
	for(int i=0;i<PlaneCounts;i++){
		if(Planes[i].Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ColorCube::Load(QIODevice *f)
{
	int32	iPlaneCounts;
	if(::Load(f,iPlaneCounts)==false){
		return false;
	}
	if(iPlaneCounts!=PlaneCounts){
		PlaneCounts=iPlaneCounts;
		if(Planes!=NULL){
			delete	[]Planes;
		}
		Planes=new ColorPlane[PlaneCounts];
	}
	for(int i=0;i<PlaneCounts;i++){
		if(Planes[i].Load(f)==false){
			return false;
		}
	}
	return true;
}

bool	ColorCube::Calc(BYTE r ,BYTE g ,BYTE b,int Mergin)
{
	for(int i=0;i<PlaneCounts;i++){
		if(Planes[i].Calc(r,g,b)==false){
			return false;
		}
	}
	return true;
}
bool	ColorCube::Calc(int RGBM[4])
{
	return Calc((BYTE)RGBM[0],(BYTE)RGBM[1],(BYTE)RGBM[2],(BYTE)RGBM[3]);
}

void	ColorCube::Multiply(double m)
{
	for(int i=0;i<PlaneCounts;i++){
		Planes[i].Multiply(m);
	}
}
void	ColorCube::ShiftColor(int dR ,int dG ,int dB)
{
	for(int i=0;i<PlaneCounts;i++){
		Planes[i].ShiftColor(dR ,dG ,dB);
	}
}


bool	ColorCube::Create(RGBStock &Inside ,RGBStock &Outside)
{
	return true;
}


ColorCube	&ColorCube::operator=(const ColorCube &src)
{
	if(this!=&src){
		if(PlaneCounts>src.PlaneCounts){
			PlaneCounts=src.PlaneCounts;
			if(Planes!=NULL){
				delete	[]Planes;
			}
			Planes=new ColorPlane[PlaneCounts];
		}
		for(int i=0;i<PlaneCounts;i++){
			Planes[i]=src.Planes[i];
		}
	}
	return *this;
}

//===============================================================

#define	BufferSize_ColorCubeBit	((256/8)*256*256)

ColorCubeBit::ColorCubeBit(void)
{
	CubeMap=new BYTE[BufferSize_ColorCubeBit];
	Clear();
}
ColorCubeBit::ColorCubeBit(const ColorCubeBit &src)
{
	CubeMap=new BYTE[BufferSize_ColorCubeBit];
	memcpy(CubeMap,src.CubeMap,BufferSize_ColorCubeBit);
}
ColorCubeBit::~ColorCubeBit(void)
{
	delete	[]CubeMap;
	CubeMap=NULL;
}

bool	ColorCubeBit::Save(QIODevice *f)
{
	if(f->write((const char *)CubeMap,BufferSize_ColorCubeBit)!=BufferSize_ColorCubeBit){
		return false;
	}
	if(::Save(f,Active)==false){
		return false;
	}
	return true;
}
bool	ColorCubeBit::Load(QIODevice *f)
{
	if(f->read((char *)CubeMap,BufferSize_ColorCubeBit)!=BufferSize_ColorCubeBit){
		return false;
	}
	if(::Load(f,Active)==false){
		return false;
	}
	return true;
}

bool	ColorCubeBit::CalcOnMask(BYTE r ,BYTE g ,BYTE b)
{
	int	L=(r<<16)+(g<<8)+b;
	if((CubeMap[L>>3]&((0x01)<<(L&0x07)))!=0){
		return true;
	}
	return false;
}

ColorCubeBit	&ColorCubeBit::operator=(const ColorCubeBit &src)
{
	memcpy(CubeMap,src.CubeMap,BufferSize_ColorCubeBit);
	Active	=src.Active;
	return *this;
}

void	ColorCubeBit::Clear(void)
{
	memset(CubeMap,0,BufferSize_ColorCubeBit);
	Active=false;
}
void	ColorCubeBit::AppendMask(BYTE r ,BYTE g ,BYTE b,int Mergin)
{
	int	MinR=max(0  ,r-Mergin);
	int	MaxR=min(255,r+Mergin);
	int	MinG=max(0  ,g-Mergin);
	int	MaxG=min(255,g+Mergin);
	int	MinB=max(0  ,b-Mergin);
	int	MaxB=min(255,b+Mergin);

	for(int wr=MinR;wr<=MaxR;wr++){
		int	Lr=wr<<16;
		for(int wg=MinG;wg<=MaxG;wg++){
			int	Lg=Lr+(wg<<8);
			for(int wb=MinB;wb<=MaxB;wb++){
				int	Lb=Lg+wb;
				CubeMap[Lb>>3] |= 0x01<<(Lb&0x07);
			}
		}
	}
	Active=true;
}
//===============================================================

ColorSphere::ColorSphere(const ColorSphere &src)
{
	operator=(src);
}
ColorSphere::~ColorSphere(void)
{
}

void	ColorSphere::Set(int r ,int g ,int b, int radius)
{
	Center=qRgb(r,g,b);
	Radius=radius;
	CreateCalcTable();
}

void	ColorSphere::CreateCalcTable(void)
{
	CalcTable[0]=qRed  (Center);
	CalcTable[1]=qGreen(Center);
	CalcTable[2]=qBlue (Center);
	CalcTable[3]=-Radius;

	for(int i=0;i<8;i++){
		CalcTable16bitR[i]=qRed  (Center);
		CalcTable16bitG[i]=qGreen(Center);
		CalcTable16bitB[i]=qBlue (Center);
	}
}

void	ColorSphere::Multiply(double m)
{
	Center=qRgb( Clipping((int)(qRed(Center)*m),0,255) 
				,Clipping((int)(qGreen(Center)*m),0,255) 
				,Clipping((int)(qBlue(Center)*m),0,255));
	Radius*=m;
	CreateCalcTable();
}
void	ColorSphere::ShiftColor(int dR ,int dG ,int dB)
{
	Center=qRgb( Clipping((int)(qRed(Center)+dR),0,255) 
				,Clipping((int)(qGreen(Center)+dG),0,255) 
				,Clipping((int)(qBlue(Center)+dB),0,255));
	CreateCalcTable();
}

bool	ColorSphere::operator==(const ColorSpace &src)	const
{
	if(GetClassID()!=src.GetClassID()){
		return false;
	}
	const ColorSphere	*s=dynamic_cast<const ColorSphere *>(&src);
	if(s!=NULL){
		if(Center==s->Center && Radius==s->Radius){
			return true;
		}
	}
	return false;
}

bool	ColorSphere::Save(QIODevice *f)
{
	if(::Save(f,Center)==false){
		return false;
	}
	if(::Save(f,Radius)==false){
		return false;
	}
	return true;
}
bool	ColorSphere::Load(QIODevice *f)
{
	if(::Load(f,Center)==false){
		return false;
	}
	if(::Load(f,Radius)==false){
		return false;
	}
	CreateCalcTable();
	return true;
}

bool	ColorSphere::Create(RGBStock &Inside)
{
	double r ,g ,b;
	Inside.GetCenter(r ,g ,b);
	double	MaxR=0;
	for(RGBSample *c=Inside.GetFirst();c!=NULL;c=c->GetNext()){
		double R=(r-c->GetRed())*(r-c->GetRed()) + (g-c->GetGreen())*(g-c->GetGreen())+(b-c->GetBlue())*(b-c->GetBlue())+c->GetWeight()*c->GetWeight();
		if(R>MaxR){
			MaxR=R;
		}
	}
	Radius=ceil(sqrt(MaxR));
	Center=qRgb(r,g,b);
	CreateCalcTable();
	return true;
}
double	ColorSphere::GetLength(BYTE r ,BYTE g ,BYTE b)
{
	double R=(r-qRed(Center))*(r-qRed(Center)) + (g-qGreen(Center))*(g-qGreen(Center))+(b-qBlue(Center))*(b-qBlue(Center));
	return sqrt(R);
}

ColorSphere	&ColorSphere::operator=(const ColorSphere &src)
{
	Center	=src.Center;
	Radius	=src.Radius;
	CreateCalcTable();
	return *this;
}
void	ColorSphere::AddMergin(int mergin)
{
	int	n=Radius;
	n+=mergin;
	if(n<0){
		n=0;
	}
	Radius=n;
	CreateCalcTable();
}
void	ColorSphere::GetMonoColorRange(int &ColL, int &ColH)
{
	ColL=qRed(Center)-Radius;
	ColH=qRed(Center)+Radius;
}

//--------------------------------------------------
void	ColorBox::Set(int colRL,int colRH
					 ,int colGL,int colGH
					 ,int colBL,int colBH)
{
	ColRL=colRL;
	ColRH=colRH;
	ColGL=colGL;
	ColGH=colGH;
	ColBL=colBL;
	ColBH=colBH;
}
bool	ColorBox::operator==(const ColorSpace &src)	const
{
	const ColorBox	*s=dynamic_cast<const ColorBox *>(&src);
	if(s!=NULL){
		if(ColRL==s->ColRL
		&& ColRH==s->ColRH
		&& ColGL==s->ColGL
		&& ColGH==s->ColGH
		&& ColBL==s->ColBL
		&& ColBH==s->ColBH){
			return true;
		}
	}
	return false;
}
ColorBox &ColorBox::operator=(const ColorSpace &src)
{
	const ColorBox	*s=dynamic_cast<const ColorBox *>(&src);
	if(s!=NULL){
		ColRL=s->ColRL;
		ColRH=s->ColRH;
		ColGL=s->ColGL;
		ColGH=s->ColGH;
		ColBL=s->ColBL;
		ColBH=s->ColBH;
	}
	return *this;
}
bool	ColorBox::Save(QIODevice *f)
{
	if(::Save(f,ColRL)==false){
		return false;
	}
	if(::Save(f,ColRH)==false){
		return false;
	}
	if(::Save(f,ColGL)==false){
		return false;
	}
	if(::Save(f,ColGH)==false){
		return false;
	}
	if(::Save(f,ColBL)==false){
		return false;
	}
	if(::Save(f,ColBH)==false){
		return false;
	}
	return true;
}
bool	ColorBox::Load(QIODevice *f)
{
	if(::Load(f,ColRL)==false){
		return false;
	}
	if(::Load(f,ColRH)==false){
		return false;
	}
	if(::Load(f,ColGL)==false){
		return false;
	}
	if(::Load(f,ColGH)==false){
		return false;
	}
	if(::Load(f,ColBL)==false){
		return false;
	}
	if(::Load(f,ColBH)==false){
		return false;
	}
	return true;
}
bool	ColorBox::Calc(BYTE r		,BYTE g		,BYTE b ,int Mergin)
{
	if((ColRL-Mergin)<=(int)r && (int)r<=(ColRH+Mergin)
	&& (ColGL-Mergin)<=(int)g && (int)g<=(ColGH+Mergin)
	&& (ColBL-Mergin)<=(int)b && (int)b<=(ColBH+Mergin)){
		return true;
	}
	return false;
}
bool	ColorBox::Calc(double	r	,double g	,double b ,int Mergin)
{
	if((ColRL-Mergin)<=r && r<=(ColRH+Mergin)
	&& (ColGL-Mergin)<=g && g<=(ColGH+Mergin)
	&& (ColBL-Mergin)<=b && b<=(ColBH+Mergin)){
		return true;
	}
	return false;
}
bool	ColorBox::Calc(int RGBM[4])
{
	return Calc((BYTE)RGBM[0],(BYTE)RGBM[1],(BYTE)RGBM[2],RGBM[3]);
}
BYTE	ColorBox::Calc8(BYTE *r ,BYTE *g ,BYTE   *b,int Mergin)
{
	BYTE	Ret=0;
	if(Calc(*(r+0),*(g+0),*(b+0),Mergin)==true){
		Ret |= 0x80;
	}
	if(Calc(*(r+1),*(g+1),*(b+1),Mergin)==true){
		Ret |= 0x40;
	}
	if(Calc(*(r+2),*(g+2),*(b+2),Mergin)==true){
		Ret |= 0x20;
	}
	if(Calc(*(r+3),*(g+3),*(b+3),Mergin)==true){
		Ret |= 0x10;
	}
	if(Calc(*(r+4),*(g+4),*(b+4),Mergin)==true){
		Ret |= 0x08;
	}
	if(Calc(*(r+5),*(g+5),*(b+5),Mergin)==true){
		Ret |= 0x04;
	}
	if(Calc(*(r+6),*(g+6),*(b+6),Mergin)==true){
		Ret |= 0x02;
	}
	if(Calc(*(r+7),*(g+7),*(b+7),Mergin)==true){
		Ret |= 0x01;
	}
	return Ret;
}
double	ColorBox::GetLength(BYTE r ,BYTE g ,BYTE b)
{
	double	R=(ColRL+ColRH)/2.0-(int)r;
	double	G=(ColGL+ColGH)/2.0-(int)g;
	double	B=(ColBL+ColBH)/2.0-(int)b;
	return sqrt(R*R+G*G+B*B);
}
void	ColorBox::Multiply(double m)
{
	ColRL *=m;
	ColRH *=m;
	ColGL *=m;
	ColGH *=m;
	ColBL *=m;
	ColBH *=m;
}
void	ColorBox::ShiftColor(int dR ,int dG ,int dB)
{
	ColRL +=dR;
	ColRH +=dR;
	ColGL +=dG;
	ColGH +=dG;
	ColBL +=dB;
	ColBH +=dB;
}
void	ColorBox::AddMergin(int mergin)
{
	ColRL -= mergin;
	ColRH += mergin;
	ColGL -= mergin;
	ColGH += mergin;
	ColBL -= mergin;
	ColBH += mergin;
}
void	ColorBox::MakeOrTable(BYTE *Table, int Mergin)
{}
void	ColorBox::MakeAndTable(BYTE *Table, int Mergin)
{}
void	ColorBox::GetMonoColorRange(int &ColL, int &ColH)
{
	ColL=ColRL;
	ColH=ColRH;
}

//--------------------------------------------------

ColorLogic::ColorLogic(ColorLogic &src)
{
	operator=(src);
}
ColorLogic::ColorLogic(const ColorLogic &src)
{
	operator=((ColorLogic &)src);
}
bool	ColorLogic::Calc(BYTE	r ,BYTE	  g ,BYTE   b,int Mergin)
{
	int	RGBM[4];
	RGBM[0]=r;
	RGBM[1]=g;
	RGBM[2]=b;
	RGBM[3]=Mergin;

	for(ColorSpace *bs=Base.GetFirst();bs!=NULL;bs=bs->GetNext()){
		if(bs->Calc(RGBM)==true){
			goto	PNext;
		}
	}
	return false;
PNext:;
	for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->Calc(RGBM)==true){
			return false;
		}
	}
	return true;
}
bool	ColorLogic::Calc(double	r ,double g ,double	b,int Mergin)
{
	for(ColorSpace *bs=Base.GetFirst();bs!=NULL;bs=bs->GetNext()){
		if(bs->Calc(r,g,b,Mergin)==true){
			goto	PNext;
		}
	}
	return false;
PNext:;
	for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		if(e->Calc(r,g,b,Mergin)==true){
			return false;
		}
	}
	return true;
}

BYTE	ColorLogic::Calc8(BYTE *r ,BYTE *g ,BYTE *b,int Mergin)
{
	BYTE	m=0;
	BYTE	n=0;
	for(ColorSpace *bs=Base.GetFirst();bs!=NULL;bs=bs->GetNext()){
		m|=bs->Calc8(r,g,b,Mergin);
	}
	for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		n|=e->Calc8(r,g,b,Mergin);
	}
	return m & (~n);
}

bool	ColorLogic::Save(QIODevice *f)
{
	int32	N;
	N=Base.GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(ColorSpace *b=Base.GetFirst();b!=NULL;b=b->GetNext()){
		int32	id=b->GetClassID();
		if(::Save(f,id)==false){
			return false;
		}
		if(b->Save(f)==false){
			return false;
		}
	}
	N=Eliminated.GetNumber();
	if(::Save(f,N)==false)
		return false;
	for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		int32	id=e->GetClassID();
		if(::Save(f,id)==false){
			return false;
		}
		if(e->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	ColorLogic::Load(QIODevice *f)
{
	int32	N;
	Base.RemoveAll();
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		int32	id;
		if(::Load(f,id)==false){
			return false;
		}
		ColorSpace *b=ColorSpace::GetNew(id);
		if(b==NULL){
			return false;
		}
		if(b->Load(f)==false){
			return false;
		}
		Base.AppendList(b);
	}
	Eliminated.RemoveAll();
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		int32	id;
		if(::Load(f,id)==false){
			return false;
		}
		ColorSpace *e=ColorSpace::GetNew(id);
		if(e==NULL){
			return false;
		}
		if(e->Load(f)==false){
			return false;
		}
		Eliminated.AppendList(e);
	}
	return true;
}

ColorLogic	&ColorLogic::operator=(const ColorLogic &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	((ColorLogic *)&src)->Save(&Buff);
	Buff.seek(0);
	Load(&Buff);

	return *this;
}
ColorLogic	&ColorLogic::operator=(ColorLogic &src)
{
	QBuffer	Buff;
	Buff.open(QIODevice::ReadWrite);
	src.Save(&Buff);
	Buff.seek(0);
	Load(&Buff);

	return *this;
}

void	ColorLogic::ClearBase(void)
{
	Base.RemoveAll();
}
void	ColorLogic::ClearEliminate(void)
{
	Eliminated.RemoveAll();
}
void	ColorLogic::ClearAll(void)
{
	ClearBase();
	ClearEliminate();
}

void	ColorLogic::Eliminate(ColorLogic &src ,int AdditionalMergin)
{
	for(ColorSpace *b=src.Base.GetFirst();b!=NULL;b=b->GetNext()){
		int	id=b->GetClassID();
		ColorSpace	*s=ColorSpace::GetNew(id);
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		b->Save(&Buff);
		Buff.seek(0);
		s->Load(&Buff);
		s->AddMergin(AdditionalMergin);
		Eliminated.AppendList(s);
	}
}

void	ColorLogic::Add(ColorLogic &src ,int AdditionalMergin)
{
	for(ColorSpace *b=src.Base.GetFirst();b!=NULL;b=b->GetNext()){
		int	id=b->GetClassID();
		ColorSpace	*s=ColorSpace::GetNew(id);
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		b->Save(&Buff);
		Buff.seek(0);
		s->Load(&Buff);
		s->AddMergin(AdditionalMergin);
		Base.AppendList(s);
	}
	for(ColorSpace *e=src.Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		int	id=e->GetClassID();
		ColorSpace	*s=ColorSpace::GetNew(id);
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		e->Save(&Buff);
		Buff.seek(0);
		s->Load(&Buff);
		s->AddMergin(AdditionalMergin);
		Eliminated.AppendList(s);
	}

}

void	ColorLogic::Eliminame(QRgb src ,int Mergin)
{
	ColorSphere	*s=new ColorSphere(src,Mergin);
	Eliminated.AppendList(s);
}
void	ColorLogic::Add(ColorSpace *src)
{
	Base.AppendList(src);
}
void	ColorLogic::Add(QRgb src ,int Mergin)
{
	ColorSphere	*s=new ColorSphere(src,Mergin);
	Base.AppendList(s);
}

void	ColorLogic::Multiply(double m)
{
	for(ColorSpace *b=Base.GetFirst();b!=NULL;b=b->GetNext()){
		b->Multiply(m);
	}
	for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		e->Multiply(m);
	}
}

bool	ColorLogic::IsEmpty(void)	const
{
	if(Base.GetFirst()!=NULL){
		return false;
	}
	if(Eliminated.GetFirst()!=NULL){
		return false;
	}
	return true;
}

void	ColorLogic::ShiftColor(int dR ,int dG ,int dB)
{
	for(ColorSpace *b=Base.GetFirst();b!=NULL;b=b->GetNext()){
		b->ShiftColor(dR ,dG ,dB);
	}
	for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
		e->ShiftColor(dR ,dG ,dB);
	}
}

void	ColorLogic::AddMerginInBases(int mergin)
{
	for(ColorSpace *b=Base.GetFirst();b!=NULL;b=b->GetNext()){
		b->AddMergin(mergin);
	}
}

void	ColorLogic::AddMerginInEliminated(int mergin)
{
	for(ColorSpace *b=Eliminated.GetFirst();b!=NULL;b=b->GetNext()){
		b->AddMergin(mergin);
	}
}


#define	Clip0(n)	((n)>=0?(n):0)
void	ColorSphere::MakeOrTable(BYTE *Table, int Mergin)
{
	int	rs=max(0,(Clip0(qRed  (Center)-(Radius+Mergin))));
	int	gs=max(0,(Clip0(qGreen(Center)-(Radius+Mergin))));
	int	bs=max(0,(Clip0(qBlue (Center)-(Radius+Mergin))));
	int	re=min(256,(qRed  (Center)+(Radius+Mergin)));
	int	ge=min(256,(qGreen(Center)+(Radius+Mergin)));
	int	be=min(256,(qBlue (Center)+(Radius+Mergin)));
	int	gn=ge-gs;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int gi=0;gi<gn;gi++){
			int	g=gi+gs;
			for(int r=rs;r<re;r++){
				for(int b=bs;b<be;b++){
					if(Calc((BYTE)r ,(BYTE)g ,(BYTE)b ,Mergin)==false){
						Table[(r>>3)+(g<<5)+(b<<13)]|=1<<(r&7);
					}
				}
			}
		}
	}
}

void	ColorSphere::MakeAndTable(BYTE *Table,int Mergin)
{
	int	rs=max(0,(Clip0(qRed  (Center)-(Radius+Mergin))));
	int	gs=max(0,(Clip0(qGreen(Center)-(Radius+Mergin))));
	int	bs=max(0,(Clip0(qBlue (Center)-(Radius+Mergin))));
	int	re=min(256,(qRed  (Center)+(Radius+Mergin)));
	int	ge=min(256,(qGreen(Center)+(Radius+Mergin)));
	int	be=min(256,(qBlue (Center)+(Radius+Mergin)));
	int	gn=ge-gs;

	#pragma omp parallel                             
	{                                                
		#pragma omp for
		for(int gi=0;gi<gn;gi++){
			int	g=gi+gs;
			for(int r=rs;r<re;r++){
				for(int b=bs;b<be;b++){
					if(Calc((BYTE)r ,(BYTE)g ,(BYTE)b ,Mergin)==false){
						Table[(r>>3)+(g<<5)+(b<<13)]|=~(1<<(r&7));
					}
				}
			}
		}
	}
}

bool	ColorLogic::operator==(const ColorLogic &src)	const
{
	ColorSpace *s;
	ColorSpace *d;
	for(s=Base.GetFirst(),d=src.Base.GetFirst();s!=NULL && d!=NULL;s=s->GetNext(),d=d->GetNext()){
		if(*s==*d){
			continue;
		}
		return false;
	}
	if(s!=NULL || d!=NULL){
		return false;
	}

	for(s=Eliminated.GetFirst(),d=src.Eliminated.GetFirst();s!=NULL && d!=NULL;s=s->GetNext(),d=d->GetNext()){
		if(*s==*d){
			continue;
		}
		return false;
	}
	if(s!=NULL || d!=NULL){
		return false;
	}
	return true;
}

bool	ColorLogic::GetMonoColorRange(int &ColL, int &ColH)	const
{
	ColorSpace	*c=Base.GetFirst();
	if(c!=NULL){
		c->GetMonoColorRange(ColL, ColH);
		return true;
	}
	return false;
}

void	ColorLogic::SetMonoColorRange(int ColL, int ColH)
{
	ColorSpace	*c=Base.GetFirst();
	if(c==NULL){
		c=new ColorSphere();
		Base.AppendList(c);
	}
	int	r=(ColL+ColH)/2;
	ColorSphere	*s=dynamic_cast<ColorSphere *>(c);
	if(s!=NULL){
		s->Set(r,r,r,ColH-r);
	}
}

void	ColorLogic::SetMonoColorRange(int RColL, int RColH
									, int GColL, int GColH
									, int BColL, int BColH)
{
	Base.RemoveAll();
	ColorBox	*c=new ColorBox();
	c->Set(RColL, RColH
		, GColL, GColH
		, BColL, BColH);
	Base.AppendList(c);
}


bool	ColorLogic::MakeBitmap(ImagePointerContainer &Images ,BYTE **DestMap ,int XLen ,int YLen)
{
	int	ICount=Images.GetCount();
	if(ICount>=3){
		ImageBuffer	*RBuff=Images[0];
		ImageBuffer	*GBuff=Images[1];
		ImageBuffer	*BBuff=Images[2];

		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*h=DestMap[y];
				BYTE	*R=RBuff->GetY(y);
				BYTE	*G=GBuff->GetY(y);
				BYTE	*B=BBuff->GetY(y);
				int	x;
				for(x=0;x<XLen-7;x+=8){
					*h=Calc8(R,G,B,0);
					h++;
					R+=8;
					G+=8;
					B+=8;
				}
				if(x<XLen){
					*h=0;
				}
				int	i=0;
				for(;x<XLen;x++,i++){
					if(Calc(*R,*G,*B,0)==true){
						h[i>>3] |= (0x80>>(i&7));
					}
					R++;
					G++;
					B++;
				}
			}
		}
		return true;
	}
	else if(ICount==1){
		ImageBuffer	*RBuff=Images[0];

		int	ColL,ColH;
		if(GetMonoColorRange(ColL, ColH)==false){
			return false;
		}

		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<YLen;y++){
				BYTE	*h=DestMap[y];
				BYTE	*R=RBuff->GetY(y);
				int	x;
				for(x=0;x<XLen;x++){
					if(ColL<=*R && *R<=ColH){
						SetBmpBitOnY1(h,x);
					}
					else{
						SetBmpBitOnY0(h,x);
					}
					R++;
				}
			}
		}
		return true;

	}
	return false;
}


ColorLogicWithTable::ColorLogicWithTable(const ColorLogicWithTable &src)
{
	OKTable=NULL;
	OriginTable=false;
	operator=(src);
}
ColorLogicWithTable::~ColorLogicWithTable(void)
{
	if(OriginTable==true){
		if(OKTable!=NULL){
			delete	[]OKTable;
		}
	}
	OKTable=NULL;
}

bool	ColorLogicWithTable::Calc(BYTE	r ,BYTE	  g ,BYTE   b,int Mergin)
{
	if(OKTable!=NULL){
		int	mr=r;
		int	mg=g;
		int	mb=b;
		if((OKTable[(mr>>3)+(mg<<5)+(mb<<13)] & (1<<(mr&7)))!=0){
			return true;
		}
	}
	return ColorLogic::Calc(r,g,b,Mergin);
}
bool	ColorLogicWithTable::Calc(double	r ,double g ,double	b,int Mergin)
{
	if(OKTable!=NULL){
		int	mr=r;
		int	mg=g;
		int	mb=b;
		if((OKTable[(mr>>3)+(mg<<5)+(mb<<13)] & (1<<(mr&7)))!=0){
			return true;
		}
	}
	return ColorLogic::Calc(r,g,b,Mergin);
}
ColorLogicWithTable	&ColorLogicWithTable::operator=(const ColorLogicWithTable &src)
{
	ColorLogic::operator=(src);

	OKTable	=src.OKTable;
	OriginTable=false;

	return *this;
}
ColorLogicWithTable	&ColorLogicWithTable::operator=(const ColorLogic &src)
{
	ColorLogic::operator=(src);

	if(OriginTable==true){
		delete	[]OKTable;
	}
	OKTable=NULL;
	OriginTable=false;
	return *this;
}


void	ColorLogicWithTable::CreateTable(int Mergin)
{
	ColorLogicTableAccessor.lockForRead();
	for(ColorLogicWithTable *e=(ColorLogicWithTable *)(ColorLogicTable[Mergin&0xFF].GetFirst());e!=NULL;e=(ColorLogicWithTable *)(e->GetNext())){
		if((operator==(*e))==true){
			ColorLogicTableAccessor.unlock();
			OKTable=e->OKTable;
			OriginTable=false;
			return;
		}
	}
	ColorLogicTableAccessor.unlock();

	if(ColorLogicTableCount<MaxColorLogicTableCount){
		ColorLogicWithTable	*h=new ColorLogicWithTable();
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		Save(&Buff);
		Buff.seek(0);
		h->Load(&Buff);

		h->OKTable=new BYTE[OKTableByte];
		h->OriginTable=true;
		OKTable=h->OKTable;
		OriginTable=false;
		memset(h->OKTable,0,OKTableByte);
		for(ColorSpace *b=Base.GetFirst();b!=NULL;b=b->GetNext()){
			b->MakeOrTable(OKTable,Mergin);
		}
		for(ColorSpace *e=Eliminated.GetFirst();e!=NULL;e=e->GetNext()){
			e->MakeAndTable(OKTable,Mergin);
		}
		ColorLogicTableAccessor.lockForWrite();
		ColorLogicTable[Mergin&0xFF].AppendList(h);
		ColorLogicTableCount++;
		ColorLogicTableAccessor.unlock();
	}
}

void	ColorLogicWithTable::ClearTable(void)
{
	ColorLogicTableAccessor.lockForWrite();
	for(int i=0;i<sizeof(ColorLogicTable)/sizeof(ColorLogicTable[0]);i++){
		ColorLogicTable[i].RemoveAll();
	}
	ColorLogicTableCount=0;
	ColorLogicTableAccessor.unlock();
}

ColorLogic	QString2ColorLogic(const QString &str)
{
	BYTE	Buff[10000];
	int	N=str.length();
	bool	Lower=true;
	int		BuffPoint=0;
	for(int i=0;i<N;i++){
		QChar	c=str[i];
		int	k;
		if(c=='0')		{	k=0;	}
		else if(c=='1'){	k=1;	}
		else if(c=='2'){	k=2;	}
		else if(c=='3'){	k=3;	}
		else if(c=='4'){	k=4;	}
		else if(c=='5'){	k=5;	}
		else if(c=='6'){	k=6;	}
		else if(c=='7'){	k=7;	}
		else if(c=='8'){	k=8;	}
		else if(c=='9'){	k=9;	}
		else if(c=='A'){	k=10;	}
		else if(c=='B'){	k=11;	}
		else if(c=='C'){	k=12;	}
		else if(c=='D'){	k=13;	}
		else if(c=='E'){	k=14;	}
		else if(c=='F'){	k=15;	}
		else{
			k=0;
		}
		if(Lower==true){
			Buff[BuffPoint]=k;
			Lower=false;
		}
		else{
			Buff[BuffPoint] |= k<<4;
			BuffPoint++;
			Lower=true;
		}
	}
	QBuffer	FBuff;
	FBuff.setData((const char *)Buff,BuffPoint);
	FBuff.open(QIODevice::ReadOnly);
	ColorLogic	Col;
	Col.Load(&FBuff);
	return Col;
}
QString		ColorLogic2QString(const ColorLogic &L)
{
	QBuffer	FBuff;
	FBuff.open(QIODevice::WriteOnly);
	((ColorLogic *)&L)->Save(&FBuff);
	int	N=FBuff.buffer().length();
	char	*TempBuff=new char[N*2+1];
	int		BuffPoint=0;
	for(int i=0;i<N;i++){
		char	c=FBuff.buffer().data()[i];
		for(int j=0;j<2;j++){
			int	h=c&0x0f;
			switch(h){
				case 0:	TempBuff[BuffPoint]='0';	break;
				case 1:	TempBuff[BuffPoint]='1';	break;
				case 2:	TempBuff[BuffPoint]='2';	break;
				case 3:	TempBuff[BuffPoint]='3';	break;
				case 4:	TempBuff[BuffPoint]='4';	break;
				case 5:	TempBuff[BuffPoint]='5';	break;
				case 6:	TempBuff[BuffPoint]='6';	break;
				case 7:	TempBuff[BuffPoint]='7';	break;
				case 8:	TempBuff[BuffPoint]='8';	break;
				case 9:	TempBuff[BuffPoint]='9';	break;
				case 10:TempBuff[BuffPoint]='A';	break;
				case 11:TempBuff[BuffPoint]='B';	break;
				case 12:TempBuff[BuffPoint]='C';	break;
				case 13:TempBuff[BuffPoint]='D';	break;
				case 14:TempBuff[BuffPoint]='E';	break;
				case 15:TempBuff[BuffPoint]='F';	break;
			}
			BuffPoint++;
			c>>=4;
		}
	}
	TempBuff[BuffPoint]=0;
	QString	ret(TempBuff);
	delete	[]TempBuff;
	return ret;
}

//===============================================================

RgbList &RgbList::operator=(const RgbList &src)
{
	RGBData=src.RGBData;
	return *this;
}
bool	RgbList::Save(QIODevice *f)
{
	if(::Save(f,RGBData)==false){
		return false;
	}
	return true;
}
bool	RgbList::Load(QIODevice *f)
{
	if(::Load(f,RGBData)==false){
		return false;
	}
	return true;
}


RgbStocker	&RgbStocker::operator=(const RgbStocker &src)
{
	RemoveAll();
	for(RgbList *a=src.GetFirst();a!=NULL;a=a->GetNext()){
		RgbList	*b=new RgbList();
		*b= *a;
		AppendList(b);
	}
	return *this;
}
	
bool	RgbStocker::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(RgbList *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->Save(f)==false){
			return false;
		}
	}
	return true;
}
	
bool	RgbStocker::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false)
		return false;
	for(int i=0;i<N;i++){
		RgbList *a=new RgbList();
		if(a->Load(f)==false){
			return false;
		}
		AppendList(a);
	}
	return true;
}

//===============================================================

RGBSample::RGBSample(const RGBSample &src)
{
	operator=(src);
}


bool	RGBSample::Save(QIODevice *f)
{
	if(::Save(f,rgbData)==false){
		return false;
	}
	if(::Save(f,Weight)==false){
		return false;
	}
	return true;
}
bool	RGBSample::Load(QIODevice *f)
{
	if(::Load(f,rgbData)==false){
		return false;
	}
	if(::Load(f,Weight)==false){
		return false;
	}
	return true;
}
bool	RGBSample::IsInclude(int r ,int g ,int b ,int Ext)	const
{
	int	S[4];
	S[0]=GetRed()	 -r;
	if(S[0]<-Ext || Ext<S[0]){
		return false;
	}
	S[1]=GetGreen()-g;
	if(S[1]<-Ext || Ext<S[1]){
		return false;
	}
	S[2]=GetBlue() -b;
	if(S[2]<-Ext || Ext<S[2]){
		return false;
	}
	S[3]=Ext;

	int	M[4];
	for(int i=0;i<4;i++){
		M[i]=S[i]*S[i];
	}
	if(M[0]+M[1]+M[2]<M[3]){
		return true;
	}

//	if(dR*dR+dG*dG+dB*dB<Ext*Ext){
//		return true;
//	}
	return false;
}
RGBSample	&RGBSample::operator=(const RGBSample &src)
{
	rgbData=src.rgbData;
	Weight=src.Weight;
	return *this;
}
double	RGBSample::GetLength(const RGBSample &s)	const
{
	double	dr=GetRed()-s.GetRed();
	double	dg=GetGreen()-s.GetGreen();
	double	db=GetBlue()-s.GetBlue();
	return sqrt(dr*dr+dg*dg+db*db);
}
RGBStock::RGBStock(const RGBStock &src)
{
	operator=(src);
}

bool	RGBStock::Save(QIODevice *f)
{
	int32	N=GetNumber();
	if(::Save(f,N)==false){
		return false;
	}
	for(RGBSample *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->Save(f)==false){
			return false;
		}
	}
	return true;
}
bool	RGBStock::Load(QIODevice *f)
{
	RemoveAll();
	int32	N;
	if(::Load(f,N)==false){
		return false;
	}
	for(int i=0;i<N;i++){
		RGBSample *c=new RGBSample();
		if(c->Load(f)==false){
			return false;
		}
		AppendList(c);
	}
	return true;
}
RGBSample	*RGBStock::SearchRGBSample(const QRgb &Col)	const
{
	for(RGBSample *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(*d==Col){
			return d;
		}
	}
	return NULL;
}
	
RGBSample	*RGBStock::SearchRGBSample(const QRgb &Col,int Ext)	const
{
	for(RGBSample *d=GetFirst();d!=NULL;d=d->GetNext()){
		if(d->IsInclude(qRed(Col),qGreen(Col),qBlue(Col),Ext)==true){
			return d;
		}
	}
	return NULL;
}
void	RGBStock::SetWeight(float w)
{
	for(RGBSample *d=GetFirst();d!=NULL;d=d->GetNext()){
		d->SetWeight(w);
	}
}


RGBStock	&RGBStock::operator=(const RGBStock &src)
{
	RemoveAll();

	for(RGBSample *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		RGBSample *d=new RGBSample();
		*d= *c;
		AppendList(d);
	}
	return *this;
}

RGBStock	&RGBStock::operator+=(const RGBStock &src)
{
	for(RGBSample *c=src.GetFirst();c!=NULL;c=c->GetNext()){
		RGBSample *d=SearchRGBSample(*c);
		if(d!=NULL){
			if(d->GetWeight()<c->GetWeight()){
				d->SetWeight(c->GetWeight());
			}
		}
		else{
			d=new RGBSample();
			*d= *c;
			AppendList(d);
		}
	}
	return *this;
}

QRgb	RGBStock::GetCenter(void)	const
{
	double	r,g,b;
	GetCenter(r,g,b);
	return qRgb(r,g,b);
}

void	RGBStock::GetCenter(double &r ,double &g ,double &b)	const
{
	int	ir=0;
	int	ig=0;
	int	ib=0;
	int	N=0;
	for(RGBSample *c=GetFirst();c!=NULL;c=c->GetNext(),N++){
		ir+=c->GetRed();
		ig+=c->GetGreen();
		ib+=c->GetBlue();
	}
	if(N!=0){
		r=((double)ir)/N;
		g=((double)ig)/N;
		b=((double)ib)/N;
	}
	else{
		r=0;
		g=0;
		b=0;
	}
}
bool	RGBStock::IsInclude(int r ,int g ,int b ,int Ext)	const
{
	for(RGBSample *c=GetFirst();c!=NULL;c=c->GetNext()){
		if(c->IsInclude(r ,g ,b ,Ext)==true){
			return true;
		}
	}
	return false;
}

double		RGBStock::GetClosedLength(const RGBSample &Col)	const
{
	double	Len=99999999;
	for(RGBSample *c=GetFirst();c!=NULL;c=c->GetNext()){
		double	d=c->GetLength(Col);
		if(d<Len){
			Len=d;
		}
	}
	return Len;
}

//===============================================================

bool	ColorSampleList::SaveData(QIODevice *f)
{
	switch(DataType){
		case TypeColorLogic:
			return ((ColorLogic *)Data)->Save(f);
		case TypeRGBStock:
			return ((RGBStock *)Data)->Save(f);
	}
	return false;
}
bool	ColorSampleList::LoadData(QIODevice *f)
{
	if(Data!=NULL){
		if(DataType==TypeColorLogic){
			ColorLogic	*L=(ColorLogic *)Data;
			delete	L;
		}
		else if(DataType==TypeRGBStock){
			RGBStock	*L=(RGBStock *)Data;
			delete	L;
		}
	}
	Data=NULL;
	switch(DataType){
		case TypeColorLogic:
			Data=new ColorLogic();
			return ((ColorLogic *)Data)->Load(f);
		case TypeRGBStock:
			Data=new RGBStock();
			return ((RGBStock *)Data)->Load(f);
		default:
			return false;
	}
	return false;
}

ColorSampleList	&ColorSampleList::operator=(ColorSampleList &src)
{
	if(Data!=NULL){
		switch(DataType){
			case TypeColorLogic:
				delete	((ColorLogic *)Data);
				break;
			case TypeRGBStock:
				delete	((RGBStock *)Data);
				break;
			default:
				break;
		}
		Data=NULL;
	}

	AutoCount	=src.AutoCount;
	Name		=src.Name;
	DataType	=src.DataType;
	UpdateTime	=src.UpdateTime;
	if(src.Data!=NULL){
		QBuffer	Buff;
		Buff.open(QIODevice::ReadWrite);
		src.SaveData(&Buff);
		Buff.seek(0);
		LoadData(&Buff);
	}
	return *this;
}

void	ColorSampleList::Set(ColorLogic &src)
{
	if(Data!=NULL){
		switch(DataType){
			case TypeColorLogic:
				delete	((ColorLogic *)Data);
				break;
			case TypeRGBStock:
				delete	((RGBStock *)Data);
				break;
			default:
				break;
		}
	}
	DataType=TypeColorLogic;

	Data=new ColorLogic();
	*((ColorLogic *)Data)=src;
}
void	ColorSampleList::Set(RGBStock &src)
{
	if(Data!=NULL){
		switch(DataType){
			case TypeColorLogic:
				delete	((ColorLogic *)Data);
				break;
			case TypeRGBStock:
				delete	((RGBStock *)Data);
				break;
			default:
				break;
		}
	}
	DataType=TypeRGBStock;

	Data=new RGBStock();
	*((RGBStock *)Data)=src;
}
void	ColorSampleList::Set(RGBStock &src,float weight)
{
	if(Data!=NULL){
		switch(DataType){
			case TypeColorLogic:
				delete	((ColorLogic *)Data);
				break;
			case TypeRGBStock:
				delete	((RGBStock *)Data);
				break;
			default:
				break;
		}
	}
	DataType=TypeRGBStock;


	Data=new RGBStock();
	*((RGBStock *)Data)=src;
	((RGBStock *)Data)->SetWeight(weight);
}

RGBStock	*ColorSampleList::GetRGBStock(void)	const
{
	if(Data==NULL){
		return NULL;
	}
	return (RGBStock *)Data;
}
ColorLogic	*ColorSampleList::GetColorLogic(void)	const
{
	if(DataType==TypeColorLogic){
		if(Data==NULL){
			return NULL;
		}
		return (ColorLogic *)Data;
	}
	else if(DataType==TypeRGBStock){
		static	ColorLogic	ColorLogicData;
		ColorSphere	*s=new ColorSphere();
		s->Create(*((RGBStock*)Data));
		ColorLogicData.ClearAll();
		ColorLogicData.Add(s);
		return &ColorLogicData;
	}
	return NULL;
}

//===============================================================

FloatRGBColor::FloatRGBColor(const QColor &col)
{
	R=col.red();
	G=col.green();
	B=col.blue();
}
FloatRGBColor::FloatRGBColor(const FloatRGBColor &src)
{
	R=src.R;
	G=src.G;
	B=src.B;
}

FloatRGBColor	&FloatRGBColor::operator=(const FloatRGBColor &src)
{
	R=src.R;
	G=src.G;
	B=src.B;
	return *this;
}
bool	FloatRGBColor::operator==(const FloatRGBColor &src)
{
	if(R==src.R
	&& G==src.G
	&& B==src.B)
		return true;
	return false;
}
bool	FloatRGBColor::operator!=(const FloatRGBColor &src)
{
	return !operator==(src);
}

double	FloatRGBColor::GetDistance(const FloatRGBColor &src)
{
	double	dR=R-src.R;
	double	dG=G-src.G;
	double	dB=B-src.B;
	double	Len=dR*dR+dG*dG+dB*dB;
	return sqrt(Len);
}

struct FloatRGBColorStruct
{
	double	R,G,B;
};
bool	FloatRGBColor::Save(QIODevice *f)
{
	struct FloatRGBColorStruct	D;

	D.R=R;
	D.G=G;
	D.B=B;
	if(f->write((const char *)&D,sizeof(D))!=sizeof(D)){
		return false;
	}
	return true;
}
bool	FloatRGBColor::Load(QIODevice *f)
{
	struct FloatRGBColorStruct	D;
	if(f->read((char *)&D,sizeof(D))!=sizeof(D)){
		return false;
	}
	R=D.R;
	G=D.G;
	B=D.B;
	return true;
}
//===============================================================

RelativeThresholdColorBox	&RelativeThresholdColorBox::operator=(const RelativeThresholdColorBox &src)
{
	ColData.rL	=src.ColData.rL;
	ColData.rH	=src.ColData.rH;
	ColData.gL	=src.ColData.gL;
	ColData.gH	=src.ColData.gH;
	ColData.bL	=src.ColData.bL;
	ColData.bH	=src.ColData.bH;
	return *this;
}
bool	RelativeThresholdColorBox::Save(QIODevice *f)
{
	if(f->write((const char *)&ColData ,sizeof(ColData))!=sizeof(ColData)){
		return false;
	}
	return true;
}
bool	RelativeThresholdColorBox::Load(QIODevice *f)
{
	if(f->read((char *)&ColData ,sizeof(ColData))!=sizeof(ColData)){
		return false;
	}
	return true;
}

void	RelativeThresholdColorBox::GetColorRange(QRgb &center 
						,int &RL ,int &RH
						,int &GL ,int &GH
						,int &BL ,int &BH) const
{
	RL=qRed	(center)-ColData.rL;
	RH=qRed	(center)+ColData.rH;
	GL=qGreen(center)-ColData.gL;
	GH=qGreen(center)+ColData.gH;
	BL=qBlue(center)-ColData.bL;
	BH=qBlue(center)+ColData.bH;
	if(RL<0)
		RL=0;
	if(RH>255)
		RH=255;
	if(GL<0)
		GL=0;
	if(GH>255)
		GH=255;
	if(BL<0)
		BL=0;
	if(BH>255)
		BH=255;
}

void	RelativeThresholdColorBox::GetMonoRange(int center
						,int &L ,int &H) const
{
	L=center-ColData.rL;
	H=center+ColData.rH;
	if(L<0)
		L=0;
	if(H>255)
		H=255;
}
void	RelativeThresholdColorBox::SetAbsColorRange(QRgb &center 
						,int AbsRL ,int AbsRH
						,int AbsGL ,int AbsGH
						,int AbsBL ,int AbsBH)
{
	int	rl=qRed(center)-AbsRL;
	if(rl<0)
		ColData.rL=0;
	else if(rl<256)
		ColData.rL=rl;
	else
		ColData.rL=255;

	int	rh=AbsRH-qRed(center);
	if(rh<0)
		ColData.rH=0;
	else if(rh<256)
		ColData.rH=rh;
	else
		ColData.rH=255;

	int	gl=qGreen(center)-AbsGL;
	if(gl<0)
		ColData.gL=0;
	else if(gl<256)
		ColData.gL=gl;
	else
		ColData.gL=255;

	int	gh=AbsGH-qGreen(center);
	if(gh<0)
		ColData.gH=0;
	else if(gh<256)
		ColData.gH=gh;
	else
		ColData.gH=255;

	int	bl=qBlue(center)-AbsBL;
	if(bl<0)
		ColData.bL=0;
	else if(bl<256)
		ColData.bL=bl;
	else
		ColData.bL=255;

	int	bh=AbsBH-qBlue(center);
	if(bh<0)
		ColData.bH=0;
	else if(bh<256)
		ColData.bH=bh;
	else
		ColData.bH=255;
}
void	RelativeThresholdColorBox::SetAbsMonoRange(int center
						,int AbsL ,int AbsH)
{
	int	l=center-AbsL;
	if(l<0)
		ColData.rL=0;
	else if(l<256)
		ColData.rL=l;
	else
		ColData.rL=255;

	int	h=AbsH-center;
	if(h<0)
		ColData.rH=0;
	else if(h<256)
		ColData.rH=h;
	else
		ColData.rH=255;
}

void	RelativeThresholdColorBox::GetRelColorRange(
						 int &RL ,int &RH
						,int &GL ,int &GH
						,int &BL ,int &BH) const
{
	RL=ColData.rL;
	RH=ColData.rH;
	GL=ColData.gL;
	GH=ColData.gH;
	BL=ColData.bL;
	BH=ColData.bH;
}

void	RelativeThresholdColorBox::GetRelMonoRange(int &L ,int &H) const
{
	L=ColData.rL;
	H=ColData.rH;
}

void	RelativeThresholdColorBox::SetRelColorRange(int AbsRL ,int AbsRH
						,int AbsGL ,int AbsGH
						,int AbsBL ,int AbsBH)
{
	ColData.rL=AbsRL;
	ColData.rH=AbsRH;
	ColData.gL=AbsGL;
	ColData.gH=AbsGH;
	ColData.bL=AbsBL;
	ColData.bH=AbsBH;
}
void	RelativeThresholdColorBox::SetRelMonoRange(int AbsL ,int AbsH)
{
	ColData.rL=AbsL;
	ColData.rH=AbsH;
}

bool	RelativeThresholdColorBox::operator==(const RelativeThresholdColorBox &src)	const
{
	if(ColData.rL!=src.ColData.rL)	return false;
	if(ColData.rH!=src.ColData.rH)	return false;
	if(ColData.gL!=src.ColData.gL)	return false;
	if(ColData.gH!=src.ColData.gH)	return false;
	if(ColData.bL!=src.ColData.bL)	return false;
	if(ColData.bH!=src.ColData.bH)	return false;
	return true;
}

void	HSV2RGB(double h,double s ,double v ,int &R ,int &G ,int &B)
// HSV(HSB)色空間からRGB色空間へ変換する 
//  h(hue)       : 色相/色合い   0-360度の値
//  s(saturation): 彩度/鮮やかさ 0-255の値
//  v(Value)     : 明度/明るさ   0-255の値 
//  ※v は b(Brightness)と同様 
{
   while(h>= 360.0){
     h-=360.0;
   }
   
   s = s / 256.0;
   v = v / 256.0;
   
   if (s == 0.0){
     R= v;
     G= v;
     B= v;
     return;
   } 
   
   double	dh = floor(h / 60.0);
   double	p = v * (1 - s);
   double	q = v * (1 - s * (h / 60 - dh));
   double	t = v * (1 - s * (1 - (h / 60 - dh)));
   
   double	fR,fG,fB;
   switch ((int)dh){
   case 0 : fR= v; fG= t; fB= p;  break;
   case 1 : fR= q; fG= v; fB= p;  break;
   case 2 : fR= p; fG= v; fB= t;  break;
   case 3 : fR= p; fG= q; fB= v;  break;
   case 4 : fR= t; fG= p; fB= v;  break;
   case 5 : fR= v; fG= p; fB= q;  break;
   }   
   
   R =  Clipping((int)(fR * 255),0,255);
   G =  Clipping((int)(fG * 255),0,255);
   B =  Clipping((int)(fB * 255),0,255);
}

void	RGB2HSV(double &h,double &s ,double &v ,int r ,int g ,int b)
 // RGB色空間からHSV色空間へ変換する 
 //  r(red)  : 赤色 0-255の値
 //  g(green): 緑色 0-255の値
 //  b(blue) : 青色 0-255の値 
{
	int	cmax = max(r, g, b);
	int cmin = min(r, g, b);
	v=cmax;
   
	if (cmax != cmin) {
		// H(色相)  
		if (cmax == r)	h=60.0*(g-b)/((double)(cmax-cmin));
		if (cmax == g)	h=60.0*(b-r)/((double)(cmax-cmin)) + 120.0;
		if (cmax == b)	h=60.0*(r-g)/((double)(cmax-cmin)) + 240.0;
		
		// S(彩度)
		s = (cmax - cmin) / ((double)cmax);
	}
	else{
		h=0;
		s=0;
	}
	if (h < 0){
		h = h + 360;
	}
   
	h = Clipping(h,0.0,360.0);
	s = Clipping(s*256,0.0,255.0);
	v = Clipping(v,0.0,255.0);     
}

void	RGB2HSV(double &h,double &s ,double &v ,double r ,double g ,double b)
 // RGB色空間からHSV色空間へ変換する 
 //  r(red)  : 赤色 0-255の値
 //  g(green): 緑色 0-255の値
 //  b(blue) : 青色 0-255の値 
{
	double	cmax = max(r, g, b);
	double cmin = min(r, g, b);
	v=cmax;
   
	if (cmax != cmin) {
		// H(色相)  
		if (cmax == r)	h=60.0*(g-b)/((cmax-cmin));
		if (cmax == g)	h=60.0*(b-r)/((cmax-cmin)) + 120.0;
		if (cmax == b)	h=60.0*(r-g)/((cmax-cmin)) + 240.0;
		
		// S(彩度)
		s = (cmax - cmin) / (cmax);
	}
	else{
		h=0;
		s=0;
	}
	if (h < 0){
		h = h + 360;
	}
   
	h = Clipping(h,0.0,360.0);
	s = Clipping(s*256,0.0,255.0);
	v = Clipping(v,0.0,255.0);     
}

void	RGB2XYZ(double R,double G ,double B,double &X ,double &Y ,double &Z)
{
	R=R/256.0;
	G=G/256.0;
	B=B/256.0;
	//X=2.76883*R+1.75171*G+1.13014*B;
	//Y=R+4.59061*G+0.06007*B;
	//Z=0.05651*G+5.59417*B;

	X=0.4124*R + 0.3576*G + 0.1805*B;
	Y=0.2126*R + 0.7152*G + 0.0722*B;
	Z=0.0193*R + 0.1192*G + 0.9505*B;

}
void	XYZ2RGB(double X ,double Y ,double Z,double &R,double &G ,double &B)
{
	//R=0.418466*X-0.158661*Y-0.082835*Z;
	//G=-0.091169*X+0.252431*Y+0.015707*Z;
	//B=0.000921*X-0.002550*Y+0.178599*Z;
	
	R= 3.2406*X-1.5372*Y-0.4986*Z;
	G=-0.9689*X+1.8757*Y+0.04151*Z;
	B=0.05571*X-0.2040*Y+1.0570*Z;

	R=R*256.0;
	G=G*256.0;
	B=B*256.0;
}

void	LAB2XYZ(double L,double A ,double B,double &X ,double &Y ,double &Z)
{
	double	fy=(L+16)/116.0;
	double	fx=fy+A/500.0;
	double	fz=fy-B/200.0;
	X=fx;
	Y=fy;
	Z=fz;
}
void	XYZ2LAB(double X ,double Y ,double Z,double &L,double &A ,double &B)
{
	L=116*Y-16;
	A=500*(X-Y);
	B=200*(Y-Z);
}

double	GetDeltaE76(double L1 ,double A1 ,double B1 ,double L2 ,double A2 ,double B2)
{
	return sqrt((L1-L2)*(L1-L2)+(A1-A2)*(A1-A2)+(B1-B2)*(B1-B2));
}

double	GetDeltaE2000(double L1 ,double A1 ,double B1 ,double L2 ,double A2 ,double B2)
{
	static	double	pi_2=2*M_PI;
	static	double	d6	=6.0/180.0*M_PI;
	static	double	d25	=25.0/180.0*M_PI;
	static	double	d30	=30.0/180.0*M_PI;
	static	double	d60	=60.0/180.0*M_PI;
	static	double	d63	=63.0/180.0*M_PI;
	static	double	d275=275.0/180.0*M_PI;
	static	double	kl=1.0;
	static	double	kc=1.0;
	static	double	kh=1.0;

	double dld = L2 - L1;
	double lb = (L1 + L2) / 2;
	
	double cs1 = hypot(A1, B1);
	double cs2 = hypot(A2, B2);
	double cb = (cs1 + cs2) / 2;
	double cb7 = pow(cb,7);
	double	v25_7=pow(25.0,7);
	double ad1 = A1 + A1 / 2 * (1 - sqrt(cb7 / (cb7 + v25_7)));
	double ad2 = A2 + A2 / 2 * (1 - sqrt(cb7 / (cb7 + v25_7)));
	
	double cd1 = hypot(ad1, B1);
	double cd2 = hypot(ad2, B2);
	double cbd = (cd1 + cd2) / 2;
	double cbd7 = pow(cbd,7);
	
	double dcd = (cd2 - cd1);
	double hd1 = (B1==0 && ad1==0) ? 0 : atan(ad1/B1);
	if(hd1 < 0){
	    hd1 += pi_2;
	}
	double hd2 = (B2==0 && ad2==0) ? 0 : atan(ad2/B2);
	if(hd2 < 0){
	    hd2 += pi_2;
	}
	
	double dhd = hd2 - hd1;
	if(cd1 * cd2 == 0){
	    dhd = 0;
	} else if(fabs(hd1 - hd2) > M_PI) {
	    if(hd2 <= hd1){
	        dhd += pi_2;
	    } else {
	        dhd -= pi_2;
	    }
	}
	
	
	double dhhd = 2 * sqrt(cd1 * cd2) * sin(dhd / 2);
	double hhbd = 0;
	if(cd1 * cd2 != 0){
	    hhbd = abs(hd1 - hd2) > M_PI ? ( hd1 + hd2 + pi_2) / 2 : (hd1 + hd2) / 2;
	}
	
	double tt = 1
	        - 0.17 * cos(hhbd - d30)
	        + 0.24 * cos(2 * hhbd)
	        + 0.32 * cos(3 * hhbd + d6)
	        - 0.20 * cos(4 * hhbd - d63);
	double lb50_2 = pow(lb - 50,2);
	double ssl = 1 + (0.015 * lb50_2) / sqrt(20 + lb50_2);
	double ssc = 1 + 0.045 * cbd;
	double ssh = 1 + 0.015 * cbd * tt;
	double rrt = -2.0 * sqrt(cbd7 / (cbd7 +v25_7)) * sin(d60 * exp(- pow((hhbd - d275)/ d25,2)));
	double de = pow(dld / (kl * ssl),2)
	        + pow(dcd / (kc * ssc),2)
	        + pow(dhhd / (kh * ssh),2)
	        + rrt * (dcd / (kc * ssc)) * (dhhd / (kh * ssh));
	
	return sqrt(de);
}
