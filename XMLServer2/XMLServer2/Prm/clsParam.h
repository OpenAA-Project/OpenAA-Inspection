#ifndef CLSPARAM_H
#define CLSPARAM_H

#include <QWidget>
#include <QDialog>
#include "ui_clsParam.h"

#include "clsLog.h"
#include "clsDb.h"

/**
 * @brief ÉpÉâÉÅÅ[É^ê›íË
 */
class clsParam : public QDialog
{
    Q_OBJECT

public:
    clsParam(QWidget *parent = 0);
    ~clsParam();

private slots:
	void closeWin();
	void selFolder();
	void selDbFile();
	void createDbFile();
	void saveParam();

	void addTag();
	void delTag();
	void chgTag(int,int);
	void addAttr();
	void delAttr();

	void selDbFolder();

private:
    Ui::clsParamClass ui;

    clsParamDef *prm;

    void putParam();
    void getParam();

    int nTagCnt;
    int nCurTagRow;
    int nAttrCnt;
    int nCurAttrRow;

    void setInitTag();
    void setTagAttr(int row);
};

#endif // CLSPARAM_H
