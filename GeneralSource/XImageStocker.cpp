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
#include <cmath>
#include "XImageStocker.h"

ListOfQImage::ListOfQImage(QImage &img)
{
	Img=new QImage();
	*Img=img;
}
ListOfQImage::ListOfQImage(const QString &resourcename)
{
	ResourceName	=resourcename;
	Img				=new QImage(resourcename);
}
ListOfQImage::~ListOfQImage(void)
{
	delete	Img;
	Img=NULL;
}

ListOfQImage	&ListOfQImage::operator=(const ListOfQImage &src)
{
	ResourceName=src.ResourceName;
	*Img=*src.Img;
	return *this;
}

const QImage	&ListOfQImageStocker::GetImage(const QString &resourcename)
{
	for(ListOfQImage *a=GetFirst();a!=NULL;a=a->GetNext()){
		if(a->GetResourceName()==resourcename){
			return a->GetImage();
		}
	}
	ListOfQImage *b=new ListOfQImage(resourcename);
	AppendList(b);
	return b->GetImage();
}