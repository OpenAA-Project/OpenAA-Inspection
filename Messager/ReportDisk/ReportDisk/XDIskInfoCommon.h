#if	!defined(XDISKINFOCOMMON_H)
#define	XDISKINFOCOMMON_H

#include "NListComp.h"
#include <QString>
#include "XDateTime.h"
#include <time.h>
#include "XTypeDef.h"
#include "XGeneralFunc.h"

class	DiskFileInfo : public NPListSaveLoad<DiskFileInfo>
{
public:
	QString		PCName;
	QString		Path;
	QString		FileName;
	qint64		Size;
	XDateTime	UpdatedTime;

	DiskFileInfo(void){	Size=0;	}

	virtual	bool Save(QIODevice *f);
	virtual	bool Load(QIODevice *f);

	DiskFileInfo	&operator=(DiskFileInfo &src);
};

class	DiskFileInfoContainer : public NPListPackSaveLoad<DiskFileInfo>
{
public:
	DiskFileInfoContainer(void){}
	virtual	DiskFileInfo	*Create(void){	return new DiskFileInfo();	}
};

//------------------------------------------------------------------------
inline	bool DiskFileInfo::Save(QIODevice *f)
{
	if(::Save(f,PCName)==false)
		return false;
	if(::Save(f,Path)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Size)==false)
		return false;
	if(::Save(f,UpdatedTime)==false)
		return false;
	return true;
}

inline	bool DiskFileInfo::Load(QIODevice *f)
{
	if(::Load(f,PCName)==false)
		return false;
	if(::Load(f,Path)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Size)==false)
		return false;
	if(::Load(f,UpdatedTime)==false)
		return false;
	return true;
}

inline	DiskFileInfo	&DiskFileInfo::operator=(DiskFileInfo &src)
{
	PCName	=src.PCName;
	Path	=src.Path;
	FileName=src.FileName;
	Size	=src.Size;
	UpdatedTime	=src.UpdatedTime;
	return *this;
}

#endif