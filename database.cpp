/****************************************************************************
//   mtafsir Copyright (C) 2012 yahia nouah <yahiaui@gmail.com>
//
//      This program comes with ABSOLUTELY NO WARRANTY; for details type `show w'.
//      This is free software, and you are welcome to redistribute it
//      under certain conditions; type `show c' for details.
//
//  The hypothetical commands `show w' and `show c' should show the appropriate
//  parts of the General Public License.  Of course, your program's commands
//  might be different; for a GUI interface, you would use an "about box".
//
//    You should also get your employer (if you work as a programmer) or school,
//  if any, to sign a "copyright disclaimer" for the program, if necessary.
//  For more information on this, and how to apply and follow the GNU GPL, see
//  <http://www.gnu.org/licenses/>.
//
//    The GNU General Public License does not permit incorporating your program
//  into proprietary programs.  If your program is a subroutine library, you
//  may consider it more useful to permit linking proprietary applications with
//  the library.  If this is what you want to do, use the GNU Lesser General
//  Public License instead of this License.  But first, please read
//  <http://www.gnu.org/philosophy/why-not-lgpl.html>.
// ----------------------------------------------------------
** If you have questions regarding the use of this file, please contact
** yahia nouah (yahiaui@gmail.com)
** $mtafsir_END_LICENSE$
**
****************************************************************************/

#include "database.h"
//#include <QtGui>
//#include <QObject>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRecord>
#include <QSqlQuery>
//#include <QDomDocument>
#include <QFile>
#include <QXmlStreamReader>

#include <QTextStream>
#include <QFileInfo>
#include <QApplication>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QAction>
 #include <QSqlError>
 #include <QTextDocument>
#include <QTextCursor>
Database::Database()

{
    QDir appDir(qApp->applicationDirPath());
#if defined(Q_OS_WIN)

    appDir.cdUp();
        appPath=  appDir.absolutePath()+"/share/mtafsir";
#elif defined(Q_OS_MAC)
    if (appDir.dirName() == "MacOS") {
        appDir.cdUp();
        appDir.cdUp();
        appDir.cdUp();
            appPath=  appDir.absolutePath()+"/mtafsir";
    }
#else
    appDir.cdUp();
    appPath=  appDir.absolutePath()+"/share/mtafsir";
   // qDebug()<<appPath;
#endif


  db = QSqlDatabase::addDatabase("QSQLITE");
}


void Database::treeChargeSoura(QTreeWidget *view,QComboBox *combo)
{

        if(openQuranDb(false)==false)
                return;
        QLocale lc(QLocale::Arabic);
        lc.setNumberOptions(QLocale::OmitGroupSeparator);
        QString querytxt;
        querytxt=QString("SELECT* FROM sura_info  ORDER BY id");
        QSqlQuery query(querytxt,db);

        while (query.next()) {
                int fieldId= query.record().indexOf("id");
                QString myid= query.value(fieldId).toString();
                int fieldTxt= query.record().indexOf("sura");
                QString mytext = query.value(fieldTxt).toString();

                int fieldPos= query.record().indexOf("pos");
                QString mypos= query.value(fieldPos).toString();

                int fieldAyats= query.record().indexOf("ayats");
                QString ayatscount= query.value(fieldAyats).toString();

                QString suratext=lc.toString(myid.toInt())+"-"+mytext;

                QTreeWidgetItem *item=new  QTreeWidgetItem(view);

                item->setText(0,suratext);

                item->setText(1,mypos);

             combo->addItem(suratext,mypos+","+ayatscount);
        }
        //-----
       query.clear();

        querytxt=QString("SELECT* FROM quran  ORDER BY id");
        query.exec(querytxt);
        while (query.next()) {
                int fieldId= query.record().indexOf("id");
                QString myid= query.value(fieldId).toString();
                int fieldTxt= query.record().indexOf("text");
                QString mytext = query.value(fieldTxt).toString();
                int fieldSura= query.record().indexOf("sura");
                QString mysura= query.value(fieldSura).toString();
                int fieldAya= query.record().indexOf("aya");
                QString myaya= query.value(fieldAya).toString();
                int fieldnass_safy= query.record().indexOf("nass_safy");
                QString mynass_safy= query.value(fieldnass_safy).toString();
                QTreeWidgetItem *item=new  QTreeWidgetItem(view->topLevelItem(mysura.toInt()-1));
                item->setText(0,lc.toString(myaya.toInt())+"-"+mynass_safy);
                item->setData(0,Qt::UserRole,myaya);
                item->setText(1,myid);
                item->setText(2,mytext );

        }
}

