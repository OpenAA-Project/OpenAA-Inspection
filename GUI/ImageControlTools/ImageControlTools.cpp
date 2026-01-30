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


#include "ImageControlTools.h"
#include "XDisplayImage.h"
#include "ImageControlToolsFormResource.h"

const	char	*sRoot=/**/"Button";
const	char	*sName=/**/"ImageControlTools";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"ImageControlTools";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show Image-control toolbar");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdSetImageControlTools(Base,QString(sRoot),QString(sName));

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ImageControlTools(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<15)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowImageMaster";
	Data[0].Pointer				 =&((ImageControlTools *)Instance)->ShowImageMaster;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowImageMaster2";
	Data[1].Pointer				 =&((ImageControlTools *)Instance)->ShowImageMaster2;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowImageTarget";
	Data[2].Pointer				 =&((ImageControlTools *)Instance)->ShowImageTarget;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowImageBackGround";
	Data[3].Pointer				 =&((ImageControlTools *)Instance)->ShowImageBackGround;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowImageGrayLower";
	Data[4].Pointer				 =&((ImageControlTools *)Instance)->ShowImageGrayLower;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowImageGrayUpper";
	Data[5].Pointer				 =&((ImageControlTools *)Instance)->ShowImageGrayUpper;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ShowImageTargetTR";
	Data[6].Pointer				 =&((ImageControlTools *)Instance)->ShowImageTargetTR;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ShowLayer";
	Data[7].Pointer				 =&((ImageControlTools *)Instance)->ShowLayer;
	Data[8].Type				 =/**/"QStringList";
	Data[8].VariableNameWithRoute=/**/"RelatedPanels";
	Data[8].Pointer				 =&((ImageControlTools *)Instance)->RelatedPanels;
	Data[9].Type				 =/**/"int32";
	Data[9].VariableNameWithRoute=/**/"IconSize";
	Data[9].Pointer				 =&((ImageControlTools *)Instance)->IconSize;
	Data[10].Type				 =/**/"QImage";
	Data[10].VariableNameWithRoute=/**/"MasterIcon";
	Data[10].Pointer				 =&((ImageControlTools *)Instance)->MasterIcon;
	Data[11].Type				 =/**/"QImage";
	Data[11].VariableNameWithRoute=/**/"TargetIcon";
	Data[11].Pointer				 =&((ImageControlTools *)Instance)->TargetIcon;
	
	Data[12].Type				 =/**/"bool";
	Data[12].VariableNameWithRoute=/**/"ExclusiveLayer";
	Data[12].Pointer				 =&((ImageControlTools *)Instance)->ExclusiveLayer;
	Data[13].Type				 =/**/"int32";
	Data[13].VariableNameWithRoute=/**/"ShowLayerAtFirst";
	Data[13].Pointer				 =&((ImageControlTools *)Instance)->ShowLayerAtFirst;
	Data[14].Type				 =/**/"bool";
	Data[14].VariableNameWithRoute=/**/"BitBuffForMasterImage";
	Data[14].Pointer			 =&((ImageControlTools *)Instance)->BitBuffForMasterImage;

	return(15);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ImageControlTools.png")));
}
