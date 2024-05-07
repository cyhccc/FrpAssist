#include "widget.h"

#include <QApplication>
#include <QSettings>
#include <QFile>
#include <QDateTime>
void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString text;
    switch (type)
    {
    case QtDebugMsg:
        text = QString("Debug:");
        break;

    case QtWarningMsg:
        text = QString("Warning:");
        break;

    case QtCriticalMsg:
        text = QString("Critical:");
        break;

    case QtFatalMsg:
        text = QString("Fatal:");
    }
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy-MM-dd hh:mm:ss ddd");
    QString message = text.append(msg).append("(").append(current_date).append(")");

    QFile file(QCoreApplication::applicationDirPath() + "/log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);
    file.resize(0);

    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.close();
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qInstallMessageHandler(outputMessage);
    Widget w;
    qDebug() << QCoreApplication::applicationDirPath();
    QSettings settings("AssistFrpc", "widget");
    bool book = settings.value("book", false).toBool();

    // 获取命令行参数，判断是否是【开机自启动】，如果是，最小化。
    QStringList arguments = QCoreApplication::arguments();
    qDebug() << arguments;
    // 以第一个参数是程序路径，第二个参数才是min,所以我们取第二个参数。
    if (arguments.size() > 1)
    {
        QString para2 = arguments.at(1);
        qDebug() << "para2:" << para2;
        if (para2 == "min")
        {
            w.on_btnClicked();
            // 打印日志到文件中
            // qInfo("success!");
            QThread::msleep(1000); // 阻塞延时50ms

            return 0;
        }
    }
    w.show();
    return a.exec();
}
