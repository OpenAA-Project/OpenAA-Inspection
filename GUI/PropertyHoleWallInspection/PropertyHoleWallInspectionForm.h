#ifndef PROPERTYHOLEWALLINSPECTIONFORM_H
#define PROPERTYHOLEWALLINSPECTIONFORM_H

#include <QWidget>
#include <QModelIndex>
#include <QTabBar>
#include "XGUIFormBase.h"
#include "XHoleWallInspection.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyHoleWallInspectionForm;
}

class	AlgorithmLibraryLevelContainer;
class PropertyHoleWallInspectionForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyHoleWallInspectionForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyHoleWallInspectionForm();

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
    void on_tableWidgetBlockInfo_clicked(const QModelIndex &index);
	void	TabBarBlockOnMouseChanged(int);
    void on_pushButtonMakeBitBuff_clicked();

private:
    Ui::PropertyHoleWallInspectionForm *ui;

	HoleWallBase	*GetHoleWallBase(void);

	void	ShowLibList(void);
	void	ShowSelectedLibList(void);
	virtual void	BuildForShow(void)	override;
	virtual void	ShowInEdit	(void)	override;

	AlgorithmLibraryLevelContainer	*LLib;
	int						LibType;

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;

	QTabBar	TabBarBlockOnMouse;
	struct	HoleWallItemWithPageLayer{
		HoleWallItem	*HoleWallInfoOnMouse;
		int			Page;
		int			Layer;
	};	
	struct	HoleWallItemWithPageLayer	BInfo[100];
	void	ShowTab(void);

	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	NPListPack<HoleWallInfoList>	HoleWallInfos;
	void	ShowBlockInfoList(void);
};

class	GUICmdCreateHoleWall : public GUICmdPacketBase
{
public:
	AlgorithmLibraryListContainer	SelectedLibList;
	IntList							LayerList;

	GUICmdCreateHoleWall(LayersBase *Base ,const QString &EmitterRoot,const QString &EmitterName ,int globalPage=-1);

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

#endif // PROPERTYHOLEWALLINSPECTIONFORM_H
