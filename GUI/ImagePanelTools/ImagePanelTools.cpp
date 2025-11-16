/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ImagePanelTools\ImagePanelTools.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "ImagePanelTools.h"
#include "XDisplayImage.h"
#include "ImagePanelToolsFormResource.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Button";
	Name=/**/"ImagePanelTools";
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show ImagePanel toolbar");
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new ImagePanelTools(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<24)
		return(-1);
	Data[0].Type				 =/**/"bool";
	Data[0].VariableNameWithRoute=/**/"ShowRectangle";
	Data[0].Pointer				 =&((ImagePanelTools *)Instance)->ShowRectangle;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"ShowEndlessLine";
	Data[1].Pointer				 =&((ImagePanelTools *)Instance)->ShowEndlessLine;
	Data[2].Type				 =/**/"bool";
	Data[2].VariableNameWithRoute=/**/"ShowLine";
	Data[2].Pointer				 =&((ImagePanelTools *)Instance)->ShowLine;
	Data[3].Type				 =/**/"bool";
	Data[3].VariableNameWithRoute=/**/"ShowHLine";
	Data[3].Pointer				 =&((ImagePanelTools *)Instance)->ShowHLine;
	Data[4].Type				 =/**/"bool";
	Data[4].VariableNameWithRoute=/**/"ShowVLine";
	Data[4].Pointer				 =&((ImagePanelTools *)Instance)->ShowVLine;
	Data[5].Type				 =/**/"bool";
	Data[5].VariableNameWithRoute=/**/"ShowHalfLine";
	Data[5].Pointer				 =&((ImagePanelTools *)Instance)->ShowHalfLine;
	Data[6].Type				 =/**/"bool";
	Data[6].VariableNameWithRoute=/**/"ShowEllipse";
	Data[6].Pointer				 =&((ImagePanelTools *)Instance)->ShowEllipse;
	Data[7].Type				 =/**/"bool";
	Data[7].VariableNameWithRoute=/**/"ShowEllipse4";
	Data[7].Pointer				 =&((ImagePanelTools *)Instance)->ShowEllipse4;
	Data[8].Type				 =/**/"bool";
	Data[8].VariableNameWithRoute=/**/"ShowArc";
	Data[8].Pointer				 =&((ImagePanelTools *)Instance)->ShowArc;
	Data[9].Type				 =/**/"bool";
	Data[9].VariableNameWithRoute=/**/"ShowArc3";
	Data[9].Pointer				 =&((ImagePanelTools *)Instance)->ShowArc3;
	Data[10].Type				 =/**/"bool";
	Data[10].VariableNameWithRoute=/**/"ShowCircle";
	Data[10].Pointer				 =&((ImagePanelTools *)Instance)->ShowCircle;
	Data[11].Type				 =/**/"bool";
	Data[11].VariableNameWithRoute=/**/"ShowCircle3";
	Data[11].Pointer				 =&((ImagePanelTools *)Instance)->ShowCircle3;
	Data[12].Type				 =/**/"bool";
	Data[12].VariableNameWithRoute=/**/"ShowRotRectangle";
	Data[12].Pointer				 =&((ImagePanelTools *)Instance)->ShowRotRectangle;
	Data[13].Type				 =/**/"bool";
	Data[13].VariableNameWithRoute=/**/"ShowRotEllipse";
	Data[13].Pointer				 =&((ImagePanelTools *)Instance)->ShowRotEllipse;
	Data[14].Type				 =/**/"bool";
	Data[14].VariableNameWithRoute=/**/"ShowRing";
	Data[14].Pointer				 =&((ImagePanelTools *)Instance)->ShowRing;
	Data[15].Type				 =/**/"bool";
	Data[15].VariableNameWithRoute=/**/"ShowLongCircle";
	Data[15].Pointer				 =&((ImagePanelTools *)Instance)->ShowLongCircle;
	Data[16].Type				 =/**/"bool";
	Data[16].VariableNameWithRoute=/**/"ShowDot";
	Data[16].Pointer				 =&((ImagePanelTools *)Instance)->ShowDot;
	Data[17].Type				 =/**/"bool";
	Data[17].VariableNameWithRoute=/**/"ShowPolyline";
	Data[17].Pointer				 =&((ImagePanelTools *)Instance)->ShowPolyline;
	Data[18].Type				 =/**/"bool";
	Data[18].VariableNameWithRoute=/**/"ShowFreeline";
	Data[18].Pointer				 =&((ImagePanelTools *)Instance)->ShowFreeline;
	Data[19].Type				 =/**/"bool";
	Data[19].VariableNameWithRoute=/**/"ShowRingArc1";
	Data[19].Pointer				 =&((ImagePanelTools *)Instance)->ShowRingArc1;
	Data[20].Type				 =/**/"bool";
	Data[20].VariableNameWithRoute=/**/"ShowRingArc4";
	Data[20].Pointer				 =&((ImagePanelTools *)Instance)->ShowRingArc4;
	Data[21].Type				 =/**/"QColor";
	Data[21].VariableNameWithRoute=/**/"LineColor";
	Data[21].Pointer				 =&((ImagePanelTools *)Instance)->LineColor;
	Data[22].Type				 =/**/"QStringList";
	Data[22].VariableNameWithRoute=/**/"RelatedPanels";
	Data[22].Pointer			 =&((ImagePanelTools *)Instance)->RelatedPanels;
	Data[23].Type				 =/**/"int32";
	Data[23].VariableNameWithRoute=/**/"IconSize";
	Data[23].Pointer			 =&((ImagePanelTools *)Instance)->IconSize;

	return(24);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ImagePannelTools.png")));
}