//! تحميل الاجزاء والارباع والاحزاب في الشجرة
void Database::treeChargeJozaa(QTreeWidget *view)
{
      //-------------------------------------------
    QTreeWidgetItem *item=new QTreeWidgetItem(view) ;
    QTreeWidgetItem *osloItem=new QTreeWidgetItem(item) ;
    QTreeWidgetItem *osloItem2 ;

    QFile file(appPath+"/ajzaa.xml");
 //   qDebug()<<appPath+"/ajzaa.xml";
    file.open(QIODevice::ReadOnly);
    view->clear();

    QXmlStreamReader xml;
    xml.setDevice(&file);
    int nJoz=0;
    int nHizb=0;
    int nRob=0;
     QString idjoza;
     QString idhizb;
     QString idhrobaa;

    while (!xml.atEnd()) {

        xml.readNext();
        if (xml.name() == "root"){

             idjoza= xml.attributes().value("id").toString();
            QString textjoza=xml.attributes().value("Name").toString();
           //QString id=   creatIndex(idjoza);
            if(!textjoza.isNull()){
                  nJoz++;
                item= new QTreeWidgetItem(view);
                item->setText(0,QString::number(nJoz)+"-"+textjoza );
        //    item->setData(1,1,idjoza);
               item->setText(1,idjoza );

            }
        }else if (xml.name() == "Item"){

             idhizb= xml.attributes().value("id").toString();
            QString texthizb= xml.attributes().value("Name").toString();
            //QString id=   creatIndex(idhizb);
            if(!texthizb.isNull()){
                  nHizb++;
                osloItem= new QTreeWidgetItem(item);
                osloItem->setText(0,QString::number(nHizb)+"-"+texthizb );
             //   osloItem->setData(1,1,idhizb);
                 osloItem->setText(1,idhizb);

            }
        }else if (xml.name() == "bk"){

             idhrobaa= xml.attributes().value("id").toString();
        QString     textrobaa= xml.attributes().value("name").toString();
         // QString id=   creatIndex(idhrobaa);

            if(!textrobaa.isNull()){
                nRob++;
                if(nRob==5){
                      nRob=1;

                }

                osloItem2= new QTreeWidgetItem(osloItem);
                osloItem2->setText(0,QString::number(nRob)+"-"+textrobaa );
              //  osloItem2->setData(1,1,idhrobaa);
                osloItem2->setText(1,idhrobaa );

            }
        }

    }
    xml.clear();
    file.close();
  //  fileReciter.close();
}

   //! فتح قاعدة بيانات القرءان الكريم
 bool  Database:: openQuranDb(bool debug)
 {
         db.setDatabaseName(appPath+"/quran.db");

               QString txt="no database";
         if(!db.open()){
                 txt=db.lastError().text();
                 if(debug==false){
                          QMessageBox::information(0,"error",txt);
                 }else{
                          qDebug()<<txt;
                 }
              return false;

         }
        return true;
 }

//! فتح قاعدة البيانات
 void Database::openDb(QString dataName)
 {

         qDebug()<<dataName;
     databaseName=dataName;
     QFileInfo fi(dataName);
     tableName = fi.completeBaseName();
     db.setDatabaseName(dataName);
     QString txt="no database";
     if(!db.open()){

         txt=db.lastError().text();
         QMessageBox::information(0,"",txt);

     }

 }
 //! جلب التفسير
QString Database::getTranslation(int pos)
{


    QString querytxt=QString("SELECT* FROM %1 WHERE id=%2 ORDER BY id").arg(tableName).arg(QString::number(pos));

    QSqlQuery query(querytxt,db);
    if(query.lastError().isValid()){
        qDebug()<<query.lastError();
          // QMessageBox::information(0,"",query.lastError().text());
        return query.lastError().text();
    }
    query.next();
    int fieldNo = query.record().indexOf("text");
    if (fieldNo==-1){
        fieldNo = query.record().indexOf("tafsir");
    }
    QString mytext = query.value(fieldNo).toString();
    query.next();
   qDebug()<<mytext;
    return mytext;
}

