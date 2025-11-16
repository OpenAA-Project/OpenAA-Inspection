#include "XMakeDifferencialImage.h"
#include <omp.h>

MakeDifferencialImageThreshold::MakeDifferencialImageThreshold(MakeDifferencialImageItem *parent)
	:AlgorithmThreshold(parent)
{
}

ExeResult	MakeDifferencialImageInPage::ExecutePreAlignment	(int ExeID ,ResultInPageRoot *Res)
{
	MakeDifferencialImageBase	*BBase=(MakeDifferencialImageBase *)GetParentBase();
	if(GetPhaseCode()==BBase->DestinationPhase){
		ImagePointerContainer TargetImages;
		GetTargetImages(TargetImages);

		AlgorithmInPageInOnePhase	*PhSrc1=BBase->GetPageDataPhase(BBase->SourcePair1Phase);
		AlgorithmInPageInOnePhase	*PhSrc2=BBase->GetPageDataPhase(BBase->SourcePair2Phase);
		if(PhSrc1!=NULL && PhSrc2!=NULL){
			AlgorithmInPageRoot	*PageSrc1=PhSrc1->GetPageData(GetPage());
			AlgorithmInPageRoot	*PageSrc2=PhSrc2->GetPageData(GetPage());

			ImagePointerContainer Src1TargetImages;
			PageSrc1->GetTargetImages(Src1TargetImages);
			ImagePointerContainer Src2TargetImages;
			PageSrc2->GetTargetImages(Src2TargetImages);

			ImagePointerList *Src1=Src1TargetImages.GetFirst();
			ImagePointerList *Src2=Src2TargetImages.GetFirst();
			for(ImagePointerList *Dst=TargetImages.GetFirst();Dst!=NULL;Dst=Dst->GetNext()){
				MakeDifferencial(Dst->GetImage(),Src1->GetImage(),Src2->GetImage());
				Src1=Src1->GetNext();
				Src2=Src2->GetNext();
			}
		}
	}
	return _ER_true;
}

void	MakeDifferencialImageInPage::MakeDifferencial(ImageBuffer *Dst ,ImageBuffer *Src1,ImageBuffer *Src2)
{
	int	YNumb=GetMaxLines();
	#pragma omp parallel
	{
		#pragma omp for
		for(int y=0;y<YNumb;y++){
			BYTE	*d=Dst->GetY(y);
			BYTE	*s1=Src1->GetY(y);
			BYTE	*s2=Src2->GetY(y);
			for(int x=0;x<GetDotPerLine();x++){
				*d=(*s1>*s2)?*s1-*s2:*s2-*s1;
				d++;
				s1++;
				s2++;
			}
		}
	}
}

//===========================================
MakeDifferencialImageBase::MakeDifferencialImageBase(LayersBase *Base)
:AlgorithmBase(Base)
{
	SourcePair1Phase	=0;
	SourcePair2Phase	=1;
	DestinationPhase	=2;

	SetParam(&SourcePair1Phase			, /**/"Phase" ,/**/"SourcePair1Phase"			,"Source Pair 1 Phase");
	SetParam(&SourcePair2Phase			, /**/"Phase" ,/**/"SourcePair2Phase"			,"Source Pair 2 Phase");
	SetParam(&DestinationPhase			, /**/"Phase" ,/**/"DestinationPhase"			,"Destination Phase");
}

AlgorithmDrawAttr	*MakeDifferencialImageBase::CreateDrawAttr(void)
{
	return NULL;
}


