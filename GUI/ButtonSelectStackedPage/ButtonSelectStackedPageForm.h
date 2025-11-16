#ifndef BUTTONSELECTSTACKEDPAGEFORM_H
#define BUTTONSELECTSTACKEDPAGEFORM_H

#include "XGUIFormBase.h"
#include <QToolButton>
#include <QString>
#include <QStringList>
#include <QColor>
#include <QFont>

namespace Ui {
class ButtonSelectStackedPageForm;
}

class ButtonSelectStackedPageForm : public GUIFormBase
{
    Q_OBJECT
    
	QToolButton	**B[10];
public:
	QString		StackFormInst;
	QStringList	Msg;
	QColor		CharColor;
	QFont		CFont;
	int32		FirstPage;

    explicit ButtonSelectStackedPageForm(LayersBase *Base ,QWidget *parent = 0);
    ~ButtonSelectStackedPageForm();
    
	virtual void	Prepare(void)			override;
	void	SelectPage(int page);
private slots:

    void on_toolButton1_clicked();
    void on_toolButton2_clicked();
    void on_toolButton3_clicked();
    void on_toolButton4_clicked();
    void on_toolButton5_clicked();
    void on_toolButton6_clicked();
    void on_toolButton7_clicked();
    void on_toolButton8_clicked();
    void on_toolButton9_clicked();
    void on_toolButton10_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSelectStackedPageForm *ui;
};

#endif // BUTTONSELECTSTACKEDPAGEFORM_H
