#ifndef MOVEALLDIALOG_H
#define MOVEALLDIALOG_H

#include <QDialog>
#include <QToolButton>
#include "XServiceForLayers.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XIntClass.h"
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"
#include "NListComp.h"

namespace Ui {
class MoveAllDialog;
}

class MachineButton : public QToolButton
{
public:
    int SlaveNo;

    MachineButton(int slaveNo):SlaveNo(slaveNo){}

};

class MoveAllDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

    MachineButton *Button[100];

    IntList SlaveNumbers;
    bool    Mastered;
    bool    Targeted;
    int     XDir;
    int     YDir;

public:
    explicit MoveAllDialog(LayersBase *Base ,QWidget *parent = nullptr);
    ~MoveAllDialog();

private slots:
    void on_pushButtonGo_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::MoveAllDialog *ui;
};


//===================================================================================================

class	IntegrationMoveAll : public IntegrationCmdPacketBase
{
public:
    bool    Mastered;
    bool    Targeted;
    int     XDir;
    int     YDir;

	IntegrationMoveAll(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	
};


#endif // MOVEALLDIALOG_H
