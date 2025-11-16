#pragma once

#include "rwdev3dmouse_global.h"
#include "XRWDevice.h"

class RWDev3DMouseForm;

class RWDev3DMouse : public RWDeviceBaseClass
{
	RWDev3DMouseForm	*Form;
public:
    RWDev3DMouse(LayersBase *base ,const QString &Parameter ,QWidget *parent);
	~RWDev3DMouse(void);

	virtual	void	Prepare(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	void	LoopOnIdle(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSettingDialog(QWidget *parent);
};
