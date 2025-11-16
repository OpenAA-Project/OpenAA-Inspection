#ifndef SELECTALIGNMENTAREAFORM_H
#define SELECTALIGNMENTAREAFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SelectAlignmentAreaForm;
}
class EasyPropertyAlignmentForm;

class SelectAlignmentAreaForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    EasyPropertyAlignmentForm   *Parent;
    ListPhasePageLayerItemPack		AreaID;
    IntList	AreaIDList;
public:
    explicit SelectAlignmentAreaForm(LayersBase *base
                                    ,EasyPropertyAlignmentForm *P
                                    ,QWidget *parent = nullptr);
    ~SelectAlignmentAreaForm();
    void    Initial(void);

    int     SelectedAreaID;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_toolButtonSelect_clicked();
    void on_toolButtonCancel_clicked();
    void on_tableWidget_itemSelectionChanged();
    void on_tableWidget_clicked(const QModelIndex &index);

private:
    Ui::SelectAlignmentAreaForm *ui;
};

#endif // SELECTALIGNMENTAREAFORM_H
