#ifndef INPUTTHRESHOLDDIALOG_H
#define INPUTTHRESHOLDDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputThresholdDialog;
}

class InputThresholdDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
	int	SearchDot;

    explicit InputThresholdDialog(LayersBase *Base ,QWidget *parent = 0);
    ~InputThresholdDialog();

	void	Initialize(int searchdot);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputThresholdDialog *ui;
};

#endif // INPUTTHRESHOLDDIALOG_H
