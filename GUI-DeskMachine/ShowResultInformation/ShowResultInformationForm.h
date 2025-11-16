#ifndef SHOWRESULTINFORMATIONFORM_H
#define SHOWRESULTINFORMATIONFORM_H

#include "XGUIFormBase.h"
#include "ui_ShowResultInformationForm.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

class ShowResultInformationForm : public GUIFormBase
{
	Q_OBJECT

public:
	bool	ShowInspectCount;
	bool	ShowOKCount;
	bool	ShowNGCount;
	bool	ShowReInspectCount;

	QString	TitleInspectCount;
	QString	TitleOKCount;
	QString	TitleNGCount;
	QString	TitleReInspectCount;

	bool	ShowHeadInspectCount;
	bool	ShowHeadOKCount;
	bool	ShowHeadNGCount;
	bool	ShowHeadReInspectCount;

	QString	AlignAttr;
	QColor	CharColor;
	QColor	BackColor;
	bool	TransparentBackColor;
	QColor	BorderColor;
	int		BorderWidth;
	QString	BorderStyle;
	QFont	CFont;

	QString	HeadAlignAttr;
	QColor	HeadCharColor;
	QColor	HeadBackColor;
	bool	HeadTransparentBackColor;
	QColor	HeadBorderColor;
	int		HeadBorderWidth;
	QString	HeadBorderStyle;
	QFont	HeadCFont;

	int		HeadWidth;

	ShowResultInformationForm(LayersBase *Base ,QWidget *parent = 0);
	~ShowResultInformationForm();

	virtual void	Prepare(void)		override;
	virtual void	ShowInPlayer(int64 shownInspectionID)	override;
	virtual void	BuildForShow(void)	override;

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private:
	Ui::ShowResultInformationFormClass ui;
private slots:
	void	ResizeAction();
};

#endif // SHOWRESULTINFORMATIONFORM_H
