#ifndef RWSHOWOBJECTPROPERTYFORM_H
#define RWSHOWOBJECTPROPERTYFORM_H

#include <QWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
namespace Ui {
class RWShowObjectPropertyForm;
}

class RWShowObjectPropertyForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit RWShowObjectPropertyForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~RWShowObjectPropertyForm();

private:
    Ui::RWShowObjectPropertyForm *ui;

    virtual void resizeEvent(QResizeEvent *event) override;
};

#endif // RWSHOWOBJECTPROPERTYFORM_H
