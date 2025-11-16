#ifndef PROPERTYWORLD3DFORM_H
#define PROPERTYWORLD3DFORM_H

#include "XGUIFormBase.h"
#include "XWorld3D.h"

namespace Ui {
class PropertyWorld3DForm;
}

class PropertyWorld3DForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyWorld3DForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyWorld3DForm();

private slots:
    void on_pushButtonAddStepFile_clicked();

private:
    Ui::PropertyWorld3DForm *ui;

    World3DBase	*GetWorld3DBase(void);
};

#endif // PROPERTYWORLD3DFORM_H
