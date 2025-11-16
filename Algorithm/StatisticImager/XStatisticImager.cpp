/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XStatisticImager.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "StatisticImagerResource.h"
#include "XStatisticImager.h"
#include "XCrossObj.h"
#include "XGeneralFunc.h"
#include "XAnyData.h"
#include "XStatisticPacket.h"
#include <QColor>
#include <omp.h>
#include "swap.h"
#include "XFormOperator.h"
#include "XAutoMaskingPI.h"
#include "XMaskingFromGeneral.h"
#include "XImageProcess.h"

#define OldShaderEnabled

//#define DebugConsole
#ifdef DebugConsole
#include "windows.h"
#endif

//#define Debug
#ifdef Debug
int DebugPoint=0;
int DebugPointX	=618;
int DebugPointY	=4537;
#endif

inline	BYTE	Clip255(int d)
{
	if(d<0)
		return 0;
	if(d>255)
		return 255;
	return d;
}

inline	BYTE	_PixelStatisticInLayer::GetAvr(int n)
{
	return Added/n;
}
/*	//D-20100208
inline	BYTE	_PixelStatisticInLayer::GetLight(int n,double Gain)
{
	double	Avr=(double)Added/(double)n;
	double	v=(Added2-Avr*Avr*(double)n)/(double)n;
	return Clip255((int)(Avr+Gain*sqrt(v)));
}
inline	BYTE	_PixelStatisticInLayer::GetDark(int n,double Gain)
{
	double	Avr=(double)Added/(double)n;
	double	v=(Added2-Avr*Avr*(double)n)/(double)n;
	return Clip255((int)(Avr-Gain*sqrt(v)));
}
*/
inline	BYTE	_PixelStatisticInLayer::GetDisorder(int n)
{
	double	Avr=Added/(double)n;
	double	v=(Added2-(double)Avr*(double)Avr*n)/(double)n;
	return Clip255(sqrt(v));
}

inline	BYTE	GetDisorder2(DWORD Added,DWORD Added2,int n)
{
	double	Avr=Added/(double)n;
	double	v=(Added2-(double)Avr*(double)Avr*n)/(double)n;
	return Clip255(sqrt(v));
}


StatisticImagerThreshold::StatisticImagerThreshold(StatisticImagerItem *parent)
:AlgorithmThreshold(parent)
{
}

void	StatisticImagerThreshold::CopyFrom(const AlgorithmThreshold &src)
{
}
bool	StatisticImagerThreshold::Save(QIODevice *f)
{
	return true;
}
bool	StatisticImagerThreshold::Load(QIODevice *f)
{
	return true;
}

StatisticImagerInLayer::StatisticImagerInLayer(AlgorithmInPageRoot *parent)
:AlgorithmInLayerPLI(parent)
{
	StatisticBuff=NULL;
	StatisticBuffCount=0;
	AllocXLen=AllocYLen=0;
	ExecuteInitialAfterEditFlag=false;

	MasterBrightAvg	=0;
	TargetBrightAvg	=0;
	MaskBmpCnt		=0;
	MaskBmp			=NULL;
	pAlignPage		=NULL;
	ABase			=NULL;

	MLeastSquaresMethodTable=NULL;
	TLeastSquaresMethodTable=NULL;

	EnLargeDot		=0;
	ShaderEnabled	=false;
}

StatisticImagerInLayer::~StatisticImagerInLayer(void)
{
	if(StatisticBuff!=NULL){
		for(int y=0;y<AllocYLen;y++){
			delete	[]StatisticBuff[y];
		}
		delete	[]StatisticBuff;
		StatisticBuff=NULL;
	}
}


void	StatisticImagerInLayer::InitialAlloc(void)
{
	if(StatisticBuff==NULL){
		AllocXLen=GetDotPerLine();
		AllocYLen=GetMaxLines();
		StatisticBuff	=new PixelStatisticInLayer*[AllocYLen];
		for(int y=0;y<AllocYLen;y++){
			StatisticBuff[y]=new PixelStatisticInLayer[AllocXLen];
		}
	}
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<AllocYLen;y++){
			for(int x=0;x<AllocXLen;x++){
				StatisticBuff[y][x].Added		=0;
				StatisticBuff[y][x].Added2		=0;
				StatisticBuff[y][x].Lightest	=0;
				StatisticBuff[y][x].Darkest		=255;
				StatisticBuff[y][x].Lighter		=0;
				StatisticBuff[y][x].Darker		=255;
			}
		}
	}
}

BYTE	**StatisticImagerInLayer::GetMaskBitmap(void)
{
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(LBase!=NULL){
		AlgorithmInPageRoot	*LPI=LBase->GetPageData(GetPage());
		CmdCreateAutoMaskingPIBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	AlgorithmBase	*MBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"MaskingPI");
	if(MBase!=NULL){
		AlgorithmInPageRoot	*LPI=MBase->GetPageData(GetPage());
		CmdCreateMaskingPIBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.BmpMap;
	}
	return NULL;
}

BYTE	**StatisticImagerInLayer::GetAutoMaskBitmap(void)
{
	AlgorithmBase	*LBase=GetLayersBase()->GetAlgorithmBase(/**/"Basic" ,/**/"AutoMaskingPI");
	if(LBase!=NULL){
		AlgorithmInPageRoot	*LPI=LBase->GetPageData(GetPage());
		CmdCreateAutoMaskingPIAutoBitmapWithLibPacket	CmdPacket(GetLayersBase());
		CmdPacket.XByte	=(GetDotPerLine()+7)/8;
		CmdPacket.YLen	=GetMaxLines();
		CmdPacket.LibType=-1;
		CmdPacket.LibID	=-1;
		LPI->TransmitDirectly(&CmdPacket);
		return CmdPacket.AutoBmpMap;
	}
	return NULL;
}

bool	StatisticImagerInLayer::GetAutoAlignmentLibrary(GUIDirectMessage *CmdPacket)
{
	if(ABase!=NULL){
		CmdGetAutoAlignmentLibraryListPacket	*Packet=dynamic_cast<CmdGetAutoAlignmentLibraryListPacket *>(CmdPacket);
		if(Packet!=NULL){
			Packet->LibFolderID=-1;
			ABase->TransmitDirectly(Packet);
			return true;
		}
	}
	return false;
}

