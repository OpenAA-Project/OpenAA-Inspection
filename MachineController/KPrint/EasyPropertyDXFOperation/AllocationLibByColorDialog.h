#ifndef ALLOCATIONLIBBYCOLORDIALOG_H
#define ALLOCATIONLIBBYCOLORDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "mtPushButtonColored.h"
#include "XIntegrationPacketComm.h"
#include "XDXFOperationCommon.h"
#include "XAllocationLibByColor.h"

namespace Ui {
class AllocationLibByColorDialog;
}
class	GeneralLibFolderForm;
class	DXFOperationBase;
class	DotColorMatchingBase;
class	CartonMenuForm;
class	EasyPropertyDXFOperationForm;

class AllocationLibByColorDialog : public QDialog,public ServiceForLayers
{
    Q_OBJECT
    
	EasyPropertyDXFOperationForm	*Parent;
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;
public:
    explicit AllocationLibByColorDialog(EasyPropertyDXFOperationForm *p,LayersBase *Base ,QWidget *parent = 0);
    ~AllocationLibByColorDialog();
    
private slots:
    void on_horizontalSliderEasyThreshold_valueChanged(int value);
    void on_pushButtonOK_clicked();
    void on_pushButtonFromDXF_clicked();
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
	void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::AllocationLibByColorDialog *ui;

	GeneralLibFolderForm	*pLibFolderForm;
	int		LibFolderID;
	int		LibType;
	AlgorithmLibraryListContainer	LibList;

	void ShowAllocation(void);
	DXFOperationBase		*GetDXFOperationBase(void);
	DotColorMatchingBase	*GetDotColorMatchingBase(void);
	void	ShowSelectedLibList(void);

	void	ReqAllocationLibByColorContainer(int LevelID);
};

class	ColotButtonInList : public mtPushButtonColored
{
    Q_OBJECT

public:
	int	Row;
	ColotButtonInList(int row ,QWidget *parent = 0);

signals:
	void	SignalClicked(int row);
private slots:
	void	SlotClicked();
};

//========================================================================================================

class	IntegrationCmdReqAllocationLibByColor: public IntegrationCmdPacketBase
{
public:
	int		LevelID;
	IntegrationCmdReqAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdAckAllocationLibByColor: public IntegrationCmdPacketBase
{
public:
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;

	IntegrationCmdAckAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	

private:

};

class	IntegrationCmdSetAllocationLibByColor: public IntegrationCmdPacketBase
{
public:
	int		LevelID;
	AllocationLibByColorContainer	AllocationLibByColorContainerInst;

	IntegrationCmdSetAllocationLibByColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);

private:

};

class	IntegrationCmdReqDXFColor: public IntegrationCmdPacketBase
{
public:
	int		LevelID;
	IntegrationCmdReqDXFColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName);	

private:

};

class	IntegrationCmdAckDXFColor: public IntegrationCmdPacketBase
{
public:
	ColorCodeListContainer	ColorList;

	IntegrationCmdAckDXFColor(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int SlaveNo=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 slaveNo, int cmd ,QString &EmitterRoot,QString &EmitterName){}	

private:

};


#endif // ALLOCATIONLIBBYCOLORDIALOG_H
