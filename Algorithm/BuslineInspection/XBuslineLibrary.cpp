#include "XBuslineInspection.h"
#include "XGeneralFunc.h"
#include "XImageProcess.h"

BuslineLibrary::BuslineLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	BlockMinArea		=0;
	BlockMaxArea		=0x7FFFFFFF;
	MinWidth			=3;
	MinGap				=3;
	LimitDot			=200;
	MinArea				=0;
	MaxArea				=0x7FFFFFFF;
	MinSize				=0;
	Darkside			=true;
	CompareToMaster		=false;
	AutoBinarize		=false;
	ReduceNoise			=true;
	BinarizedLength		=200;	//局所２値化領域サイズ
	ReferredBrightness	=100;	//２値化参照輝度
	SearchDotToMaster	=5;
	WidthToIgnoreEdge	=2;
	OKNickRate			=50;			//0-100% for MinWidth
	OKShortRate			=50;		//0-100% for MinGap
	BrightnessWidthInsideL	=20;
	BrightnessWidthInsideH	=20;
	BrightnessWidthOutsideL	=20;
	BrightnessWidthOutsideH	=20;
}

bool	BuslineLibrary::SaveBlob(QIODevice *f)
{
	int32	Ver=7;

	if(::Save(f,Ver)==false){
		return false;
	}
	if(::Save(f,BlockMinArea)==false){
		return false;
	}
	if(::Save(f,BlockMaxArea)==false){
		return false;
	}
	if(::Save(f,MinWidth)==false){
		return false;
	}
	if(::Save(f,MinGap)==false){
		return false;
	}
	if(::Save(f,LimitDot)==false){
		return false;
	}
	if(::Save(f,Darkside)==false){
		return false;
	}
	if(::Save(f,CompareToMaster)==false){
		return false;
	}
	if(::Save(f,AutoBinarize)==false){
		return false;
	}
	if(::Save(f,ReduceNoise)==false){
		return false;
	}
	if(::Save(f,BinarizedLength)==false){
		return false;
	}
	if(::Save(f,ReferredBrightness)==false){
		return false;
	}
	if(::Save(f,SearchDotToMaster)==false){
		return false;
	}
	if(::Save(f,MinArea)==false){
		return false;
	}
	if(::Save(f,MaxArea)==false){
		return false;
	}
	if(::Save(f,MinSize)==false){
		return false;
	}
	if(::Save(f,WidthToIgnoreEdge)==false){
		return false;
	}
	if(::Save(f,OKNickRate)==false){
		return false;
	}
	if(::Save(f,OKShortRate)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthInsideL)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthInsideH)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthOutsideL)==false){
		return false;
	}
	if(::Save(f,BrightnessWidthOutsideH)==false){
		return false;
	}
	return true;
}
bool	BuslineLibrary::LoadBlob(QIODevice *f)
{
	int32	Ver;

	if(::Load(f,Ver)==false){
		return false;
	}
	if(Ver>=7){
		if(::Load(f,BlockMinArea)==false){
			return false;
		}
		if(::Load(f,BlockMaxArea)==false){
			return false;
		}
	}
	if(::Load(f,MinWidth)==false){
		return false;
	}
	if(::Load(f,MinGap)==false){
		return false;
	}
	if(::Load(f,LimitDot)==false){
		return false;
	}
	if(::Load(f,Darkside)==false){
		return false;
	}
	if(::Load(f,CompareToMaster)==false){
		return false;
	}
	if(::Load(f,AutoBinarize)==false){
		return false;
	}
	if(::Load(f,ReduceNoise)==false){
		return false;
	}
	if(::Load(f,BinarizedLength)==false){
		return false;
	}
	if(::Load(f,ReferredBrightness)==false){
		return false;
	}
	if(::Load(f,SearchDotToMaster)==false){
		return false;
	}
	if (Ver >= 6) {
		if (::Load(f, MinArea) == false) {
			return false;
		}
		if (::Load(f, MaxArea) == false) {
			return false;
		}
	}
	else
	if(Ver>=3){
		int	iMinArea;
		int	iMaxArea;
		if(::Load(f,iMinArea)==false){
			return false;
		}
		if(::Load(f,iMaxArea)==false){
			return false;
		}
		MinArea	=iMinArea;
		MaxArea =iMaxArea;
	}
	if (Ver>=7) {
		if(::Load(f,MinSize)==false){
			return false;
		}
	}
	if(Ver>=4){
		if(::Load(f,WidthToIgnoreEdge)==false){
			return false;
		}
		if(::Load(f,OKNickRate)==false){
			return false;
		}
		if(::Load(f,OKShortRate)==false){
			return false;
		}
	}
	if(Ver>=5){
		if(::Load(f,BrightnessWidthInsideL)==false){
			return false;
		}
		if(::Load(f,BrightnessWidthInsideH)==false){
			return false;
		}
		if(::Load(f,BrightnessWidthOutsideL)==false){
			return false;
		}
		if(::Load(f,BrightnessWidthOutsideH)==false){
			return false;
		}
	}
	return true;
}

