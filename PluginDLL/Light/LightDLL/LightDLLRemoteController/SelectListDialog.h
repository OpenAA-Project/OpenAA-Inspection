#ifndef SELECTLISTDIALOG_H
#define SELECTLISTDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XTypeDef.h"
#include "XDLLType.h"
#include "XDataInLayer.h"
#include "XServiceForLayers.h"

namespace Ui {
class SelectListDialog;
}


class	LightList : public NPList<LightList>
{
public:
	int ID;
	QString Name;
	QString Remark;

	LightList(int id, const QString &name ,const QString &remark)
		:ID(id),Name(name),Remark(remark){}
};

class SelectListDialog : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit SelectListDialog(LayersBase *base ,QWidget *parent = 0);
    ~SelectListDialog();
    
	void	Initial(int LightID);
	void	ShowLightList(void);

	int	LightID;
	NPListPack<LightList>	LightListContainer;

private slots:
    void on_tableWidgetLight_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonCancel_clicked();

    void on_tableWidgetLight_clicked(const QModelIndex &index);

private:
    Ui::SelectListDialog *ui;
};

#endif // SELECTLISTDIALOG_H
