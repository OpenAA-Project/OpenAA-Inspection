#include "AddRouteDialog.h"
#include "ui_AddRouteDialog.h"
#include <QFileDialog>

AddRouteDialog::AddRouteDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddRouteDialog)
{
    ui->setupUi(this);
}

AddRouteDialog::~AddRouteDialog()
{
    delete ui;
}
void	AddRouteDialog::Initial(PathClass &d)
{
	Path	=d.Path;
	Priority=d.Priority;
	ui->lineEditPath		->setText(d.Path);
	ui->spinBoxPriority		->setValue(d.Priority);
	ui->lineEditNetworkPath	->setText(d.NetworkPath);
	ui->lineEditDFSFilterDLLFileName	->setText(d.DFSFilterDLLFileName);
	ui->lineEditDFSFilterParameter		->setText(d.DFSFilterParameter);
}

void AddRouteDialog::on_pushButtonAdd_clicked()
{
	Path				=ui->lineEditPath					->text();
	Priority			=ui->spinBoxPriority				->value();
	NetworkPath			=ui->lineEditNetworkPath			->text();
	DFSFilterDLLFileName=ui->lineEditDFSFilterDLLFileName	->text();
	DFSFilterParameter	=ui->lineEditDFSFilterParameter		->text();

	done(true);
}

void AddRouteDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void AddRouteDialog::on_pushButtonSearchDLL_clicked()
{
	QString	DLLFileName=QFileDialog::getOpenFileName ( NULL
													, QString("Search DFSFilterDLL")
													, QString()
													, QString("DLL(*.DLL);;All files(*.*)"));
	if(DLLFileName.isEmpty()==false){
		QString	RelativeFileName=QDir::current ().relativeFilePath(DLLFileName);
		ui->lineEditDFSFilterDLLFileName	->setText(RelativeFileName);
	}
}
