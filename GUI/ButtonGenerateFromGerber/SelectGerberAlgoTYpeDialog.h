#ifndef SELECTGERBERALGOTYPEDIALOG_H
#define SELECTGERBERALGOTYPEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SelectGerberAlgoTYpeDialog;
}

class SelectGerberAlgoTYpeDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectGerberAlgoTYpeDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectGerberAlgoTYpeDialog();

	int	GerberAlgoType;

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectGerberAlgoTYpeDialog *ui;
};

#endif // SELECTGERBERALGOTYPEDIALOG_H
