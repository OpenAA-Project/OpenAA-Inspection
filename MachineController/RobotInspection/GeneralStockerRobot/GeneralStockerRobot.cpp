#include "GeneralStockerRobot.h"
#include "XTypeDef.h"
#include "XGeneralStockerForDLL.h"
#include "XDataInLayer.h"
#include "XDateTime.h"
#include "XLotInformation.h"
#include "XDatabaseLoader.h"
#include "XForWindows.h"
#include "XGeneralFunc.h"
#include "XCrossObj.h"
#include "XGUIFormBase.h"
#include "swap.h"
#include "XResult.h"
#include "XImageProcess.h"
#include "XPointer.h"
#include "XGeneralStockerClass.h"


//BatteryStocker	*LPointer;

//====================================================================================

DEFFUNCEX	bool			DLL_GetName(QString &str)
/*
	このＤＬＬの名称を返す
	str:	返す名称を設定する
	検査システムからＤＬＬをオープンした後、
		「DLL_Initial」が呼ばれる直前にこの関数が呼ばれる
	このExport関数は必ず必要
*/
{
	str=/**/"GeneralStockerRobot";
	return true;
}

DEFFUNCEX	bool			DLL_GetOrganization(QString &str)
/*
	このＤＬＬの組織名を返す
	str:	返す組織名を設定する
	検査システムからＤＬＬをオープンした後、
		「DLL_Initial」が呼ばれる直前にこの関数が呼ばれる
	このExport関数は必ずしも必要ない
*/
{
	str=/**/"MEGATRADE";
	return true;
}
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString)
{
	CopyrightString=/**/"MEGATRADE";
	return true;
}

DEFFUNCEX	WORD			DLL_GetDLLType(void)
/*
	必ず「DLLGeneralStockerMode」を返すべき
	検査システムからＤＬＬをオープンするときにこの値がチェックされる
	このExport関数は必ず必要
*/
{
	return DLLGeneralStockerMode;
}
DEFFUNCEX	WORD			DLL_GetVersion(void)
/*
	このＤＬＬのバージョン番号を返す。
	これはシステムでは使用していない
	このExport関数は必ずしも必要ない
*/
{
	return 1;
}


DEFFUNCEX	void			DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode)
{
}

DEFFUNCEX	GeneralStockerItemBase	*DLL_Initial(LayersBase *base)
{
	GeneralStockerRobot	*LPointer=new GeneralStockerRobot(base);
	return LPointer;
}
DEFFUNCEX	void			DLL_Release(GeneralStockerItemBase *handle)
{

}


DEFFUNCEX	void			DLL_EnumKeyword(GeneralStockerItemBase *handle ,QStringList &List)
{
	List<<"GeneralStockerRobot";
}

DEFFUNCEX	QVariant::Type	DLL_GetType(GeneralStockerItemBase *handle ,QString Keyword)
/*
	キーワードの型を返す	
	このExport関数は必ず必要
*/
{
	return QVariant::Invalid;
}
DEFFUNCEX	bool			DLL_GetData(GeneralStockerItemBase *handle ,QString Keyword 
										,QVariantList &ReturnValues,QVariantList &ArgValues);
/*
	キーワードにひも付けされたデータを返す
	ArgValuesに必要があれば引数を入れる
	ReturnValuesにデータを入れてリターンする

	正常に終了したとき、trueを返さなければならない
	このExport関数は必ず必要
*/

DEFFUNCEX	bool				DLL_ShowDialog(GeneralStockerItemBase *handle,QString Keyword, QWidget *parent)
/*
	キーワードに関連するダイアログを開く
	これが呼ばれるのは、特定の処理系に依存する
	このExport関数は必ずしも必要ない
*/
{
	return true;
}

DEFFUNCEX	bool			DLL_Save(QIODevice *f,GeneralStockerItemBase *handle)
/*
	設定情報を保存する
	このExport関数は必ずしも必要ない
*/
{

	return true;
}

DEFFUNCEX	bool			DLL_Load(QIODevice *f,GeneralStockerItemBase *handle)
/*
	設定情報を読みだし、このＤＬＬに設定する
	このExport関数は必ずしも必要ない
*/
{
	return true;
}


DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data)
{
	GuiAdditionalDatabase	*RobotSpline=new GuiAdditionalDatabase();
	RobotSpline->TableName=/**/"MASTERDATA";
	RobotSpline->FieldName=/**/"ROBOTSPLINE";
	QByteArray	A;
	RobotSpline->DefaultData.setValue(A);
	Data.AppendList(RobotSpline);

}
DEFFUNCEX	void	DLL_TransmitDirectly(GeneralStockerItemBase *handle ,GUIDirectMessage *packet)
{
	GeneralStockerRobot	*H=(GeneralStockerRobot *)handle;
	H->TransmitDirectly(packet);
}

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res)
{
	GeneralStockerRobot	*H=(GeneralStockerRobot *)handle;
	return H->ExecuteInitialAfterEditPost	(ExeID ,Res);
}