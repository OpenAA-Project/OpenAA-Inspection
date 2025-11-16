#ifndef SHOWCHECKEVERYDAYFORM_H
#define SHOWCHECKEVERYDAYFORM_H

#include <QDialog>
#include "XCheckEveryday.h"
#include "XStandardPropertyForm.h"
#include "XGUIFormBase.h"

namespace Ui {
class ShowCheckEverydayForm;
}

class ShowCheckEverydayForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    bool    UpdateInEveryInspection;
    explicit ShowCheckEverydayForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowCheckEverydayForm();
    
	CheckEverydayBase	*GetCheckEverydayBase(void);
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	Prepare(void)	override;
	virtual void	ShowInPlayer		(int64 shownInspectionID=-1)    override;
private slots:
    void on_pushButtonUpdate_clicked();
	void	ResizeAction();
private:
    Ui::ShowCheckEverydayForm *ui;
};

#endif // SHOWCHECKEVERYDAYFORM_H
