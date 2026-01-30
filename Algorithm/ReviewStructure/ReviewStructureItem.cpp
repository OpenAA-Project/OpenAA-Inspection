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

#include "ReviewStructureItems.h"
#include "XReviewStructure.h"


HistoryItem::HistoryItem(ReviewPIBase *pBase)
{
	PBase=pBase;
	m_NGReader = new NGImageReaderOneFile(PBase->getProperty().NGImagePath
										,pBase->GetParamGlobal()->TransDatabaseIP
										,pBase->GetParamGlobal()->ImageFileCachePort,NULL);
};

void HistoryItem::createReader(void)
{
	if(m_NGReader==NULL){
		m_NGReader = new NGImageReaderOneFile(PBase->getProperty().NGImagePath
											,PBase->GetParamGlobal()->TransDatabaseIP
											,PBase->GetParamGlobal()->ImageFileCachePort
											,NULL);
		m_NGReader->setFilename(m_Filename);
		m_NGReader->setIDXList(m_IDXList);
	}
};

bool	ReviewNGPoint::operator==(const ReviewNGPoint &src)
{
	if(x==src.x && y==src.y && TypeCode==src.TypeCode && LibCode==src.LibCode)
		return true;
	return false;
}