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

#include "GraphicPanelResource.h"

#include <QDir>
#include "GraphicPanel.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"General";
	Name=/**/"GraphicPanel";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Graphic panel from BMP/JPG/PNG file");
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
	return(new GraphicPanel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<2)
		return(-1);
	Data[0].Type				 =/**/"FileName";
	Data[0].VariableNameWithRoute=/**/"FileName";
	Data[0].Pointer				 =&((GraphicPanel *)Instance)->FileName;
	Data[1].Type				 =/**/"bool";
	Data[1].VariableNameWithRoute=/**/"Scaling";
	Data[1].Pointer				 =&((GraphicPanel *)Instance)->Scaling;

	return(2);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/GraphicPanel.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
GraphicPanel::GraphicPanel(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Scaling	=true;
	Label.setParent(this);
	Label.move(0,0);
	resize(100,100);
}

GraphicPanel::~GraphicPanel(void)
{
}

void	GraphicPanel::Prepare(void)
{
	DrawOnly();
	ResizeAction();
}

void	GraphicPanel::DrawOnly(void)
{
	static	bool	ReEntrant=false;

	if(ReEntrant==true)
		return;
	ReEntrant=true;
	if(FileName.isEmpty()==false && QFile::exists (FileName)==true){
		QPixmap	GMap;
		if(GMap.load(FileName)==false){
			ReEntrant=false;
			return;
		}
		if(Scaling==true){
			QPixmap	RMap=GMap.scaled(Label.width(),Label.height());
			Label.setPixmap(RMap);
		}
		else{
			int	W=GMap.width();
			int	H=GMap.height();
			resize(W+1,H+1);
			Label.setPixmap(GMap);
		}
	}
	ReEntrant=false;
}

void	GraphicPanel::ResizeAction(void)
{
	Label.resize(width(),height());
	DrawOnly();
}