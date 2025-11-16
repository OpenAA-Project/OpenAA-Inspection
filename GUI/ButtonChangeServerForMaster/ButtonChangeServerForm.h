#ifndef BUTTONCHANGESERVERFORM_H
#define BUTTONCHANGESERVERFORM_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "XChangeServerInfo.h"

namespace Ui {
class ButtonChangeServerForm;
}

class ButtonChangeServerForm : public GUIFormBase
{
    Q_OBJECT
    
public:
	QString	Msg;
	QFont	CFont;

    explicit ButtonChangeServerForm(LayersBase *base ,QWidget *parent = 0);
    ~ButtonChangeServerForm();
    
	virtual void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

	bool	ExeChangeServer(ChangeServerInfo *d);
	virtual	void	RxSync(QByteArray &f)	override;
private slots:
    void on_pushButton_clicked();
	void	ResizeAction();

private:
    Ui::ButtonChangeServerForm *ui;
};

class	GUICmdChangeServer : public GUICmdPacketBase
{
public:
	ChangeServerInfo	ServerData;

	GUICmdChangeServer(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONCHANGESERVERFORM_H
