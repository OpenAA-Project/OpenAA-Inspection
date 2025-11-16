#ifndef DISPLAYPRODUCTIVITYFORM_H
#define DISPLAYPRODUCTIVITYFORM_H

#include <QString>
#include <QStringList>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XResult.h"
#include "XTypeDef.h"

namespace Ui {
class DisplayProductivityForm;
}

class DisplayProductivityForm : public GUIFormBase
{
    Q_OBJECT

    DWORD   InspectedTimeMilisec[100];
    int     CountInspected;
    int     WPoint;
public:
    QString CountType;

    explicit DisplayProductivityForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~DisplayProductivityForm();

	virtual void	Prepare(void)		override;
    virtual void	ShowInPlayer(int64 shownInspectionID)		override;
private:
    Ui::DisplayProductivityForm *ui;
};

#endif // DISPLAYPRODUCTIVITYFORM_H
