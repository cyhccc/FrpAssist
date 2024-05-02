#include "svcolorarea.h"

#include <QPainter>
#include<QDebug>
#include<QMouseEvent>
SVColorArea::SVColorArea(QWidget *parent) : QWidget(parent)
{

}

void SVColorArea::on_hueChanged(double hue)
{

    this->hue=hue;

//    qDebug()<<"SVColorArea:"<<this->hue;
    update();
}

void SVColorArea::mousePressEvent(QMouseEvent *event)
{
    is_pressed=true;
    saturation=qBound(0,event->pos().x(),width());
    brightness=qBound(0,event->pos().y(),height());
    emit svColorChanged(hue,saturation/width(),(height()-brightness)/height());
    update();
}

void SVColorArea::mouseMoveEvent(QMouseEvent *event)
{
    saturation=qBound(0,event->pos().x(),width());
    brightness=qBound(0,event->pos().y(),height());
    emit svColorChanged(hue,saturation/width(),(height()-brightness)/height());
    update();
}

void SVColorArea::paintEvent(QPaintEvent *event)
{


    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHint(QPainter::Antialiasing);
    QRect rect(0,0,width(),height());

    QColor newColor;
    newColor.setHsvF(hue, 1, 1);
    QLinearGradient svGradient(0, 0, width(), 0);
    svGradient.setColorAt(1, newColor);
    svGradient.setColorAt(0, QColor("#ffffff"));
    painter.setBrush(QBrush(svGradient));
    painter.drawRoundedRect(rect,13,13);


    QLinearGradient vGradient(0, height(), 0,0 );
    vGradient.setColorAt(1, QColor(0, 0, 0, 0));
    vGradient.setColorAt(0, QColor(0, 0, 0, 255));
    painter.setBrush(vGradient);
    painter.drawRoundedRect(rect,12,12);

    /***********************/
    if(is_pressed)
    {
        painter.setPen(Qt::white);
        painter.setBrush(QBrush(Qt::transparent));
        painter.drawEllipse(QPoint(saturation,brightness),10,10);
    }

}

void SVColorArea::resizeEvent(QResizeEvent *event)
{
}
