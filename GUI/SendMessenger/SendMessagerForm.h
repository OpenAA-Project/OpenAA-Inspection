#ifndef SENDMESSAGERFORM_H
#define SENDMESSAGERFORM_H

#include "XGUIFormBase.h"
#include "ui_SendMessagerForm.h"
#include <QPushButton>
#include <QBuffer>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XMessagerClient.h"

class SendMessagerForm : public GUIFormBase
{
	Q_OBJECT

	MessagerClient	MClient;
public:
	QString	IPAddress;

	SendMessagerForm(LayersBase *Base ,QWidget *parent = 0);
	~SendMessagerForm();

	virtual	void	Prepare(void)	override;

private:
	Ui::SendMessagerFormClass ui;

private slots:
	void on_pushButtonSend_clicked();
};


#endif // SENDMESSAGERFORM_H
