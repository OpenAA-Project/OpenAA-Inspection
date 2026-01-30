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

//#include "DentResource.h"
#include "XAlgorithmDLL.h"
#include "XDentInspection.h"
#include "XDentLibrary.h"
#include "DentHistgramForm.h"


DEFFUNCEX	bool	DLL_ResultItemToString(ResultInItemRoot *ItemRes ,QString &RetStrBuff)
{
	AlgorithmItemRoot	*aitem	=ItemRes->GetAlgorithmItem();
	if(aitem==NULL){
		RetStrBuff=/**/"Need Fin";
		return false;
	}
	AlgorithmLibraryList	*c=aitem->GetParentBase()->FindLibFromCache(aitem->GetLibID());
	
	if(c!=NULL){
		RetStrBuff+=c->GetLibName();
	}
	/*
	if((ItemRes->GetError()&0x0f)==5){
		char	*txt="Hole Shift";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	else if((ItemRes->GetError()&0x0f)==4){
		char	*txt="Hole Diameter";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	else if((ItemRes->GetError()&0x0f)==3){
		char	*txt="Ring";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	else if((ItemRes->GetError()&0x0f)==6){
		char	*txt="Ring";
		int	Len=strlen(txt);
		ByteOfStrBuff-=Len;
		if(ByteOfStrBuff<0)
			return false;
		strcpy(fp,txt);
		fp=strchr(fp,0);
	}
	*/
	return true;
}


DEFFUNCEX	bool	DLL_DrawResultDetail(AlgorithmItemRoot *Item ,ResultPosList *Pos ,DetailResultInfoListContainer &RetList)
{
	//QString	Str;
	//if((Pos->result&0xFF00)==0x000){
	//	Str="OK/NG";
	//}
	//else
	//if((Pos->result&0xFF00)==0x100){
	//	Str="��E";
	//}
	//else
	//if((Pos->result&0xFF00)==0x200){
	//	Str="HSV";
	//}
	//
	//RetList.append(Str);

	return true;
}