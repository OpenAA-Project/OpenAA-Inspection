/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImageControlTools\ImageControlTools.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

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

