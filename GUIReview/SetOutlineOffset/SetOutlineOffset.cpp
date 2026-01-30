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

#include "SetOutlineOffsetResource.h"

#include "SetOutlineOffset.h"
#include "XDataInLayer.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XGeneralFunc.h"
#include "XReviewCommonPacket.h"

#include "ReviewStructurePacket.h"
#include "../XGUIReviewGlobal.h"
#include <QSqlRecord>
#include <QSqlQuery>

static	char	*sRoot=/**/"Review";
static	char	*sName=/**/"SetOutlineOffset";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Set outline offset when MasterData is loaded");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SetOutlineOffset(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/SetOutlineOffset.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
SetOutlineOffset::SetOutlineOffset(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LangSolver.SetUI(this);
}

SetOutlineOffset::~SetOutlineOffset(void)
{
}

void	SetOutlineOffset::BuildForShow(void)
{
	ReviewPIBase *RBase = GetReviewAlgorithm();
	
}

void	SetOutlineOffset::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqOutlineOffset	*CmdReqOutlineOffsetVar=dynamic_cast<CmdReqOutlineOffset *>(packet);
	if(CmdReqOutlineOffsetVar!=NULL){
		CmdReqOutlineOffsetVar->Result=false;
		QString	S=QString(/**/"SELECT SAVEOUTLINEOFFSET FROM MASTERDATA where MASTERCODE=")+QString::number(CmdReqOutlineOffsetVar->MasterCode);
		QSqlQuery query(S,*GetLayersBase()->GetDataBase());
		if(query.next ()==true){
			QByteArray	Gd	=query.value(query.record().indexOf(/**/"SAVEOUTLINEOFFSET")).toByteArray();
			QBuffer		Buff(&Gd);
			Buff.open(QIODevice::ReadOnly);
			int32	iPageNumb;
			if(::Load(&Buff,iPageNumb)==false)
				return;

			CmdReqOutlineOffsetVar->Data.Initial();
			for(int page=0;page<iPageNumb;page++){
				OutlineOffsetInPage		PageData;
				int32	iOffsetX;
				int32	iOffsetY;
				if(::Load(&Buff,iOffsetX)==false)
					return;
				if(::Load(&Buff,iOffsetY)==false)
					return;
				PageData.Dx=iOffsetX;
				PageData.Dy=iOffsetY;
				CmdReqOutlineOffsetVar->Data.SetData(0,page ,PageData);
			}
			CmdReqOutlineOffsetVar->Result=true;
		}
		return;
	}
}