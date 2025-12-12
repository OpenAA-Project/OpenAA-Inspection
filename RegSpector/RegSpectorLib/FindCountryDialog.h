#ifndef FINDCOUNTRYDIALOG_H
#define FINDCOUNTRYDIALOG_H

#include <QDialog>
#include "XServiceRegSpector.h"

namespace Ui {
class FindCountryDialog;
}

class FindCountryDialog : public QDialog
{
    Q_OBJECT

    QStringList CodeList;
public:
    explicit FindCountryDialog(const QString &CSVFileName=CountryListFileName,QWidget *parent = nullptr);
    ~FindCountryDialog();

    QString CountryCode;

private slots:
    void on_tableWidget_doubleClicked(const QModelIndex &index);

private:
    Ui::FindCountryDialog *ui;

    virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // FINDCOUNTRYDIALOG_H
