#ifndef BUTTONADDSUBFORM_H
#define BUTTONADDSUBFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ButtonAddSubForm;
}

class ButtonAddSubForm : public GUIFormBase
{
    Q_OBJECT

public:
    bool    CopyAllAlgorithm;
    bool    CopyAllFilters;

    explicit ButtonAddSubForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~ButtonAddSubForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_toolButtonAdd_clicked();
    void on_toolButtonSub_clicked();

private:
    Ui::ButtonAddSubForm *ui;
};

#endif // BUTTONADDSUBFORM_H
