/*
 * Copyright (C) 2016
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

#if	!defined(XReviewCameraCommon_h)
#define	XReviewCameraCommon_h

#include <QIODevice>
#include <QWidget>
#include "XTypeDef.h"
#include "XGUIPacketForDLL.h"
#include <QImage>


class	CmdReqImageFromReviewCamera : public GUIDirectMessage
{
public:
	int		ImageWidth;
	int		ImageHeight;
	QImage	Image;
	bool	Result;

	CmdReqImageFromReviewCamera(LayersBase *base)
		:GUIDirectMessage(base){	ImageWidth=0;	ImageHeight=0;	}
};


#endif