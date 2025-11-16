#pragma once

#include "rwdevyrc1000_global.h"
#include "XRWDevice.h"

class RWDevYRC1000 : public RWDeviceBaseClass
{
public:
    RWDevYRC1000(LayersBase *base ,const QString &Parameter ,QWidget *parent);
	~RWDevYRC1000(void);

	virtual	void	Prepare(void);

	virtual	void	TransmitDirectly(GUIDirectMessage *packet);
	virtual	void	LoopOnIdle(void);

	virtual	bool	Save(QIODevice *f);
	virtual	bool	Load(QIODevice *f);

	virtual	bool	ShowSettingDialog(QWidget *parent);
};
