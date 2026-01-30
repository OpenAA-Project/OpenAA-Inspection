/*
 * Copyright (C) 2017
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

//#include "SelectLotForReviewResource.h"
#include "SelectLotForReviewPacket.h"
#include "XGeneralFunc.h"
#include "ReviewStructureItems.h"

bool GUICmdReviewLotList::Save(QIODevice *f)
{
	if(::Save(f, lotList.count())==false)
		return false;
	for(int i=0; i<lotList.count(); i++){
		if(::Save(f, lotList[i].TableName)==false)
			return false;
		if(::Save(f, lotList[i].LotName)==false)
			return false;
		if(::Save(f, lotList[i].Remark)==false)
			return false;
	}

	return true;
}

bool GUICmdReviewLotList::Load(QIODevice *f)
{
	int count;
	if(::Load(f, count)==false)
		return false;

	lotList.clear();
	for(int i=0; i<count; i++){
		LotInfoItem info;
		if(::Save(f, info.TableName)==false)
			return false;
		if(::Save(f, info.LotName)==false)
			return false;
		if(::Save(f, info.Remark)==false)
			return false;
		lotList << info;
	}

	return true;
}