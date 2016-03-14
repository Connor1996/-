#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);
    this->setWindowTitle("Travel-Query-System");

    ui->DurationText->setEnabled(false);
    ui->FareEdit->setEnabled(false);
    ui->TotalTimeEdit->setEnabled(false);

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
    QObject::connect(ui->resetButton, SIGNAL(clicked()), this, SLOT(resetButtonClicked()));

    QObject::connect(mstimer, SIGNAL(timeout()), this, SLOT(displayCurrentTime()));
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
    QTime startTime;
    if (startclickedtimes == 0)//首次运行，目的地和始发地不能相同，相同则弹出窗口，重新来过
    {
        strategy = getStrategy();
        start = getStart();
        priordestination = destination = getDestination();
        if (start == destination)
        {
            QMessageBox::information(this, "Error", QString::fromWCharArray(L"出发地和目的地相同"));
            return;
        }
        startTime = getStartTime();
        getDeadline();
        std::vector<Attribute> path = schedule.Dijkstra(startTime, strategy, start, destination);

        setTotalTime(1, 2, 30);
        displayTotalTime();
        setFare(2340);
        displayFare();
        displayPath(path);

        ui->StartComboBox->setEnabled(false);
        ui->StrategyComboBox->setEnabled(false);
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
            std::vector<Attribute> path = schedule.Dijkstra(startTime, strategy, start, destination);
            displayPath(path);
            qDebug() << "Prior Destination after changed" << priordestination;
            //getDeadline();//如果涉及第三策略下截止时间修订，则保留
        }
        qDebug()<< "------------";
    }
}

//单击“重置”按钮，重置所有变量，重新来过
void Widget::resetButtonClicked()
{
    startclickedtimes = 0;
    priordestination = 0;
    secondcnt = 0;

    ui->StartComboBox->setEnabled(true);
    ui->StrategyComboBox->setEnabled(true);
    ui->DeadlineDateTimeEdit->setEnabled(true);
    ui->StartDateTimeEdit->setEnabled(true);
    ui->StartButton->setEnabled(true);

    ui->StrategyComboBox->setCurrentIndex(0);
    ui->StartComboBox->setCurrentIndex(0);
    ui->DestinationComboBox->setCurrentIndex(0);

    ui->StartDateTimeEdit->setDate(QDate(2000, 1, 1));
    ui->StartDateTimeEdit->setTime(QTime(0, 00));
    ui->DeadlineDateTimeEdit->setReadOnly(false);
    ui->DeadlineDateTimeEdit->setDate(QDate(2000, 1, 1));
    ui->DeadlineDateTimeEdit->setTime(QTime(0, 00));

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
        QMessageBox::warning(this, "Error", QString::fromWCharArray(L"策略非法"));
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
        QMessageBox::warning(this, "Error", QString::fromWCharArray(L"始发地非法"));
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
        QMessageBox::warning(this, "Error", QString::fromWCharArray(L"目的地非法"));
        break;
    }
    return ui->DestinationComboBox->currentIndex();
}

//获取截止时间
void Widget::getDeadline()
{
    QDate date = ui->DeadlineDateTimeEdit->date();
    QTime time = ui->DeadlineDateTimeEdit->time();
    date.getDate(&deadlineyear, &deadlinemonth, &deadlineday);
    deadlinehour = time.hour();
    deadlinemin = time.minute();
    ui->DeadlineDateTimeEdit->setEnabled(false);
    qDebug() << "Deadline:" << deadlineyear << deadlinemonth << deadlineday << deadlinehour << deadlinemin;
}

//获取开始时间
QTime Widget::getStartTime()
{
    date = ui->StartDateTimeEdit->date();
    time = ui->StartDateTimeEdit->time();
    date.getDate(&currentyear, &currentmonth, &currentday);
    currenthour = time.hour();
    currentmin = time.minute();

    startyear = currentyear;
    startmonth = currentmonth;
    startday = currentday;
    starthour = currenthour;
    startmin = currentmin;

    ui->StartDateTimeEdit->setEnabled(false);
    return time;
}

//显示当前时间
void Widget::displayCurrentTime()
{
    if (startclickedtimes == 1)
    {
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
        displaySpentTime();
    }
}

//如果mstimer未激活，那么发出DoStartTimer信号
void Widget::timeStart()
{
    if (mstimer->isActive())
        return;
    emit DoStartTimer();
}

