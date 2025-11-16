#ifndef BUTTONTOSNAPIMAGE_H
#define BUTTONTOSNAPIMAGE_H

#include "buttontosnapimage_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>
#include <QIODevice>
#include <QByteArray>
#include <QString>
#include <QColor>
#include <QFont>

class	ButtonToSnapImage : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	QString	SavedFolder;
	QString	FileNameFormat;

	ButtonToSnapImage(LayersBase *Base ,QWidget *parent);
	~ButtonToSnapImage(void);
	virtual void	Prepare(void)								override;

	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;
public slots:
	void SlotClicked (bool checked);

private slots:
	void	ResizeAction();
};

class	CmdSnapImageToFile : public GUIDirectMessage
{
public:
	QString RetFileName;
	bool	Success;
	CmdSnapImageToFile(LayersBase *base):GUIDirectMessage(base){}
};

class	CmdSnapImageToFixedFile : public GUIDirectMessage
{
public:
	int		ImageXLen;
	int		ImageYLen;
	QList<QByteArray>	Arrays;
	QString FileName;
	bool	Success;
	CmdSnapImageToFixedFile(LayersBase *base):GUIDirectMessage(base){}
};


class	CmdSnapSaveImageToFixedFile : public GUIDirectMessage
{
public:
	int		ImageXLen;
	int		ImageYLen;
	QList<QByteArray>	Arrays;
	QImage	SourceImage;
	QString FileName;
	bool	Success;
	CmdSnapSaveImageToFixedFile(LayersBase *base):GUIDirectMessage(base){}
};


#endif // BUTTONTOSNAPIMAGE_H
