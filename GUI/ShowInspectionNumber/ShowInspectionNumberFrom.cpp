#include "ShowInspectionNumberResource.h"
#include "ShowInspectionNumberFrom.h"

ShowInspectionNumberFrom::ShowInspectionNumberFrom(LayersBase *Base ,QWidget *parent)
	: GUIFormBase(Base,parent)
{
	ui.setupUi(this);
	TitleMessage=/**/"検査番号";
}

ShowInspectionNumberFrom::~ShowInspectionNumberFrom()
{

}

void	ShowInspectionNumberFrom::Prepare(void)
{
	ui.label->setText(TitleMessage);
}

void	ShowInspectionNumberFrom::ShowInPlayer(int64 N)
{
	ui.lineEditInspectionNumber->setText(QString::number(GetLayersBase()->GetInspectionNumber()));
}
