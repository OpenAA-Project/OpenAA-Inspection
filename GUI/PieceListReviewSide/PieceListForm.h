#ifndef PIECELISTFORM_H
#define PIECELISTFORM_H

#include "XGUIFormBase.h"
#include "XPieceReviewSide.h"
#include "NListComp.h"
#include "XPieceListReviewSidePacket.h"

namespace Ui {
    class PieceListForm;
}

class PieceListForm : public GUIFormBase
{
    Q_OBJECT

	ItemListReviewSideContainer	ListData;
public:
    explicit PieceListForm(LayersBase *Base,QWidget *parent = 0);
    ~PieceListForm();

	virtual	void	BuildForShow(void)	override;
private:
    Ui::PieceListForm *ui;

	PieceReviewSideBase	*GetResultImportanceBase(void);
protected:
	virtual	void resizeEvent ( QResizeEvent * event )	override;
};

//---------------------------------------------------------------


#endif // PIECELISTFORM_H
