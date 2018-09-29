#ifndef DIALOGOPTIONS_H
#define DIALOGOPTIONS_H
#include "buttoncolor.h"
#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class DialogOptions;
}

class DialogOptions : public QDialog
{
        Q_OBJECT
        
public:
        explicit DialogOptions(QWidget *parent = 0);
        ~DialogOptions();
signals:
        void settingsChanged();
private:
        Ui::DialogOptions *ui;
ButtonColor *btnColorBack;
ButtonColor *btnColorFont;
ButtonColor *btnColorSymbol;
ButtonColor *btnColorFind;
private slots:
     void loadSettings();
      void saveSettings();
      void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // DIALOGOPTIONS_H
