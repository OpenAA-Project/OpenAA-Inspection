#ifndef BUTTONALIGNMENTLARGETRANSFORM_H
#define BUTTONALIGNMENTLARGETRANSFORM_H

#include "buttonalignmentlargetransform_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"

class	ButtonAlignmentLargeTransform : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	MasterImage;

	ButtonAlignmentLargeTransform(LayersBase *Base ,QWidget *parent);
	~ButtonAlignmentLargeTransform(void);
	virtual void	Prepare(void)	override;

private:

private slots:
	void	SlotClicked();
	void	ResizeAction();
};

class	GUICmdReqAlignmentLargeTransform : public GUICmdPacketBase
{
public:
	bool	MasterImage;

	GUICmdReqAlignmentLargeTransform(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // BUTTONALIGNMENTLARGETRANSFORM_H
