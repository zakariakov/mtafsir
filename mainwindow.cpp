#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialogoptions.h"
#include "ui_dialogAbout.h"
#include <QDir>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>
#include <QSettings>
#include <QPrintDialog>
#include <QPrinter>

//#include <QSound>
MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{

        //-------اعدادات الادوات--------
        ui->setupUi(this);

        comboTafsir=new QComboBox;
        comboSura=new QComboBox;
        spinAya=new  QSpinBox;
        lineSearch=new  QLineEdit;
        QAction  *actSearch=new QAction(trUtf8("ابحث"),this);
        QAction  *actPage=new QAction(trUtf8("عرض الصفحات"),this);
        actNextAya=new QAction(trUtf8("الاية التالية"),this);
        actPrevAya=new QAction(trUtf8("الاية السابقة"),this);
        actNextSura=new QAction(trUtf8("السورة التالية"),this);
        actPrevSura=new QAction(trUtf8("السورة السابقة"),this);

        QAction  *actZoomIn=new QAction(trUtf8("تكبير النص"),this);
        QAction  *actZoomOut=new QAction(trUtf8("تصغير النص"),this);

        actNextTefsir=new QAction(trUtf8("التفسير التالي"),this);
        actPrevTefsir=new QAction(trUtf8("التفسير السابق"),this);

        QAction *actDock=ui->dockWidget->toggleViewAction();
        QAction  *actOption=new QAction(trUtf8("الاعدادات"),this);
        QAction *actAbout=new QAction(trUtf8("حول"),this);
        QAction  *actQuit=new QAction(trUtf8("خروج"),this);
        QAction  *actPrint=new QAction(trUtf8("طباعة الصفحة"),this);
        //        QWidget *wid=new QWidget;
        //        QSpacerItem *horizontalSpacer = new QSpacerItem(20, 10, QSizePolicy::Expanding, QSizePolicy::Minimum);
        //        QHBoxLayout *horizontalLayout = new QHBoxLayout(wid);
        //        horizontalLayout->addItem(horizontalSpacer);
        //-------اضافات الى لوحة الادوات--------
        ui->mainToolBar->addAction(actOption);
        ui->mainToolBar->addAction(actDock);
        ui->mainToolBar->addAction(actPrint);
        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addWidget(comboSura);
        ui->mainToolBar->addWidget(spinAya);
        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addWidget(comboTafsir);
        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addAction(actPage);
        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addWidget(lineSearch);
        ui->mainToolBar->addAction(actSearch);
        ui->mainToolBar->addSeparator();

        ui->mainToolBar->addAction(actPrevSura);
        ui->mainToolBar->addAction(actPrevAya);
        ui->mainToolBar->addAction(actNextAya);
        ui->mainToolBar->addAction(actNextSura);

        ui->mainToolBar->addSeparator();
        ui->mainToolBar->addAction(actZoomIn);
        ui->mainToolBar->addAction(actZoomOut);

        ui->mainToolBar->addSeparator();

        this->addAction(actNextTefsir);
        this->addAction(actPrevTefsir);
        //-------اضافات الى القوائم--------
        ui->menuFile->addAction(actOption);
        //  ui->menuFile->addAction(actDock);
        ui->menuFile->addAction(actPrint);
        ui->menuFile->addSeparator();
        ui->menuFile->addAction(actQuit);
        ui->menuView->addAction(actDock);
        ui->menuView->addAction(ui->mainToolBar->toggleViewAction());
        ui->menuView->addSeparator();
        ui->menuView->addAction(actPage);
        ui->menuView->addSeparator();
        ui->menuView->addAction(actZoomIn);
        ui->menuView->addAction(actZoomOut);

        ui->menuEdit->addAction(actPrevAya);
        ui->menuEdit->addAction(actNextAya);
          ui->menuEdit->addAction(actPrevSura);
        ui->menuEdit->addAction(actNextSura);

        ui->menuEdit->addSeparator();
        ui->menuEdit->addAction(actNextTefsir);
        ui->menuEdit->addAction(actPrevTefsir);


        ui->menuHelp->addAction(actAbout);
        //-------الاشارات--------
        connect(comboSura, SIGNAL(activated(int)), this, SLOT(goSura(int )));
        connect(comboSura, SIGNAL(currentIndexChanged(int)), this, SLOT(setSpinAyaMaximum(int)));
        connect(spinAya, SIGNAL(editingFinished()), this, SLOT(goAya()));
        connect(comboTafsir, SIGNAL(activated(int)), this, SLOT(tefsirChanged(int)));

        connect(lineSearch, SIGNAL(returnPressed()), this, SLOT(searchString()));
        connect(actSearch, SIGNAL(triggered()), this, SLOT(searchString()));

        connect(actPage, SIGNAL(triggered()), this, SLOT(goPage()));
        connect(actPrint, SIGNAL(triggered()), this, SLOT(filePrint()));

        connect(actNextAya, SIGNAL(triggered()), this, SLOT(dataNextAya()));
        connect(actPrevAya, SIGNAL(triggered()), this, SLOT(dataPrevAya()));
        connect(actNextSura, SIGNAL(triggered()), this, SLOT(dataNextSura()));
        connect(actPrevSura, SIGNAL(triggered()), this, SLOT(dataPrevSura()));

        connect(actZoomIn, SIGNAL(triggered()), ui->textEdit, SLOT(zoomIn()));
        connect(actZoomOut, SIGNAL(triggered()), ui->textEdit, SLOT(zoomOut()));

        connect(actNextTefsir, SIGNAL(triggered()), this, SLOT(nextTefsir()));
        connect(actPrevTefsir, SIGNAL(triggered()), this, SLOT(prevtTefsir()));

        connect(actOption, SIGNAL(triggered()), this, SLOT(getOptions()));

        connect(actAbout, SIGNAL(triggered()), this, SLOT(AboutThisApp()));
        connect(actQuit, SIGNAL(triggered()), qApp, SLOT(quit()));
        //-------الاختصارات--------
        actOption->setShortcut(QKeySequence("Ctrl+S"));

        actNextAya->setShortcut(QKeySequence("Ctrl+Left"));
        actPrevAya->setShortcut(QKeySequence("Ctrl+Right"));
        actNextSura->setShortcut(QKeySequence("Ctrl+Up"));
        actPrevSura->setShortcut(QKeySequence("Ctrl+Down"));
        actZoomIn->setShortcut(QKeySequence::ZoomIn);
        actZoomOut->setShortcut(QKeySequence::ZoomOut);
        actPage->setShortcut(QKeySequence("Ctrl+N"));
        actNextTefsir->setShortcut(QKeySequence("Alt+Left"));
        actPrevTefsir->setShortcut(QKeySequence("Alt+Right"));

        ui->dockWidget->toggleViewAction()->setShortcut(QKeySequence(tr("Ctrl+F")));
        actAbout->setShortcut(QKeySequence("F1"));
        actQuit->setShortcut(QKeySequence::Quit);
        actPrint->setShortcut(QKeySequence::Print);
        //-------التعريفات على الادوات--------
        actOption->setToolTip(actOption->text()+"\n"+actOption->shortcut().toString());
        actDock->setToolTip(ui->dockWidget->toggleViewAction()->text()
                            +"\n"+ui->dockWidget->toggleViewAction()->shortcut().toString());

        actNextAya->setToolTip(actNextAya->text()+"\n"+actNextAya->shortcut().toString());
        actPrevAya->setToolTip(actPrevAya->text()+"\n"+actPrevAya->shortcut().toString());
        actNextSura->setToolTip(actNextSura->text()+"\n"+actNextSura->shortcut().toString());
        actPrevSura->setToolTip(actPrevSura->text()+"\n"+actPrevSura->shortcut().toString());
        actZoomIn->setToolTip(actZoomIn->text()+"\n"+actZoomIn->shortcut().toString());
        actZoomOut->setToolTip(actZoomOut->text()+"\n"+actZoomOut->shortcut().toString());
        actSearch->setToolTip(trUtf8("نفذ البحث"));
        actAbout->setToolTip(actAbout->text()+"\n"+actAbout->shortcut().toString());
        actQuit->setToolTip(actQuit->text()+"\n"+actQuit->shortcut().toString());
        actPage->setToolTip(actPage->text()+"\n"+actPage->shortcut().toString());
        actPrint->setToolTip(actPrint->text()+"\n"+actPrint->shortcut().toString());
        //-------شريط المعلومات--------
        actOption->setStatusTip(actOption->toolTip());
        actDock->setStatusTip(actDock->toolTip());

        actNextAya->setStatusTip(actNextAya->toolTip());
        actPrevAya->setStatusTip(actPrevAya->toolTip());
        actNextSura->setStatusTip(actNextSura->toolTip());
        actPrevSura->setStatusTip(actPrevSura->toolTip());
        actZoomIn->setStatusTip(actZoomIn->toolTip());
        actZoomOut->setStatusTip(actZoomOut->toolTip());
        actAbout->setStatusTip(actAbout->toolTip());
        actQuit->setStatusTip(actQuit->toolTip());
        comboSura->setStatusTip(trUtf8("اختر السورة"));
        comboTafsir->setStatusTip(trUtf8(" Alt+Left للتفسير التالي او Alt+right للتفسير السابق اختر التفسير الذي سيتم عرضه "));
        actSearch->setStatusTip(trUtf8("نفذ البحث"));
        actPage->setStatusTip(actPage->toolTip());
        actPrint->setStatusTip(actPrint->toolTip());
        //-------الايقونات--------
        actOption->setIcon(QIcon::fromTheme("document-properties",QIcon(":/images/document-properties.png")));
        actDock->setIcon(QIcon::fromTheme("find",QIcon(":/images/find.png")));

        actNextAya->setIcon(QIcon::fromTheme("go-previous",QIcon(":/images/go-previous.png")));
        actPrevAya->setIcon(QIcon::fromTheme("go-next",QIcon(":/images/go-next.png")));
        actNextSura->setIcon(QIcon::fromTheme("go-first",QIcon(":/images/go-first.png")));
        actPrevSura->setIcon(QIcon::fromTheme("go-last",QIcon(":/images/go-last.png")));
        actZoomIn->setIcon(QIcon::fromTheme("zoom-in",QIcon(":/images/zoom-in.png")));
        actZoomOut->setIcon(QIcon::fromTheme("zoom-out",QIcon(":/images/zoom-out.png")));
        actAbout->setIcon(QIcon::fromTheme("help-about",QIcon(":/images/help-about.png")));
        actQuit->setIcon(QIcon::fromTheme("application-exit",QIcon(":/images/gtk-quit.png")));
        actPage->setIcon(QIcon::fromTheme("empty",QIcon(":/images/empty.png")));
        ui->toolButtonGoSearch->setIcon(QIcon::fromTheme("dialog-ok",QIcon(":/images/dialog-ok.png")));
        ui->toolButtonGoSearchTefsir->setIcon(QIcon::fromTheme("dialog-ok",QIcon(":/images/dialog-ok.png")));
        ui->toolBox->setItemIcon(0,QIcon::fromTheme("find",QIcon(":/images/find.png")));
        ui->toolBox->setItemIcon(1,QIcon::fromTheme("stock_text_indent",QIcon(":/images/stock_text_indent.png")));
        actSearch->setIcon(QIcon::fromTheme("dialog-ok",QIcon(":/images/dialog-ok.png")));
        actPrint->setIcon(QIcon::fromTheme("document-print",QIcon(":/images/document-print.png")));

        //-------تخيص خصائص بغض الادوات--------
        ui->treeWidgetSearch->setColumnHidden(3,true);
        ui->treeWidgetSearchTefsir->setColumnHidden(2,true);

        ui->treeWidgetIndex->setColumnHidden(1,true);
        ui->treeWidgetIndex->setColumnHidden(2,true);
        ui->treeWidgetAjzaa->setColumnHidden(1,true);

        spinAya->setPrefix(trUtf8("آية : "));
        spinAya->setToolTip(trUtf8("الاية"));
        lineSearch->setMaximumWidth(150);
        lineSearch->installEventFilter(this);
        lineSearch->setText(trUtf8("بحث"));
        lineSearch->setStyleSheet("QLineEdit {font: italic;color: rgb(115, 115, 115);}");

        ui->lineEditSearchTree->installEventFilter(this);
        ui->lineEditSearchTree->setText(trUtf8("بحث"));
        ui->lineEditSearchTree->setStyleSheet("QLineEdit {font: italic;color: rgb(115, 115, 115);}");
        //-------مجلد البرنامج--------
        QDir appDir(qApp->applicationDirPath());

        appDir.cdUp();
        m_appPath=  appDir.absolutePath()+"/share/mtafsir";

        //-------كلاس قاعدة البيانات--------
        database=new Database();
        database->treeChargeJozaa(ui->treeWidgetAjzaa);
        database->treeChargeSoura(ui->treeWidgetIndex,comboSura);
        //     database->dataChargeSoura(ui->treeWidgetIndex,comboSura);
        //---------toolbox style---------------------------------
        int mred= this->palette().color(QPalette::Light).red();
        int mgreen= this->palette().color(QPalette::Light).green();
        int mblue= this->palette().color(QPalette::Light).blue();
        QString colorHighlighName=    this->palette().color(QPalette::Highlight).name();

        QString colorName=    this->palette().color(QPalette::HighlightedText).name();
        //   QString colorName=    this->palette().color(QPalette::BrightText).name();
        QString stylbox=QString("QToolBox::tab {"
                                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(%1, %2, %3, 80), stop:1 rgba(%1, %2, %3, 80));"
                                 "border-radius: 5px;}"
                                "QToolBox::tab:hover { "
                                "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 80), stop:1 rgba(%1, %2, %3, 200));"
                                "font: italic;  }"
                                        " QToolBox::tab:selected {"
        " background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 %4, stop:0.172222 %4, stop:0.177778 rgba(%1, %2, %3, 200), stop:0.65 rgba(255, 255, 255, 0));"
        " }").arg(QString::number(mred)).arg(QString::number(mgreen)).arg(QString::number(mblue)).arg(colorHighlighName)  ;


     /*   "QToolBox::tab:selected { "
        "background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(%1, %2, %3, 255), stop:1 rgba(%1, %2, %3, 100));"
        "}"*/
        ui->toolBox->setStyleSheet(stylbox);
        ui->toolBox->setCurrentIndex(1);
        //-تحميل التفاسير
        chargeDataTools();
        changeSettings();
        //---------------------------
        loadSettings();
        //


        QSettings setting(QApplication::applicationName(),"settings");
        setting.beginGroup("Geometry");
        this->restoreGeometry(setting.value("geo_data").toByteArray());
        this->restoreState( setting.value("layout_data").toByteArray());
        setting.endGroup();
}

