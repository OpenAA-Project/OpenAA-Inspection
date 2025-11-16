#ifndef PROPERTYREPLACEIMAGEFORM_H
#define PROPERTYREPLACEIMAGEFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class PropertyReplaceImageForm;
}

class PropertyReplaceImageForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyReplaceImageForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyReplaceImageForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

private slots:
    void on_toolButtonViewMask_clicked();

private:
    Ui::PropertyReplaceImageForm *ui;
};

#endif // PROPERTYREPLACEIMAGEFORM_H