//! [1]  البحث في الشجرة
void Database::searchInTreeview(QTreeWidget *view,QString searchString,int colum,bool hamza)
{
    for( int i = 0; i <view->topLevelItemCount(); i++ ) {
        view->topLevelItem(i)->setHidden(false );
        showAllItems(view->topLevelItem(i),view);
    }
    if (!searchString.isEmpty()){
        for( int i = 0; i <view->topLevelItemCount(); i++ ) {
            searchTreeForString(searchString,view->topLevelItem(i),true,i,view,colum,hamza) ;
        }
    }
}
//! [2]  البحث في الشجرة
bool Database::searchTreeForString(const QString &searchString, QTreeWidgetItem* parent
                                   , bool itemtop, int  topindex, QTreeWidget *view, int colum, bool hamza)
{
    int hiddenCount = 0;
    int hiddenparent=0;
    if (parent->childCount()==0 && !parent->text(colum).contains( searchString, Qt::CaseInsensitive )) {
        parent->setHidden(true);
    }
    for( int i = 0; i < parent->childCount(); ++i) {
        QTreeWidgetItem *child = parent->child(i);
    QString txtChild=child->text(colum);
    if(hamza==true){
        txtChild.replace(trUtf8("أ"),trUtf8("ا"));
        txtChild.replace(trUtf8("إ"),trUtf8("ا"));
        txtChild.replace(trUtf8("ؤ"),trUtf8("و"));
        // txtChild.replace(trUtf8("ئ"),trUtf8(""));
    }
        if( parent->isHidden() )
            hiddenCount++;
        else if(child->childCount()>0
                && !txtChild.contains( searchString, Qt::CaseInsensitive ) ) {//لا يحمل النص وله ابناء
            if( !searchTreeForString( searchString, child ,false,topindex,view,colum,hamza)) {
                child->setHidden(true);
                hiddenCount++;
            }
        } else if(child->childCount()>0// يحمل النص  له ابناء
                  && ( txtChild.contains( searchString, Qt::CaseInsensitive ) ) ){
            searchTreeForString( searchString, child ,false,topindex,view,colum,hamza);
        } else if(child->childCount()==0//لا يحمل النص وليس له ابناء
                  && ( !txtChild.contains( searchString, Qt::CaseInsensitive ) ) ) {
            child->setHidden(true);
            hiddenCount++;
        }
        if (itemtop==true){
            if(child->isHidden()){hiddenparent++;}
        }
    }
    QTreeWidgetItem *toplevel=view->topLevelItem(topindex);
    int topc=toplevel->childCount();
    QString txtTop=toplevel->text(colum);
    if(hamza==true){
        txtTop.replace(trUtf8("أ"),trUtf8("ا"));
        txtTop.replace(trUtf8("إ"),trUtf8("ا"));
        txtTop.replace(trUtf8("ؤ"),trUtf8("و"));
    }
    if( hiddenparent == topc  && !txtTop.contains( searchString, Qt::CaseInsensitive )){
        toplevel->setHidden(true);
    }
    if( hiddenCount == parent->childCount() )
        return false;
    return true;
}
//! [3]  البحث في الشجرة
bool Database::showAllItems( QTreeWidgetItem* parent,QTreeWidget *view )
{
    for( int i = 0; i < parent->childCount(); i++ ) {
        view->setItemHidden(parent->child(i),false);
        showAllItems( parent->child( i) ,view);
    }
    return true;
}
//--------------------------------search- treeview------------------------------

