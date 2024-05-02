#ifndef GLOBAL_H
#define GLOBAL_H

#include <QColor>
#include<QObject>
#include<QWidget>

class Global
{
public:

    static  QColor aroundWidgetColor;
    static  int id;
    static  QColor aroundDialogColor;
    static qreal dialogRadius;
    static QColor aroundDialogColorLight;
    static QColor lightBlue;
    static QColor text_color_light;
    static QColor btn_background_color;
public:
    static void setFont(QFont &font,QString fontFamily,int size);
    static void setFont(QFont &font,int size);
};



#endif // GLOBAL_H
