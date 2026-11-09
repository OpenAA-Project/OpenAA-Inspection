#define _USE_MATH_DEFINES
#include <math.h>
#include "XEdgeMatching.h"
#include "XEdgeMatchingPacket.h"

//===========================================================================
// EdgeMatchingThreshold
//===========================================================================
EdgeMatchingThreshold::EdgeMatchingThreshold(EdgeMatchingItem *parent)
    : AlgorithmThreshold(parent)
{
    SearchDotX = 0;
    SearchDotY = 0;
    SearchByPixel = 0;
    ThresholdDiv = 0.0;
    ThresholdDirection = 0.0;
    FocusRadius = 0;
    Layer = -1;
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
    if (FocusRadius != p->FocusRadius)     return false;
    if (Layer != p->Layer)                 return false;
    
    return true;
}

bool EdgeMatchingThreshold::Save(QIODevice *f)
{
    if (::Save(f, SearchDotX) == false)     return false;
    if (::Save(f, SearchDotY) == false)     return false;
    if (::Save(f, SearchByPixel) == false)  return false;
    if (::Save(f, ThresholdDiv) == false)   return false;
    if (::Save(f, ThresholdDirection) == false) return false;
    if (::Save(f, FocusRadius) == false)    return false;
    if (::Save(f, Layer) == false)          return false;
    
    return true;
}

bool EdgeMatchingThreshold::Load(QIODevice *f)
{
    if (::Load(f, SearchDotX) == false)     return false;
    if (::Load(f, SearchDotY) == false)     return false;
    if (::Load(f, SearchByPixel) == false)  return false;
    if (::Load(f, ThresholdDiv) == false)   return false;
    if (::Load(f, ThresholdDirection) == false) return false;
    if (::Load(f, FocusRadius) == false)    return false;
    if (::Load(f, Layer) == false)          return false;
    
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
    // 独立データ設定処理（Undoスタックの処理等）
}

void EdgeMatchingItem::Clear(void)
{
    ResultDx = 0;
    ResultDy = 0;
    ResultRotation = 0;
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
}

void EdgeMatchingItem::DrawResultItem(ResultInItemRoot *Res, QImage &IData, QPainter &PData, int MovX, int MovY, double ZoomRate, bool OnlyNG)
{
    QColor ce = Qt::red;
    ce.setAlpha(180);

    GetArea().Draw(ResultDx, ResultDy, &IData, ce.rgba(), ZoomRate, MovX, MovY);

    if (ZoomRate >= 1.0) {
        PData.drawText((MasterCx + MovX) * ZoomRate, (MasterCy + MovY) * ZoomRate,
                       QString("dx=") + QString::number((int)ResultDx) + QString(",dy=") + QString::number((int)ResultDy));
    }
}

ExeResult EdgeMatchingItem::ExecuteInitialAfterEdit(int ExeID, int ThreadNo, ResultInItemRoot *Res, ExecuteInitialAfterEditInfo &EInfo)
{
    ExeResult Ret = AlgorithmItemPI::ExecuteInitialAfterEdit(ExeID, ThreadNo, Res, EInfo);
    GetArea().GetCenter(MasterCx, MasterCy);
    // 初期解析処理などをここに実装
    return Ret;
}

ExeResult EdgeMatchingItem::ExecuteStartByInspection(int ExeID, int ThreadNo, ResultInItemRoot *Res)
{
    return AlgorithmItemPI::ExecuteStartByInspection(ExeID, ThreadNo, Res);
}

ExeResult EdgeMatchingItem::ExecuteAlignment(int ExeID, int ThreadNo, ResultInItemRoot *Res)
{
    ExeResult Ret = AlgorithmItemPI::ExecuteAlignment(ExeID, ThreadNo, Res);
    // アライメント計算処理をここに実装
    return Ret;
}

void EdgeMatchingItem::CopyThresholdOnly(EdgeMatchingItem *src)
{
    GetThresholdW()->CopyFrom(*src->GetThresholdR());
    SetInvertLogic(src->GetInvertLogic());
}