#include "CreateNewRelation.h"

CreateNewRelation::CreateNewRelation(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

CreateNewRelation::~CreateNewRelation()
{

}


void CreateNewRelation::on_pushButtonOK_clicked()
{
	Name	=ui.EditName->text();
	Remark	=ui.EditRemark->text();
	RelationType	=ui.spinBoxRelationType->value();
	done(true);
}

void CreateNewRelation::on_pushButtonCancel_clicked()
{
	done(false);
}