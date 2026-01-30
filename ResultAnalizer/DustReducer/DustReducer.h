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

#ifndef DUSTREDUCER_H
#define DUSTREDUCER_H

#include "dustreducer_global.h"
#include "XResultAnalizer.h"

class	ImageBuffer;

struct	DustReducerResult
{
	int	Phase;
	int	Page;
	int	Layer;
	int	ItemID;
	int	PosNo;
	int	Dots;
	int	Length;
	double	S;
	bool	Dust;
};

class  DustReducer : public ResultAnalizerItemBase
{
	BYTE	**NGMap;
	int		XLen;
	int		XByte;
	int		YLen;
public:
	struct	DustReducerResult	*Dim;
	int		AllocatedCount;
	int		WPoint;
public:
	int		VLayer;
	int		BrightnessL;
	int		BrightnessH;
	int		MaxAreaDots;
	int		MaxLength;
	double	MaxV;

	explicit	DustReducer(LayersBase *Base);
	~DustReducer(void);

	virtual	bool	Save(QIODevice *f)	override;
	virtual	bool	Load(QIODevice *f)	override;

	virtual	bool	ShowSettingDialogFunc(void) override;

	void		Allocate(void);

	void		ExecuteStartByInspection(void);
	ExeResult	Execute(ResultInItemRoot *Res);
private:
	bool	IsDust(int Phase ,int Page ,int Layer ,int ItemID, int PosNo,int X,int Y,ImageBuffer &TBuff);
};

#endif // DUSTREDUCER_H