//?A?Å ?n?a?@?d?g?p?É ?A?A?P?x?I?Q???3???E?d?i?Å ?i?}?X?^?[?a???j
void	StatisticImagerInLayer::GetLeastSquaresMethodM()
{
//////////////////////////////////////////////////////
//	?R???3???E?A?I?A?Å ?n?a?@?E?a?e?P?x?a?3?d?l?|?e	//
//////////////////////////////////////////////////////
//	
//	???E ax + by + c = z ?A?É ?A
//	                       2
//	S = ?Åã(ax + by + c - z)  ?dabc?Å‚?e???e?A?I?ÅÄ?a?É ?Å‚?e?d =0 ?A?É ???A?Åò?u?o?R?d?d?-?iZ?2?u?u?A?I?ÅE?a?j
//	        2 2    2 2    2          2
//	  = ?Åã(a x  + b y  + c  - 2cz + z  + 2abxy + 2bcy - 2byz + 2acx - 2axz)
//	     2   2    2   2    2                 2
//	  = a ?Åãx  + b ?Åãy  + c ?Åã1 - 2c?Åãz + ?Åãz  + 2ab?Åãxy + 2bc?Åãy - 2b?Åãyz + 2ac?Åãx - 2a?Åãxz
//	
//	?YS        2
//	--- = 2a?Åãx  + 2b?Åãxy + 2c?Åãx - 2?Åãxz
//	?Ya
//	
//	?YS        2
//	--- = 2b?Åãy  + 2a?Åãxy + 2c?Åãy - 2?Åãyz
//	?Yb
//	
//	?YS
//	--- = 2nc - 2?Åãz + 2b?Åãy + 2a?Åãx
//	?Yc
//	
//	?a?L?I?R?d =0 ?A?ÅN?-?I?A?A
//	
//	?C     2
//	|  a?Åãx  + b?Åãxy + c?Åãx - ?Åãxz = 0
//	|      2
//	|  b?Åãy  + a?Åãxy + c?Åãy - ?Åãyz = 0
//	|  
//	|  nc - ?Åãz + b?Åãy + a?Åãx = 0
//	?
//
///////////////////
//	?I?`?É ?A?A
//
//	?C     2
//	|  a?Åãx  + b?Åãxy + c?Åãx = ?Åãxz
//	|              2
//	|  a?Åãxy + b?Åãy  + c?Åãy = ?Åãyz
//	|  
//	|  a?Åãx + b?Åãy + nc = ?Åãz
//	?
//
//?@?Å}?e?d?s?n?A?d?-?A?A
//
//	?C     2
//	|  |?Åãx   ?Åãxy  ?Åãx| | a | = |?Åãxz|
//	|  |         2     | |   |   |    |
//	|  |?Åãxy  ?Åãy   ?Åãy| | b | = |?Åãyz|
//	|  |               | |   |   |    |
//	|  |?Åãx   ?Åãy    n | | c | = |?Åãz |
//	?
//
//	        2
//	    |?Åãx   ?Åãxy  ?Åãx|       |?Åãxz|       | a |
//	    |         2     |       |    |       |   |
//	A = |?Åãxy  ?Åãy   ?Åãy|   B = |?Åãyz|   C = | b |
//	    |               |       |    |       |   |
//	    |?Åãx   ?Åãy    n |       |?Åãz |       | c |
//
//?@?A?ÅE?e?A?A
//
//?@A?EC = B
//
//?@?E?I?A?A
//
//?@C = A^(-1)?EB
//
//?@A?I?t?s?n?I?A
//
//            2     2                                           2                     2
//?@detA = ?Åãx ?E?Åãy ?En + ?Åãxy?E?Åãy?E?Åãx + ?Åãx?E?Åãxy?E?Åãy - ?Åãx ?E?Åãy?E?Åãy - ?Åãx?E?Åãy ?E?Åãx - ?Åãxy?E?Åãxy?En ?? 0
//
//	             2
//	         |?Åãx   ?Åãxy  ?Åãx|
//	         |         2     |
//	A^(-1) = |?Åãxy  ?Åãy   ?Åãy|
//	         |               |
//	         |?Åãx   ?Åãy    n |
//
//
//
//
//
//	
//
///////////////////
//	   2        2
//	?Åãx = A, ?Åãy = B, ?Åãx = C, ?Åãy = D
//	
//	?Åãz = E, ?Åãxy = F, ?Åãyz = G, ?Åãxz = H ?A?ÅE?e?A?A
//	
//	?C
//	|  aA + bF + cC - H = 0 ?c ?
//	|
//	|  bB + aF + cD - G = 0 ?c ?
//	|  
//	|  nc - E + bD + aC = 0 ?c ?
//	?
//	
//	??c?c?@nc = E - bD - aC
//	
//	          E - bD - aC      
//	  ?? c = ------------- ?c ?
//	               n
//	
//	??E?'?I c ?d?a?u?É ?A?A
//	
//	  naA  + nbF + (E - bD - aC)C - nH = 0
//	                           2
//    naA + nbF + CE - bCD - aC  - nH = 0
//	         2
//	  (nA - C )a + (nF - CD)b + CE - nH = 0 ?c ?'
//	
//	??E?'?I c ?d?a?u?É ?A?A
//	     
//	  nbB + naF + (E - bD - aC)D - G = 0
//	                     2
//	  nbB + naF + DE - bD  - aCD - nG = 0
//	                      2
//	  (nF - CD)a + (nB - D )b + DE - nG = 0 ?c ?'
//	
//	           2
//	?'*(nB - D ) - ?'*(nF - CD) ?A b ?d?A?É ?A a ?d???s?e
//	         2         2            2                      2
//	  (nB - D )*(nA - C )a + (nB - D )*(nF - CD)b + (nB - D )*(CE - nH) = 0 ?c ?"
//	           2                    2
//	  (nF - CD) a          + (nB - D )*(nF - CD)b + (nF - CD)*(DE - nG) = 0 ?c ?"
//	
//	?" - ?"
//	         2         2              2           2
//	  (nB - D )*(nA - C )a - (nF - CD) a + (nB - D )*(CE - nH) - (nF - CD)*(DE - nG) = 0
//	          2         2             2                                  2
//	  [(nB - D )*(nA - C ) - (nF - CD) ]a = (nF - CD)*(DE - nG) - (nB - D )*(CE - nH)
//	
//	                                       2
//	          (nF - CD)*(DE - nG) - (nB - D )*(CE - nH)
//	  ?? a = ------------------------------------------- ?c ?
//	                     2         2             2
//	              (nB - D )*(nA - C ) - (nF - CD)
//	
//	?'?a?e b ?d???s?e
//	                        2
//	  (nF - CD)b = - (nA - C )a + nH - CE
//	
//	                   2
//	          - (nA - C )a - (CE - nH)
//	  ?? b = --------------------------  ?c ?
//	                 (nF - CD)
//	
//////////////////////////////////////////////////////

	ImageBuffer &MasterBuff=GetMasterBuff();
	int MaskBitmapFPackNumb=MasterMaskBitmapFPack.GetCount();

	if(MLeastSquaresMethodTable!=NULL){
		delete MLeastSquaresMethodTable;
	}
	MLeastSquaresMethodTable=new struct LeastSquaresMethodStruct1[MaskBitmapFPackNumb];

	//???I?l?A?W?Ä?I?ÅE?d???s?e
	BYTE *AveragePack	=new BYTE[MaskBitmapFPackNumb];
	BYTE *DisorderPack	=new BYTE[MaskBitmapFPackNumb];
	int Cnt=0;
	for(PureFlexAreaList *c=MasterMaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
		uint64	Added2;
		uint32	Added;
		Added=Added2=0;
		int	Len	=c->GetFLineLen();
		for(int j=0;j<Len;j++){
			int x1=c->GetFLineLeftX (j);
			int x2=c->GetFLineRightX(j);
			int y =c->GetFLineAbsY  (j);
#ifdef Debug
			if(y>DebugPointY-10 && y<DebugPointY+10 && x1>DebugPointX-10 && x1<DebugPointX+10){
				DebugPoint++;
			}
#endif
			BYTE *Buff=MasterBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				Added+=Buff[x];
				Added2+=Buff[x]*Buff[x];
			}
		}
		int n=c->GetPatternByte();
		AveragePack[Cnt]=Added/n;
		DisorderPack[Cnt]=GetDisorder2(Added,Added2,n);
	}

	int x;
	Cnt=0;
	for(PureFlexAreaList *c=MasterMaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
#ifdef Debug
		if(Cnt==DebugPoint){
			DebugPoint++;
		}
#endif
///		int ExclusionNumb=0;	//???O?h?b?g??
///		uint64	A,B,F,G,H;
///		uint32	C,D,E;
		int64	A,B,C,D,E,F,G,H;
		A=B=C=D=E=F=G=H=0;
		int	Len	=c->GetFLineLen();
		int xxx1,yyy1;
		if(Len>0){
			c->GetCenter(xxx1,yyy1);
		}

		//?I?a?a?a?Å·?Åë?e???I?O?o?Åë?A?v?Z
		int N=0;
		int ThinLen	=0;
		int ThinX	=0;
		const int RimitAreaSize=300;
		int PatternByte=c->GetPatternByte();
		while(PatternByte>RimitAreaSize){
			N++;
			PatternByte=(c->GetPatternByte()>>N);
			if((N&0x01)==1){
				ThinLen++;
			}
			else{
				ThinX++;
			}
		}
		ThinLen	=pow(2.0,ThinLen);
		ThinX	=pow(2.0,ThinX);

		int n=0;
		for(int j=ThinLen-1;j<Len;j+=ThinLen){
			int x1=c->GetFLineLeftX	(j);
			int x2=c->GetFLineRightX(j);
			int y =c->GetFLineAbsY  (j);
			BYTE *Buff=MasterBuff.GetY(y);
///			for(int x=x1+ThinX-1;x<x2;x+=ThinX){
			for(x=x1+ThinX-1;x<x2;x+=ThinX){
				//?f?[?^?I?I?E
				if(Buff[x]<AveragePack[Cnt]-DisorderPack[Cnt]*2 || Buff[x]>AveragePack[Cnt]+DisorderPack[Cnt]*2){
///					ExclusionNumb++;
					continue;
				}
				int xxx=x-xxx1;
				int yyy=y-yyy1;
				A+=xxx*xxx;
				B+=yyy*yyy;
				C+=xxx;
				D+=yyy;
				E+=Buff[x];
				F+=xxx*yyy;
				G+=yyy*Buff[x];
				H+=xxx*Buff[x];
				n++;
			}
		}
//	                                       2
//	          (nF - CD)*(DE - nG) - (nB - D )*(CE - nH)
//	  ?? a = ------------------------------------------- ?c ?
//	                     2         2             2
//	              (nB - D )*(nA - C ) - (nF - CD)

		int64 aDenominator;	//a?I?a?e
		int64 nBDD=n*B-D*D;
		int64 nACC=n*A-C*C;
		int64 nFCD=n*F-C*D;
		int64 CEnH=C*E-n*H;
		if((aDenominator=nBDD*nACC-nFCD*nFCD)==0){
			MLeastSquaresMethodTable[Cnt].a=0;
		}
		else{
			MLeastSquaresMethodTable[Cnt].a=(double)((int64)(nFCD*(D*E-n*G))-nBDD*CEnH)/aDenominator;
		}
//	                   2
//	          - (nA - C )a - (CE - nH)
//	  ?? b = --------------------------  ?c ?
//	                 (nF - CD)

		if(nFCD==0){
			MLeastSquaresMethodTable[Cnt].b=0;
		}
		else{
			MLeastSquaresMethodTable[Cnt].b=(-nACC*MLeastSquaresMethodTable[Cnt].a-CEnH)/nFCD;
		}
/*
/////////////////////////////////////////////////////////////////
//	                                                  2
//	          -(CE - nH)*(nF - CD) - (nG - DE)*(nA - C )
//	  ?? b = --------------------------------------------  ?c ?'
//	                        2         2         2
//	               (nF - CD)  - (nA -C )*(nB - D )

		int64 bDenominator;	//b?I?a?e
		if((bDenominator=nFCD*nFCD-nACC*nBDD)==0){
			MLeastSquaresMethodTable[Cnt].b=0;
		}
		else{
			MLeastSquaresMethodTable[Cnt].b=((-CEnH*nFCD)-(int64)((n*G-D*E)*nACC))/(double)bDenominator;
		}
*/
//	          E - bD - aC      
//	  ?? c = ------------- ?c ?
//	               n

		MLeastSquaresMethodTable[Cnt].c=(E-MLeastSquaresMethodTable[Cnt].b*D-MLeastSquaresMethodTable[Cnt].a*C)/(uint64)n;
	}

	//delete
	delete []AveragePack;
	AveragePack				=NULL;
	delete []DisorderPack;
	DisorderPack			=NULL;
}

//?A?Å ?n?a?@?d?g?p?É ?A?A?P?x?I?Q???3???E?d?i?Å ?i?^?[?Q?b?g?a???j
void	StatisticImagerInLayer::GetLeastSquaresMethodT()
{
	ImageBuffer &TargetBuff=GetTargetBuff();
	int MaskBitmapFPackNumb=TargetMaskBitmapFPack.GetCount();

	if(TLeastSquaresMethodTable!=NULL){
		delete TLeastSquaresMethodTable;
	}
	TLeastSquaresMethodTable=new struct LeastSquaresMethodStruct2[MaskBitmapFPackNumb];

	//???I?l?A?W?Ä?I?ÅE?d???s?e
	BYTE *AveragePack	=new BYTE[MaskBitmapFPackNumb];
	BYTE *DisorderPack	=new BYTE[MaskBitmapFPackNumb];
	int Cnt=0;
	for(PureFlexAreaList *c=TargetMaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
		uint64	Added2;
		uint32	Added;
		Added=Added2=0;
		int	Len	=c->GetFLineLen();
		for(int j=0;j<Len;j++){
			int x1=c->GetFLineLeftX (j);
			int x2=c->GetFLineRightX(j);
			int y =c->GetFLineAbsY  (j);
#ifdef Debug
			if(y>DebugPointY-10 && y<DebugPointY+10 && x1>DebugPointX-10 && x1<DebugPointX+10){
				DebugPoint++;
			}
#endif
			BYTE *Buff=TargetBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				Added+=Buff[x];
				Added2+=Buff[x]*Buff[x];
			}
		}
		int n=c->GetPatternByte();
		AveragePack[Cnt]=Added/n;
		DisorderPack[Cnt]=GetDisorder2(Added,Added2,n);
	}

	Cnt=0;
	for(PureFlexAreaList *c=TargetMaskBitmapFPack.GetFirst();c!=NULL;c=c->GetNext(),Cnt++){
#ifdef Debug
		if(Cnt==DebugPoint){
			DebugPoint++;
		}
#endif
///		int ExclusionNumb=0;	//???O?h?b?g??
///		uint64	A,B,F,G,H;
///		uint32	C,D,E;
		int64	A,B,C,D,E,F,G,H;
		A=B=C=D=E=F=G=H=0;
		int	Len	=c->GetFLineLen();
		int xxx1,yyy1;
		if(Len>0){
			c->GetCenter(xxx1,yyy1);
		}

		//?I?a?a?a?Å·?Åë?e???I?O?o?Åë?A?v?Z
		int N=0;
		int ThinLen	=0;
		int ThinX	=0;
		const int RimitAreaSize=300;
		int PatternByte=c->GetPatternByte();
		while(PatternByte>RimitAreaSize){
			N++;
			PatternByte=(c->GetPatternByte()>>N);
			if((N&0x01)==1){
				ThinLen++;
			}
			else{
				ThinX++;
			}
		}
		ThinLen	=pow(2.0,ThinLen);
		ThinX	=pow(2.0,ThinX);

		int n=0;
		for(int j=ThinLen-1;j<Len;j+=ThinLen){
			int x1=c->GetFLineLeftX (j);
			int x2=c->GetFLineRightX(j);
			int y =c->GetFLineAbsY  (j);
			BYTE *Buff=TargetBuff.GetY(y);
///			for(int x=x1+ThinX-1;x<x2;x+=ThinX){
			for(int x=x1+ThinX-1;x<x2;x+=ThinX){
				//?f?[?^?I?I?E
				if(Buff[x]<AveragePack[Cnt]-DisorderPack[Cnt]*2 || Buff[x]>AveragePack[Cnt]+DisorderPack[Cnt]*2){
///					ExclusionNumb++;
					continue;
				}
				int xxx=x-xxx1;
				int yyy=y-yyy1;
				A+=xxx*xxx;
				B+=yyy*yyy;
				C+=xxx;
				D+=yyy;
				E+=Buff[x];
				F+=xxx*yyy;
				G+=yyy*Buff[x];
				H+=xxx*Buff[x];
				n++;
			}
		}
//	                                       2
//	          (nF - CD)*(DE - nG) - (nB - D )*(CE - nH)
//	  ?? a = ------------------------------------------- ?c ?
//	                     2         2             2
//	              (nB - D )*(nA - C ) - (nF - CD)

		int64 aDenominator;	//a?I?a?e
		int64 nBDD=n*B-D*D;
		int64 nACC=n*A-C*C;
		int64 nFCD=n*F-C*D;
		int64 CEnH=C*E-n*H;
		if((aDenominator=nBDD*nACC-nFCD*nFCD)==0){
			TLeastSquaresMethodTable[Cnt].a=0;
		}
		else{
			TLeastSquaresMethodTable[Cnt].a=(double)((nFCD*(D*E-n*G))-nBDD*CEnH)/aDenominator;
		}
//	                   2
//	          - (nA - C )a - (CE - nH)
//	  ?? b = --------------------------  ?c ?
//	                 (nF - CD)

		if(nFCD==0){
			TLeastSquaresMethodTable[Cnt].b=0;
		}
		else{
			TLeastSquaresMethodTable[Cnt].b=(-nACC*TLeastSquaresMethodTable[Cnt].a-CEnH)/nFCD;
		}
/*
/////////////////////////////////////////////////////////////////
//	                                                  2
//	          -(CE - nH)*(nF - CD) - (nG - DE)*(nA - C )
//	  ?? b = --------------------------------------------  ?c ?'
//	                        2         2         2
//	               (nF - CD)  - (nA -C )*(nB - D )

		int64 bDenominator;	//b?I?a?e
		if((bDenominator=nFCD*nFCD-nACC*nBDD)==0){
			TLeastSquaresMethodTable[Cnt].b=0;
		}
		else{
			TLeastSquaresMethodTable[Cnt].b=(double)((-CEnH*nFCD)-(int64)((n*G-D*E)*nACC))/bDenominator;
		}
*/
//	          E - bD - aC      
//	  ?? c = ------------- ?c ?
//	               n

		TLeastSquaresMethodTable[Cnt].c=(E-TLeastSquaresMethodTable[Cnt].b*D-TLeastSquaresMethodTable[Cnt].a*C)/(uint64)n;
	}

