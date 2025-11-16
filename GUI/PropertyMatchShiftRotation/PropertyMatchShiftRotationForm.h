#ifndef PROPERTYMATCHSHIFTROTATIONFORM_H
#define PROPERTYMATCHSHIFTROTATIONFORM_H

#include <QWidget>
#include "XGUIFormBase.h"
#include "WMultiGrid.h"
#include "XPropertyMatchShiftRotationPacket.h"
#include "XMatchShiftRotation.h"
#include "XMatchShiftRotationLibrary.h"
#include "XStandardPropertyForm.h"

namespace Ui {
class PropertyMatchShiftRotationForm;
}

class PropertyMatchShiftRotationForm : public GUIFormBase,public StandardPropertyForm
{
    Q_OBJECT
	MatchShiftRotationAreaListPack			AreaList;
	MatchShiftRotationItemListPack			ItemInfos;
	FlexAreaImageListCoeffAngleContainer	CurrentPatterns;
public:
    explicit PropertyMatchShiftRotationForm(LayersBase *Base,QWidget *parent = 0);
    ~PropertyMatchShiftRotationForm();

	virtual	void	Prepare(void) override;
	virtual	void	TransmitDirectly(GUIDirectMessage *packet) override;
	virtual	void	BuildForShow(void) override;
	virtual void	SetupLibFolder(int LibFolderID,int originalLibFolder) override;
	void	ShowInEdit(void) override;
	void	CreateAndShowPointGrid(void);
	virtual void	StartPage	(void) override;

	void	CreateAlignmentArea(FlexArea &area);
	void	CreateAlignmentPoint(FlexArea &area ,int MoveDot);
	void	GenerateAreaFromMask(int ItemLibID);
	void	ClearLibList(void);
	void	SetLib(int LibID);
	void	SelectModeType(int ModeType);
    
	struct	BlockItemWithPage{
		MatchShiftRotationItem	*MatchShiftRotationInfoOnMouse;
		int			Page;
	};

private slots:
    void on_tableWidgetPartList_clicked(const QModelIndex &index);
    void on_tableWidgetPartList_doubleClicked(const QModelIndex &index);
    void on_tableWidgetMarkList_clicked(const QModelIndex &index);
    void on_tableWidgetMarkList_doubleClicked(const QModelIndex &index);
    void on_toolButtonPart_clicked();
    void on_toolButtonMark_clicked();

    void on_pushButtonEditLibFolder_clicked();
    void on_pushButtonEditLibrary_clicked();

    void on_listWidgetAngleList_clicked(const QModelIndex &index);

private:
    Ui::PropertyMatchShiftRotationForm *ui;

	//MatchShiftRotationLibrary	*TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
	int		LibType;

	void	ShowAreaGrid(void);
	void	ShowMarkList(void);

	virtual	void	SetLibFolder(int LibFolderID ,const QString &LinFolderName)	override;
	void	SetLayersFromLib(IntList &Layers);

	AlgorithmLibraryListContainer	LibList;
	AlgorithmLibraryListContainer	SelectedLibList;
	int		LibFolderID;
	//ShowMarkListForm	*ShowMarkListFormInst;
	MatchShiftRotationBase	*GetMatchShiftRotationBase(void);

	void		ShowMatchShiftRotationInfoList(void);
	void		ShowTab(void);
	GUIFormBase	*GetImagePanel(void);
	void		RepaintImage(void);

	FlexArea	GlobalPickupArea;

	void	ShowPatternList(void);
	
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
};

#endif // PROPERTYMATCHSHIFTROTATIONFORM_H
