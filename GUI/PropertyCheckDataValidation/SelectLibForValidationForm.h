#ifndef SELECTLIBFORVALIDATIONFORM_H
#define SELECTLIBFORVALIDATIONFORM_H

#include <QWidget>
#include "XServiceForLayers.h"
#include "XAlgorithmLibrary.h"

namespace Ui {
class SelectLibForValidationForm;
}
class   LibFolderForm;

class SelectLibForValidationForm : public QWidget,public ServiceForLayers
{
    Q_OBJECT


public:
    explicit SelectLibForValidationForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~SelectLibForValidationForm();

    bool    Initial(int LibType, int LibID);

    void	ShowFolder(int LibType);

private slots:
    void on_comboBoxAlgorithm_currentIndexChanged(int index);
    void on_tableWidgetLibList_clicked(const QModelIndex &index);
    void	SlotSelectLibFolder(int LibFolderID ,QString FolderName);
private:
    Ui::SelectLibForValidationForm *ui;
    LibFolderForm					*pLibFolderForm;
    int                             SelectedLibType;
    int								LibFolderID;
    AlgorithmLibraryListContainer	LibIDList;

signals:
    void    SignalSelectedLib(int LibType,int LibID);
};

#endif // SELECTLIBFORVALIDATIONFORM_H
