#include "widget.h"
#include "log.h"

#include <QApplication>
#include <QTextCodec>


//消息传递函数 传输到LOG.TXT
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{

    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString timestr = time.toString("yyyy-MM-dd hh:mm:ss ddd"); //设置显示格式

    QFile file("log.txt");
    //file.resize(0);
    file.open(QFile::WriteOnly| QIODevice::Append);
    QTextStream out(&file);

    switch (type) {
    case QtDebugMsg:
        out << "Debug: "  << msg << " (" << timestr << ") " << "\r\n";
        break;
    case QtWarningMsg:
        out << "warning: "<< msg << " (" << timestr << ") " << "\r\n";
        break;
    case QtCriticalMsg:
        out << "critical: "<< msg << " (" << timestr << ") " << "\r\n";
        break;
    case QtFatalMsg:
        out << "fatal: "<< msg << " (" << timestr << ") " << "\r\n";
        abort();
    }
}




void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    static QMutex mutex;
    mutex.lock();

    QString text;
    switch(type)
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

    QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
    QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
    QString current_date = QString("(%1)").arg(current_date_time);
    QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

    QFile file("log.txt");
    file.open(QIODevice::WriteOnly | QIODevice::Append);//Append 追加方式
    QTextStream text_stream(&file);
    text_stream << message << "\r\n";
    file.flush();
    file.close();

    mutex.unlock();
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //输出log.txt文件



    //支持中文编码
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForLocale(codec);

    qInstallMessageHandler(myMessageOutput);

    Widget window;
    window.show();

    return a.exec();
}
