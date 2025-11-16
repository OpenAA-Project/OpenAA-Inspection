#ifndef SHOWMATRIXIMAGECENTERFORM_H
#define SHOWMATRIXIMAGECENTERFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class ShowMatrixImageCenterForm;
}

class ShowMatrixImageCenterForm : public GUIFormBase
{
    Q_OBJECT

	int	CenterX ,CenterY;
public:
    explicit ShowMatrixImageCenterForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowMatrixImageCenterForm();

	void	SetCenter(int x ,int y);
	virtual	void	Prepare(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
private:
    Ui::ShowMatrixImageCenterForm *ui;
};

#endif // SHOWMATRIXIMAGECENTERFORM_H
