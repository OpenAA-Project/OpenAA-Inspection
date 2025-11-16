#ifndef SHOWCURRENTLIGHTNAMEFORM_H
#define SHOWCURRENTLIGHTNAMEFORM_H

#include "XGUIFormBase.h"

namespace Ui {
class ShowCurrentLightNameForm;
}

class ShowCurrentLightNameForm : public GUIFormBase
{
    Q_OBJECT

public:
	QFont	CFont;

    explicit ShowCurrentLightNameForm(LayersBase *base ,QWidget *parent = 0);
    ~ShowCurrentLightNameForm();

	virtual void	Prepare		(void) override;
	virtual void	ShowInEdit	(void) override;
private slots:
		void	ResizeAction();
private:
    Ui::ShowCurrentLightNameForm *ui;
};

#endif // SHOWCURRENTLIGHTNAMEFORM_H
