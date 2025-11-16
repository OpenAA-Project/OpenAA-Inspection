#ifndef EDITWAVEGRAPHDIALOG_H
#define EDITWAVEGRAPHDIALOG_H

#include <QDialog>
#include <QString>
#include "XServiceForLayers.h"

namespace Ui {
class EditWaveGraphDialog;
}

class ReferencePDF;

class EditWaveGraphDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    ReferencePDF *RefPDF;
    QImage      *GraphImage;
public:
    explicit EditWaveGraphDialog(ReferencePDF *R,LayersBase *Base
                                ,QWidget *parent = nullptr);
    ~EditWaveGraphDialog();

    void    SetDeletable(bool Deletable);
    QString ReferenceName;

private slots:
    void on_pushButtonDelete_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonUpdateName_clicked();

private:
    Ui::EditWaveGraphDialog *ui;

    void MakeGraph(void);
};

#endif // EDITWAVEGRAPHDIALOG_H
