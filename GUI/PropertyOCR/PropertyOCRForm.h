#ifndef PROPERTYOCRFORM_H
#define PROPERTYOCRFORM_H

#include "XGUIFormBase.h"
#include "XOCRInspection.h"
#include "XStandardPropertyForm.h"
#include "XPropertyOCRPacket.h"

namespace Ui {
class PropertyOCRForm;
}

class PropertyOCRForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit PropertyOCRForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyOCRForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_tableWidget_doubleClicked(const QModelIndex &index);

    void on_pushButtonTest_clicked();

private:
    Ui::PropertyOCRForm *ui;

	void	ShowGrid(void);
	OCRContainer	GridList;
};

#endif // PROPERTYOCRFORM_H
