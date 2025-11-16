#ifndef PROPERTYLINEPATTERNFORM_H
#define PROPERTYLINEPATTERNFORM_H

#include <QWidget>
#include <QModelIndex>
#include <QTabBar>
#include "XGUIFormBase.h"
#include "XStandardPropertyForm.h"
#include "XGUIPacketForDLL.h"
#include "XAlgorithmLibrary.h"
#include "XLinePatternInspection.h"
#include "XLinePatternPacket.h"

namespace Ui {
class PropertyLinePatternForm;
}

class PropertyLinePatternForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT

public:
    explicit PropertyLinePatternForm(LayersBase *Base ,QWidget *parent = 0);
    ~PropertyLinePatternForm();

	virtual	void	BuildForShow(void)	override;
	virtual	void	ShowInEdit(void)	override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;

private slots:
    void on_ButtonLibSave_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_tableWidgetGeneratedLibList_clicked(const QModelIndex &index);
    void on_tableWidgetLibList_doubleClicked(const QModelIndex &index);
    void on_ButtonGenerateLibs_clicked();
    void on_pushButtonEditLibrary_clicked();
    void on_toolButtonLibrary_clicked();
    void on_toolButtonCreateBlock_clicked();
    void on_tableWidgetBlockInfo_clicked(const QModelIndex &index);
    void on_pushButtonSetFrom_clicked();
    void on_pushButtonGetBack_clicked();
    void on_pushButtonSetFromAll_clicked();
    void on_pushButtonGetBackAll_clicked();
    void on_pushButtonEditLibFolder_clicked();
    void on_tableWidgetGeneratedLibList_doubleClicked(const QModelIndex &index);
	void	TabBarBlockOnMouseChanged(int);
	void	MListSectionClicked ( int logicalIndex );
    void on_toolButtonArea_clicked();
    void on_toolButtonInside_clicked();
    void on_toolButtonOutside_clicked();
    void on_comboBoxResultAngleNumber_currentIndexChanged(int index);

private:
    Ui::PropertyLinePatternForm *ui;

	//LinePatternLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;
	void	ShowLibrary(AlgorithmLibraryLevelContainer &data);
	void	ShowSelectedLibList(void);

	void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer &data);
	void	ShowLibList(void);

	AlgorithmLibraryListContainer	LibList;
	int		LibFolderID;
	AlgorithmLibraryListContainer	SelectedLibList;

	LinePatternBase	*GetLinePatternBase(void);
	void	ShowListGrid(void);

	LinePatternListForPacketPack	LinePatternItemList;

	enum	KindOfSort
	{
		KOS_ID_Up
		,KOS_ID_Dn
		,KOS_Name_Up
		,KOS_Name_Dn
	}LibSortType;
	QTabBar	TabBarBlockOnMouse;

	struct	BlockItemWithPageLayer{
		LinePatternItem	*BlockInfoOnMouse;
		int			Page;
		int			Layer;
	};

	struct	BlockItemWithPageLayer	BInfo[100];
	void		ShowBlockInfoList(void);
	void		ShowTab(void);

	NPListPack<BlockInfoList>	BlockInfos;
};

#endif // PROPERTYLINEPATTERNFORM_H
