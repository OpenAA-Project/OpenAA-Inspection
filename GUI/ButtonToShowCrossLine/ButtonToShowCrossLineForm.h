#ifndef BUTTONTOSHOWCROSSLINEFORM_H
#define BUTTONTOSHOWCROSSLINEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include <QToolButton>
#include <QStringList>
#include <QColor>

namespace Ui {
class ButtonToShowCrossLineForm;
}

class	CrossLineButton : public QToolButton
{
    Q_OBJECT
public:
	CrossLineButton ( QWidget * parent = 0);

signals:
	void	SignalRightButton();
protected:
	void	mouseReleaseEvent ( QMouseEvent * e );
};

class ButtonToShowCrossLineForm : public GUIFormBase
{
    Q_OBJECT

	CrossLineButton	Button;
public:
	QStringList		ImagePanelInst;
	QColor			LineColor;
	bool			CrossLine;
	bool			MatrixLine;

    explicit ButtonToShowCrossLineForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonToShowCrossLineForm();

	virtual void	AfterPrepare(void)	override;
private slots:
    void on_toolButtonCrossLine_clicked(bool b);
	void	ResizeAction();
    void on_toolButtonCrossLine_pressed();

private:
    Ui::ButtonToShowCrossLineForm *ui;
};

#endif // BUTTONTOSHOWCROSSLINEFORM_H
