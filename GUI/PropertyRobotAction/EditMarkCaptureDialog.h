#ifndef EDITMARKCAPTUREDIALOG_H
#define EDITMARKCAPTUREDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class EditMarkCaptureDialog;
}
class ActionMarkBase;

class EditMarkCaptureDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EditMarkCaptureDialog(LayersBase *base,QWidget *parent = nullptr);
    ~EditMarkCaptureDialog();

    void    Initial(ActionMarkBase *src);

	int32	AlgorithmType	;
	int32	AlgorithmPhase	;
	int32	AlgorithmPage	;
	int32	AlgorithmLayer	;
	int32	AlgorithmItemID	;	
    float	StopMilisec;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::EditMarkCaptureDialog *ui;
};

#endif // EDITMARKCAPTUREDIALOG_H
