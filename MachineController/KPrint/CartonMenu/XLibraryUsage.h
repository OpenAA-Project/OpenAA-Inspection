#pragma once
#include "NListComp.h"
#include <QString>
#include "XAlgorithmLibrary.h"

class LibraryUsage : public NPListSaveLoad<LibraryUsage>
{
public:
	QString	UsageName;
	//int		LibType;
	//int		LibID;
	AlgorithmLibraryListContainer	LibList;
	int		AlignmentPriority;
	bool	DefaultPushed;

	LibraryUsage(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);
};

class LibraryUsageContainer : public NPListPackSaveLoad<LibraryUsage>
{
public:
	LibraryUsageContainer(void){}
	virtual	LibraryUsage	*Create(void)	override;
};
