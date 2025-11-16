#include "ButtonHelp.h"
#include "XGeneralFunc.h"
#include "XFileRegistry.h"



char	*sRoot="Button";
char	*sName="ButtonHelp";

DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}
DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Button Display NGList");
}
/*
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
	LangSolver.SetLanguage(Pkg,LanguageCode);
}
*/
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
	return(new ButtonHelp(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<0){
		return(-1);
	}

	return(0);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ButtonHelp.png")));
}

//=========================================================================================================

ButtonHelp::ButtonHelp(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent),Button(parent,false)
{
	//Œ¾Œê‘Î‰ž
	FileRegistry	*FRegistry=new FileRegistry("./MachineInfo.dat");
	int	LanguageCode=FRegistry->LoadRegInt("Language",0);

	QString ImageBmpFile[5]={
		":Resources/HelpImage.bmp",		//“ú–{Œê
		":Resources/HelpImage-en.bmp",	//English
		":Resources/HelpImage-en.bmp",	//ŠÈ‘Ì’†•¶
		":Resources/HelpImage-en.bmp",	//”É‘Ì’†•¶
		":Resources/HelpImage-en.bmp"	//Korean
	};
	Button.setImageBmp(QImage(ImageBmpFile[LanguageCode]));

	Button.setParent(this);
	Button.move(0,0);
	resize(120,39);
	connect(&Button,SIGNAL(SignalClicked(bool)),this,SLOT(SlotClicked(bool)));
	connect(this,	SIGNAL(SignalResize()),		this,SLOT(ResizeAction()));
}


void	ButtonHelp::Prepare(void)
{
	ResizeAction();
}
void	ButtonHelp::ResizeAction()
{
	Button.resize(width(),height());
}

void ButtonHelp::SlotClicked (bool checked)
{
}
