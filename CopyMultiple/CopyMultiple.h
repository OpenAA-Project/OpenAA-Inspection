#ifndef COPYMULTIPLE_H
#define COPYMULTIPLE_H

#include <QMainWindow>
#include <QPushButton>
#include "ui_CopyMultiple.h"
#include "WMultiGrid.h"
#include "XCopyMultiple.h"

class	FolderListButton : public QPushButton
{
    Q_OBJECT
public:

	FolderListButton(QWidget *parent = 0);
	~FolderListButton();

private slots:
	void ButtonClick();
};

class	CopyMultiple;
class	IndicatorWindow;


class	DestinationList : public WMultiGrid
{
	CopyMultiple	*Parent;
    Q_OBJECT
public:
	DestinationList(CopyMultiple *parent = 0);

	virtual	void	ChangeValue(int row ,int col,const QVariant &value);
	virtual	void	GetValue(int row ,int col,QVariant &value);
signals:
	void	Changed();


};

class CopyMultiple : public QMainWindow
{
	Q_OBJECT

	static	char	*DefaultFileName;
public:
	CopyMultiple(QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~CopyMultiple();

	DestinationList		dGrid;
	CopyMultipleData	Data;
	IndicatorWindow	*Indicator;

	virtual	void showEvent ( QShowEvent * event )	override;
	virtual	void closeEvent ( QCloseEvent * event )	override;
	void setDestination ();

private slots:
        void on_pushButtonSourcePath_clicked();
        void on_pushButtonLoadFilter_clicked();
        void on_pushButtonSaveFilter_clicked();
        void on_pushButtonStartCopy_clicked();
		void	SlotClickedXYButton( int row ,int col);
		void	SlotFinishCopy();
        void on_pushButtonAllFiles_clicked();
        void on_pushButtonForRelease_clicked();
		void on_pushButtonAllClear_clicked();
        void on_pushButtonStopCopy_clicked();

private:
	Ui::CopyMultipleClass ui;

	void StoreFilterToWindow(void);
	void LoadFilterFromWindow(void);
};

#endif // COPYMULTIPLE_H
