#include "CartonMenuResource.h"
#include "ShowReqLotDialog.h"
#include "ui_ShowReqLotDialog.h"
#include "XGeneralFunc.h"
#include "IntegrationInputLotForm.h"
#include "XDataInLayer.h"


ShowReqLotDialog::ShowReqLotDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::ShowReqLotDialog)
{
    ui->setupUi(this);
	LangSolver.SetUI(this);
	SetWidgetCenter(this);
	setWindowFlags(Qt::Dialog | Qt::WindowTitleHint | Qt::WindowSystemMenuHint);

	IntegrationInputLotForm	*f=(IntegrationInputLotForm *)GetLayersBase()->FindByName(/**/"Integration",/**/"InputLot",/**/"");
	if(f!=NULL){
		QString	s	=QString(LangSolver.GetString(ShowReqLotDialog_LS,LID_9)/*"驛｢譎｢�ｽ�ｭ驛｢譎｢�ｿ�ｽ郢晢ｽｨ驍ｵ�ｺ�ｽ�ｮ"*/)
					+f->TitleLotID
					+QString(LangSolver.GetString(ShowReqLotDialog_LS,LID_10)/*"驍ｵ�ｲ�ｽ�ｽ*/)
					+f->TitleLotNumber
					+QString(LangSolver.GetString(ShowReqLotDialog_LS,LID_11)/*"驍ｵ�ｲ�ｽ�ｽ*/)
					+f->TitleSubCode
					+QString(LangSolver.GetString(ShowReqLotDialog_LS,LID_12)/*"驛｢�ｧ髮区ｩｸ�ｿ�ｽ髯ｷ迚呻ｽｸ蜻ｻ�ｼ�ｽ驍ｵ�ｺ�ｽ�ｦ鬨ｾ蜈ｷ�ｽ�ｻ鬯ｪ�ｭ�ｽ�ｲ驛｢譎�ｿｽ邵ｺ�｡驛｢譎｢�ｽ�ｳ驛｢�ｧ陷ｻ蝓滂ｽｬ�ｾ驍ｵ�ｺ陷会ｽｱ遯ｶ�ｻ驍ｵ�ｺ闕ｳ蟯ｩ蜻ｳ驍ｵ�ｺ髴郁ｲｻ�ｼ�ｽ*/);
		ui->label->setText(s);
	}
}

ShowReqLotDialog::~ShowReqLotDialog()
{
    delete ui;
}

void ShowReqLotDialog::on_PushButtonOK_clicked()
{
	close();
}