#ifdef Debug
	int	Len;
	int xxx1,yyy1;
	int RetCnt;
	int tx,ty;
	int j;
	int x1,x2;
	int x,y;
	BYTE *Buff;
	int MBrightness,TBrightness;
	int Index;
#endif

	Cnt=0;
	int MasterCnt=0;
	double BrightCoef=((StatisticImagerBase *)GetParentBase())->BrightCoef;
	double HBrightCoef=1.0+BrightCoef;
	double LBrightCoef=1.0-BrightCoef;
	PureFlexAreaList *MasterArea=MasterMaskBitmapFPack.GetFirst();
	for(PureFlexAreaList *TargetArea=TargetMaskBitmapFPack.GetFirst();TargetArea!=NULL;TargetArea=TargetArea->GetNext(),Cnt++){
#ifdef Debug
		if(Cnt==DebugPoint){
			DebugPoint++;
		}
		//?P?x?a?3?W???I?Z?o
		Len	=TargetArea->GetFLineLen();
#else
		//?P?x?a?3?W???I?Z?o
		int	Len	=TargetArea->GetFLineLen();
		int xxx1,yyy1;
		int RetCnt;
#endif
		if(Len>0){
#ifdef Debug
			tx=TargetArea->GetFLineLeftX(0);
			ty=TargetArea->GetFLineAbsY(0);
#else
			int tx=TargetArea->GetFLineLeftX(0);
			int ty=TargetArea->GetFLineAbsY(0);
#endif
			//?}?X?^?[?a???A?I?I?a?I?O???d?2?Å~?e
			RetCnt=SearchMasterArea(TargetArea,MasterArea,pAlignPage->GetShiftXFromTarget(tx,ty),pAlignPage->GetShiftYFromTarget(tx,ty),Cnt,MasterCnt);
			if(RetCnt==-1){
				if(MasterArea->GetNext()!=NULL){
					MasterArea=MasterArea->GetNext();
					MasterCnt++;
					TLeastSquaresMethodTable[Cnt].TMBrightCoef=NULL;
					TLeastSquaresMethodTable[Cnt].EnableShader=false;
				}
				continue;
			}
			TargetArea->GetCenter(xxx1,yyy1);
		}

		int SumTargetArea=TargetArea->GetPatternByte();
		TLeastSquaresMethodTable[Cnt].TMBrightCoef=new double[SumTargetArea];
		TLeastSquaresMethodTable[Cnt].EnableShader=true;

#ifdef Debug
		Index=0;
		for(j=0;j<Len;j++){
			x1=TargetArea->GetFLineLeftX (j);
			x2=TargetArea->GetFLineRightX(j);
			y =TargetArea->GetFLineAbsY  (j);
			Buff=TargetBuff.GetY(y);
			for(x=x1;x<x2;x++){
				MBrightness=MLeastSquaresMethodTable[RetCnt].a*(x-xxx1)+MLeastSquaresMethodTable[RetCnt].b*(y-yyy1)+MLeastSquaresMethodTable[RetCnt].c;
				TBrightness=TLeastSquaresMethodTable[Cnt]	.a*(x-xxx1)+TLeastSquaresMethodTable[Cnt]	.b*(y-yyy1)+TLeastSquaresMethodTable[Cnt]	.c;
#else
		int Index=0;
		for(int j=0;j<Len;j++){
			int x1=TargetArea->GetFLineLeftX (j);
			int x2=TargetArea->GetFLineRightX(j);
			int y =TargetArea->GetFLineAbsY  (j);
			BYTE	*Buff=TargetBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				int MBrightness=MLeastSquaresMethodTable[RetCnt].a*(x-xxx1)+MLeastSquaresMethodTable[RetCnt].b*(y-yyy1)+MLeastSquaresMethodTable[RetCnt].c;
				int TBrightness=TLeastSquaresMethodTable[Cnt]	.a*(x-xxx1)+TLeastSquaresMethodTable[Cnt]	.b*(y-yyy1)+TLeastSquaresMethodTable[Cnt]	.c;
#endif
				if(MBrightness>=0 && MBrightness<256 && TBrightness>=0 && TBrightness<256){
					//Target?c?cMaster?O?I?P?x?I?ÅE?W???d?Z?o
					TLeastSquaresMethodTable[Cnt].TMBrightCoef[Index]=(double)MBrightness/TBrightness;
					if(TLeastSquaresMethodTable[Cnt].TMBrightCoef[Index]>HBrightCoef || TLeastSquaresMethodTable[Cnt].TMBrightCoef[Index]<LBrightCoef){
						TLeastSquaresMethodTable[Cnt].EnableShader=false;
						break;
					}
				}
				Index++;
			}
			if(TLeastSquaresMethodTable[Cnt].EnableShader==false){
				break;
			}
		}
		if(MasterArea->GetNext()!=NULL){
			MasterArea=MasterArea->GetNext();
			MasterCnt++;
		}
	}

	//delete
	delete []AveragePack;
	AveragePack				=NULL;
	delete []DisorderPack;
	DisorderPack			=NULL;
}

