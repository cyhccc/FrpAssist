#ifndef DIALOG1BUTTON_H
#define DIALOG1BUTTON_H

#include <QWidget>

class ImageButton : public QWidget
{
    Q_OBJECT
public:
    explicit ImageButton(int buttonState,qint8 id,int w,int h,QString imagePath,QWidget *parent = nullptr);
    explicit ImageButton(int buttonState, qint8 id, int btn_width, int btn_height,int pix_width,int pix_height, QString imagePath, QWidget *parent=nullptr);
    void changeState(int state);
    qint8 getState();
    qint8  getId();
signals:
    void clicked_id(qint8 id);
private:
    QString imagePath;
    QString imagePathFill;
    QString imagePathDisable;
    int buttonState=0;
    qint8 id;
    int pix_width;
    int pix_height;

    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
};

#endif // DIALOG1BUTTON_H
