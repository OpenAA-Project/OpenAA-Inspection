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


#include "SelectStackedWindows.h"
#include "AllocateMenuDialog.h"
#include "XGeneralDialog.h"
#include "XGeneralFunc.h"
#include "XMacroFunction.h"
#include "swap.h"

const	char	*sRoot=/**/"Panel";
const	char	*sName=/**/"SelectStackedWindows";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button list for stacked window");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdSendImagePartial	(Base,sRoot,sName);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new SelectStackedWindows(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<4)
		return(-1);

	Data[0].Type				 =/**/"QColor";
	Data[0].VariableNameWithRoute=/**/"CharColor";
	Data[0].Pointer				 =&((SelectStackedWindows *)Instance)->CharColor;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"BackColor";
	Data[1].Pointer				 =&((SelectStackedWindows *)Instance)->BackColor;
	Data[2].Type				 =/**/"QFont";
	Data[2].VariableNameWithRoute=/**/"CFont";
	Data[2].Pointer				 =&((SelectStackedWindows *)Instance)->CFont;
	Data[3].Type				 =/**/"QByteArray";
	Data[3].VariableNameWithRoute=/**/"MenuData";
	Data[3].Pointer				 =&((SelectStackedWindows *)Instance)->MenuData;

	return(4);
}
//==================================================================================================

AllocationList::AllocationList(void)
{
	connect(&Button,SIGNAL(clicked()),this,SLOT(SlotClicked()));
}

bool	AllocationList::Save(QIODevice *f)
{
	if(::Save(f,ButtonMessage	)==false)	return false;
	if(::Save(f,InstName		)==false)	return false;
	if(::Save(f,PageName		)==false)	return false;
	return true;
}
bool	AllocationList::Load(QIODevice *f)
{
	if(::Load(f,ButtonMessage	)==false)	return false;
	if(::Load(f,InstName		)==false)	return false;
	if(::Load(f,PageName		)==false)	return false;
	return true;
}

void	AllocationList::SlotClicked()
{
	Parent->SlotClick(InstName,PageName);
}
//==================================================================================================

SelectStackedWindows::SelectStackedWindows(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	CharColor	=Qt::black;
	BackColor	=Qt::lightGray;
	resize(100,100);

	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}
SelectStackedWindows::~SelectStackedWindows(void)
{
}
void	SelectStackedWindows::Prepare(void)
{
}
void	SelectStackedWindows::ReadyParam(void)
{
	QBuffer	Buff(&MenuData);
	if(Buff.open(QIODevice::ReadOnly)==true){
		if(MContainer.Load(&Buff)==true){
			for(AllocationList *a=MContainer.GetFirst();a!=NULL;a=a->GetNext()){
				a->Button.setParent(this);
				a->Button.setText(a->ButtonMessage);
				a->Button.setFont(CFont);
				a->Parent=this;
				a->Button.show();
			}
		}
	}
}
void	SelectStackedWindows::ResizeAction()
{
	int	N=MContainer.GetCount();
	if(N>0){
		int	H=height()/N;
		int	YPos=0;
		for(AllocationList *a=MContainer.GetFirst();a!=NULL;a=a->GetNext()){
			a->Button.setGeometry(0,YPos,width(),H);
			YPos+=H;
		}
	}
}

bool	SelectStackedWindows::ShowQByteArrayDialog(const QString &VariableName)
{
	if(VariableName==/**/"MenuData"){
		AllocateMenuDialog	*D=new AllocateMenuDialog(&MenuData);
		if(D->exec()==(int)true){
			ReadyParam();
			ResizeAction();
		}
		delete	D;
	}
	return true;
}

void	SelectStackedWindows::SlotClick(const QString &InstName,const QString &PageName)
{
	GUIFormBase	*f=GetLayersBase()->FindByName(InstName);
	if(f!=NULL){
		OpenTabPageSpecifiedBroadcaster	RCmd;
		RCmd.TabPageName=PageName;
		f->BroadcastSpecifiedDirectly(&RCmd);
	}
}