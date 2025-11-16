#ifndef BUTTONLIGHTON_H
#define BUTTONLIGHTON_H

#include "buttonlighton_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIFormBase.h"
#include "XGUIPacketForDLL.h"
#include "mtToolButtonColored.h"

class	SignalOperandBit;

class	ButtonLightON : public GUIFormBase
{
	Q_OBJECT

	mtToolButtonColored	Button;
	bool	SyncMode;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	bool	DefaultPushed;

	ButtonLightON(LayersBase *Base ,QWidget *parent);
	~ButtonLightON(void);
	
	virtual void	ReadyTerminate(void);

	virtual void	Prepare(void)			override;
	virtual	void	RxSync(QByteArray &f)	override;
private:
	void	ExecuteToggled( bool checked );
private slots:
	void	SlotToggled(bool tgl);
	void	ResizeAction();
};
#endif // BUTTONLIGHTON_H
