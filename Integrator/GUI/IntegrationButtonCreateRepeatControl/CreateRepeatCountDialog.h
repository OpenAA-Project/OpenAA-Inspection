#ifndef CREATEREPEATCOUNTDIALOG_H
#define CREATEREPEATCOUNTDIALOG_H

#include <QDialog>
#include "XServiceForLayers.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

namespace Ui {
class CreateRepeatCountDialog;
}

class CreateRepeatCountDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit CreateRepeatCountDialog(LayersBase *base ,QWidget *parent = nullptr);
    ~CreateRepeatCountDialog();

private slots:
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::CreateRepeatCountDialog *ui;
};

//==============================================================================
class	IntegrationCmdReqRepeatCount: public IntegrationCmdPacketBase
{
public:
	IntegrationCmdReqRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};
class	IntegrationCmdAckRepeatCount: public IntegrationCmdPacketBase
{
public:
	int	RepeatCount;

	IntegrationCmdAckRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName){}
};

class	IntegrationCmdSetRepeatCount: public IntegrationCmdPacketBase
{
public:
	int	RepeatCount;

	IntegrationCmdSetRepeatCount(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo,int cmd,QString &EmitterRoot,QString &EmitterName);
};

#endif // CREATEREPEATCOUNTDIALOG_H
