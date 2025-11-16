#ifndef DEFINESHORTCUTKEYDIALOG_H
#define DEFINESHORTCUTKEYDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include <QPushButton>

struct	ShortcutKeyInfoList;

namespace Ui {
class DefineShortcutKeyDialog;
}


class DefineShortcutKeyDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT

	struct	ShortcutKeyInfoList	 *ShortcutKeyDim;
	int		CountOfShortcut;
public:
    explicit DefineShortcutKeyDialog(struct	ShortcutKeyInfoList	 _ShortcutKeyDim[] , int _CountOfShortcut ,LayersBase *base,QWidget *parent = 0);
    ~DefineShortcutKeyDialog();

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonSaveFile_clicked();
    void on_pushButtonLoadFile_clicked();

private:
    Ui::DefineShortcutKeyDialog *ui;

	void StoreDataFromWindow(struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);
	void ShowDataToWindow	(struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);

	bool	SaveToFile  (QIODevice *f , struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);
	bool	LoadFromFile(QIODevice *f , struct ShortcutKeyInfoList tShortcutKeyDim[] , int tCountOfShortcut);
};


class	CellInComponentControl : public QPushButton
{
    Q_OBJECT
public:
	DefineShortcutKeyDialog	*Parent;
	int	Row;
	QString		DLLRoot;
	QString		DLLName;
	QString		DLLInst;
	QString		ObjPath;
	QString		ObjName;

	CellInComponentControl(DefineShortcutKeyDialog *p ,int row);
	
	void	Set( const QString &DLLRoot
				,const QString &DLLName
				,const QString &DLLInst
				,const QString &ObjPath
				,const QString &ObjName);
	
private slots:
	void	SlotClicked();
};

#endif // DEFINESHORTCUTKEYDIALOG_H
