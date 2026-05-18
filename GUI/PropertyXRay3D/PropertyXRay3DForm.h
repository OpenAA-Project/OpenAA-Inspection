#ifndef PROPERTYXRAY3DFORM_H
#define PROPERTYXRAY3DFORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
namespace Ui {
class PropertyXRay3DForm;
}
class XRay3DBase;

class PropertyXRay3DForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyXRay3DForm(LayersBase *Base,QWidget *parent = nullptr);
    ~PropertyXRay3DForm();

    virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override; 
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;

private slots:
    void on_verticalSliderImageFiles_valueChanged(int value);
    void on_pushButtonLoadImageFiles_clicked();
    void on_pushButtonLoadGerber_clicked();

    void on_pushButtonSmooth_clicked();

    void on_pushButtonEmphasize_clicked();

    void on_pushButtonSearchPosition_clicked();

private:
    Ui::PropertyXRay3DForm *ui;

    XRay3DBase	*GetXRay3DBase(void);
    void    ReviewImage(void);
};

#endif // PROPERTYXRAY3DFORM_H
