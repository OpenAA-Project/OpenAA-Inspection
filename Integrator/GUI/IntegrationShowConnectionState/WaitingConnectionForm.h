#ifndef WAITINGCONNECTIONFORM_H
#define WAITINGCONNECTIONFORM_H

#include <QWidget>
#include <QTimer>
#include <QCheckBox>
#include "XServiceForLayers.h"
#include "XDateTime.h"

namespace Ui {
class WaitingConnectionForm;
}
class	IntegrationShowConnectionState;

class WaitingConnectionForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

	IntegrationShowConnectionState	*Parent;
	QTimer	TM;
	QCheckBox	**CheckBox;
	int			Count;
public:
    explicit WaitingConnectionForm(LayersBase *base ,IntegrationShowConnectionState *p,QWidget *parent = 0);
    ~WaitingConnectionForm();
    
private slots:
	void	SlotTimeOut();
	void	SlotConnectedAll();
    void on_toolButtonStopLoading_clicked();

private:
    Ui::WaitingConnectionForm *ui;
};

#endif // WAITINGCONNECTIONFORM_H
