/*
 * Copyright (C) 2025
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */



#ifndef XExecuteInspectH
#define XExecuteInspectH

#include <QThread>
#include <QReadWriteLock>
#include "XExecuteInspectBase.h"
#include "XCameraClass.h"

class	SeqControlParam;
class	CmdInspectionReplied;
class	CmdInspectionRepliedBuffered;
class	GUIExecuteCmdStartInspect;
class	GUIExecuteCmdReplyInspect;
class	GUIExecuteCmdCancelCapture;
class	CmdCaptureBegins;
class	GUIFormBase;
class	CmdCapturedOnly;
class	ExecuteInspect;
class	CmdCheckReply;

class ExecuteInspect : public ExecuteInspectBase
{
	Q_OBJECT
		char	*DefaultCameraFileName;

	CmdInspectionReplied	*PacketReplied;
	CmdCapturedOnly			*CapturedReplied;
	CmdCaptureBegins		*CaptureBeginsReplied;
	CmdCheckReply			*CmdCheckReplied;

	GUIExecuteCmdStartInspect	**GUIExecuteCmdStartInspectPoint;
	GUIExecuteCmdReplyInspect	**GUIExecuteCmdReplyInspectPoint;
	GUIExecuteCmdCancelCapture	**GUIExecuteCmdCancelCapturePoint;
	int		AllocatedPage;

	PageAndLayerFlagListContainer	CurrentCapturedPageLayer;
	QMutex				ChangingCameraInfo;
public:
	bool		TriggeredCapture;
	int			StackedCountInAutoMode;
	ResultInspection	*ResultInspectionToAccessInSlotAutomodeStart;
public:
	ExecuteInspect(QObject *parent ,EntryPointBase *_EntryPoint ,SeqControlParam *SeqParam);
	~ExecuteInspect(void);

	virtual	void	Initial(void);
	virtual	void	Release(void);
	virtual	void	CamRelease(void);

	virtual	bool	InitialCamera(int32 &ErrorCode)	override;
	virtual	bool	ChangeCameraInfo(CameraReqInfoAnyData *anydata=NULL)	override;
	virtual	bool	CheckCameraDLL(void)			override;
	virtual	bool	LoadDefault(void)				override;
	virtual	bool	LoadDefaultOldVer(void);
	virtual	bool	SaveDefault(void)				override;
	virtual	bool	Load(QIODevice *file)			override;
	virtual	bool	Save(QIODevice *file)			override;
	virtual	bool	IsLocalCamera(void)				override;

	virtual	int		GetAllocatedCameraCount(void)		override;
	virtual	CameraClass		*GetCamera(int n)			override;
	virtual	int		GetCameraDim(CameraClass *CamDim[])	override;
	virtual	void	SetCameraDim(CameraClass *CamDim[])	override;

	//�������͊O�������̑���
	virtual	void	GoInspect(void)					override;
	virtual	void	GoInspectWithoutCapture(void)	override;
	virtual	void	GoMasterCaptureOnly(void)		override;
	virtual	void	GoTargetCaptureOnly(void)		override;
	virtual	void	GoGray(void)					override;
	virtual	void	CamShowSetting(int CamNo)		override;
	virtual	bool	LoadCameraSetting(QIODevice *f)	override;
	virtual	void	ChangeLot(void)					override;
	virtual	void	ClearCameraBuffer(void)			override;

	bool	CapturePrepare(void);
	bool	CaptureStart(void);
	bool	CaptureHalt(void);

	int		GetCameraCount(void);
	static	ExecuteInspect	*StaticInstance		;
	volatile	bool	GoSlotAutomodeStart;
	void	EmitCalcDone(int32 nStrategicNumber);

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)	override;
	void	SetScanInfo(int ScanNumber ,bool ScanMastered);
	virtual	bool	Reallocate(int newPhaseNumb , int newPageNumb ,int newLayerNumb)	override;
protected:
	virtual	void run()	override;

	CameraClass				**Cam;
	int						AllocatedCamNumb;

	
	int32		CameraErrorCode;
	bool		StatusCameraHalt;

