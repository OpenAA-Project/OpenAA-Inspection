#ifndef INTEGRATIONMODIFYMASTERFORM_H
#define INTEGRATIONMODIFYMASTERFORM_H

#include <QWidget>
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntClass.h"
namespace Ui {
class IntegrationModifyMasterForm;
}
class PopupMenuForm;

class IntegrationModifyMasterForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT
	PopupMenuForm	*W;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

    explicit IntegrationModifyMasterForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~IntegrationModifyMasterForm();

	virtual	void	Prepare(void)	override;
private slots:
    void on_PushButton_clicked();
	void	ResizeAction();
private:
    Ui::IntegrationModifyMasterForm *ui;
};

#endif // INTEGRATIONMODIFYMASTERFORM_H
