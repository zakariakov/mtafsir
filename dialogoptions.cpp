#include "dialogoptions.h"
#include "ui_dialogoptions.h"
#include <QSettings>
#include <QDebug>

DialogOptions::DialogOptions(QWidget *parent) :
        QDialog(parent),
        ui(new Ui::DialogOptions)
{
        ui->setupUi(this);
this->setAttribute(Qt::WA_DeleteOnClose);
        QFontDatabase db;
        foreach(int size, db.standardSizes()){
                ui->comboFontSize->addItem(QString::number(size));

        }


        loadSettings();
}

DialogOptions::~DialogOptions()
{
        qDebug()<<"delet";
        delete ui;
}

void DialogOptions::loadSettings()
{
        QSettings setting(QApplication::applicationName(),"settings");

        setting.beginGroup("Main");
        QString fQ=   setting.value("fontQuran","Amiri Quran").toString();
        int indx= ui->fontComboQuran->findText(fQ);
        ui->fontComboQuran->setCurrentIndex(indx);

        QString fT=   setting.value("fontTafsir","Traditional Arabic").toString();
        int ind= ui->fontComboQuran->findText(fT);
        ui->fontComboTefsir->setCurrentIndex(ind);

        ui->comboFontSize->setEditText(setting.value("fontSize",22).toString());
        QColor m_fontColor=setting.value("fontColor",QColor("#000000")).value<QColor>();
        QColor m_backColor=setting.value("backColor",QColor("#FFFFFF")).value<QColor>();
        QColor m_symbolColor=setting.value("symbolColor",QColor("#008000")).value<QColor>();
        QColor m_findColor=setting.value("findColor",QColor("#FF0000")).value<QColor>();
        setting.endGroup();

        btnColorBack=new ButtonColor(m_backColor,this);
        btnColorFont=new ButtonColor(m_fontColor,this);
        btnColorSymbol=new ButtonColor(m_symbolColor,this);
        btnColorFind=new ButtonColor(m_findColor,this);
        ui->horizontalLayoutBack->addWidget(btnColorBack);
        ui->horizontalLayoutFont->addWidget(btnColorFont);
        ui->horizontalLayoutSymbol->addWidget(btnColorSymbol);
        ui->horizontalLayoutFind->addWidget(btnColorFind);
        ui->comboFontSize->setCurrentIndex(ui->comboFontSize->findText(ui->comboFontSize->currentText()));
}
void DialogOptions::saveSettings()
{
int size=ui->comboFontSize->currentText().toInt();
if(size<=0)size=QApplication::font().pointSize();
        QSettings setting(QApplication::applicationName(),"settings");

       setting.beginGroup("Main");

        setting.setValue("fontQuran",ui->fontComboQuran->currentText());
        setting.setValue("fontTafsir",ui->fontComboTefsir->currentText());
        setting.setValue("fontSize", size);

        setting.setValue("fontColor",btnColorFont->color());
        setting.setValue("backColor",btnColorBack->color());
        setting.setValue("symbolColor",btnColorSymbol->color());
        setting.setValue("findColor",btnColorFind->color());
        setting.endGroup();


}

void DialogOptions::on_buttonBox_clicked(QAbstractButton *button)
{
        if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Ok){
                saveSettings();
                emit settingsChanged();
                this->accept();
        }else if(ui->buttonBox->standardButton(button)==QDialogButtonBox::Apply){
                saveSettings();
                emit settingsChanged();
        }
}
