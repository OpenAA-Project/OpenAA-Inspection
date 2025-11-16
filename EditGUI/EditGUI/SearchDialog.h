#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "NList.h"
#include "XGUI.h"
#include "XServiceForLayers.h"

namespace Ui {
class SearchDialog;
}

class	GUINameClassifiedPointer : public NPList<GUINameClassifiedPointer>
{
public:
	GUINameClassified	*GUIItemPointer;

	GUINameClassifiedPointer(GUINameClassified *v):GUIItemPointer(v){}
};



class SearchDialog : public QDialog ,public ServiceForLayers
{
    Q_OBJECT

	NPListPack<GUINameClassifiedPointer>	PointerList;
public:
    explicit SearchDialog(LayersBase *base ,QWidget *parent = 0);
    ~SearchDialog();

private slots:
    void on_listWidgetRootList_clicked(const QModelIndex &index);
    void on_pushButtonSearcg_clicked();
    void on_tableWidgetComponents_doubleClicked(const QModelIndex &index);
    void on_pushButtonSelect_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::SearchDialog *ui;

	void ShowGUIItemGrid(void);
};

#endif // SEARCHDIALOG_H
