#ifndef WIDGET_H
#define WIDGET_H

#include "schedule.h"

#include <QWidget>
#include <QDebug>
#include <QPushButton>
#include <QComboBox>
#include <QString>
#include <QMessageBox>
#include <QDate>
#include <QTime>
#include <QDateTimeEdit>
#include <QTimer>
#include <QThread>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

    int getStrategy();//获取用户所选策略
    int getStart();//获取用户所选始发地
    int getDestination();//获取用户所选目的地
    void getStartTime();//获取开始时间
    void getDeadline();//获取截止时间
    void displaySpentTime();//显示已经花费的时间
    void displayTotalTime();//显示方案所需总时间
    void setTotalTime(int totaldaytmp, int totalhourtmp, int totalmintmp);//设置方案所需总时间
    void setFare(int faretmp);//设置方案所需经费
    void displayFare();//显示方案所需经费
    void displayPath();//在pathlist窗口中显示路径
    QString numToCity(int index);//将城市编号转为城市名称

private:
    Ui::Widget *ui;

    //主算法需用变量
    int strategy;
    int start;
    int destination;
    int startclickedtimes;//“开始”按钮点击次数，0次表示首次运行，1表示其他
    int priordestination;//保留目的地，如果运行过程中目的地改变，作为两个目的地比较的前者，与currentIndex比较
    int totalday;//策略所需总时间--天数
    int totalhour;//策略所需总时间--小时数
    int totalmin;//策略所需总时间--分钟数
    int fare;

    //参与时间进程的变量
    int currentyear;
    int currentmonth;
    int currentday;
    int currenthour;
    int currentmin;
    int secondcnt;

    int deadlineyear;
    int deadlinemonth;
    int deadlineday;
    int deadlinehour;
    int deadlinemin;

    int startyear;
    int startmonth;
    int startday;
    int starthour;
    int startmin;

    QTimer *mstimer;
    QThread *timethread;
    QDate date;
    QTime time;

private slots:
    void startButtonClicked();//开始按钮按下，开始计算路径图形输出
    void resetButtonClicked();//reset按钮按下，重置所有变量重新来过
    void displayCurrentTime();//显示当前时间
    void timeStart();//此函数用于，如果mstimer未激活，那么this发出DoStartTimer信号

signals:
    void DoStartTimer();//开始计时的信号

};

#endif // WIDGET_H