//---------------------------------search --------------------
//! البحث في القرءان الكريم
void Database::searchInQuran(QTreeWidget *view,QString arg1,QString arg2,QString orAnd ,int option)
{

        if(openQuranDb(false)==false)
                return;
        //-----------------------
        QString querytxt;
        if(option==3){
                querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1%' %2 nass_safy like'%%3%' ORDER BY id").arg(arg1).arg(orAnd).arg(arg2);
        }else{
                if(option==0){
                        querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1%' ORDER BY id").arg(arg1);
                }else if(option==1){
                        querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%1%' ORDER BY id").arg(arg1);
                }else if(option==2){
                        querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1' ORDER BY id").arg(arg1);
                }
        }

        QSqlQuery query(querytxt,db);
        if(query.lastError().isValid()){
                qDebug()<<query.lastError();
                QMessageBox::information(0,"",query.lastError().text());
                return ;
        }
        //query.next();
        view->clear();
        while (query.next()) {
                int fieldId= query.record().indexOf("id");
                QString myid= query.value(fieldId).toString();
                int fieldTxt= query.record().indexOf("nass_safy");
                QString mytext = query.value(fieldTxt).toString();
                int fieldSura= query.record().indexOf("sura");
                QString mysura= query.value(fieldSura).toString();
                int fieldAya= query.record().indexOf("aya");
                QString myaya= query.value(fieldAya).toString();
                QTreeWidgetItem *item=new  QTreeWidgetItem(view);

                int fieldpage= query.record().indexOf("safha");
                QString mypage= query.value(fieldpage).toString();

                item->setText(0,mysura);
                item->setText(1,myaya);
                item->setText(2,mytext);
                item->setText(3,myid);
                //  QMessageBox::information(0,"",mytext);
                qDebug()<< mypage;
                // query.next();
        }
//        int i=query.record().count();
//        for (int r = 0; r < i; ++r) {
//                qDebug()<< query.record().fieldName(r);
//        }

        openDb(databaseName);

}
//! البحث في التفاسير
void Database::searchInTefsir(QTreeWidget *view,QString arg1,QString arg2,QString orAnd ,int option)
{

        QString querytxt;
        if(option==3){
                querytxt=QString("SELECT* FROM %4 WHERE text like '%%1%' %2 text like'%%3%' ORDER BY id")
                                .arg(arg1).arg(orAnd).arg(arg2).arg(tableName);
        }else if(option==0){

                        querytxt=QString("SELECT* FROM %1 WHERE text like '%%2%' ORDER BY id").arg(tableName).arg(arg1);
        }


        QSqlQuery query(querytxt,db);
        if(query.lastError().isValid()){
                qDebug()<<query.lastError();
                QMessageBox::information(0,"",query.lastError().text());
                return ;
        }
        //query.next();
        view->clear();
        while (query.next()) {
                int fieldId= query.record().indexOf("id");
                QString myid= query.value(fieldId).toString();

                int fieldSura= query.record().indexOf("sura");
                QString mysura= query.value(fieldSura).toString();
                int fieldAya= query.record().indexOf("aya");
                QString myaya= query.value(fieldAya).toString();
                QTreeWidgetItem *item=new  QTreeWidgetItem(view);
                item->setText(0,mysura);
                item->setText(1,myaya);
                      item->setText(2,myid);

        }


}
//! لبيحث في الصفحة
bool  Database::searchInDoc(QTextDocument *document,QString searchString,QString searchString2,QColor color)
{

        bool firstModified=false;
        if (document->isModified()){
                firstModified=true;
        }
        bool found = false;
        //     if (findMultiFind==false){
        //         chargelistStrToFind(searchString);
        //     }else{
        //         chargelistStrMultiFind(searchString);
        //     }
        QStringList list;
        list<<searchString<<searchString2;
        for (int i=0;i<2;i++)   {
            QString findText=list.at(i);

            if(!findText.isEmpty()){
                    QFont font= document->defaultFont();
                   // document->undo();
                    QTextCursor highlightCursor(document);
                    QTextCursor cursor(document);
                    cursor.beginEditBlock();

                    QTextCharFormat colorFormat(highlightCursor.charFormat());
                    colorFormat.setForeground(color);
                    colorFormat.setFont(font);
                    colorFormat.setFontPointSize(font.pointSize());
                    while (!highlightCursor.isNull() && !highlightCursor.atEnd()) {
                            highlightCursor = document->find(findText, highlightCursor, QTextDocument::FindCaseSensitively);

                            if (!highlightCursor.isNull()) {
                                    found = true;
                                    highlightCursor.movePosition(QTextCursor::Right,
                                                                 QTextCursor::KeepAnchor,-1);

                                    highlightCursor.mergeCharFormat(colorFormat);

                            }
                    }
                    cursor.endEditBlock();
            }
        }

        if (found == false) {
                return false;
        }
        document->setModified(firstModified);
        return true;
}

