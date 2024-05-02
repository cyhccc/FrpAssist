#ifndef COLORSELECTWIDGET_H
#define COLORSELECTWIDGET_H

#include <QWidget>
#include<component/colorselectwidget/hcolorarea.h>
#include<component/colorselectwidget/svcolorarea.h>
#include<myq++.h>
class ColorSelectWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ColorSelectWidget(QWidget *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event) override;
    void initUI();

signals:
    void colorChanged(QColor color);
    void hueChanged(double hue);
public slots:
    void on_hsvColorChanged(double hue,double saturation,double brightness);
private:
    HColorArea *hColorArea;
    SVColorArea *svColorArea;
    CustomButton *btn1;
    CustomButton *btn2;
    CustomButton *btn3;
    CustomButton *btn4;
    CustomButton *btn5;
    CustomButton *btn6;
    CustomButton *btn7;
    CustomButton *btn8;
    CustomButton *btn9;
    CustomButton *btn10;
    CustomButton *btn11;
    CustomButton *btn12;
    CustomButton *current_btn_focused=nullptr;
    double hue=0;
    int margin=30;

protected:
    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
private:
    void btnFocusChanged(CustomButton * cnt_btn);


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // COLORSELECTWIDGET_H
