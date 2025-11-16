#ifndef BUTTONSELECTLEARNINGTARGETIMAGE_H
#define BUTTONSELECTLEARNINGTARGETIMAGE_H


#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"


class	ButtonSelectLearningTargetImage : public GUIFormBase
{
	Q_OBJECT
	
	QPushButton	Button;
public:
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	QString	DisplayImageRoot;
	QString	DisplayImageName;
	QString	DisplayImageInst;

	ButtonSelectLearningTargetImage(LayersBase *Base ,QWidget *parent);
	~ButtonSelectLearningTargetImage(void);

	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)	override;
	virtual	void	ExecuteMenu(int ID)	override;

private:

private slots:
	void SlotClicked (bool checked);
	void	ResizeAction();
};


#endif
