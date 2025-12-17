#ifndef IMAGEDIALOG_H
#define IMAGEDIALOG_H

#include <QDialog>
#include <QImage>

namespace Ui {
class ImageDialog;
}

class ImageDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ImageDialog(const QImage &sImage ,QWidget *parent = 0);
    ~ImageDialog();

    QImage	SImage;
private slots:
    void on_pushButtonClear_clicked();
    void on_pushButtonCancel_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();

private:
    Ui::ImageDialog *ui;
};

#endif // IMAGEDIALOG_H
