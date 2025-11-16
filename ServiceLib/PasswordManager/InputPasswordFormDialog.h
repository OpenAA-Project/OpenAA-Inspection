#ifndef INPUTPASSWORDFORMDIALOG
#define INPUTPASSWORDFORMDIALOG

#include <QDialog>

namespace Ui {
class InputPasswordFormDialog;
}

class InputPasswordFormDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit InputPasswordFormDialog(QWidget *parent = 0, Qt::WindowFlags f = Qt::Widget);
    ~InputPasswordFormDialog();
    
	QString	GetLiedPassword(void);

public:
    Ui::InputPasswordFormDialog *ui;
};

#endif // INPUTPASSWORDFORMDIALOG
