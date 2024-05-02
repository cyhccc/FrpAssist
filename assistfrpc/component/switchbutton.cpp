#include "switchbutton.h"

#include <QPainter>
#include<QTimer>
#include<QDebug>
SwitchButton::SwitchButton(QWidget *parent): QWidget(parent)
{
    setFixedSize(this->w,this->h);

}

SwitchButton::SwitchButton(int w,int h,QWidget *parent) : QWidget(parent)
{
    setFixedSize(w,h);
}

void SwitchButton::changeState(bool book)
{
    state=book;
    update();
}


void SwitchButton::mousePressEvent(QMouseEvent *event)
{

    this->state=!this->state;
    update();
    emit clicked(state);
}

void SwitchButton::paintEvent(QPaintEvent *event)
{
    radius = height()/2;

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    if(state)
    {
        painter.setBrush(QColor(22,119,255));
        painter.drawEllipse(QPoint(radius,radius),radius,radius);
        painter.drawEllipse(QPoint(width()-radius,radius),radius,radius);
        painter.drawRect(QRect(radius,0,width()-radius*2,height()));
        painter.setBrush(Qt::white);
        painter.drawEllipse(QPoint(width()-radius-3,radius),radius,radius);
    }
    else
    {
        painter.setBrush(QColor(167,167,167));
        painter.drawEllipse(QPoint(radius,radius),radius,radius);
        painter.drawEllipse(QPoint(width()-radius,radius),radius,radius);
        painter.drawRect(QRect(radius,0,width()-radius*2,height()));
        painter.setBrush(Qt::white);
        painter.drawEllipse(QPoint(radius+3,radius),radius,radius);
    }


}
