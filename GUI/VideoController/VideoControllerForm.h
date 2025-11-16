#ifndef VIDEOCONTROLLERFORM_H
#define VIDEOCONTROLLERFORM_H

#include <QWidget>
#include <QToolButton>
#include <QThread>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XServiceForLayers.h"
#include <QTimer>
namespace Ui {
class VideoControllerForm;
}

class	PlayVideoWidget;

class VideoControllerForm : public GUIFormBase
{
    Q_OBJECT
    PlayVideoWidget	*PlayVideoWidgetPointer;
	QTimer	TM;

public:
	bool	ShowFileOpenButton;

    explicit VideoControllerForm(LayersBase *Base ,QWidget *parent = 0);
    ~VideoControllerForm();
    virtual void	ReadyParam(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
private slots:
    void on_toolButtonBackwardMovie_clicked();
    void on_toolButtonRunMovie_clicked();
    void on_toolButtonForwardMovie_clicked();
    void on_horizontalSliderMovie_valueChanged(int value);
    void on_toolButtonOpenFile_clicked();
	void	SlotTimeOut();

private:
    Ui::VideoControllerForm *ui;
};


class	CmdLoadFileAndStart : public GUIDirectMessage
{
public:
	QString VideoFileName;
	CmdLoadFileAndStart(LayersBase *base):GUIDirectMessage(base){}
};


#endif // VIDEOCONTROLLERFORM_H
