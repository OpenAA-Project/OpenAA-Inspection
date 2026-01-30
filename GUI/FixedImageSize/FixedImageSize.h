/*
 * Copyright (C) 2022
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

#ifndef FIXEDIMAGESIZE_H
#define FIXEDIMAGESIZE_H

#include "fixedimagesize_global.h"
#include "XServiceForLayers.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"


class	FixedImageSize : public GUIFormBase
{
	Q_OBJECT

public:

	int32	PosLeft;
	int32	PosTop;
	int32	PosRight;
	int32	PosBottom;
	QString	DisplayImageName;

	FixedImageSize(LayersBase *Base ,QWidget *parent);
	~FixedImageSize(void);

	virtual void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

private slots:

};
#endif // FIXEDIMAGESIZE_H