#include "CommonGUIDLLResource.h"
#include "SelectFontDialog.h"
#include "ui_SelectFontDialog.h"

SelectFontDialog::SelectFontDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectFontDialog)
{
    ui->setupUi(this);
}
SelectFontDialog::SelectFontDialog(const QFont & initial, QWidget *parent)
 :
    QDialog(parent),
    ui(new Ui::SelectFontDialog)
{
    ui->setupUi(this);
	CurrentFont=initial;
}

SelectFontDialog::~SelectFontDialog()
{
    delete ui;
}

void SelectFontDialog::on_listWidgetFont_currentRowChanged(int currentRow)
{

}

void SelectFontDialog::on_listWidgetStyle_currentRowChanged(int currentRow)
{

}

void SelectFontDialog::on_listWidgetSize_currentRowChanged(int currentRow)
{

}

void SelectFontDialog::on_pushButtonOK_clicked()
{

}

void SelectFontDialog::on_pushButtonCancel_clicked()
{

}

void SelectFontDialog::showEvent ( QShowEvent * event )
{

}

QFont	SelectFontDialog::currentFont()const
{
	return CurrentFont;
}
QFont	SelectFontDialog::selectedFont()const
{
	return CurrentFont;
}
void	SelectFontDialog::setCurrentFont(const QFont & initial)
{
	CurrentFont=initial;
	showEvent(NULL);
}
