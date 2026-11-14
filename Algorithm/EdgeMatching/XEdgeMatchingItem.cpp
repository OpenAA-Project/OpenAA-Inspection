#define _USE_MATH_DEFINES
#include <math.h>
#include "XEdgeMatching.h"
#include "XEdgeMatchingPacket.h"
#include "XMainSchemeMemory.h"
#include <cmath>
#include <vector>
#include "swap.h"

//===========================================================================
// EdgeMatchingThreshold
//===========================================================================
EdgeMatchingThreshold::EdgeMatchingThreshold(EdgeMatchingItem *parent)
    : AlgorithmThreshold(parent)
{
    SearchDotX      = 0;
    SearchDotY      = 0;
    SearchByPixel   = 0;
    ThresholdDiv    = 0.0;
    ThresholdDirection = 0.0;
    FocusRadius     = 0;
    Layer           = -1;
    BlockSizeX      =99999999;
    BlockSizeY      =99999999;
    UseDivided      =false;
}

EdgeMatchingThreshold::~EdgeMatchingThreshold(void)
{
}

void EdgeMatchingThreshold::RegistHist(void)
{
}

void EdgeMatchingThreshold::CopyFrom(const AlgorithmThreshold &src)
{
    const EdgeMatchingThreshold *p = dynamic_cast<const EdgeMatchingThreshold *>(&src);
    if (p == NULL) return;
    
    SearchDotX      = p->SearchDotX;
    SearchDotY      = p->SearchDotY;
    SearchByPixel   = p->SearchByPixel;
    ThresholdDiv    = p->ThresholdDiv;
    ThresholdDirection = p->ThresholdDirection;
    FocusRadius     = p->FocusRadius;
    Layer           = p->Layer;
    BlockSizeX      = p->BlockSizeX;
    BlockSizeY      = p->BlockSizeY;
	UseDivided      = p->UseDivided;
}

void EdgeMatchingThreshold::FromLibrary(AlgorithmLibrary *src)
{
    EdgeMatchingLibrary *p = dynamic_cast<EdgeMatchingLibrary *>(src);
    if (p == NULL) return;
    
    SearchDotX      = p->SearchDotX;
    SearchDotY      = p->SearchDotY;
    SearchByPixel   = p->SearchByPixel;
    ThresholdDiv    = p->ThresholdDiv;
    ThresholdDirection = p->ThresholdDirection;
    FocusRadius     = p->FocusRadius;
    Layer           = p->Layer;
    BlockSizeX      = p->BlockSizeX;
    BlockSizeY      = p->BlockSizeY;
	UseDivided      = p->UseDivided;
}

void EdgeMatchingThreshold::ToLibrary(AlgorithmLibrary *Dest)
{
    EdgeMatchingLibrary *p = dynamic_cast<EdgeMatchingLibrary *>(Dest);
    if (p == NULL) return;
    
    p->SearchDotX   = SearchDotX;
    p->SearchDotY   = SearchDotY;
    p->SearchByPixel= SearchByPixel;
    p->ThresholdDiv = ThresholdDiv;
    p->ThresholdDirection = ThresholdDirection;
    p->FocusRadius  = FocusRadius;
    p->Layer        = Layer;
    p->BlockSizeX   = BlockSizeX;
    p->BlockSizeY   = BlockSizeY;
	p->UseDivided   = UseDivided;
}

bool EdgeMatchingThreshold::IsEqual(const AlgorithmThreshold &src) const
{
    const EdgeMatchingThreshold *p = dynamic_cast<const EdgeMatchingThreshold *>(&src);
    if (p == NULL) return false;
    
    if (SearchDotX != p->SearchDotX)        return false;
    if (SearchDotY != p->SearchDotY)        return false;
    if (SearchByPixel != p->SearchByPixel)  return false;
    if (ThresholdDiv != p->ThresholdDiv)    return false;
    if (ThresholdDirection != p->ThresholdDirection) return false;
    if (FocusRadius != p->FocusRadius)      return false;
    if (Layer != p->Layer)                  return false;
    if (BlockSizeX != p->BlockSizeX)        return false;
    if (BlockSizeY != p->BlockSizeY)        return false;
    if (UseDivided != p->UseDivided)        return false;

    return true;
}

bool EdgeMatchingThreshold::Save(QIODevice *f)
{
	WORD	Ver=EdgeMatchingVersion;

	if(::Save(f,Ver)==false)
		return false;

    if (::Save(f, SearchDotX) == false)     return false;
    if (::Save(f, SearchDotY) == false)     return false;
    if (::Save(f, SearchByPixel) == false)  return false;
    if (::Save(f, ThresholdDiv) == false)   return false;
    if (::Save(f, ThresholdDirection) == false) return false;
    if (::Save(f, FocusRadius) == false)    return false;
    if (::Save(f, Layer) == false)          return false;
    if(::Save(f, BlockSizeX) == false)      return false;
    if(::Save(f, BlockSizeY) == false)      return false; 
    if(::Save(f, UseDivided) == false)      return false; 

    return true;
}

