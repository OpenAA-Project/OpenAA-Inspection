#ifndef PROPERTYSAVEPARTIALIMAGEFORM_H
#define PROPERTYSAVEPARTIALIMAGEFORM_H

#include <QWidget>
#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"
#include "XServiceForLayers.h"

namespace Ui {
class PropertySavePartialImageForm;
}

class PropertySavePartialImageForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertySavePartialImageForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertySavePartialImageForm();
    
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	void	ShowGrid(void);

private:
    Ui::PropertySavePartialImageForm *ui;
};

#endif // PROPERTYSAVEPARTIALIMAGEFORM_H
