#include "XDataInLayer.h"
#include "XEntryPoint.h"

EntryPointBase::EntryPointBase(void)
{	
	Base=NULL;
	EditMode=false;
	NoCamDevice=false;
}
int	EntryPointBase::GetGlobalPageFromLocal(int localPage)
{	
	return GetLayersBase()->GetGlobalPageFromLocal(localPage);
}
