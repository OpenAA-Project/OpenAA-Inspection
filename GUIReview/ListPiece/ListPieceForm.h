#ifndef LISTPIECEFORM_H
#define LISTPIECEFORM_H

#include "XGUIFormBase.h"
#include "XGUIDLL.h"
#include "XDLLOnly.h"
#include "XYCross.h"
#include "XGUIPacketForDLL.h"

namespace Ui {
class ListPieceForm;
}

class	AreaList : public NPList<AreaList>
{
public:
	int			Front;
	QString		Row;
	QString		Column;
	QString		AreaName;

	virtual	int	Compare(AreaList &src)	override;
};

class	AreaListContainer : public NPListPack<AreaList>
{
public:
	void	MergeArea(QString &aname);
	QStringList	MakeAreaList(void);
};


class ListPieceForm : public GUIFormBase
{
    Q_OBJECT

	AreaListContainer	FrontList;
	AreaListContainer	BackList;
public:
    explicit ListPieceForm(LayersBase *base ,QWidget *parent = 0);
    ~ListPieceForm();

	virtual	void TransmitDirectly(GUIDirectMessage *packet)	override;
	
private slots:
    void on_tableWidgetPiece_clicked(const QModelIndex &index);
	void	ResizeAction();
private:
    Ui::ListPieceForm *ui;

	void	UpdateList(void);
};

#endif // LISTPIECEFORM_H
