#pragma once

#include "filtershiftbylayer_global.h"
#include "XFilterClass.h"
#include "XDLLType.h"
#include "XMainSchemeMemory.h"
#include "NListComp.h"

class	ImageBuffer;

class	ShiftXYList : public NPListSaveLoad<ShiftXYList>
{
public:
	int	Layer;
	int	ShiftX,ShiftY;

	ShiftXYList(void);
	ShiftXYList(const ShiftXYList &src);

	ShiftXYList	&operator=(const ShiftXYList &src);
	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class	ShiftXYInPageContainer : public NPListPackSaveLoad<ShiftXYList>
								,public NPListSaveLoad<ShiftXYInPageContainer>
{
public:
	int	Page;

	ShiftXYInPageContainer(void);
	ShiftXYInPageContainer(const ShiftXYInPageContainer &src);

	virtual	ShiftXYList	*Create(void)	override;
	ShiftXYInPageContainer	&operator=(const ShiftXYInPageContainer &src);

	ShiftXYList	*Find(int layer);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};
class	ShiftXYInPhaseContainer :public NPListPackSaveLoad<ShiftXYInPageContainer>
								,public NPListSaveLoad<ShiftXYInPhaseContainer>
{
public:
	int	Phase;

	ShiftXYInPhaseContainer(void);
	ShiftXYInPhaseContainer(const ShiftXYInPhaseContainer &src);

	virtual	ShiftXYInPageContainer	*Create(void)	override;
	ShiftXYInPhaseContainer	&operator=(const ShiftXYInPhaseContainer &src);

	ShiftXYInPageContainer	*Find(int page);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
};

class	ShiftXYInfo :public NPListPackSaveLoad<ShiftXYInPhaseContainer>
{
public:
	ShiftXYInfo(void);
	ShiftXYInfo(const ShiftXYInfo &src);

	ShiftXYInfo	&operator=(const ShiftXYInfo &src);
	
	virtual	ShiftXYInPhaseContainer	*Create(void)	override;

	ShiftXYInPhaseContainer	*Find(int phase);
};


class	FilterShiftByLayer : public FilterClassBase
{
public:
	ShiftXYInfo	ShiftInfo;

	FilterShiftByLayer(LayersBase *base);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;
	virtual	bool	Execute(ImageBuffer *Buff[],int BufferDimCounts)	override;
	virtual	bool	Initial(void)	override;
	virtual	bool	Release(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	QString	GetDataText(void)			override{	return "ShiftByLayer";	}
	virtual	QString	GetDefaultFileName(void)	override{	return "FilterShiftByLayer.dat";	}

private:
	void	ExecuteShift(ImageBuffer *Buff,int ShiftX,int ShiftY);
};
