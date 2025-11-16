#if	!defined(XLIBFOLDEROPERATION_H)
#define	XLIBFOLDEROPERATION_H

#include "XTypeDef.h"
#include "XFlexArea.h"

class	StandardPropertyForm
{
public:
	StandardPropertyForm(void){}

	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)=0;
};

#endif