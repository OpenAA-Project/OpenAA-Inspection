#ifndef SHOWALLIMAGEFORM_H
#define SHOWALLIMAGEFORM_H

#include <QWidget>
#include "XServiceForLayers.h"

namespace Ui {
class ShowAllImageForm;
}

class GUIShowPointsButtonForm;

class ShowAllImageForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

    GUIShowPointsButtonForm *Parent;

public:
    explicit ShowAllImageForm(GUIShowPointsButtonForm *P ,LayersBase *Base,QWidget *parent = nullptr);
    ~ShowAllImageForm();

private slots:
    void on_tableWidget_cellDoubleClicked(int row, int column);

private:
    Ui::ShowAllImageForm *ui;

    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);

};

#endif // SHOWALLIMAGEFORM_H
