#include "ListResultFrameForm.h"
#include "ui_ListResultFrameForm.h"

ListResultFrameForm::ListResultFrameForm(LayersBase *base ,QWidget *parent) :
    GUIFormBase(base,parent),
    ui(new Ui::ListResultFrameForm)
{
    ui->setupUi(this);
}

ListResultFrameForm::~ListResultFrameForm()
{
    delete ui;
}


void	ListResultFrameForm::Prepare(void)
{
	ResizeAction();
}

void	ListResultFrameForm::ResizeAction()
{
	ui->tableWidget->resize(width(),height());
}
