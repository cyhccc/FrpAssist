#include "widget.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QCoreApplication>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include <QDir>
#include <QProcess>
#include <QApplication>
#include <QSettings>
#include <QHostInfo>
#define AUTO_RUN "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{

    initUi();
    readConfig();
    connect(btn_confirm, &CustomButton::clicked, this, &Widget::on_btnClicked);
    connect(switch_btn, &SwitchButton::clicked, [=](bool book)
            {
        setProcessAutoRun(book);
        writeConfig(); });

    // qDebug()<<QApplication::applicationFilePath();
}

void Widget::initUi()
{
    QVBoxLayout *Vlayout = new QVBoxLayout();

    QLabel *label1 = new QLabel();
    label1->setText("服务器ip");
    server_ip = new QLineEdit();
    // server_ip->setText(serverIp);

    QHBoxLayout *Hlayout1 = new QHBoxLayout();
    Hlayout1->addStretch();
    Hlayout1->addWidget(label1);
    Hlayout1->addWidget(server_ip);

    QLabel *label2 = new QLabel();
    label2->setText("服务器端口");
    server_port = new QLineEdit();
    // server_port->setText(QString::number(serverPort));

    QHBoxLayout *Hlayout2 = new QHBoxLayout();
    Hlayout2->addStretch();
    Hlayout2->addWidget(label2);
    Hlayout2->addWidget(server_port);

    QLabel *label3 = new QLabel();
    label3->setText("远程桌面端口");
    remote_port = new QLineEdit();
    // remote_port->setText(QString::number(port));

    QHBoxLayout *Hlayout3 = new QHBoxLayout();
    Hlayout3->addStretch();
    Hlayout3->addWidget(label3);
    Hlayout3->addWidget(remote_port);

    QLabel *label4 = new QLabel();
    label4->setText("开机自启frpc.exe");
    switch_btn = new SwitchButton(70, 30);

    QHBoxLayout *Hlayout5 = new QHBoxLayout();
    Hlayout5->addWidget(label4);
    Hlayout5->addWidget(switch_btn);
    // switch_btn->changeState(book);

    btn_confirm = new CustomButton(80, 30);
    btn_confirm->setText("确认");
    btn_confirm->setTextSize(20);
    btn_confirm->turnOn();
    QHBoxLayout *Hlayout4 = new QHBoxLayout();
    Hlayout4->addStretch();
    Hlayout4->addWidget(btn_confirm);

    Vlayout->addLayout(Hlayout1);
    Vlayout->addLayout(Hlayout2);
    Vlayout->addLayout(Hlayout3);
    Vlayout->addLayout(Hlayout5);
    Vlayout->addLayout(Hlayout4);
    setLayout(Vlayout);
}

bool Widget::isProcessRunning(const char *processName)
{
    QProcess process;
    QString cmd = "tasklist";
    process.start(cmd);
    process.waitForFinished();                     // 等待进程结束
    QString str = process.readAllStandardOutput(); // 获取执行命令后的输出内容

    if (str.contains(processName)) // 判断是否有包含当前指定的进程名
    {
        return true;
    }
    else
    {
        return false;
    }
}

void Widget::killProcess(const char *processName)
{
    QStringList params;
    params << "-f"
           << "-im" << processName;
    QProcess process;
    process.start("taskkill", params);

    if (!process.waitForFinished(-1))
    {
        qDebug() << "Error: " << process.errorString();
        return;
    }
    qDebug() << "Process " << processName << " has been killed.";
}

void Widget::setProcessAutoRun(bool flag)
{

    QSettings settings(AUTO_RUN, QSettings::Registry64Format);
    QString path = QCoreApplication::applicationFilePath();

    QString appName = "assistfrpc";
    // 如果注册表中的路径和当前程序路径不一样，则表示没有设置自启动或本自启动程序已经更换了路径
    QString oldPath = settings.value(appName).toString();      // 获取目前的值-绝对路劲
    QString newPath = QDir::toNativeSeparators(path) + " min"; // toNativeSeparators函数将"/"替换为"\"
    if (flag)
    {
        if (oldPath != newPath)
            settings.setValue(appName, newPath);
    }
    else
        settings.remove(appName);
}

void Widget::readConfig()
{
    QSettings settings("AssistFrpc", "widget");
    server_ip->setText(settings.value("server_ip", "").toString());
    server_port->setText(settings.value("server_port", "").toString());
    remote_port->setText(settings.value("remote_port", "").toString());
    switch_btn->changeState(settings.value("book", false).toBool());
}

void Widget::writeConfig()
{

    QSettings settings("AssistFrpc", "widget");
    settings.setValue("server_ip", server_ip->text());
    settings.setValue("server_port", server_port->text());
    settings.setValue("remote_port", remote_port->text());
    settings.setValue("book", switch_btn->getState());
}

Widget::~Widget() {}

void Widget::on_btnClicked()
{

    if (server_ip->text().length() > 15)
        return;

    QString currentPath = QCoreApplication::applicationDirPath();
    QFile file(currentPath + "/frpc/frpc.toml");
    // qDebug() << file.fileName();
    if (!file.open(QIODevice::ReadWrite))
    {
        qDebug() << "error";
        qDebug() << file.errorString();
        return;
    }
    file.resize(0);
    QTextStream out(&file);
    out << "[common]\n";
    out << QString("server_addr = %1 \n").arg(server_ip->text());
    out << QString("server_port =  %1 \n").arg(server_port->text());

    out << QString("[%1]\n").arg(QHostInfo::localHostName());
    out << "type=tcp\n";
    out << "local_port = 3389 \n";
    out << QString("remote_port=%1").arg(remote_port->text());
    file.close();

    const char *targetProcessName = "frpc.exe";

    if (isProcessRunning(targetProcessName))
    {
        killProcess(targetProcessName);
    }

    QString cmdParam = QCoreApplication::applicationDirPath() + "/frpc/frpc.exe";
    QStringList list;
    list << "-c" << QCoreApplication::applicationDirPath() + "/frpc/frpc.toml";
    QProcess process;
    bool m_frpOk;
    m_frpOk = process.startDetached(cmdParam, list);
    if (m_frpOk)
    {
        qDebug() << "frp start success!!!";
        qInfo("success!");
    }

    else
    {

        qInfo("fatal");
        qDebug() << "frp start failed..." << cmdParam << m_frpOk << process.errorString();
    }

    writeConfig();
}
