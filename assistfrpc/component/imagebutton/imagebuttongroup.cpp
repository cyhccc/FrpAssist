#include "imagebuttongroup.h"
#include<QDebug>
ImageButtonGroup::ImageButtonGroup(QObject *parent) : QObject(parent)
{

}

void ImageButtonGroup::addButton(ImageButton *btn, qint8 id)
{
    if(map_btn.value(id))
    {
        qDebug()<<"btn id already exist";
        return;
    }
    map_btn.insert(id,btn);
    connect(btn,&ImageButton::clicked_id,this,&ImageButtonGroup::on_btnClicked);
}

void ImageButtonGroup::initState(qint8 id)
{
    if(id==-1)return;
    if(!map_btn.value(id))
    {
        qDebug()<<"btn id dont exist";
        return;
    }
    current_btn=map_btn.value(id);
    current_btn->changeState(2);
}

void ImageButtonGroup::on_btnClicked(qint8 id)
{
    if(id==-1)
    {
        current_btn=nullptr;
        emit btnClicked(-1);
        return;
    }
    if(current_btn==map_btn.value(id))
    {
        current_btn->changeState(1);
        current_btn=nullptr;
        emit btnClicked(-1);
        return;
    }
    if(current_btn)
    {
        current_btn->changeState(1);
    }
    current_btn=map_btn.value(id);
    current_btn->changeState(2);
    emit btnClicked(id);
}
