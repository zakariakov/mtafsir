#include "buttoncolor.h"
#include <QColorDialog>
#include <QPainter>
#include <QDebug>
ButtonColor::ButtonColor(QColor color,QWidget *parent) :
        QPushButton(parent)
{
        setIconSize(QSize(32,16));
          setMaximumSize(QSize(48,26));
         setMinimumSize(QSize(40,26));
        connect(this,SIGNAL(clicked()),this,SLOT(getColor()));
        setColor( color);
}


void ButtonColor::setColor(QColor color)
{

     m_color=color;
     QPixmap pix(32,16);
     pix.fill(Qt::transparent);
QPainter p;

p.begin(&pix);

p.fillRect(pix.rect(),m_color);
p.setPen(this->palette().shadow().color());
p.drawRect(pix.rect());
p.setPen(this->palette().light().color());
p.drawRect(-1,-1,32,16);
    // pix.fill(m_color);
     this->setIcon(pix);
}

void ButtonColor::getColor()
{
        QColor color=QColorDialog::getColor(m_color,this,"Get Color");

        if(color.isValid()){
            setColor(color);
            emit colorChanged() ;
        }

}