bool EdgeMatchingThreshold::Load(QIODevice *f)
{
    WORD	Ver=0;
    if(::Load(f, SearchDotX) == false)      return false;
    if(SearchDotX>=10000){
        Ver=SearchDotX;
        if(::Load(f, SearchDotX) == false)      return false;
    }
    if (::Load(f, SearchDotY) == false)     return false;
    if (::Load(f, SearchByPixel) == false)  return false;
    if (::Load(f, ThresholdDiv) == false)   return false;
    if (::Load(f, ThresholdDirection) == false) return false;
    if (::Load(f, FocusRadius) == false)    return false;
    if (::Load(f, Layer) == false)          return false;
    if(Ver>=10000){
        if(::Load(f, BlockSizeX) == false)      return false;
        if(::Load(f, BlockSizeY) == false)      return false;
        if(::Load(f, UseDivided) == false)      return false; 
    }   
    return true;
}

int EdgeMatchingThreshold::GetSize(void) const
{
    return sizeof(*this);
}

void EdgeMatchingThreshold::MakeReportedTopics(ReportedTopicContainer &RetContainer) const
{
    RetContainer.Add("SearchDotX", SearchDotX);
    RetContainer.Add("SearchDotY", SearchDotY);
    RetContainer.Add("SearchByPixel", SearchByPixel);
    RetContainer.Add("ThresholdDiv", ThresholdDiv);
    RetContainer.Add("ThresholdDirection", ThresholdDirection);
    RetContainer.Add("FocusRadius", FocusRadius);
    RetContainer.Add("Layer", Layer);
    RetContainer.Add("BlockSizeX", BlockSizeX);
    RetContainer.Add("BlockSizeY", BlockSizeY);
    RetContainer.Add("UseDivided", UseDivided);
}


//===========================================================================
// EdgeMatchingItem
//===========================================================================
EdgeMatchingItem::EdgeMatchingItem(void)
{
    AVector = NULL;
    VMap = NULL;
    RMap = NULL;
    MapXLen = 0;
    MapYLen = 0;
    MasterCx = MasterCy = 0;
    ResultDx = ResultDy = 0;
    ResultRotation = 0;

    TargetMap=NULL;
    TargetMapXLen=TargetMapYLen =0;
    TargetX1     =TargetY1      =0;

    A   =0;
	AA  = 0;
    ShiftByGlobalX  =0;
    ShiftByGlobalY  =0;
    GlobalRotation  =0;
}

EdgeMatchingItem::~EdgeMatchingItem(void)
{
    Clear();
}

void EdgeMatchingItem::SetRefereneFrom(AlgorithmItemRoot *src, int OffsetX, int OffsetY)
{
    AlgorithmItemRoot::SetRefereneFrom(src, OffsetX, OffsetY);
}

void EdgeMatchingItem::MoveTo(int dx, int dy)
{
    AlgorithmItemRoot::MoveTo(dx, dy);
}

AlgorithmItemPI &EdgeMatchingItem::operator=(const AlgorithmItemRoot &src)
{
    const EdgeMatchingItem *p = dynamic_cast<const EdgeMatchingItem *>(&src);
    if (p == NULL) return *this;

    AlgorithmItemPI::operator=(src);
    const AlgorithmThreshold *RThr = ((AlgorithmItemRoot *)&src)->GetThresholdBaseReadable();
    GetThresholdW()->CopyFrom(*((const EdgeMatchingThreshold *)RThr));

    MasterCx = p->MasterCx;
    MasterCy = p->MasterCy;
    ResultDx = p->ResultDx;
    ResultDy = p->ResultDy;
    ResultRotation = p->ResultRotation;
    return *this;
}

EdgeMatchingItem &EdgeMatchingItem::operator=(const EdgeMatchingItem &src)
{
    if (this == &src) return *this;

    AlgorithmItemPI::operator=(src);
    const AlgorithmThreshold *RThr = ((AlgorithmItemRoot *)&src)->GetThresholdBaseReadable();
    GetThresholdW()->CopyFrom(*((const EdgeMatchingThreshold *)RThr));

    MasterCx = src.MasterCx;
    MasterCy = src.MasterCy;
    ResultDx = src.ResultDx;
    ResultDy = src.ResultDy;
    ResultRotation = src.ResultRotation;
    return *this;
}

