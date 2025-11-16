#ifndef BUTTONSAVEPWAFILE_H
#define BUTTONSAVEPWAFILE_H

#include <QLabel>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QPushButton>

class	ButtonSavePWAFile : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString FileName;

	ButtonSavePWAFile(LayersBase *Base ,QWidget *parent);
	
	virtual void	Prepare(void)	override;

	bool	SavePWA(QString LFileName);

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
#endif // BUTTONSAVEPWAFILE_H