QStringList  Database::getQuranPage(int pos)
{
          QStringList list;
        if(openQuranDb(false)==false)
                return list;

        QString querytxt=QString("SELECT* FROM quran WHERE id=%1 ORDER BY id").arg(QString::number(pos));

        QSqlQuery query(querytxt,db);
        if(query.lastError().isValid()){
            qDebug()<<query.lastError();
             QMessageBox::information(0,"",query.lastError().text());
            return list;
        }
        query.next();
        int fieldpage= query.record().indexOf("safha");
        QString mypage= query.value(fieldpage).toString();
        list<<"page:"+mypage;
     querytxt=QString("SELECT* FROM quran WHERE safha=%1 ORDER BY id").arg(mypage);
  query.exec(querytxt);
     while (query.next()) {

             int fieldTxt= query.record().indexOf("text");
             QString mytext = query.value(fieldTxt).toString();

             int fieldAya= query.record().indexOf("aya");
             QString myaya= query.value(fieldAya).toString();

             int fieldsura= query.record().indexOf("sura");
             QString mysura= query.value(fieldsura).toString();

             int fieldid= query.record().indexOf("id");
             QString myid= query.value(fieldid).toString();

             list<<"sura:"+mysura<<"id:"+myid<<"aya:"+myaya<<mytext;
             //  QMessageBox::information(0,"",mytext);
             qDebug()<< mypage<<mytext<<myaya;
             // query.next();
     }
        openDb(databaseName);
           return list;
}
QStringList  Database::getQuranForPage(int page)
{
          QStringList list;
        if(openQuranDb(false)==false)
                return list;


        list<<"page:"+QString::number(page);
   QString  querytxt=QString("SELECT* FROM quran WHERE safha=%1 ORDER BY id").arg(QString::number(page));
 QSqlQuery query(querytxt,db);
     while (query.next()) {

             int fieldTxt= query.record().indexOf("text");
             QString mytext = query.value(fieldTxt).toString();

             int fieldAya= query.record().indexOf("aya");
             QString myaya= query.value(fieldAya).toString();

             int fieldsura= query.record().indexOf("sura");
             QString mysura= query.value(fieldsura).toString();

             int fieldid= query.record().indexOf("id");
             QString myid= query.value(fieldid).toString();

             list<<"sura:"+mysura<<"id:"+myid<<"aya:"+myaya<<mytext;
             //  QMessageBox::information(0,"",mytext);
             qDebug()<< page<<mytext<<myaya;
             // query.next();
     }
        openDb(databaseName);
           return list;
}
/*****************************************************************************
 *********************************CMD*****************************************
 ******************************************************************************/

void  Database::cmdGetTafsirName()
{
        QFile file;

        //-تحميل التفاسير
        file.setFileName(appPath+"/tafasir/tafasirInfo");
        if(file.open( QFile::ReadOnly)){
                QTextStream textStream(&file);
               // textStream.setCodec(QTextCodec::codecForName("UTF-8"));
                QString line;
               int id=0;
                line = textStream.readLine();//premier line
                while (!line.isNull()) {
                        id++;
                        QString txtdata=line.section(",",0,0);
                        QString txt=line.section(",",1,1);
                        qDebug()<<id<<" -  "+txt<<" id= "<<txtdata;

                        line = textStream.readLine();
                }

           }
        file.close();
}
void Database::cmdGetTranslation(int sura,int aya,const QString &tafsir)
{
        if(sura<0||sura>114){
                qDebug()<< trUtf8("لا توجد سورة بهذا الرقم")<<QString::number(sura);
                return;
        }
        int aCount=cmdGetAyatNumber( sura,false);
        if(aya<0||aya>aCount){
                qDebug()<< trUtf8("لا توجد آية بهذا الرقم :")+QString::number(aya);
                qDebug()<< trUtf8("عدد الايات في هذه السورة هو : ")+QString::number(aCount);
                return;
        }
        //open data-----
        QString dataName=    appPath+"/tafasir/"+tafsir;

        QFileInfo fi(dataName);
      QString  tName = fi.completeBaseName();
        db.setDatabaseName(dataName);
        QString txt="no database";
        if(!db.open()){

            txt=db.lastError().text();
          qDebug()<<txt;
          return;

        }
        //end open data-----

     QString   querytxt=QString("SELECT* FROM %1 WHERE sura='%2' and aya='%3' ORDER BY id")
                        .arg(tName).arg(QString::number(sura)).arg(QString::number(aya));

  //  QString querytxt=QString("SELECT* FROM %1 WHERE id=%2 ORDER BY id").arg(tName).arg(QString::number(pos));

    QSqlQuery query(querytxt,db);
    if(query.lastError().isValid()){
        qDebug()<<query.lastError();
          // QMessageBox::information(0,"",query.lastError().text());
        return ;
    }
    query.next();
    int fieldNo = query.record().indexOf("text");
    if (fieldNo==-1){
        fieldNo = query.record().indexOf("tafsir");
    }
    QString mytext = query.value(fieldNo).toString();
    int fieldSura= query.record().indexOf("sura");
    QString mysura= query.value(fieldSura).toString();
    int fieldAya= query.record().indexOf("aya");
    QString myaya= query.value(fieldAya).toString();
    query.next();
     qDebug()<<mytext;
    qDebug()<<"sura "+mysura<<"aya "+myaya;
    return ;
}
int Database::cmdGetAyatNumber(int sura,bool debug)
{
        if(openQuranDb(true)==false)
                return 0;
        //-----------------------
        QString   querytxt=QString("SELECT* FROM sura_info WHERE id='%1' ORDER BY id").arg(QString::number(sura));
        QSqlQuery query(querytxt,db);
        query.first();
        int fieldAya= query.record().indexOf("ayats");
        QString myaya= query.value(fieldAya).toString();

        int fieldsura= query.record().indexOf("sura");
        QString mysura= query.value(fieldsura).toString();

        if(debug==true)
        qDebug()<<mysura+trUtf8(" عدد الايات : ")+myaya;

        return myaya.toInt();
}
QString Database::cmdGetSuraName(int sura,bool debug)
{
        if(openQuranDb(true)==false)
                return 0;
        //-----------------------
        QString   querytxt=QString("SELECT* FROM sura_info WHERE id='%1' ORDER BY id").arg(QString::number(sura));
        QSqlQuery query(querytxt,db);
        query.first();

        int fieldsura= query.record().indexOf("sura");
        QString mysura= query.value(fieldsura).toString();

        if(debug==false)
                openDb(databaseName);
        qDebug()<<mysura;

        return mysura;
}

