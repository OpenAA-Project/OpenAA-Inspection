/*
 * Copyright (C) 2025
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
#include "JDTUnpacker.h"

#include "JDTAnalyzer.h"
#include "XGeneralFunc.h"
#include <QDir>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QEvent>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData> // Qt6で必須
#include <QUrl>

JDTUnpacker::JDTUnpacker(QWidget *parent, Qt::WindowFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);
	ui.leJDTFilePath->setDragEnabled(true);
	
	// Qt6推奨の関数ポインタ形式に変更 (コンパイル時チェックが効くようになります)
	connect(ui.pbExec, &QPushButton::clicked, this, &JDTUnpacker::slotClickUnpack);
	connect(ui.pbOpen, &QPushButton::clicked, this, &JDTUnpacker::fileopen);
}

JDTUnpacker::~JDTUnpacker()
{

}

QString JDTUnpacker::unpack()
{
	QFont font = ui.lbInfo->font();
	QFontMetrics fm(font);
	QString unpackStr = "Unpacking...";
	int pixcelWidth = fm.boundingRect(unpackStr).width();
	ui.lbInfo->setText(unpackStr);

	QRect geo = ui.lbInfo->geometry();

	geo.setWidth(pixcelWidth);

	ui.lbInfo->setGeometry(geo);
	ui.lbInfo->updateGeometry();
	
	repaint();

	QString	tFilePath=ui.leJDTFilePath->text();

	JDTFile file(tFilePath,"",0);

	if(file.isSuccess()==false){
		ui.lbInfo->setText("Unpack was failed.");
		return "";
	}

	QDir dir(qApp->applicationDirPath());
	QDir srcDir(tFilePath);
	QString subDirName = srcDir.dirName();

	dir.mkdir( srcDir.dirName() );
	dir.cd( srcDir.dirName() );

	QString preOutputPath = dir.path() + QDir::separator();

	int count=0;
	// Qt6のQListはQVectorベースに変更されましたが、イテレータの使い方は同じです
	for(QList<JDTImage>::const_iterator it=file.constBegin(); it!=file.constEnd(); it++){
		QString saveFilePath;
		saveFilePath = preOutputPath;
		int	Version=it->version();
		switch(Version){
		case 1:
		case 2:
			saveFilePath += QString("page-%1").arg(it->page()) + QDir::separator();
			break;
		case 3:
		case 4:
		case 5:
			saveFilePath += QString("phase-%1/page-%2").arg(it->phase()).arg(it->page()) + QDir::separator();
			break;
		default:
			continue;
			break;
		}

		QString filename = saveFilePath +
			QString("No%7_(%1,%2)-(%3,%4)_W%5H%6")
			.arg(it->left()).arg(it->top()).arg(it->right()).arg(it->bottom()).arg(it->width()).arg(it->height()).arg(it->staticID());
		dir.mkpath(saveFilePath);
		if(it->image().isNull()==true){
			QFile file;
			filename += " is not exist.txt";
			file.setFileName(filename);
			file.open(QIODevice::WriteOnly);
			QTextStream stream(&file);
			stream << "faild.";
		}else{
			filename += QString("_Ext[%1].png").arg(it->imageExtention());
			char	Buff[100];
			::QString2Char(it->imageExtention(), Buff, sizeof(Buff));
			it->image().save(filename, Buff);
			count++;
		}
	}

	ui.lbInfo->setText("Idle");

	return preOutputPath;
}

void JDTUnpacker::slotClickUnpack()
{
	setEnableInput(false);
	if(ui.cbAutoUnpack->isChecked()==true){
		QString	Str=unpack();
		setWindowTitle(Str);
	}
	setEnableInput(true);
}

void JDTUnpacker::fileopen()
{
	QString filename = QFileDialog::getOpenFileName(this, "Open one JDT File", "", "*.jdt");
	
	ui.lbInfo->setText("Idle");

	ui.leJDTFilePath->setText( filename );
}

void JDTUnpacker::dragEnterEvent(QDragEnterEvent *event)
{
	// Qt6では廃止されたQRegExpのAPIが混在していたため、シンプルな endsWith に変更
	if (event->mimeData()->hasUrls() && 
		event->mimeData()->urls().first().toLocalFile().endsWith(".jdt", Qt::CaseInsensitive)) {
		ui.lbInfo->setText("Your item is enable drop.");
		event->setDropAction(Qt::CopyAction);
		event->accept();
	} else {
		ui.lbInfo->setText("Your item is unable drop.");
	}
}

void JDTUnpacker::dragMoveEvent(QDragMoveEvent *event)
{
	if (event->mimeData()->hasUrls() && 
		event->mimeData()->urls().first().toLocalFile().endsWith(".jdt", Qt::CaseInsensitive)) {
		ui.lbInfo->setText("Your item Enable Drop.");
		event->setDropAction(Qt::CopyAction);
		event->accept();
	} else {
		ui.lbInfo->setText("Your item is unable drop.");
	}
}

void JDTUnpacker::dropEvent(QDropEvent *event)
{
	if (event->mimeData()->hasUrls() && 
		event->mimeData()->urls().first().toLocalFile().endsWith(".jdt", Qt::CaseInsensitive)) {
		int	N=event->mimeData()->urls().count();
		for(int i=0;i<N;i++){
			QUrl U=event->mimeData()->urls().at(i);
			ui.leJDTFilePath->setText(U.toLocalFile());
			slotClickUnpack();
		}
		event->setDropAction(Qt::CopyAction);
		event->accept();
	} else {
		ui.lbInfo->setText("Idle");
	}
}

void JDTUnpacker::dragLeaveEvent(QDragLeaveEvent *event)
{
	ui.lbInfo->setText("Idle");
}

void JDTUnpacker::setEnableInput(bool b)
{
	ui.leJDTFilePath->setEnabled(b);
	ui.pbOpen->setEnabled(b);
	ui.pbExec->setEnabled(b);
	ui.cbAutoUnpack->setEnabled(b);
	ui.leJDTFilePath->repaint();
	ui.pbOpen->repaint();
	ui.pbExec->repaint();
	ui.cbAutoUnpack->repaint();
}