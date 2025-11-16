#ifndef CHRONOLOGICALGRAPHFORM_H
#define CHRONOLOGICALGRAPHFORM_H

#include <QWidget>
#include "mtGraph.h"
#include "mtLineGraph.h"

namespace Ui {
class ChronologicalGraphForm;
}
class NGCountForm;


class ChronologicalGraphForm : public QWidget
{
    Q_OBJECT
    NGCountForm	*Parent;

	mtLineGraph		GraphWidget;
	mtGLine			GraphData;
	mtGLine			GraphMain;
	int				*Dim;
	int				DimCount;
public:
    explicit ChronologicalGraphForm(NGCountForm *p,QWidget *parent = 0);
    ~ChronologicalGraphForm();
    
	void	SetGraph(void);

protected:
	virtual	void resizeEvent(QResizeEvent *event)	override;

private:
    Ui::ChronologicalGraphForm *ui;
};

#endif // CHRONOLOGICALGRAPHFORM_H
