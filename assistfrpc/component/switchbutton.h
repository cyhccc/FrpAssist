#ifndef SWITCHBUTTON_H
#define SWITCHBUTTON_H

#include <QWidget>

class SwitchButton : public QWidget
{
    Q_OBJECT
public:
    explicit SwitchButton(QWidget *parent = nullptr);
    explicit SwitchButton(int w,int h,QWidget *parent = nullptr);
    void changeState(bool book);
signals:
     void clicked(bool);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    bool state=false;
    qreal x=2;  
    int w=100;
    int h=40;
    int radius=h-2;

};

#endif // SWITCHBUTTON_H
