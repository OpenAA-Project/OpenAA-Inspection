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

#include "ShowNGCountResource.h"

#include "ShowNGCount.h"
#include "XGeneralFunc.h"
#include "XResult.h"

static	const	char	*sRoot=/**/"Inspection";
static	const	char	*sName=/**/"ShowNGCount";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Show NG Count Label");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	(*Base)=new GUICmdReqNGCount	(Base,sRoot,sName);
	(*Base)=new GUICmdSendNGCount	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowNGCount(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);
	Data[0].Type				 =/**/"QString";
	Data[0].VariableNameWithRoute=/**/"Msg";
	Data[0].Pointer				 =&((ShowNGCount *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ShowNGCount *)Instance)->MsgColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"CountColor";
	Data[2].Pointer				 =&((ShowNGCount *)Instance)->CountColor;
	Data[3].Type				 =/**/"QColor";
	Data[3].VariableNameWithRoute=/**/"CountColor";
	Data[3].Pointer				 =&((ShowNGCount *)Instance)->OkNgColor;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ShowNGCount.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}

//==================================================================================================
ShowNGCount::ShowNGCount(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	LabelMsg	.setParent(this);
	LabelCount	.setParent(this);
	LabelOkNg	.setParent(this);
	LabelMsg	.move(0,0);
	LabelMsg	.resize(50,25);
	LabelCount	.move(100,0);
	LabelCount	.resize(50,25);
	LabelOkNg	.move(150,0);
	LabelOkNg	.resize(50,25);
	Msg			=/**/"NG";
	MsgColor	=Qt::black;
	CountColor	=Qt::red;
	OkNgColor	=Qt::green;
	resize(200,25);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

void	ShowNGCount::Prepare(void)
{
	LabelMsg.setText(Msg);

	QPalette P=LabelMsg.palette();
	P.setColor(QPalette::Text,MsgColor);
	LabelMsg.setPalette(P);

	P=LabelCount.palette();
	P.setColor(QPalette::Text,MsgColor);
	LabelCount.setPalette(P);

	P=LabelOkNg.palette();
	P.setColor(QPalette::Text,MsgColor);
	LabelOkNg.setPalette(P);

	ResizeAction();
}

void	ShowNGCount::ResizeAction()
{
	LabelMsg	.move(0,0);
	LabelMsg	.resize(width()-100,height());
	LabelCount	.move(width()-100,0);
	LabelCount	.resize(50,height());
	LabelOkNg	.move(width()-50,0);
	LabelOkNg	.resize(50,height());
}

void	ShowNGCount::BuildForShow(void)
{
	ShowInPlayer(GetLayersBase()->GetCurrentInspectIDForDisplay());
}
void	ShowNGCount::ShowInPlayer(int64 shownInspectionID)
{
	int	NGCount=0;
	for(int page=0;page<GetPageNumb();page++){
		int	GlobalPage=GetLayersBase()->GetGlobalPageFromLocal(page);
		GUICmdReqNGCount	CmdReq(GetLayersBase(),sRoot,sName,GlobalPage);
		CmdReq.ShownInspectionID=shownInspectionID;
		GUICmdSendNGCount	CmdAck(GetLayersBase(),sRoot,sName,GlobalPage);
		if(CmdReq.Send(GlobalPage ,0,CmdAck)==true){
			NGCount+=CmdAck.NGCount;
		}
	}
	LabelCount	.setText(QString::number(NGCount));
	if(NGCount==0)
		LabelOkNg	.setText(LangSolver.GetString(ShowNGCount_LS,LID_0)/*"OK"*/);
	else
		LabelOkNg	.setText(LangSolver.GetString(ShowNGCount_LS,LID_1)/*"NG"*/);
}

//===================================================================
GUICmdReqNGCount::GUICmdReqNGCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
}


bool	GUICmdReqNGCount::Load(QIODevice *f)
{
	::Load(f,ShownInspectionID);
	return true;
}
bool	GUICmdReqNGCount::Save(QIODevice *f)
{
	::Save(f,ShownInspectionID);
	return true;
}
void	GUICmdReqNGCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
	GUICmdSendNGCount	*SendBack=GetSendBack(GUICmdSendNGCount,GetLayersBase(),EmitterRoot,EmitterName ,localPage);
	if(localPage==0){
		ResultInspection	*R=GetLayersBase()->GetBufferedResult(ShownInspectionID);
		if(R!=NULL){
			SendBack->NGCount=R->GetNGCount();
		}
		else{
			SendBack->NGCount=0;
		}
	}

	SendBack->Send(this ,GetLayersBase()->GetGlobalPageFromLocal(localPage),0);
	CloseSendBack(SendBack);
}

GUICmdSendNGCount::GUICmdSendNGCount(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage)
:GUICmdPacketBase(Base,EmitterRoot,EmitterName ,typeid(this).name(),globalPage)
{
	NGCount=0;
}

bool	GUICmdSendNGCount::Load(QIODevice *f)
{
	if(::Load(f,NGCount)==false)
		return false;
	return true;
}
bool	GUICmdSendNGCount::Save(QIODevice *f)
{
	if(::Save(f,NGCount)==false)
		return false;
	return true;
}
void	GUICmdSendNGCount::Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName)
{
}

