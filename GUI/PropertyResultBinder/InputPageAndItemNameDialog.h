#ifndef INPUTPAGEANDITEMNAMEDIALOG_H
#define INPUTPAGEANDITEMNAMEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class InputPageAndItemNameDialog;
}

class InputPageAndItemNameDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit InputPageAndItemNameDialog(LayersBase *Base ,QWidget *parent = 0);
    ~InputPageAndItemNameDialog();

	int		Page;
	QString	ItemName;

	void	Initial(const QString &ItemName);

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputPageAndItemNameDialog *ui;
};

#endif // INPUTPAGEANDITEMNAMEDIALOG_H
