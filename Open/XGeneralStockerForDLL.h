#if	!defined(XGENERALSTOCKERFORDLL_H)
#define	XGENERALSTOCKERFORDLL_H

#include <QtGui>
#include <QVariant>
#include <QIODevice>

#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"

#ifdef _MSC_VER
#define	DEFFUNCEX		__declspec(dllexport)
#else
#define	DEFFUNCEX
#endif


class	LanguagePackage;
class	GeneralStockerItemBase;
class	ListPhasePageLayerPack;

extern	"C"{

DEFFUNCEX	bool			DLL_GetName(QString &str);
/*
	このＤＬＬの名称を返す
	str:	返す名称を設定する
	検査システムからＤＬＬをオープンした後、
		「DLL_Initial」が呼ばれる直前にこの関数が呼ばれる
	このExport関数は必ず必要
*/
DEFFUNCEX	bool			DLL_GetOrganization(QString &str);
/*
	このＤＬＬの組織名を返す
	str:	返す組織名を設定する
	検査システムからＤＬＬをオープンした後、
		「DLL_Initial」が呼ばれる直前にこの関数が呼ばれる
	このExport関数は必ずしも必要ない
*/
DEFFUNCEX	bool	DLL_CheckCopyright(QString &CopyrightString);

DEFFUNCEX	WORD		DLL_GetDLLType(void);
/*
	必ず「DLLGeneralStockerMode」を返すべき
	検査システムからＤＬＬをオープンするときにこの値がチェックされる
	このExport関数は必ず必要
*/
DEFFUNCEX	WORD		DLL_GetVersion(void);
/*
	このＤＬＬのバージョン番号を返す。
	これはシステムでは使用していない
	このExport関数は必ずしも必要ない
*/
DEFFUNCEX	const char	*DLL_GetSystemVersion(VersionType vtype);

DEFFUNCEX	void		DLL_AssociateComponent(LayersBase *Base,ComponentListContainer &List);

DEFFUNCEX	void		DLL_SetLanguage(LanguagePackage &Pkg ,int LanguageCode);
/*
	ＤＬＬが言語に対応する必要がある時この引数を使って言語を設定する
	DLL_Initial」が呼ばれた後でこの関数が呼ばれる
	このExport関数は必ずしも必要ない
*/
DEFFUNCEX	GeneralStockerItemBase		*DLL_Initial(LayersBase *base);
/*
	ＤＬＬを初期化する
	内部処理はＤＬＬによる
	このExport関数は必ずしも必要ない
	ハンドルを返さなければならない
*/

DEFFUNCEX	void			DLL_Release(GeneralStockerItemBase *handle);
/*
	ＤＬＬを終了する直前に呼ばれる
	内部処理はＤＬＬによる
	このExport関数は必ずしも必要ない
*/

DEFFUNCEX	void			DLL_ReturnProperty(struct	PropertyGeneralStocker &Prop);
/*
	ＤＬＬを終了する直前に呼ばれる
	内部処理はＤＬＬによる
	このExport関数は必ずしも必要ない
*/

DEFFUNCEX	void			DLL_EnumKeyword(GeneralStockerItemBase *handle ,QStringList &List);
/*
	キーワードリストを返す
	このExport関数は必ず必要
*/

DEFFUNCEX	QVariant::Type	DLL_GetType(GeneralStockerItemBase *handle ,QString Keyword);
/*
	キーワードの型を返す	
	このExport関数は必ず必要
*/
DEFFUNCEX	bool			DLL_GetData(GeneralStockerItemBase *handle ,QString Keyword 
										,QVariantList &ReturnValues,QVariantList &ArgValues);
/*
	キーワードにひも付けされたデータを返す
	ArgValuesに必要があれば引数を入れる
	ReturnValuesにデータを入れてリターンする

	正常に終了したとき、trueを返さなければならない
	このExport関数は必ず必要
*/

DEFFUNCEX	bool				DLL_ShowDialog(GeneralStockerItemBase *handle ,QString Keyword, QWidget *parent);
/*
	キーワードに関連するダイアログを開く
	これが呼ばれるのは、特定の処理系に依存する
	このExport関数は必ずしも必要ない
*/

DEFFUNCEX	void	DLL_TransmitDirectly(GeneralStockerItemBase *handle ,GUIDirectMessage *packet);

DEFFUNCEX	bool			DLL_Save(QIODevice *f,GeneralStockerItemBase *handle);
/*
	設定情報を保存する
	このExport関数は必ずしも必要ない
*/
DEFFUNCEX	bool			DLL_Load(QIODevice *f,GeneralStockerItemBase *handle);
/*
	設定情報を読みだし、このＤＬＬに設定する
	このExport関数は必ずしも必要ない
*/

DEFFUNCEX	void	DLL_GetGuiAdditionalDatabase(NPListPack<GuiAdditionalDatabase> &Data);

DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPrev	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteInitialAfterEditPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPrev(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteStartByInspectionPost(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteCapturedPrev			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	DLL_ExecuteCapturedPost			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignmentPrev		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreAlignmentPost		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignmentPrev		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteAlignmentPost		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessingPrev	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePreProcessingPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPrev		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingPost		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevivedPrev(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecuteProcessingRevivedPost(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessingPrev	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
DEFFUNCEX	ExeResult	DLL_ExecutePostProcessingPost	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);

};


#endif