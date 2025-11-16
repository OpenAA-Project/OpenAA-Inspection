#ifndef BUTTONSYNCHRONIZEIMAGEPANEL_H
#define BUTTONSYNCHRONIZEIMAGEPANEL_H

#include "buttonsynchronizeimagepanel_global.h"

#include <QToolBar>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XGUIFormBase.h"
#include "mtToolButtonColored.h"
#include <QPushButton>
#include <QStringList>
#include <QString>
#include <QColor>
#include <QFont>

class ButtonSynchronizeImagePanel : public GUIFormBase
{
	Q_OBJECT

	int	IconSizeW;
	int	IconSizeH;
public:
	QString		ButtonTitle;
	QFont		ButtonFont;
	QColor		UncheckedColor;
	QColor		ActiveColor;

	QString		SrcAlgoImagePanelRoot;
	QString		SrcAlgoImagePanelName;
	QString		SrcAlgoImagePanelInst;

	QString		TargetImagePanelRoot;
	QString		TargetImagePanelName;
	QString		TargetImagePanelInst;

	QPushButton	Button;

	ButtonSynchronizeImagePanel(LayersBase *Base ,QWidget *parent);
	~ButtonSynchronizeImagePanel(void);

	virtual void	Prepare(void)		override;
	void	Release(void);
	virtual void	ShowInEdit(void)	override;

private:

private slots:
	void	ResizeAction();
	void	SlotButtonDown();
};

#endif // BUTTONSYNCHRONIZEIMAGEPANEL_H
