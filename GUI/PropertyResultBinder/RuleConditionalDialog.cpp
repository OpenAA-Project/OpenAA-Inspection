#include "PropertyResultBinderFormResource.h"
#include "RuleConditionalDialog.h"
#include "ui_RuleConditionalDialog.h"
#include "XGeneralFunc.h"

RuleConditionalDialog::RuleConditionalDialog(LayersBase *base, int _InputNumb ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::RuleConditionalDialog)
{
    ui->setupUi(this);
	InputNumb=_InputNumb;

	ui->tableWidget	->setColumnWidth(0,40);
	ui->tableWidget	->setColumnWidth(1,70);
	ui->tableWidget	->setColumnWidth(2,80);
	ui->tableWidget	->setColumnWidth(3,100);

	InstallOperationLog(this);
}

RuleConditionalDialog::~RuleConditionalDialog()
{
    delete ui;
}

void RuleConditionalDialog::ShowConditionList(void)
{
	int	CondCount=ConditionData.GetCount();
	ui->listWidgetCondition->clear();
	for(int i=0;i<CondCount;i++){
		ui->listWidgetCondition->addItem(LangSolver.GetString(RuleConditionalDialog_LS,LID_4)/*"Condition "*/+QString::number(i));
	}
}

void	RuleConditionalDialog::Initial(ChildOfRuleOperationConditional *rule ,int InputNumb)
{
	ConditionData=rule->ConditionData;

	ShowConditionList();
	ui->checkBoxNGOthers	->setChecked(rule->NGOthers);

	ui->tableWidget->setRowCount(InputNumb);
	for(int i=0;i<InputNumb;i++){
		QTableWidgetItem	*d1=new QTableWidgetItem();
		d1->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsUserCheckable);
		d1->setCheckState(Qt::Unchecked);
		ui->tableWidget->setItem(i,1,d1);

		QTableWidgetItem	*d2=new QTableWidgetItem();
		d2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
		ui->tableWidget->setItem(i,2,d2);

		::SetDataToTable(ui->tableWidget,0,i ,QString::number(i));
	}

	ui->lineEditName	->setText(rule->Name);
	ui->lineEditRemark	->setText(rule->Remark);
	ui->checkBoxConclusion	->setChecked(rule->Conclusion);
}

void RuleConditionalDialog::on_pushButtonInsertNew_clicked()
{
	ConditionList	*CL=new ConditionList();
	int	InpNumb=ui->tableWidget->rowCount();
	for(int i=0;i<InpNumb;i++){
		QTableWidgetItem	*d1=ui->tableWidget->item(i,1);
		ConditionList::InputList	*c=new ConditionList::InputList();
		c->OK=(d1->checkState ()==Qt::Checked)?true:false;
		c->ErrorCode	=GetDataToTable(ui->tableWidget ,2,i).toInt();

		QString	CondStr	=GetDataToTable(ui->tableWidget ,3,i);
		c->ErrorCondition	=GetCondition(CondStr);

		CL->InputData.AppendList(c);
	}
	CL->OutputOK=(ui->comboBoxOutputOK	->currentIndex()==0)?true:false;
	CL->OutputErrorCode	=ui->spinBoxOutputErrorCode->value();
	ConditionData.AppendList(CL);

	ShowConditionList();
}

int	RuleConditionalDialog::GetCondition(const QString &CondStr)
{
	int	Ret=0;
			
	bool	ok;
	int	Condition	=CondStr.toInt(&ok);
	if(ok==true){
		Ret=Condition;
	}
	else{
		if(CondStr.toUpper()==LangSolver.GetString(RuleConditionalDialog_LS,LID_5)/*"IGNORE"*/)
			Ret=0;
		else if(CondStr.toUpper()==LangSolver.GetString(RuleConditionalDialog_LS,LID_6)/*"EQUAL"*/)
			Ret=1;
		else if(CondStr.toUpper()==LangSolver.GetString(RuleConditionalDialog_LS,LID_7)/*"LARGER"*/)
			Ret=2;
		else if(CondStr.toUpper()==LangSolver.GetString(RuleConditionalDialog_LS,LID_8)/*"SMALLER"*/)
			Ret=3;
	}
	return Ret;
}


void RuleConditionalDialog::on_pushButtonModify_clicked()
{
	int	R=ui->listWidgetCondition->currentRow();
	if(R<0)
		return;
	ConditionList	*CL=ConditionData[R];
	if(CL!=NULL){
		CL->InputData.RemoveAll();
		int	InpNumb=ui->tableWidget->rowCount();
		for(int i=0;i<InpNumb;i++){
			QTableWidgetItem	*d1=ui->tableWidget->item(i,1);
			ConditionList::InputList	*c=new ConditionList::InputList();
			c->OK=(d1->checkState ()==Qt::Checked)?true:false;
			bool	ok;
			c->ErrorCode	=GetDataToTable(ui->tableWidget ,2,i).toInt(&ok);

			QString	CondStr	=GetDataToTable(ui->tableWidget ,3,i);
			c->ErrorCondition	=GetCondition(CondStr);

			CL->InputData.AppendList(c);
		}
	}
}

void RuleConditionalDialog::on_pushButtonDelete_clicked()
{
	int	R=ui->listWidgetCondition->currentRow();
	if(R<0)
		return;
	ConditionList	*CL=ConditionData[R];
	if(CL!=NULL){
		ConditionData.RemoveList(CL);
		delete	CL;
		ShowConditionList();
	}
}

void RuleConditionalDialog::on_pushButtonOK_clicked()
{
	RuleName	=ui->lineEditName	->text();
	RuleRemark	=ui->lineEditRemark	->text();
	Conclusion	=ui->checkBoxConclusion	->isChecked();
	NGOthers	=ui->checkBoxNGOthers	->isChecked();

	done(true);
}

void RuleConditionalDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void RuleConditionalDialog::on_listWidgetCondition_currentRowChanged(int currentRow)
{
	int	R=ui->listWidgetCondition->currentRow();
	if(R<0)
		return;
	ConditionList	*CL=ConditionData[R];
	if(CL!=NULL){
		ui->tableWidget->setRowCount(InputNumb);
		for(int i=0;i<InputNumb;i++){
			ConditionList::InputList	*c=CL->InputData[i];
			if(c!=NULL){
				QTableWidgetItem	*d1=ui->tableWidget->item(i,1);
				d1->setCheckState(c->OK==true?Qt::Checked:Qt::Unchecked);
				::SetDataToTable(ui->tableWidget,2,i ,QString::number(c->ErrorCode));
				QTableWidgetItem	*d2=ui->tableWidget->item(i,2);
				d2->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);

				if(c->ErrorCondition==0)
					::SetDataToTable(ui->tableWidget,3,i ,LangSolver.GetString(RuleConditionalDialog_LS,LID_9)/*"Ignore"*/,Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
				else if(c->ErrorCondition==1)
					::SetDataToTable(ui->tableWidget,3,i ,LangSolver.GetString(RuleConditionalDialog_LS,LID_10)/*"Equal"*/,Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
				else if(c->ErrorCondition==2)
					::SetDataToTable(ui->tableWidget,3,i ,LangSolver.GetString(RuleConditionalDialog_LS,LID_11)/*"Larger"*/,Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
				else if(c->ErrorCondition==3)
					::SetDataToTable(ui->tableWidget,3,i ,LangSolver.GetString(RuleConditionalDialog_LS,LID_12)/*"Smaller"*/,Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
			}
		}
	}
}