BuslineLibrary	&BuslineLibrary::operator=(const AlgorithmLibrary &src)
{
	const BuslineLibrary	*s=dynamic_cast<const BuslineLibrary *>(&src);
	MinWidth	=s->MinWidth;
	return *this;
}
void	BuslineLibrary::MakeBlocks(ImageBuffer &IBuff ,PureFlexAreaListContainer &Blocks
					,int page
					,BYTE **MaskMap)
{
	int	iDotPerLine	=GetDotPerLine(page);
	int	iMaxLines	=GetMaxLines(page);

	int		XByte	=(iDotPerLine+7)/8;
	int		YLen	=iMaxLines;

	BYTE	**TmpMap =MakeMatrixBuff(XByte,YLen);
	BYTE	**TmpMap2=MakeMatrixBuff(XByte,YLen);
	MatrixBuffClear	(TmpMap ,0 ,XByte,YLen);

	int	CenterAve=MakeThreshold(IBuff ,0,0,iDotPerLine,iMaxLines,MaskMap);

	int	XNumb=(iDotPerLine+LimitDot-1)/LimitDot;
	int	YNumb=(iMaxLines  +LimitDot-1)/LimitDot;

	for(int yn=0;yn<YNumb;yn++){
		for(int xn=0;xn<XNumb;xn++){
			int	x1=xn*LimitDot;
			int	y1=yn*LimitDot;
			int	x2=x1+LimitDot;
			int	y2=y1+LimitDot;
			if(x2>iDotPerLine){
				x2=iDotPerLine;
			}
			if(y2>iMaxLines){
				y2=iMaxLines;
			}
			MakeMap(IBuff ,x1 ,y1 ,x2 ,y2 ,MaskMap
									,TmpMap);
		}
	}

	GetLayersBase()->FatAreaN(TmpMap
				,TmpMap2
				,XByte, YLen
				,(MinWidth*2+10));

	for(int yn=0;yn<YNumb;yn++){
		for(int xn=0;xn<XNumb;xn++){
			int	L=(MinWidth*2+10);
			int	x1=xn*LimitDot-L;
			int	y1=yn*LimitDot-L;
			int	x2=x1+LimitDot+L;
			int	y2=y1+LimitDot+L;
			if(x2>iDotPerLine){
				x2=iDotPerLine;
			}
			if(y2>iMaxLines){
				y2=iMaxLines;
			}
			PureFlexAreaList	*f=new PureFlexAreaList();
			f->BuildFromRaster(TmpMap,XByte ,YLen
								,0,0
						        ,x1,y1,x2,y2
								,iDotPerLine,iMaxLines);
			Blocks.AppendList(f);
		}
	}
	DeleteMatrixBuff(TmpMap ,YLen);
	DeleteMatrixBuff(TmpMap2,YLen);
}

