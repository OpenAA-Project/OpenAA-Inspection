#ifndef HIOTESTMODEDIALOG_H
#define HIOTESTMODEDIALOG_H

#include <QDialog>

namespace Ui {
class HioTestModeDialog;
}

class HioTestModeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit HioTestModeDialog(QWidget *parent = nullptr);
    ~HioTestModeDialog();

private:
    Ui::HioTestModeDialog *ui;
};

#endif // HIOTESTMODEDIALOG_H
