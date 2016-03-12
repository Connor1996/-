#ifndef WIDGET_H
#define WIDGET_H

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
    void getDeadline();//获取截止时间

private:
    Ui::Widget *ui;
    int strategy;
    int start;
    int destination;
    int currentyear;
    int currentmonth;
    int currentday;
    int currenthour;
    int currentmin;
    int secondcnt;
    int startclickedtimes;//“开始”按钮点击次数，0次表示首次运行，1表示其他
    int priordestination;//保留目的地，如果运行过程中目的地改变，作为两个目的地比较的前者，与currentIndex比较
    QTimer *mstimer;
    QThread *timethread;

private slots:
    void startButtonClicked();//开始按钮按下，开始计算路径图形输出
    void timeSlot();//###
    void timeStart();//###

signals://###
    void DoStartTimer();//###

};

#endif // WIDGET_H