//?P?x?a?3
void	StatisticImagerInLayer::CalcLeastSquaresMethodT()
{
	ImageBuffer &TargetBuff=GetTargetBuff();

#ifdef Debug
	int	Len;
	int j;
	int x1,x2;
	int x,y;
	BYTE *Buff;
	int	Index;
#endif

	int Cnt=0;
	for(PureFlexAreaList *TargetArea=TargetMaskBitmapFPack.GetFirst();TargetArea!=NULL;TargetArea=TargetArea->GetNext(),Cnt++){
#ifdef Debug
		if(Cnt==DebugPoint){
			DebugPoint++;
		}
#endif
		if(TLeastSquaresMethodTable[Cnt].TMBrightCoef==NULL){
			continue;
		}
		if(TLeastSquaresMethodTable[Cnt].EnableShader==true){
#ifdef Debug
			//?P?x?a?3
			Index=0;
			Len	=TargetArea->GetFLineLen();
			for(j=0;j<Len;j++){
				x1=TargetArea->GetFLineLeftX (j);
				x2=TargetArea->GetFLineRightX(j);
				y =TargetArea->GetFLineAbsY  (j);
				Buff=TargetBuff.GetY(y);
				for(x=x1;x<x2;x++){
#else
			//?P?x?a?3
			int Index=0;
			int	Len	=TargetArea->GetFLineLen();
			for(int j=0;j<Len;j++){
				int x1=TargetArea->GetFLineLeftX (j);
				int x2=TargetArea->GetFLineRightX(j);
				int y =TargetArea->GetFLineAbsY  (j);
				BYTE	*Buff=TargetBuff.GetY(y);
				for(int x=x1;x<x2;x++){
#endif
					//Target?c?cMaster?O?I?P?x?I?ÅE?W???d?Z?o
					Buff[x]=Clip255((Buff[x])*TLeastSquaresMethodTable[Cnt].TMBrightCoef[Index++]);
				}
			}
		}
		//delete
		delete []TLeastSquaresMethodTable[Cnt].TMBrightCoef;
	}

	//delete
	delete TLeastSquaresMethodTable;
	TLeastSquaresMethodTable=NULL;
}

bool	StatisticImagerInLayer::CheckTargetPoint(int X,int Y,bool IsPad,bool IsSilk)
{
	if(pAlignPage->GetBitFirstPickupFromTarget(X,Y)==IsPad && pAlignPage->GetBitPickupFromTarget(X,Y)==IsSilk){
		return true;
	}
	//?u?I?d?m?F
	int SearchDot=1;
	if(X-SearchDot<0 || Y-SearchDot<0){
		return true;
	}
	for(int Len=1;Len<=SearchDot;Len++){
		int	dx;
		int	dy=-Len;
		for(dx=-Len;dx<Len;dx++){
			if(pAlignPage->GetBitFirstPickupFromTarget(X+dx,Y+dy)==IsPad && pAlignPage->GetBitPickupFromTarget(X+dx,Y+dy)==IsSilk){
				return true;
			}
		}
		dx=Len;
		for(;dy<Len;dy++){
			if(pAlignPage->GetBitFirstPickupFromTarget(X+dx,Y+dy)==IsPad && pAlignPage->GetBitPickupFromTarget(X+dx,Y+dy)==IsSilk){
				return true;
			}
		}
		dy=Len;
		for(;dx>-Len;dx--){
			if(pAlignPage->GetBitFirstPickupFromTarget(X+dx,Y+dy)==IsPad && pAlignPage->GetBitPickupFromTarget(X+dx,Y+dy)==IsSilk){
				return true;
			}
		}
		dx=-Len;
		for(;dy>-Len;dy--){
			if(pAlignPage->GetBitFirstPickupFromTarget(X+dx,Y+dy)==IsPad && pAlignPage->GetBitPickupFromTarget(X+dx,Y+dy)==IsSilk){
				return true;
			}
		}
	}
	return false;
}

int		StatisticImagerInLayer::SearchMasterArea(PureFlexAreaList *TArea,PureFlexAreaList *MArea,int ShiftX,int ShiftY,int TCnt,int MCnt)
{
	//?Å ?3?Åë?I?a?I?P?x?a?3?I?U?O?E?ÅE?e
	const int MinAreaSize=2;
	if(TArea->GetPatternByte()<=MinAreaSize){
		return -1;
	}

	int Ret;

	//Max/Min?IXY?A?W?A?Å‚?f?ÅE?e
	const int SearchDot=10;
	if(MArea->GetMinX()>TArea->GetMinX()+ShiftX-SearchDot
	&& MArea->GetMinX()<TArea->GetMinX()+ShiftX+SearchDot
	&& MArea->GetMinY()>TArea->GetMinY()+ShiftY-SearchDot
	&& MArea->GetMinY()<TArea->GetMinY()+ShiftY+SearchDot
	&& MArea->GetMaxX()>TArea->GetMaxX()+ShiftX-SearchDot
	&& MArea->GetMaxX()<TArea->GetMaxX()+ShiftX+SearchDot
	&& MArea->GetMaxY()>TArea->GetMaxY()+ShiftY-SearchDot
	&& MArea->GetMaxY()<TArea->GetMaxY()+ShiftY+SearchDot){
		return MCnt;
	}
	const int TooFar=50;
	bool IsTooFar1=false;
	bool IsTooFar2=false;
	PureFlexAreaList *NextMArea=MArea;
	PureFlexAreaList *PrevMArea=MArea;
	for(int i=1;IsTooFar1==false || IsTooFar2==false;i++){
		if(IsTooFar1==false){
			if(NextMArea->GetNext()!=NULL){
				NextMArea=NextMArea->GetNext();
				if(NextMArea->GetTopY()-TArea->GetTopY()>TooFar){
					IsTooFar1=true;
				}
				else{
					if(NextMArea->GetMinX()>TArea->GetMinX()+ShiftX-SearchDot
					&& NextMArea->GetMinX()<TArea->GetMinX()+ShiftX+SearchDot
					&& NextMArea->GetMinY()>TArea->GetMinY()+ShiftY-SearchDot
					&& NextMArea->GetMinY()<TArea->GetMinY()+ShiftY+SearchDot
					&& NextMArea->GetMaxX()>TArea->GetMaxX()+ShiftX-SearchDot
					&& NextMArea->GetMaxX()<TArea->GetMaxX()+ShiftX+SearchDot
					&& NextMArea->GetMaxY()>TArea->GetMaxY()+ShiftY-SearchDot
					&& NextMArea->GetMaxY()<TArea->GetMaxY()+ShiftY+SearchDot){
						return MCnt+i;
					}
				}
			}
			else{
				IsTooFar1=true;
			}
		}
		if(IsTooFar2==false){
			if(PrevMArea->GetPrev()!=NULL){
				PrevMArea=PrevMArea->GetPrev();
				if(TArea->GetTopY()-PrevMArea->GetTopY()>TooFar){
					IsTooFar2=true;
				}
				else{
					if(PrevMArea->GetMinX()>TArea->GetMinX()+ShiftX-SearchDot
					&& PrevMArea->GetMinX()<TArea->GetMinX()+ShiftX+SearchDot
					&& PrevMArea->GetMinY()>TArea->GetMinY()+ShiftY-SearchDot
					&& PrevMArea->GetMinY()<TArea->GetMinY()+ShiftY+SearchDot
					&& PrevMArea->GetMaxX()>TArea->GetMaxX()+ShiftX-SearchDot
					&& PrevMArea->GetMaxX()<TArea->GetMaxX()+ShiftX+SearchDot
					&& PrevMArea->GetMaxY()>TArea->GetMaxY()+ShiftY-SearchDot
					&& PrevMArea->GetMaxY()<TArea->GetMaxY()+ShiftY+SearchDot){
						return MCnt-i;
					}
				}
			}
			else{
				IsTooFar2=true;
			}
		}
	}
	return -1;
}

ExeResult	StatisticImagerInLayer::ExecutePreScanning(int ExeID ,ResultInLayerRoot *Res)
{
#ifdef DebugConsole
	//???O?I?v?a
	clock_t	StartTime,EndTime;
	StartTime=clock();
#endif

	//?X?L?????n???I?a??
	int CurrentMasterCnt=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);

	//DebugMode
	if(((StatisticImagerBase *)GetParentBase())->DebugMode==true && GetLayer()==0){
		//?a???d?U?Å˜
		if(CurrentMasterCnt==0){
			//?}?X?^?[?a???d?U?Å˜
			FormOperator	F((QWidget *)GetLayersBase()->GetMainWidget());
			F.ButtonPush(/**/"MainForm" ,/**/"AutoSaveMaster");
		}
		else{
			//?^?[?Q?b?g?a???d?U?Å˜
			FormOperator	F((QWidget *)GetLayersBase()->GetMainWidget());
			F.ButtonPush(/**/"MainForm" ,/**/"AutoSaveTarget");
		}
	}

	if(StatisticBuff==NULL){
		InitialAlloc();
	}

	//?P?X?L?????U?E?Q?X?L?????U?I?A?}?X?^?[?a???E?i?A?3?É ?a???E?I?A?o?I?ÅE
	if(CurrentMasterCnt<3){
		return _ER_true;
	}

	if(CurrentMasterCnt==3){
		//AutoAlignment?I?A?N?o?É 
		ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
		if(ABase!=NULL){
			AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
			if(APage!=NULL){
				pAlignPage=dynamic_cast<AutoAlignmentInPage *>(APage);
			}
		}
	}

#ifdef OldShaderEnabled
	return _ER_true;
#endif

/*
//////////////////////////////////////
	if(GetLayer()==0){
		//?A???C?????g?a?3?l?d?U?Å˜
		QFile	mfile("D:/?i?a?@???O?a??/ShiftXFromMasterInStatisticImager.dat");
		if(mfile.open(QIODevice::WriteOnly)==true){
			QTextStream mystream(&mfile);
			for(int y=0;y<AllocYLen;y++){
				for(int x=0;x<AllocXLen;x++){
					mystream << QString::number(pAlignPage->GetShiftXFromMaster(x,y));
					mystream << ",";
				}
				mystream << endl;
			}
			mfile.close();
		}
		QFile	mfileY("D:/?i?a?@???O?a??/ShiftYFromMasterInStatisticImager.dat");
		if(mfileY.open(QIODevice::WriteOnly)==true){
			QTextStream mystream(&mfileY);
			for(int y=0;y<AllocYLen;y++){
				for(int x=0;x<AllocXLen;x++){
					mystream << QString::number(pAlignPage->GetShiftYFromMaster(x,y));
					mystream << ",";
				}
				mystream << endl;
			}
			mfileY.close();
		}
	}
//////////////////////////////////////
*/
	//?}?X?N?I?a?d?a???ÅE?e
//	MaskBmp=GetMaskBitmap();
	MaskBmp=GetAutoMaskBitmap();

#ifdef Debug
	uint64	Sum;
	int		Cnt;
	int		x,y;
	bool	IsPad,IsSilk;
	BYTE	*ps;
	BYTE	*MBmp;
	int		X,Y;
	PixelStatisticInLayer	*d;
	BYTE	s;
#endif

	//?V?F?[?_?[?@?\???e
	if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
		if(CurrentMasterCnt==3){
			//?a??(Master)?I????
			if(MaskBmp!=NULL){
				//AutoAlignment???C?u?????c?c?c?Åí?h?b?g?d?a??
				CmdGetAutoAlignmentLibraryListPacket	packet(GetLayersBase());
				AlgorithmLibraryList *p=NULL;
				if(GetAutoAlignmentLibrary(&packet)==true){
					for(p=packet.AList.GetFirst();p!=NULL;p=p->GetNext()){
						break;
					}
				}
				if(p!=NULL){
					//???C?u?????I?Å˜?Å ?R?[?h?a?3?-?A?a???z?O???A?Å˜?Å ?A?Å·?e
					if(ABase!=NULL){
						AlgorithmLibraryLevelContainer	SrcLib(ABase);
						if(ABase->GetLibraryContainer()->GetLibrary(p->GetLibID(),SrcLib)==true){
							AutoAlignmentLibrary	*ALib=dynamic_cast<AutoAlignmentLibrary *>(SrcLib.GetLibrary());
							//?c?Åí?h?b?g
							if(ALib!=NULL){
								EnLargeDot=ALib->ExpandForPickup;
							}
						}
					}
				}

				//ResultBitFirstPickupFromMaster?I?R?s?[?d?i?e?iTmpMap?j
				int XByte	=(GetDotPerLine()+7)/8;
				int XLen	=GetDotPerLine();
				int YLen	=GetMaxLines();
				BYTE **TmpMap=MakeMatrixBuff(XByte,YLen);
				BYTE **TmpMap2=MakeMatrixBuff(XByte,YLen);
				MatrixBuffCopy(TmpMap,XByte,YLen
							 , (const BYTE **)pAlignPage->ResultBitFirstPickupFromMaster,XByte, YLen);
				//?c?Åí?h?b?g?a?A?u?k?3?1?e
				for(int i=0;i<EnLargeDot;i++){
					ThinArea(TmpMap,TmpMap2,XByte,YLen);
				}
				PickupFlexArea((BYTE **)TmpMap,XByte,XLen,YLen,MasterMaskBitmapFPack);
				//?}?X?^?[?a???d?v?Z
				GetLeastSquaresMethodM();
				//delete
				DeleteMatrixBuff(TmpMap,YLen);
				DeleteMatrixBuff(TmpMap2,YLen);
			}
		}
		//?a??(Target)?I????
		if(MaskBmp!=NULL){
			ExecutePreShader();
		}
	}

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteScanning(%d)?F%.2f?b\n",GetLayer(),(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
#endif

	return _ER_true;
}

ExeResult	StatisticImagerInLayer::ExecuteScanning	(int ExeID ,ResultInLayerRoot *Res)
{
#ifdef DebugConsole
	//???O?I?v?a
	clock_t	StartTime,EndTime;
	StartTime=clock();
#endif

	//?X?L?????n???I?a??
	int CurrentMasterCnt=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);

	//?P?X?L?????U?E?Q?X?L?????U?I?A?}?X?^?[?a???E?i?A?3?É ?a???E?I?A?o?I?ÅE
	if(CurrentMasterCnt<3){
		return _ER_true;
	}

	//?}?X?N?I?a?d?a???ÅE?e
//	MaskBmp=GetMaskBitmap();
	MaskBmp=GetAutoMaskBitmap();

#ifdef OldShaderEnabled
	ImageBuffer &TargetBuff=GetTargetBuff();
	double TMBrightCoef;

	//?V?F?[?_?[?@?\???e
	if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
		//?a??(Master)?I???I?P?x?d???s?e
		if(CurrentMasterCnt==3){
			ImageBuffer &MasterBuff=GetMasterBuff();
			if(MaskBmp!=NULL){
				uint64	Sum=0;
				int		Cnt=0;
				#pragma omp parallel
				{
					#pragma omp for reduction(+:Sum) reduction(+:Cnt)
					for(int y=0;y<AllocYLen;y+=2){
						BYTE	*ps=MasterBuff.GetY(y);
						BYTE	*MBmp=MaskBmp[y];
						for(int x=0;x<AllocXLen;x+=2){
							if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))!=0){
								Sum+=*(ps+x);
								Cnt++;
							}
						}
					}
				}
				MaskBmpCnt		=Cnt;
				MasterBrightAvg	=(double)Sum/MaskBmpCnt;
			}
		}

		//?a??(Target)?I???I?P?x?d???s?e
		if(MaskBmp!=NULL){
			uint64 Sum=0;
			#pragma omp parallel
			{
				#pragma omp for reduction(+:Sum)
				for(int y=0;y<AllocYLen;y+=2){
					BYTE	*MBmp=MaskBmp[y];
					for(int x=0;x<AllocXLen;x+=2){
						if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))!=0){
							int	X=x+pAlignPage->GetShiftXFromMaster(x,y);
							int	Y=y+pAlignPage->GetShiftYFromMaster(x,y);
							if(X<0){
								X=0;
							}
							else if(X>=AllocXLen){
								X=AllocXLen-1;
							}
							if(Y<0){
								Y=0;
							}
							else if(Y>=AllocYLen){
								Y=AllocYLen-1;
							}
							BYTE	*ps=TargetBuff.GetY(Y)+X;
							Sum+=(*ps);
						}
					}
				}
			}
			TargetBrightAvg=(double)Sum/MaskBmpCnt;
		}

		//Target?c?cMaster?O?I?P?x?I?ÅE?W???d?Z?o
		TMBrightCoef=MasterBrightAvg/TargetBrightAvg;
	}
	else{
		//?V?F?[?_?[?@?\?E?É 
		TMBrightCoef=1;
	}

	if(ExecuteInitialAfterEditFlag==false){
		//?e?s?N?Z???I?A?W?d?A???C?????g?a?3?A?E?u???i?1?d?É ?A?A?Å‚?I?s?N?Z???I?P?x?I
		//?u?A?Z?l?v?A?u?Q?a?a?v
		//?u?e?O???e?Åë?P?x?v?A?u?e?O?A?Åë?P?x?v
		//?u?n?O?U?E???e?Åë?P?x?v?A?u?n?O?U?E?A?Åë?P?x?v?d???s?e
		if(MaskBmp!=NULL){
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<AllocYLen;y++){
					PixelStatisticInLayer	*d=StatisticBuff[y];
					for(int x=0;x<AllocXLen;x++,d++){
						int	X=x+pAlignPage->GetShiftXFromMaster(x,y);
						int	Y=y+pAlignPage->GetShiftYFromMaster(x,y);
						if(X<0){
							X=0;
						}
						else if(X>=AllocXLen){
							X=AllocXLen-1;
						}
						if(Y<0){
							Y=0;
						}
						else if(Y>=AllocYLen){
							Y=AllocYLen-1;
						}
						BYTE	s=*(TargetBuff.GetY(Y)+X);
						s=Clip255(s*TMBrightCoef);
						d->Added+=s;
						d->Added2+=s*s;
						if(s>d->Lightest){
							d->Lighter	=d->Lightest;
							d->Lightest	=s;
						}
						else if(s>d->Lighter){
							d->Lighter=s;
						}
						if(s<d->Darkest){
							d->Darker	=d->Darkest;
							d->Darkest	=s;
						}
						else if(s<d->Darker){
							d->Darker=s;
						}
					}
				}
			}
		}
		StatisticBuffCount++;
	}
	return _ER_true;

