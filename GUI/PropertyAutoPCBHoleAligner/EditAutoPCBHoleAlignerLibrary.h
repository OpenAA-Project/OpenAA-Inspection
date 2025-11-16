#ifndef EDITAUTOPCBHOLEALIGNERLIBRARY_H
#define EDITAUTOPCBHOLEALIGNERLIBRARY_H

#include <QDialog>
#include <QModelIndex>
#include <QColor>
#include "mtLineGraph.h"
#include "mtGraph.h"
#include "mtColorFrame.h"
#include "XAlgorithmLibrary.h"
#include "XServiceForLayers.h"
#include "XColorSpace.h"
#include "ShowRGBCube.h"
#include "SelectColorSample.h"
#include "XDataAlgorithm.h"
#include "XAutoPCBHoleAligner.h"
#include "ShowRGBSamples.h"

namespace Ui {
class EditAutoPCBHoleAlignerLibrary;
}

class	GeneralLibFolderForm;

class EditAutoPCBHoleAlignerLibrary : public QDialog, public ServiceForLayers
{
    Q_OBJECT
    
public:
    explicit EditAutoPCBHoleAlignerLibrary(LayersBase* Base, QWidget *parent = 0);
    ~EditAutoPCBHoleAlignerLibrary();

    void	Initial(AlgorithmBase* InstBase);

private slots:
    void on_pushButtonAddColor_clicked();
    void on_pushButtonEliminateColor_clicked();
    void on_ButtonLibNew_clicked();
    void on_ButtonLibDelete_clicked();
    void on_ButtonLibSaveNew_clicked();
    void on_ButtonLibSave_clicked();
    void on_pushButton_clicked();
    void on_listWidgetBaseColor_doubleClicked(const QModelIndex &index);
    void on_listWidgetEliminatedColor_doubleClicked(const QModelIndex &index);
    void on_pushButtonAddAllColor_clicked();
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_pushButtonAddPickupColor_clicked();
    void on_pushButtonSubPickupColor_clicked();
    void on_pushButtonAddColorArea_clicked();
    void on_pushButtonEliminateColorArea_clicked();

    void	SlotSelectLibFolder(int LibFolderID, QString FolderName);
    void	SlotColorSampleBeforeSave();
    void	SlotColorSampleSelectOne();
    void	SlotAddEliminated(void);
    void	SlotDelEliminated(void);

private:
    Ui::EditAutoPCBHoleAlignerLibrary *ui;

    GeneralLibFolderForm* pLibFolderForm;
    int		LibFolderID;
    //AutoPCBHoleAlignerLibrary* TempLib;
	AlgorithmLibraryLevelContainer	*TempLib;
    int		LibType;
    void	ShowLibrary(AlgorithmLibraryLevelContainer& data);
    void	GetLibraryFromWindow(AlgorithmLibraryLevelContainer& data);

    AlgorithmLibraryListContainer	LibIDList;

    ShowRGBSpace		ColorThre;
    SelectColorSample	ColorSamples;
    ShowRGBSamples		RGBPanel;
    QColor PickupColor;
    mtColorFrame	PickupColorFrame;

    void ShowThresholdList(void);
    AutoPCBHoleAlignerBase* GetAutoPCBHoleAlignerBase(void);
    AlgorithmLibraryListContainer	LibList;
};

#endif // EDITAUTOPCBHOLEALIGNERLIBRARY_H
