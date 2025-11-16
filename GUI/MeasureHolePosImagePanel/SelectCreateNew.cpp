#include "MeasureHolePosImagePanelResource.h"
#include "SelectCreateNew.h"

SelectCreateNew::SelectCreateNew(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SelectCreateNew::~SelectCreateNew()
{

}


void SelectCreateNew::on_pushButtonCreateNew_clicked()
{
	done(1);
}

void SelectCreateNew::on_pushButtonGetColorMap_clicked()
{
	done(2);
}