#ifndef COPYIMAGEINPHASESDIALOG_H
#define COPYIMAGEINPHASESDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class CopyImageInPhasesDialog;
}

class CopyImageInPhasesDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit CopyImageInPhasesDialog(LayersBase *base,QWidget *parent = 0);
    ~CopyImageInPhasesDialog();
    
	int	SrcPhase;
	int	DstPhase;
	bool	FlagMaster;
	bool	FlagTarget;

private slots:
    void on_pushButtonCopy_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CopyImageInPhasesDialog *ui;
};

#endif // COPYIMAGEINPHASESDIALOG_H
