#ifndef HCOLORAREA_H
#define HCOLORAREA_H

#include <QWidget>

class HColorArea : public QWidget
{
    Q_OBJECT
public:
    explicit HColorArea(QWidget *parent = nullptr);
    void drawHuePix();

public slots:
    void on_hueChanged(double hue);
signals:
    void hueChanged(double hue);
private:
   double mousePressedX=30;
   QPixmap huePix;
   QPixmap arrowPix=QPixmap(":/dialog3/aroundicons/dialog3/up_no.png").transformed(QTransform().rotate(180));
   int margin=30;
   double hue=0;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

};

#endif // HCOLORAREA_H
