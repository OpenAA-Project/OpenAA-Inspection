#ifndef INTEGRATIONSHOWNGMAPBUTTONFORM_H
#define INTEGRATIONSHOWNGMAPBUTTONFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class IntegrationShowNGMapButtonForm;
}

class IntegrationShowNGMapButtonForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	
	explicit IntegrationShowNGMapButtonForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationShowNGMapButtonForm();
    
	virtual	void	Prepare(void)	override;

private slots:
    void on_PushButtonNGMap_clicked();
	void	ResizeAction();
private:
    Ui::IntegrationShowNGMapButtonForm *ui;
};

#endif // INTEGRATIONSHOWNGMAPBUTTONFORM_H
