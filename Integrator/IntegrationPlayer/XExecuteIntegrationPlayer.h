

#ifndef XExecuteIntegrationPlayerH
#define XExecuteIntegrationPlayerH

#include <QThread>
#include <QReadWriteLock>
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"

class	GUIFormBase;
class	IntegrationPlayer;


class ExecuteIntegrationPlayer : public ExecuteInspectBase
{
	Q_OBJECT
		char	*DefaultCameraFileName;

	PageAndLayerFlagListContainer	CurrentCapturedPageLayer;
	QMutex				ChangingCameraInfo;

	ExecuteInspectState		CurrentState;
	IntegrationPlayer			*Parent;

public:
	ExecuteIntegrationPlayer(IntegrationPlayer *p, EntryPointBase *_EntryPoint);
	~ExecuteIntegrationPlayer(void);

	virtual	void	Initial(void);
	virtual	void	Release(void);

	virtual	ExecuteInspectState	GetState(void)	override{	return CurrentState;	}
	virtual	MotionMode			GetMode(void)	override{	return _CaptureInspect;	}

	virtual	bool	IsLocalCamera(void)		override	{	return true;	}
	virtual	bool	LoadDefault(void)		override	{	return true;	}
	virtual	bool	SaveDefault(void)		override	{	return true;	}
	virtual	bool	Load(QIODevice *file)	override	{	return true;	}
	virtual	bool	Save(QIODevice *file)	override	{	return true;	}
	virtual	CameraClass		*GetCamera(int n)	override{	return NULL;	}
	virtual	void	CamShowSetting(int CamNo)	override{}
	virtual	bool	LoadCameraSetting(const QString &CamFileName)override{	return NULL;	}

	void	SetScanInfo(int ScanNumber ,bool ScanMastered);

	static	ExecuteIntegrationPlayer	*StaticInstance;

protected:
	virtual	void run()	override;

	QReadWriteLock			MutexStateMode;


	virtual	void	GoInspect(void)					override{}
	virtual	void	GoInspectWithoutCapture(void)	override{}
	virtual	void	GoMasterCaptureOnly(void)		override{}
	virtual	void	GoTargetCaptureOnly(void)		override{}
	virtual	void	GoGray(void)					override{}
private:

signals:

private slots:

public slots:
	void	Exit(GUIFormBase *);
};

#endif
