#include "ShowResultInformation.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "ShowResultInformationForm.h"

static	char	*sRoot="Panel";
static	char	*sName="ShowResultInformation";



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root=sRoot;
	Name=sName;
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("Show Result Information");
}
DEFFUNCEX	void	DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
//	LangSolver.SetLanguage(Pkg,LanguageCode);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new ShowResultInformationForm(Base,parent));
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
	if(maxDataDim<29){
		return(-1);
	}
	Data[0].Type					="bool";
	Data[0].VariableNameWithRoute	="ShowInspectCount";
	Data[0].Pointer					=&((ShowResultInformationForm *)Instance)->ShowInspectCount;
	Data[1].Type					="bool";
	Data[1].VariableNameWithRoute	="ShowOKCount";
	Data[1].Pointer					=&((ShowResultInformationForm *)Instance)->ShowOKCount;
	Data[2].Type					="bool";
	Data[2].VariableNameWithRoute	="ShowNGCount";
	Data[2].Pointer					=&((ShowResultInformationForm *)Instance)->ShowNGCount;
	Data[3].Type					="bool";
	Data[3].VariableNameWithRoute	="ShowReInspectCount";
	Data[3].Pointer					=&((ShowResultInformationForm *)Instance)->ShowReInspectCount;

	Data[4].Type					="QString";
	Data[4].VariableNameWithRoute	="TitleInspectCount";
	Data[4].Pointer					=&((ShowResultInformationForm *)Instance)->TitleInspectCount;
	Data[5].Type					="QString";
	Data[5].VariableNameWithRoute	="TitleOKCount";
	Data[5].Pointer					=&((ShowResultInformationForm *)Instance)->TitleOKCount;
	Data[6].Type					="QString";
	Data[6].VariableNameWithRoute	="TitleNGCount";
	Data[6].Pointer					=&((ShowResultInformationForm *)Instance)->TitleNGCount;
	Data[7].Type					="QString";
	Data[7].VariableNameWithRoute	="TitleReInspectCount";
	Data[7].Pointer					=&((ShowResultInformationForm *)Instance)->TitleReInspectCount;

	Data[8].Type					="bool";
	Data[8].VariableNameWithRoute	="ShowHeadInspectCount";
	Data[8].Pointer					=&((ShowResultInformationForm *)Instance)->ShowHeadInspectCount;
	Data[9].Type					="bool";
	Data[9].VariableNameWithRoute	="ShowHeadOKCount";
	Data[9].Pointer					=&((ShowResultInformationForm *)Instance)->ShowHeadOKCount;
	Data[10].Type					="bool";
	Data[10].VariableNameWithRoute	="ShowHeadNGCount";
	Data[10].Pointer				=&((ShowResultInformationForm *)Instance)->ShowHeadNGCount;
	Data[11].Type					="bool";
	Data[11].VariableNameWithRoute	="ShowHeadReInspectCount";
	Data[11].Pointer				=&((ShowResultInformationForm *)Instance)->ShowHeadReInspectCount;

	Data[12].Type					="AlignLeft,AlignCenter,AlignRight";
	Data[12].VariableNameWithRoute	="AlignAttr";
	Data[12].Pointer				=&((ShowResultInformationForm *)Instance)->AlignAttr;
	Data[13].Type					="QColor";
	Data[13].VariableNameWithRoute	="CharColor";
	Data[13].Pointer				=&((ShowResultInformationForm *)Instance)->CharColor;
	Data[14].Type					="QColor";
	Data[14].VariableNameWithRoute	="BackColor";
	Data[14].Pointer				=&((ShowResultInformationForm *)Instance)->BackColor;
	Data[15].Type					="bool";
	Data[15].VariableNameWithRoute	="TransparentBackColor";
	Data[15].Pointer				=&((ShowResultInformationForm *)Instance)->TransparentBackColor;
	Data[16].Type					="QColor";
	Data[16].VariableNameWithRoute	="BorderColor";
	Data[16].Pointer				=&((ShowResultInformationForm *)Instance)->BorderColor;
	Data[17].Type					="int32";
	Data[17].VariableNameWithRoute	="BorderWidth";
	Data[17].Pointer				=&((ShowResultInformationForm *)Instance)->BorderWidth;
	Data[18].Type					="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[18].VariableNameWithRoute	="BorderStyle";
	Data[18].Pointer				=&((ShowResultInformationForm *)Instance)->BorderStyle;
	Data[19].Type					="QFont";
	Data[19].VariableNameWithRoute	="CFont";
	Data[19].Pointer				=&((ShowResultInformationForm *)Instance)->CFont;

	Data[20].Type					="AlignLeft,AlignCenter,AlignRight";
	Data[20].VariableNameWithRoute	="HeadAlignAttr";
	Data[20].Pointer				=&((ShowResultInformationForm *)Instance)->HeadAlignAttr;
	Data[21].Type					="QColor";
	Data[21].VariableNameWithRoute	="HeadCharColor";
	Data[21].Pointer				=&((ShowResultInformationForm *)Instance)->HeadCharColor;
	Data[22].Type					="QColor";
	Data[22].VariableNameWithRoute	="HeadBackColor";
	Data[22].Pointer				=&((ShowResultInformationForm *)Instance)->HeadBackColor;
	Data[23].Type					="bool";
	Data[23].VariableNameWithRoute	="HeadTransparentBackColor";
	Data[23].Pointer				=&((ShowResultInformationForm *)Instance)->HeadTransparentBackColor;
	Data[24].Type					="QColor";
	Data[24].VariableNameWithRoute	="HeadBorderColor";
	Data[24].Pointer				=&((ShowResultInformationForm *)Instance)->HeadBorderColor;
	Data[25].Type					="int32";
	Data[25].VariableNameWithRoute	="HeadBorderWidth";
	Data[25].Pointer				=&((ShowResultInformationForm *)Instance)->HeadBorderWidth;
	Data[26].Type					="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[26].VariableNameWithRoute	="HeadBorderStyle";
	Data[26].Pointer				=&((ShowResultInformationForm *)Instance)->HeadBorderStyle;
	Data[27].Type					="QFont";
	Data[27].VariableNameWithRoute	="HeadCFont";
	Data[27].Pointer				=&((ShowResultInformationForm *)Instance)->HeadCFont;

	Data[28].Type					="int32";
	Data[28].VariableNameWithRoute	="HeadWidth";
	Data[28].Pointer				=&((ShowResultInformationForm *)Instance)->HeadWidth;

	return(29);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/ShowResultInformation.png")));
}
