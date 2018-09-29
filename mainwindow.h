#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"
#include <QSpinBox>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT
        
public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();
protected:

        bool eventFilter(QObject *obj, QEvent *ev);
private:
        Ui::MainWindow *ui;
     //settings-------------
        QString m_fontQuran;
        QString m_fontTafsir;
         int m_fontSize;
         QColor m_fontColor;
         QColor m_backColor;
         QColor m_symbolColor;
         QColor m_findColor;
      //settings-------------


        int m_sura,m_pos,m_tIndex;
        Database *database;
        QString m_appPath,m_curTefsir;
        QComboBox *comboSura, *comboTafsir;
        QSpinBox *spinAya;
        QAction *actNextAya,*actPrevAya,*actNextSura,*actPrevSura;
        QAction  *actNextTefsir,*actPrevTefsir;
        QLineEdit *lineSearch;


private slots:
        void loadSettings();
        void changeSettings();
         void saveSettings();
        void chargeDataTools();
        void setSpinAyaMaximum(int index);
        void goSura(int index);
        void goAya();
void getOptions();
        void setCurentPos(int pos);
        void tefsirChanged(int indx);

        void  nextTefsir();
        void  prevtTefsir();
        void on_treeWidgetIndex_itemActivated(QTreeWidgetItem *item, int);
        void on_treeWidgetAjzaa_itemActivated(QTreeWidgetItem *item, int );


        void dataNextAya(){if(m_pos==6236)return;setCurentPos(m_pos+1); }
        void dataPrevAya(){if(m_pos==1)return;setCurentPos(m_pos-1); }
        void dataNextSura() {if(m_sura==113)return; goSura(m_sura+1); }
        void dataPrevSura() {if(m_sura<=0)return; goSura(m_sura-1); }


       void searchString();


        void on_toolButtonGoSearch_clicked();
        void on_lineEditSearchTree_textChanged(const QString &arg1);

        void on_treeWidgetSearch_itemActivated(QTreeWidgetItem *item, int /*column*/);
        void on_lineEditSearch_returnPressed();
        void on_lineEditSearchAnd_returnPressed();
        void on_toolButtonGoSearchTefsir_clicked();
        void on_treeWidgetSearchTefsir_itemActivated(QTreeWidgetItem *item, int);
        void on_lineEditSearchTefsir_returnPressed();
        void on_lineEditSearchAndTefsir_returnPressed();
        void on_textEdit_customContextMenuRequested(const QPoint &);
       void AboutThisApp();
void  goPage();
       void QuranPageAnchorClicked(const QString &arg1);
       void on_textEdit_highlighted(const QString &arg1);
       void on_textEdit_anchorClicked(const QUrl &arg1);
       void filePrint();


};

#endif // MAINWINDOW_H
