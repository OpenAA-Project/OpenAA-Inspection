#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "ImageControlTools.h"
#include "XDLLOnly.h"
#include "XGUI.h"
#include "XPointer.h"
#include "XDotColorMatchingLibrary.h"
#include "XDisplayBitImage.h"
#include "XImageProcess.h"
#include <omp.h>
#include "XMaskingFromGeneral.h"
#include "XUndo.h"
#include "XPropertyDotColorMatchingPacket.h"
#include "XDotColorMatchingAlgoPacket.h"
#include "XDisplaySimPanel.h"
#include "swap.h"
#include "XLearningRegist.h"


class ScratchDivTable
{
public:
	double	MulTable[4000];

	ScratchDivTable();
};

ScratchDivTable::ScratchDivTable()
{
	for(int i=0;i<sizeof(MulTable)/sizeof(MulTable[0]);i++){
		if(i>=3){
			MulTable[i]=1.0/(double)i;
		}
		else{
			MulTable[i]=0.0;
		}
	}

}

static	ScratchDivTable	ScratchDivTableDim;

		//hw3z9785

void	DotColorMatchingItem::InitialScratch(ImageBuffer *ImageMasterList[])
{
	ScratchCounter	=0;
	int	W=GetArea().GetWidth();
	int	H=GetArea().GetHeight();
	ScratchTableDimLen=ceil(hypot(W,H));
	if(ScratchTableDim!=NULL){
		delete	[]ScratchTableDim;
	}
	ScratchTableDim=new struct	ScratchTable[ScratchTableDimLen];

	if(ScratchTableMasterDim!=NULL){
		delete	[]ScratchTableMasterDim;
	}
	ScratchTableMasterDim=new struct	ScratchTable[ScratchTableDimLen];

	ScratchMasterAverage=-1;
	ScratchLayer=-1;
	double	DAvr[1000];
	for(int layer=0;layer<GetLayerNumb();layer++){
		double	d=GetArea().GetAverage(*ImageMasterList[layer],0,0);
		DAvr[layer]=d;
	}
	bool	AllBright=true;
	for(int layer=0;layer<GetLayerNumb();layer++){
		if(DAvr[layer]<200.0){
			AllBright=false;
		}
	}
	if(AllBright==true){
		double	MaxD=1000;
		for(int layer=0;layer<GetLayerNumb();layer++){
			if(MaxD>DAvr[layer]){
				MaxD=DAvr[layer];
				ScratchLayer=layer;
				ScratchMasterAverage=DAvr[layer];
			}
		}
	}
	else{
		double	MaxD=0;
		for(int layer=0;layer<GetLayerNumb();layer++){
			if(MaxD<DAvr[layer] && DAvr[layer]<200.0){
				MaxD=DAvr[layer];
				ScratchLayer=layer;
				ScratchMasterAverage=DAvr[layer];
			}
		}
	}

	//for(int i=0;i<sizeof(ScratchXYTable)/sizeof(ScratchXYTable[0]);i++){
	//	if(ScratchXYTable[i]!=NULL){
	//		delete	[]ScratchXYTable[i];
	//	}
	//	ScratchXYTable[i]=new struct ScratchXY[ScratchTableDimLen];
	//	for(double s=0;s<180;s+=1.0){
	//		double Angle=s * M_PI / 180.0;
	//		double	CosS = cos(Angle);
	//		double	SinS = sin(Angle);
	//
	//}
	//
	//int	Cx,Cy;
	//GetArea().GetCenter(Cx,Cy);
	//ScratchTableDimLen
}

