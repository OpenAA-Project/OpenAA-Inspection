#ifndef GIOTESTMODEDIALOG_H
#define GIOTESTMODEDIALOG_H

#include <QDialog>

namespace Ui {
class GioTestModeDialog;
}

class GioTestModeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit GioTestModeDialog(QWidget *parent = 0);
    ~GioTestModeDialog();
    
private:
    Ui::GioTestModeDialog *ui;
};

#endif // GIOTESTMODEDIALOG_H
