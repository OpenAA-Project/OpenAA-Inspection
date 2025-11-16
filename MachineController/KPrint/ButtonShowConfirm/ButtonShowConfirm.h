#pragma once

#include "buttonshowconfirm_global.h"
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "XIntegrationBase.h"
#include <QImage>
#include <QString>
#include <QColor>
#include <QFont>
#include <QPushButton>

class	ConfirmForm;
class	IntegrationReqConfirmPanelImage;

class  ButtonShowConfirm: public GUIFormBase
{
	Q_OBJECT

	friend	class ConfirmForm;
	friend	class	IntegrationReqConfirmPanelImage;
	friend	class	IntegrationAckConfirmPanelImage;

	QImage	TargetImageWithNG;
	QImage	TargetImageItems;
	BYTE	*TargetImageWithNGBuff;
	int		TargetImageWithNGXLen;
	int		TargetImageWithNGYLen;

	QPushButton	Button;
	ConfirmForm	*Window;
public:
	int32	SlaveNo;
	QString	Msg;
	QColor	CharColor;
	QColor	BackColor;
	QFont	CFont;
	int32	ImageBankListCount;

	explicit ButtonShowConfirm(LayersBase *Base ,QWidget *parent = 0);
	~ButtonShowConfirm();

	virtual	void	Prepare(void)	override;
	virtual void	ReadyParam(void) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;

	ConfirmForm	*GetWindow(void)	{	return Window;	}
	void	SetSelectedArea(FlexArea &_SelectedArea);
	virtual	void	SpecifiedDirectly(SpecifiedBroadcaster *v)  override;

private slots:
	void	SlotClicked (bool checked);
	void	ResizeAction();
};
