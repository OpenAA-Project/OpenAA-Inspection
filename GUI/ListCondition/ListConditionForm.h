#ifndef LISTCONDITIONFORM_H
#define LISTCONDITIONFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include <QPushButton>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ListConditionForm;
}

class ListConditionForm : public GUIFormBase
{
    Q_OBJECT
    
	QStringList		FileNames;

public:
    explicit ListConditionForm(LayersBase *Base ,QWidget *parent = 0);
    ~ListConditionForm();
    
	virtual	void	Prepare(void)	override;

private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonSelect_clicked();
    void on_listWidgetConditions_doubleClicked(const QModelIndex &index);
    void on_pushButtonUpdate_clicked();

private:
    Ui::ListConditionForm *ui;

	bool	Save(QIODevice *f);
	bool	Load(QIODevice *f);
};

#endif // LISTCONDITIONFORM_H
