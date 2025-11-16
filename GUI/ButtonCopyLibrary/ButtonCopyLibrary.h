#ifndef BUTTONCOPYLIBRARY_H
#define BUTTONCOPYLIBRARY_H

#include "buttoncopylibrary_global.h"
#include <QPushButton>
#include <QBuffer>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class	ButtonCopyLibrary : public GUIFormBase
{
	Q_OBJECT

	QPushButton	Button;

public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	AlgorithmRoot;
	QString	AlgorithmName;

	ButtonCopyLibrary(LayersBase *Base ,QWidget *parent);
	~ButtonCopyLibrary(void);
	
	virtual void	Prepare(void)	override;

	void ExecuteLoad(QIODevice &F
				  ,QString _AlgorithmRoot ,QString _AlgorithmName);

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONCOPYLIBRARY_H