#else

	//?V?F?[?_?[?@?\???e
	if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
		//?a??(Target)?I????
		if(MaskBmp!=NULL){
			//?^?[?Q?b?g?a???d?P?x?a?3
			CalcLeastSquaresMethodT();
			//Remove
			TargetMaskBitmapFPack.RemoveAll();
		}
	}

#ifdef Debug
	uint64	Sum;
	int		Cnt;
	int		x,y;
	bool	IsPad,IsSilk;
	BYTE	*ps;
	BYTE	*MBmp;
	int		X,Y;
	PixelStatisticInLayer	*d;
	BYTE	s;
#endif

	ImageBuffer &TargetBuff=GetTargetBuff();
	ImageBuffer &MasterBuff=GetMasterBuff();

	if(ExecuteInitialAfterEditFlag==false){
		//?e?s?N?Z???I?A?W?d?A???C?????g?a?3?A?E?u???i?1?d?É ?A?A?Å‚?I?s?N?Z???I?P?x?I
		//?u?A?Z?l?v?A?u?Q?a?a?v
		//?u?e?O???e?Åë?P?x?v?A?u?e?O?A?Åë?P?x?v
		//?u?n?O?U?E???e?Åë?P?x?v?A?u?n?O?U?E?A?Åë?P?x?v?d???s?e
		if(MaskBmp!=NULL){
#ifdef Debug
				for(y=0;y<AllocYLen;y++){
					d=StatisticBuff[y];
					for(x=0;x<AllocXLen;x++,d++){
						if(y==DebugPointY && x==DebugPointX){
							DebugPoint++;
						}
						IsPad	=pAlignPage->GetBitFirstPickupFromMaster(x,y);
						IsSilk	=pAlignPage->GetBitPickupFromMaster(x,y);
						X=x+pAlignPage->GetShiftXFromMaster(x,y);
						Y=y+pAlignPage->GetShiftYFromMaster(x,y);
#else
			#pragma omp parallel
			{
				#pragma omp for
				for(int y=0;y<AllocYLen;y++){
					PixelStatisticInLayer	*d=StatisticBuff[y];
					for(int x=0;x<AllocXLen;x++,d++){
						bool IsPad	=pAlignPage->GetBitFirstPickupFromMaster(x,y);
						bool IsSilk	=pAlignPage->GetBitPickupFromMaster(x,y);
						int	X=x+pAlignPage->GetShiftXFromMaster(x,y);
						int	Y=y+pAlignPage->GetShiftYFromMaster(x,y);
#endif
						if(X<0){
							X=0;
						}
						else if(X>=AllocXLen){
							X=AllocXLen-1;
						}
						if(Y<0){
							Y=0;
						}
						else if(Y>=AllocYLen){
							Y=AllocYLen-1;
						}
#ifndef Debug
						BYTE	s;
#endif
//						//?A???C?????g?a?I?`?F?b?N?ÅN?3?o?E?I
//						if(CheckTargetPoint(X,Y,IsPad,IsSilk)==false){
//							s=*(MasterBuff.GetY(y)+x);
///*
//							int	wX	=x-pAlignPage->GetShiftXFromTarget(X,Y);
//							Y		=y-pAlignPage->GetShiftYFromTarget(X,Y);
//							X		=wX;
//							if(CheckTargetPoint(X,Y,IsPad,IsSilk)==false){
//								X	=x+pAlignPage->GetShiftXFromMaster(x,y);
//								Y	=y+pAlignPage->GetShiftYFromMaster(x,y);
//							}
//*/
//						}
//						else{
							s=*(TargetBuff.GetY(Y)+X);
//						}

						d->Added+=s;
						d->Added2+=s*s;
						if(s>d->Lightest){
							d->Lighter	=d->Lightest;
							d->Lightest	=s;
						}
						else if(s>d->Lighter){
							d->Lighter=s;
						}
						if(s<d->Darkest){
							d->Darker	=d->Darkest;
							d->Darkest	=s;
						}
						else if(s<d->Darker){
							d->Darker=s;
						}
					}
				}
#ifndef Debug
			}
#endif
		}
		StatisticBuffCount++;
	}
#endif
/*	else{
		//?e?s?N?Z???I?A?W?d?A???C?????g?a?3?A?E?u???i?1?d?É ?A?A?Å‚?I?s?N?Z???I?P?x?I
		//?u?A?Z?l?v?A?u?Q?a?a?v
		//?u?n?O?U?E???e?Åë?P?x?v?A?u?n?O?U?E?A?Åë?P?x?v?d???s?e
		#pragma omp parallel
		{
			#pragma omp for
			for(int y=0;y<AllocYLen;y++){
				PixelStatisticInLayer	*d=StatisticBuff[y];
				for(int x=0;x<AllocXLen;x++,d++){
					bool IsPad	=pAlignPage->GetBitFirstPickupFromMaster(x,y);
					bool IsSilk	=pAlignPage->GetBitPickupFromMaster(x,y);
					int	X=x+pAlignPage->GetShiftXFromMaster(x,y);
					int	Y=y+pAlignPage->GetShiftYFromMaster(x,y);
					if(X<0){
						X=0;
					}
					else if(X>=AllocXLen){
						X=AllocXLen-1;
					}
					if(Y<0){
						Y=0;
					}
					else if(Y>=AllocYLen){
						Y=AllocYLen-1;
					}
					BYTE	s;
					//?A???C?????g?a?I?`?F?b?N
					if(CheckTargetPoint(X,Y,IsPad,IsSilk)==false){
						s=*(MasterBuff.GetY(y)+x);
					}
					else{
						s=*(TargetBuff.GetY(Y)+X);
					}
					s=Clip255(s);
					d->Added+=s;
					d->Added2+=s*s;
					if(s>d->Lightest){
						d->Lighter	=d->Lightest;
						d->Lightest	=s;
					}
					else if(s>d->Lighter){
						d->Lighter=s;
					}
					if(s<d->Darkest){
						d->Darker	=d->Darkest;
						d->Darkest	=s;
					}
					else if(s<d->Darker){
						d->Darker=s;
					}
				}
			}
		}
	}
*/

#ifdef DebugConsole
	EndTime=clock();
	printf(/**/"ExecuteScanning(%d)?F%.2f?b\n",GetLayer(),(double)(EndTime-StartTime)/CLOCKS_PER_SEC);
#endif

	return _ER_true;
}

ExeResult	StatisticImagerInLayer::ExecuteInitialAfterEdit(int ExeID 
															,ResultInLayerRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	if(GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1)!=99999999){
		return _ER_true;
	}
	if(ExecuteInitialAfterEditFlag==true){
		//?V?F?[?_?[?@?\???e
#ifdef OldShaderEnabled
		//AutoAlignment?I?A?N?o?É 
		if(pAlignPage==NULL){
			ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
			if(ABase!=NULL){
				AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
				if(APage!=NULL){
					pAlignPage=dynamic_cast<AutoAlignmentInPage *>(APage);
				}
			}
		}
		if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
			if(MaskBmpCnt==0){
				ImageBuffer &MasterBuff=GetMasterBuff();
				MaskBmp=GetAutoMaskBitmap();
				if(MaskBmp!=NULL){
					uint64	Sum=0;
					int		Cnt=0;
					#pragma omp parallel
					{
						#pragma omp for reduction(+:Sum) reduction(+:Cnt)
						for(int y=0;y<AllocYLen;y+=2){
							BYTE	*ps=MasterBuff.GetY(y);
							BYTE	*MBmp=MaskBmp[y];
							for(int x=0;x<AllocXLen;x+=2){
								if(MBmp!=NULL && (MBmp[x>>3]&(0x80>>(x&7)))!=0){
									Sum+=*(ps+x);
									Cnt++;
								}
							}
						}
					}
					MaskBmpCnt		=Cnt;
					MasterBrightAvg	=(double)Sum/MaskBmpCnt;
				}
			}
		}
		return _ER_true;
#endif
	}

	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<AllocYLen;y++){
			PixelStatisticInLayer	*d=StatisticBuff[y];
			for(int x=0;x<AllocXLen;x++,d++){
				//?e?O???e?Åë?P?x?A?e?O?A?Åë?P?x?d?o?-
				d->Added-=(d->Lightest+d->Darkest);
				//?e?O???e?Åë?P?x?I?Q?a?A?e?O?A?Åë?P?x?I?Q?a?d?o?-
				d->Added2-=(d->Lightest*d->Lightest+d->Darkest*d->Darkest);
			}
		}
	}
	//?e?O???e?Åë?I?A?e?O?A?Åë?I?d?o?Åë???I?A?A?Å‚?I?a?J?E???g?d?]?Q?ÅE?e
	StatisticBuffCount-=2;

	//ExecuteInitialAfterEdit?d?A?s?I?Y?t???O
	ExecuteInitialAfterEditFlag=true;

	return _ER_true;
}

ExeResult	StatisticImagerInLayer::ExecutePreProcessing(int ExeID ,ResultInLayerRoot *Res)
{
#ifdef OldShaderEnabled
	if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
		//?V?F?[?_?[?@?\???e
		ImageBuffer &TargetBuff=GetTargetBuff();

		//?X?L?????n???I?a??
		int CurrentMasterCnt=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);

		//?}?X?^?[?o?^?I?!???n?X?L???????I?Y?A?s
		if(CurrentMasterCnt>1 && CurrentMasterCnt==99999999){
			//?a??(Inspect)?I???I?P?x?d???s?e
			if(MaskBmp!=NULL){
				uint64 Sum=0;
				#pragma omp parallel
				{
					#pragma omp for reduction(+:Sum)
					for(int y=0;y<AllocYLen;y+=2){
						BYTE	*MBmp=MaskBmp[y];
						if(MBmp!=NULL){
							for(int x=0;x<AllocXLen;x+=2){
								if((MBmp[x>>3]&(0x80>>(x&7)))!=0){
									int	X=x+pAlignPage->GetShiftXFromMaster(x,y);
									int	Y=y+pAlignPage->GetShiftYFromMaster(x,y);
									if(X<0){
										X=0;
									}
									else if(X>=AllocXLen){
										X=AllocXLen-1;
									}
									if(Y<0){
										Y=0;
									}
									else if(Y>=AllocYLen){
										Y=AllocYLen-1;
									}
									BYTE	*ps=TargetBuff.GetY(Y)+X;
									Sum+=(*ps);
								}
							}
						}
					}
				}
				TargetBrightAvg=(double)Sum/MaskBmpCnt;

				//Target?c?cMaster?O?I?P?x?I?ÅE?W???d?Z?o
				double TMBrightCoef=MasterBrightAvg/TargetBrightAvg;

				//?a??(Inspect)?I???I?P?x?a?3?d?s??	?Å·?Å}?I?????d???A?c???Å ?Å‚?I?I
				#pragma omp parallel
				{
					#pragma omp for
					for(int y=0;y<AllocYLen;y++){
						for(int x=0;x<AllocXLen;x++){
							BYTE	*ps=TargetBuff.GetY(y)+x;
							*ps=Clip255((*ps)*TMBrightCoef);
						}
					}
				}
			}
		}
	}
