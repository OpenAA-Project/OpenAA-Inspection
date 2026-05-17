/*******************************************************************************
** Copyright (C) 2005-2008 MEGATRADE corp. All rights reserved.
**
** Please consult your licensing agreement or contact customer@mega-trade.co.jp 
** if any conditions of this licensing agreement are not clear to you.
**
** This file is C:\Regulus64v5\GUI\GeneralLabel\GeneralLabel.cpp
** Author : YYYYYYYYYY
****************************************************************************-**/

#include "GeneralLabel.h"



DEFFUNCEX	bool	DLL_GetName(QString &Root ,QString &Name)
{
	Root="General";
	Name="Label";
	return(true);
}

DEFFUNCEX	const char	*DLL_GetExplain(void)
{
	return("General Label");
}

DEFFUNCEX	bool	DLL_Initial(LayersBase *Base)
{
	Q_INIT_RESOURCE(ServiceLib);
	return true;
}
DEFFUNCEX	void	DLL_Close(void)
{
	
	Q_CLEANUP_RESOURCE(ServiceLib);
}

DEFFUNCEX	GUIFormBase	*DLL_CreateInstance(LayersBase *Base,QWidget *parent)
{
	return(new GeneralLabel(Base,parent));
}
DEFFUNCEX	void	DLL_DeleteInstance(GUIFormBase *Instance)
{
	delete	Instance;
}


DEFFUNCEX	int32	DLL_GetPropertyString(void	*Instance ,struct	PropertyClass Data[] ,WORD	maxDataDim)
{
	if(maxDataDim<10){
		return(-1);
	}
	Data[0].Type				 ="QString";
	Data[0].VariableNameWithRoute="Msg";
	Data[0].Pointer				 =&((GeneralLabel *)Instance)->Msg;
	Data[0].Translatable		 =true;
	Data[1].Type				 ="AlignLeft,AlignCenter,AlignRight";
	Data[1].VariableNameWithRoute="AlignAttr";
	Data[1].Pointer				 =&((GeneralLabel *)Instance)->AlignAttr;
	Data[2].Type				 ="QColor";
	Data[2].VariableNameWithRoute="CharColor";
	Data[2].Pointer				 =&((GeneralLabel *)Instance)->CharColor;
	Data[3].Type				 ="QColor";
	Data[3].VariableNameWithRoute="BackColor";
	Data[3].Pointer				 =&((GeneralLabel *)Instance)->BackColor;
	Data[4].Type				 ="bool";
	Data[4].VariableNameWithRoute="TransparentBackColor";
	Data[4].Pointer				 =&((GeneralLabel *)Instance)->TransparentBackColor;
	Data[5].Type				 ="QColor";
	Data[5].VariableNameWithRoute="BorderColor";
	Data[5].Pointer				 =&((GeneralLabel *)Instance)->BorderColor;
	Data[6].Type				 ="int32";
	Data[6].VariableNameWithRoute="BorderWidth";
	Data[6].Pointer				 =&((GeneralLabel *)Instance)->BorderWidth;
	Data[7].Type				 ="dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none";
	Data[7].VariableNameWithRoute="BorderStyle";
	Data[7].Pointer				 =&((GeneralLabel *)Instance)->BorderStyle;
	Data[8].Type				 ="QFont";
	Data[8].VariableNameWithRoute="CFont";
	Data[8].Pointer				 =&((GeneralLabel *)Instance)->CFont;
	Data[9].Type				 ="bool";
	Data[9].VariableNameWithRoute="UseStyleSheet";
	Data[9].Pointer				 =&((GeneralLabel *)Instance)->UseStyleSheet;

	return(10);
}

DEFFUNCEX	QIcon	*DLL_GetIcon(void)
{
	return(new QIcon(QPixmap(":Resources/GeneralLabel.png")));
}


//==================================================================================================
GeneralLabel::GeneralLabel(LayersBase *Base ,QWidget *parent)
:GUIFormBase(Base,parent)
{
	AlignAttr="AlignLeft";
	Label.setParent(this);
	Label.move(0,0);
	Label.setWordWrap(true);
	Msg="Label";
	TransparentBackColor=true;
	BorderWidth=1;
	BorderStyle="none";
	UseStyleSheet=true;
	resize(60,25);
}

GeneralLabel::~GeneralLabel(void)
{
}

void	GeneralLabel::Prepare(void)
{
	Label.setText(Msg);

	//Alignment
	if(AlignAttr=="AlignLeft"){
		Label.setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
	}
	else if(AlignAttr=="AlignRight"){
		Label.setAlignment(Qt::AlignRight|Qt::AlignVCenter);
	}
	else{
		Label.setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
	}

	//UseStyleSheet
	if(UseStyleSheet==true){
		//Background
		QString strBackgroundStyleSheet;
		if(TransparentBackColor==true){
			strBackgroundStyleSheet="background: none;";
		}
		else{
			strBackgroundStyleSheet	= "background-color: "
									+ BackColor.name() + ";";
		}

		//Font
		QString strFont="";
		if(CFont.bold()==true){
			strFont	+="font-weight: bold;";
		}
		if(CFont.style()==QFont::StyleItalic){
			strFont	+="font-style: italic;";
		}
		else if(CFont.style()==QFont::StyleOblique){
			strFont	+="font-style: oblique;";
		}
		QString strFontStyleSheet	= "font-family: "
									+ CFont.family() + ";"
									+ "font-size: "
									+ QString::number(CFont.pointSize()) + "pt;"
									+ strFont;

		//StyleSheet
		QString strStyleSheet	= "color: "
								+ CharColor.name() + ";"
								+ "border-width: "
								+ QString::number(BorderWidth) + "px;"
								+ "border-color: "
								+ BorderColor.name() + ";"
								+ "border-style: "
								+ BorderStyle + ";"
								+ strBackgroundStyleSheet
								+ strFontStyleSheet;
		setStyleSheet(strStyleSheet);
	}
	else{
		//Color
		//QPalette palette;
		//palette.setColor(QPalette::Background,BackColor);
		//Label.setPalette(palette);
		//BorderStyle "dot-dash,dot-dot-dash,dotted,double,groove,inset,outset,ridge,solid,none"
		Label.setFrameShadow(QFrame::Plain);
		if(BorderStyle=="solid"){
			Label.setFrameShape(QFrame::Box);
		}
		else if(BorderStyle=="none"){
			Label.setFrameShape(QFrame::NoFrame);
		}
	}

	ResizeAction();
}

void	GeneralLabel::ResizeAction(void)
{
	Label.resize(width(),height());
}
