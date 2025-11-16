#if	!defined(XGENERALSTOCKER_H)
#define	XGENERALSTOCKER_H

#include <QtGui>
#include <QVariant>
#include <QIODevice>
#include <QLibrary>

#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XServiceForLayers.h"
#include "XDatabase.h"
#include "XGeneralStockerClass.h"

class	LayersBase;
class	GeneralStocker;
class	GeneralStockerContainer;
class	LanguagePackage;
class	GUIDirectMessage;
class	ResultInspection;
struct	PropertyGeneralStocker;
class	ListPhasePageLayerPack;
class	ExecuteInitialAfterEditInfo;
class	GuiAdditionalDatabase;
class	SpecifiedBroadcaster;


class	GeneralStockerPointerList : public NPList<GeneralStockerPointerList>
{
public:
	GeneralStocker	*Point;
	GeneralStockerPointerList(void){}
	GeneralStockerPointerList(GeneralStocker *p){	Point=p;	}
};

class	GeneralStocker : public NPList<GeneralStocker>, public ServiceForLayers
{
	friend	class	GeneralStockerContainer;

	bool			ReEntrantDLL;
	bool			(*DLL_GetName)(QString &str);
	bool			(*DLL_GetOrganization)(QString &str);
	WORD			(*DLL_GetDLLType)(void);
	WORD			(*DLL_GetVersion)(void);
	const char		*(*DLL_GetSystemVersion)(VersionType vtype);
	void			(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);
	void			(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	GeneralStockerItemBase	*(*DLL_Initial)(LayersBase *base);
	void			(*DLL_Release)(GeneralStockerItemBase *handle);
	void			(*DLL_ReturnProperty)(struct	PropertyGeneralStocker &Prop);

	void			(*DLL_EnumKeyword)(GeneralStockerItemBase *handle ,QStringList &List);
	QVariant::Type	(*DLL_GetType)(GeneralStockerItemBase *handle ,QString Keyword);
	bool			(*DLL_GetData)(GeneralStockerItemBase *handle ,QString Keyword 
										,QVariantList &ReturnValue,QVariantList &ArgValue);

	bool			(*DLL_ShowDialog)(GeneralStockerItemBase *handle ,QString Keyword, QWidget *parent);
	void			(*DLL_TransmitDirectly)(GeneralStockerItemBase *handle ,GUIDirectMessage *packet);

	bool			(*DLL_Save)(QIODevice *f ,GeneralStockerItemBase *handle);
	bool			(*DLL_Load)(QIODevice *f ,GeneralStockerItemBase *handle);
	void			(*DLL_GetGuiAdditionalDatabase)(NPListPack<GuiAdditionalDatabase> &Data);

	ExeResult	(*DLL_ExecuteInitialAfterEditPrev)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteInitialAfterEditPost)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteStartByInspectionPrev)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteStartByInspectionPost)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteCapturedPrev)			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	(*DLL_ExecuteCapturedPost)			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	(*DLL_ExecutePreAlignmentPrev)		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePreAlignmentPost)		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteAlignmentPrev)			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteAlignmentPost)			(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePreProcessingPrev)		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePreProcessingPost)		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteProcessingPrev)		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteProcessingPost)		(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteProcessingRevivedPrev)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecuteProcessingRevivedPost)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePostProcessingPrev)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);
	ExeResult	(*DLL_ExecutePostProcessingPost)	(int ExeID ,GeneralStockerItemBase *handle ,ResultInspection *Res);

	QLibrary 		DllLib;
	QString			FileName;
	QString			Name;
	QString			Organization;
	QStringList		KeywordList;
	bool			SynchronizeToSlave;
	bool			SaveInMasterData;
	GeneralStockerItemBase	*Handle;

