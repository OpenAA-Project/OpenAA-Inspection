/*
 * Copyright (C) 2023
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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