MainWindow::~MainWindow()
{
        saveSettings();
        delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
 QLineEdit *lineT = qobject_cast<QLineEdit *>(obj);
        if (obj ==  lineT) {

                if (event->type() == QEvent::FocusIn &&lineT->text()==trUtf8("بحث")) {
                        lineT->setText("");
                        lineT->setStyleSheet("");
                        return true;
                }else if (event->type() == QEvent::FocusOut && lineT->text().isEmpty()){

                        lineT->setText(trUtf8("بحث"));
                        lineT->setStyleSheet("QLineEdit {font: italic;color: rgb(115, 115, 115);}");
                        return true;
                }

        }
        return QMainWindow::eventFilter(obj, event);
}
void MainWindow::loadSettings()
{
        QSettings setting(QApplication::applicationName(),"settings");

        setting.beginGroup("Main");
        m_pos =setting.value("Pos",1).toInt();
        m_tIndex=setting.value("Tefsir",0).toInt();


        setting.endGroup();

        comboTafsir->setCurrentIndex(m_tIndex);

        tefsirChanged(m_tIndex);

}
void MainWindow::changeSettings()
{
        QSettings setting(QApplication::applicationName(),"settings");

        setting.beginGroup("Main");

        m_fontQuran=setting.value("fontQuran","Amiri Quran").toString();
        m_fontTafsir=setting.value("fontTafsir","Traditional Arabic").toString();
        m_fontSize=setting.value("fontSize",22).toInt();
        m_fontColor=setting.value("fontColor",QColor("#000000")).value<QColor>();
        m_backColor=setting.value("backColor",QColor("#FFFFFF")).value<QColor>();
        m_symbolColor=setting.value("symbolColor",QColor("#008000")).value<QColor>();
        m_findColor=setting.value("findColor",QColor("#FF0000")).value<QColor>();
        setting.endGroup();



        QFont font;
        font.setFamily(m_fontTafsir);
        font.setPointSize(m_fontSize);
        ui->textEdit->document()->setDefaultFont(font);
        ui->textEdit->setFont(font);
       setCurentPos(m_pos);
}

