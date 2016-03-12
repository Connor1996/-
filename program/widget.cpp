#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->resize(1280, 720);
    this->setWindowTitle("Travel-Query-System");

    //计时功能及所需的线程
    mstimer = new QTimer;
    mstimer->setInterval(1);

    timethread = new QThread();
    timethread->start();

    mstimer->moveToThread(timethread);

    //开始点击次数初始化--前目的地初始化--计秒初始化
    startclickedtimes = 0;
    priordestination = 0;
    secondcnt = 0;

    QObject::connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    QObject::connect(mstimer, SIGNAL(timeout()), this, SLOT(timeSlot()));
    QObject::connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(timeStart()));
    QObject::connect(this, SIGNAL(DoStartTimer()), mstimer, SLOT(start()));

}

Widget::~Widget()
{
    delete ui;
}

//单击“开始”按钮，获取用户输入信息
void Widget::startButtonClicked()
{
    if (startclickedtimes == 0)//首次运行，目的地和始发地不能相同，相同则弹出窗口，重新来过
    {
        strategy = getStrategy();
        start = getStart();
        priordestination = destination = getDestination();
        if (start == destination)
        {
            QMessageBox::information(this, "Error", QString::fromWCharArray(L"出发地目的地相同"));
            return;
        }
        getDeadline();
        startclickedtimes += 1;
        qDebug()<< "------------";
        return;
    }
    if (startclickedtimes == 1)//不是首次运行，执行以下代码，如果目的地没有改变那么不作操作
    {
        qDebug() << "Prior Destination before changed:" << priordestination;
        if (priordestination != ui->DestinationComboBox->currentIndex())
        {
            //strategy = getStrategy();//如果涉及途中策略更改，则保留
            //start = getStart();
            priordestination = destination = getDestination();
            qDebug() << "Prior Destination after changed" << priordestination;
            //getDeadline();//如果涉及第三策略下截止时间修订，则保留
        }
        qDebug()<< "------------";
    }
}

//获取用户所选策略
int Widget::getStrategy()
{
    qDebug()<< "Strategy";
    switch (ui->StrategyComboBox->currentIndex())
    {
    case 0:
        //费用最少策略
        qDebug()<< "Least Fare";
        break;
    case 1:
        //耗时最短策略
        qDebug()<< "Least Time";
        break;
    case 2:
        //限时费用最少
        qDebug()<< "Least Fare in Given Time";
        break;
    default:
        QMessageBox::warning(this, "Error", "Illegal Strategy");
        break;
    }
    return ui->StrategyComboBox->currentIndex();
}

//获取用户所选始发地
int Widget::getStart()
{
    qDebug()<< "Start:";
    switch (ui->StartComboBox->currentIndex())
    {
    case 0:
        //北京
        qDebug()<< "Beijing";
        break;
    case 1:
        //上海
        qDebug()<< "Shanghai";
        break;
    case 2:
        //西安
        qDebug()<< "Xi`an";
        break;
    case 3:
        //武汉
        qDebug()<< "Wuhan";
        break;
    case 4:
        //深圳
        qDebug()<< "Shenzhen";
        break;
    case 5:
        //郑州
        qDebug()<< "Zhengzhou";
        break;
    case 6:
        //海南
        qDebug()<< "Hainan";
        break;
    case 7:
        //拉萨
        qDebug()<< "Lasa";
        break;
    case 8:
        //纽约
        qDebug()<< "NewYork";
        break;
    case 9:
        //首尔
        qDebug()<< "Seoul";
        break;
    case 10:
        //哈尔滨
        qDebug()<< "Haerbing";
        break;
    case 11:
        //莫斯科
        qDebug()<< "Moscow";
        break;
    default:
        QMessageBox::warning(this, "Error", "Start City Illegal");
        break;
    }
    return ui->StartComboBox->currentIndex();
}

//获取用户所选目的地
int Widget::getDestination()
{
    qDebug()<< "Destination:";
    switch (ui->DestinationComboBox->currentIndex())
    {
    case 0:
        //北京
        qDebug()<< "Beijing";
        break;
    case 1:
        //上海
        qDebug()<< "Shanghai";
        break;
    case 2:
        //西安
        qDebug()<< "Xi`an";
        break;
    case 3:
        //武汉
        qDebug()<< "Wuhan";
        break;
    case 4:
        //深圳
        qDebug()<< "Shenzhen";
        break;
    case 5:
        //郑州
        qDebug()<< "Zhengzhou";
        break;
    case 6:
        //海南
        qDebug()<< "Hainan";
        break;
    case 7:
        //拉萨
        qDebug()<< "Lasa";
        break;
    case 8:
        //纽约
        qDebug()<< "NewYork";
        break;
    case 9:
        //首尔
        qDebug()<< "Seoul";
        break;
    case 10:
        //哈尔滨
        qDebug()<< "Haerbing";
        break;
    case 11:
        //莫斯科
        qDebug()<< "Moscow";
        break;
    default:
        QMessageBox::warning(this, "Error", "Start City Illegal");
        break;
    }
    return ui->DestinationComboBox->currentIndex();
}

//获取截止时间
void Widget::getDeadline()
{
    int year, month, day, hour, min;
    QDate date = ui->DeadlineDateTimeEdit->date();
    QTime time = ui->DeadlineDateTimeEdit->time();
    date.getDate(&year, &month, &day);
    hour = time.hour();
    min = time.minute();
    qDebug() << "Deadline:" << year << month << day << hour << min;
}
//##############
void Widget::timeSlot()
{
    QDate date = ui->StartDateTimeEdit->date();
    QTime time = ui->StartDateTimeEdit->time();
    date.getDate(&currentyear, &currentmonth, &currentday);
    currenthour = time.hour();
    currentmin = time.minute();
    secondcnt ++;
    if(secondcnt == 360)
    {
        currentmin ++;
        secondcnt = 0;
        if (currentmin == 60)
        {
            currenthour ++;
            currentmin = 0;
            if (currenthour == 24)
            {
                currentday ++;
                currenthour = 0;
                switch (currentmonth)
                {
                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                    if (currentday == 32)
                    {
                        currentmonth ++;
                        currentday = 1;
                    }
                    break;
                case 4:
                case 6:
                case 9:
                case 11:
                    if (currentday == 31)
                    {
                        currentmonth ++;
                        currentday = 1;
                    }
                    break;
                case 2:
                    if (currentyear % 4 == 0 || currentyear % 400 == 0)
                    {
                        if (currentday == 30)
                        {
                            currentmonth ++;
                            currentday = 1;
                        }
                    }
                    if (currentyear % 4 != 0 && currentyear % 400 != 0)
                    {
                        if (currentday == 29)
                        {
                            currentmonth ++;
                            currentday = 1;
                        }
                    }
                    break;
                case 12:
                    if (currentday == 32)
                    {
                        currentyear ++;
                        currentmonth = 1;
                    }
                default:
                    break;
                }
            }
        }
    }
    ui->StartDateTimeEdit->setReadOnly(false);
    ui->StartDateTimeEdit->setDate(QDate(currentyear, currentmonth, currentday));
    ui->StartDateTimeEdit->setTime(QTime(currenthour, currentmin, 0, 0));
}

void Widget::timeStart()
{
    if (mstimer->isActive())
        return;
    emit DoStartTimer();
}