bool	DotColorMatchingItem::ExecuteProcessingScratch(ResultInItemRoot* Res
								, double Angle, int Cx, int Cy, int dx, int dy
								, double RotationAngleDegree
								, double& NGDifference, int& ResultWidth
								, float& tScratchResultPeakH, float& tScratchResultPeakL
								, float& tScratchResultVariety
								, int& ResultX, int& ResultY
								, double	&MaxCoef
								, double	&MinCoef
								,int &NGPos
								,bool Mastered ,struct ScratchTable *tScratchTableDim
								,int Isolation)
{
	const	DotColorMatchingThreshold* Thr = GetThresholdR();
	int		Error=0;
	MaxCoef	=0;
	MinCoef	=0;
	NGPos	=-1;
	memset(tScratchTableDim, 0, ScratchTableDimLen * sizeof(struct ScratchTable));

	NGDifference = 0;
	double	CosS = cos(Angle);
	double	SinS = sin(Angle);

	int	AWidth	=GetArea().GetWidth();
	int	AHeight	=GetArea().GetHeight();
	int	MinLen = min(AWidth, AHeight)*0.8/Isolation;
	if(MinLen<10){
		MinLen=10;
	}

	double	ScratchMainDirection = RotationAngleDegree * M_PI / 180.0;
	ScratchResultAngle = (Angle + ScratchMainDirection) * 180.0 / M_PI;

	double	RAngle = ScratchMainDirection;
	double	CosT = cos(RAngle + M_PI / 2);
	double	SinT = sin(RAngle + M_PI / 2);

	ImageBuffer* ImageMasterList[100];
	ImageBuffer* ImageTargetList[100];
	ImageBuffer* ImagePointer;
	if(Mastered==false){
		GetTargetBuffList(ImageTargetList);
		ImagePointer = ImageTargetList[ScratchLayer];
	}
	else{
		GetMasterBuffList(ImageMasterList);
		ImagePointer = ImageMasterList[ScratchLayer];
	}
	//DotColorMatchingBase* ABase = ((DotColorMatchingBase*)GetParentBase());

	int		sDotPerLine = GetDotPerLine();
	int		sMaxLines = GetMaxLines();

	int	ALen=ceil(hypot(AWidth,AHeight))+3;
	if((Cx-ALen+dx)<0 || sDotPerLine<=(Cx+ALen+dx)
	|| (Cy-ALen+dy)<0 || sMaxLines<=(Cy+ALen+dy)){
		return true;
	}

	int	Len = ScratchTableDimLen / 2;
	int	N = GetArea().GetFLineLen();

	if((-45<=ScratchResultAngle && ScratchResultAngle <=45)
	|| (135<=ScratchResultAngle && ScratchResultAngle <=225)){

		double	CosS3=CosS*Isolation;
		double	SinS3=SinS*Isolation;
		double	CosT3=CosT*Isolation;

		int		iCosS3=CosS3*65536.0;
		int		iSinS3=SinS3*65536.0;
		int		iCosT3=CosT3*65536.0;

		for (int i = 0; i < N; i++) {
			int	y = GetArea().GetFLineAbsY(i);
			int	x1 = GetArea().GetFLineLeftX(i);
			int	Numb = GetArea().GetFLineNumb(i);
		
			double	DX = CosS * (x1 - Cx) -SinS * (y - Cy) + Cx + dx;
			double	DY = SinS * (x1 - Cx) +CosS * (y - Cy) + Cy + dy;
			double	DL = CosT * (x1 - Cx) + SinT * (y - Cy) + Len;
			int	iDX	=DX*65536.0;
			int	iDY	=DY*65536.0;
			int	iDL	=DL*65536.0;

			for (int t = 0; t < Numb; t+=Isolation) {
				//int	x = x1 + t;
				int	X = iDX>>16;	//CosS * (x - Cx) +HSin;
				int	Y = iDY>>16;	//SinS * (x - Cx) +HCos;
				iDX+=iCosS3;
				iDY+=iSinS3;
		
				BYTE* s = ImagePointer->GetYWithoutDepended(Y);
				int	d = s[X];
		
				int	L = iDL>>16;	//CosT * (x - Cx) + SinT * (y - Cy) + Len;
				if(L<0 || ScratchTableDimLen<=L){
					Error=1;
					return true;
				}
				iDL+=iCosT3;
		
				tScratchTableDim[L].Brightness += d;
				tScratchTableDim[L].PixelCount++;
			}
		}
	}
	else{
		int		iCosS=CosS*65536.0;
		int		iSinS=SinS*65536.0;
		int		iCosT=CosT*65536.0;
		for (int i = 0; i < N; i++) {
			int	y = GetArea().GetFLineAbsY(i);
			if((y%Isolation)!=0){
				continue;
			}
			int	x1 = GetArea().GetFLineLeftX(i);
			int	Numb = GetArea().GetFLineNumb(i);
		
			double	DX = CosS * (x1 - Cx) -SinS * (y - Cy) + Cx + dx;
			double	DY = SinS * (x1 - Cx) +CosS * (y - Cy) + Cy + dy;
			double	DL = CosT * (x1 - Cx) +SinT * (y - Cy) + Len;
			int	iDX	=DX*65536.0;
			int	iDY	=DY*65536.0;
			int	iDL	=DL*65536.0;
		
			for (int t = 0; t < Numb; t++) {
				//int	x = x1 + t;
				int	X = iDX>>16;	//CosS * (x - Cx) +HSin;
				int	Y = iDY>>16;	//SinS * (x - Cx) +HCos;
				iDX+=iCosS;
				iDY+=iSinS;
		
				BYTE* s = ImagePointer->GetYWithoutDepended(Y);
				int	d = s[X];
		
				int	L = iDL>>16;	//CosT * (x - Cx) + SinT * (y - Cy) + Len;
				if(L<0 || ScratchTableDimLen<=L){
					Error=1;
					return true;
				}
				iDL+=iCosT;
		
				tScratchTableDim[L].Brightness += d;
				tScratchTableDim[L].PixelCount++;
			}
		}
	}

	int	EffectiveCount=0;
	for (int i = 0; i < ScratchTableDimLen; i++) {
		if(tScratchTableDim[i].PixelCount>=MinLen){
			EffectiveCount++;
		}
	}
	if(EffectiveCount<ScratchTableDimLen*0.5){
		return true;
	}

	//TargetAverage /= TotalPixelCount;

	for(int i = 0; i < ScratchTableDimLen; i++) {
		tScratchTableDim[i].Brightness = tScratchTableDim[i].Brightness * ScratchDivTableDim.MulTable[tScratchTableDim[i].PixelCount];
	}

	for(int i = 0; i < ScratchTableDimLen; i++) {
		if(tScratchTableDim[i].PixelCount <= 3) {
			tScratchTableDim[i].PixelCount = 0;
		}
	}
	ScratchResultStartDim = 0;
	for (int i = 0; i < ScratchTableDimLen; i++) {
		if (tScratchTableDim[i].PixelCount > MinLen) {
			ScratchResultStartDim = i;
			break;
		}
	}
	ScratchResultEndDim = 0;
	for (int i = ScratchTableDimLen - 1; i >= 0; i--) {
		if (tScratchTableDim[i].PixelCount > MinLen) {
			ScratchResultEndDim = i;
			break;
		}
	}
	if (ScratchResultEndDim - ScratchResultStartDim < 10)
		return true;

	double	MaxLD = 0;
	bool	FoundCoef = false;
	for (int L = 1; L < Thr->ScratchMaxWidth; L++) {
		double	MaxD = 0;
		double	TmpDim[10000];
		for (int i = ScratchResultStartDim + L*3; i<ScratchResultEndDim; i++) {
			TmpDim[i]=0.0;
		}
		int	L5 = L * 3;
		int	L2 = L;
		int	LTotal = L;
		double	MulL5=50.0/((double)L5);
		double	MulL2=1.0/((double)L2);
		for (int i = ScratchResultStartDim + LTotal; i < (ScratchResultEndDim - L2); i++) {
			double	D = 0;

			double	AddedL=0;
			double	AddedH=0;
			double	AddedD=0;
			int k = i - LTotal;
			for (int j = 0; j < L2; j++, k++) {
				if (tScratchTableDim[k].PixelCount <= 3) {
					goto	NoCoef;
				}
				AddedL+=tScratchTableDim[k].Brightness;
			}
			for (int j = 0; j < L; j++, k++) {
				if (tScratchTableDim[k].PixelCount <= 3) {
					goto	NoCoef;
				}
				AddedD += tScratchTableDim[k].Brightness;
			}
			for (int j = 0; j < L2; j++, k++) {
				if (tScratchTableDim[k].PixelCount <= 3) {
					goto	NoCoef;
				}
				AddedH+=tScratchTableDim[k].Brightness;
			}
			D=(AddedD+AddedD-AddedL-AddedH)*MulL5;

			double	DiffRL=abs(AddedL-AddedH)*MulL2;
			D*=exp(-DiffRL);

			TmpDim[i] = D;
			double	AbsD = fabs(D);
			if (MaxD < AbsD) {
				MaxD = AbsD;
			}
		}
		if (MaxD > MaxLD) {
			MaxLD = MaxD;
			for (int i = ScratchResultStartDim + L * 3; i < ScratchResultEndDim; i++) {
				if(tScratchTableDim[i].PixelCount>=MinLen){
					tScratchTableDim[i].CoefD = TmpDim[i];
				}
			}
			FoundCoef = true;
			ResultWidth = L;
		}
	NoCoef:;
	}
	if (FoundCoef == false) {
		return true;
	}

	tScratchResultPeakH = 0;
	tScratchResultPeakL = 0;
	int	LMergin	=Thr->ScratchMaxWidth+1;

	int	LocalScratchDetectLevelH=Thr->ScratchDetectLevelH+(Thr->ScratchDetectLevelH*0.05*Thr->AddedBrightness);
	int	LocalScratchDetectLevelL=Thr->ScratchDetectLevelL+(Thr->ScratchDetectLevelL*0.05*Thr->AddedBrightness);
	int	ResultPos;
	int	WLen2=(Thr->ScratchMaxWidth+1)/2;

	for(int i=ScratchResultStartDim+3;i<ScratchResultEndDim-3;i++){
		MaxCoef=max(MaxCoef,tScratchTableDim[i].CoefD);
		MinCoef=min(MinCoef,tScratchTableDim[i].CoefD);
		if(tScratchTableDim[i].CoefD>0
		&& tScratchTableDim[i].CoefD>=LocalScratchDetectLevelH
		&& (0<=(i-LMergin) && fabs(tScratchTableDim[i-LMergin].CoefD)>0)
		&& ((i+LMergin)<ScratchTableDimLen && fabs(tScratchTableDim[i+LMergin].CoefD)>0)){
			int	n;
			NGDifference=0.0;
			double	PeakD=tScratchTableDim[i].Brightness;

			for(int m=-WLen2;m<=WLen2;m++){
				PeakD=max(PeakD,tScratchTableDim[i+m].Brightness);
			}
			for(n=0;n<Thr->ScratchMaxWidth;n++){
				if(i+n>=ScratchTableDimLen){
					break;
				}
				if(tScratchTableDim[i+n].CoefD<0
				|| tScratchTableDim[i+n].CoefD<LocalScratchDetectLevelH){
					break;
				}
				NGDifference=max(NGDifference,tScratchTableDim[i+n].CoefD);
			}

			if(n<Thr->ScratchMaxWidth
			&& n>=1){
				double	S=GetScratchVariety(tScratchTableDim,ScratchResultStartDim,ScratchResultEndDim
											,i,n);
				if(S<Thr->ScratchVariety){
					tScratchResultPeakH=tScratchTableDim[i].CoefD;
					tScratchResultVariety=S;

					double	SideL,SideR;
					GetScratchSide(tScratchTableDim,ScratchResultStartDim,ScratchResultEndDim
									,i-n/2 ,n
									,SideL,SideR);
					if((PeakD-min(SideL,SideR))>Thr->ScratchDiff){
						NGPos=i-n/2;
						ResultPos=i-n/2-Len;
						//NGWidth	=n;
						goto	NGProcess;
					}
				}
			}
		}
		if(tScratchTableDim[i].CoefD<0
		&& -tScratchTableDim[i].CoefD>=LocalScratchDetectLevelL
		&& (0<=(i-LMergin) && fabs(tScratchTableDim[i-LMergin].CoefD)>0)
		&& ((i+LMergin)<ScratchTableDimLen && fabs(tScratchTableDim[i+LMergin].CoefD)>0)){
			int	n;
			NGDifference=0.0;
			double	PeakD=tScratchTableDim[i].Brightness;

			for(int m=-WLen2;m<=WLen2;m++){
				PeakD=min(PeakD,tScratchTableDim[i+m].Brightness);
			}
			for(n=0;n<Thr->ScratchMaxWidth;n++){
				if(i+n>=ScratchTableDimLen){
					break;
				}
				if(tScratchTableDim[i+n].CoefD>0
				|| -tScratchTableDim[i+n].CoefD<LocalScratchDetectLevelL){
					break;
				}
				NGDifference=min(NGDifference,tScratchTableDim[i+n].CoefD);
			}
			if(n<Thr->ScratchMaxWidth
			&& n>=1){
				double	S=GetScratchVariety(tScratchTableDim,ScratchResultStartDim,ScratchResultEndDim
											,i,n);
				if(S<Thr->ScratchVariety){
					tScratchResultPeakL=-tScratchTableDim[i].CoefD;
					tScratchResultVariety=S;
					double	SideL,SideR;
					GetScratchSide(tScratchTableDim,ScratchResultStartDim,ScratchResultEndDim
									,i-n/2,n
									,SideL,SideR);
					if((max(SideL,SideR)-PeakD)>Thr->ScratchDiff){
						NGPos=i-n/2;
						ResultPos=i-n/2-Len;
						goto	NGProcess;
					}
				}
			}
		}
	}

	return true;

NGProcess:;
	ResultX	=CosT*ResultPos+Cx;
	ResultY	=SinT*ResultPos+Cy;

	return false;
}

