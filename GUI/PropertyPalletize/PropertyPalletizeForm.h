#ifndef PROPERTYPALLETIZEFORM_H
#define PROPERTYPALLETIZEFORM_H

#include "XGUIFormBase.h"
#include "XPalletize.h"
#include "XStandardPropertyForm.h"
#include <QLocalSocket>

namespace Ui {
class PropertyPalletizeForm;
}

class PalletizeBase;

class PropertyPalletizeForm : public GUIFormBase
{
    Q_OBJECT

    QLocalSocket    Sock;
    IntList         LastIndexMasterPosList;

	MatchingResultContainer LastResult;
public:
    explicit PropertyPalletizeForm(LayersBase *Base ,QWidget *parent = nullptr);
    ~PropertyPalletizeForm();

 	virtual	void	TransmitDirectly(GUIDirectMessage *packet)	override;
	virtual void	ShowInEdit(void)	override;
	virtual void	BuildForShow(void)	override;
	virtual void	StartPage	(void)	override;
    virtual void	ShowInPlayer		(int64 shownInspectionID=-1)    override;
private slots:
    void on_pushButtonEditLibrary_clicked();
    void on_pushButtonSend_clicked();

private:
    Ui::PropertyPalletizeForm *ui;

    PalletizeBase	*GetPalletizeBase(void);
    void    TransferMotorData(double Dim[5]);
    void    ShowResultGrid(PalletizeItem *Item ,int IndexMasterPos,MatchingResult *MatchingResultList);
};

#endif // PROPERTYPALLETIZEFORM_H
