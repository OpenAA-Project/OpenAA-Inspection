#ifndef SHOWREVIEWMASTERNAMEFORM_H
#define SHOWREVIEWMASTERNAMEFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ShowReviewMasterNameForm;
}

class ShowReviewMasterNameForm : public GUIFormBase
{
    Q_OBJECT
    
public:
    explicit ShowReviewMasterNameForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowReviewMasterNameForm();

	virtual void	BuildForShow(void)	override;
    virtual	void	Prepare(void)		override;
private slots:
	void	ResizeAction();

private:
    Ui::ShowReviewMasterNameForm *ui;
};

#endif // SHOWREVIEWMASTERNAMEFORM_H
