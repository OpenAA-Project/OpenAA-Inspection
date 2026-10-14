#include "XAlignmentShiftRotationLibrary.h"
#include "XGeneralFunc.h"

	
AlignmentShiftRotationLibrary::AlignmentShiftRotationLibrary(int LibType,LayersBase *Base)
	:ServiceForLayers(Base)
{
	Threshold	=20;
	LineCount	=10;
	TargetLayer	=-1;
	LineLen		=6;
	SearchDotX	=30;
	SearchDotY	=30;
	SparseAngle	=1.0;
	Rotation.AppendList(new RotationRange(-5,5));
}


bool	AlignmentShiftRotationLibrary::SaveBlob(QIODevice *f)
{
	if(::Save(f,Threshold)==false)
		return false;
	if(::Save(f,LineCount)==false)
		return false;
	if(::Save(f,TargetLayer)==false)
		return false;
	if(::Save(f,LineLen)==false)
		return false;

	if(::Save(f,SearchDotX)==false)
		return false;
	if(::Save(f,SearchDotY)==false)
		return false;

	if(::Save(f,SparseAngle)==false)
		return false;

	if(Rotation.Save(f)==false)
		return false;

	return true;
}
bool	AlignmentShiftRotationLibrary::LoadBlob(QIODevice *f)
{
	if(::Load(f,Threshold)==false)
		return false;
	if(::Load(f,LineCount)==false)
		return false;
	if(::Load(f,TargetLayer)==false)
		return false;
	if(::Load(f,LineLen)==false)
		return false;

	if(::Load(f,SearchDotX)==false)
		return false;
	if(::Load(f,SearchDotY)==false)
		return false;

	if(::Load(f,SparseAngle)==false)
		return false;

	if(Rotation.Load(f)==false)
		return false;

	return true;
}

AlignmentShiftRotationLibrary	&AlignmentShiftRotationLibrary::operator=(const AlgorithmLibrary &src)
{
	AlignmentShiftRotationLibrary *s = dynamic_cast<AlignmentShiftRotationLibrary *>((AlgorithmLibrary *)&src);
	Threshold	=s->Threshold	;
	LineCount	=s->LineCount	;
	TargetLayer	=s->TargetLayer	;
	LineLen		=s->LineLen		;
	SearchDotX	=s->SearchDotX	;
	SearchDotY	=s->SearchDotY	;
	SparseAngle	=s->SparseAngle;
	Rotation	=s->Rotation;
	return *this;
}

void	AlignmentShiftRotationLibrary::MakeReportedTopics(ReportedTopicContainer &RetContainer)	const
{
	RetContainer.AppendListItem(new ReportedTopic("Threshold",Threshold));
	RetContainer.AppendListItem(new ReportedTopic("LineCount",LineCount));
	RetContainer.AppendListItem(new ReportedTopic("TargetLayer",TargetLayer));
	RetContainer.AppendListItem(new ReportedTopic("LineLen",LineLen));
	RetContainer.AppendListItem(new ReportedTopic("SearchDotX",SearchDotX));
	RetContainer.AppendListItem(new ReportedTopic("SearchDotY",SearchDotY));
	RetContainer.AppendListItem(new ReportedTopic("SparseAngle",SparseAngle));

	//ReportedTopicContainer *sub = new ReportedTopicContainer("Rotation");
	//for(RotationRange *r=Rotation.GetFirst();r!=NULL;r=r->GetNext()){
	//	ReportedTopicContainer *sub2 = new ReportedTopicContainer("Range");
	//	sub2->AppendListItem(new ReportedTopic("MinAngleDegree",r->MinAngleDegree));
	//	sub2->AppendListItem(new ReportedTopic("MaxAngleDegree",r->MaxAngleDegree));
	//	sub->AppendListItem(sub2);
	//}
	//RetContainer.AppendListItem(sub);
}

AlignmentShiftRotationLibraryContainer::AlignmentShiftRotationLibraryContainer(LayersBase *base)
	:AlgorithmLibraryContainer(base)
{
}