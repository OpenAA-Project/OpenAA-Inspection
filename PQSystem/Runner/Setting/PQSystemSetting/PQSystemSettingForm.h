#ifndef PQSYSTEMSETTINGFORM_H
#define PQSYSTEMSETTINGFORM_H

#include <QWidget>
#include <QTabWidget>
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XGUIPacketForDLL.h"
#include "WEditParameterTab.h"
#include "PQSystemService.h"
#include "XDataInLayer.h"
#include "XAlgorithmLibrary.h"
#include "XPQSystemFunc.h"

namespace Ui {
class PQSystemSettingForm;
}

class PQSystemSettingForm : public PQSystemRunner
{
    Q_OBJECT
    WEditParameterTab		*WTabGeneral;
public:
    explicit PQSystemSettingForm(LayersBase *base ,const QString &root ,const QString &name
                                ,QWidget *parent = 0);
    ~PQSystemSettingForm();
    
    virtual	bool	Initial(void)   override;
    virtual	const QString	GetPath(void)		override;
	virtual	QString	GetDataText(void)			override    {   return /**/"PQSystemSetting";      }
	virtual	QString	GetDefaultFileName(void)	override    {   return /**/"PQSystemSetting.dat";  }

private slots:
    void on_ButtonOK_clicked();

private:
    Ui::PQSystemSettingForm *ui;
};

#endif // PQSYSTEMSETTINGFORM_H
