#ifndef BUTTONLEARNINGOK_H
#define BUTTONLEARNINGOK_H

#include "buttonlearningok_global.h"
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "LearningPanelForm.h"

class	ButtonLearningOK : public GUIFormBase
{
	Q_OBJECT
	
	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	RelatedImagePanel;
	QString	NGListInst;

	ButtonLearningOK(LayersBase *Base ,QWidget *parent);
	~ButtonLearningOK(void);

	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private:
	LearningPanelForm	*LForm;

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};

#endif // BUTTONLEARNINGOK_H
