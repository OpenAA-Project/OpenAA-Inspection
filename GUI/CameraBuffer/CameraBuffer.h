#ifndef CAMERABUFFER_H
#define CAMERABUFFER_H

#include "camerabuffer_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	SignalOperandBit;

class	CameraBuffer : public GUIFormBase
{
	Q_OBJECT

public:
	int32	SystemRegisterNo;

	CameraBuffer(LayersBase *Base ,QWidget *parent);
	~CameraBuffer(void);
	
	virtual void	Prepare(void)	override;

private:
	SignalOperandBit	*ioMode;
private slots:
	void	OperandLoaded();
};


class	SpecifiedBroadcasterReqCameraBuffer : public SpecifiedBroadcaster
{
public:
	int		Page;
	bool	Empty;
	SpecifiedBroadcasterReqCameraBuffer(void){}
};

//--------------------------------------------------------------------------

class	GUICmdReqCameraBuffer : public GUICmdPacketBase
{
public:

	GUICmdReqCameraBuffer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSendCameraBuffer : public GUICmdPacketBase
{
public:
	bool	Empty;

	GUICmdSendCameraBuffer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // CAMERABUFFER_H
