#ifndef FORMCOMMSETTING_H
#define FORMCOMMSETTING_H

#include <QWidget>
#include"XParamGlobal.h"
#include "WMultiGrid.h"
#include "XServiceForLayers.h"

namespace Ui {
class FormCommSetting;
}

class	FormCommSetting;

class	ConnectionGrid : public WMultiGrid
{
    Q_OBJECT

    FormCommSetting *RootParent;
public:

    ConnectionGrid(FormCommSetting *root,QWidget * parent=0):WMultiGrid(parent),RootParent(root){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
    virtual	void	selectRowX(int row)                                 override;
signals:
    void	ChangedData();
};

class	GlobalCameraNoGrid : public WMultiGrid
{
    FormCommSetting	*RootParent;
public:

    GlobalCameraNoGrid(FormCommSetting	*root,QWidget * parent=0):WMultiGrid(parent),RootParent(root){}

protected:
    virtual	void	ChangeValue(int row ,int col,const QVariant &value) override;
    virtual	void	GetValue(int row ,int col,QVariant &value)          override;
};


class FormCommSetting : public QWidget, public ServiceForLayers
{
    friend	class	ConnectionGrid;
    friend	class	GlobalCameraNoGrid;
    Q_OBJECT
    
public:
    explicit FormCommSetting(LayersBase *Base ,QWidget *parent = 0);
    explicit FormCommSetting(LayersBase *Base ,ParamComm *RefData ,QWidget *parent = 0);
    ~FormCommSetting();

    void	SetGrid(void);
    void	ShowLocalCameraGrid(void);

    int		GetConnectionIndex();
    void	LoadFromWindow(void);
    void	Show(void);

signals:
    void	SignalClose();
private slots:
    void on_SpinBoxThisCamCount_valueChanged(int arg1);
    void on_CheckBoxMastered_stateChanged(int arg1);
    void on_OKButton_clicked();
    void on_CancelButton_clicked();
    void on_SpinBoxMaxSlaveNumb_valueChanged(int arg1);

    void	ChangedData();

    void on_pushButtonShowCommError_clicked();

private:
    Ui::FormCommSetting *ui;

    ParamComm	TmpLocalData;
    ParamComm	&LocalData;
    ConnectionGrid		dGrid;
    GlobalCameraNoGrid	aGrid;
    bool			BeforeInitialized;
    virtual	void closeEvent ( QCloseEvent * event )	override;
};

#endif // FORMCOMMSETTING_H
