#include "GeneralGroupResource.h"
#include "GeneralGroupSelfPasswordForm.h"

GeneralGroupSelfPasswordForm::GeneralGroupSelfPasswordForm(LayersBase *base, QWidget *parent, Qt::WindowFlags f)
	:QDialog(parent, f),ServiceForLayers(base)
{
	ui.setupUi(this);
	InstallOperationLog(this);
}

QString GeneralGroupSelfPasswordForm::password() const
{
	return ui.lePassword->text();
}
