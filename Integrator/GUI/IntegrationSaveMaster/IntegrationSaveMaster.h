#ifndef INTEGRATIONSAVEMASTER_H
#define INTEGRATIONSAVEMASTER_H

#include "integrationsavemaster_global.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationBase.h"

class	IntegrationSaveMaster: public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT

	QToolButton	Button;
public:
	QString	ErrorMessageOfFalse;
	bool	ExeReturn;

	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	LastOpenedFileName;
	int			LastOpenedID;
	int			LastOrderMode;
	bool		LastAcsendantOrder;

	IntegrationSaveMaster(LayersBase *Base ,QWidget *parent);
	~IntegrationSaveMaster(){}

	virtual void	Prepare(void)	override;
	void	OpenDialog(bool ModeCopyImage);
	void	CreateNewDialog(void);
	void	UpdateWithoutDialog(void);
	bool	CheckDupInMaster(const QString &ResultName
							,const QString &ResultNumber
							,const QString &ResultRemark
							,bool NewMode);
private slots:
	void	SlotClicked ();
	void	ResizeAction();

private:
	void	SaveWithDialog(bool ModeCopyImage ,bool ModeNew=true ,bool ModeUpdate=true);
};


class	IntegrationCmdSaveMaster : public IntegrationCmdPacketBase
{
public:
	int		RelationCode;
	int		MasterCode	;
	QString	ResultName	;
	QString	ResultRemark;
	IntegrationCommonData	CommonData;
	bool ModeCopyImage;

	IntegrationCmdSaveMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationAckSaveMaster : public IntegrationCmdPacketBase
{
public:
	int	MasterCode;

	IntegrationAckSaveMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}
};


class	IntegrationReqSaveMasterReturn : public IntegrationCmdPacketBase
{
public:
	IntegrationReqSaveMasterReturn(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	IntegrationAckSaveMasterReturn : public IntegrationCmdPacketBase
{
public:
	bool	ExeReturn;
	QString	ErrorMessageOfFalse;

	IntegrationAckSaveMasterReturn(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd, QString & EmitterRoot, QString & EmitterName){}
};


#endif // INTEGRATIONSAVEMASTER_H
