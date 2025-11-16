#ifndef SETTHRESHOLDLEVELFORM_H
#define SETTHRESHOLDLEVELFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XIntClass.h"

namespace Ui {
class SetThresholdLevelForm;
}

class SetThresholdLevelForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT
    
    IntList ThresholdLevelIDs;
    bool    ReflectDirectly;
    int     CurrentThresholdLevelID;
public:
    explicit SetThresholdLevelForm(LayersBase *base ,bool ReflectDirectly=true,QWidget *parent = 0);
    ~SetThresholdLevelForm();
    
    void    SetCurrentThresholdLevelID(int32 ThresholdLevelID);
    int     GetCurrentThresholdLevelID(void);
signals:
	void	SignalReqChangeLevelParent();
    void    SignalChangeThresholdLevelID(int ThresholdLevelID);

private slots:
    void on_horizontalSlider_valueChanged(int value);
	void	SlotChangeThresholdLevel(int OldLevel ,int NewLevel);

    void on_pushButtonParent_clicked();

private:
    Ui::SetThresholdLevelForm *ui;

    virtual	void showEvent(QShowEvent *event)       override;
	virtual	void resizeEvent(QResizeEvent *event)	override;
    void    ShowCurrentThresholdInfo(void);
};

#endif // SETTHRESHOLDLEVELFORM_H
