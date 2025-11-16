#ifndef PIXELLIBRARYMANAGER_H
#define PIXELLIBRARYMANAGER_H

#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include "ui_PixelLibraryManager.h"
#include "XServiceForLayers.h"

class PixelLibraryManager : public QWidget,public ServiceForLayers
{
	Q_OBJECT

public:
	PixelLibraryManager(LayersBase *Base,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~PixelLibraryManager();

private slots:
	void	twPixelLibraryListDoubleClicked(const QModelIndex &Index);
	void	twPixelLibraryListCurrentCellChanged(int currentRow,int currentColumn,int previousRow,int previousColumn);

	void	cmbPixelLibraryNameListCurrentIndexChanged(int Index);
	void	cmbLibraryNameListCurrentIndexChanged(int Index);
	void	cmbUniqueNameListCurrentIndexChanged(int Index);

	void	pbSaveClicked();
	void	pbUpdateClicked();
	void	pbLoadClicked();
	void	pbAddRowClicked();
	void	pbDeleteRowClicked();
	void	pbCloseClicked();

private:
	Ui::PixelLibraryManagerClass ui;

	QComboBox	*cmbPixelLibraryNameList;
	QComboBox	*cmbAlgorithmNameList;
	QComboBox	*cmbLibraryNameList;
	QComboBox	*cmbUniqueNameList;
	QSpinBox	*sbPriority;

	QStringList	TableColHeader;
	QStringList	TableRowHeader;
	QStringList	PixelLibraryIDList;
	QStringList	PixelLibraryNameList;
	QStringList	AlgorithmListName;
	QStringList	LibraryIDList;
	QStringList	LibraryNameList;
	QStringList	UniqueNameList[1];

	int		NowRow;
	QString NowFileName;

	typedef	enum	_UniqueType{
		_DynamicClassify	=0
	}UniqueType;

	void	CreateTable();
	void	CreatePixelLibraryNameList();
	void	CreateAlgorithmNameList();
	bool	CreateLibraryNameList(int Row);
	bool	CreateUniqueNameList(int Row);
	void	CreatePriority();

	bool	SaveFile(const QString &FileName);
	bool	CheckLoadData(int Row,int Col,const QStringList &myStringList,QString &Msg);
	void	SetDataToTable(QTableWidget *W,int row,int col,QVariant value);
};

#endif // PIXELLIBRARYMANAGER_H
