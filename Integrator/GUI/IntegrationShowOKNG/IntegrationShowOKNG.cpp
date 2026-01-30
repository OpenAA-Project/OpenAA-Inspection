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

#include "IntegrationShowOKNG.h"
#include <QPainter>
#include "XAlgorithmBase.h"
#include "XDataAlgorithm.h"
#include "XParamIntegrationMaster.h"

const	char	*sRoot=/**/"Integration";
const	char	*sName=/**/"ShowOKNG";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show OK/NG");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
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
	return(new IntegrationShowOKNG(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<3)
		return(-1);

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/IntegrationShowOKNG.png")));
}

//==================================================================================================================
	
IntegrationShowOKNG::IntegrationShowOKNG(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	ColorOK	=Qt::green;
	ColorNG	=Qt::red;
	ColorHalt=Qt::yellow;
	MsgOK=/**/"OK";
	MsgNG=/**/"NG";
	resize(250,250);

	CriticalError	=ResultInspection::_NoError;
	ResultOk		=none3;
	ResultTimeOut	=false;
	ResultMaxError	=false;
}

void	IntegrationShowOKNG::Prepare(void)
{
	ResultOk		=none3;
}

void	IntegrationShowOKNG::paintEvent ( QPaintEvent * event )
{
	QPainter	pnt(this);

	pnt.setFont(MessageSize);

	QString	Msg;
	if(CriticalError==ResultInspection::_ErrorOverflowBuffer){
		QBrush	B(Qt::magenta);
		Msg="Overflow";
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(CriticalError==ResultInspection::_ErrorOverrun){
		QBrush	B(Qt::magenta);
		Msg="OverRun";
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(CriticalError==ResultInspection::_ErrorCantWrite){
		QBrush	B(Qt::magenta);
		Msg="Lost Result";
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(ResultOk==true3){
		QBrush	B(ColorOK);
		Msg=MsgOK;
		pnt.fillRect(0,0,width(),height(),B);
	}
	else if(ResultOk==none3){
		QBrush	B(Qt::gray);
		Msg=/**/"--";
		pnt.fillRect(0,0,width(),height(),B);
	}
	else{
		if(ResultTimeOut==false && ResultMaxError==false){
			QBrush	B(ColorNG);
			Msg=MsgNG;
			pnt.fillRect(0,0,width(),height(),B);
		}
		if(ResultTimeOut==true && ResultMaxError==false){
			QBrush	B(ColorHalt);
			Msg="Time out";
			pnt.fillRect(0,0,width(),height(),B);
		}
		if(ResultTimeOut==false && ResultMaxError==true){
			QBrush	B(ColorHalt);
			Msg="Max Error";
			pnt.fillRect(0,0,width(),height(),B);
		}
		if(ResultTimeOut==true && ResultMaxError==true){
			QBrush	B(ColorHalt);
			Msg="Halt";
			pnt.fillRect(0,0,width(),height(),B);
		}
	}

	QBrush	B(Qt::black);
	pnt.setBrush(B);
	int	H=height();
	int	Row=1;
	if(Message1.isEmpty()==false)
		Row++;
	if(Message2.isEmpty()==false)
		Row++;
	H/=Row;

	int	Y=0;
	if(Message1.isEmpty()==false){
		if(ResultOk==true3){
			QBrush	B(ColorOK);
			Msg=MsgOK;
			pnt.fillRect(0,0,width(),height(),B);
			pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,QString("OK")+Msg);
		}
		else if(ResultOk==false3){
			QBrush	B(ColorNG);
			Msg=/**/"--";
			pnt.fillRect(0,0,width(),height(),B);
			pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,QString("NG")+Msg);
		}
		else if(ResultOk==none3){
			QBrush	B(Qt::gray);
			Msg=/**/"--";
			pnt.fillRect(0,0,width(),height(),B);
			pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,QString("NG")+Msg);
		}
		Y=H;
		pnt.drawText(0,Y,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,Message1);
		Y+=H;
	}
	else{
		pnt.drawText(0,0,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,Msg);
	}
	if(Message2.isEmpty()==false){
		pnt.drawText(0,Y,width(),H,Qt::AlignHCenter | Qt::AlignVCenter ,Message2);
		Y+=H;
	}
}

void	IntegrationShowOKNG::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdSendOkNG	*CmdSendOkNGVar=dynamic_cast<CmdSendOkNG *>(packet);
	if(CmdSendOkNGVar!=NULL){
		if(CmdSendOkNGVar->ResultOk==true)
			ResultOk		=true3;
		else
			ResultOk		=false3;
		ResultTimeOut	=CmdSendOkNGVar->ResultTimeOut;
		ResultMaxError	=CmdSendOkNGVar->ResultMaxError;
		CriticalError	=CmdSendOkNGVar->CriticalError;
		EmitRepaint();
		return;
	}
}