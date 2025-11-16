#include <cmath>
#include "XPickupPad.h"
#include "XPointer.h"
#include "XFlexArea.h"
#include "XImageProcess.h"
#include "XMainSchemeMemory.h"
#include "swap.h"

static	int	MakeColorCenterInside(int BrListSum[256],int	ColSeparation);

int	MakeColorCenter(int BrList[256])
//	輝度リストの２つのピークの中央値を求める
{
	int BrListSum[256];
	int	ColSeparation=10;

	//ノイズを除去するために近隣を加算する
	int	N=5;
	for(int i=0;i<256;i++){
		BrListSum[i]=BrList[i];
		for(int j=1;j<N;j++){
			if(i+j<256){
				BrListSum[i]+=BrList[i+j];
			}
			else{
				BrListSum[i]+=BrList[255];
			}
		}
	}

	int	H1=MakeColorCenterInside(BrListSum,ColSeparation);
	int	H2=MakeColorCenterInside(BrListSum,ColSeparation);
	int	H3=MakeColorCenterInside(BrListSum,ColSeparation);

	if(BrList[H3]>100 || (BrList[H3]>20 && BrList[H3]>BrList[H2]/5)){
		if(H3>H1 && H3>H2){
			int	MaxH12=max(H1,H2);
			if(abs(H2-H1)<abs(H3-MaxH12)){
				return (H3+MaxH12)/2-N/2;
			}
		}
		if(H3<H1 && H3<H2){
			int	MinH12=min(H1,H2);
			if(abs(H2-H1)<abs(H3-MinH12)){
				return (H3+MinH12)/2-N/2;
			}
		}
	}
	return (H1+H2)/2-N/2;
}

int	MakeColorCenterInside(int BrListSum[256],int	ColSeparation)
{
	int	MaxC=0;
	int	MaxPos=0;
	for(int i=0;i<256;i++){
		if(MaxC<BrListSum[i]){
			MaxC=BrListSum[i];
			MaxPos=i;
		}
	}
	if(MaxC==0){
		return 0;
	}
	int t1;
	for(t1=MaxPos-1;t1>0;t1--){
		if(BrListSum[t1]!=BrListSum[MaxPos]){
			break;
		}
	}
	int t2;
	for(t2=MaxPos+1;t2<256;t2++){
		if(BrListSum[t2]!=BrListSum[MaxPos]){
			break;
		}
	}
	if(t1<0){
		t1=0;
	}
	if(t2>=256){
		t2=255;
	}
	int	H1=(t1+t2)/2;

	int	k1;
	for(k1=t1-1;k1>0;k1--){
		if(BrListSum[k1]>BrListSum[k1+1]){
			k1++;
			break;
		}
	}
	int	k2;
	for(k2=t2+1;k2<256;k2--){
		if(BrListSum[k2]>BrListSum[k2-1]){
			k2++;
			break;
		}
	}

	if(H1-t1<ColSeparation){
		k1=t1-ColSeparation;
	}
	if(k2-H1<ColSeparation){
		k2=t2+ColSeparation;
	}
	if(k1<0){
		k1=0;
	}
	if(k2>=256){
		k2=255;
	}
	for(int i=k1;i<=k2;i++){
		BrListSum[i]=0;
	}

	return H1;
}

bool	GetPadFromImage(ImageBuffer &Img
						,FlexArea &SurroundArea
						,FlexArea &PadArea)
{
	int BrList[256];
	int	XLen=SurroundArea.GetWidth();
	int	YLen=SurroundArea.GetHeight();

	int	XBitLen	=XLen+2;
	int	YBitLen	=YLen+2;
	int	XByte	=(XBitLen+7)/8+1;
	BYTE	**RMap=MakeMatrixBuff(XByte,YBitLen);
	int	Mx=SurroundArea.GetMinX();
	int	My=SurroundArea.GetMinY();

	int	XNumb;
	int	YNumb;
	if(XLen>400 && YLen>400){
		for(int	Cell=100;Cell>=5;Cell/=2){
			XNumb=(XLen-Cell-1)/Cell;
			YNumb=(YLen-Cell-1)/Cell;
			if(XNumb>=2 && YNumb>=2){
				break;
			}
		}
	}
	else{
		XNumb=1;
		YNumb=1;
	}
	int	XCell=XLen/XNumb;
	int	YCell=YLen/YNumb;

	MatrixBuffClear(RMap,0,XByte,YBitLen);
	for(int yn=0;yn<YNumb;yn++){
		for(int xn=0;xn<XNumb;xn++){
			for(int i=0;i<sizeof(BrList)/sizeof(BrList[0]);i++){
				BrList[i]=0;
			}
			FlexArea	A=SurroundArea;
			A.ClipArea(Mx+xn*XCell,My+yn*YCell,Mx+(xn+1)*XCell,My+(yn+1)*YCell);
			A.MakeBrightList(BrList ,Img.GetWidth(),Img.GetHeight(),Img ,0,0);

			int	Col=MakeColorCenter(BrList);
			for(int i=0;i<A.GetFLineLen();i++){
				int	x1	=A.GetFLineLeftX(i);
				int	Numb=A.GetFLineNumb(i);
				int	y	=A.GetFLineAbsY(i);
				BYTE	*s=Img.GetY(y)+x1;
				int	ky=y-My+1;
				for(int x=0;x<Numb;x++){
					if(*s>=Col){
						int	kx=x1+x-Mx+1;
						SetBmpBit1(RMap,kx,ky);
					}
					s++;
				}
			}
		}
	}
	PureFlexAreaListContainer FPack;
	PickupFlexArea(RMap ,XByte ,XBitLen,YBitLen ,FPack);
	PureFlexAreaList	*MaxAreaPoint=NULL;
	int64				MaxDots=0;
	for(PureFlexAreaList *p=FPack.GetFirst();p!=NULL;p=p->GetNext()){
		int64	Dots=p->GetPatternByte();
		if(Dots>MaxDots){
			MaxDots=Dots;
			MaxAreaPoint=p;
		}
	}
	DeleteMatrixBuff(RMap ,YBitLen);
	if(MaxAreaPoint!=NULL){
		PadArea=*MaxAreaPoint;
		PadArea.MoveToNoClip(Mx,My);
		return true;
	}
	return false;
}
