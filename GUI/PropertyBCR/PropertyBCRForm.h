#ifndef PROPERTYBCRFORM_H
#define PROPERTYBCRFORM_H

#include "XGUIFormBase.h"
#include "XBCRInspection.h"
#include "XStandardPropertyForm.h"
#include "XPropertyBCRPacket.h"
#include <QModelIndex>

namespace Ui {
class PropertyBCRForm;
}

class PropertyBCRForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit PropertyBCRForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyBCRForm();
    
	virtual	void	BuildForShow(void)  override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)  override;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
    void on_pushButtonTest_clicked();
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::PropertyBCRForm *ui;

	void	ShowGrid(void);
	BCRContainer	GridList;
};

#endif // PROPERTYBCRFORM_H
