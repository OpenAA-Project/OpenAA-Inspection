#ifndef EDITSCANPHASENUMBER_H
#define EDITSCANPHASENUMBER_H

#include "EditGUILibResource.h"
#include <QDialog>
#include"XParamGlobal.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

namespace Ui {
    class EditScanPhaseNumber;
}

class	EditScanPhaseNumber;

class	ScanPhaseNumberGrid : public WMultiGrid
{
	EditScanPhaseNumber	*EParent;

public:
	ScanPhaseNumberGrid(EditScanPhaseNumber *eParent ,QWidget * parent=0):WMultiGrid(parent),EParent(eParent){}

protected:
	virtual	void	ChangeValue(int row ,int col,const QVariant &value)	override;
	virtual	void	GetValue(int row ,int col,QVariant &value)			override;
};

class EditScanPhaseNumber : public QWidget ,public ServiceForLayers
{
    Q_OBJECT

	ScanPhaseNumberGrid	aGrid;
public:
    explicit EditScanPhaseNumber(LayersBase *Base,QWidget *parent = 0);
    ~EditScanPhaseNumber();

	void	SetGrid(void);
	void	Show(void);

public slots:
	void	ChangeValue();

signals:
	void	Reflect();
	void	ChangedValue();

private slots:
    void on_pushButtonCancel_clicked();
    void on_pushButtonOK_clicked();

private:
    Ui::EditScanPhaseNumber *ui;
};

#endif // EDITSCANPHASENUMBER_H
