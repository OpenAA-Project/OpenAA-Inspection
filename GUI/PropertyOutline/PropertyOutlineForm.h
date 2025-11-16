#ifndef PROPERTYOUTLINEFORM_H
#define PROPERTYOUTLINEFORM_H

#include "XGUIFormBase.h"
#include <QModelIndex>
#include <QTabBar>
#include "XDisplayImagePacket.h"
#include "XOutlineInspect.h"
#include "XPropertyOutlinePacket.h"
#include "ShowRGBCube.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyOutlineForm;
}

class PropertyOutlineForm : public GUIFormBase, public StandardPropertyForm
{
    Q_OBJECT
    
public:
    explicit PropertyOutlineForm(LayersBase* Base, QWidget *parent = 0);
    ~PropertyOutlineForm();

    virtual	void	TransmitDirectly(GUIDirectMessage* packet)	override;
    virtual void	ShowInEdit(void)	override;
    virtual void	BuildForShow(void)	override;
    virtual void	StartPage(void)		override;

private slots:
    void on_toolButtonLibrary_clicked();
    void on_toolButtonCreateBlock_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
    void on_toolButtonArea_clicked();
    void on_toolButtonEdge_clicked();
    void on_toolButtonInside_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_ButtonPickupTest_clicked();
    void on_ButtonPickupClearTest_clicked();
    void on_ButtonGenerateLibs_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetBlockInfo_clicked(const QModelIndex &index);
    void on_radioButtonInsideStable_toggled(bool checked);
    void on_radioButtonInsideTrans_toggled(bool checked);
    void on_radioButtonOutsideStable_toggled(bool checked);
    void on_radioButtonOutsideTrans_toggled(bool checked);
    void on_pushButtonInsideColor_clicked();
    void on_pushButtonOutsideColor_clicked();
    void on_radioButtonInsideBStable_toggled(bool checked);
    void on_radioButtonInsideBTrans_toggled(bool checked);
    void on_radioButtonOutsideBStable_toggled(bool checked);
    void on_radioButtonOutsideBTrans_toggled(bool checked);
    void on_pushButtonInsideBColor_clicked();
    void on_pushButtonOutsideBColor_clicked();
    void	TabBarBlockOnMouseChanged(int);

    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();

private:
    Ui::PropertyOutlineForm *ui;

    //OutlineInspectLibrary* TempLib;
	AlgorithmLibraryLevelContainer* TempLib;
    int		LibType;
    void	ShowLibrary(AlgorithmLibraryLevelContainer& data);
    void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer& data);
    void	ShowSelectedLibList(void);
    void	ShowLibList(void);
    virtual	void	SetLibFolder(int LibFolderID, const QString& LinFolderName)	override;
    void	SetLayersFromLib(IntList& Layers);

    AlgorithmLibraryListContainer	LibList;
    AlgorithmLibraryListContainer	SelectedLibList;
    int		LibFolderID;
    OutlineBase* GetOutlineBase(void);
    QTabBar	TabBarBlockOnMouse;

    ShowRGBSpace	ColorGenerator;
    ShowRGBSpace	ColorInside;
    ShowRGBSpace	ColorOutside;
    ShowRGBSpace	TrColorInside;
    ShowRGBSpace	TrColorOutside;

    ShowRGBSpace	ColorBInside;
    ShowRGBSpace	ColorBOutside;
    ShowRGBSpace	TrColorBInside;
    ShowRGBSpace	TrColorBOutside;

    struct	OutlineItemWithPageLayer {
        OutlineItem* OutlineInfoOnMouse;
        int			Page;
        int			Layer;
    };

    struct	OutlineItemWithPageLayer	BInfo[100];
    void		ShowBlockInfoList(void);
    void		ShowTab(void);

    NPListPack<OutlineInfoList>	OutlineInfos;
    FlexArea	GlobalPickupArea;

    virtual	bool	SaveContent(QIODevice* f)	override;
    virtual	bool	LoadContent(QIODevice* f)	override;
};

#endif // PROPERTYOUTLINEFORM_H
