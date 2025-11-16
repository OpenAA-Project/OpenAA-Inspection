#ifndef SELECTOBJECTFORM_H
#define SELECTOBJECTFORM_H

#include <QDialog>
#include <QTreeWidgetItem>
#include "XTypeDef.h"

namespace Ui {
    class SelectObjectForm;
}

class SelectObjectForm : public QDialog
{
    Q_OBJECT
	QWidget *StartObject;
public:
    explicit SelectObjectForm(QWidget *_StartObject, QWidget *parent = 0);
    ~SelectObjectForm();

	QString	SelectedObjPath;
	int32	ControlMode;
private slots:
    void on_pushButtonSelect_clicked();

    void on_pushButtonCancel_clicked();

    void on_treeWidget_currentItemChanged(QTreeWidgetItem *current, QTreeWidgetItem *previous);

private:
    Ui::SelectObjectForm *ui;

	bool	SetObjectText(int Index,QTreeWidgetItem *ThisTree,QObject *thisObj);
	void	AddChild(int Index,QTreeWidgetItem *ParentTree,QObject *ParentObject);
	QString	GetSelectedObjPath(QObject *d);
	QObject *GetChildObject(const QStringList &ObjList ,int Index ,QObject *CurrentObject);
};

#endif // SELECTOBJECTFORM_H
