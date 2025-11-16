#ifndef EASYPROPERTYCOLORDIFFERENCEFORM_H
#define EASYPROPERTYCOLORDIFFERENCEFORM_H

#include "XGUIFormBase.h"
#include "XIntegrationPacketComm.h"
#include "XAlgorithmLibrary.h"
#include <QModelIndex>
#include "OnFlowForm.h"

namespace Ui {
class EasyPropertyColorDifferenceForm;
}

class	ColorDifferenceBase;

class EasyPropertyColorDifferenceForm : public GUIFormBase
{
    Q_OBJECT
    AlgorithmLibraryListContainer	LibList;
	OnFlowForm	*OnFlowFormWindow;
public:
	int32	SlaveNo;
	
	explicit EasyPropertyColorDifferenceForm(LayersBase *Base ,QWidget *parent = 0);
    ~EasyPropertyColorDifferenceForm();
    
	virtual void	Prepare(void) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	StartInitial(void)	override;
private slots:
    void on_toolButtonItem_clicked();
    void on_toolButtonReference_clicked();
	void	ResizeAction();
    void on_toolButtonRegisterOK_clicked();
    void on_toolButtonRegisterNG_clicked();
    void on_toolButtonRegistInFlow_clicked();
    void on_toolButtonSetThresholdByFlow_clicked();
    void on_toolButtonClearFlow_clicked();
    void on_toolButtonAutoGenerate_clicked();

private:
    Ui::EasyPropertyColorDifferenceForm *ui;

	ColorDifferenceBase	*GetColorDifferenceBase(void);
};


class	CmdColorDifferenceDrawInfo : public GUIDirectMessage
{
public:
	int		LibID;

	CmdColorDifferenceDrawInfo(LayersBase *base):GUIDirectMessage(base){}
	CmdColorDifferenceDrawInfo(GUICmdPacketBase *gbase):GUIDirectMessage(gbase){}
};

class	IntegrationCmdRegisterOK : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdRegisterOK(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};
class	IntegrationCmdRegisterNG : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdRegisterNG(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};
class	IntegrationCmdRegistInFlowON: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdRegistInFlowON(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};
class	IntegrationCmdRegistInFlowOFF: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdRegistInFlowOFF(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationCmdAutoGenerate: public IntegrationCmdPacketBase
{
public:
	int		LibID;
	IntegrationCmdAutoGenerate(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:
};

class	IntegrationCmdSetStatisticThreshold : public IntegrationCmdPacketBase
{
public:
	double	SigmaH;
	double	SigmaS;
	double	SigmaV;

	IntegrationCmdSetStatisticThreshold(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};
class	IntegrationCmdClearFlowStack : public IntegrationCmdPacketBase
{
public:
	IntegrationCmdClearFlowStack(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f){	return true;	}
	virtual	bool	Save(QIODevice *f){	return true;	}

	virtual	void	Receive(int32 slaveNo, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // EASYPROPERTYCOLORDIFFERENCEFORM_H