#else
	//?V?F?[?_?[?@?\???e
	if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
		//?a??(Target)?I????
		if(MaskBmp!=NULL){
			//?^?[?Q?b?g?a???d?P?x?a?3
			CalcLeastSquaresMethodT();
			//Remove
			TargetMaskBitmapFPack.RemoveAll();
		}
	}
#endif
	return AlgorithmInLayerPLI::ExecutePreProcessing(ExeID ,Res);
}

void	StatisticImagerInLayer::ExecutePreShader()
{
	//ResultBitFirstPickupFromTarget?I?R?s?[?d?i?e?iTmpMap?j
	int XByte	=(GetDotPerLine()+7)/8;
	int XLen	=GetDotPerLine();
	int YLen	=GetMaxLines();
	BYTE **TmpMap=MakeMatrixBuff(XByte,YLen);
	BYTE **TmpMap2=MakeMatrixBuff(XByte,YLen);
	MatrixBuffCopy(TmpMap,XByte,YLen
				 , (const BYTE **)pAlignPage->ResultBitFirstPickupFromTarget,XByte, YLen);
	//?c?Åí?h?b?g?a?A?u?k?3?1?e
	for(int i=0;i<EnLargeDot;i++){
		ThinArea(TmpMap,TmpMap2,XByte,YLen);
	}
	PickupFlexArea((BYTE **)TmpMap,XByte,XLen,YLen,TargetMaskBitmapFPack);
	//?^?[?Q?b?g?a???d?v?Z
	GetLeastSquaresMethodT();
	//delete
	DeleteMatrixBuff(TmpMap,YLen);
	DeleteMatrixBuff(TmpMap2,YLen);
}

bool	StatisticImagerInLayer::MakeAverageImage(ImageBuffer &Dest)
{
	if(StatisticBuffCount<=LeastStatisticBuffCount){
		return false;
	}

	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int y=0;y<AllocYLen;y++){
			PixelStatisticInLayer	*s=StatisticBuff[y];
			BYTE					*d=Dest.GetY(y);
			for(int x=0;x<AllocXLen;x++){
				*d=s->GetAvr(StatisticBuffCount);
				d++;
				s++;
			}
		}
	}
	return true;
}

bool	StatisticImagerInLayer::MakeLightImage(ImageBuffer &Dest)
{
	if(StatisticBuffCount<=LeastStatisticBuffCount)
		return false;

	StatisticImagerBase	*BBase=(StatisticImagerBase *)GetParentBase();
	double	Gain=BBase->Gain;
	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int y=0;y<AllocYLen;y++){
			PixelStatisticInLayer	*s=StatisticBuff[y];
			BYTE					*d=Dest.GetY(y);
			for(int x=0;x<AllocXLen;x++){
//				*d=s->GetLight(StatisticBuffCount,Gain);	//D-20100208
				*d=s->Lighter;								//A-20100208
				d++;
				s++;
			}
		}
	}
	return true;
}

bool	StatisticImagerInLayer::MakeDarkImage(ImageBuffer &Dest)
{
	if(StatisticBuffCount<=LeastStatisticBuffCount)
		return false;

	StatisticImagerBase	*BBase=(StatisticImagerBase *)GetParentBase();
	double	Gain=BBase->Gain;
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<AllocYLen;y++){
			PixelStatisticInLayer	*s=StatisticBuff[y];
			BYTE					*d=Dest.GetY(y);
			for(int x=0;x<AllocXLen;x++){
//				*d=s->GetDark(StatisticBuffCount,Gain);	//D-20100208
				*d=s->Darker;							//A-20100208
				d++;
				s++;
			}
		}
	}
	return true;
}

bool	StatisticImagerInLayer::MakeDisorderImage(ImageBuffer &Dest)
{
	if(StatisticBuffCount<=LeastStatisticBuffCount)
		return false;

	#pragma omp parallel
	{                                                
		#pragma omp for
		for(int y=0;y<AllocYLen;y++){
			PixelStatisticInLayer	*s=StatisticBuff[y];
			BYTE					*d=Dest.GetY(y);
			for(int x=0;x<AllocXLen;x++){
				*d=s->GetDisorder(StatisticBuffCount);
				d++;
				s++;
			}
		}
	}
	return true;
}

bool    StatisticImagerInLayer::Save(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Save(f)==false)
		return false;

	if(::Save(f,AllocXLen)==false)
		return false;
	if(::Save(f,AllocYLen)==false)
		return false;
	for(int y=0;y<AllocYLen;y++){
		PixelStatisticInLayer	*p=StatisticBuff[y];
		if(f->write((char *)p,AllocXLen*sizeof(p[0]))!=AllocXLen*sizeof(p[0]))
			return false;
	}
	if(::Save(f,StatisticBuffCount)==false)
		return false;
	if(::Save(f,ExecuteInitialAfterEditFlag)==false)
		return false;
	return true;
}
bool    StatisticImagerInLayer::Load(QIODevice *f)
{
	if(AlgorithmInLayerPLI::Load(f)==false)
		return false;

	int	iAllocXLen;
	int	iAllocYLen;
	if(::Load(f,iAllocXLen)==false)
		return false;
	if(::Load(f,iAllocYLen)==false)
		return false;
	if(iAllocXLen!=AllocXLen || iAllocYLen!=AllocYLen){
		if(StatisticBuff!=NULL){
			for(int y=0;y<AllocYLen;y++){
				delete	[]StatisticBuff[y];
			}
			StatisticBuff=NULL;
		}
		AllocXLen=iAllocXLen;
		AllocYLen=iAllocYLen;
		if(AllocXLen!=0 && AllocYLen!=0){
			StatisticBuff	=new PixelStatisticInLayer*[AllocYLen];
			for(int y=0;y<AllocYLen;y++){
				StatisticBuff[y]=new PixelStatisticInLayer[AllocXLen];
			}
		}
	}
	for(int y=0;y<AllocYLen;y++){
		PixelStatisticInLayer	*p=StatisticBuff[y];
		if(f->read((char *)p,AllocXLen*sizeof(p[0]))!=AllocXLen*sizeof(p[0]))
			return false;
	}
	if(::Load(f,StatisticBuffCount)==false)
		return false;
	if(::Load(f,ExecuteInitialAfterEditFlag)==false)
		return false;

	return true;
}

void	StatisticImagerInLayer::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdMakeAverageStatistic	*CmdMakeAverageStatisticVar=dynamic_cast<CmdMakeAverageStatistic *>(packet);
	if(CmdMakeAverageStatisticVar!=NULL){
		MakeAverageImage(GetMasterBuff());
		return;
	}
	CmdLightImageStatistic	*CmdLightImageStatisticVar=dynamic_cast<CmdLightImageStatistic *>(packet);
	if(CmdLightImageStatisticVar!=NULL){
		int LayerNumb=CmdLightImageStatisticVar->CurrentLayerNumb;
		CmdLightImageStatisticVar->LightImageList[LayerNumb]=new ImageBuffer(0,CmdLightImageStatisticVar->XLen,CmdLightImageStatisticVar->YLen);
		if((CmdLightImageStatisticVar->IsLightImage=MakeLightImage(*(CmdLightImageStatisticVar->LightImageList[LayerNumb])))==false){
			delete CmdLightImageStatisticVar->LightImageList[LayerNumb];
			CmdLightImageStatisticVar->LightImageList[LayerNumb]=NULL;
		}
		return;
	}
	CmdDarkImageStatistic	*CmdDarkImageStatisticVar=dynamic_cast<CmdDarkImageStatistic *>(packet);
	if(CmdDarkImageStatisticVar!=NULL){
		int LayerNumb=CmdDarkImageStatisticVar->CurrentLayerNumb;
		CmdDarkImageStatisticVar->DarkImageList[LayerNumb]=new ImageBuffer(0,CmdDarkImageStatisticVar->XLen,CmdDarkImageStatisticVar->YLen);
		if((CmdDarkImageStatisticVar->IsDarkImage=MakeDarkImage(*(CmdDarkImageStatisticVar->DarkImageList[LayerNumb])))==false){
			delete CmdDarkImageStatisticVar->DarkImageList[LayerNumb];
			CmdDarkImageStatisticVar->DarkImageList[LayerNumb]=NULL;
		}
		return;
	}
	CmdDisorderImageStatistic	*CmdDisorderImageStatisticVar=dynamic_cast<CmdDisorderImageStatistic *>(packet);
	if(CmdDisorderImageStatisticVar!=NULL){
		int LayerNumb=CmdDisorderImageStatisticVar->CurrentLayerNumb;
		CmdDisorderImageStatisticVar->DisorderImageList[LayerNumb]=new ImageBuffer(0,CmdDisorderImageStatisticVar->XLen,CmdDisorderImageStatisticVar->YLen);
		if((CmdDisorderImageStatisticVar->IsDisorderImage=MakeDisorderImage(*(CmdDisorderImageStatisticVar->DisorderImageList[LayerNumb])))==false){
			delete CmdDisorderImageStatisticVar->DisorderImageList[LayerNumb];
			CmdDisorderImageStatisticVar->DisorderImageList[LayerNumb]=NULL;
		}
		return;
	}
	CmdAverageImageStatistic	*CmdAverageImageStatisticVar=dynamic_cast<CmdAverageImageStatistic *>(packet);
	if(CmdAverageImageStatisticVar!=NULL){
		int LayerNumb=CmdAverageImageStatisticVar->CurrentLayerNumb;
		CmdAverageImageStatisticVar->AverageImageList[LayerNumb]=new ImageBuffer(0,CmdAverageImageStatisticVar->XLen,CmdAverageImageStatisticVar->YLen);
		if((CmdAverageImageStatisticVar->IsAverageImage=MakeAverageImage(*(CmdAverageImageStatisticVar->AverageImageList[LayerNumb])))==false){
			delete CmdAverageImageStatisticVar->AverageImageList[LayerNumb];
			CmdAverageImageStatisticVar->AverageImageList[LayerNumb]=NULL;
		}
		return;
	}
	CmdStatisticBuff	*CmdStatisticBuffVar=dynamic_cast<CmdStatisticBuff *>(packet);
	if(CmdStatisticBuffVar!=NULL){
		CmdStatisticBuffVar->StatisticBuff=StatisticBuff;
		return;
	}
	CmdExecuteInitialAllocPacket	*CmdExecuteInitialAllocPacketVar=dynamic_cast<CmdExecuteInitialAllocPacket *>(packet);
	if(CmdExecuteInitialAllocPacketVar!=NULL){
		StatisticBuffCount=0;
		ExecuteInitialAfterEditFlag=false;
		InitialAlloc();
		return;
	}
}
//==============================================================

