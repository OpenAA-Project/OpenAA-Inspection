#ifndef BUTTONSELECTMACHINEFORREVIEW_H
#define BUTTONSELECTMACHINEFORREVIEW_H

#include <QWidget>
#include <QPushButton>
#include <QTranslator>
#include "XGUIDLL.h"
#include "XDLLOnly.h"

namespace Ui {
class ButtonSelectMachineForReview;
}

class ButtonSelectMachineForReview : public GUIFormBase
{
    Q_OBJECT
    
public:
	QString	Msg;
	QFont	CFont;
	int32		DefaultTopMachineID;
	int32		DefaultBottomMachineID;

    explicit ButtonSelectMachineForReview(LayersBase *base ,QWidget *parent = 0);
    ~ButtonSelectMachineForReview();

	virtual void	Prepare(void)		override;
	virtual	void	GetMenuInfo(MenuInfoContainer &Info)		override;
	virtual	void	ExecuteMenu(int ID)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_pushButton_clicked();
	void	ResizeAction();
private:
    Ui::ButtonSelectMachineForReview *ui;
};

#endif // BUTTONSELECTMACHINEFORREVIEW_H
