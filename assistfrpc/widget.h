#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QLineEdit>
#include"component/switchbutton.h"
#include"component/custombutton.h"
class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    void initUi();
    bool isProcessRunning(const char* processName);
    void killProcess(const char* processName);
    void setProcessAutoRun(bool flag);
    void readConfig();
    void writeConfig();
    ~Widget();

public slots:
    void on_btnClicked();

private:
    QLineEdit *server_ip;
    QLineEdit *server_port;
    QLineEdit *remote_port;
    CustomButton *btn_confirm;
    SwitchButton *switch_btn;

    // QString serverIp;
    // int serverPort;
    // int port;
    // bool book;

};
#endif // WIDGET_H