void MainWindow::saveSettings()
{
        qDebug()<<comboTafsir->currentIndex();
        QSettings setting(QApplication::applicationName(),"settings");

        setting.beginGroup("Main");

        setting.setValue("Pos",m_pos);
        setting.setValue("Tefsir",comboTafsir->currentIndex());



        setting.endGroup();

        setting.beginGroup("Geometry");
        setting.setValue("geo_data", saveGeometry());
        setting.setValue("layout_data", saveState(0));
        setting.endGroup();
}

//! تحميل معلومات التفاسير
void MainWindow::chargeDataTools()
{
        QFile file;

        //-تحميل التفاسير
        file.setFileName(m_appPath+"/tafasir/tafasirInfo");
        if(file.open( QFile::ReadOnly)){
                QTextStream textStream(&file);
                textStream.setCodec(QTextCodec::codecForName("UTF-8"));
                QString line;
                //      QList<QAction *>myListActionTefsir;
                //      QActionGroup *actTefsirGroup=new QActionGroup(this);
                line = textStream.readLine();//premier line
                while (!line.isNull()) {
                        QString txtdata=line.section(",",0,0);
                        QString txt=line.section(",",1,1);

                        comboTafsir->addItem(txt,txtdata);

                        line = textStream.readLine();
                }


        }
        file.close();


}
//! تحديد عدد الايات في ادات سبين بوكس
void MainWindow::setSpinAyaMaximum(int index)
{

        QVariant txt=comboSura->itemData(index);

        QString i =txt.toString().section(",",1,1);
        spinAya->setMaximum(i.toInt());
        spinAya->setMinimum(1);

}
//! الذهاب الى سورة معينة
void MainWindow::goSura(int index)
{


        // i/nt idx=comboSura->currentIndex();
        QVariant txt=comboSura->itemData(index);

        QString pos=txt.toString().section(",",0,0);

        setCurentPos(pos.toInt());
}
//! الذهاب الى اية معينة
void MainWindow::goAya()
{
        int idx=comboSura->currentIndex();
        QVariant txt=comboSura->itemData(idx);
        QString pos=txt.toString().section(",",0,0);
        setCurentPos(pos.toInt()+spinAya->value()-1);
}
//! عتد تغير الموضع
void MainWindow::setCurentPos(int pos)
{
        ui->textEdit->clear();
        m_pos=pos;
        QString translation=( database->getTranslation(pos));
        QString textQuran;
        //تحديد الموضع الحالي في الفهرسة
        QVariant dd=pos;
        QTreeWidgetItem *item=new QTreeWidgetItem;
        QList<QTreeWidgetItem *> found =ui->treeWidgetIndex->findItems( dd.toString(),Qt::MatchExactly | Qt::MatchRecursive,1);
        foreach (item, found){
                ui-> treeWidgetIndex->setCurrentItem(item);
                if(item->parent()){
                        m_sura= ui-> treeWidgetIndex->indexOfTopLevelItem(item->parent());
                        //  qDebug()<<m_sura;
                        comboSura->setCurrentIndex(m_sura);
                        spinAya->setValue(item->data(0,Qt::UserRole).toInt());
                }
                textQuran=(item->text(2));

        }

        QLocale lc(QLocale::Arabic);
        lc.setNumberOptions(QLocale::OmitGroupSeparator);


     QString txt;
      //  المعقوفة عن يمين الاية
 QString right=QString(trUtf8("<p dir='rtl' align=\"right\" ><  font face='AGA Arabesque' size='5' color=%1></font>").arg(m_symbolColor.name()));
        // الاية
 QString center= QString(trUtf8(" <span style=\" font-family:'%1,Arial';\"> %2  </span>").arg(m_fontQuran))
                        .arg(textQuran);
        //المعقوفة عن بسار الاية
        QString left=   QString(trUtf8("<  font face='AGA Arabesque' size='5' color=%1></font>").arg(m_symbolColor.name()));

        QString ayainfo=QString(trUtf8("<font size='2'>  [%1 : %2]</font></p><p>"))
                        .arg(comboSura->currentText().section("-",1,1)).arg(lc.toString(spinAya->value()));
        txt=(right+center+left +ayainfo);
        //عنوان التفسير
//        QString tefsirName=QString(trUtf8("<p dir='rtl' align=\"right\" ><span style=\"  color:%2;\"> %1</span></p><p>"))
//                        .arg(comboTafsir->currentText()).arg(m_findColor.name());

        QString colorhightName=    this->palette().color(QPalette::Highlight).name();
        QString colorhightText=    this->palette().color(QPalette::HighlightedText).name();

        QString tefsirName="<table width=\"100%\" border=\"0\">"
                        "<tr><th width=\"100%\" bgcolor=\""+colorhightName+"\"  scope=\"col\"><font  color="+colorhightText+">"
                        +comboTafsir->currentText()+"</font></th></tr></table>";



        txt+=(tefsirName);
       QRegExp rxD("(\\d+)");
       int posix = 0;
       while ((posix = rxD.indexIn(translation, posix)) != -1) {

           translation.remove(posix,rxD.matchedLength());
           translation.insert(posix,lc.toString(rxD.cap(1).toInt()));


           posix += rxD.matchedLength();
       }
        translation=translation.replace(trUtf8("صلى الله عليه وسلم"),QString("<  font face='AGA Arabesque' size='3' color=%2>%1</font>").arg(trUtf8("\357\201\262")).arg(m_symbolColor.name()));
        translation=translation.replace(trUtf8("عليه السلام"),QString("<  font face='AGA Arabesque' size='3' color=%2>%1</font>").arg(trUtf8("\357\201\265")).arg(m_symbolColor.name()));
        translation=translation.replace(trUtf8("عز وجل"),QString("<  font face='AGA Arabesque' size='3' color=%2>%1</font>").arg(trUtf8("\357\201\225")).arg(m_symbolColor.name()));

        translation=translation.replace(trUtf8("رضي الله عنهم"),QString("<  font face='AGA Arabesque' size='3' color=%2>%1</font>").arg(trUtf8("\357\201\264")).arg(m_symbolColor.name()));

        translation=translation.replace(trUtf8("رضي الله عنه"),QString("<  font face='AGA Arabesque' size='3' color=%2>%1</font>").arg(trUtf8("\357\201\264")).arg(m_symbolColor.name()));
        translation=translation.replace(trUtf8("* * *"),QString("<p dir='rtl' align=\"center\" ><  font face='AGA Arabesque'  color=%2>%1%1%1</font></p>").arg(trUtf8("\357\200\241")).arg(m_symbolColor.name()));
       // translation=translation.replace(trUtf8("لهوامش :"),QString("<div dir='rtl' align=\"right\" ><  font  size='1' >%1").arg(trUtf8("لهوامش :")));

        QString bgrcolor = "<body bgcolor='"+m_backColor.name()+"'>< font color='"+m_fontColor.name()+"' >";

 txt+=translation;


     ui->textEdit->setHtml(bgrcolor+txt);

}
void MainWindow::QuranPageAnchorClicked(const QString &arg1)
{
        QStringList list;
        if(arg1.startsWith("page:")){
                QString page=arg1;
                int i=page.remove("page:").toInt();
                qDebug()<<i;
                list=     database->getQuranForPage(i);

        }else{
                list=  database->getQuranPage(m_pos);
        }
        QLocale lc(QLocale::Arabic);
        lc.setNumberOptions(QLocale::OmitGroupSeparator);
        QString colorhightName=    this->palette().color(QPalette::Highlight).name();
        QString colorhightText=    this->palette().color(QPalette::HighlightedText).name();

        QString textQuran;
        QString page;
        QString id;
        QString aya;
        QString sura;
        foreach (QString s, list) {
                if(s.contains("page:")){
                        page=s.remove("page:");
                }else if(s.contains("aya:")){
                        aya=s.remove("aya:");
                }else if(s.contains("sura:")){
                        sura=s.remove("sura:");
                        sura= database->cmdGetSuraName(sura.toInt(),false);
                }else if(s.contains("id:")){
                        id=s.remove("id:");

                }else{
                        QString htm;
                        if(aya=="1")
                                htm+="<table width=\"100%\" border=\"0\">"
                                                "<tr><th width=\"100%\" bgcolor=\""+colorhightName+"\" scope=\"col\">"+sura+"</th></tr></table>";;

                        htm+=QString("<a href=\"%1\"> %2</a>") .arg(id).arg(s);
                        QString numAya= QString(trUtf8("<  font  color=%1> ۝%2</font>")).arg(m_symbolColor.name()).arg(lc.toString(aya.toInt()));
                        textQuran+=htm+numAya;
                }

        }

        int pageNext=page.toInt()+1;
        int pagePrev=page.toInt()-1;
        QString htmNext;
        QString htmPrev;
        if(pageNext>604){
                htmNext="";
        }else{
                htmNext=QString("<a href=\"%1\"> %2 </a>&nbsp;&nbsp;&nbsp;&nbsp;(")
                                .arg("page:"+QString::number(pageNext)).arg("<img src=\":/images/go-previous.png\"/>");
        }

        if(pagePrev<1){
                htmPrev="";
        }else{
                htmPrev=QString(")&nbsp;&nbsp;&nbsp;&nbsp;<a href=\"%1\"> %2 </a>   ")
                                .arg("page:"+QString::number(pagePrev)).arg("<img src=\":/images/go-next.png\"/>");
        }
        QString htmltop= QString("<style type=\"text/css\">"
                                 "th {color: %1;text-align: center;font-family:%3;}"
                                 "a:link {text-decoration:none;color: %2;}"
                                 "</style>").arg(colorhightText).arg(m_fontColor.name()).arg(m_fontTafsir);

        QString pageTable="<br><table width=\"100%\" border=\"0\">"
                        "<tr><th width=\"100%\" bgcolor=\""+colorhightName+"\" scope=\"col\">"
                        +htmNext+lc.toString(page.toInt())+htmPrev+"</th></tr></table>";



        QString bgrcolor = "<body bgcolor='"+m_backColor.name()+"'>< font color='"+m_fontColor.name()+"' >";

        QString mypge= QString(trUtf8("<span style=\" font-family:'%1,Arial'; \"> %2  </span>").arg(m_fontQuran))
                        .arg(textQuran);
        ui->textEdit->setHtml(htmltop+bgrcolor+mypge+pageTable);
}
void MainWindow::  goPage()
{
        QuranPageAnchorClicked("");
}

