#ifndef DALSALOADIMAGE_H
#define DALSALOADIMAGE_H

#include "dalsaloadimage_global.h"
#include <QPushButton>
#include <QTranslator>
#include <QToolButton>
#include <QColor>
#include <QFont>
#include <QString>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	DalsaLoadImage : public GUIFormBase
{
	Q_OBJECT

	QToolButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;

	DalsaLoadImage(LayersBase *Base ,QWidget *parent);
	~DalsaLoadImage(void);
	virtual void	Prepare(void);

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // DALSALOADIMAGE_H
