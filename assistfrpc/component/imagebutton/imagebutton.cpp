#include "imagebutton.h"

#include <QPainter>
#include<QMouseEvent>
ImageButton::ImageButton(int buttonState,qint8 id,int w,int h,QString imagePath,QWidget *parent) : QWidget(parent)
{
    this->id=id;

    this->buttonState=buttonState;
    this->imagePath=imagePath;
    imagePathFill=imagePath.section(".",0,0)+"_fill.png";
    imagePathDisable=imagePath.section(".",0,0)+"_no.png";

    setFixedSize(w,h);
    this->pix_width=w;
    this->pix_height=h;
    //    setMinimumSize(QSize(w,h));
    //    setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
}

ImageButton::ImageButton(int buttonState, qint8 id, int btn_width, int btn_height, int pix_width, int pix_height, QString imagePath, QWidget *parent)
    : QWidget(parent)
{
    this->id=id;

    this->buttonState=buttonState;
    this->imagePath=imagePath;
    imagePathFill=imagePath.section(".",0,0)+"_fill.png";
    imagePathDisable=imagePath.section(".",0,0)+"_no.png";
    setFixedSize(btn_width,btn_height);
    this->pix_width=pix_width;
    this->pix_height=pix_height;
}

void ImageButton::changeState(int state)
{
    buttonState=state;
    update();
}

qint8 ImageButton::getState()
{
    return buttonState;
}

qint8 ImageButton::getId()
{
     return id;
}

void ImageButton::mousePressEvent(QMouseEvent *event)
{
    if(buttonState==1)
    {
        changeState(2);
       emit clicked_id(id);
    }
    else if(buttonState==2)
    {
        changeState(1);
       emit clicked_id(-1);
    }
    event->ignore();
}

void ImageButton::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::NoPen);
    painter.setRenderHints ( QPainter::Antialiasing | QPainter::TextAntialiasing );
    QPixmap pic;
    QRect rect((width()-pix_width)/2,(height()-pix_height)/2,pix_width,pix_width);
    if(buttonState==0) //禁用按钮
    {
        pic.load(imagePathDisable);

    }
    else if(buttonState==1)//按钮初始状态
    {
        pic.load(imagePath);
    }
    else //点击按钮
    {
        pic.load(imagePathFill);
    }
    pic=pic.scaled(QSize(pix_width,pix_height),Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    // painter.setBrush(Qt::red);
    painter.drawRect(QRect(0,0,width(),height()));
    painter.drawPixmap(rect,pic);
}
