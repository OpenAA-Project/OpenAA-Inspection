#ifndef LEARNINGSERVER_H
#define LEARNINGSERVER_H

#include <QMainWindow>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include "ui_LearningServer.h"
#include "XServerLayerBase.h"
#include "XServiceForLayers.h"
#include <QTcpServer>
#include <QTcpSocket>
#include "NList.h"
#include "XServerComm.h"
#include "mtToolButtonColored.h"
#include "XImageExpand.h"

class	LearningServer;
class ThreadServer;
class ConfirmForm;
class LearningInDB;
class LearningParamInDB;
class DetailResultInfoListContainer;
class AlgorithmComponentWindow;

class	QSqlLearningModel : public QSqlTableModel
{
public:
	QSqlLearningModel(QObject * parent, QSqlDatabase db);
	QString selectStatement () const;
};

class LabelWithRightButton : public QLabel
{
	Q_OBJECT
public:
	LabelWithRightButton(QWidget *parent);

signals:
	void	SignalRClicked(int x ,int y);
	void	SignalLClicked(int x ,int y);
private:
	virtual	void mouseReleaseEvent(QMouseEvent *ev)	override;
};


class LearningServer : public QMainWindow,public ServiceForLayers
{
	Q_OBJECT

	friend	class ConfirmForm;

	mtToolButtonColored		ButtonR,ButtonG,ButtonB;
	ServerEntryPoint		*EPointForDraw;
	ServerLayerBase			*LayerForDraw;
	QImage					MasterImage;
	QImage					TargetImage;
	LabelWithRightButton	TargetPanel;
	double					ZoomRate;
	int						LastY;

	ServerEntryPoint		*EPointForCalc;
	ServerLayerBase			*LayerForCalc;
	int						SelectedLearningID;
	int						LastLearningID;
	int						LastLibType;
	int						LastLibID;
	std::shared_ptr<ShrinkingPackContainer>	ShrinkingPackContainerInstance;

	QTcpServer				Server;
	NPListPack<LearningServerSocket>	SocketPack;
	ThreadServer			*Executer;
	AlgorithmThresholdPointerPointerContainer	AlgorithmThresholdPP;
	AlgorithmItemIndependentPack *IndependentPackData;
	ConfirmForm				*ConfirmFormInst;
	AlgorithmComponentWindow	*CurrentAlgoWindow;
public:
	LearningServer(LayersBase *base ,bool StartRun ,QWidget *parent = 0, Qt::WindowFlags flags = Qt::Widget);
	~LearningServer();

	void	RemoveSocket(LearningServerSocket *s);
	QByteArray	GetLibData(int LibType, int LibID);

	bool		CheckLearningListInDB(void);
	void	StopExecute(void);
	void	StartExecute(void);

	QImage	MakeImage(ImageBuffer *Buff[] ,LayersBase *Base ,int LayerNumb ,int Width ,int Height);
	int		ExecuteProcess(LearningInDB *LearningInDBPoint,LearningParamInDB *Param
							,DetailResultInfoListContainer &RetList);
	bool	SetThreshold(int LibType,int LibID,QByteArray &ItemData);
	void	SetItemDataInWindow(LearningInDB *LearningInDBPoint,LearningParamInDB *From);

	void	EditItem(int LearningID);
	void    RemoveItem(int LearningID);
private:
	Ui::LearningServerClass ui;

	void	ShowLearning(int LearningID);
	void	ShowLibrary(int LearningID);
	void	ExecuteLine(int LearningID);
	void	ExecuteItem(int LearningID ,int LibType,int LibID,QByteArray &ParamData);
	void	ShowLibraryMap(int LibType,int LibID);
	virtual	void	resizeEvent ( QResizeEvent * event )	override;

private slots:
	void on_tableViewRegisteredData_clicked(const QModelIndex &);
	void on_pushButtonSetting_clicked();
	void on_pushButtonClose_clicked();
    void on_tableViewRegisteredData_doubleClicked(const QModelIndex &index);
    void on_tableWidgetLibrary_doubleClicked(const QModelIndex &index);
	void	SlotEditLine();
	void	SlotDeleteLine();
	void	SlotExecuteLine();
	void	SlotDeleteItem();
	void	SlotExecuteItem();
    void on_tableWidgetLibrary_clicked(const QModelIndex &index);

	void	SlotNewConnection();
	void	SlotRClickedTargetPanel(int x ,int y);
	void	SlotSaveImage();
    void on_pushButtonSaveImage_clicked();
    void on_pushButtonBackup_clicked();
    void on_pushButtonRestore_clicked();
    void on_pushButtonUpdate_clicked();
    void on_pushButtonExecute_clicked();
	void	SlotShowList();
	void	SlotShowImage();
	void	SlotUpdateList();

    void on_tableWidgetAlgorithmThreshold_clicked(const QModelIndex &index);
    void on_tableWidgetExecuter_doubleClicked(const QModelIndex &index);
    void on_tableWidgetAlgorithmThreshold_cellDoubleClicked(int row, int column);

private:
	void	ShowConnection(void);
};

#endif // LEARNINGSERVER_H
