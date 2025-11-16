#ifndef SELECTONELIBRATYFORANYTYPEFORM_H
#define SELECTONELIBRATYFORANYTYPEFORM_H

#include <QWidget>
#include <QModelIndex>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectOneLibratyForAnyTypeForm;
}

class   LibFolderForm;

class SelectOneLibratyForAnyTypeForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT

public:
    explicit SelectOneLibratyForAnyTypeForm(LayersBase *base ,bool UseOkCancel=false,QWidget *parent = nullptr);
    ~SelectOneLibratyForAnyTypeForm();

    AlgorithmLibraryList	SelectedLib;

    void	SetSelected(AlgorithmLibraryList &selectedLib);

    void	SetLibTypeInComboBox(void);
    void	ShowFolder(int LibType);
    void    ShowSelectedLib(void);

    bool	Save(QIODevice *f);
    bool	Load(QIODevice *f);
		
private slots:
    void on_comboBLibType_currentIndexChanged(int index);
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectOneLibratyForAnyTypeForm *ui;

    bool                            InitialMode;
    LibFolderForm					*pLibFolderForm;
    int								LibFolderID;
    int								LibType;
    AlgorithmLibraryListContainer	LibIDList;

    virtual	void closeEvent (QCloseEvent * event)   override;
    virtual void resizeEvent(QResizeEvent *event)   override;
    virtual void showEvent(QShowEvent *e)   override;
};

#endif // SELECTONELIBRATYFORANYTYPEFORM_H
