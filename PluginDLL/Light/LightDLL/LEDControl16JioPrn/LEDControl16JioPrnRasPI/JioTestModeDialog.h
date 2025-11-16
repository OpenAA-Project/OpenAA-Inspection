#ifndef JioTESTMODEDIALOG_H
#define JioTESTMODEDIALOG_H

#include <QDialog>

namespace Ui {
class JioTestModeDialog;
}

class JioTestModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit JioTestModeDialog(QWidget *parent = nullptr);
    ~JioTestModeDialog();

private:
    Ui::JioTestModeDialog *ui;
};

#endif // JioTESTMODEDIALOG_H
