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

#include "IntegrationCreateThresholdResource.h"
//#include "ButtonSaveBmpJpgResource.h"
#include "IntegrationCreateThreshold.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include <QStringList>
#include "XMacroFunction.h"
#include <QSqlQuery>
#include <QSqlRecord>
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "CreateThresholdDialog.h"
#include "XMacroFunction.h"

static	const	char	*sRoot=/**/"Integration";
static	const	char	*sName=/**/"CreateThreshold";


DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to Create threshold");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);

	return true;
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	void	DLL_Close(void)
{
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new IntegrationCreateThreshold(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<5)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((IntegrationCreateThreshold *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((IntegrationCreateThreshold *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((IntegrationCreateThreshold *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((IntegrationCreateThreshold *)Instance)->CFont;
	Data[4].Type				 =/**/"double";
	Data[4].VariableNameWithRoute=/**/"AddedMMX";
	Data[4].Pointer				 =&((IntegrationCreateThreshold *)Instance)->AddedMMX;
	Data[5].Type				 =/**/"double";
	Data[5].VariableNameWithRoute=/**/"AddedMMY";
	Data[5].Pointer				 =&((IntegrationCreateThreshold *)Instance)->AddedMMY;
	Data[6].Type				 =/**/"double";
	Data[6].VariableNameWithRoute=/**/"AddedMMZ";
	Data[6].Pointer				 =&((IntegrationCreateThreshold *)Instance)->AddedMMZ;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationCreateThreshold.png")));
}


//==================================================================================================

IntegrationCreateThreshold::IntegrationCreateThreshold(LayersBase *Base ,QWidget *parent)
	:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.setObjectName(/**/"IntegrationCreateThresholdBtn");
	Button.move(0,0);
	Msg=/**/"Threshold";
	resize(80,25);
	AddedMMX	=0;
	AddedMMY	=0;
	AddedMMZ	=0;
	Button.setStyleSheet("QToolButton {"
						"	border-style: outset;"
						"	border-width: 1px;"
						"	border-radius: 25px;"
						"	border-color: gray;"
						"	background-color: qlineargradient(spread:pad, x1:0.0113636, y1:0, x2:0, y2:1, stop:0 rgba(254, 254, 254, 255), stop:1 rgba(165, 165, 165, 255));"
						"}"
						"QToolButton:pressed { 	"
						"	background-color: qlineargradient(spread:pad, x1:0, y1:1, x2:0, y2:0, stop:0 rgba(225, 225, 225, 255), stop:1 rgba(141, 141, 141, 255));"
						"}"
						);
	connect(&Button,SIGNAL(clicked()), this ,SLOT(SlotClicked()));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

IntegrationCreateThreshold::~IntegrationCreateThreshold()
{

}

void	IntegrationCreateThreshold::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	IntegrationCreateThreshold::ResizeAction()
{
	Button.setGeometry(0,0,width(),height());
}

void	IntegrationCreateThreshold::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	IntegrationCreateThreshold::SlotClicked ()
{
	CreateThresholdDialog	D(GetLayersBase());
	D.exec();
}