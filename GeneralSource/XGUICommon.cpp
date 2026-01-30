/*
 * Copyright (C) 2025
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
#include "XGUIInterfaceDLL.h"
#include "XGUI.h"
#include "XErrorCode.h"
#include <string.h>
#include "XGeneralFunc.h"
#include <QBuffer>
#include "XParamGlobal.h"
#include "XDataInLayer.h"
#include "XDataInExe.h"
#include "XDisplayImage.h"

QString	GUIItemInstance::GetDLLRoot(void)
{
	if(DLLAccess!=NULL){
		return DLLAccess->RootName;
	}
	return /**/"";
}
QString	GUIItemInstance::GetDLLName(void)
{
	if(DLLAccess!=NULL){
		return DLLAccess->Name;
	}
	return /**/"";
}

GUIFormBase	*GUIInstancePack::GetFirstForm(void)
{
	GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();
	if(v==NULL){
		return NULL;
	}
	return v->Handle;
}


GUIFormBase	*GUIInstancePack::FindByName(const QString &FormRoot ,const QString &FormName ,const QString &InstName)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->DLLAccess==NULL){
			continue;
		}
		if(v->DLLAccess->RootName==FormRoot && v->DLLAccess->Name==FormName){
			if(InstName==/**/""){
				return v->Handle;
			}
			if(v->Handle!=NULL && InstName==v->Handle->GetName()){
				return v->Handle;
			}
		}
	}
	return NULL;
}

GUIFormBase	*GUIInstancePack::FindByName(const QString &InstName)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(v->DLLAccess==NULL){
			continue;
		}
		if(v->Handle==NULL){
			continue;
		}
		if(InstName==v->Handle->GetName()){
			return v->Handle;
		}
	}
	return NULL;
}

int GUIInstancePack::EnumGUIInst(const QString &FormRoot ,const QString &FormName ,GUIFormBase *Ret[] ,int MaxRet)
{
	int	n=0;
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(n>=MaxRet){
			return n;
		}
		if(v->DLLAccess==NULL){
			continue;
		}
		if(v->DLLAccess->RootName==FormRoot && v->DLLAccess->Name==FormName){
			Ret[n]=v->Handle;
			n++;
		}
	}
	return n;
}

int GUIInstancePack::EnumGUIInst(GUIFormBase *Ret[] ,int MaxRet)
{
	int	n=0;
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		if(n>=MaxRet){
			return n;
		}
		if(v->DLLAccess==NULL){
			continue;
		}
		Ret[n]=v->Handle;
		n++;
	}
	return n;
}
void	GUIInstancePack::SetAreaSizeInImagePanel(bool DrawWholeMode)
{
	for(GUIItemInstance *v=NPListPack<GUIItemInstance>::GetFirst();v!=NULL;v=v->GetNext()){
		GUIFormBase	*f=v->GetForm();
		f->SetAreaSize();
		DisplayImage	*Disp=dynamic_cast<DisplayImage *>(f);
		if(Disp!=NULL){
			if(DrawWholeMode==true){
				QStringList Args;
				bool 		ExeReturn;
				Disp->ExecuteMacro(/**/"ZoomWhole", Args, ExeReturn);
			}
		}
	}
}

GUIFormBase	*GUIInitializer::Search(QString &DLLRoot,QString &DLLName ,QString &InstName)
{
	for(GUIInstancePack	*f=GetGUIInstanceRoot();f!=NULL;f=f->GetNext()){
		GUIFormBase	*form=f->FindByName(DLLRoot ,DLLName ,InstName);
		if(form!=NULL){
			return form;
		}
	}
	return NULL;
}