void	StatisticImagerInPage::DrawStatistic(QImage &pnt, IntList &LayerList ,int movx ,int movy ,double ZoomRate ,AlgorithmDrawAttr *Attr)
{
	StatisticImagerBase	*BBase=(StatisticImagerBase *)GetParentBase();
	StatisticImagerDrawAttr *attr=dynamic_cast<StatisticImagerDrawAttr *>(Attr);
	if(attr==NULL || attr->DrawMode==StatisticImagerDrawAttr::_None){
		AlgorithmInPagePLI::Draw(pnt, LayerList,movx ,movy ,ZoomRate ,Attr);
	}
	else if(attr->DrawMode==StatisticImagerDrawAttr::_Average){
		int	N			=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuffCount;
		/*if(N<=LeastStatisticBuffCount)*/
		if(N<LeastStatisticBuffCount)
			return;

		double	Z=1.0/ZoomRate;
		if(GetLayerNumb()==3){
			int	AllocXLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocXLen;
			int	AllocYLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocYLen;
			PixelStatisticInLayer	**Buff0=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuff;
			PixelStatisticInLayer	**Buff1=((StatisticImagerInLayer *)GetLayerData(1))->StatisticBuff;
			PixelStatisticInLayer	**Buff2=((StatisticImagerInLayer *)GetLayerData(2))->StatisticBuff;
			for(int y=0;y<pnt.height();y++){
				int	Y=y*Z-movy;
				QRgb	*d=(QRgb *)pnt.scanLine(y);
				if(0<=Y && Y<AllocYLen){
					PixelStatisticInLayer	*BuffY0=Buff0[Y];
					PixelStatisticInLayer	*BuffY1=Buff1[Y];
					PixelStatisticInLayer	*BuffY2=Buff2[Y];
					for(int x=0;x<pnt.width();x++){
						int	X=x*Z-movx;
						if(0<=X && X<AllocXLen){
							d[x]=qRgb(BuffY0[X].GetAvr(N),BuffY1[X].GetAvr(N),BuffY2[X].GetAvr(N));
						}
						else{
							d[x]=qRgb(0,0,0);
						}
					}
				}
				else{
					for(int x=0;x<pnt.width();x++){
						d[x]=qRgb(0,0,0);
					}
				}
			}
		}
	}
	else if(attr->DrawMode==StatisticImagerDrawAttr::_Light){
		int	N			=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuffCount;
		//if(N<=LeastStatisticBuffCount)
		if(N<LeastStatisticBuffCount)
			return;

		double	Z=1.0/ZoomRate;
		if(GetLayerNumb()==3){
			int	AllocXLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocXLen;
			int	AllocYLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocYLen;
			double	Gain	=BBase->Gain;
			PixelStatisticInLayer	**Buff0=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuff;
			PixelStatisticInLayer	**Buff1=((StatisticImagerInLayer *)GetLayerData(1))->StatisticBuff;
			PixelStatisticInLayer	**Buff2=((StatisticImagerInLayer *)GetLayerData(2))->StatisticBuff;
			for(int y=0;y<pnt.height();y++){
				int	Y=y*Z-movy;
				QRgb	*d=(QRgb *)pnt.scanLine(y);
				if(0<=Y && Y<AllocYLen){
					PixelStatisticInLayer	*BuffY0=Buff0[Y];
					PixelStatisticInLayer	*BuffY1=Buff1[Y];
					PixelStatisticInLayer	*BuffY2=Buff2[Y];
					for(int x=0;x<pnt.width();x++){
						int	X=x*Z-movx;
						if(0<=X && X<AllocXLen){
//							d[x]=qRgb(BuffY0[X].GetLight(N,Gain)
//									 ,BuffY1[X].GetLight(N,Gain)
//									 ,BuffY2[X].GetLight(N,Gain));	//D-20100208
							d[x]=qRgb(BuffY0[X].Lighter
									 ,BuffY1[X].Lighter
									 ,BuffY2[X].Lighter);			//A-20100208
						}
						else{
							d[x]=qRgb(0,0,0);
						}
					}
				}
				else{
					for(int x=0;x<pnt.width();x++){
						d[x]=qRgb(0,0,0);
					}
				}
			}
		}
	}
	else if(attr->DrawMode==StatisticImagerDrawAttr::_Dark){
		int	N			=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuffCount;
		//if(N<=LeastStatisticBuffCount)
		if(N<LeastStatisticBuffCount)
			return;

		double	Z=1.0/ZoomRate;
		if(GetLayerNumb()==3){
			int	AllocXLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocXLen;
			int	AllocYLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocYLen;
			double	Gain	=BBase->Gain;
			PixelStatisticInLayer	**Buff0=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuff;
			PixelStatisticInLayer	**Buff1=((StatisticImagerInLayer *)GetLayerData(1))->StatisticBuff;
			PixelStatisticInLayer	**Buff2=((StatisticImagerInLayer *)GetLayerData(2))->StatisticBuff;
			for(int y=0;y<pnt.height();y++){
				int	Y=y*Z-movy;
				QRgb	*d=(QRgb *)pnt.scanLine(y);
				if(0<=Y && Y<AllocYLen){
					PixelStatisticInLayer	*BuffY0=Buff0[Y];
					PixelStatisticInLayer	*BuffY1=Buff1[Y];
					PixelStatisticInLayer	*BuffY2=Buff2[Y];
					for(int x=0;x<pnt.width();x++){
						int	X=x*Z-movx;
						if(0<=X && X<AllocXLen){
//							d[x]=qRgb(BuffY0[X].GetDark(N,Gain)
//									 ,BuffY1[X].GetDark(N,Gain)
//									 ,BuffY2[X].GetDark(N,Gain));	//D-20100208
							d[x]=qRgb(BuffY0[X].Darker
									 ,BuffY1[X].Darker
									 ,BuffY2[X].Darker);			//A-20100208
						}
						else{
							d[x]=qRgb(0,0,0);
						}
					}
				}
				else{
					for(int x=0;x<pnt.width();x++){
						d[x]=qRgb(0,0,0);
					}
				}
			}
		}
	}
	else if(attr->DrawMode==StatisticImagerDrawAttr::_Disorder){
		int	N			=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuffCount;
		//if(N<=LeastStatisticBuffCount)
		if(N<LeastStatisticBuffCount)
			return;

		double	Z=1.0/ZoomRate;
		if(GetLayerNumb()==3){
			int	AllocXLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocXLen;
			int	AllocYLen	=((StatisticImagerInLayer *)GetLayerData(0))->AllocYLen;
			PixelStatisticInLayer	**Buff0=((StatisticImagerInLayer *)GetLayerData(0))->StatisticBuff;
			PixelStatisticInLayer	**Buff1=((StatisticImagerInLayer *)GetLayerData(1))->StatisticBuff;
			PixelStatisticInLayer	**Buff2=((StatisticImagerInLayer *)GetLayerData(2))->StatisticBuff;
			for(int y=0;y<pnt.height();y++){
				int	Y=y*Z-movy;
				QRgb	*d=(QRgb *)pnt.scanLine(y);
				if(0<=Y && Y<AllocYLen){
					PixelStatisticInLayer	*BuffY0=Buff0[Y];
					PixelStatisticInLayer	*BuffY1=Buff1[Y];
					PixelStatisticInLayer	*BuffY2=Buff2[Y];
					for(int x=0;x<pnt.width();x++){
						int	X=x*Z-movx;
						if(0<=X && X<AllocXLen){
							d[x]=qRgb(BuffY0[X].GetDisorder(N)
									 ,BuffY1[X].GetDisorder(N)
									 ,BuffY2[X].GetDisorder(N));
						}
						else{
							d[x]=qRgb(0,0,0);
						}
					}
				}
				else{
					for(int x=0;x<pnt.width();x++){
						d[x]=qRgb(0,0,0);
					}
				}
			}
		}
	}
}

