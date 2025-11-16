#ifndef SHOWMARKROTATIONDIALOG_H
#define SHOWMARKROTATIONDIALOG_H

#include <QDialog>
#include <QString>
#include <QModelIndex>
#include <QToolButton>
#include "XShiftMark.h"
#include "XShiftMarkLibrary.h"
#include "XServiceForLayers.h"

namespace Ui {
class ShowMarkRotationDialog;
}

class ShowMarkRotationDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    int Phase;
    int GlobalPage;
    int ItemID;

	FlexAreaColorRotatedImageContainer	EdgeArea;
	FlexAreaColorRotatedImageContainer	MarkArea;

    QImage  ImgEdge;
    QImage  ImgMark;
public:
    explicit ShowMarkRotationDialog(LayersBase *base 
                                ,int Page ,int ItemID ,QWidget *parent = nullptr);
    ~ShowMarkRotationDialog();

private slots:
    void on_horizontalSliderAngleNumber_valueChanged(int value);
    void on_pushButtonClose_clicked();

private:
    Ui::ShowMarkRotationDialog *ui;
};

#endif // SHOWMARKROTATIONDIALOG_H
