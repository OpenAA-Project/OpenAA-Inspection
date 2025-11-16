#include "EditItemsDialog.h"
#include "ui_EditItemsDialog.h"
#include "XDotColorMatching.h"
#include "XGeneralFunc.h"
#include "XDisplayImagePacket.h"
#include "SubtractLibIDDialog.h"

EditItemsDialog::EditItemsDialog(LayersBase *Base ,QWidget *parent) :
    QDialog(parent),ServiceForLayers(Base),
    ui(new Ui::EditItemsDialog)
{
    ui->setupUi(this);

	AvailableMasterNo	=false;
	MasterNoOriginCode	=-1;
	AvailableSubBlock	=false;
}

EditItemsDialog::~EditItemsDialog()
{
    delete ui;
}
void    EditItemsDialog::SetItemInfo(int _MasterNoOriginCode
									,AlgorithmLibraryListContainer &SubLibBlock
									,int _ExpandToSubBlock)
{
	MasterNoOriginCode	=_MasterNoOriginCode;
	SubBlockList		=SubLibBlock;
	ExpandToSubBlock	=_ExpandToSubBlock;
	ui->EditExpandToSubBlock->setValue(ExpandToSubBlock);
}

void EditItemsDialog::on_pushButtonMasterNo_clicked()
{
    MasterNoOriginCode=GetLayersBase()->ShowSelectMasterNoOriginCodeDialog(MasterNoOriginCode);
	AvailableMasterNo=true;
}


void EditItemsDialog::on_pushButtonSubtractLibID_clicked()
{
	SubtractLibIDDialog	D(GetLayersBase());
	D.SetSelected(SubBlockList);
	if(D.exec()==true){
		SubBlockList	=D.SelectedList;
		AvailableSubBlock=true;
	}
}


void EditItemsDialog::on_pushButtonOK_clicked()
{
	ExpandToSubBlock=ui->EditExpandToSubBlock->value();
	done(true);
}


void EditItemsDialog::on_pushButtonCancel_clicked()
{
	done(false);
}

