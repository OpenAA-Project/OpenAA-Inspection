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



#include "XAlgorithmDLL.h"
#include "XOutlineInspect.h"


DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=/**/"Need Fin";
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	if(c!=NULL){
		RetStrBuff=c->GetLibName();
	}
	if((ItemRes->GetError()&0x010)!=0){
		RetStrBuff+=QString(" InN")+QString::number((int)(ItemRes->GetResult1()>>16));
	}
	if((ItemRes->GetError()&0x020)!=0){
		RetStrBuff+=QString(" OutN")+QString::number((int)(ItemRes->GetResult2()>>16));
	}
	if((ItemRes->GetError()&0x040)!=0){
		RetStrBuff+=QString(" InB")+QString::number((int)(ItemRes->GetResult1()&0xFFFF));
	}
	if((ItemRes->GetError()&0x080)!=0){
		RetStrBuff+=QString(" OutB")+QString::number((int)(ItemRes->GetResult2()&0xFFFF));
	}
	return true;
}