void Database::cmdGetAyat(int sura,int aya)
{
        if(sura<0||sura>114){
                qDebug()<< trUtf8("لا توجد سورة بهذا الرقم")<<QString::number(sura);
                return;
        }
        int aCount=cmdGetAyatNumber( sura,false);
        if(aya<0||aya>aCount){
                qDebug()<< trUtf8("لا توجد آية بهذا الرقم :")+QString::number(aya);
                qDebug()<< trUtf8("عدد الايات في هذه السورة هو : ")+QString::number(aCount);
                return;
        }
        //open data-----
        if(openQuranDb(true)==false)
                return;
        //end open data-----


   QString  querytxt=QString("SELECT* FROM quran WHERE sura='%1' and aya ='%3' ORDER BY id").arg(QString::number(sura)).arg(QString::number(aya));

  //  QString querytxt=QString("SELECT* FROM %1 WHERE id=%2 ORDER BY id").arg(tName).arg(QString::number(pos));

    QSqlQuery query(querytxt,db);
    if(query.lastError().isValid()){
        qDebug()<<query.lastError();
          // QMessageBox::information(0,"",query.lastError().text());
        return ;
    }
    query.next();
    int fieldNo = query.record().indexOf("nass_safy");

    QString mytext = query.value(fieldNo).toString();
    int fieldSura= query.record().indexOf("sura");
    QString mysura= query.value(fieldSura).toString();
    int fieldAya= query.record().indexOf("aya");
    QString myaya= query.value(fieldAya).toString();
    query.next();

    qDebug()<<mytext+"\n["+mysura<<" : "+myaya+"]";
    return ;
}
void Database::cmdSearchInQuran(QString searchString )
{
        //open data-----
        if(openQuranDb(true)==false)
                return;
        //end open data-----
    QString    querytxt=QString("SELECT* FROM quran WHERE nass_safy like '%%1%' ORDER BY id").arg(searchString);

    QSqlQuery query(querytxt,db);
    if(query.lastError().isValid()){
        qDebug()<<query.lastError();

        return ;
    }


    while (query.next()) {

            int fieldTxt= query.record().indexOf("nass_safy");
            QString mytext = query.value(fieldTxt).toString();
            int fieldSura= query.record().indexOf("sura");
            QString mysura= query.value(fieldSura).toString();
            int fieldAya= query.record().indexOf("aya");
            QString myaya= query.value(fieldAya).toString();



            qDebug()<< mysura+"-"+myaya+"("+mytext+")";

    }
}
