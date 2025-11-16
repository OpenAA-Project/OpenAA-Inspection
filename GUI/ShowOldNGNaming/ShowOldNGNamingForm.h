#ifndef SHOWOLDNGNAMINGFORM_H
#define SHOWOLDNGNAMINGFORM_H

#include <QDialog>
#include "XGUIFormBase.h"
#include "XNaming.h"
#include "XIntClass.h"
#include "XTypeDef.h"

namespace Ui {
    class ShowOldNGNamingForm;
}

class	NamingBase;
class	SignalOperandInt;
class	SignalOperandBit;

class ShowOldNGNamingForm : public GUIFormBase
{
    Q_OBJECT

public:
	class ComplessNGArea{
	public:
		QString Name;
		QList<int> GlobalPageList;
		QList<int> ItemIDList;
	//private:
	//	int m_GlobalX1;
	//	int m_GlobalY1;
	//	int m_GlobalX2;
	//	int m_GlobalY2;
	//	QList<int> m_GlobalPage;
	//	QList<int> m_ItemID;

	//public:
	//	ComplessNGArea():m_GlobalX1(0),m_GlobalY1(0),m_GlobalX2(0),m_GlobalY2(0),m_GlobalPage(),m_ItemID(){};

	//public:
	//	void pushData(int globalPage, int itemID){
	//		m_GlobalPage.push_back(globalPage);
	//		m_ItemID.push_back(itemID);
	//	};

	//	QList<int> getGlobalPage() const { return m_GlobalPage; };
	//	QList<int> getItemID() const { return m_ItemID; };
	//	int getGlobalPage(int i) const { return m_GlobalPage[i]; };
	//	int getItemID(int i) const { return m_ItemID[i]; };
	//	int count() const { return m_GlobalPage.count(); };

	public:
		bool hasData(int GlobalPage, int ItemID) const {
			for(int i=0; i<GlobalPageList.count() && i<ItemIDList.count(); i++){
				if(GlobalPageList[i]==GlobalPage && ItemIDList[i]==ItemID){
					return true;
				}
			}

			return false;
		};
	};

	class ComplessNGAreaList
	{
	public:
		ComplessNGAreaList():m_ListData(){
			int i = m_ListData.count();
		};
	private:
		QVector<ComplessNGArea> m_ListData;
	public:
		bool search(const QString &Name) const {
			for(int i=0; i<m_ListData.count(); i++){
				if(m_ListData.at(i).Name==Name){
					return true;
				}
			}
			return false;
		};

		QString search(int GlobalPage, int ItemID) const {
			for(int i=0; i<m_ListData.count(); i++){
				if(m_ListData.at(i).hasData(GlobalPage, ItemID)==true){
					return m_ListData.at(i).Name;
				}
			}

			return QString();
		};

		bool search(const QString &Name, int GlobalPage, int ItemID) const {
			for(int i=0; i<m_ListData.count(); i++){
				if(m_ListData.at(i).Name==Name && m_ListData.at(i).hasData(GlobalPage, ItemID)==true){
					return true;
				}
			}

			return false;
		};

		void push(const QString &Name, int GlobalPage, int ItemID){
			for(int i=0; i<m_ListData.count(); i++){
				if(m_ListData[i].Name==Name){
					int gind = m_ListData[i].GlobalPageList.indexOf(GlobalPage);
					int iind = m_ListData[i].ItemIDList.indexOf(ItemID);
					if((gind==-1 || iind==-1) || (gind != iind)){
						m_ListData[i].GlobalPageList.push_back(GlobalPage);
						m_ListData[i].ItemIDList.push_back(ItemID);
						return;
					}else if(gind == iind){
						return;
					}
				}
			}

			ComplessNGArea area;
			area.Name = Name;
			area.GlobalPageList << GlobalPage;
			area.ItemIDList << ItemID;
			m_ListData.append(area);
		};

		void clear(){
			m_ListData.clear();
		};

	};

private:
	NamingPointerStock	*NamingArea;
	NamingNGContainer	*NGNaming;
	QList<ComplessNGAreaList> CompNGAreaList;
	bool NamingCompiled;

public:
    explicit ShowOldNGNamingForm(LayersBase *Base,QWidget *parent = 0);
    ~ShowOldNGNamingForm();

	int32		GenerationLevel;	//0:Current 1Å`:n older
	QStringList	TargetImagePanelNames;

	virtual	void	BuildForShow(void)	override;
	virtual void	ShowInPlayer(int64 shownInspectionID=-1)	override;

	SignalOperandInt	*ioNGCount;
	SignalOperandInt	*ioCurrentCounter;
	SignalOperandInt	*ioNGXPos;
	SignalOperandInt	*ioNGYPos;
	SignalOperandInt	*ioAck;
	SignalOperandBit	*ioReqResult;

private slots:
    void on_tableWidget_clicked(const QModelIndex &index);
	void	ResizeAction();
	void	OperandChanged();
	void	SlotReqResult();

        void on_pushButtonGetNow_clicked();

private:
    Ui::ShowOldNGNamingForm *ui;

	NamingBase	*GetNamingBase(void);

	virtual	void	Prepare(void)	override;
	void	ReqNamingData(int64 shownInspectionID);
	void	ShowGrid(void);
	NamingNG	*FindNG(NamingPointer *a);
	NamingNG	*FindNG(NamingPointer *a, int phase);
	int CountNG(NamingPointer *a, int phase);

	void debugOut();
};


#endif // SHOWOLDNGNAMINGFORM_H