bool	DotColorMatchingItem::CheckScratchInMaster(struct ScratchTable *ScratchTableMasterDim,int NGPos)
{
	double	A=0;
	double	AA=0;
	int		Numb=0;
	for(int i=NGPos-10;i<=(NGPos+10);i++){
		if(0<=i && i<ScratchTableDimLen && ScratchTableMasterDim[i].PixelCount>10){
			A	+=ScratchTableMasterDim[i].Brightness;
			AA	+=ScratchTableMasterDim[i].Brightness*ScratchTableMasterDim[i].Brightness;
			Numb++;
		}
	}
	if(Numb<=3){
		return true;
	}
	double	Avr=A/Numb;
	double	V=(AA-Avr*Avr*Numb)/Numb;
	if(V>=0){
		V=sqrt(V);
		if(V<((DotColorMatchingBase *)GetParentBase())->MasterScratchFlatness){
			return false;
		}
	}
	return true;
}
	
void	DotColorMatchingItem::GetScratchSide(struct ScratchTable *tScratchTableDim ,int ScratchStartDim,int ScratchEndDim
							,int PosCenter ,int Width
							,double &SideL ,double &SideR)
{
	SideL=tScratchTableDim[PosCenter].Brightness;
	SideR=tScratchTableDim[PosCenter].Brightness;
	int	CountL=0;
	double	tSideL=0;
	int		Width2=Width/2+1;
	for(int i=PosCenter-Width2-3;i>=ScratchStartDim;i--){
		if(tScratchTableDim[i].PixelCount>0){
			tSideL+=tScratchTableDim[i].Brightness;
			CountL++;
		}
		if(CountL>=10)
			break;
	}
	int	CountR=0;
	double	tSideR=0;
	for(int i=PosCenter+Width2+3;i<ScratchEndDim;i++){
		if(tScratchTableDim[i].PixelCount>0){
			tSideR+=tScratchTableDim[i].Brightness;
			CountR++;
		}
		if(CountR>=10)
			break;
	}
	if(CountL>0)
		SideL=tSideL/CountL;
	if(CountR>0)
		SideR=tSideR/CountR;
}

double	DotColorMatchingItem::GetScratchVariety(struct ScratchTable *TableDim,int ScratchStartDim,int ScratchEndDim
												,int Point,int W)
{
	int	h1=Point-W/2-W-2;
	int	h2=Point+W/2+W+2;
	double	A=0;
	double	AA=0;
	int		LNumb=0;
	int	KStart	=max(ScratchStartDim+3,h1-W-15);
	int	KEnd	=min(ScratchEndDim-3,h2+W+15);
	for(int k=KStart;k<KEnd;k++){
		if(h1<=k && k<h2){
			continue;
		}
		double	a=TableDim[k].Brightness;
		A +=a;
		AA+=a*a;
		LNumb++;
	}
	if(LNumb<=3){
		return 0;
	}
	double	Avr=A/LNumb;
	double	S=sqrt((AA-LNumb*Avr*Avr)/LNumb);
	return S;
}


