#include <QApplication>
#include "mainwindow.h"
#include "database.h"
#include <QTextCodec>
#include <QTranslator>
#include <QLibraryInfo>
#include <QDebug>
#include <QFontDatabase>
#include <QDir>


int main(int argc, char *argv[])
{
        QApplication a(argc, argv);
        a.setApplicationName("QuranMufasir");
        a.setApplicationVersion("0.2");
        a.setOrganizationName("abouzakaria");
        a.setWindowIcon(QIcon::fromTheme("mtafsir",QIcon(":/images/mtafsir.png")));
        QString txt=QString(QObject::trUtf8(
                                    "QuranMufasir The electronic Holly Quran tefsir Version : %1 \n"
                                    "طريقة الاستعمال: mtafsir [options]\n"
                                    "الخيارات:\n"
                                    "-h,--help                             أظهر المساعدة حول الخيارات.\n"
                                    "-l,--list                             قائمة بجميع التفاسير المتاحة .\n"
                                    "-n,--number  <int sura>               عدد الايات في السورة .\n"
                                    "-t,--translat  <int sura> <int aya> <string tefsir> \n"
                                    "                                      جلب التفسير للسورة والاية من التفسير المحدد\n"
                                    "-a,--aya   <int sura> <int aya>       جلب الاية المحددة من السورة المحددة .\n"
                                    "-f,--find   <string>                  بحث في القرءان عن نص محدد.\n"
                                    "مثال:\n"
                                     " السورة الخامسة الاية السادسة تفسير السعدي: 'mtafsir -t 5 6 sa3dy.db'.\n"
                                    )).arg(a.applicationVersion());


        //---cmd------
        const QStringList args = QCoreApplication::arguments();
        QString   goPos1 ;
        if (args.count() >1) {
                goPos1 = args.at(1);
                Database d;
                if (args.count() ==2){

                        if (goPos1.toLower()==("--list")||goPos1.toLower()==("-l"))
                                d.cmdGetTafsirName();

                        if (goPos1.toLower()==("-h")||goPos1.toLower()==("--help"))
                                qDebug()<<txt;

                }
                if (args.count() ==3){

                        if (goPos1.toLower()==("-n")||goPos1.toLower()==("--number"))
                                d.cmdGetAyatNumber(args.at(2).toInt(),true);

                        if (goPos1.toLower()==("-f")||goPos1.toLower()==("--find"))
                                d.cmdSearchInQuran(args.at(2));

                }
                if (args.count() ==4){

                        if (goPos1.toLower()==("-a")||goPos1.toLower()==("--aya"))
                                d.cmdGetAyat(args.at(2).toInt(),args.at(3).toInt());

                }
                if (args.count() ==5){

                        if (goPos1.toLower()==("-t")||goPos1.toLower()==("--translat"))
                                d.cmdGetTranslation(args.at(2).toInt(),args.at(3).toInt(),args.at(4));

                }
                return 0;
        }
        QString translatorFileName = QLatin1String("qt_ar");
        // translatorFileName += QLocale::system().name();
        QTranslator *translatorsys = new QTranslator(&a);
        if (translatorsys->load(translatorFileName, QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
                a.installTranslator(translatorsys);
        QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
        //-------مجلد البرنامج--------
        QDir appDir(qApp->applicationDirPath());

        appDir.cdUp();
        QString appPath=  appDir.absolutePath()+"/share/mtafsir";

        QFontDatabase::addApplicationFont(appPath+"/ARABSQ.TTF");
         QFontDatabase::addApplicationFont(appPath+"/amiri-quran.ttf");
         QFontDatabase::addApplicationFont(appPath+"/trado.ttf");
a.setLayoutDirection(Qt::RightToLeft);
        MainWindow w;
        w.show();
        
        return a.exec();
}
