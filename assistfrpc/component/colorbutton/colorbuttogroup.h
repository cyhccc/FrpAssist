#ifndef COLORBUTTOGROUP_H
#define COLORBUTTOGROUP_H

#include<QObject>
#include<component/colorbutton/colorbutton.h>
#include<QMap>
class ColorButtoGroup : public QObject
{
    Q_OBJECT
public:
    explicit ColorButtoGroup(QWidget *parent = nullptr);
    void addButton(ColorButton *btn,qint8 id);
    void initConfigs(qint8 id);
signals:
    void clicked(QColor color,qint8 id);
public slots:
    void on_btnClicked(QColor color,qint8 id);
private:
    QMap<qint8,ColorButton*>map_btn;
    int current_id=-1;
    ColorButton *current_btn=nullptr;
};

#endif // COLORBUTTOGROUP_H
