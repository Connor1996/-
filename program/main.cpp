#include "widget.h"
#include "log.h"

#include <QApplication>
#include <QTextCodec>


//消息传递函数 传输到LOG.TXT
void myMessageOutput(QtMsgType type, const QString &msg)
{

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timestr = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式

    QFile file("log.txt");
    file.open(QFile::WriteOnly|QIODevice::Append);
    QTextStream out(&file);

    switch (type) {
    case QtDebugMsg:
        out << "Debug: "<< msg << timestr << "\r\n";
        break;
    case QtWarningMsg:
        out << "warning: "<< msg<< timestr << "\r\n";
        break;
    case QtCriticalMsg:
        out << "critical: "<< msg << timestr << "\r\n";
        break;
    case QtFatalMsg:
        out << "fatal: "<< msg << timestr << "\r\n";
        abort();
    }
}




int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //输出log.txt文件
    //qInstallMessageHandler(myMessageOutput);

    //支持中文编码
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    Widget window;
    window.show();

    return a.exec();
}
