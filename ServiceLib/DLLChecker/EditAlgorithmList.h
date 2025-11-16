#ifndef EDITALGORITHMLIST_H
#define EDITALGORITHMLIST_H

#include <QWidget>
#include "ui_EditAlgorithmList.h"
#include "XServiceForLayers.h"
#include "WMultiGrid.h"
#include "XBoolList.h"

class	EditAlgorithmList;
class	AlgoGrid : public WMultiGrid,public ServiceForLayers
{
	EditAlgorithmList	*MParent;
public:
	AlgoGrid(LayersBase *Base,EditAlgorithmList *mParent,QWidget * parent=0)
		:WMultiGrid(parent),ServiceForLayers(Base),MParent(mParent){}

	virtual	void	ChangeValue(int row ,int col,const QVariant &value);
	virtual	void	GetValue(int row ,int col,QVariant &value);
};


class EditAlgorithmList : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	EditAlgorithmList(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~EditAlgorithmList();

	BoolList	EffectiveList;

private:
	Ui::EditAlgorithmListClass ui;

	AlgoGrid	WTable;

signals:
	void	SignalClose();

private slots:
	void on_pushButtonCancel_clicked();
	void on_pushButtonSave_clicked();

};

#endif // EDITALGORITHMLIST_H
