#ifndef COPYBETWEENPHASEDIALOG_H
#define COPYBETWEENPHASEDIALOG_H

#include <QDialog>
#include "XAlgorithmLibrary.h"
#include "XDataAlgorithm.h"
#include "XServiceForLayers.h"

namespace Ui {
class CopyBetweenPhaseDialog;
}

class CopyBetweenPhaseDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	int32	SourcePhase;
	int32	DestinationPhase;
	bool	ModeCopyMasterImage;
	bool	ModeCopyTargetImage;
	bool	ModeCopyAlgorithm;

    explicit CopyBetweenPhaseDialog(const QString &AlgoRoot , const QString &AlgoName 
									,int32	SourcePhase
									,int32	DestinationPhase
									,bool	ModeCopyMasterImage
									,bool	ModeCopyTargetImage
									,bool	ModeCopyAlgorithm
									, LayersBase *base ,QWidget *parent = 0);
    ~CopyBetweenPhaseDialog();

private slots:
    void on_pushButtonCopy_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CopyBetweenPhaseDialog *ui;
};

#endif // COPYBETWEENPHASEDIALOG_H
