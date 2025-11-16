#if	!defined(_XExecuteInspectForReview)
#define	_XExecuteInspectForReview

#include "XExecuteInspectBase.h"

class ExecuteInspectForReview : public ExecuteInspectBase
{

public:
	ExecuteInspectForReview(QObject *parent ,EntryPointBase *_EntryPointBaseData ,SeqLocalParam *_SeqParam)
		:ExecuteInspectBase(parent,_EntryPointBaseData ,_SeqParam){}
	virtual	~ExecuteInspectForReview(void){}

	virtual	bool	IsLocalCamera(void)			{	return false;	}
	virtual	ExecuteInspectBase::ExecuteInspectState	GetState(void)	{	return ExecuteInspectBase::_EI_IDLE;	}
	virtual	ExecuteInspectBase::MotionMode			GetMode(void)	{	return ExecuteInspectBase::_CaptureNone;	}
	virtual	bool	Load(QIODevice *f)	{	return true;		}
	virtual	bool	Save(QIODevice *f)	{	return true;		}
	virtual	bool	LoadDefault(void)	{	return true;		}
	virtual	bool	SaveDefault(void)	{	return true;		}
	
	virtual	CameraClass		*GetCamera(int n)	{	return NULL;	}

	//Ç±ÇÍÇÁÇÕäOïîÇ©ÇÁÇÃëÄçÏ
	virtual	void	GoInspect(void)				{}
	virtual	void	GoInspectWithoutCapture(void){}
	virtual	void	GoMasterCaptureOnly(void)	{}
	virtual	void	GoTargetCaptureOnly(void)	{}
	virtual	void	GoGray(void)				{}
	virtual	void	CamShowSetting(int CamNo)	{}
	virtual	bool	LoadCameraSetting(const QString &CamFileName)	{	return true;	}

	
protected:
};



#endif