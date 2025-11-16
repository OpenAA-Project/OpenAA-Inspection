#pragma once

#include "resultcategorizer_global.h"
#include "XResultAnalizer.h"
#include "NListComp.h"
#include <QString>

#define	VersionResultCategorizer	1

class	ImageBuffer;
class	ResultInItemRoot;
class	ResultPosList;

class	ResultCatShape : public NPListSaveLoad<ResultCatShape>
{
public:
	int		CategoryID;	//  >1
	int32	Phase;
	int32	Priority;
	QString	ResultName;
	struct LayerJudgement
	{
		int	MinLength	;
		int	MaxLength	;
		int	MinPixels	;
		int	MaxPixels	;
		int	BrightDiffL	;
		int	BrightDiffH	;

		LayerJudgement(void);

		bool	Save(QIODevice *f);
		bool	Load(QIODevice *f);
	};
	struct LayerJudgement	Judge[3];

	explicit	ResultCatShape(void);

	virtual	bool	Save(QIODevice *f)		override;	
	virtual	bool	Load(QIODevice *f)		override;
	virtual	int	Compare(ResultCatShape &src)override;

	void	Execute(ResultInItemRoot *Res
					,ImageBuffer *MasterImageList[] 
					,ImageBuffer *TargetImageList[]
					,int LayerNumb);

private:
	bool	Execute(ResultInItemRoot *Res
					,ResultPosList *r
					,ImageBuffer *MasterImageList[] 
					,ImageBuffer *TargetImageList[]
					,int LayerNumb);
};

class	ResultCatShapeContainer : public NPListPackSaveLoad<ResultCatShape>
{
public:
	explicit	ResultCatShapeContainer(void){}

	virtual	ResultCatShape	*Create(void);
};


class  ResultCategorizer : public ResultAnalizerItemBase
{
public:
	ResultCatShapeContainer	ResultCat;

	explicit	ResultCategorizer(LayersBase *Base);
	~ResultCategorizer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	ShowSettingDialogFunc(void) override;

	void		Allocate(void);

	void		ExecuteStartByInspection(void);
	ExeResult	Execute(ResultInItemRoot *Res);
private:
};
