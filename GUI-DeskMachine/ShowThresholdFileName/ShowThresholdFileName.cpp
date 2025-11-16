#include "ShowThresholdFileName.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "ShowThresholdFileNameForm.h"

static	char	*sRoot="Panel";
static	char	*sName="ShowThresholdFileName";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Show file name of threshold");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
///	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowThresholdFileNameForm(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	;
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<20){
		return(-1);
	}
	Data[0].Type					="bool";
	Data[0].VariableNameWithRoute	="ShowThresholdFile";
	Data[0].Pointer					=&((ShowThresholdFileNameForm *)Instance)->ShowThresholdFile;
	Data[1].Type					="QString";
	Data[1].VariableNameWithRoute	="TitleThresholdFile";
	Data[1].Pointer					=&((ShowThresholdFileNameForm *)Instance)->TitleThresholdFile;
	Data[2].Type					="bool";
	Data[2].VariableNameWithRoute	="ShowHeadThresholdFile";
	Data[2].Pointer					=&((ShowThresholdFileNameForm *)Instance)->ShowHeadThresholdFile;

	Data[3].Type					="AlignLeft,AlignCenter,AlignRight";
	Data[3].VariableNameWithRoute	="AlignAttr";
	Data[3].Pointer				=&((ShowThresholdFileNameForm *)Instance)->AlignAttr;
	Data[4].Type					="QColor";
	Data[4].VariableNameWithRoute	="CharColor";
	Data[4].Pointer				=&((ShowThresholdFileNameForm *)Instance)->CharColor;
	Data[5].Type					="QColor";
	Data[5].VariableNameWithRoute	="BackColor";
	Data[5].Pointer				=&((ShowThresholdFileNameForm *)Instance)->BackColor;
	Data[6].Type					="bool";
	Data[6].VariableNameWithRoute	="TransparentBackColor";
	Data[6].Pointer				=&((ShowThresholdFileNameForm *)Instance)->TransparentBackColor;
	Data[7].Type					="QColor";
	Data[7].VariableNameWithRoute	="BorderColor";
	Data[7].Pointer				=&((ShowThresholdFileNameForm *)Instance)->BorderColor;
	Data[8].Type					="int32";
	Data[8].VariableNameWithRoute	="BorderWidth";
	Data[8].Pointer				=&((ShowThresholdFileNameForm *)Instance)->BorderWidth;
	Data[9].Type					="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[9].VariableNameWithRoute	="BorderStyle";
	Data[9].Pointer				=&((ShowThresholdFileNameForm *)Instance)->BorderStyle;
	Data[10].Type					="QFont";
	Data[10].VariableNameWithRoute	="CFont";
	Data[10].Pointer				=&((ShowThresholdFileNameForm *)Instance)->CFont;

	Data[11].Type					="AlignLeft,AlignCenter,AlignRight";
	Data[11].VariableNameWithRoute	="HeadAlignAttr";
	Data[11].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadAlignAttr;
	Data[12].Type					="QColor";
	Data[12].VariableNameWithRoute	="HeadCharColor";
	Data[12].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadCharColor;
	Data[13].Type					="QColor";
	Data[13].VariableNameWithRoute	="HeadBackColor";
	Data[13].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadBackColor;
	Data[14].Type					="bool";
	Data[14].VariableNameWithRoute	="HeadTransparentBackColor";
	Data[14].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadTransparentBackColor;
	Data[15].Type					="QColor";
	Data[15].VariableNameWithRoute	="HeadBorderColor";
	Data[15].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadBorderColor;
	Data[16].Type					="int32";
	Data[16].VariableNameWithRoute	="HeadBorderWidth";
	Data[16].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadBorderWidth;
	Data[17].Type					="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[17].VariableNameWithRoute	="HeadBorderStyle";
	Data[17].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadBorderStyle;
	Data[18].Type					="QFont";
	Data[18].VariableNameWithRoute	="HeadCFont";
	Data[18].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadCFont;

	Data[19].Type					="int32";
	Data[19].VariableNameWithRoute	="HeadWidth";
	Data[19].Pointer				=&((ShowThresholdFileNameForm *)Instance)->HeadWidth;

	return(20);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ShowMasterNames.png")));
}

