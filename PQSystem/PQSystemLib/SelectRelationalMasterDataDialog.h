#ifndef SELECTRELATIONALMASTERDATADIALOG_H
#define SELECTRELATIONALMASTERDATADIALOG_H

#include <QDialog>
#include <QLabel>
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"

namespace Ui {
class SelectRelationalMasterDataDialog;
}

class	SelectRelationalMasterDataDialog;

class	QSqlLoadMasterModel : public QSqlTableModel
{
	SelectRelationalMasterDataDialog	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class SelectRelationalMasterDataDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
      
	QLabel	*TopViewDim;
	int		AllocatedViewCount;  
public:
	bool	AcsendantOrder;
	int		OrderMode;		//0:RELATIONCODE,1:REGTIME,2:RELATIONNUMBER,3:RELATIONNAME,4:REMARK

	int	ResultRelationCode;
	
	explicit SelectRelationalMasterDataDialog(LayersBase *Base,int LastOrderMode,int LastAcsendantOrder,int LastOpenedID,QWidget *parent = 0);
    ~SelectRelationalMasterDataDialog();
 
	QString	GetNameForSearch(void);
	QString	GetNumberForSearch(void);
	QString	GetRemarkForSearch(void);

	void	SelectView(void);
	void	SelectView(int RelationCode);

private slots:
    void on_pushButtonLoad_clicked();
    void on_pushButtonCancel_clicked();
    void on_lineEditSearchByNumber_textChanged(const QString &arg1);
    void on_lineEditSearchByName_textChanged(const QString &arg1);
    void on_lineEditSearchByRemark_textChanged(const QString &arg1);
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);
	void	MListSectionClicked ( int logicalIndex );

private:
    Ui::SelectRelationalMasterDataDialog *ui;
};

#endif // SELECTRELATIONALMASTERDATADIALOG_H
