#ifndef EASYPROPERTYDOTCOLORMATCHFORM_H
#define EASYPROPERTYDOTCOLORMATCHFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class EasyPropertyDotColorMatchForm;
}

class EasyPropertyDotColorMatchForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	int32	SlaveNo;

    explicit EasyPropertyDotColorMatchForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyDotColorMatchForm();
    
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	void	GenerateAutomatically(void);
signals:
	void	SignalBusy();
	void	SignalIdle();
private slots:
    void on_toolButtonAutoGenerate_clicked();
    void on_toolButtonDeleteAll_clicked();
	void	ResizeAction();

    void on_toolButtonShrinkOutline_clicked();

private:
    Ui::EasyPropertyDotColorMatchForm *ui;
};

class	IntegrationCmdGenerate : public IntegrationCmdPacketBase
{
public:
	IntList	GeneratedLibs;

	IntegrationCmdGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationDeleteAll : public IntegrationCmdPacketBase
{
public:
	IntList	GeneratedLibs;

	IntegrationDeleteAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};


class	GUICmdSetLevel: public GUICmdPacketBase
{
public:
	double	Level;	//1.0=Save as Origin
	int		Type;	

	GUICmdSetLevel(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};


class	IntegrationCmdReqLimitedMask : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqLimitedMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdAckLimitedMask : public IntegrationCmdPacketBase
{
public:
	IntList	LimitedLib;

	IntegrationCmdAckLimitedMask(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}

private:

};

class	IntegrationAutoGeneration : public GUIDirectMessage
{
public:
	IntegrationAutoGeneration(LayersBase *base):GUIDirectMessage(base){}
	IntegrationAutoGeneration(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

#endif // EASYPROPERTYDOTCOLORMATCHFORM_H
