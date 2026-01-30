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

#include "FixedImageSizeResource.h"

#include "FixedImageSize.h"
#include "XDLLOnly.h"
#include "XForWindows.h"
#include <QMessageBox>
#include "XDisplayImage.h"

static	const	char	*sRoot=/**/"General";
static	const	char	*sName=/**/"FixedImageSize";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Fix ImageSize");
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
	return(new FixedImageSize(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"int32";
	Data[0].VariableNameWithRoute=/**/"PosLeft";
	Data[0].Pointer				 =&((FixedImageSize *)Instance)->PosLeft;
	Data[1].Type				 =/**/"int32";
	Data[1].VariableNameWithRoute=/**/"PosTop";
	Data[1].Pointer				 =&((FixedImageSize *)Instance)->PosTop;
	Data[2].Type				 =/**/"int32";
	Data[2].VariableNameWithRoute=/**/"PosRight";
	Data[2].Pointer				 =&((FixedImageSize *)Instance)->PosRight;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"PosBottom";
	Data[3].Pointer				 =&((FixedImageSize *)Instance)->PosBottom;
	Data[4].Type				 =/**/"QString";
	Data[4].VariableNameWithRoute=/**/"DisplayImageName";
	Data[4].Pointer				 =&((FixedImageSize *)Instance)->DisplayImageName;

	return(5);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/FixedImageSize.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
FixedImageSize::FixedImageSize(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	PosLeft		=0;
	PosTop		=0;
	PosRight	=1000;
	PosBottom	=1000;
}

FixedImageSize::~FixedImageSize(void)
{
}

void	FixedImageSize::BuildForShow(void)
{
	GUIFormBase		*r=GetFormByName(DisplayImageName);
	if(r==NULL)
		return;
	DisplayImage	*m=dynamic_cast<DisplayImage *>(r);
	if(m!=NULL){
		m->ZoomRect(PosLeft, PosTop, PosRight, PosBottom);
	}	
}
void	FixedImageSize::ShowInPlayer(int64 shownInspectionID)
{
	BuildForShow();
}