//计算开始出行到目前所用的时间
void Widget::displaySpentTime()
{
    //QString durationyear = QString::number(currentyear - startyear);//年月表示时间跨度不准确，如durationmonth+1，不能确定是因为31天还是30天+1
    //QString durationmonth = QString::number(currentmonth - startmonth);
    int durday = currentday - startday;
    int durhour = currenthour - starthour;
    int durmin = currentmin - startmin;
    if (durmin == 60)
    {
        durmin = 0;
        durhour ++;
        if (durhour== 24)
        {
            durhour = 0;
            durday++;
        }
    }
    QString durationday = QString::number(durday);
    QString durationhour = QString::number(durhour);
    QString durationmin = QString::number(durmin);

    ui->DurationText->setText(durationday + QString::fromWCharArray(L"天") + durationhour + QString::fromWCharArray(L"小时") + durationmin + QString::fromWCharArray(L"分钟"));
}

//直接在TotalTimeEdit显示方案所需总时间
void Widget::displayTotalTime()
{
    ui->TotalTimeEdit->setText(QString::number(totalday) + QString::fromWCharArray(L"天") + QString::number(totalhour) + QString::fromWCharArray(L"小时") + QString::number(totalmin) + QString::fromWCharArray(L"分钟"));
}

//设置方案所需总时间
void Widget::setTotalTime(int totaldaytmp, int totalhourtmp, int totalmintmp)
{
    totalday = totaldaytmp;
    totalhour = totalhourtmp;
    totalmin = totalmintmp;
}

//显示方案所需经费
void Widget::displayFare()
{
    ui->FareEdit->setText(QString::number(fare) + QString::fromWCharArray(L"元"));
}

//设置方案所需经费
void Widget::setFare(int faretmp)
{
    fare = faretmp;
}

//将方案中城市编号对应城市名称
QString Widget::numToCity(int index){
    QString city;
    switch (index)
    {
    case 0:
        //北京
        //city = tr("北京");
        city = QString::fromWCharArray(L"北京");
        break;
    case 1:
        //上海
        //city = tr("上海");
        city = QString::fromWCharArray(L"上海");
        break;
    case 2:
        //西安
        //city = tr("西安");
        city = QString::fromWCharArray(L"西安");
        break;
    case 3:
        //武汉
        //city = tr("武汉");
        city = QString::fromWCharArray(L"武汉");
        break;
    case 4:
        //深圳
        //city = tr("深圳");
        city = QString::fromWCharArray(L"深圳");
        break;
    case 5:
        //郑州
        //city = tr("郑州");
        city = QString::fromWCharArray(L"郑州");
        break;
    case 6:
        //海南
        //city = tr("海南");
        city = QString::fromWCharArray(L"海南");
        break;
    case 7:
        //拉萨
        //city = tr("拉萨");
        city = QString::fromWCharArray(L"拉萨");
        break;
    case 8:
        //纽约
        //city = tr("纽约");
        city = QString::fromWCharArray(L"纽约");
        break;
    case 9:
        //首尔
        //city = tr("首尔");
        city = QString::fromWCharArray(L"首尔");
        break;
    case 10:
        //哈尔滨
        //city = tr("哈尔滨");
        city = QString::fromWCharArray(L"哈尔滨");
        break;
    case 11:
        //莫斯科
        //city = tr("莫斯科");
        city = QString::fromWCharArray(L"莫斯科");
        break;
    default:
        QMessageBox::warning(this, "Error", QString::fromWCharArray(L"程序运行错误--请联系工作人员"));
        break;
    }
    return city;
}

//显示路径
void Widget::displayPath(std::vector<Attribute> path)
{
    QVBoxLayout *listlayout = new QVBoxLayout;
    QWidget *containwidget = new QWidget(ui->PathList);
    for(std::vector<Attribute>::size_type index = 0;
            index != path.size(); index++)
    {
        QLabel *vehiclelabel = new QLabel;
        QLabel *textlabel = new QLabel;

        if (path[index].vehicle == 0)
            vehiclelabel->setPixmap(QPixmap(":/new/vehicle/resource/car.ico"));
        else if (path[index].vehicle == 1)
            vehiclelabel->setPixmap(QPixmap(":/new/vehicle/resource/train.ico"));
        else if (path[index].vehicle == 2)
            vehiclelabel->setPixmap(QPixmap(":/new/vehicle/resource/plane.ico"));
        textlabel->setText(numToCity(path[index].from) + "->" + numToCity(path[index].to) + QString::fromWCharArray(L" 车次：") + path[index].num + QString::fromWCharArray(L" 票价：") + QString::number(path[index].cost));
//        textlabel->setText(numToCity(path[index].from) + "->" + numToCity(path[index].to) + tr(" 车次：") + path[index].num + tr(" 票价：") + QString::number(path[index].cost));

        QHBoxLayout *rowlayout = new QHBoxLayout;
        rowlayout->addWidget(vehiclelabel);
        rowlayout->addWidget(textlabel);
        listlayout->addLayout(rowlayout);
    }
    containwidget->setLayout(listlayout);
    ui->PathList->setWidget(containwidget);
}
