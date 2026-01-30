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

#include "XTypeDef.h"
#include"XFlexAreaImageBuffer.h"

FlexAreaImageBuffer::FlexAreaImageBuffer(const FlexAreaImageBuffer &src)
{
	Area=src.Area;
	Image=src.Image;
}

bool	FlexAreaImageBuffer::Save(QIODevice *f)
{
	if(Area.Save(f)==false)
		return false;
	if(Image.Save(f)==false)
		return false;
	return true;
}

bool	FlexAreaImageBuffer::Load(QIODevice *f)
{
	if(Area.Load(f)==false)
		return false;
	if(Image.Load(f)==false)
		return false;
	return true;
}

void	FlexAreaImageBuffer::Copy(const FlexArea &Src ,ImageBuffer &SrcImage ,int mergin)
{
	int	X=Src.GetMinX();
	int	Y=Src.GetMinY();
	Area=Src;
	Area.MoveToNoClip(-X+mergin,-Y+mergin);
	int	W=Src.GetWidth();
	int	H=Src.GetHeight();
	Image.Set(0,0,W+mergin*2,H+mergin*2);
	Image.PartialCopy(SrcImage,X-mergin,Y-mergin);

}

FlexAreaImageBuffer	&FlexAreaImageBuffer::operator=(FlexAreaImageBuffer &src)
{
	Area=src.Area;
	Image.Set(0,0,src.GetImage().GetWidth(), src.GetImage().GetHeight());
	Image=src.Image;
	return *this;
}