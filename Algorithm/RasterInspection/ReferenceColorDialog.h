#ifndef REFERENCECOLORDIALOG_H
#define REFERENCECOLORDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XReferencePDF.h"

namespace Ui {
class ReferenceColorDialog;
}

class RasterInspectionBase;

class ReferenceColorDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit ReferenceColorDialog(LayersBase *Base,QWidget *parent = nullptr);
    ~ReferenceColorDialog();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdateClose_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::ReferenceColorDialog *ui;

    void ShowGrid(void);
    RasterInspectionBase	*GetRasterInspectionBase(void);
};

#endif // REFERENCECOLORDIALOG_H
