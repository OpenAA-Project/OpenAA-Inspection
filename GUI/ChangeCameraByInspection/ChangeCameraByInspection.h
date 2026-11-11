#pragma once

#include "changecamerabyinspection_global.h"
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QString>
#include <QColor>
#include <QFont>
#include <QImage>


class	ChangeCameraByInspection : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	PageNo;
	QByteArray	CamData;

	ChangeCameraByInspection(LayersBase *Base ,QWidget *parent);
	~ChangeCameraByInspection(void);
	
	virtual void	Prepare(void)				override;

	virtual	bool	SaveContent(QIODevice *f);
	virtual	bool	LoadContent(QIODevice *f);
private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
	void	SlotBeforeScan();
};