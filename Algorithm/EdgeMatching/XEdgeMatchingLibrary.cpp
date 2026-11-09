#include "XEdgeMatchingLibrary.h"
#include "XGeneralFunc.h"

EdgeMatchingLibrary::EdgeMatchingLibrary(int LibType, LayersBase *Base)
    : ServiceForLayers(Base)
{
    // èâä˙ílê›íË
    SearchDotX         = 30;
    SearchDotY         = 30;
    SearchByPixel      = 10;
    ThresholdDiv       = 0.5;
    ThresholdDirection = 0.5;
    FocusRadius        = 5;
    Layer              = -1; // é©ìÆëIë
}

bool EdgeMatchingLibrary::SaveBlob(QIODevice *f)
{
    if(::Save(f, SearchDotX) == false)      return false;
    if(::Save(f, SearchDotY) == false)      return false;
    if(::Save(f, SearchByPixel) == false)   return false;
    if(::Save(f, ThresholdDiv) == false)    return false;
    if(::Save(f, ThresholdDirection) == false) return false;
    if(::Save(f, FocusRadius) == false)     return false;
    if(::Save(f, Layer) == false)           return false;

    return true;
}

bool EdgeMatchingLibrary::LoadBlob(QIODevice *f)
{
    if(::Load(f, SearchDotX) == false)      return false;
    if(::Load(f, SearchDotY) == false)      return false;
    if(::Load(f, SearchByPixel) == false)   return false;
    if(::Load(f, ThresholdDiv) == false)    return false;
    if(::Load(f, ThresholdDirection) == false) return false;
    if(::Load(f, FocusRadius) == false)     return false;
    if(::Load(f, Layer) == false)           return false;

    return true;
}

EdgeMatchingLibrary &EdgeMatchingLibrary::operator=(const AlgorithmLibrary &src)
{
    EdgeMatchingLibrary *s = dynamic_cast<EdgeMatchingLibrary *>((AlgorithmLibrary *)&src);
    if(s != nullptr) {
        SearchDotX         = s->SearchDotX;
        SearchDotY         = s->SearchDotY;
        SearchByPixel      = s->SearchByPixel;
        ThresholdDiv       = s->ThresholdDiv;
        ThresholdDirection = s->ThresholdDirection;
        FocusRadius        = s->FocusRadius;
        Layer              = s->Layer;
    }
    return *this;
}

void EdgeMatchingLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer) const
{
    RetContainer.AppendListItem(new ReportedTopic("SearchDotX", SearchDotX));
    RetContainer.AppendListItem(new ReportedTopic("SearchDotY", SearchDotY));
    RetContainer.AppendListItem(new ReportedTopic("SearchByPixel", SearchByPixel));
    RetContainer.AppendListItem(new ReportedTopic("ThresholdDiv", ThresholdDiv));
    RetContainer.AppendListItem(new ReportedTopic("ThresholdDirection", ThresholdDirection));
    RetContainer.AppendListItem(new ReportedTopic("FocusRadius", FocusRadius));
    RetContainer.AppendListItem(new ReportedTopic("Layer", Layer));
}

EdgeMatchingLibraryContainer::EdgeMatchingLibraryContainer(LayersBase *base)
    : AlgorithmLibraryContainer(base)
{
}