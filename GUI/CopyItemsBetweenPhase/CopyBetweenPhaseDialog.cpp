#include "CopyBetweenPhaseDialogResource.h"
#include "CopyBetweenPhaseDialog.h"
#include "ui_CopyBetweenPhaseDialog.h"

CopyBetweenPhaseDialog::CopyBetweenPhaseDialog(const QString &AlgoRoot , const QString &AlgoName 
											,int32	iSourcePhase
											,int32	iDestinationPhase
											,bool	iModeCopyMasterImage
											,bool	iModeCopyTargetImage
											,bool	iModeCopyAlgorithm
											, LayersBase *base ,QWidget *parent) :
    QDialog(parent)
	,ServiceForLayers(base)
    ,ui(new Ui::CopyBetweenPhaseDialog)
{
    ui->setupUi(this);
	SourcePhase				=iSourcePhase;
	DestinationPhase		=iDestinationPhase;
	ModeCopyMasterImage		=iModeCopyMasterImage;
	ModeCopyTargetImage		=iModeCopyTargetImage;
	ModeCopyAlgorithm		=iModeCopyAlgorithm;

	ui->checkBoxMaster		->setChecked(ModeCopyMasterImage);
	ui->checkBoxTarget		->setChecked(ModeCopyTargetImage);
	ui->checkBoxAlgorithm	->setChecked(ModeCopyAlgorithm);
	for(int phase=0;phase<GetPhaseNumb();phase++){
		ui->listWidgetSourcePhase->addItem(GetLayersBase()->GetParamGlobal()->GetPhaseString(phase));
		ui->listWidgetDestPhase	 ->addItem(GetLayersBase()->GetParamGlobal()->GetPhaseString(phase));
	}
	InstallOperationLog(this);
}

CopyBetweenPhaseDialog::~CopyBetweenPhaseDialog()
{
    delete ui;
}

void CopyBetweenPhaseDialog::on_pushButtonCopy_clicked()
{
	SourcePhase			=ui->listWidgetSourcePhase->currentRow();
	DestinationPhase	=ui->listWidgetDestPhase->currentRow();

	ModeCopyMasterImage	=ui->checkBoxMaster		->isChecked();
	ModeCopyTargetImage	=ui->checkBoxTarget		->isChecked();
	ModeCopyAlgorithm	=ui->checkBoxAlgorithm	->isChecked();
	done(true);
}

void CopyBetweenPhaseDialog::on_pushButtonCancel_clicked()
{
	done(false);
}
