#ifndef SEARCHLOTDIALOG_H
#define SEARCHLOTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"

namespace Ui {
class SearchLotDialog;
}

class SearchLotDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SearchLotDialog(LayersBase *Base ,QWidget *parent = 0);
    ~SearchLotDialog();
    
    QString SelectedLotID		;
    QString SelectedLotNumber	;
    QString SelectedSubCode	    ;

private slots:
    void on_pushButtonSelect_clicked();

private:
    Ui::SearchLotDialog *ui;
};

#endif // SEARCHLOTDIALOG_H
