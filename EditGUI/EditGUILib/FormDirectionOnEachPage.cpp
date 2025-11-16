#include "EditGUILibResource.h"
#include "XTypeDef.h"
#include "FormDirectionOnEachPage.h"
#include "ui_FormDirectionOnEachPage.h"
#include "XDataInLayer.h"
#include <swap.h>


void	DirectionGrid::ChangeValue(int row ,int col,const QVariant &value)
{
    if(col==0){
        RootParent->LocalData.SetPageXDir(row,value.toBool());
    }
    else if(col==1){
        RootParent->LocalData.SetPageYDir(row,value.toBool());
    }
    else if(col==2){
        RootParent->LocalData.SetPageYDelay(row,value.toInt());
    }
}
void	DirectionGrid::GetValue(int row ,int col,QVariant &value)
{
    if(col==0){
        value=QVariant(RootParent->LocalData.GetPageXDir(row));
    }
    else if(col==1){
        value=QVariant(RootParent->LocalData.GetPageYDir(row));
    }
    else if(col==2){
        value=QVariant(RootParent->LocalData.GetPageYDelay(row));
    }
}

FormDirectionOnEachPage::FormDirectionOnEachPage(LayersBase *Base ,QWidget *parent) :
    QWidget(parent)
    ,ServiceForLayers(Base)
    ,dGrid(this)
    ,ui(new Ui::FormDirectionOnEachPage)
    ,LocalData(Base)
{
    ui->setupUi(this);
    LocalData.CopyFrom(*GetLayersBase()->GetParamGlobal());

    dGrid.SetColumnCount(3);
    dGrid.move(0,0);
    dGrid.resize(ui->frameDirection->width(),ui->frameDirection->height());

    dGrid.setColumnWidth(0,60);
    dGrid.SetTopHeader(0, LangSolverGUILib.GetString(FormDirectionOnEachPage_LS,LID_18)/*"X Reverse"*/);
    dGrid.setColumnWidth(1,60);
    dGrid.SetTopHeader(1, LangSolverGUILib.GetString(FormDirectionOnEachPage_LS,LID_19)/*"Y Reverse"*/);
    dGrid.setColumnWidth(2,60);
    dGrid.SetTopHeader(2, LangSolverGUILib.GetString(FormDirectionOnEachPage_LS,LID_20)/*"YDelay"*/);

    ShowGrid();
}

FormDirectionOnEachPage::~FormDirectionOnEachPage()
{
    delete ui;
}

void	FormDirectionOnEachPage::ShowGrid(void)
{
    dGrid.setParent(ui->frameDirection);
    dGrid.SetRowCount(LocalData.PageNumb);

    for(int page=0;page<LocalData.PageNumb;page++){
        bool XDirReverse ,YDirReverse;
        LocalData.GetPageDir(page ,XDirReverse ,YDirReverse);

        WMultiGrid::CellData *Lx=dGrid.GetData(page ,0);
        Lx->Value		=QVariant(XDirReverse);
        Lx->CType		=WMultiGrid::_CType_CheckBox;
        Lx->Alignment	=Qt::AlignVCenter | Qt::AlignHCenter;

        WMultiGrid::CellData *Ly=dGrid.GetData(page ,1);
        Ly->Value		=QVariant(YDirReverse);
        Ly->CType		=WMultiGrid::_CType_CheckBox;
        Ly->Alignment	=Qt::AlignVCenter | Qt::AlignHCenter;

        WMultiGrid::CellData *Ld=dGrid.GetData(page ,2);
        Ld->Value		=QVariant(LocalData.GetPageYDelay(page));
        Ld->CType		=WMultiGrid::_CType_SpinBox;
        Ld->Alignment	=Qt::AlignVCenter | Qt::AlignHCenter;
    }

    dGrid.InitialGrid();

    for(int page=0;page<LocalData.PageNumb;page++){
        dGrid.SetLeftHeader(page,LangSolverGUILib.GetString(FormDirectionOnEachPage_LS,LID_21)/*"Pg/Str "*/
                                +QString::number(page));
    }
    dGrid.ShowGrid();
}
void FormDirectionOnEachPage::LoadFromWindow(void)
{
    GetLayersBase()->GetParamGlobal()->CopyPageDirFrom(LocalData);
}
void FormDirectionOnEachPage::CopyFromOriginal(LayersBase *src)
{
    LocalData.CopyFrom(*src->GetParamGlobal());
}

void FormDirectionOnEachPage::on_OKButton_clicked()
{
    GetLayersBase()->GetParamGlobal()->CopyPageDirFrom(LocalData);
    close();
}

void FormDirectionOnEachPage::on_CancelButton_clicked()
{
    close();
}

void FormDirectionOnEachPage::closeEvent ( QCloseEvent * event )
{
    emit	SignalClose();
}
