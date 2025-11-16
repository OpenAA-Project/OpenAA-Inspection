#ifndef LISTRESULTFRAMEFORM_H
#define LISTRESULTFRAMEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"


namespace Ui {
class ListResultFrameForm;
}

class ListResultFrameForm : public GUIFormBase
{
    Q_OBJECT

public:
    explicit ListResultFrameForm(LayersBase *base ,QWidget *parent = 0);
    ~ListResultFrameForm();

	virtual void	Prepare(void)	override;
	
private slots:
	void	ResizeAction();

private:
    Ui::ListResultFrameForm *ui;
};

#endif // LISTRESULTFRAMEFORM_H
