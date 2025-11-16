#ifndef EXPANDEDPASTEFORM_H
#define EXPANDEDPASTEFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class ExpandedPasteForm;
}

class	DisplayImage;

class ExpandedPasteForm : public QWidget
{
    Q_OBJECT
    DisplayImage	*MainPanel;
public:
    explicit ExpandedPasteForm(DisplayImage *mainPanel,QWidget *parent = 0);
    ~ExpandedPasteForm();
    
    void	SetZone(int WDot,int HDot);

signals:
    void	ExecuteOk(void);
    void	ExecuteOkInSameAlgorithm(void);
    void	ExecuteMatrix(void);
    void	CancelPaste(void);

private slots:
    void on_ButtonPasteSameAlgo_clicked();
    void on_ButtonArrange_clicked();
    void on_ButtonCancel_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_pushButtonLoadMastixList_clicked();
    void on_pushButtonSaveMastixList_clicked();
    void on_ButtonPasteSameAlgoInMatrixList_clicked();
    void on_tableWidgetMatrixList_clicked(const QModelIndex &index);

private:
    Ui::ExpandedPasteForm *ui;

    virtual	void showEvent ( QShowEvent * event )	override;
    void ShowMatrixList(void);
    virtual	void closeEvent ( QCloseEvent * event )	override;
};

#endif // EXPANDEDPASTEFORM_H
