#ifndef SHAREMASTERCHANGEMULTIPLYDIALOG_H
#define SHAREMASTERCHANGEMULTIPLYDIALOG_H

#include <QDialog>

namespace Ui {
class ShareMasterChangeMultiplyDialog;
}

class ShareMasterChangeMultiplyDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ShareMasterChangeMultiplyDialog(double MultiplyLayer[],QWidget *parent = 0);
    ~ShareMasterChangeMultiplyDialog();

	double	MultiplyLayer[256];
    
private:
    Ui::ShareMasterChangeMultiplyDialog *ui;
};

#endif // SHAREMASTERCHANGEMULTIPLYDIALOG_H
