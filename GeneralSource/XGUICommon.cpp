/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GeneralSource\XGUICommon.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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