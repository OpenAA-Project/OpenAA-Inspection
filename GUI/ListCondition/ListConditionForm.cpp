#include "ListConditionResource.h"
#include "ListConditionForm.h"
#include "ui_ListConditionForm.h"
#include "XLightClass.h"
#include <QMessageBox>

ListConditionForm::ListConditionForm(LayersBase *Base ,QWidget *parent) :
    GUIFormBase(Base,parent),
    ui(new Ui::ListConditionForm)
{
    ui->setupUi(this);
}

ListConditionForm::~ListConditionForm()
{
    delete ui;
}

void	ListConditionForm::Prepare(void)
{
	ui->listWidgetConditions->clear();

	QDir	CD(GetLayersBase()->GetUserPath());
	QStringList nameFilters;
	nameFilters.append(/**/"*.cond");
	FileNames.clear();
	QFileInfoList	List=CD.entryInfoList ( nameFilters);
	for(int i=0;i<List.count();i++){
		ui->listWidgetConditions->addItem(List[i].baseName());
		FileNames.append(List[i].fileName());
	}
}

void ListConditionForm::on_pushButtonSave_clicked()
{
	QString	CName=ui->lineEditName->text();
	if(CName.isEmpty()==true)
		return;
	QString	FileName=CName+QString(/**/".cond");
	QFile	File(FileName);
	if(File.open(QIODevice::WriteOnly)==true){
		if(Save(&File)==false){
			QMessageBox::warning(NULL
								,LangSolver.GetString(ListConditionForm_LS,LID_0)/*"Error"*/
								,LangSolver.GetString(ListConditionForm_LS,LID_1)/*"Not saved"*/
								,QMessageBox::Ok);
		}
	}
	Prepare();
}

bool	ListConditionForm::Save(QIODevice *f)
{
	WORD	Ver=1;
	if(::Save(f,Ver)==false)
		return false;
	if(GetLayersBase()->GetLightBase()!=NULL){
		if(GetLayersBase()->GetLightBase()->Save(f)==false)
			return false;
	}
	return true;
}

bool	ListConditionForm::Load(QIODevice *f)
{
	WORD	Ver=1;
	if(::Load(f,Ver)==false)
		return false;
	if(GetLayersBase()->GetLightBase()!=NULL){
		if(GetLayersBase()->GetLightBase()->Load(f)==false)
			return false;
	}
	BroadcastBuildForShow();
	return true;
}

void ListConditionForm::on_pushButtonSelect_clicked()
{
	int	R=ui->listWidgetConditions->currentRow();
	if(R>=0){
		QString	FileName=FileNames[R];
		QFile	File(FileName);
		if(File.open(QIODevice::ReadOnly)==true){
			if(Load(&File)==false){
				QMessageBox::warning(NULL
									,LangSolver.GetString(ListConditionForm_LS,LID_2)/*"Error"*/
									,LangSolver.GetString(ListConditionForm_LS,LID_3)/*"Not loaded"*/
									,QMessageBox::Ok);
			}
		}
		else{
			QMessageBox::warning(NULL
								,LangSolver.GetString(ListConditionForm_LS,LID_4)/*"Error"*/
								,LangSolver.GetString(ListConditionForm_LS,LID_5)/*"Not opened"*/
								,QMessageBox::Ok);
		}
	}
}

void ListConditionForm::on_listWidgetConditions_doubleClicked(const QModelIndex &index)
{
	on_pushButtonSelect_clicked();
}

void ListConditionForm::on_pushButtonUpdate_clicked()
{
	int	R=ui->listWidgetConditions->currentRow();
	if(R>=0){
		QString	FileName=FileNames[R];
		QFile	File(FileName);
		if(File.open(QIODevice::WriteOnly)==true){
			if(Save(&File)==false){
				QMessageBox::warning(NULL
									,LangSolver.GetString(ListConditionForm_LS,LID_6)/*"Error"*/
									,LangSolver.GetString(ListConditionForm_LS,LID_7)/*"Not updated"*/
									,QMessageBox::Ok);
			}
		}
	}
}
