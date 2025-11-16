#include "RWDevYRC1000.h"
#include "SettingDialog.h"

RWDevYRC1000::RWDevYRC1000(LayersBase *base ,const QString &Parameter ,QWidget *parent)
	:RWDeviceBaseClass(base,parent)
{
}
RWDevYRC1000::~RWDevYRC1000(void)
{
}

void	RWDevYRC1000::Prepare(void)
{
}

void	RWDevYRC1000::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	RWDevYRC1000::LoopOnIdle(void)
{
}

bool	RWDevYRC1000::Save(QIODevice *f)
{
	return true;
}
bool	RWDevYRC1000::Load(QIODevice *f)
{
	return true;
}

bool	RWDevYRC1000::ShowSettingDialog(QWidget *parent)
{
	SettingDialog	D(GetLayersBase(),this);
	D.exec();
	return true;
}