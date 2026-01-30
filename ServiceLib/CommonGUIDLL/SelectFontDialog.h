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

#ifndef SELECTFONTDIALOG_H
#define SELECTFONTDIALOG_H

#include <QDialog>
#include <QFont>

namespace Ui {
class SelectFontDialog;
}

class SelectFontDialog : public QDialog
{
    Q_OBJECT
    QFont	CurrentFont;

public:
    explicit    SelectFontDialog(QWidget *parent = 0);
	explicit    SelectFontDialog(const QFont & initial, QWidget *parent = 0);
    ~SelectFontDialog();
    
	QFont	currentFont()const;
	QFont	selectedFont()const;
	void	setCurrentFont(const QFont & initial);

private slots:
    void on_listWidgetFont_currentRowChanged(int currentRow);
    void on_listWidgetStyle_currentRowChanged(int currentRow);
    void on_listWidgetSize_currentRowChanged(int currentRow);
    void on_pushButtonOK_clicked();
    void on_pushButtonCancel_clicked();

private:
    Ui::SelectFontDialog *ui;

	virtual void showEvent ( QShowEvent * event )   override;
};

#endif // SELECTFONTDIALOG_H