int	BuslineLibrary::MakeThreshold(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap)
{
	int	BrList[256];
	double  Ave=GetAverageRough(IBuff,x1,y1,x2,y2 ,MaskMap);
	memset(BrList,0,sizeof(BrList));
	MakeBrightList(BrList ,IBuff,x1,y1,x2,y2 ,MaskMap);
	int	C=Ave;

	//輝度リストでのAve付近の極小個数輝度を求める
	for(int k=C-1;k<=0;k--){
		if(BrList[k]>BrList[k+1]){
			C=k+1;
			break;
		}
	}
	for(int k=C+1;k<256;k++){
		if(BrList[k]>BrList[k-1]){
			C=k-1;
			break;
		}
	}
	//Cの両側で最大個数の輝度をそれぞれ求める
	int	MaxD=0;
	int	MaxBLow=0;
	for(int k=0;k<=C;k++){
		if(MaxD<BrList[k]){
			MaxD=BrList[k];
			MaxBLow=k;
		}
	}
	MaxD=0;
	int	MaxBHigh=0;
	for(int k=0;k<=C;k++){
		if(MaxD<BrList[k]){
			MaxD=BrList[k];
			MaxBHigh=k;
		}
	}

	int	CenterBright= (MaxBLow+MaxBHigh+1)/2;
	return CenterBright;
}

void	BuslineLibrary::MakeMap(ImageBuffer &IBuff ,int x1 ,int y1 ,int x2 ,int y2 ,BYTE **MaskMap
									,BYTE **BMap)
{
	int CenterBright=MakeThreshold(IBuff ,x1 ,y1 ,x2 ,y2 ,MaskMap);
	if(Darkside==true){
		for(int y=y1;y<y2;y++){
			BYTE	*s=IBuff.GetY(y);
			BYTE	*d=BMap[y];
			for(int x=x1;x<x2;x++){
				if(s[x]<=CenterBright){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
	else{
		for(int y=y1;y<y2;y++){
			BYTE	*s=IBuff.GetY(y);
			BYTE	*d=BMap[y];
			for(int x=x1;x<x2;x++){
				if(CenterBright<=s[x]){
					SetBmpBitOnY1(d,x);
				}
			}
		}
	}
}

double	BuslineLibrary::GetAverageRough(ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap)
{
	double	Added=0.0;
	if(MaskMap==NULL){
		for(int y=y1;y<y2;y++){
			int	D=0;
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				D+=s[x];
			}
			Added+=D;
		}
	}
	else{
		for(int y=y1;y<y2;y++){
			int	D=0;
			BYTE	*s=IBuff.GetY(y);
			BYTE	*m=MaskMap[y];
			for(int x=x1;x<x2;x++){
				if(GetBmpBitOnY(m,x)!=0){
					D+=s[x];
				}
			}
			Added+=D;
		}
	}
	int	Numb=(x2-x1)*(y2-y1);
	if(Numb<=0){
		return (0.0);
	}
	return Added/Numb;
}

void	BuslineLibrary::MakeBrightList(int BrList[] ,ImageBuffer &IBuff,int x1,int y1,int x2,int y2 ,BYTE **MaskMap)
{
	if(MaskMap==NULL){
		for(int y=y1;y<y2;y++){
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				BrList[s[x]]++;
			}
		}
	}
	else{
		for(int y=y1;y<y2;y++){
			BYTE	*m=MaskMap[y];
			BYTE	*s=IBuff.GetY(y);
			for(int x=x1;x<x2;x++){
				if(GetBmpBitOnY(m,x)!=0){
					BrList[s[x]]++;
				}
			}
		}
	}
}


//==============================================================

BuslineLibraryContainer::BuslineLibraryContainer(LayersBase *base)
	:AlgorithmLibraryContainer(base)
{}