//! عند تغير التفسير
void MainWindow:: tefsirChanged(int indx)
{
        //  QAction *action = qobject_cast<QAction *>(sender());

        QString data=comboTafsir->itemData(indx).toString();

        database->openDb(m_appPath+"/tafasir/"+data);

        setCurentPos(m_pos);
        //qDebug()<<txt;

}
void MainWindow:: nextTefsir()
{
        int count=comboTafsir->count();
      int indx=comboTafsir->currentIndex()+1;

      if(indx==count)indx=0;
      comboTafsir->setCurrentIndex(indx);

       tefsirChanged(indx);

}

void MainWindow:: prevtTefsir()
{
      int count=comboTafsir->count();
      int indx=comboTafsir->currentIndex()-1;

      if(indx<0)indx=count-1;
      comboTafsir->setCurrentIndex(indx);

       tefsirChanged(indx);

}

/*#############################################################
#########################عمليات البحث-#########################
#############################################################*/
//! تفعيل عنصر شجرة السور
void MainWindow::on_treeWidgetIndex_itemActivated(QTreeWidgetItem *item, int /*column*/)
{
        int id =item->text(1).toInt();

        setCurentPos(id);


}
//!  تفعيل عنصر شجرة الاجزاء والاحزاب
void MainWindow::on_treeWidgetAjzaa_itemActivated(QTreeWidgetItem *item, int )
{
        int id =item->text(1).toInt();

        setCurentPos(id);
}

