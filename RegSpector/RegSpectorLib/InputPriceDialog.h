#ifndef INPUTPRICEDIALOG_H
#define INPUTPRICEDIALOG_H

#include <QDialog>
#include <QSqlDatabase>
#include <QString>
#include "XCSV.h"
#include "NList.h"
#include "XServiceRegSpector.h"

namespace Ui {
class InputPriceDialog;
}




class InputPriceDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputPriceDialog(PriceContainer &prices ,QWidget *parent = 0);
    ~InputPriceDialog();
    
    PriceContainer  Prices;

private slots:
    void on_pushButtonSet_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::InputPriceDialog *ui;
};

#endif // INPUTPRICEDIALOG_H
