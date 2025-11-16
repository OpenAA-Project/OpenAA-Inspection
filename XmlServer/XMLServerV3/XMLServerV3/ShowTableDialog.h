#ifndef SHOWTABLEDIALOG_H
#define SHOWTABLEDIALOG_H

#include <QDialog>

namespace Ui {
class ShowTableDialog;
}
class	XMLElementRoot;
class	XMLServerComm;

class ShowTableDialog : public QDialog
{
    Q_OBJECT
	XMLServerComm	*ServerCommData;
	XMLElementRoot	*SRoot;
public:
    explicit ShowTableDialog(XMLElementRoot *s, XMLServerComm *ServerCommDataParent ,QWidget *parent = 0);
    ~ShowTableDialog();

private slots:
    void on_pushButtonSave_clicked();
    void on_pushButtonRemove_clicked();
    void on_pushButtonClose_clicked();

private:
    Ui::ShowTableDialog *ui;
};

#endif // SHOWTABLEDIALOG_H
