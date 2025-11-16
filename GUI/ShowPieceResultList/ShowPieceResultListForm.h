#ifndef SHOWPIECERESULTLISTFORM_H
#define SHOWPIECERESULTLISTFORM_H

#include "XGUIFormBase.h"
#include "XShowPieceResultListPacket.h"

namespace Ui {
    class ShowPieceResultListForm;
}

class ShowPieceResultListForm : public GUIFormBase
{
    Q_OBJECT

	ResultPieceListContainer	ResData;
	ResultPieceList				**ResPointer;
	int							ResPointerCount;
public:
    explicit ShowPieceResultListForm(LayersBase *Base ,QWidget *parent = 0);
    ~ShowPieceResultListForm();

	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;
private:
    Ui::ShowPieceResultListForm *ui;
protected:
	virtual	void resizeEvent ( QResizeEvent * event )	override;
};

#endif // SHOWPIECERESULTLISTFORM_H