public:
	SeqControlParam *SeqParam;
private:

	bool	CheckCamera(int32 &ErrorCode);
	int		CaptureGetState(void);
		//�S�ẴJ�����̃r�b�g�n�q
		//	�߂��l�F	�r�b�g�O	�P�F�B�e������
		//				�r�b�g�P	�P�F�g���K�[�ҋ@��
		//				�r�b�g�Q	�P�F�c�l�`�]����
		//				�r�b�g�R	�P�F�I�[�o�[�����G���[����
		//				�r�b�g�S	�P�F���̑��G���[����
	bool	CaptureGetMasterImage(int CStrategic,ListPhasePageLayerPack &CapturedList);
	bool	CaptureGetTargetImage(ListPhasePageLayerPack &CapturedList);
	void	OccurCamError(int CamStatus);
	void	ExecuteHalt(void);
	void				TestMP(void);
	QString	MakeCamDefaultName(void);
	void	SetCaptured(int CStrategic);

signals:
    void	SignalFinishCalc(ResultInspection *Res,int localPage,int CurrentStrategic);
    void	SignalFinishCaptureOnly(ResultInspection *Res,int localPage ,int CurrentStrategic,int motionMode);
	void	SignalAutomodeStart();
	void	SignalCaptureHalt();
	void	SignalCaptureStart();
	void	SignalCheckCycle(int nStrategicNumber);

private slots:
	void	FinishCalcFunc(ResultInspection *Res,int localPage,int CurrentStrategic);
	void	FinishCaptureOnlyFunc(ResultInspection *Res,int localPage ,int CurrentStrategic,int motionMode);
	void	SlotCaptureHalt();
	void	SlotCaptured(int CStrategic);
	void	SlotCaptureStart();
	void	SlotCheckCycle(int nStrategicNumber);
public slots:
	void	Exit(GUIFormBase *);
	void	SlotAutomodeStart();
};

//CameraClass		*ExecuteInspect::GetCamera(int n)	{	return Cam[n];	}


class	CmdInspectionRepliedBase : public GUICmdPacketBase
{
public:
	enum	__Result
	{
		_OK			=1
		,_NG		=2
		,_Nothing	=3
	}Result;
	int64		NGCounts;
	int32		NGImageCount;
	bool		TimeOutBreak;
	bool		MaxErrorBreak;
	bool		CountUpID;
	int32		ExecuterID;
	int32		StrategicNumber;

	CmdInspectionRepliedBase(const QString &ClassName ,LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdInspectionReplied : public CmdInspectionRepliedBase
{
public:

	CmdInspectionReplied(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
};
class	CmdInspectionRepliedBuffered : public CmdInspectionRepliedBase
{
public:

	CmdInspectionRepliedBuffered(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
};

class	CmdCapturedOnly : public GUICmdPacketBase
{
public:

	CmdCapturedOnly(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdCheckReply : public GUICmdPacketBase
{
public:
	int	StrategicNumber;
	CmdCheckReply(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdCaptureBegins : public GUICmdPacketBase
{
public:

	CmdCaptureBegins(LayersBase *base,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);
	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}
	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

/*
	�摜�ǂݍ��݁������̗���

	�J�����B�荞�ݏ���
	����������
	�J�����B�e�J�n

	�J�����B�����Ԏ擾
	�J�����B��������
	�@�����J�n
	�������ʏo��

*/


//==============================================================
class	GUIExecuteCmdStartInspect : public GUICmdPacketBase
{
public:
	XDateTime	StartInspectionTime;
	int64		CurrentInspectID;
	int32		StrategicNumber;

	GUIExecuteCmdStartInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUIExecuteCmdStartInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUIExecuteCmdReplyInspect : public GUICmdPacketBase
{
public:

	GUIExecuteCmdReplyInspect(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUIExecuteCmdReplyInspect(void);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	GUIExecuteCmdCancelCapture : public GUICmdPacketBase
{
public:

	GUIExecuteCmdCancelCapture(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);
	~GUIExecuteCmdCancelCapture(void);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);
};


#endif