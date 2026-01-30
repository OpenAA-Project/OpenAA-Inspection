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

#if	!defined(XFlexAreaImageBuffer_H)
#define	XFlexAreaImageBuffer_H

#include "XFlexArea.h"
#include "XMainSchemeMemory.h"

class	FlexAreaImageBuffer
{
	FlexArea	Area;
	ImageBuffer	Image;

public:
	FlexAreaImageBuffer(void){}
	FlexAreaImageBuffer(const FlexAreaImageBuffer &src);

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);

	void	Copy(const FlexArea &Src ,ImageBuffer &SecImage ,int mergin=0);
	FlexAreaImageBuffer	&operator=(FlexAreaImageBuffer &src);
	bool	IsNull(void)		const	{	return Area.IsNull();	}

	FlexArea	&GetArea(void)	const	{	return (FlexArea &)Area;		}
	ImageBuffer	&GetImage(void)	const	{	return (ImageBuffer	&)Image;	}
};

#endif