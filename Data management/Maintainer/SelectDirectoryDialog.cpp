#include "SelectDirectoryDialog.h"
#include "ui_SelectDirectoryDialog.h"
#include <QStringList>

SelectDirectoryDialog::SelectDirectoryDialog(const QString &Path ,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDirectoryDialog)
{
    ui->setupUi(this);

	Model.setFilter(QDir::AllDirs | QDir::Files);

	QStringList	NameList;

	NameList.append(/**/"*");

	Model.setFilter(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Drives);
	Model.setNameFilters(NameList);
	Model.setNameFilterDisables(false);
	QModelIndex	Index=Model.setRootPath(Path);

	ui->treeView->setModel(&Model);
	ui->treeView->setRootIndex(Index);
	ui->treeView->resizeColumnToContents(1);
	ui->treeView->resizeColumnToContents(2);
}

SelectDirectoryDialog::~SelectDirectoryDialog()
{
    delete ui;
}

void SelectDirectoryDialog::on_pushButtonOK_clicked()
{
	Directory=ui->lineEditDirectory->text();
	done(true);
}

void SelectDirectoryDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

void SelectDirectoryDialog::on_treeView_clicked(const QModelIndex &index)
{
	QFileInfo	FInfo=Model.fileInfo(index);
	QString	path=FInfo.absoluteFilePath();
	ui->lineEditDirectory->setText(path);
}
