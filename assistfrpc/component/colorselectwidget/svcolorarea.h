#ifndef SVCOLORAREA_H
#define SVCOLORAREA_H

#include <QWidget>

class SVColorArea : public QWidget
{
    Q_OBJECT
public:
    explicit SVColorArea(QWidget *parent = nullptr);
signals:
    void svColorChanged(double hue,double saturation,double brightness);
private:
    QPixmap svPix;
    QPixmap vPix;
    double hue=0;
    bool is_pressed=false;
    double saturation;
    double brightness;
public slots:
    void on_hueChanged(double hue);
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // SVCOLORAREA_H
