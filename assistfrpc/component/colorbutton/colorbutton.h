#ifndef COLORBUTTON_H
#define COLORBUTTON_H

#include <QWidget>

class ColorButton : public QWidget
{
    Q_OBJECT
public:
    explicit ColorButton(int width,int height,QColor color,QWidget *parent = nullptr);
    void setBtnState(bool book);
    void setId(int id);
    int  getId();
    void setColor(QColor color);
signals:
    void clicked(QColor color);
    void clicked_id(QColor color,int id);
private:
    QColor color;
    bool is_clicked=false;
    int margin=20;
    int radius=5;
    int id=-1;
    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
};

#endif // COLORBUTTON_H
