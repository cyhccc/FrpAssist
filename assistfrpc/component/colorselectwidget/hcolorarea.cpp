#include "hcolorarea.h"

#include <QPainter>
#include<QMouseEvent>
#include<QDebug>
HColorArea::HColorArea(QWidget *parent) : QWidget(parent)
{

    //    hColorArea;
}

void HColorArea::drawHuePix()
{
    int huePixH=height()/4;
    huePix=QPixmap(width()-margin*2,huePixH);
    QPainter painter(&huePix);
//    huePix.fill(Qt::transparent);
    QLinearGradient hueGradient(0, 0, huePix.width(), 0);
    for (double i = 0; i < 1.0; i += 1.0 / huePix.width())
    {
        hueGradient.setColorAt(i, QColor::fromHsvF(i, 1, 1, 1));
    }
    hueGradient.setColorAt(1, QColor::fromHsvF(0, 1, 1, 1));
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(hueGradient));
    painter.drawRect(0,0,huePix.width(),huePix.height());
}

void HColorArea::on_hueChanged(double hue)
{
    this->hue=hue;
    mousePressedX=hue*huePix.width()+30;
    update();
}

void HColorArea::mousePressEvent(QMouseEvent *event)
{
    mousePressedX=qBound(margin,event->pos().x(),width()-margin);

    update();
    event->ignore();
//    QWidget::mousePressEvent(event);
}

void HColorArea::mouseMoveEvent(QMouseEvent *event)
{
    mousePressedX=qBound(margin,event->pos().x(),width()-margin);
    event->accept();
    update();
}

void HColorArea::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);

//        QRect rect(0,0,width(),height());
//        painter.setBrush(Qt::black);
//        painter.drawRect(rect);
    drawHuePix();
    painter.drawPixmap(QRect(margin,height()-huePix.height()-30,huePix.width(),huePix.height()),huePix);
    painter.drawPixmap(QRect(mousePressedX-arrowPix.width()/2,0,arrowPix.width(),arrowPix.height()),arrowPix);

    hue=(mousePressedX-30.0)/huePix.width();
    emit hueChanged(hue);
//    qDebug()<<hue;
}
