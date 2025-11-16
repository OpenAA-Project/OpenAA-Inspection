#ifndef PROPERTYPARTIALIMAGINGFORM_H
#define PROPERTYPARTIALIMAGINGFORM_H

#include <QWidget>
#include "XPartialImaging.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"
#include "XPropertyPartialImagingPacket.h"

namespace Ui {
class PropertyPartialImagingForm;
}

class PropertyPartialImagingForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyPartialImagingForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyPartialImagingForm();

	PartialImagingBase	*GetPartialImagingBase(void);

	void	ShowLibList(void);
	virtual void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyPartialImagingForm *ui;

	PartialImagingInfoContainer	PInfoContainer;

};

#endif // PROPERTYPARTIALIMAGINGFORM_H
