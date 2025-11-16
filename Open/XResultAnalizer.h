#if	!defined(XResultAnalizer_h)
#define	XResultAnalizer_h

#include <QtGui>
#include <QVariant>
#include <QIODevice>
#include <QLibrary>

#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"

class	LayersBase;
class	ResultAnalizerDLL;
class	ResultAnalizerDLLContainer;
class	LanguagePackage;
class	GUIDirectMessage;
class	ResultInspection;
class	ResultInItemRoot;
class	AlgorithmBase;
class	ListPhasePageLayerPack;
class	ExecuteInitialAfterEditInfo;

enum ModeParallelExecution{
	 ModeParallelExecution_ExecuteInitialAfterEditPost	=1
	,ModeParallelExecution_ExecuteStartByInspectionPost	=2
	,ModeParallelExecution_ExecuteCapturedPost			=9
	,ModeParallelExecution_ExecutePreAlignmentPost		=3
	,ModeParallelExecution_ExecuteAlignmentPost			=4
	,ModeParallelExecution_ExecutePreProcessingPost		=5
	,ModeParallelExecution_ExecuteProcessingPost		=6
	,ModeParallelExecution_ExecuteProcessingRevivedPost	=7
	,ModeParallelExecution_ExecutePostProcessingPost	=8
};

class	ResultAnalizerItemBase : public NPList<ResultAnalizerItemBase>,public ServiceForLayers
{
	friend	class	ResultAnalizerDLL;
	friend	class	ResultAnalizerItemBaseContainer;

