#pragma once

#include "NListComp.h"
#include <QString>
#include "XServiceForLayers.h"
#include "XTypeDef.h"

class LevelFolder;

class LevelFolderContainer final
			: public NPListPackSaveLoad<LevelFolder>,public ServiceForLayers
{
public:
	explicit	LevelFolderContainer(LayersBase *base);
	LevelFolderContainer(const LevelFolderContainer &src);

	LevelFolder	*Create(void);

	LevelFolderContainer	&operator=(const LevelFolderContainer &src);

	LevelFolder	*FindByLevelID(int LevelID);
	LevelFolder	*FindByLevelValue(int LevelParentID,int LevelValue);
	bool	RemoveByLevelID(int LevelID);
	bool	BuildFromDB(int ParentID=0	/*From top*/);
	int		GetMaxLevelID(void);
private:
	LevelFolder *RemoveByLevelIDInner(int LevelID);
};


class LevelFolder : public NPListSaveLoad<LevelFolder>,public ServiceForLayers
{
public:
	int		LevelID		;
	int		LevelValue	;		//Order in folder	0,1,2,3...
	int		ParentID	;		//0:Top root
	QString	LevelName	;
	QString	Remark		;
	LevelFolderContainer	Children;

	explicit	LevelFolder(LayersBase *base);
	LevelFolder(const LevelFolder &src);

	LevelFolder	&operator=(const LevelFolder &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	int	Compare(LevelFolder &src)	override;

};