void	StatisticImagerInPage::DarkImageStatistic()
{
}
/*
//???I?P?x?a?3?i?}?X?^?[?a???j
bool	StatisticImagerInPage::GetAverageBrightnessCorrectionM()
{
#ifdef Debug
	DynamicClassifyItem	*pDynamicClassifyItem;
	AlgorithmLibraryList *p;
#endif

	//DynamicClassify?IItem?d?a???ÅE?e
	AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase("Basic","DynamicClassify");
	if(ABase!=NULL){
		AlgorithmInPageRoot	*APageRoot=ABase->GetPageData(GetPage());
		if(APageRoot!=NULL){
			AlgorithmInPagePI	*APage=dynamic_cast<AlgorithmInPagePI *>(APageRoot);
			if(APage!=NULL){
				int ItemCount=APage->GetItemCount();
				for(int i=0;i<ItemCount;i++){
#ifdef Debug
					pDynamicClassifyItem						=dynamic_cast<DynamicClassifyItem *>(APage->GetItem(i));
#else
					DynamicClassifyItem	*pDynamicClassifyItem	=dynamic_cast<DynamicClassifyItem *>(APage->GetItem(i));
#endif
					if(pDynamicClassifyItem!=NULL){
						//?I?a?d?u?k?ÅE?e

						//?I?a?I???I?P?x?d???s?e
					}
				}
			}
		}
	}
}
*/
void	StatisticImagerInPage::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdMakeAverageStatistic	*CmdMakeAverageStatisticVar=dynamic_cast<CmdMakeAverageStatistic *>(packet);
	if(CmdMakeAverageStatisticVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdLightImageStatistic	*CmdLightImageStatisticVar=dynamic_cast<CmdLightImageStatistic *>(packet);
	if(CmdLightImageStatisticVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			CmdLightImageStatisticVar->CurrentLayerNumb=layer;
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdDarkImageStatistic	*CmdDarkImageStatisticVar=dynamic_cast<CmdDarkImageStatistic *>(packet);
	if(CmdDarkImageStatisticVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			CmdDarkImageStatisticVar->CurrentLayerNumb=layer;
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdDisorderImageStatistic	*CmdDisorderImageStatisticVar=dynamic_cast<CmdDisorderImageStatistic *>(packet);
	if(CmdDisorderImageStatisticVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			CmdDisorderImageStatisticVar->CurrentLayerNumb=layer;
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdAverageImageStatistic	*CmdAverageImageStatisticVar=dynamic_cast<CmdAverageImageStatistic *>(packet);
	if(CmdAverageImageStatisticVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			CmdAverageImageStatisticVar->CurrentLayerNumb=layer;
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
	CmdStatisticBuff	*CmdStatisticBuffVar=dynamic_cast<CmdStatisticBuff *>(packet);
	if(CmdStatisticBuffVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		//GetLayerData(0)->TransmitDirectly(packet);
		return;
	}
	CmdExecuteInitialAllocPacket	*CmdExecuteInitialAllocPacketVar=dynamic_cast<CmdExecuteInitialAllocPacket *>(packet);
	if(CmdExecuteInitialAllocPacketVar!=NULL){
		for(int layer=0;layer<GetLayerNumb();layer++){
			GetLayerData(layer)->TransmitDirectly(packet);
		}
		return;
	}
}

ExeResult	StatisticImagerInPage::ExecutePreScanning(int ExeID ,ResultInPageRoot *Res)
{
#ifdef OldShaderEnabled
	return AlgorithmInPagePLI::ExecutePreScanning(ExeID ,Res);
#endif

	ExeResult	Ret=AlgorithmInPagePLI::ExecutePreScanning(ExeID ,Res);
/*
	if(GetLayerNumb()==1){
		((StatisticImagerInLayer *)GetLayerDataPLI(0))->ExecutePreScanning(&((ResultInPagePLI *)Res)->GetLayerData(0),pInspectionData);
	}
	else if(GetLayerNumb()==3){
		#pragma omp parallel
		{
			#pragma omp for
			for(int layer=0;layer<3;layer++){
				((StatisticImagerInLayer *)GetLayerDataPLI(layer))->ExecutePreScanning(&((ResultInPagePLI *)Res)->GetLayerData(layer),pInspectionData);
			}
		}
	}
*/
	//?P?x?a?3?ÅE?e?c?C???c?I?Å‚?f
	ExecuteDoShader();

	return Ret;
}

ExeResult	StatisticImagerInPage::ExecuteScanning(int ExeID ,ResultInPageRoot *Res)
{
	ExeResult	Ret=AlgorithmInPagePLI::ExecuteScanning(ExeID ,Res);
/*
	if(GetLayerNumb()==1){
		((StatisticImagerInLayer *)GetLayerDataPLI(0))->ExecuteScanning(&((ResultInPagePLI *)Res)->GetLayerData(0),pInspectionData);
	}
	else if(GetLayerNumb()==3){
		#pragma omp parallel
		{
			#pragma omp for
			for(int layer=0;layer<3;layer++){
				((StatisticImagerInLayer *)GetLayerDataPLI(layer))->ExecuteScanning(&((ResultInPagePLI *)Res)->GetLayerData(layer),pInspectionData);
			}
		}
	}
*/
	return Ret;
}

ExeResult	StatisticImagerInPage::ExecuteInitialAfterEdit(int ExeID 
															,ResultInPageRoot *Res
															,ExecuteInitialAfterEditInfo &EInfo)
{
	ExeResult	Ret=AlgorithmInPagePLI::ExecuteInitialAfterEdit(ExeID ,Res,EInfo);

	//phase?I??
	/*if(GetGlobalPage()==GetPageNumb()-1){
		if(GetPhaseNumb()>=2){
			int CurrentPhase=GetLayersBase()->GetCurrentPhase();
			if((CurrentPhase+1)==GetPhaseNumb()){
				GetLayersBase()->SetCurrentPhase(0);
			}
			else{
				GetLayersBase()->SetCurrentPhase(CurrentPhase+1);
			}
		}
	}*/

	return Ret;
}

ExeResult	StatisticImagerInPage::ExecutePreAlignment(int ExeID ,ResultInPageRoot *Res)
{
	//?X?L?????n???I?a??
	int CurrentMasterCnt=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);

	//?}?X?^?[?o?^?I?!???n?X?L???????I?Y?A?s
	if(CurrentMasterCnt>1 && CurrentMasterCnt!=99999999){
		AlgorithmBase	*ABase=GetLayersBase()->GetAlgorithmBase(/**/"Basic",/**/"AutoAlignment");
		if(ABase!=NULL){
			AlgorithmInPageRoot	*APage=ABase->GetPageData(GetPage());
			if(APage!=NULL){
				CmdAutoAlignmentNoAdjustPacket	CmdAutoAlignmentNoAdjustInst(GetLayersBase());
				APage->TransmitDirectly(&CmdAutoAlignmentNoAdjustInst);
			}
		}
	}
	else{
		//DebugMode
		if(((StatisticImagerBase *)GetParentBase())->DebugMode==true){
			if(CurrentMasterCnt>1){
				//???ÅC?a???d?U?Å˜
				FormOperator	F((QWidget *)GetLayersBase()->GetMainWidget());
				F.ButtonPush(/**/"MainForm" ,/**/"AutoSaveInspect");
			}
		}
	}
	return AlgorithmInPagePLI::ExecutePreAlignment(ExeID ,Res);
}

ExeResult	StatisticImagerInPage::ExecutePreProcessing(int ExeID ,ResultInPageRoot *Res)
{
#ifdef OldShaderEnabled
	return AlgorithmInPagePLI::ExecutePreProcessing(ExeID ,Res);
#endif

	//?V?F?[?_?[?@?\???e
	if(((StatisticImagerBase *)GetParentBase())->ShaderEnabled==true){
		//?X?L?????n???I?a??
		int CurrentMasterCnt=GetLayersBase()->GetAnyData()->ToInt(/**/"CurrentMasterCounter",-1);

		//???ÅC???I?Y?A?s
		if(CurrentMasterCnt==99999999){
			//?^?[?Q?b?g?a???P?x?a?3?O????
			if(GetLayerNumb()==1){
				((StatisticImagerInLayer *)GetLayerDataPLI(0))->ExecutePreShader();
			}
			else if(GetLayerNumb()==3){
				#pragma omp parallel
				{
					#pragma omp for
					for(int layer=0;layer<3;layer++){
						((StatisticImagerInLayer *)GetLayerDataPLI(layer))->ExecutePreShader();
					}
				}
			}
			//?P?x?a?3?ÅE?e?c?C???c?I?Å‚?f
			ExecuteDoShader();

			if(GetLayerNumb()==1){
				((StatisticImagerInLayer *)GetLayerDataPLI(0))->ExecutePreProcessing(ExeID ,&((ResultInPagePLI *)Res)->GetLayerData(0));
			}
			else if(GetLayerNumb()==3){
				#pragma omp parallel
				{
					#pragma omp for
					for(int layer=0;layer<3;layer++){
						((StatisticImagerInLayer *)GetLayerDataPLI(layer))->ExecutePreProcessing(ExeID ,&((ResultInPagePLI *)Res)->GetLayerData(layer));
					}
				}
			}
		}
	}
	else{
		return AlgorithmInPagePLI::ExecutePreProcessing(ExeID ,Res);
	}

	return _ER_true;
}

void	StatisticImagerInPage::ExecuteDoShader()
{
	bool ShaderEnabled=((StatisticImagerBase *)GetParentBase())->ShaderEnabled;
	if(ShaderEnabled==true){
		int SumNumb=((StatisticImagerInLayer *)GetLayerDataPLI(0))->GetTargetMaskBitmapFPack().GetNumber();
		for(int Cnt=0;Cnt<SumNumb;Cnt++){
			int layer;
			for(layer=0;layer<GetLayerNumb();layer++){
				if(((StatisticImagerInLayer *)GetLayerDataPLI(layer))->GetTLeastSquaresMethodTable(Cnt).EnableShader==false){
					break;
				}
			}
			if(layer<GetLayerNumb()){
				for(layer=0;layer<GetLayerNumb();layer++){
					((StatisticImagerInLayer *)GetLayerDataPLI(layer))->GetTLeastSquaresMethodTable(Cnt).EnableShader=false;
				}
			}
		}
	}
}

//==============================================================
StatisticImagerBase::StatisticImagerBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	Gain=2.0;
	AutoMakeAverageImage=true;
	AlignmentScanMergin	=80;
	DebugMode			=false;
	ShaderEnabled		=false;
	BrightCoef			=0.2;

	SetParam(&Gain					, /**/"Setting" ,/**/"Gain"					,LangSolver.GetString(XStatisticImager_LS,LID_1)/*"Gain for light/dark"*/);
	SetParam(&AutoMakeAverageImage	, /**/"Setting" ,/**/"AutoMakeAverageImage"	,LangSolver.GetString(XStatisticImager_LS,LID_3)/*"True in making automatic average image"*/);
	SetParam(&AlignmentScanMergin	, /**/"Setting" ,/**/"AlignmentScanMergin"	,LangSolver.GetString(XStatisticImager_LS,LID_4)/*"Mergin for alignment piece"*/);
	SetParam(&DebugMode				, /**/"Setting" ,/**/"DebugMode"			,LangSolver.GetString(XStatisticImager_LS,LID_5)/*"Manual inspection for debug"*/);
	SetParam(&ShaderEnabled			, /**/"Setting" ,/**/"ShaderEnabled"		,LangSolver.GetString(XStatisticImager_LS,LID_6)/*"By checked state, shader is enabled"*/);
	SetParam(&BrightCoef			, /**/"Setting" ,/**/"BrightCoef"			,LangSolver.GetString(XStatisticImager_LS,LID_7)/*"Shading Bright Coef"*/);

#ifdef DebugConsole
	FILE *fp;
	AllocConsole();
	freopen_s(&fp,/**/"CON",/**/"w",stdout);
///	printf("?Å}?n?E???I\n");
#endif
}

AlgorithmDrawAttr	*StatisticImagerBase::CreateDrawAttr(void)
{
	return new StatisticImagerDrawAttr();
}

ExeResult	StatisticImagerBase::ExecutePreScanning(int ExeID ,ResultBaseForAlgorithmRoot *Res)
{
	int CurrentStrategicNumber=GetLayersBase()->GetCurrentStrategicNumber();
	GetLayersBase()->PopCurrentStrategicNumberForCalc();

	ExeResult	Ret=AlgorithmBase::ExecutePreScanning(ExeID ,Res);

	return Ret;
}

ExeResult	StatisticImagerBase::ExecuteInitialAfterEdit(int ExeID 
														,ResultBaseForAlgorithmRoot *Res
														,ExecuteInitialAfterEditInfo &EInfo)
{
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ResultBasePhase		*Ph=Res->GetPageDataPhase(phase);
		for(int page=0;page<GetPageNumb();page++){
			GetPageDataPhase(phase)->GetPageData(page)->ExecuteInitialAfterEdit(ExeID ,Ph->GetPageData(page),EInfo);
		}
	}
	return _ER_true;
}

void	StatisticImagerBase::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdDrawStatistic	*CmdDrawStatisticVar=dynamic_cast<CmdDrawStatistic *>(packet);
	if(CmdDrawStatisticVar!=NULL){
		StatisticImagerInPage	*P=(StatisticImagerInPage *)GetPageData(CmdDrawStatisticVar->LocalPage);
		IntList LayerList;
		StatisticImagerDrawAttr	DAttr;
		DAttr.DrawMode	=CmdDrawStatisticVar->DrawMode;
		P->DrawStatistic(*CmdDrawStatisticVar->Image ,LayerList
				,CmdDrawStatisticVar->Movx ,CmdDrawStatisticVar->Movy ,CmdDrawStatisticVar->ZoomRate
				,&DAttr);
		return;
	}
	CmdMakeAverageStatistic	*CmdMakeAverageStatisticVar=dynamic_cast<CmdMakeAverageStatistic *>(packet);
	if(CmdMakeAverageStatisticVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
	CmdAutoMakeAverageStatistic	*CmdAutoMakeAverageStatisticVar=dynamic_cast<CmdAutoMakeAverageStatistic *>(packet);
	if(CmdAutoMakeAverageStatisticVar!=NULL){
		if(AutoMakeAverageImage==true){
			CmdMakeAverageStatistic	RCmd(GetLayersBase());
			for(int page=0;page<GetPageNumb();page++){
				GetPageData(page)->TransmitDirectly(&RCmd);
			}
		}
		return;
	}
	CmdLightImageStatistic	*CmdLightImageStatisticVar=dynamic_cast<CmdLightImageStatistic *>(packet);
	if(CmdLightImageStatisticVar!=NULL){
		GetPageData(CmdLightImageStatisticVar->CurrentPageNumb)->TransmitDirectly(packet);
		return;
	}
	CmdDarkImageStatistic	*CmdDarkImageStatisticVar=dynamic_cast<CmdDarkImageStatistic *>(packet);
	if(CmdDarkImageStatisticVar!=NULL){
		GetPageData(CmdDarkImageStatisticVar->CurrentPageNumb)->TransmitDirectly(packet);
		return;
	}
	CmdDisorderImageStatistic	*CmdDisorderImageStatisticVar=dynamic_cast<CmdDisorderImageStatistic *>(packet);
	if(CmdDisorderImageStatisticVar!=NULL){
		GetPageData(CmdDisorderImageStatisticVar->CurrentPageNumb)->TransmitDirectly(packet);
		return;
	}
	CmdAverageImageStatistic	*CmdAverageImageStatisticVar=dynamic_cast<CmdAverageImageStatistic *>(packet);
	if(CmdAverageImageStatisticVar!=NULL){
		GetPageData(CmdAverageImageStatisticVar->CurrentPageNumb)->TransmitDirectly(packet);
		return;
	}
	CmdStatisticBuff	*CmdStatisticBuffVar=dynamic_cast<CmdStatisticBuff *>(packet);
	if(CmdStatisticBuffVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
	CmdGetAutoAlignmentLibraryListPacket	*AListPacket=dynamic_cast<CmdGetAutoAlignmentLibraryListPacket *>(packet);
	if(AListPacket!=NULL){
		if(AListPacket->LibFolderID==-1){
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->AList);
		}
		else{
			GetLibraryContainer()->EnumLibrary(GetLibType(),AListPacket->LibFolderID,AListPacket->AList);
		}
		return;
	}
	CmdExecuteInitialAllocPacket	*CmdExecuteInitialAllocPacketVar=dynamic_cast<CmdExecuteInitialAllocPacket *>(packet);
	if(CmdExecuteInitialAllocPacketVar!=NULL){
		for(int page=0;page<GetPageNumb();page++){
			GetPageData(page)->TransmitDirectly(packet);
		}
		return;
	}
}
