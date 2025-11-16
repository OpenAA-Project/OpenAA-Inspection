#include "ButtonCopyLibraryResource.h"
#include "InputNameForm.h"

InputNameForm::InputNameForm(LayersBase *base, const QString &_DefaultName ,QWidget *parent)
	: QDialog(parent),ServiceForLayers(base)
{
	ui.setupUi(this);
	ui.lineEditLibName->setText(_DefaultName);
	InstallOperationLog(this);
}

InputNameForm::~InputNameForm()
{

}

void InputNameForm::on_pushButtonOK_clicked()
{
	LibName=ui.lineEditLibName->text();
	done(true);
}

void InputNameForm::on_pushButtonCancel_clicked()
{
	done(false);
}