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

#include "PropertyRasterForm.h"


RasterFileLayerLine::RasterFileLayerLine(void)
{
	ShownBox=new QCheckBox();
	FileLayerID=-1;
}
RasterFileLayerLine::RasterFileLayerLine(const RasterFileLayerLine &src)
{
	ShownBox=new QCheckBox()	;

	FileLayerID	=-1				;
	FileName	=src.FileName	;
	Color		=src.Color		;
}


void	RasterFileLayerLine::SetShown(bool b)
{
	ShownBox->setChecked(b);

}
bool	RasterFileLayerLine::GetShown(void)
{
	return ShownBox->isChecked();
}

void	RasterFileLayerLine::StoreFromWindow(void)
{
}
void	RasterFileLayerLine::ReflectToWindow(void)
{
}
bool	RasterFileLayerLine::SaveContent(QIODevice *f)
{
	if(::Save(f,FileLayerID)==false)
		return false;
	if(::Save(f,FileName)==false)
		return false;
	if(::Save(f,Color)==false)
		return false;
	return true;
}
bool	RasterFileLayerLine::LoadContent(QIODevice *f)
{
	if(::Load(f,FileLayerID)==false)
		return false;
	if(::Load(f,FileName)==false)
		return false;
	if(::Load(f,Color)==false)
		return false;
	return true;
}