//! تنفيذ البحث في القرءان الكريم
void MainWindow::on_toolButtonGoSearch_clicked()
{
        if(ui->lineEditSearch->text().isEmpty())
                return;


        int option;
        if(ui->radioButtonSearch->isChecked())
                option=0;
        if(ui->radioButtonSearchFirst->isChecked())
                option=1;
        if(ui->radioButtonSearchLast->isChecked())
                option=2;
        if(ui->radioButtonAdvensed->isChecked())
                option=3;
        if (option==3&&ui->lineEditSearchAnd->text().isEmpty())
                return;
        QString orAnd;
        if(ui->checkBoxAnd->isChecked()==true){
                orAnd="and";
        }else if(ui->checkBoxOr->isChecked()==true){
                orAnd="or";
        }
        database->searchInQuran(ui->treeWidgetSearch,
                                ui->lineEditSearch->text(),
                                ui->lineEditSearchAnd->text(),
                                orAnd,
                                option);
}
//! البحث في الشجرة القرءان الكريم  عند ادخال النص
void MainWindow::on_lineEditSearchTree_textChanged(const QString &arg1)
{
        if(arg1==trUtf8("بحث"))
                return;
        database->searchInTreeview(ui->treeWidgetIndex,arg1,0,ui->checkBoxHamza->isChecked());
}


