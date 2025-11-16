/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\PanelInputInformation\PanelInputInformation.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "PanelInputInformation.h"
#include "ThreadSequence.h"
#include "XSequenceLocal.h"
#include "XExecuteInspectBase.h"
#include "XRememberer.h"
#include "XGUI.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=/**/"Panel";
	Name=/**/"InputInformation";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Information panel to input");
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
	return(new PanelInputInformation(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<7)
		return(-1);
	Data[0].Type				 =/**/"QStringList";
	Data[0].VariableNameWithRoute=/**/"ItemTitles";
	Data[0].Pointer				 =&((PanelInputInformation *)Instance)->ItemTitles;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"TitleColor";
	Data[1].Pointer				 =&((PanelInputInformation *)Instance)->TitleColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"InputColor";
	Data[2].Pointer				 =&((PanelInputInformation *)Instance)->InputColor;
	Data[3].Type				 =/**/"int32";
	Data[3].VariableNameWithRoute=/**/"ItemHeight";
	Data[3].Pointer				 =&((PanelInputInformation *)Instance)->ItemHeight;
	Data[4].Type				 =/**/"int32";
	Data[4].VariableNameWithRoute=/**/"TitleWidth";
	Data[4].Pointer				 =&((PanelInputInformation *)Instance)->TitleWidth;
	Data[5].Type				 =/**/"QFont";
	Data[5].VariableNameWithRoute=/**/"TitleFont";
	Data[5].Pointer				 =&((PanelInputInformation *)Instance)->TitleFont;
	Data[6].Type				 =/**/"QFont";
	Data[6].VariableNameWithRoute=/**/"InputFont";
	Data[6].Pointer				 =&((PanelInputInformation *)Instance)->InputFont;

	return(7);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/PanelInputInformation.png")));
}

DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	QStringList	LList;
	GuiAdditionalDatabase	*A=new GuiAdditionalDatabase(/**/"MASTERDATA",/**/"INPUTINFO",LList);
	Data.AppendList(A);
}

//==================================================================================================
PanelInputInformation::PanelInputInformation(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	CountOfItemControls	=0;
	ItemControls		=NULL;

	TitleColor=Qt::green;
	InputColor=Qt::black;

	ItemHeight	=25;
	TitleWidth	=100;
	resize(200,60);
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

PanelInputInformation::~PanelInputInformation(void)
{
	if(ItemControls!=NULL){
		delete	[]ItemControls;
	}
	CountOfItemControls	=0;
	ItemControls		=NULL;
}

void	PanelInputInformation::Prepare(void)
{
	CountOfItemControls	=ItemTitles.count();
	ItemControls=new struct	InformationItem[CountOfItemControls];
	for(int i=0;i<CountOfItemControls;i++){
		ItemControls[i].Edit		.setParent(this);
		ItemControls[i].ItemLabel	.setParent(this);
		ItemControls[i].ItemLabel	.resize(TitleWidth,ItemHeight);

		ItemControls[i].ItemLabel	.setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);

		QPalette	PEdit=ItemControls[i].Edit		.palette();
		PEdit.setColor(QPalette::Text,InputColor);
		ItemControls[i].Edit		.setPalette(PEdit);
		ItemControls[i].Edit		.setFont(InputFont);

		QPalette	PLabel=ItemControls[i].ItemLabel		.palette();
		PLabel.setColor(QPalette::WindowText,TitleColor);
		ItemControls[i].ItemLabel		.setPalette(PLabel);
		ItemControls[i].ItemLabel		.setFont(TitleFont);

		ItemControls[i].ItemLabel	.setText(ItemTitles[i]);
	}

	QStringList	LList=ControlRememberer::GetStringList	(/**/"InputInformationList");
	ReflectToWindow(LList);
}

void		PanelInputInformation::ReflectToWindow(QStringList &LList)
{
	for(int i=0;i<CountOfItemControls && i<LList.count();i++){
		ItemControls[i].Edit.setText(LList[i]);
	}
}
QStringList	PanelInputInformation::GetListFromWindow(void)
{
	QStringList	LList;
	for(int i=0;i<CountOfItemControls;i++){
		LList.append(ItemControls[i].Edit.text());
	}
	return LList;
}
void	PanelInputInformation::ResizeAction(void)
{
	int	XGap=4;
	int	Mergin=(height()-ItemHeight*CountOfItemControls)/(CountOfItemControls+1);

	for(int i=0;i<CountOfItemControls;i++){
		ItemControls[i].ItemLabel.move(0				,Mergin+i*(Mergin+ItemHeight));
		ItemControls[i].Edit	 .move(TitleWidth+XGap	,Mergin+i*(Mergin+ItemHeight));
		ItemControls[i].Edit	 .resize(width()-TitleWidth-XGap,ItemHeight);
	}
}

void	PanelInputInformation::SpecifiedDirectly(SpecifiedBroadcaster *v)
{
	LoadMasterSpecifiedBroadcaster	*LoadMasterSpecifiedBroadcasterVar=dynamic_cast<LoadMasterSpecifiedBroadcaster *>(v);
	if(LoadMasterSpecifiedBroadcasterVar!=NULL){
		QVariant	data;
		if(GetLayersBase()->LoadMasterFieldData(/**/"INPUTINFO", data)==true){
			QStringList	LList=data.toStringList();
			ReflectToWindow(LList);
		}
		return;
	}
	CreateUpdateMasterSpecifiedBroadcaster	*CreateUpdateMasterSpecifiedBroadcasterVar=dynamic_cast<CreateUpdateMasterSpecifiedBroadcaster *>(v);
	if(CreateUpdateMasterSpecifiedBroadcasterVar!=NULL){
		QStringList	LList=GetListFromWindow();
		GetLayersBase()->AddMasterFieldData(/**/"INPUTINFO", LList);
		return;
	}
	CloseApplicationSpecifiedBroadcaster	*CloseApplicationSpecifiedBroadcasterVar=dynamic_cast<CloseApplicationSpecifiedBroadcaster *>(v);
	if(CloseApplicationSpecifiedBroadcasterVar!=NULL){
		QStringList	LList=GetListFromWindow();
		ControlRememberer::SetValue(/**/"InputInformationList",LList);
		return;
	}
}

void	PanelInputInformation::TransmitDirectly(GUIDirectMessage *packet)
{
	CmdReqInputInformationPacket	*CmdReqInputInformationPacketVar=dynamic_cast<CmdReqInputInformationPacket *>(packet);
	if(CmdReqInputInformationPacketVar!=NULL){
		for(int i=0;i<CountOfItemControls;i++){
			CmdReqInputInformationPacketVar->Titles.append(ItemControls[i].ItemLabel.text());
			CmdReqInputInformationPacketVar->Datas .append(ItemControls[i].Edit     .text());
		}
		return;
	}
}