void EdgeMatchingItem::SetIndependentItemData(int32 Command, int32 LocalPage, int32 Layer, AlgorithmItemRoot *Data, IntList &EdittedMemberID, QByteArray &Something, QByteArray &AckData)
{
	if(Command==SetIndependentItemDataCommand_OnlyOne){
		if(GetParentInPage()->GetPage()==LocalPage && GetID()==Data->GetID()){
			EdgeMatchingInPage	*Pg=dynamic_cast<EdgeMatchingInPage *>(GetParentInPage());
			UndoElement<EdgeMatchingInPage>	*UPointer=new UndoElement<EdgeMatchingInPage>(Pg,&EdgeMatchingInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			EdgeMatchingItem *src=(EdgeMatchingItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
	else if(Command==SetIndependentItemDataCommand_All){
		if(GetLibID()==((EdgeMatchingItem *)Data)->GetLibID()){
			EdgeMatchingInPage	*Pg=dynamic_cast<EdgeMatchingInPage *>(GetParentInPage());
			UndoElement<EdgeMatchingInPage>	*UPointer=new UndoElement<EdgeMatchingInPage>(Pg,&EdgeMatchingInPage::UndoSetIndependentItemDataCommand);
			::Save(UPointer->GetWritePointer(),GetID());
			GetThresholdW()->Save(UPointer->GetWritePointer());
			GetLayersBase()->GetUndoStocker().SetElementToNewTopic(UPointer);

			EdgeMatchingItem *src=(EdgeMatchingItem *)Data;
			CopyThresholdOnly(src);
			SetLibID(src->GetLibID());
		}
	}
}

void EdgeMatchingItem::Clear(void)
{
    ResultDx = 0;
    ResultDy = 0;
    ResultRotation = 0;

    if(VMap!=NULL){
        DeleteMatrixBuff((BYTE **)VMap,MapYLen);
        VMap=NULL;
	}
    if(RMap!=NULL){
        DeleteMatrixBuff((BYTE **)RMap,MapYLen);
		RMap = NULL;
    }
    if(TargetMap!=NULL){
        DeleteMatrixBuff((BYTE **)TargetMap,TargetMapYLen);
		TargetMap = NULL;
    }

    MapXLen = 0;
    MapYLen = 0;
    TargetMapXLen=TargetMapYLen =0;
    TargetX1     =TargetY1      =0;
}

bool EdgeMatchingItem::Save(QIODevice *file)
{
    WORD Ver = 1;
    if (AlgorithmItemPI::Save(file) == false) return false;
    if (::Save(file, Ver) == false) return false;
    return true;
}

bool EdgeMatchingItem::Load(QIODevice *file, LayersBase *LBase)
{
    WORD Ver = 0;
    if (AlgorithmItemPI::Load(file, LBase) == false) return false;
    if (::Load(file, Ver) == false) return false;
    return true;
}

void EdgeMatchingItem::Draw(QImage &pnt, int movx, int movy, double ZoomRate, AlgorithmDrawAttr *Attr)
{
    EdgeMatchingDrawAttr *a = dynamic_cast<EdgeMatchingDrawAttr *>(Attr);
    if (a != NULL && a->DrawModeArea == true) {
        AlgorithmItemRoot::Draw(pnt, movx, movy, ZoomRate, Attr);
    }
    else if(a!=NULL && a->DrawModeEdge==true) {
        AlgorithmItemRoot::Draw(pnt, movx, movy, ZoomRate, Attr);

        int x1 = GetArea().GetMinX();
		int y1 = GetArea().GetMinY();
		int x2 = GetArea().GetMaxX();
		int y2 = GetArea().GetMaxY();
		int Gx1 = ceil((x1 + movx) * ZoomRate);
		int Gy1 = ceil((y1 + movy) * ZoomRate);
		int Gx2 = floor((x2 + movx) * ZoomRate);
		int Gy2 = floor((y2 + movy) * ZoomRate);

		Gx1 = std::max(Gx1,0);
		Gy1 = std::max(Gy1,0);
		Gx2 = std::min(Gx2,pnt.width()-1);
		Gy2 = std::min(Gy2,pnt.height()-1);

        for(int Y=Gy1;Y<=Gy2;Y++){
            QRgb *line = (QRgb *)pnt.scanLine(Y);
			int y = Y/ZoomRate - movy;
            for(int X=Gx1;X<=Gx2;X++){
				int x = X/ZoomRate - movx;
				float   v=fabs((VMap[y-y1])[x-x1]);
                line[X] = qRgba(v,0,0,128);
            }
		}
	}
    else if(a!=NULL && a->DrawModeEdge==true) {
        AlgorithmItemRoot::Draw(pnt, movx, movy, ZoomRate, Attr);

        int x1 = GetArea().GetMinX();
		int y1 = GetArea().GetMinY();
		int x2 = GetArea().GetMaxX();
		int y2 = GetArea().GetMaxY();
		int Gx1 = (x1 + movx) * ZoomRate;
		int Gy1 = (y1 + movy) * ZoomRate;
		int Gx2 = (x2 + movx) * ZoomRate;
		int Gy2 = (y2 + movy) * ZoomRate;

		Gx1 = std::max(Gx1,0);
		Gy1 = std::max(Gy1,0);
		Gx2 = std::min(Gx2,pnt.width()-1);
		Gy2 = std::min(Gy2,pnt.height()-1);

        for(int Y=Gy1;Y<=Gy2;Y++){
            QRgb *line = (QRgb *)pnt.scanLine(Y);
			int y = Y/ZoomRate - movy;
            for(int X=Gx1;X<=Gx2;X++){
				int x = X/ZoomRate - movx;
				float   v=fabs((RMap[y-y1])[x-x1]);
                
                line[x] = qRgba(v,0,0,128);
            }
		}
	}
}

void EdgeMatchingItem::DrawResultItem(ResultInItemRoot *Res, QImage &IData, QPainter &PData, int MovX, int MovY, double ZoomRate, bool OnlyNG)
{
    QColor ce = Qt::red;
    ce.setAlpha(180);

    GetArea().Draw(ResultDx, ResultDy, &IData, ce.rgba(), ZoomRate, MovX, MovY);

    if (ZoomRate >= 1.0) {
        PData.drawText((MasterCx + MovX) * ZoomRate, (MasterCy + MovY) * ZoomRate,
                          QString("dx=") + QString::number((int)ResultDx) 
                        + QString(",dy=") + QString::number((int)ResultDy));
        PData.drawText((MasterCx + MovX) * ZoomRate, (MasterCy + MovY) * ZoomRate+16,
                          QString("Result=") + QString::number(Res->GetResultDouble(),'f',4)); 
    }
}

struct SecondDerivativeResult
{
    double maxVal;      // 2回微分の最大値 (最大主曲率)
    double minVal;      // 2回微分の最小値 (直交方向の2回微分)
    double angle;       // 最大値となる法線の角度 [rad] (-π 〜 π)
    double normalX;     // 法線ベクトルのX成分
    double normalY;     // 法線ベクトルのY成分
    bool   isValid;     // 範囲外など計算不能時はfalse
};
/**
 * @brief 指定座標(x, y)の半径R近傍から輝度の2回微分最大値と法線ベクトルを算出
 * @param sourceImage 対象画像バッファ
 * @param x           中心X座標
 * @param y           中心Y座標
 * @param radius      近傍半径 R (R >= 1)
 * @param outResult   結果の格納先
 * @return 成功時はtrue、失敗時はfalse
 */
bool CalcMaxSecondDerivative(const ImageBuffer *sourceImage, int x, int y, int radius
                            ,struct SecondDerivativeResult &outResult)
{
    if (sourceImage == nullptr || sourceImage->IsNull() || radius < 1) {
        outResult.isValid = false;
        return false;
    }

    const int width  = sourceImage->GetWidth();
    const int height = sourceImage->GetHeight();

    // 指定半径 R の矩形窓が画像内に収まっているかをチェック
    if (x - radius < 0 || x + radius >= width ||
        y - radius < 0 || y + radius >= height) {
        outResult.isValid = false;
        return false;
    }

    // 近傍多項式近似: f(u, v) ≈ a*u^2 + b*v^2 + c*u*v + d*u + e*v + f_0
    // ここで u = xi - x, v = yi - y (-R <= u, v <= R)
    // 対称な矩形格子領域では基底関数間の直交性により各係数が個別に算出可能:
    //   Ixx = 2 * a = 2 * sum( (u^2 - mean(u^2)) * I(u,v) ) / sum( (u^2 - mean(u^2))^2 )
    //   Iyy = 2 * b = 2 * sum( (v^2 - mean(v^2)) * I(u,v) ) / sum( (v^2 - mean(v^2))^2 )
    //   Ixy = c     = sum( (u * v) * I(u,v) ) / sum( (u * v)^2 )

    const int N = 2 * radius + 1; // 1辺の画素数
    
    // 1次元の u^2 の総和: sum_{u=-R}^R u^2 = R*(R+1)*(2R+1)/3
    const double sum_u2_1d = static_cast<double>(radius * (radius + 1) * (2 * radius + 1)) / 3.0;
    // 2次元全画素における u^2 の平均値
    const double u2_mean = sum_u2_1d / static_cast<double>(N);

    // 重み分母の集計
    double denom_xx = 0.0;
    double denom_xy = 0.0;

    for (int v = -radius; v <= radius; ++v) {
        for (int u = -radius; u <= radius; ++u) {
            const double qu = static_cast<double>(u * u) - u2_mean;
            denom_xx += qu * qu;
            denom_xy += static_cast<double>((u * v) * (u * v));
        }
    }

    // 各画素値を用いた分子（重み付き和）の集計
    double num_xx = 0.0;
    double num_yy = 0.0;
    double num_xy = 0.0;

    for (int v = -radius; v <= radius; ++v) {
        const BYTE *pRow = sourceImage->GetY(y + v);
        const double qv = static_cast<double>(v * v) - u2_mean;

        for (int u = -radius; u <= radius; ++u) {
            const double val = static_cast<double>(pRow[x + u]);
            const double qu  = static_cast<double>(u * u) - u2_mean;

            num_xx += qu * val;
            num_yy += qv * val;
            num_xy += static_cast<double>(u * v) * val;
        }
    }

    // 2階微分の算出
    const double Ixx = (denom_xx > 1e-12) ? (2.0 * num_xx / denom_xx) : 0.0;
    const double Iyy = (denom_xx > 1e-12) ? (2.0 * num_yy / denom_xx) : 0.0; // 格子の対称性よりdenom_yy == denom_xx
    const double Ixy = (denom_xy > 1e-12) ? (num_xy / denom_xy) : 0.0;

    // ヘッセ行列の固有値解析: H = [Ixx, Ixy; Ixy, Iyy]
    const double trace = Ixx + Iyy;
    const double diff  = Ixx - Iyy;
    const double disc  = std::sqrt(diff * diff + 4.0 * Ixy * Ixy);

    // 最大主曲率 (λ1) および最小曲率 (λ2)
    const double lambda1 = 0.5 * (trace + disc);
    const double lambda2 = 0.5 * (trace - disc);

    // 最大固有値 λ1 に対応する法線ベクトル (vx, vy)
    double vx = 0.0;
    double vy = 0.0;

    if (std::abs(Ixy) > 1e-7 || std::abs(lambda1 - Ixx) > 1e-7) {
        vx = Ixy;
        vy = lambda1 - Ixx;
        const double norm = std::hypot(vx, vy);
        if (norm > 1e-7) {
            vx /= norm;
            vy /= norm;
        } else {
            vx = 1.0;
            vy = 0.0;
        }
    } else {
        vx = 1.0;
        vy = 0.0;
    }

    outResult.maxVal  = lambda1;
    outResult.minVal  = lambda2;
    outResult.angle   = std::atan2(vy, vx);
    outResult.normalX = vx;
    outResult.normalY = vy;
    outResult.isValid = true;

    return true;
}


ExeResult EdgeMatchingItem::ExecuteInitialAfterEdit(int ExeID, int ThreadNo, ResultInItemRoot *Res, ExecuteInitialAfterEditInfo &EInfo)
{
    ExeResult Ret = AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID, ThreadNo, Res, EInfo);
    GetArea().GetCenter(MasterCx, MasterCy);

	AVector=(AlignmentPacket2D *)GetAlignmentPointer(MasterCx,MasterCy);
	if(AVector!=NULL){
		AVector->Set(this);    
    }
    
    const EdgeMatchingThreshold *Thr = GetThresholdR();
	int W = GetArea().GetWidth();
	int H = GetArea().GetHeight();
	int X1 = GetArea().GetMinX();
	int Y1 = GetArea().GetMinY();
    int MaxLines    =GetMaxLines();
    int DotPerLine  =GetDotPerLine();

    Clear();
    MapXLen=W;
    MapYLen=H;

    VMap=(float **)MakeMatrixBuff(MapXLen*sizeof(float),MapYLen);
    RMap=(float **)MakeMatrixBuff(MapXLen*sizeof(float),MapYLen);

    MatrixBuffClear	((BYTE **)VMap ,0 ,MapXLen*sizeof(float),MapYLen);
    MatrixBuffClear	((BYTE **)RMap ,0 ,MapXLen*sizeof(float),MapYLen);

    TargetMapXLen   =hypot(W,H);
    TargetMapYLen   =hypot(W,H);
    TargetX1    =X1-(TargetMapXLen-W)/2;
    TargetY1    =Y1-(TargetMapYLen-H)/2;
    TargetMap=(float **)MakeMatrixBuff(TargetMapXLen*sizeof(float),TargetMapYLen);
    MatrixBuffClear	((BYTE **)TargetMap ,0 ,TargetMapXLen*sizeof(float),TargetMapYLen);

    ImagePointerContainer MasterImageList;
    GetMasterBuffList(MasterImageList);
    AdoptedLayer=Thr->Layer;
    if(Thr->Layer<0 || GetLayerNumb()<=Thr->Layer){
        double  MaxV=0;
        int     MaxLayer=0;
        for(int layer=0;layer<GetLayerNumb();layer++){
            ImageBuffer *tMasterImage = MasterImageList[layer];
            double DAvr;
            double  V=GetArea().GetVar(0,0,*tMasterImage,DAvr);
            if(MaxV<V){
                MaxV=V;
                MaxLayer=layer;
            }
        }
        AdoptedLayer=MaxLayer;
    }
    ImageBuffer *MasterImage = MasterImageList[AdoptedLayer];
    int N=GetArea().GetFLineLen();
    float   MaxV=0;
    for(int i=0;i<N;i++){
        int x1=GetArea().GetFLineLeftX(i);
        int y =GetArea().GetFLineAbsY(i);
        int Numb=GetArea().GetFLineNumb(i);
        if(0<=y || y<MaxLines){
            for(int n=0;n<Numb;n++){
                int x=x1+n;
                if(0<=x && x<DotPerLine){
                    struct SecondDerivativeResult   D;
                    bool ret=CalcMaxSecondDerivative(MasterImage
                            ,x, y, Thr->FocusRadius, D);
                    if(ret==true){
                        if(MaxV<D.maxVal){
                            MaxV=D.maxVal;
						}
                        (VMap[y-Y1])[x-X1]=D.maxVal;
                        (RMap[y-Y1])[x-X1]=D.angle;
					}
                    else{
                        (VMap[y-Y1])[x-X1]=0;
                        (RMap[y-Y1])[x-X1]=0;
					}
                }
            }
		}
    }
    for(int y=0;y<MapYLen;y++){
        float   *lineV=VMap[y];
        for(int x=0;x<MapXLen;x++){
			lineV[x] = 255.0*lineV[x]/MaxV;
        }
    }
    A =0;
    AA=0;
    for(int y=0;y<MapYLen;y++){
        float   *lineV=VMap[y];
        for(int x=0;x<MapXLen;x++){
            double  D=lineV[x];
            A+=D;
            AA+=D*D;
        }
    }
    MakeDividedArea();

    return Ret;
}

qint64 EdgeMatchingItem::GetVArea(FlexArea *A,double  AvrV)
{
    qint64  VArea=0;
    int Left= GetArea().GetMinX();
	int Top = GetArea().GetMinY();
    int MaxLines    =GetMaxLines();
    int DotPerLine  =GetDotPerLine();
    int N=A->GetFLineLen();
    for(int i=0;i<N;i++){
        int x1  =A->GetFLineLeftX(i);
        int y   =A->GetFLineAbsY(i);
        int Numb=A->GetFLineNumb(i);
        if(0<=y || y<MaxLines){
            float   *lineV=VMap[y-Top];
            for(int n=0;n<Numb;n++){
                int x=x1+n;
                if(0<=x && x<DotPerLine){
                    if(fabs(lineV[x-Left])>AvrV){
                    VArea++;
                    }
                }
            }
        }
    }
    return VArea;
}

double EdgeMatchingItem::GetVSum(FlexArea *A)
{
    double  VSum=0;
    int Left= GetArea().GetMinX();
	int Top = GetArea().GetMinY();
    int MaxLines    =GetMaxLines();
    int DotPerLine  =GetDotPerLine();
    int N=A->GetFLineLen();
    for(int i=0;i<N;i++){
        int x1  =A->GetFLineLeftX(i);
        int y   =A->GetFLineAbsY(i);
        int Numb=A->GetFLineNumb(i);
        if(0<=y || y<MaxLines){
            float   *lineV=VMap[y-Top];
            for(int n=0;n<Numb;n++){
                int x=x1+n;
                if(0<=x && x<DotPerLine){
                    VSum+=fabs(lineV[x-Left]);
                }
            }
        }
    }
    return VSum;
}

class FlexAreaWithInt : public FlexArea
{
public:
	qint64  Value;
    double  Avr;
	bool	IsValid;
	int		IndexX,IndexY;

    FlexAreaWithInt(void){}

    FlexAreaWithInt &operator=(const FlexArea &src)
    {
        FlexArea::operator=(src);
        Value = 0;
        Avr     =0;
        IsValid = false;
        IndexX = -1;
        IndexY = -1;
        return *this;
	}
};

void    EdgeMatchingItem::CalcAA(EdgeMatchingItem::DividedArea *d)
{
    d->A    =0;
	d->AA   =0;
    int Left= GetArea().GetMinX();
	int Top = GetArea().GetMinY();
    int MaxLines    =GetMaxLines();
    int DotPerLine  =GetDotPerLine();
    int N=d->Area.GetFLineLen();
    for(int i=0;i<N;i++){
        int x1  =d->Area.GetFLineLeftX(i);
        int y   =d->Area.GetFLineAbsY(i);
        int Numb=d->Area.GetFLineNumb(i);
        if(0<=y || y<MaxLines){
            float   *lineV=VMap[y-Top];
            for(int n=0;n<Numb;n++){
                int x=x1+n;
                if(0<=x && x<DotPerLine){
                    double D=lineV[x-Left];
                    d->A+=D;
					d->AA += D*D;
                }
            }
        }
    }
}

double	EdgeMatchingItem::CalcDividedCoef(EdgeMatchingItem::DividedArea &DArea,int dx,int dy)
{
    int Mx=(TargetMapXLen-MapXLen)/2;
    int My=(TargetMapYLen-MapYLen)/2;
    int Left= GetArea().GetMinX();
	int Top = GetArea().GetMinY();
    double  B=0;
    double  BB=0;
    double  AB=0;
    int     Err=0;
    int N=DArea.Area.GetFLineLen();
    int MaxLines    =GetMaxLines();
    int DotPerLine  =GetDotPerLine();
    for(int i=0;i<N;i++){
        int x1  =DArea.Area.GetFLineLeftX(i);
        int y   =DArea.Area.GetFLineAbsY(i);
        int Numb=DArea.Area.GetFLineNumb(i);
        if(0<=y || y<MaxLines){
            float   *lineV=VMap[y-Top];
            int ty=Mx+y+dy-Top;
            if(0<=ty && ty<TargetMapYLen){
                float   *TargetV=TargetMap[ty];
                for(int n=0;n<Numb;n++){
                     int x=x1+n;
                     if(0<=x && x<DotPerLine){
                         double D=lineV[x-Left];
                         int tx=My+x+dx-Left;
                         if(0<=tx && tx<TargetMapXLen){
                             double   tD=TargetV[tx];
                             AB+=D*tD;
                             B+=tD;
                             BB+=tD*tD;
                         }
                         else{
                             Err++;
                         }
                     }
                     else{
                         Err++;
                     }
                }
            }
            else{
                Err++;
            }
        }
        else{
            Err++;
        }
    }
	int  Numb = DArea.Area.GetPatternByte();
    double  AvrS=DArea.A/Numb;
    double  AvrD=B/Numb;
    double  M=(DArea.AA-AvrS*AvrS*Numb)*(BB-AvrD*AvrD*Numb);
    if(M>=0){
        M=sqrt(M);
        double  C=(AB-AvrS*AvrD*Numb)/M;
        return C;
    }
    return 0;
}


void	EdgeMatchingItem::MakeDividedArea(void)
{
	int W = GetArea().GetWidth();
	int H = GetArea().GetHeight();
    int Left= GetArea().GetMinX();
	int Top = GetArea().GetMinY();
    int MaxLines    =GetMaxLines();
    int DotPerLine  =GetDotPerLine();
    int N=GetArea().GetFLineLen();
	double  AddedV=0;
	float   PeakV = 0;
    for(int i=0;i<N;i++){
        int x1=GetArea().GetFLineLeftX(i);
        int y =GetArea().GetFLineAbsY(i);
        int Numb=GetArea().GetFLineNumb(i);
        if(0<=y || y<MaxLines){
            float   *lineV=VMap[y-Top];
            for(int n=0;n<Numb;n++){
                int x=x1+n;
                if(0<=x && x<DotPerLine){
					float   v = fabs(lineV[x-Left]);
					AddedV += v;
					if(v > PeakV){
						PeakV = v;
					}
                }
            }
		}
    }
    double  AvrV;
    if(GetArea().GetPatternByte()==0){
        AvrV=0;
    }
    else{
        AvrV = AddedV/GetArea().GetPatternByte();
	}
    AvrV    =(PeakV+AvrV)/2;

	int NumbX = (W+GetThresholdR()->BlockSizeX-1)/GetThresholdR()->BlockSizeX;
	int NumbY = (H+GetThresholdR()->BlockSizeY-1)/GetThresholdR()->BlockSizeY;

	int MinArea=20;
    FlexAreaWithInt   **AreaDim;
	AreaDim = new FlexAreaWithInt *[NumbY];
    for(int iy=0;iy<NumbY;iy++){
        AreaDim[iy] = new FlexAreaWithInt[NumbX];
        for(int ix=0;ix<NumbX;ix++){
            int x1 = GetArea().GetMinX() + ix*GetThresholdR()->BlockSizeX;
            int y1 = GetArea().GetMinY() + iy*GetThresholdR()->BlockSizeY;
            int x2 = min((int)(x1+GetThresholdR()->BlockSizeX-1),GetArea().GetMaxX());
            int y2 = min((int)(y1+GetThresholdR()->BlockSizeY-1),GetArea().GetMaxY());
            FlexAreaWithInt    *A=&(AreaDim[iy])[ix];
			*A = GetArea();
			A->ClipArea(x1,y1,x2,y2);
            A->Value=GetVArea(A,AvrV);
            if(A->GetPatternByte()!=0){
			    A->Avr = GetVSum(A)/A->GetPatternByte();
            }
            else{
				A->Avr = 0;
            }
			A->IsValid = (A->GetPatternByte()>0 && A->Value>=MinArea);
        }
    }

    for(int iy=0;iy<NumbY;iy++){
        for(int ix=0;ix<NumbX;ix++){
            FlexAreaWithInt    *A=&(AreaDim[iy])[ix];
            if(A->IsValid==false){
				int iCx,iCy;
                A->GetCenter(iCx,iCy);
				int MinLen = 1000000;
				int MinTx = -1;
				int MinTy = -1;
                for(int ty=0;ty<NumbY;ty++){
                    for(int tx=0;tx<NumbX;tx++){
                        FlexAreaWithInt    *M=&(AreaDim[ty])[tx];
                        if(M->IsValid==true){
							int tCx,tCy;
                            M->GetCenter(tCx,tCy);
							double  Len = hypot(tCx-iCx,tCy-iCy);
                            if(Len<MinLen){
								MinLen = Len;
								MinTx = tx;
								MinTy = ty;
                            }
                        }
                    }
                }
                if(MinTx>=0 && MinTy>=0){
					A->IndexX = MinTx;
					A->IndexY = MinTy;
                }
			}
        }
    }

    for(int iy=0;iy<NumbY;iy++){
        for(int ix=0;ix<NumbX;ix++){
            FlexAreaWithInt    *A=&(AreaDim[iy])[ix];
            if(A->IsValid==false && A->IndexX>=0 && A->IndexY>=0){
                FlexAreaWithInt    *M=&(AreaDim[A->IndexY])[A->IndexX];
				(*M) += *A;
				M->Value += A->Value;
				A->Clear();
			}
        }
    }

	DividedAreas.RemoveAll();
    for(int iy=0;iy<NumbY;iy++){
        for(int ix=0;ix<NumbX;ix++){
            FlexAreaWithInt    *A=&(AreaDim[iy])[ix];
            if(A->GetPatternByte()>0){
				DividedArea *d = new DividedArea;
                d->Area=*A;
                d->ResultCoef=0;
                CalcAA(d);
				DividedAreas.AppendList(d);
			}
        }
    }
    for(int iy=0;iy<NumbY;iy++){
        delete  []AreaDim[iy];
    }
    delete  []AreaDim;
}

ExeResult EdgeMatchingItem::ExecuteStartByInspection(int ExeID, int ThreadNo, ResultInItemRoot *Res)
{
    ResultDx = 0;
    ResultDy = 0;
    ResultRotation = 0;
	ShiftByGlobalX=0;
	ShiftByGlobalY=0;
    GlobalRotation=0;
    for(DividedArea *d=DividedAreas.GetFirst();d!=NULL;d=d->GetNext()){
        d->ResultCoef=0;
	}

    return AlgorithmItemPI::ExecuteStartByInspection(ExeID, ThreadNo, Res);
}

ExeResult	EdgeMatchingItem::ExecuteProcessing		(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
    ExeResult Ret = AlgorithmItemPI::ExecuteProcessing(ExeID, ThreadNo, Res);
	ShiftByGlobalX=0;
	ShiftByGlobalY=0;
    GlobalRotation=0;
	if(AVector!=NULL){
		ShiftByGlobalX=AVector->ShiftX;
		ShiftByGlobalY=AVector->ShiftY;
        GlobalRotation=AVector->Rotation;
	}
	else{
		AlignmentPacket2D	V;
		V.PosXOnTarget=MasterCx;
		V.PosYOnTarget=MasterCy;
		V.ShiftX=0;
		V.ShiftY=0;
		Parent->GetAlignmentForProcessing(V);
		ShiftByGlobalX=V.ShiftX;
		ShiftByGlobalY=V.ShiftY;
        GlobalRotation=V.Rotation;
	}
	const EdgeMatchingThreshold *RThr = GetThresholdR();
    ImagePointerContainer TargetImageList;
    GetTargetBuffList(TargetImageList);
    ImageBuffer *TargetImage = TargetImageList[AdoptedLayer];

    double  MaxV=0;
    for(int ky=0;ky<TargetMapYLen;ky++){
        int y=TargetY1+ky+ShiftByGlobalY;
        float   *TargetV=TargetMap[y-TargetY1-ShiftByGlobalY];
        if(0<=y || y<GetMaxLines()){
            for(int kx=0;kx<TargetMapXLen;kx++){
                int x=TargetX1+kx+ShiftByGlobalX;
                if(0<=x && x<GetDotPerLine()){

                    struct SecondDerivativeResult   D;
                    bool ret=CalcMaxSecondDerivative(TargetImage
                            ,x, y, RThr->FocusRadius, D);
                    if(ret==true){
                        if(MaxV<D.maxVal){
                            MaxV=D.maxVal;
						}
                        TargetV[x-TargetX1-ShiftByGlobalX]=D.maxVal;
					}
                    else{
                        TargetV[x-TargetX1-ShiftByGlobalX]=0;
					}
                }
                else{
                    TargetV[x-TargetX1-ShiftByGlobalX]=0;
                }
            }
		}
        else{
            for(int kx=0;kx<TargetMapXLen;kx++){
                int x=TargetX1+kx+ShiftByGlobalX;
                TargetV[x-TargetX1-ShiftByGlobalX]=0;
            }
        }
    }

    int Mx=(TargetMapXLen-MapXLen)/2;
    int My=(TargetMapYLen-MapYLen)/2;
    double  Numb=MapXLen*MapYLen;
    double  MaxC=0;

    for(int dy=-RThr->SearchDotY;dy<=RThr->SearchDotY;dy++){
        for(int dx=-RThr->SearchDotX;dx<=RThr->SearchDotX;dx++){
            if(0<=(My-dy) && (MapYLen+My+dy)<TargetMapYLen
            && 0<=(Mx-dx) && (MapXLen+Mx+dx)<TargetMapXLen){

                double  B=0;
                double  BB=0;
                double  AB=0;
                double  CosS=cos(GlobalRotation);
                double  SinS=sin(GlobalRotation);


                for(int y=0;y<MapYLen;y++){
					float *lineV = VMap[y];
                    float *TargetV=TargetMap[y+Mx+dy];
                    for(int x=0;x<MapXLen;x++){
                        double  s=lineV[x];
                        double  d=TargetV[x+My+dx];
                        B+=d;
                        BB+=d*d;
                        AB+=s*d;
                    }
                }

                double  AvrS=A/Numb;
                double  AvrD=B/Numb;
                double  M=(AA-AvrS*AvrS*Numb)*(BB-AvrD*AvrD*Numb);
                if(M>=0){
                    M=sqrt(M);
                    double  C=(AB-AvrS*AvrD*Numb)/M;
                    if(MaxC<C){
                        MaxC=C;
                        ResultDx=dx;
                        ResultDy=dy;
                    }
                }
            }
        }
    }
    for(DividedArea *d=DividedAreas.GetFirst();d!=NULL;d=d->GetNext()){
	    d->ResultCoef=CalcDividedCoef(*d,ResultDx,ResultDy);
    }

    ResultDx+=ShiftByGlobalX;
    ResultDy+=ShiftByGlobalY;

    if(RThr->UseDivided==true){
        double  DividedMaxC=1.0;
        for(DividedArea *d=DividedAreas.GetFirst();d!=NULL;d=d->GetNext()){
            if(DividedMaxC>d->ResultCoef){
                DividedMaxC=d->ResultCoef;
            }
        }
        if(DividedMaxC>=RThr->ThresholdDiv){
            Res->SetError(1);
            Res->SetResultDouble(DividedMaxC);
        }
        else{
            Res->SetError(2);
            Res->SetAlignedXY(ResultDx,ResultDy);
            Res->SetResultDouble(DividedMaxC);
        }
    }
	else{
        if(MaxC>=RThr->ThresholdDiv){
	    	Res->SetError(1);
            Res->SetResultDouble(MaxC);
	    }
	    else{
	    	Res->SetError(2);
            Res->SetAlignedXY(ResultDx,ResultDy);
            Res->SetResultDouble(MaxC);
	    }
    }
    return Ret;
}
ExeResult	EdgeMatchingItem::ExecutePostProcessing	(int ExeID ,int ThreadNo,ResultInItemRoot *Res)
{
    ExeResult Ret = AlgorithmItemPI::ExecutePostProcessing(ExeID, ThreadNo, Res);
    return Ret;
}

void EdgeMatchingItem::CopyThresholdOnly(EdgeMatchingItem *src)
{
    GetThresholdW()->CopyFrom(*src->GetThresholdR());
    SetInvertLogic(src->GetInvertLogic());
}