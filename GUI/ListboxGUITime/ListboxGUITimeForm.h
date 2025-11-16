#ifndef LISTBOXGUITIMEFORM_H
#define LISTBOXGUITIMEFORM_H

#include "XGUIFormBase.h"
#include "ui_ListboxGUITimeForm.h"

class	LayersBase;

class ListboxGUITimeForm : public GUIFormBase
{
	Q_OBJECT

public:
	ListboxGUITimeForm(LayersBase *Base,QWidget *parent = 0);
	~ListboxGUITimeForm();

private:
	Ui::ListboxGUITimeFormClass ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
	
private slots:
	void on_pushButtonUpdate_clicked();
};

#endif // LISTBOXGUITIMEFORM_H
