#ifndef INTEGRATIONINPUTLOTFORM_H
#define INTEGRATIONINPUTLOTFORM_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include <QString>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include "XDataInLayer.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XExecuteInspectBase.h"

namespace Ui {
class IntegrationInputLotForm;
}

class IntegrationInputLotForm  : public GUIFormBase,public IntegratorRelation
{
    Q_OBJECT

	QString	UserLotID		;
	QString	UserLotNumber	;
	QString	UserSubCode		;
public:
	QFont	TitleFont;
	QFont	CharFont;
	QFont	ButtonFont;
	QString	TitleLotID;
	QString	TitleLotNumber;
	QString	TitleSubCode;
	QColor	TitleColor;
	QString	ButtonText;

	QString	DefaultLotID		;
	QString	DefaultLotNumber	;
	QString	DefaultSubCode		;
	bool	ManualChangedLotID		;
	bool	ManualChangedLotNumber	;
	bool	ManualChangedSubCode	;
	bool	EnableManualChanged;
	int		Counter;

	QString	LotID		;
	QString	LotNumber	;
	QString	SubCode		;
	bool	Registered;

    explicit IntegrationInputLotForm(LayersBase *Base ,QWidget *parent = 0);
    ~IntegrationInputLotForm();

	virtual void	Prepare(void) override;
	virtual void	StartLot(void)override;

	void	RegisterLot(const QString &LotID,const QString &LotNumber,const QString &SubCode);

private slots:
    void on_toolButtonGenerateLot_clicked();
	void	ResizeAction();
    void on_pushButtonLotNumber_clicked();
    void on_pushButtonSubCode_clicked();
    void on_pushButtonLotID_clicked();
    void on_lineEditLotID_textChanged(const QString &arg1);
    void on_lineEditLotNumber_textChanged(const QString &arg1);
    void on_lineEditSubCode_textChanged(const QString &arg1);
    void on_pushButtonTitleLotID_clicked();
    void on_pushButtonTitleLotNumber_clicked();
    void on_pushButtonSubCode_2_clicked();

private:
    Ui::IntegrationInputLotForm *ui;

	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v) override;

	QString	ReplaceKeyword(const QString &src ,const QString &UserStr);
};

//======================================================================================================================

class	IntegrationCmdInputLot : public IntegrationCmdPacketBase
{
public:
	QString	LotID		;
	QString	LotName	;
	QString	SubCode		;
	XDateTime	GeneratedTime;	//==LotID

	IntegrationCmdInputLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
	int		LotAutoCount;

	bool ExecuteCreateNew(void);
	void SetLotToSystem(int iLotAutoCount
						,const QString &iLotID
						,const QString &iLotName
						,const QString &iLotRemark);
};

class	IntegrationReqInputLot : public IntegrationCmdPacketBase
{
public:
	IntegrationReqInputLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckInputLot : public IntegrationCmdPacketBase
{
public:
	QString	LotID;
	QString	LotName;
	QString	LotRemark;

	IntegrationAckInputLot(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};

class	GUICmdSelectLot : public GUICmdPacketBase
{
public:
	int			LotAutoCount;
	QString		LotID;
	QString		LotName;
	XDateTime	CurrentInspectTime;
	ExecuteInspectBase::AutoRepeatMode	AMode;

	GUICmdSelectLot(LayersBase *Base ,QString EmitterRoot,QString EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // INTEGRATIONINPUTLOTFORM_H
