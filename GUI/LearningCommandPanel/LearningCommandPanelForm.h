#ifndef LEARNINGCOMMANDPANELFORM_H
#define LEARNINGCOMMANDPANELFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "NListComp.h"
#include <QTcpSocket>

namespace Ui {
class LearningCommandPanelForm;
}

class LearningCommandPanelForm : public GUIFormBase
{
    Q_OBJECT

    QTcpSocket  *Sock;
public:
    QString ServerIP;
    bool    ReflectAfterMasterLoad;
    bool    ModeShowExecuteButton ;
    bool    ModeShowReflectButton ;

    explicit LearningCommandPanelForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~LearningCommandPanelForm();

    virtual void	Prepare(void) override;
    virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)  override;
private slots:
    void on_pushButtonReqExecute_clicked();
    void on_pushButtonReflectFromServer_clicked();

    void    SlotReadyReadFromServer();
private:
    Ui::LearningCommandPanelForm *ui;

    bool    ConnectToServer(void);
};

#endif // LEARNINGCOMMANDPANELFORM_H
