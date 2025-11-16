#ifndef INPUTFRAMEDIALOG_H
#define INPUTFRAMEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputFrameDialog;
}

class InputFrameDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	bool	EditMode;
public:
    explicit InputFrameDialog(bool EditMode ,LayersBase *Base ,QWidget *parent = 0);
    ~InputFrameDialog();

	void	Initial(int groupNumber ,int frameNumber ,bool origin);

	int		GroupNumber;
	int		FrameNumber;
	bool	Origin;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

    void on_spinBoxGroupNumber_valueChanged(int arg1);

private:
    Ui::InputFrameDialog *ui;
};

#endif // INPUTFRAMEDIALOG_H
