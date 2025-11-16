#ifndef LISTOFADJUSTMOVEALL_H
#define LISTOFADJUSTMOVEALL_H

#include <QDialog>
#include "AdjustMoveAllAfterLoadMaster.h"

namespace Ui {
class ListOfAdjustMoveAll;
}

class ListOfAdjustMoveAll : public QDialog
{
    Q_OBJECT
    
	AdjustMoveAllAfterLoadMaster	*LParent;
	int		LastMasterCode;
public:
    explicit ListOfAdjustMoveAll(AdjustMoveAllAfterLoadMaster *p ,QWidget *parent = 0);
    ~ListOfAdjustMoveAll();
    
private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonClose_clicked();
    void on_pushButtonLoad_clicked();

    void on_spinBoxMasterCode_valueChanged(int arg1);

private:
    Ui::ListOfAdjustMoveAll *ui;
};

#endif // LISTOFADJUSTMOVEALL_H
