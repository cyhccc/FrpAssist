#include "colorselectwidget.h"

#include <QPainter>

//530,820
ColorSelectWidget::ColorSelectWidget(QWidget *parent) : QWidget(parent)
{

    initUI();
}

void ColorSelectWidget::initUI()
{

    hColorArea=new HColorArea(this);
    svColorArea =new SVColorArea(this);
    connect(hColorArea,&HColorArea::hueChanged,svColorArea,&SVColorArea::on_hueChanged);
    connect(svColorArea,&SVColorArea::svColorChanged,this,&ColorSelectWidget::on_hsvColorChanged);
    connect(this,&ColorSelectWidget::hueChanged,hColorArea,&HColorArea::on_hueChanged);

    int btn_width=70;
    int deviation=65;
    btn1=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn1->setBackgroundColor(QColor(Qt::red));
    btn1->move(margin,530);
    btn1->installEventFilter(this);

    btn2=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn2->setBackgroundColor(QColor(0,255,1));
    btn2->move(btn1->x()+btn1->width()+deviation,530);
    btn2->installEventFilter(this);

    btn3=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn3->setBackgroundColor(QColor(0,0,255));
    btn3->move(btn2->x()+btn2->width()+deviation,530);
    btn3->installEventFilter(this);

    btn4=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn4->setBackgroundColor(QColor(255,0,127));
    btn4->move(btn3->x()+btn3->width()+deviation,530);
    btn4->installEventFilter(this);


    btn5=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn5->setBackgroundColor(QColor(128,0,255));
    btn5->move(margin,630);
    btn5->installEventFilter(this);

    btn6=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn6->setBackgroundColor(QColor(255,255,0));
    btn6->move(btn5->x()+btn5->width()+deviation,630);
    btn6->installEventFilter(this);

    btn7=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn7->setBackgroundColor(QColor(1,255,255));
    btn7->move(btn6->x()+btn6->width()+deviation,630);
    btn7->installEventFilter(this);

    btn8=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn8->setBackgroundColor(QColor(255,0,255));
    btn8->move(btn7->x()+btn7->width()+deviation,630);
    btn8->installEventFilter(this);

    btn9=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn9->setBackgroundColor(QColor(128,255,1));
    btn9->move(margin,730);
    btn9->installEventFilter(this);

    btn10=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn10->setBackgroundColor(Qt::black);
    btn10->move(btn9->x()+btn9->width()+deviation,730);
    btn10->installEventFilter(this);

    btn11=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn11->setBackgroundColor(QColor(128,128,128));
    btn11->move(btn10->x()+btn10->width()+deviation,730);
    btn11->installEventFilter(this);

    btn12=new CustomButton(btn_width,btn_width,CustomButton::color,this);
    btn12->setBackgroundColor(QColor(255,255,255));
    btn12->move(btn11->x()+btn11->width()+deviation,730);
    btn12->installEventFilter(this);
}



void ColorSelectWidget::on_hsvColorChanged(double hue, double saturation, double brightness)
{
    QColor color;
//    qDebug()<<hue<<" "<<saturation<<" "<<brightness;
    color.setHsvF(hue,saturation,brightness);
    emit colorChanged(color);
}

void ColorSelectWidget::resizeEvent(QResizeEvent *event)
{
    hColorArea->setGeometry(0,0,width(),120);
    svColorArea->setGeometry(30,140,width()-60,350);
}

void ColorSelectWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::NoPen);
    QRect rect(0,0,width(),height());
    painter.setBrush(Global::aroundDialogColor);
    painter.drawRoundedRect(rect,12,12);
}

void ColorSelectWidget::btnFocusChanged(CustomButton *cnt_btn)
{
    if(current_btn_focused)
    {
        current_btn_focused->colorBtnIsFocused(false);
    }
    if(cnt_btn)
    {
        current_btn_focused=cnt_btn;
        current_btn_focused->colorBtnIsFocused(true);
        QColor color=current_btn_focused->getBackgroundColor();
        emit hueChanged(color.hsvHueF());
        emit colorChanged(current_btn_focused->getBackgroundColor());
    }
}

void ColorSelectWidget::mousePressEvent(QMouseEvent *event)
{
    event->accept();
}



bool ColorSelectWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(event->type()==QEvent::MouseButtonPress)
    {
        if(qobject_cast<CustomButton*>(watched))
        {
            CustomButton *cnt_btn=static_cast<CustomButton*>(watched);
            btnFocusChanged(cnt_btn);
            return false;
        }
        return false;
    }
    return QWidget::eventFilter(watched,event);
}
