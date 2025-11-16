#include "RWDev3DMouse.h"
#include "RWDev3DMouseForm.h"

RWDev3DMouse::RWDev3DMouse(LayersBase *base ,const QString &Parameter ,QWidget *parent)
	:RWDeviceBaseClass(base,parent)
{
	Form=nullptr;
}
RWDev3DMouse::~RWDev3DMouse(void)
{
	if(Form!=NULL){
		Form->deleteLater();
		Form=NULL;
	}
}

void	RWDev3DMouse::Prepare(void)
{
}

void	RWDev3DMouse::TransmitDirectly(GUIDirectMessage *packet)
{
}
void	RWDev3DMouse::LoopOnIdle(void)
{
}

bool	RWDev3DMouse::Save(QIODevice *f)
{
	return true;
}
bool	RWDev3DMouse::Load(QIODevice *f)
{
	return true;
}

bool	RWDev3DMouse::ShowSettingDialog(QWidget *parent)
{
	if(Form==NULL){
		Form=new RWDev3DMouseForm(this);
	}
	Form->show();
	return true;
}