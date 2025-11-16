#include "XLibraryUsage.h"
#include "XGeneralFunc.h"
#include "XAlgorithmLibrary.h"

LibraryUsage::LibraryUsage(void)
{
	//LibType=0;
	//LibID=0;
	AlignmentPriority=-1;
	DefaultPushed	=false;
}
bool	LibraryUsage::Save(QIODevice *f)
{
	int	Ver=2;

	if(::Save(f,Ver					)	==false)	return false;

	if(::Save(f,UsageName			)	==false)	return false;
	if(LibList.Save(f)==false)						return false;
	if(::Save(f,AlignmentPriority	)	==false)	return false;
	if(::Save(f,DefaultPushed	)	==false)	return false;
	return true;
}
bool	LibraryUsage::Load(QIODevice *f)
{
	int	Ver;
	if(::Load(f,Ver					)	==false)	return false;

	if(::Load(f,UsageName			)	==false)	return false;
	if(Ver>=2){
		if(LibList.Load(f)==false)					return false;
	}
	else{
		int32	tLibType	;
		int32	tLibID	;
		if(::Load(f,tLibType		)	==false)	return false;
		if(::Load(f,tLibID			)	==false)	return false;
		AlgorithmLibraryList	*a=new AlgorithmLibraryList(tLibType,tLibID,/**/"");
		LibList.RemoveAll();
		LibList.AppendList(a);
	}

	if(::Load(f,AlignmentPriority	)	==false)	return false;
	if(::Load(f,DefaultPushed		)	==false)	return false;
	return true;
}

LibraryUsage	*LibraryUsageContainer::Create(void)
{	
	return new LibraryUsage();
}