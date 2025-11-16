#pragma once

#include <QtGui>
#include <QLibrary>
#include <QString>
#include <QIODevice>
#include "XServiceForLayers.h"
#include "XTypeDef.h"
#include "XDLLType.h"
#include "NList.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	LayersBase;
class	GUIDirectMessage;


class	RWDeviceBaseClass : public QWidget 
							,public IdentifiedClass
							,public ServiceForLayers
{
	Q_OBJECT

	int		DeviceID;
public:
	RWDeviceBaseClass(LayersBase *base,QWidget *parent);
	virtual	~RWDeviceBaseClass(void){}

	virtual	void	Prepare(void)					{}

	void	SetDeviceID(int d);
	int		GetDeviceID(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet){}
	virtual	void	LoopOnIdle(void){}

	virtual	bool	Save(QIODevice *f)						=0;
	virtual	bool	Load(QIODevice *f)						=0;

	virtual	bool	ShowSettingDialog(QWidget *parent)		=0;
};
