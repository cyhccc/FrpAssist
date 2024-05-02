#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QWidget>
#include<global.h>
class CustomButton : public QWidget
{
    Q_PROPERTY(qint8 id MEMBER m_id READ getId WRITE setId)
    Q_OBJECT
public:
    enum BtnType{general ,color};
    Q_ENUM(BtnType)
    explicit CustomButton(QWidget *parent = nullptr);
    explicit CustomButton(int w,int h,QWidget *parent = nullptr);
    explicit CustomButton(int w,int h,BtnType type,QWidget *parent = nullptr);
    void setText(QString s);
    void setRoundRadius(int r);
    void setTextSize(int size);
    void setBackgroundColor(QColor color);
    void setTextColor(QColor color);
    void setClickedColor(QColor color);
    void setClickedTextColor(QColor color);
    void setBold(bool book);
    void turnOn();
    void turnOff();
    void setAlignment(int flag);
    QColor getBackgroundColor();
    QString getText();
    void colorBtnIsFocused(bool book);
    qint8 getId();
    void setId(qint8 id);
signals:
     void clicked();
     void clicked_id(qint8 id);
private:
    int w=100;
    int h=40;
    QColor backgroundColor=Global::btn_background_color;
    QColor textColor=QColor(140,141,145);

    QColor clickedColor=Global::lightBlue;
    QColor clickedTextColor=Qt::white;
    QString text;
    int textSize=30;
    int radius=5;
    bool isBold=false;
    bool is_clicked=false;
    int alignFlag=Qt::AlignCenter;
    BtnType btn_type=general;

    qint8 m_id=-1;


protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:
    void drawGeneralBtn(QPainter &painter);
    void drawColorBtn(QPainter &painter);
};

#endif // CUSTOMBUTTON_H
