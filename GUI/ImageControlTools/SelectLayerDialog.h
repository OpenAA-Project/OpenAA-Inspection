#ifndef SELECTLAYERDIALOG_H
#define SELECTLAYERDIALOG_H

#include <QDialog>
#include <QToolButton>
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectLayerDialog;
}

class ImageControlTools;

class SelectLayerDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	mtToolButtonColored	**LButtonList;
	int						LNumb;
    ImageControlTools   *Parent;

public:
    explicit SelectLayerDialog(ImageControlTools *p,LayersBase *Base,QWidget *parent = nullptr);
    ~SelectLayerDialog();

private slots:
    void on_pushButtonOK_clicked();
    void LayerClicked(bool checked);
    void on_pushButtonAllON_clicked();
    void on_pushButtonAllOFF_clicked();
    void SlotValueChanged(int value);
private:
    Ui::SelectLayerDialog *ui;

    virtual void resizeEvent(QResizeEvent *event)   override;
};

#endif // SELECTLAYERDIALOG_H
