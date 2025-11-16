#ifndef PROPERTYEULERRINGL1FORM_H
#define PROPERTYEULERRINGL1FORM_H

#include <QModelIndex>
#include "XGUIFormBase.h"
#include "XEulerRingL1.h"
#include "XStandardPropertyForm.h"
#include <QTabBar>

namespace Ui {
class PropertyEulerRingL1Form;
}

class PropertyEulerRingL1Form : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyEulerRingL1Form(LayersBase *Base,QWidget *parent = 0);
    ~PropertyEulerRingL1Form();

	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;

private slots:
    void on_toolButtonLibrary_clicked();
    void on_toolButtonCreateBlock_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_ButtonLibSave_clicked();
    void on_tableWidgetBlockInfo_cellClicked(int row, int column);
	void	TabBarBlockOnMouseChanged(int);

private:
    Ui::PropertyEulerRingL1Form *ui;
	EulerRingL1Base	*GetEulerRingL1Base(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit	(void)	override;

	//EulerRingL1Library	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	QTabBar	TabBarBlockOnMouse;
	struct	EulerRingL1ItemWithPageLayer{
		EulerRingL1Item	*EulerRingL1InfoOnMouse;
		int			Page;
		int			Layer;
	};	
	struct	EulerRingL1ItemWithPageLayer	BInfo[100];
	void	ShowTab(void);

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	NPListPack<EulerRingL1InfoList>	EulerRingL1Infos;
	void	ShowBlockInfoList(void);
};


class	GUICmdCreateEulerRingL1 : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	IntList							LayerList;

	GUICmdCreateEulerRingL1(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

class	GUICmdSetDrawing : public GUICmdPacketBase
{
public:
	QString	InstName;

	GUICmdSetDrawing(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

	virtual	bool	Load(QIODevice *f);
	virtual	bool	Save(QIODevice *f);

	virtual	void	Receive(int32 localPage, int32 cmd ,QString &EmitterRoot,QString &EmitterName);	
};

#endif // PROPERTYEULERRINGL1FORM_H
