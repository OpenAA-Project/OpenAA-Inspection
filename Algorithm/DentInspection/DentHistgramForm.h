#ifndef DENTHISTGRAMFORM_H
#define DENTHISTGRAMFORM_H

#include <QWidget>
#include <QToolBar>
#include <QToolButton>
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XHistgramByParam.h"
#include "XPasswordQWidget.h"
#include "XDisplaySimPanel.h"

namespace Ui {
class DentHistgramForm;
}
class DentHistgramForm;

class	DentDisplaySimPanel : public DisplaySimPanel
{
	DentHistgramForm	*Parent;
public:
	DentDisplaySimPanel (LayersBase *base ,DentHistgramForm *p ,QWidget *parent = 0);

	virtual	void	GetDrawInformation(QByteArray &Something);

protected:
	virtual	void	ExecuteMouseMove	(int GlobalX ,int GlobalY);
};

class DentHistgramForm : public QWidget,public ServiceForLayers ,public PasswordInQWodget
{
    Q_OBJECT
    int	HistgramPage;
public:
    explicit DentHistgramForm(LayersBase *Base,QWidget *parent = 0);
    ~DentHistgramForm();

	void	Initial(AlgorithmBase *InstBase ,AlgorithmItemIndependentPack &Data);
    void	GetDrawInformation(QByteArray &Something);
	void	ShowResult(double ResultMaxD ,double ResultWaveLen);
private slots:
    void on_ButtonRelrectOnlyBlock_clicked();
    void on_ButtonReflectAllBlocks_clicked();
    void on_ButtonSaveToLibrary_clicked();
    void on_ButtonLoadFromLibrary_clicked();
    void on_ButtonClose_clicked();
    void on_ButtonCalc_clicked();
    void on_pushButtonTransmitItemNameAll_clicked();
    void on_pushButtonChangeLib_clicked();

	void	SlotStartCalc();
	void	SlotLayerClicked();
private:
    Ui::DentHistgramForm *ui;

	DentDisplaySimPanel		SimPanel;
	QToolBar	LayerBar;
	QToolButton	**LButtonList;
	AlgorithmLibraryListContainer	LibIDList;

	AlgorithmItemIndependentPack	*IData;
	AlgorithmBase *InstBase;
	bool	OnChanging;

	void	GetActiveLayerList(IntList &LayerList);
	void	GetDataFromWindow(void);
	void	GetDataFromWindowFromNo(int LayerNo);
	void	ShowLibrary(void);

	int		OldLibID;
	int		NewLibID;
};

class	GUICmdReqDSimPanelMouseMove: public GUICmdPacketBase
{
public:
	int	ItemID;
	int	Layer;
	int GlobalX;
	int GlobalY;

	GUICmdReqDSimPanelMouseMove(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdAckDSimPanelMouseMove: public GUICmdPacketBase
{
public:
	double	ResultMaxD;
	double	ResultWaveLen;

	GUICmdAckDSimPanelMouseMove(LayersBase *Base,const QString &emitterRoot ,const QString &emitterName,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName){}
};

#endif // DENTHISTGRAMFORM_H
