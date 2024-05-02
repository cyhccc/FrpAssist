#include "colorbuttogroup.h"
#include<QDebug>
ColorButtoGroup::ColorButtoGroup(QWidget *parent) : QObject(parent)
{

}

void ColorButtoGroup::addButton(ColorButton *btn, qint8 id)
{
    map_btn.insert(id,btn);
    btn->setId(id);
    connect(btn,&ColorButton::clicked_id,this,&ColorButtoGroup::on_btnClicked);
}

void ColorButtoGroup::initConfigs(qint8 id)
{
    if(id==-1)
    {
        current_btn=nullptr;
        return;
    }

    if(!map_btn.value(id))
    {
        qDebug()<<"initConfigs fail!";
        return;
    }
    if(current_btn)
    {
        current_btn->setBtnState(false);
    }
    current_btn=map_btn.value(id);
    current_btn->setBtnState(true);
}

void ColorButtoGroup::on_btnClicked(QColor color, qint8 id)
{

    if(current_btn==map_btn.value(id))
    {
        current_btn=nullptr;
        emit clicked(color,-1);
        return;
    }
    if(current_btn)
    {
        current_btn->setBtnState(false);
    }
//    qDebug()<<"saddd";
    current_btn=map_btn.value(id);
    emit clicked(color,id);
}


