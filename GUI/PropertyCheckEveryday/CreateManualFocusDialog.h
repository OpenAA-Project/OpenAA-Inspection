#ifndef CREATEMANUALFOCUSDIALOG_H
#define CREATEMANUALFOCUSDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class CreateManualFocusDialog;
}

class CreateManualFocusDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit CreateManualFocusDialog(LayersBase *base, QWidget *parent = 0);
    ~CreateManualFocusDialog();
    
	QString	ItemName;
	double	FocusLow;
	void	Reflect(void);
private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CreateManualFocusDialog *ui;
};

#endif // CREATEMANUALFOCUSDIALOG_H
