#ifndef IMAGEBUTTONGROUP_H
#define IMAGEBUTTONGROUP_H

#include <QMap>
#include <QObject>
#include<component/imagebutton/imagebutton.h>
class ImageButtonGroup : public QObject
{
    Q_OBJECT
public:
    explicit ImageButtonGroup(QObject *parent = nullptr);
    void addButton(ImageButton*btn,qint8 id);
    void initState(qint8 id);
signals:
    void btnClicked(qint8 id);
public slots:
    void on_btnClicked(qint8 id);
private:
    QMap<qint8,ImageButton*>map_btn;
    ImageButton * current_btn=nullptr;
};

#endif // IMAGEBUTTONGROUP_H
