#ifndef SEARCH9POSFORM_H
#define SEARCH9POSFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class Search9PosForm;
}


class Search9PosForm : public GUIFormBase
{
    Q_OBJECT
    
	XYClassContainer	XYPosData;
public:
    explicit Search9PosForm(LayersBase *base ,QWidget *parent = 0);
    ~Search9PosForm();
    
	virtual	bool	SaveContent(QIODevice *f)	override;
	virtual	bool	LoadContent(QIODevice *f)	override;
private:
    Ui::Search9PosForm *ui;
};

#endif // SEARCH9POSFORM_H
