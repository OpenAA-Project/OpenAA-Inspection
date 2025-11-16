#if	!defined(XAUTOCLASSIFYCOMMON_H)
#define	XAUTOCLASSIFYCOMMON_H

#include "XServiceForLayers.h"
#include "XGeneralFunc.h"
#include "NList.h"


class	AreaInfoList : public NPList<AreaInfoList>
{
public:
	int		LibID;
	int		AreaCount;

	int		GetLibID(void){		return LibID;	}

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

inline	bool	AreaInfoList::Save(QIODevice *f)
{
	if(::Save(f,LibID)==false)
		return false;
	if(::Save(f,AreaCount)==false)
		return false;
	return true;
}
inline	bool	AreaInfoList::Load(QIODevice *f)
{
	if(::Load(f,LibID)==false)
		return false;
	if(::Load(f,AreaCount)==false)
		return false;
	return true;
}



#endif