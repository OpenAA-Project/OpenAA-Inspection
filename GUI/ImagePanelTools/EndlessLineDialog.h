#ifndef ENDLESSLINEDIALOG_H
#define ENDLESSLINEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
    class EndlessLineDialog;
}

class EndlessLineDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit EndlessLineDialog(LayersBase *base, QWidget *parent = 0);
    ~EndlessLineDialog();

	int		x,y;
	double	S;

private slots:
    void on_pushButtonOK_clicked();

    void on_pushButtonCancel_clicked();

private:
    Ui::EndlessLineDialog *ui;
};

#endif // ENDLESSLINEDIALOG_H
