#ifndef INTEGRATIONRESULTLISTFORM_H
#define INTEGRATIONRESULTLISTFORM_H

#include "XGUIFormBase.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"


namespace Ui {
class IntegrationResultListForm;
}

class IntegrationResultListForm : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	int		ResultDimCount;
	InspectionList	*ResultDim[100];
public:
	QFont	CharFont;
	bool	ShowPos;
	bool	ShowCause;
	bool	ShowValue;
	int32	ScrollerWidth;

    explicit IntegrationResultListForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationResultListForm();

	virtual	void	Prepare(void) override;
	void	ShowList(void);

private:
    Ui::IntegrationResultListForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;
	virtual void	StartLot	(void) override;
signals:
	void	SignalShowList();
private slots:
	void	ResizeAction();
	void	SlotShowList();
    void on_tableWidget_clicked(const QModelIndex &index);
};

#endif // INTEGRATIONRESULTLISTFORM_H
