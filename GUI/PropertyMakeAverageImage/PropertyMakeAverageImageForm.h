#ifndef PROPERTYMAKEAVERAGEIMAGEFORM_H
#define PROPERTYMAKEAVERAGEIMAGEFORM_H

#include "XGUIFormBase.h"
#include "XMakeAverageImage.h"

namespace Ui {
class PropertyMakeAverageImageForm;
}

class PropertyMakeAverageImageForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyMakeAverageImageForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyMakeAverageImageForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInScanning(int64 shownInspectionID=-1)	override;

    void    ResetAverage(void);

private slots:
    void on_toolButtonDrawPartialArea_clicked();
    void on_toolButtonDrawImage_clicked();
    void on_toolButtonDrawDarkImage_clicked();
    void on_toolButtonDrawLightImage_clicked();
    void on_toolButtonDrawAverageImage_clicked();
    void on_pushButtonSetAverageToMaster_clicked();
    void on_toolButtonDrawVariableImage_clicked();
    void on_pushButtonResetAverage_clicked();

    void on_horizontalSliderVariableStrength_valueChanged(int value);

private:
    Ui::PropertyMakeAverageImageForm *ui;

	MakeAverageImageBase	*GetMakeAverageImageBase(void);
};

#endif // PROPERTYMAKEAVERAGEIMAGEFORM_H
