#ifndef INTEGRATIONNEWMASTER_H
#define INTEGRATIONNEWMASTER_H

#include "integrationnewmaster_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "XIntegrationBase.h"

class	IntegrationNewMaster : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	double	AddedMMX;
	double	AddedMMY;
	double	AddedMMZ;
	double	MaxWidth ;
	double	MaxLength;

	IntegrationNewMaster(LayersBase *Base ,QWidget *parent);
	~IntegrationNewMaster();

	virtual void	Prepare(void)	override;
	void	OpenDialog(void);
	void	ClearAlgorithm(void);
	bool	CheckDupInMaster(const QString &ResultName
							,const QString &ResultNumber
							,const QString &ResultRemark);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
private:

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};
class	IntegrationCmdNewMaster : public IntegrationCmdPacketBase
{
public:
	IntegrationCommonData	CommonData;
	int32	AddedMM;

	IntegrationCmdNewMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	IntegrationCmdClearAlgorithm : public IntegrationCmdPacketBase
{
public:

	IntegrationCmdClearAlgorithm(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	CmdOpenNewMasterDialog : public GUIDirectMessage
{
public:
	CmdOpenNewMasterDialog(LayersBase *base):GUIDirectMessage(base){}
	CmdOpenNewMasterDialog(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	GUICmdNewMaster : public GUICmdPacketBase
{
public:
	double	DistanceX;
	double	DistanceY;

	GUICmdNewMaster(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	

};

#endif // INTEGRATIONNEWMASTER_H
