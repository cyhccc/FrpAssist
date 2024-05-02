#include "custombutton.h"

#include <QPainter>
#include<QMouseEvent>

CustomButton::CustomButton(QWidget *parent) : QWidget(parent)
{
    setFixedSize(this->w,this->h);
}

CustomButton::CustomButton(int w, int h, QWidget *parent) : QWidget(parent)
{
    setFixedSize(w,h);

}

CustomButton::CustomButton(int w, int h,BtnType type, QWidget *parent): QWidget(parent)
{
    setFixedSize(w,h);
    btn_type=type;
}

void CustomButton::setText(QString s)
{
    text=s;
    update();
}

void CustomButton::setRoundRadius(int r)
{
    radius=r;
    update();
}

void CustomButton::setTextSize(int size)
{
    textSize=size;
    update();
}

void CustomButton::setBackgroundColor(QColor color)
{
    backgroundColor=color;
    update();
}

void CustomButton::setTextColor(QColor color)
{
    textColor=color;
    update();
}

void CustomButton::setClickedColor(QColor color)
{
    clickedColor=color;
}

void CustomButton::setClickedTextColor(QColor color)
{
    clickedTextColor=color;
}

void CustomButton::setBold(bool book)
{
    isBold=book;
    update();
}

void CustomButton::turnOn()
{
    is_clicked=true;
    update();
}

void CustomButton::turnOff()
{
    is_clicked=false;
    update();
}

void CustomButton::setAlignment(int flag)
{
    alignFlag=flag;
    update();
}

QColor CustomButton::getBackgroundColor()
{
    return backgroundColor;
}

QString CustomButton::getText()
{
    return this->text;
}

void CustomButton::colorBtnIsFocused(bool book)
{
   is_clicked=book;
   update();
}

qint8 CustomButton::getId()
{
    return m_id;
}

void CustomButton::setId(qint8 id)
{
    m_id=id;
}



void CustomButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing|QPainter::TextAntialiasing);
    painter.setPen(Qt::NoPen);

    if(btn_type==general)
    {
        drawGeneralBtn(painter);
    }
    else if(btn_type==color)
    {

        drawColorBtn(painter);
    }
}

void CustomButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    emit clicked_id(m_id);
    event->ignore();
    //    QWidget::mousePressEvent(event);
}

void CustomButton::drawGeneralBtn(QPainter &painter)
{
    if(is_clicked)
    {
        QRect rect(0,0,width(),height());
        painter.setBrush(clickedColor);
        painter.drawRoundedRect(rect,radius,radius);

        QFont font;
        font.setPixelSize(textSize);
        font.setBold(isBold);
        painter.setFont(font);
        painter.setPen(QPen(clickedTextColor));
        painter.drawText(rect,alignFlag,text);
    }
    else
    {
        QRect rect(0,0,width(),height());
        painter.setBrush(backgroundColor);
        painter.drawRoundedRect(rect,radius,radius);

        QFont font;
        font.setPixelSize(textSize);
        font.setBold(isBold);
        painter.setFont(font);
        painter.setPen(QPen(textColor));
        painter.drawText(rect,alignFlag,text);
    }

}

void CustomButton::drawColorBtn(QPainter &painter)
{
    if(is_clicked)
    {
        QRect rect(0,0,width(),height());
        painter.setBrush(Qt::white);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect,radius,radius);
    }

    int margin_width=10;
    QRect rect(margin_width/2,margin_width/2,width()-margin_width,height()-margin_width);
    painter.setBrush(backgroundColor);
    painter.drawRoundedRect(rect,radius,radius);
    QFont font;
    font.setPixelSize(textSize);
    font.setBold(isBold);
    painter.setFont(font);
    painter.setPen(QPen(textColor));
    painter.drawText(rect,alignFlag,text);
}


