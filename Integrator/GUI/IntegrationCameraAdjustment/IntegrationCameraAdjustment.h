#pragma once

#include "integrationcameraadjustment_global.h"
#include <QToolButton>
#include <QLabel>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "IntegrationLib.h"
#include "XIntegrationPacketComm.h"

class	IntegrationCameraAdjustment : public GUIFormBase,public IntegratorRelation
{
	Q_OBJECT
	QToolButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	IntegrationCameraAdjustment(LayersBase *Base ,QWidget *parent);
	~IntegrationCameraAdjustment();

	virtual void	Prepare(void)	override;

private slots:
	void	SlotClicked ();
	void	ResizeAction();
};
//==============================================================================
class	IntegrationCmdSetAdjustCamera: public IntegrationCmdPacketBase
{
public:
	bool	ONAdjustMode;
	IntegrationCmdSetAdjustCamera(LayersBase *Base,const QString &EmitterRoot,const QString &EmitterName,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f)	{	return true;	}
	virtual	bool	Save(QIODevice *f)	{	return true;	}

	virtual	void	Receive(int32 slaveNo, int cmd,QString &EmitterRoot,QString &EmitterName);
};