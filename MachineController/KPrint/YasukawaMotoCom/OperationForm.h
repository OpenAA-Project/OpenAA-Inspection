#ifndef OPERATIONFORM_H
#define OPERATIONFORM_H

#include <QWidget>

namespace Ui {
class OperationForm;
}
class YasukawaMotoCom;

class OperationForm : public QWidget
{
    Q_OBJECT

    double  Position[100][6];
    int     PointCount;
    double  SpeedGo;
    double  SpeedBack;
    int     ReleasePointIndex;

    YasukawaMotoCom *Parent;
public:
    explicit OperationForm(YasukawaMotoCom *P,QWidget *parent = nullptr);
    ~OperationForm();

    bool    SavePoint(QIODevice *f);
    bool    LoadPoint(QIODevice *f);

private slots:
    void on_pushButtonPlus100X_clicked();
    void on_pushButtonMinus100X_clicked();
    void on_pushButtonPlus10X_clicked();
    void on_pushButtonMinus10X_clicked();
    void on_pushButtonPlus1X_clicked();
    void on_pushButtonMinus1X_clicked();

    void on_pushButtonPlus100Y_clicked();
    void on_pushButtonMinus100Y_clicked();
    void on_pushButtonPlus10Y_clicked();
    void on_pushButtonMinus10Y_clicked();
    void on_pushButtonPlus1Y_clicked();
    void on_pushButtonMinus1Y_clicked();

    void on_pushButtonPlus100Z_clicked();
    void on_pushButtonMinus100Z_clicked();
    void on_pushButtonPlus10Z_clicked();
    void on_pushButtonMinus10Z_clicked();
    void on_pushButtonPlus1Z_clicked();
    void on_pushButtonMinus1Z_clicked();

    void on_pushButtonPlus100R_clicked();
    void on_pushButtonMinus100R_clicked();
    void on_pushButtonPlus10R_clicked();
    void on_pushButtonMinus10R_clicked();
    void on_pushButtonPlus1R_clicked();
    void on_pushButtonMinus1R_clicked();

    void on_pushButtonPlus100B_clicked();
    void on_pushButtonMinus100B_clicked();
    void on_pushButtonPlus10B_clicked();
    void on_pushButtonMinus10B_clicked();
    void on_pushButtonPlus1B_clicked();
    void on_pushButtonMinus1B_clicked();

    void on_pushButtonPlus100T_clicked();
    void on_pushButtonMinus100T_clicked();
    void on_pushButtonPlus10T_clicked();
    void on_pushButtonMinus10T_clicked();
    void on_pushButtonPlus1T_clicked();
    void on_pushButtonMinus1T_clicked();

    void on_pushButtonStart_clicked();
    void on_pushButtonRelease_clicked();
    void on_pushButtonOtherPoint_clicked();
    void on_pushButtonDeleteLine_clicked();

    void ShowPositionList(void);
    void on_pushButtonRunGo_clicked();

    void on_pushButtonRunBack_clicked();
    void on_pushButtonStepGo_clicked();
    void on_pushButtonStepBack_clicked();
    void on_pushButtonSave_clicked();
    void on_pushButtonLoad_clicked();

private:
    Ui::OperationForm *ui;
};

#endif // OPERATIONFORM_H
