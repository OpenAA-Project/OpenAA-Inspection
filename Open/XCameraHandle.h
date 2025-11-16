#if	!defined(XCameraHandle_h)
#define	XCameraHandle_h

#include <QObject>
#include"XServiceForLayers.h"
#include "XTypeDef.h"
#include <QIODevice>
#include "XParamGlobal.h"

class	ExecuteInitialAfterEditInfo;

class	CameraHandle : public QObject
					  ,public ServiceForLayers
					  ,public IdentifiedClass
{
	Q_OBJECT

	int32		CamNo;

public:
	CameraHandle(int _CamNo ,LayersBase *base);

	virtual void	InitialPrepare(void){}
	virtual void	Prepare(void)		{}
	virtual void	AfterPrepare(void)	{}
	virtual void	ReadyParam(void)	{}
	virtual void	AfterStartSequence(void){}

	virtual	bool	MakeExecuteInitialAfterEditInfo	(int ExeID ,ExecuteInitialAfterEditInfo &EInfo)	{	return true;	}

	virtual	bool	Save(QIODevice *f)	{		return true;	}
	virtual	bool	Load(QIODevice *f)	{		return true;	}

	int		GetCamNo(void)	{	return CamNo;	}
	void	SetCamNo(int n)	{	CamNo=n;		}

	int		GetDotPerLine(void);
	int		GetMaxLines(void);

	virtual	bool	ReallocXYPixels(int NewDotPerLine ,int NewMaxLines)					{	return true;	}
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	{	return true;	}
	virtual	bool	ReallocateMasterCount(int CountMaster)								{	return true;	}
	virtual	bool	InsertPage(int IndexPage)	{	return true;	}
	virtual	bool	RemovePage(int IndexPage)	{	return true;	}

	virtual	void	EmitSignalCaptured(void);
signals:
	void	CameraHandleSignalCaptured();
};

#endif