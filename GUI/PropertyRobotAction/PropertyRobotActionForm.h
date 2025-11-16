#ifndef PROPERTYROBOTACTIONFORM_H
#define PROPERTYROBOTACTIONFORM_H

#include "XGUIFormBase.h"
#include "XRobotAction.h"

namespace Ui {
class PropertyRobotActionForm;
}

class PropertyRobotActionForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyRobotActionForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyRobotActionForm();

    virtual void	BuildForShow(void)  override;
    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_tableWidgetMarkList_clicked(const QModelIndex &index);
    void on_tableWidgetMarkList_doubleClicked(const QModelIndex &index);

    void on_pushButtonClearAll_clicked();

    void on_toolButtonTeachingMode_clicked();

private:
    Ui::PropertyRobotActionForm *ui;
    RobotActionBase	*GetRobotActionBase(void);
    GUIFormBase     *GetPanel(void);
    void    ShowList(void);
};

#endif // PROPERTYROBOTACTIONFORM_H
