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

#ifndef IMAGEBANKLISTFORM_H
#define IMAGEBANKLISTFORM_H

#include <QWidget>
#include <QModelIndex>

namespace Ui {
class ImageBankListForm;
}
class	ImageBank;
class	StartProcessAgainButton;

class ImageBankListForm : public QWidget
{
    Q_OBJECT
    ImageBank	*Parent;
public:
    explicit ImageBankListForm(ImageBank *p,QWidget *parent = 0);
    ~ImageBankListForm();
    
	void	UpdateList(void);
private slots:
    void on_pushButtonClose_clicked();
    void on_tableWidgetImages_doubleClicked(const QModelIndex &index);
    void on_pushButtonClear_clicked();
    void on_pushButtonRetry_clicked();
    void on_pushButtonSaveAll_clicked();
    void on_pushButtonCountSet_clicked();
    void on_toolButtonStoreOnlyOK_clicked();
    void on_toolButtonStoreOnlyNG_clicked();

private:
    Ui::ImageBankListForm *ui;

	virtual	void	resizeEvent ( QResizeEvent * event )	override;
};

#endif // IMAGEBANKLISTFORM_H