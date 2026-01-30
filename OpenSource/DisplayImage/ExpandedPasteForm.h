/*
 * Copyright (C) 2022
 * Author : Masatoshi Sasai ,MEGATRADE corporation
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef EXPANDEDPASTEFORM_H
#define EXPANDEDPASTEFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class ExpandedPasteForm;
}

class	DisplayImage;

class ExpandedPasteForm : public QWidget
{
    Q_OBJECT
    DisplayImage	*MainPanel;
public:
    explicit ExpandedPasteForm(DisplayImage *mainPanel,QWidget *parent = 0);
    ~ExpandedPasteForm();
    
    void	SetZone(int WDot,int HDot);

signals:
    void	ExecuteOk(void);
    void	ExecuteOkInSameAlgorithm(void);
    void	ExecuteMatrix(void);
    void	CancelPaste(void);

private slots:
    void on_ButtonPasteSameAlgo_clicked();
    void on_ButtonArrange_clicked();
    void on_ButtonCancel_clicked();
    void on_tabWidget_currentChanged(int index);
    void on_pushButtonLoadMastixList_clicked();
    void on_pushButtonSaveMastixList_clicked();
    void on_ButtonPasteSameAlgoInMatrixList_clicked();
    void on_tableWidgetMatrixList_clicked(const QModelIndex &index);

private:
    Ui::ExpandedPasteForm *ui;

    virtual	void showEvent ( QShowEvent * event )	override;
    void ShowMatrixList(void);
    virtual	void closeEvent ( QCloseEvent * event )	override;
};

#endif // EXPANDEDPASTEFORM_H