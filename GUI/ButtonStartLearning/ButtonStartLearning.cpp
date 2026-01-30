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

#include "ButtonStartLearningResource.h"

#include "ButtonStartLearning.h"
#include "StartLearningForm.h"
#include "XGeneralFunc.h"
#include <QFileDialog>

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"StartLearning";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to load BMP/JPG file");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	(*Base)=new GUICmdReqStartLearning		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningReqStartOne	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningAckStartOne	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningExeTop		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningExeLoopTop	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningExeLoopNext	(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningReqData		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningAckData		(Base,QString(sRoot),QString(sName));
	(*Base)=new GUICmdLearningSetData		(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new StartLearningForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonStartLearning.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}