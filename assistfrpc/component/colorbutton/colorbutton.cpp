#include "colorbutton.h"
#include<QMouseEvent>
#include <QPainter>
ColorButton::ColorButton(int width,int height,QColor color,QWidget *parent) : QWidget(parent)
{
        setFixedSize(width,height);
        this->color=color;
}

void ColorButton::setBtnState(bool book)
{
    is_clicked=book;
    update();
}

void ColorButton::setId(int id)
{
    this->id=id;
}

int ColorButton::getId()
{
    return id;
}

void ColorButton::setColor(QColor color)
{
    this->color=color;
    update();
}

void ColorButton::mousePressEvent(QMouseEvent *event)
{
    if(!is_clicked)
    {
        is_clicked=true;
        emit clicked(color);
        emit clicked_id(color,id);
    }
    else
    {
        is_clicked=false;
        emit clicked(QColor(0,0,0,0));
         emit clicked_id(QColor(0,0,0,0),id);
    }
    event->ignore();
    update();

}

void ColorButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    if(is_clicked)
    {
         painter.setBrush(Qt::white);
         QRect rect(0,0,width(),height());
         painter.drawRoundedRect(rect,radius,radius);
    }
    painter.setPen(Qt::NoPen);
    painter.setBrush(color);
    QRect rect(margin/2,margin/2,width()-margin,height()-margin);
    painter.drawRoundedRect(rect,radius,radius);


}