//! تفعيل عنصر نتائج شجرة البحث في القرءان الكريم
void MainWindow::on_treeWidgetSearch_itemActivated(QTreeWidgetItem *item, int)
{
        int id =item->text(3).toInt();

        setCurentPos(id);
}
//!  ضغط على نص البحث لتنفيذ عملية الحث القرءان الكريم
void MainWindow::on_lineEditSearch_returnPressed()
{
        on_toolButtonGoSearch_clicked();
}
//! ضغط على نص البحث الثاني لتنفيذ عملية الحث القرءان الكريم
void MainWindow::on_lineEditSearchAnd_returnPressed()
{
        on_toolButtonGoSearch_clicked();
}
//! تنفيذ عملية البحث في التفسير
void MainWindow::on_toolButtonGoSearchTefsir_clicked()
{
        if(ui->lineEditSearchTefsir->text().isEmpty())
                return;


        int option;
        if(ui->radioButtonSearchTefsir->isChecked())
                option=0;

        if(ui->radioButtonAdvensedTefsir->isChecked())
                option=3;

        if (option==3&&ui->lineEditSearchAndTefsir->text().isEmpty())
                return;
        QString orAnd;
        if(ui->checkBoxAndTefsir->isChecked()==true){
                orAnd="and";
        }else if(ui->checkBoxOrTefsir->isChecked()==true){
                orAnd="or";
        }
        database->searchInTefsir(ui->treeWidgetSearchTefsir,
                                 ui->lineEditSearchTefsir->text(),
                                 ui->lineEditSearchAndTefsir->text(),
                                 orAnd,
                                 option);
     int   indx=comboTafsir->currentIndex();
m_curTefsir= comboTafsir->itemData(indx).toString();
}
//! تفعيل عنصر شجرة البحث في التفاسير
void MainWindow::on_treeWidgetSearchTefsir_itemActivated(QTreeWidgetItem *item, int /*column*/)
{
        int  indx=comboTafsir->currentIndex();
        if(m_curTefsir!=comboTafsir->itemData(indx).toString()){
                int index=    comboTafsir->findData(m_curTefsir);
                comboTafsir->setCurrentIndex(index);
                database->openDb(m_appPath+"/tafasir/"+m_curTefsir);

        }
        int id =item->text(2).toInt();

        setCurentPos(id);
        database->searchInDoc(ui->textEdit->document(),ui->lineEditSearchTefsir->text()
                              ,ui->lineEditSearchAndTefsir->text(),m_findColor);
}
//! ضغط على نص البحث الاول لتنفيذ عملية الحث في التفسير
void MainWindow::on_lineEditSearchTefsir_returnPressed()
{
    on_toolButtonGoSearchTefsir_clicked();
}
//! ضغط على نص البحث الثاني لتنفيذ عملية الحث في التفسير
void MainWindow::on_lineEditSearchAndTefsir_returnPressed()
{
    on_toolButtonGoSearchTefsir_clicked();
}
void MainWindow::searchString()
{
        if(lineSearch->text().isEmpty()||lineSearch->text()==trUtf8("بحث")) return;
        database->searchInDoc(ui->textEdit->document(),lineSearch->text()
                              ,"",m_findColor);
}

