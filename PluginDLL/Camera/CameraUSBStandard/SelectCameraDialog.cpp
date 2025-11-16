#include "SelectCameraDialog.h"
#include "ui_SelectCameraDialog.h"
#include "XGeneralFunc.h"
#include "XDataInLayer.h"
#include "XGUIFormBase.h"
#include <QApplication>


SelectCameraDialog::SelectCameraDialog(int _VendoredProductIDList[] ,int _CountOfCam, LayersBase *base,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::SelectCameraDialog)
{
    ui->setupUi(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::WindowTitleHint | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint | Qt::WindowSystemMenuHint);

	QIcon	Icon=qApp->windowIcon();
	setWindowIcon(Icon);
	QString	Str=qApp->objectName();	//GetLayersBase()->GetMainWidget()->windowTitle();
	setWindowTitle(Str);

	ui->listWidgetCameraList->clear();
	CountOfCam=_CountOfCam;
	for(int i=0;i<CountOfCam;i++){
		VendoredProductIDList[i]=_VendoredProductIDList[i];
		if(VendoredProductIDList[i]==0x1601)
			ui->listWidgetCameraList->addItem(/**/"L-836");
		if(VendoredProductIDList[i]==0xa007)
			ui->listWidgetCameraList->addItem(/**/"L-835");
	}
	ui->listWidgetCameraList->setCurrentRow(0);

	SelectedNo=0;
}

SelectCameraDialog::~SelectCameraDialog()
{
    delete ui;
}

void SelectCameraDialog::on_listWidgetCameraList_doubleClicked(const QModelIndex &index)
{
	SelectedNo=ui->listWidgetCameraList->currentRow();
	done(true);
}

void SelectCameraDialog::on_pushButtonSelect_clicked()
{
	SelectedNo=ui->listWidgetCameraList->currentRow();
	done(true);
}
