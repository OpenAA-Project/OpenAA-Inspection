/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\ButtonSettingPrinter\ButtonSettingPrinter.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/
//#include "ButtonSettingPrinter.h"
#include "ButtonSettingPrinter.h"
#include "XExecuteInspectBase.h"
#include "XGeneralFunc.h"
#include "XGUIDLL.h"
#include "SelectPrinterDialog.h"

//extern	LangSolverNew	LangCGSolver;



char	*sRoot=/**/"Button";
char	*sName=/**/"ButtonSettingPrinter";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return(/**/"Button to show setting printer");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	//LangSolver.SetLanguage(Pkg,LanguageCode);
}
DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	//(*Base)=new GUICmdSelectLot(Base ,sRoot,sName ,-1);

	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ButtonSettingPrinter(Base,parent));
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
	Data[0].Pointer				 =&((ButtonSettingPrinter *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 =/**/"QColor";
	Data[1].VariableNameWithRoute=/**/"CharColor";
	Data[1].Pointer				 =&((ButtonSettingPrinter *)Instance)->CharColor;
	Data[2].Type				 =/**/"QColor";
	Data[2].VariableNameWithRoute=/**/"BackColor";
	Data[2].Pointer				 =&((ButtonSettingPrinter *)Instance)->BackColor;
	Data[3].Type				 =/**/"QFont";
	Data[3].VariableNameWithRoute=/**/"CFont";
	Data[3].Pointer				 =&((ButtonSettingPrinter *)Instance)->CFont;

	return(4);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(/**/":Resources/ButtonSettingPrinter.png")));
}

//==================================================================================================


ButtonSettingPrinter::ButtonSettingPrinter(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	Button.setParent(this);
	Button.move(0,0);
	Button.setObjectName(/**/"ButtonToPrint");
	Msg=/**/"Button print";
	resize(60,25);

	connect(&Button,SIGNAL(clicked(bool)), this ,SLOT(SlotClicked(bool)));
	connect(this,SIGNAL(SignalResize()), this ,SLOT(ResizeAction()));
}

ButtonSettingPrinter::~ButtonSettingPrinter(void)
{
}

void	ButtonSettingPrinter::Prepare(void)
{
	Button.setText(Msg);
	Button.setFont (CFont);
	ResizeAction();
}

void	ButtonSettingPrinter::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonSettingPrinter::SlotClicked (bool checked)
{
	SelectPrinterDialog	*SelectLot=new SelectPrinterDialog(this,GetLayersBase(),this);
	LogoInQWidget(GetLayersBase(),SelectLot,sRoot ,sName);
	SelectLot->exec();

}

void	ButtonSettingPrinter::TransmitDirectly(GUIDirectMessage *packet)
{
}

void	ButtonSettingPrinter::GetMenuInfo(MenuInfoContainer &Info)
{
	MenuInfoList	*p=new MenuInfoList(1
										,"Print"
										,"Output print",this);
	p->SetMenuNumber(100);
	Info.AppendList(p);
}
void	ButtonSettingPrinter::ExecuteMenu(int ID)
{
	if(ID==1){
		SlotClicked(true);
	}
}



