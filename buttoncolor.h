#ifndef BUTTONCOLOR_H
#define BUTTONCOLOR_H

#include <QPushButton>

class ButtonColor : public QPushButton
{
        Q_OBJECT
public:

        explicit ButtonColor(QColor color,QWidget *parent = 0);

signals:
        void colorChanged() ;
public slots:

        void setColor(QColor color);
        QColor color(){
                return m_color;
        }

private:

        QColor m_color;

private slots:
        void getColor();


};

#endif // BUTTONCOLOR_H