	ResultAnalizerDLL	*DLLHandle;
	QString		Name;
	int32		ID;
public:
	ResultAnalizerItemBase(void):ServiceForLayers(NULL),DLLHandle(NULL){}
	ResultAnalizerItemBase(LayersBase *base,ResultAnalizerDLL *DLLInst=NULL):ServiceForLayers(base),DLLHandle(DLLInst){}
	virtual	~ResultAnalizerItemBase(void){}

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}

	const QString	&GetName(void)				const	{	return Name;	}
	void			SetName(const QString &name)		{	Name=name;		}
	int		GetID(void)							const	{	return ID;		}
	void	SetID(int id)								{	ID=id;			}

	ResultAnalizerDLL	*GetDLL(void)			const	{	return DLLHandle;	}
	virtual	bool	ShowSettingDialogFunc(void)				{	return true;	}
	virtual	bool	ShowResultDialogFunc(QByteArray &Data)	{	return true;	}
	virtual	bool	MakeDataForShow(ResultInItemRoot *Res ,QByteArray &RetData)	{	return false;	}

	bool	ShowResultDialogFunc(AlgorithmBase *Abase,int Phase ,int GlobalPage,int Layer,int ItemID);

	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	bool	Load(QIODevice *f)	{	return true;	}

	virtual	bool	MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteStartByInspectionPost(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteCapturedPost			(int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignmentPost		(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteAlignmentPost		(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecutePreProcessingPost	(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteProcessingPost		(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteProcessingRevivedPost(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecutePostProcessingPost	(int ExeID ,ResultInItemRoot *Res);
};


class	ResultAnalizerItemBaseContainer : public NPListPack<ResultAnalizerItemBase>
										 ,public ServiceForLayers
{
	friend	class	ResultAnalizerItemBase;
public:
	ResultAnalizerItemBaseContainer(LayersBase *base):ServiceForLayers(base){}

	void		TransmitDirectly(GUIDirectMessage *packet);

	bool		Save(QIODevice *f);
	bool		Load(QIODevice *f);
	bool		LoadDefault(void);
	bool		SaveDefault(void);
	int			GetMaxID(void)	const;

	ResultAnalizerItemBase	*FindByID(int ResultAnalizerItemBaseID);

	bool		MakeExecuteInitialAfterEditInfo	(int ExeID ,ResultInItemRoot *Res,ExecuteInitialAfterEditInfo &EInfo);
	ExeResult	ExecuteInitialAfterEditPost	(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteStartByInspectionPost(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteCapturedPost			(int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	ExecutePreAlignmentPost		(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteAlignmentPost		(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecutePreProcessingPost	(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteProcessingPost		(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecuteProcessingRevivedPost(int ExeID ,ResultInItemRoot *Res);
	ExeResult	ExecutePostProcessingPost	(int ExeID ,ResultInItemRoot *Res);
};


//-------------------------------------------------------------------------------------------------------

class	ResultAnalizerDLL : public NPList<ResultAnalizerDLL>, public ServiceForLayers
{
	friend	class	ResultAnalizerDLLContainer;
	friend	class	ResultAnalizerItemBase;

	bool			ReEntrantDLL;
	void			(*DLL_GetName)(QString &Root ,QString &Name);
	bool			(*DLL_GetOrganization)(QString &str);
	WORD			(*DLL_GetDLLType)(void);
	WORD			(*DLL_GetVersion)(void);
	const char		*(*DLL_GetSystemVersion)(VersionType vtype);
	void			(*DLL_AssociateComponent)(LayersBase *Base,ComponentListContainer &List);

	void			(*DLL_SetLanguage)(LanguagePackage &Pkg ,int LanguageCode);
	ResultAnalizerItemBase	*(*DLL_Initial)(LayersBase *base);
	void			(*DLL_Release)(ResultAnalizerItemBase *handle);
	bool			(*DLL_CheckParallelExecution)(ModeParallelExecution mode);

	ExeResult	(*DLL_ExecuteInitialAfterEditPost)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecuteStartByInspectionPost)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecuteCapturedPost)			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res,ListPhasePageLayerPack &CapturedList);
	ExeResult	(*DLL_ExecutePreAlignmentPost)		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecuteAlignmentPost)			(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecutePreProcessingPost)		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecuteProcessingPost)		(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecuteProcessingRevivedPost)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);
	ExeResult	(*DLL_ExecutePostProcessingPost)	(ResultAnalizerItemBase *handle ,int ExeID ,ResultInItemRoot *Res);

	QLibrary 		DllLib;
	QString			FileName;
	QString			Root;
	QString			Name;
	QString			Organization;

public:
	ResultAnalizerDLL(LayersBase *base);
	~ResultAnalizerDLL(void);

	bool			OpenDLL(const QString &DLLFileName);
	void			CloseDLL(void);
	bool			CheckSystemVersion(QStringList &Str);
	void			AssociateComponent	(ComponentListContainer &List);

	ResultAnalizerItemBase	*InitialCreate(void);
	void			SetLanguage(int LanguageCode);

	void			GetRootName(QString &_Root ,QString &_Name)			{	_Name=Name;	_Root=Root;	}
	QString			GetOrganization(void)	{	return Organization;	}
};


class	ResultAnalizerDLLContainer : public NPListPack<ResultAnalizerDLL> ,public ServiceForLayers
{
public:
	ResultAnalizerDLLContainer(LayersBase *base):ServiceForLayers(base){}

	bool			OpenDLL(void);
	void			SetLanguage(int LanguageCode);
	void			AssociateComponent	(ComponentListContainer &List);
	ResultAnalizerDLL	*Search(const QString &DLLRoot,const QString &DLLName);
	bool			CheckSystemVersion(QStringList &Str);
};

//============================================================================
class	GUICmdReqResultAnalizerShowData : public GUICmdPacketBase
{
public:
	int		ResultAnalizerItemBaseID;
	QString	AlgoRoot;
	QString	AlgoName;
	int		Phase;
	int		Layer;
	int		ItemID;

	GUICmdReqResultAnalizerShowData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	GUICmdAckResultAnalizerShowData : public GUICmdPacketBase
{
public:
	bool		Effective;
	QByteArray	DataForShow;

	GUICmdAckResultAnalizerShowData(LayersBase *base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif