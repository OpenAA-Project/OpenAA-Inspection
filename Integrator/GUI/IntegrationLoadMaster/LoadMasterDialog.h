#ifndef LOADMASTERDIALOG_H
#define LOADMASTERDIALOG_H

#include <QDialog>
#include <QSqlTableModel>
#include <QTableView>
#include "XServiceForLayers.h"
#include <QLabel>

namespace Ui {
class LoadMasterDialog;
}
class	LoadMasterDialog;
class	IntegrationLoadMaster;

class	QSqlLoadMasterModel : public QSqlTableModel
{
	LoadMasterDialog	*ParentWindow;
public:
	QSqlLoadMasterModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;

};

class LoadMasterDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    IntegrationLoadMaster	*ParentGUI;
	QLabel	*TopViewDim;
	int		AllocatedViewCount;

public:
	bool	AcsendantOrder;
	int		OrderMode;		//0:RELATIONCODE,1:REGTIME,2:RELATIONNUMBER,3:RELATIONNAME,4:REMARK

	int	ResultRelationCode;

    explicit LoadMasterDialog(LayersBase *Base,int LastOrderMode,int LastAcsendantOrder,int LastOpenedID,QWidget *parent = 0);
    ~LoadMasterDialog();
    
	QString	GetNameForSearch(void);
	QString	GetNumberForSearch(void);
    QString	GetRemarkForSearch(void);

	void	SelectView(void);
	void	SelectView(int RelationCode);
	int		GetLastRelationCode(void);

private slots:
    void on_pushButtonLoad_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonInputPanel_clicked();
    void on_tableView_clicked(const QModelIndex &index);
    void on_tableView_doubleClicked(const QModelIndex &index);
    void on_lineEditSearchByNumber_textChanged(const QString &arg1);
    void on_lineEditSearchByName_textChanged(const QString &arg1);
    void on_lineEditSearchByRemark_textChanged(const QString &arg1);
    void on_pushButtonInputMasterNumber_clicked();
    void on_pushButtonInputMasterName_clicked();
    void on_pushButtonInputRemark_clicked();
	void	MListSectionClicked ( int logicalIndex );
private:
    Ui::LoadMasterDialog *ui;
};

#endif // LOADMASTERDIALOG_H
