#ifndef CHANGETURNTOPFORM_H
#define CHANGETURNTOPFORM_H

#include "XGUIFormBase.h"
#include <QStringList>
#include <QLabel>

namespace Ui {
class ChangeTurnTopForm;
}

class ChangeTurnTopForm : public GUIFormBase
{
    Q_OBJECT

public:
	QStringList	RelatedPanels;

    explicit ChangeTurnTopForm(LayersBase *Base ,QWidget *parent = 0);
    ~ChangeTurnTopForm();

	virtual void	Prepare(void)		override;
	virtual	void	BuildForShow(void)	override;
private slots:
    void on_listWidget_currentRowChanged(int currentRow);

private:
    Ui::ChangeTurnTopForm *ui;
private slots:
	void	ResizeAction();
};

#endif // CHANGETURNTOPFORM_H
