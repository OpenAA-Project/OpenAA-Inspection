

#ifndef XExecuteIntegratePlayerH
#define XExecuteIntegratePlayerH

#include <QThread>
#include <QReadWriteLock>
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"

class	GUIFormBase;
class	IntegratePlayer;


class ExecuteIntegratePlayer : public ExecuteInspectBase
{
	Q_OBJECT
		char	*DefaultCameraFileName;

	PageAndLayerFlagListContainer	CurrentCapturedPageLayer;
	QMutex				ChangingCameraInfo;

	ExecuteInspectState		CurrentState;
	IntegratePlayer			*Parent;
	int						UnitNo;

public:
	ExecuteIntegratePlayer(IntegratePlayer *p, EntryPointBase *_EntryPoint ,int UnitNo);
	~ExecuteIntegratePlayer(void);

	virtual	void	Initial(void);
	virtual	void	Release(void);

	virtual	ExecuteInspectState	GetState(void)	{	return CurrentState;	}
	virtual	MotionMode			GetMode(void)	{	return _CaptureInspect;	}

	virtual	bool	IsLocalCamera(void)	{	return true;	}
	virtual	bool	LoadDefault(void)	{	return true;	}
	virtual	bool	SaveDefault(void)	{	return true;	}
	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	CameraClass		*GetCamera(int n)	{	return NULL;	}
	virtual	void	CamShowSetting(int CamNo)	{}
	virtual	bool	LoadCameraSetting(const QString &CamFileName){	return NULL;	}

	void	SetScanInfo(int ScanNumber ,bool ScanMastered);
protected:
	void run();

	QReadWriteLock			MutexStateMode;


	virtual	void	GoInspect(void)					{}
	virtual	void	GoInspectWithoutCapture(void)	{}
	virtual	void	GoMasterCaptureOnly(void)		{}
	virtual	void	GoTargetCaptureOnly(void)		{}
	virtual	void	GoGray(void)					{}
private:

signals:
	void	SignalOK();
	void	SignalNG();
private slots:

public slots:
	void	Exit(GUIFormBase *);
};

#endif
