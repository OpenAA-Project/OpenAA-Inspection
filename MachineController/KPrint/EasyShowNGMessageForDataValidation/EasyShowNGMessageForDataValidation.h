#pragma once

#include "easyshowngmessagefordatavalidation_global.h"
#include "XGUIFormBase.h"
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XIntegrationPacketComm.h"

class	CheckDataValidationBase;
class	ShowNGMessageForm;

class	EasyShowNGMessageForDataValidation : public GUIFormBase
{
	Q_OBJECT

	ShowNGMessageForm	*NGMessageWindow;
public:
	bool ModeShowNGMessage;

	EasyShowNGMessageForDataValidation(LayersBase *Base ,QWidget *parent);
	~EasyShowNGMessageForDataValidation(void);
	
	virtual void	ReadyParam(void)	override;
	void	SetNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage);

private:
	CheckDataValidationBase	*GetCheckDataValidationBase(void);
private slots:
	void    SlotShowNGMessage(int phase ,int page);
	void	SlotNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage);
signals:
	void	SignalNGMessage(int SlaveNo,int Phase ,int GlobalPage,const QString &NGMessage);
};


class	IntegrationCmdShowNGMessage : public IntegrationCmdPacketBase
{
public:
    int		Phase;
	QString	NGMessage;

	IntegrationCmdShowNGMessage(LayersBase *Base 
									,const QString &EmitterRoot,const QString &EmitterName 
									,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);
};

