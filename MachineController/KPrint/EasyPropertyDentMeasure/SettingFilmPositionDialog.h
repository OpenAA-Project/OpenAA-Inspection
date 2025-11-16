#ifndef SETTINGFILMPOSITIONDIALOG_H
#define SETTINGFILMPOSITIONDIALOG_H

#include <QDialog>

namespace Ui {
class SettingFilmPositionDialog;
}

class	EasyPropertyDentMeasureForm;

class SettingFilmPositionDialog : public QDialog
{
    Q_OBJECT

    EasyPropertyDentMeasureForm *Parent;
public:
    explicit SettingFilmPositionDialog(EasyPropertyDentMeasureForm *p ,int FilmIndex,int FilmPointNo ,QWidget *parent = nullptr);
    ~SettingFilmPositionDialog();

    int FilmIndex;
    int FilmPointNo;

private slots:
    void on_PushButtonOK_clicked();
    void on_PushButtonCancel_clicked();
    void	SlotEndPointClicked(int EndNo,int MeasureNo);
private:
    Ui::SettingFilmPositionDialog *ui;
};

#endif // SETTINGFILMPOSITIONDIALOG_H
