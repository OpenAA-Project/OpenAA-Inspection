#ifndef IMAGEBANKLISTFORM_H
#define IMAGEBANKLISTFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class ImageBankListForm;
}
class	ImageBank;
class	StartProcessAgainButton;

class ImageBankListForm : public QWidget
{
    Q_OBJECT
    ImageBank	*Parent;
public:
    explicit ImageBankListForm(ImageBank *p,QWidget *parent = 0);
    ~ImageBankListForm();
    
	void	UpdateList(void);
private slots:
    void on_pushButtonClose_clicked();
    void on_tableWidgetImages_doubleClicked(const QModelIndex &index);
    void on_pushButtonClear_clicked();
    void on_pushButtonRetry_clicked();
    void on_pushButtonSaveAll_clicked();
    void on_pushButtonCountSet_clicked();
    void on_toolButtonStoreOnlyOK_clicked();
    void on_toolButtonStoreOnlyNG_clicked();

private:
    Ui::ImageBankListForm *ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // IMAGEBANKLISTFORM_H
