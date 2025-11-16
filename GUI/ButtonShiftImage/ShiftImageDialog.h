#ifndef SHIFTIMAGEDIALOG_H
#define SHIFTIMAGEDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
namespace Ui {
class ShiftImageDialog;
}

class ShiftImageDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ShiftImageDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~ShiftImageDialog();

    bool    ModeMasterImage;
    bool    ModeTargetImage;
    int     StartPos;
    int     EndPos;
    int     ShiftN;


private slots:
    void on_pushButtonExecuteShiftY_clicked();
    void on_pushButtonCancelY_clicked();
    void on_pushButtonExecuteShiftX_clicked();
    void on_pushButtonCancelX_clicked();

private:
    Ui::ShiftImageDialog *ui;
};

#endif // SHIFTIMAGEDIALOG_H
