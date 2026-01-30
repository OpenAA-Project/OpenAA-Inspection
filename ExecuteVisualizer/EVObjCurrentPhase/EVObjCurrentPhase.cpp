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


#include "EVObjCurrentPhase.h"
#include "XGeneralFunc.h"
#include <QFileDialog>
#include "swap.h"
#include "EVObjDLL.h"
#include "XDataInLayer.h"

static	const	char	*sRoot=/**/"Process";
static	const	char	*sName=/**/"CurrentPhase";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Current Phase");
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

DEFFUNCEX	RunnerObject	*DLL_CreateInstance(LayersBase *Base,RunnerMap *rmap)
{
	return(new RunnerCurrentPhase(Base,rmap));
}
DEFFUNCEX	void	DLL_DeleteInstance(RunnerObject *Instance)
{
	delete	Instance;
}

//======================================================================================
int		CurrentPhaseOutput::GetOutputInt(void)
{
	RunnerCurrentPhase	*a=dynamic_cast<RunnerCurrentPhase *>(GetParent());
	if(a!=NULL){
		return a->GetLayersBase()->GetCurrentPhase();
	}
	return 0;
}
void	CurrentPhaseInput::SetInputInt(int d)
{
	RunnerCurrentPhase	*a=dynamic_cast<RunnerCurrentPhase *>(GetParent());
	if(a!=NULL){
		a->GetLayersBase()->SetCurrentPhase(d);
	}
}
const	int	ObjWidth	=72;
const	int	ObjHeight	=72;

RunnerCurrentPhase::RunnerCurrentPhase(LayersBase *Base ,RunnerMap *rmap)
	:RunnerObject(Base ,rmap)
{
	CurrentPhaseInput	*a=new CurrentPhaseInput(this);
	AppendInputConnector(a);

	CurrentPhaseOutput	*d=new CurrentPhaseOutput(this);
	AppendOutputConnector(d);

	resize(ObjWidth,ObjHeight);
}
RunnerCurrentPhase::~RunnerCurrentPhase(void)
{
}
void RunnerCurrentPhase::paintEvent ( QPaintEvent * event )
{
	QPainter	Pnt(this);

	Pnt.fillRect(0,0,ObjWidth,ObjHeight,Qt::black);

	QFont	Fnt=Pnt.font();
	Fnt.setPointSize(15);
	Pnt.setFont(Fnt);
	int	e=4;
	int	h=(ObjHeight-e-e)/3;

	Pnt.setPen(Qt::white);

	QRectF	Rect1(e,e,ObjWidth-e-e,h);
	QString	Str(/**/"Phase");
	Pnt.drawText(Rect1,Qt::AlignCenter,Str);

	QRectF	Rect2(e,e+h,ObjWidth-e-e,h);
	int	Value=GetLayersBase()->GetCurrentPhase();
	QString	Str2=QString::number(Value);
	Pnt.drawText(Rect2,Qt::AlignCenter,Str2);

	Pnt.setPen(Qt::green);
	Pnt.drawLine(0			,0			,ObjWidth-1	,0);
	Pnt.drawLine(ObjWidth-1	,0			,ObjWidth-1	,ObjHeight-1);
	Pnt.drawLine(ObjWidth-1	,ObjHeight-1,0			,ObjHeight-1);
	Pnt.drawLine(0			,ObjHeight-1,0			,0);
}

void	RunnerCurrentPhase::IntervalExecute(void)
{
}