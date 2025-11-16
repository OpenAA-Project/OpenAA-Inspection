#pragma once
#include "NListComp.h"
#include <QIODevice>

class LibIDListWithResult : public NPListSaveLoad<LibIDListWithResult>
{
public:
	int		LibType	;
	int		LibID	;
	int		Result	;	//0:Not inspect ,1:OK	2:NG

	LibIDListWithResult(void);
	LibIDListWithResult(const LibIDListWithResult &src);

	LibIDListWithResult	&operator=(const LibIDListWithResult &src);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class LibIDListWithResultContainer : public NPListPackSaveLoad<LibIDListWithResult>
{
public:
	LibIDListWithResultContainer(void);
	LibIDListWithResultContainer(const LibIDListWithResultContainer &src);

	LibIDListWithResultContainer	&operator=(const LibIDListWithResultContainer &src);
	void	Merge(const LibIDListWithResultContainer &src);

	virtual	LibIDListWithResult	*Create(void)	override;
};