public:
	GeneralStocker(LayersBase *base);
	~GeneralStocker(void);

	bool			OpenDLL(const QString &DLLFileName);
	void			CloseDLL(void);
	bool			CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);

	void			Initial(LayersBase *base);
	void			InitialAfterParamLoaded(void);
	void			SetLanguage(int LanguageCode);
	bool			GetSynchronizeToSlave(void)		{	return SynchronizeToSlave;	}
	bool			GetSaveInMasterData(void)		{	return SaveInMasterData;	}

	void			EnumKeyword(QStringList &List);
	QVariant::Type	GetType(QString Keyword);
	bool			GetData(LayersBase *Base ,const QString &Keyword 
										,QVariantList &ReturnValue,QVariantList &ArgValue);

	GeneralStockerItemBase	*GetHandle(void)	{	return Handle;	}
	bool			ShowDialog(const QString &Keyword, QWidget *parent);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	void			SpecifiedDirectly(SpecifiedBroadcaster *v);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	bool	InitialAdditionalFieldFromGUI(QSqlDatabase &DB);
	bool	CreateExcludedList(ExcludedListPack &EList);

	QString			GetName(void)			{	return Name;	}
	QString			GetOrganization(void)	{	return Organization;	}
	bool			ExistsKeyword(const QString &Keyword);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInspection *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteStartByInspectionPrev(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteStartByInspectionPost(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteCapturedPrev			(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecuteCapturedPost			(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignmentPrev		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreAlignmentPost		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteAlignmentPrev		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteAlignmentPost		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreProcessingPrev	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreProcessingPost	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingPrev		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingPost		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingRevivedPrev(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingRevivedPost(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostProcessingPrev	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostProcessingPost	(int ExeID ,ResultInspection *Res);

	void	GetExportFunctions(QStringList &Str);
};

class	GeneralStockerContainer : public NPListPack<GeneralStocker> ,public ServiceForLayers
{
public:
	GeneralStockerContainer(LayersBase *base):ServiceForLayers(base){}

	bool			OpenDLL(void);
	void			Initial(void);
	void			InitialAfterParamLoaded(void);
	void			SetLanguage(int LanguageCode);
	void			AssociateComponent	(ComponentListContainer &List);

	GeneralStocker	*Search(const QString &DLLName);
	QVariant::Type	GetType(const QString &Keyword);
	bool			GetData(const QString &Keyword 
							,QVariantList &ReturnValue,QVariantList &ArgValue);

	int				GetCountOfEffectiveShowDialog(const QString &Keyword);
	bool			ShowDialog(const QString &Keyword, QWidget *parent);
	void			TransmitDirectly(const QString &Keyword ,GUIDirectMessage *packet);
	void			TransmitDirectly(GUIDirectMessage *packet);
	void			TransmitDirectlyByName(const QString &GeneralStockerDLLName ,GUIDirectMessage *packet);
	void			SpecifiedDirectly(SpecifiedBroadcaster *v);
	bool			Save(QIODevice *f ,struct PropertyGeneralStocker &Prop);
	bool			Load(QIODevice *f ,struct PropertyGeneralStocker &Prop);

	bool			CheckSystemVersion(QStringList &Str);

	QString			GetFileName(void);
	GeneralStocker	*GetShowDialogPointer(int n);

	bool	InitialAdditionalFieldFromGUI(QSqlDatabase &DB,QString &ErrorMsg);
	bool	CreateExcludedList(ExcludedListPack &EList);

	ExeResult	ExecuteInitialAfterEditPrev	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteStartByInspectionPrev(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteStartByInspectionPost(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteCapturedPrev			(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecuteCapturedPost			(int ExeID ,ResultInspection *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignmentPrev		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreAlignmentPost		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteAlignmentPrev		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteAlignmentPost		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreProcessingPrev	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePreProcessingPost	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingPrev		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingPost		(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingRevivedPrev(int ExeID ,ResultInspection *Res);
	ExeResult	ExecuteProcessingRevivedPost(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostProcessingPrev	(int ExeID ,ResultInspection *Res);
	ExeResult	ExecutePostProcessingPost	(int ExeID ,ResultInspection *Res);
};


#endif