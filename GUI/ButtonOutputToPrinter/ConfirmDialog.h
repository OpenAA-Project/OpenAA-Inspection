#ifndef CONFIRMDIALOG_H
#define CONFIRMDIALOG_H

#include <QDialog>
#include "XDateTime.h"
#include <QByteArray>
#include <QBuffer>
#include "XIntClass.h"
#include "XServiceForLayers.h"
#include "XPrinterManager.h"

namespace Ui {
class ConfirmDialog;
}
class	ButtonOutputToPrinter;

class ConfirmDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	ButtonOutputToPrinter	*Parent;

public:
    explicit ConfirmDialog(ButtonOutputToPrinter *p ,PrinterClass *PC ,LayersBase *pbase ,QWidget *parent = 0);
    ~ConfirmDialog();

private slots:
    void on_pushButtonClose_clicked();

private:
    Ui::ConfirmDialog *ui;
};

#endif // CONFIRMDIALOG_H
