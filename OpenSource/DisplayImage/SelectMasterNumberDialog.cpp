#include "DisplayImageResource.h"
#include "SelectMasterNumberDialog.h"
#include "XTypeDef.h"
#include "ui_SelectMasterNumberDialog.h"
#include "XParamGlobal.h"
#include "XDataInLayer.h"

SelectMasterNumberDialog::SelectMasterNumberDialog(LayersBase *base,QWidget *parent) :
    QDialog(parent),ServiceForLayers(base),
    ui(new Ui::SelectMasterNumberDialog)
{
    ui->setupUi(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
	LangDISolver.SetLanguage(GetLayersBase()->GetLanguagePackageData(),GetLayersBase()->GetLanguageCode());
    LangDISolver.SetUI(this);

	SelectedMasterNo=-1;

	for(int i=0;i<GetCountOnlyMasterBuff();i++){
		if(i<GetParamGlobal()->MasterBuffNames.count()
		&& GetParamGlobal()->MasterBuffNames[i].isEmpty()==false){
			ui->comboBox->addItem(QString::number(i) 
								+ QString(/**/" : ")
								+ GetParamGlobal()->MasterBuffNames[i]);
		}
		else{
			ui->comboBox->addItem(QString::number(i));
		}
	}
}

SelectMasterNumberDialog::~SelectMasterNumberDialog()
{
    delete ui;
}

void SelectMasterNumberDialog::on_pushButtonOK_clicked()
{
	SelectedMasterNo=ui->comboBox->currentIndex();
	done(true);
}

void SelectMasterNumberDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