//! اضافة اوامر الى القائمة المتفرعة من ادات النص
void MainWindow::on_textEdit_customContextMenuRequested(const QPoint &/*pos*/)
{
        QMenu *menu=ui->textEdit->createStandardContextMenu();

        menu->addSeparator();
        menu->addAction(actNextAya);
        menu->addAction(actPrevAya);
        menu->addSeparator();
        menu->addAction(actNextSura);
        menu->addAction(actPrevSura);
        menu->addSeparator();
        menu->addAction(actNextTefsir);
        menu->addAction(actPrevTefsir);

        menu->exec(QCursor::pos());
}
void MainWindow::getOptions()
{
        DialogOptions *dlg=new DialogOptions;
        connect(dlg,SIGNAL(settingsChanged()),this,SLOT(changeSettings()));
        dlg->exec();
}
void MainWindow::AboutThisApp()
{
        QDialog dialog(this);

          Ui::DialogAbout dlgAbout;
          dlgAbout.setupUi(&dialog);
          dlgAbout.labelAppName->setText(trUtf8("القرءان المفسر"));
         dlgAbout.labelVertion->setText(trUtf8("الاصدار : ")+QApplication::applicationVersion());
         dlgAbout.labelGpl->setText(trUtf8("يمكن تعديل او تطوير البرنامج وفقا لشروط الرخصة العموميو جنو GPL "));
         dialog.exec();



}



void MainWindow::on_textEdit_highlighted(const QString &arg1)
{
    ui->statusBar->showMessage(arg1);
}

void MainWindow::on_textEdit_anchorClicked(const QUrl &arg1)
{
    QString pos=arg1.toString();
    if(pos.startsWith("page:")){

            QuranPageAnchorClicked(pos);
    }else{
          setCurentPos(pos.toInt());
    }

}
void MainWindow::filePrint()
{
#ifndef QT_NO_PRINTER
        QPrinter printer(QPrinter::HighResolution);
        QPrintDialog *dlg = new QPrintDialog(&printer, this);
        if (ui->textEdit->textCursor().hasSelection())
                dlg->addEnabledOption(QAbstractPrintDialog::PrintSelection);
        dlg->setWindowTitle(tr("Print Document"));
        if (dlg->exec() == QDialog::Accepted) {
                ui->textEdit->print(&printer);
        }
        delete dlg;
#endif
}



