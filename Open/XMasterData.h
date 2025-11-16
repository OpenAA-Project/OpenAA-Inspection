#pragma once

#include "XTypeDef.h"
#include "NList.h"
#include <QString>
#include <QIODevice>

//========================================================================================

class	LoadedInfoList : public NPList<LoadedInfoList>
{
public:
	QString		AlgoRoot;
	QString		AlgoName;
	QString		FileName;
	enum LoadedStatus{
			 _None		=0
			,_Success	=1
			,_NoFile	=2
			,_Error		=3
	};
	int64			ItemCount;
	LoadedStatus	Error;

	LoadedInfoList(void);
	LoadedInfoList(const LoadedInfoList &src);

	virtual	~LoadedInfoList(void);

	LoadedInfoList	&operator=(const LoadedInfoList &src);

	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};


class	LoadedInfoContainerInPhase : public NPListPack<LoadedInfoList>
{
public:
	int		Phase;
	bool	SuccessForImage;

	LoadedInfoContainerInPhase(void)
		:Phase(-1),SuccessForImage(false){}
	LoadedInfoContainerInPhase(const LoadedInfoContainerInPhase &src);

	virtual	~LoadedInfoContainerInPhase(void);

	LoadedInfoContainerInPhase	&operator=(const LoadedInfoContainerInPhase &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

class	LoadedInfoContainerInPhaseList : public LoadedInfoContainerInPhase ,public NPList<LoadedInfoContainerInPhaseList>
{
public:
	LoadedInfoContainerInPhaseList(void){}
	LoadedInfoContainerInPhaseList(const LoadedInfoContainerInPhaseList &src);
	virtual	~LoadedInfoContainerInPhaseList(void);

	LoadedInfoContainerInPhaseList	&operator=(const LoadedInfoContainerInPhaseList &src);
};

class	LoadedInfoContainer : public NPListPack<LoadedInfoContainerInPhaseList>
{
public:
	LoadedInfoContainer(void){}
	LoadedInfoContainer(const LoadedInfoContainer &src);
	virtual	~LoadedInfoContainer(void);

	LoadedInfoContainer	&operator=(const LoadedInfoContainer &src);
	bool	Load(QIODevice *f);
	bool	Save(QIODevice *f);
};

