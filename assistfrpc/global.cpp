#include "global.h"



int Global::id=1;
QColor Global::aroundWidgetColor=QColor(0,0,0,200);
QColor Global::aroundDialogColor=QColor(41,42,51);
QColor Global::aroundDialogColorLight=QColor(59,60,67);
qreal Global::dialogRadius=12;
QColor Global::lightBlue=QColor(22,119,255);
QColor Global::text_color_light=QColor(148,149,153);
QColor Global::btn_background_color=QColor(26,25,30);
void Global::setFont(QFont &font, QString fontFamily, int size)
{
    font.setFamily(fontFamily);
    font.setPixelSize(size);
}

void Global::setFont(QFont &font, int size)
{
    font.setFamily("Arial");
    font.setPixelSize(size);
}
