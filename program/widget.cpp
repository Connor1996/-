#include "widget.h"
#include "ui_widget.h"
#include "log.h"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
    throughcity(12, false),
    currentTraveler(-1)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);
    this->setWindowTitle("Travel-Query-System");


    ui->StartDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->DeadlineDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->StrategyComboBox->setEnabled(false);
    ui->StartComboBox->setEnabled(false);
    ui->DestinationComboBox->setEnabled(false);
    ui->TravelerComboBox->setEnabled(false);
    ui->ThroughCityCheckBox->setEnabled(false);

    ui->city0cbox->setEnabled(false);
    ui->city1cbox->setEnabled(false);
    ui->city2cbox->setEnabled(false);
    ui->city3cbox->setEnabled(false);
    ui->city4cbox->setEnabled(false);
    ui->city5cbox->setEnabled(false);
    ui->city6cbox->setEnabled(false);
    ui->city7cbox->setEnabled(false);
    ui->city8cbox->setEnabled(false);
    ui->city9cbox->setEnabled(false);
    ui->city10cbox->setEnabled(false);
    ui->city11cbox->setEnabled(false);

    ui->StartDateTimeEdit->setEnabled(false);
    ui->DeadlineDateTimeEdit->setEnabled(false);
    ui->StartButton->setEnabled(false);
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
    addtravelertimes = 0;

    QObject::connect(ui->addTravelerButton, SIGNAL(clicked()), this, SLOT(addTravelerButtonClicked()));
    QObject::connect(ui->TravelerComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(travelerChanged()));

    QObject::connect(ui->ThroughCityCheckBox, SIGNAL(toggled(bool)), this, SLOT(activeThroughCity()));
    QObject::connect(ui->city0cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity0()));
    QObject::connect(ui->city1cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity1()));
    QObject::connect(ui->city2cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity2()));
    QObject::connect(ui->city3cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity3()));
    QObject::connect(ui->city4cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity4()));
    QObject::connect(ui->city5cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity5()));
    QObject::connect(ui->city6cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity6()));
    QObject::connect(ui->city7cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity7()));
    QObject::connect(ui->city8cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity8()));
    QObject::connect(ui->city9cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity9()));
    QObject::connect(ui->city10cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity10()));
    QObject::connect(ui->city11cbox, SIGNAL(toggled(bool)), this, SLOT(setThroungCity11()));

    QObject::connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));

    QObject::connect(mstimer, SIGNAL(timeout()), this, SLOT(displaySpentTime()));
    QObject::connect(ui->StartButton, SIGNAL(clicked()), this, SLOT(timeStart()));
    QObject::connect(this, SIGNAL(DoStartTimer()), mstimer, SLOT(start()));

}

Widget::~Widget()
{
    delete ui;
    delete timethread;
}

//单击“开始”按钮，获取用户输入信息
void Widget::startButtonClicked()
{
    startclicked[ui->TravelerComboBox->currentIndex()] = true;
    QDateTime startDateTime;
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
        startDateTime = getStartTime();

        travelers[ui->TravelerComboBox->currentIndex()] = (Traveler(addtravelertimes-1, startDateTime,
                                                                    getDeadline(), QDateTime::currentDateTime(), strategy, start, destination, ui->ThroughCityCheckBox->isChecked(), throughcity));
        std::vector<Attribute> path = travelers[ui->TravelerComboBox->currentIndex()].getPlan();
        if (path.size() == 0)
        {
            QMessageBox::information(this, "Error", QString::fromWCharArray(L"无有效路径"));
            return;
        }

        currentTraveler = ui->TravelerComboBox->currentIndex();

        displayTotalTime();
        displayFare(path);
        displayPath(path);

        ui->StartComboBox->setEnabled(false);
        ui->StrategyComboBox->setEnabled(false);
        ui->StartDateTimeEdit->setEnabled(false);
        ui->DeadlineDateTimeEdit->setEnabled(false);
        startclickedtimes += 1;
        return;
    }
    if (startclickedtimes == 1)//不是首次运行，执行以下代码，如果目的地没有改变那么不作操作
    {
        if (priordestination != ui->DestinationComboBox->currentIndex())
        {
            strategy = getStrategy();//如果涉及途中策略更改，则保留
            destination = getDestination();
            //start = getStart();
            priordestination = destination = getDestination();
            std::vector<Attribute> path = travelers[ui->TravelerComboBox->currentIndex()].changePlan(strategy, destination);

            currentTraveler = ui->TravelerComboBox->currentIndex();

            displayTotalTime();
            displayFare(path);
            displayPath(path);
            //getDeadline();//如果涉及第三策略下截止时间修订，则保留
        }
    }
}

//单击“添加旅客”按钮，开始运行
void Widget::addTravelerButtonClicked()
{
    std::vector<bool> temp(12, false);
    throughcity = temp;
    travelers.push_back(Traveler(addtravelertimes-1, getStartTime(), getDeadline(),
                                 QDateTime::currentDateTime(), getStrategy(),
                                 getStart(), getDestination(),
                                 ui->ThroughCityCheckBox->isChecked(), throughcity));
    //totaltime.push_back(TotalTime(0, 0, 0));
    startclicked.push_back(false);
    addtravelertimes += 1;
    startclickedtimes = 0;
    priordestination = 0;
    secondcnt = 0;

    ui->TravelerComboBox->addItem(QString::number(addtravelertimes));
    ui->TravelerComboBox->setCurrentText(QString::number(addtravelertimes));

    ui->TravelerComboBox->setEnabled(true);
    ui->StartComboBox->setEnabled(true);
    ui->StrategyComboBox->setEnabled(true);
    ui->DestinationComboBox->setEnabled(true);
    ui->StrategyComboBox->setCurrentIndex(0);
    ui->StartComboBox->setCurrentIndex(0);
    ui->DestinationComboBox->setCurrentIndex(0);
    ui->ThroughCityCheckBox->setEnabled(true);
    ui->DeadlineDateTimeEdit->setEnabled(true);
    ui->StartDateTimeEdit->setEnabled(true);
    ui->StartButton->setEnabled(true);

    ui->StartDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->DeadlineDateTimeEdit->setDateTime(QDateTime::currentDateTime());
}

//旅客选择更改，显示更改
void Widget::travelerChanged()
{
    ui->StartDateTimeEdit->setDateTime(travelers[ui->TravelerComboBox->currentIndex()].startTime);
    ui->DeadlineDateTimeEdit->setDateTime(travelers[ui->TravelerComboBox->currentIndex()].deadlineTime);
    ui->StrategyComboBox->setCurrentIndex(travelers[ui->TravelerComboBox->currentIndex()].strategy);
    ui->StartComboBox->setCurrentIndex(travelers[ui->TravelerComboBox->currentIndex()].origin);
    ui->DestinationComboBox->setCurrentIndex(travelers[ui->TravelerComboBox->currentIndex()].destination);

    if (startclicked[ui->TravelerComboBox->currentIndex()])
    {
        displayFare(travelers[ui->TravelerComboBox->currentIndex()].getPlan());
        displayTotalTime();
        displayPath(travelers[ui->TravelerComboBox->currentIndex()].getPlan());
        displaySpentTime();

        ui->StartComboBox->setEnabled(false);
        ui->StartDateTimeEdit->setEnabled(false);
        ui->DeadlineDateTimeEdit->setEnabled(false);
        ui->ThroughCityCheckBox->setChecked(travelers[ui->TravelerComboBox->currentIndex()].isChecked);
        throughcity = travelers[ui->TravelerComboBox->currentIndex()].throughCity;
        activeThroughCity();

        currentTraveler = ui->TravelerComboBox->currentIndex();
    }
    else
    {
        ui->StrategyComboBox->setEnabled(true);
        ui->StartComboBox->setEnabled(true);
        ui->DestinationComboBox->setEnabled(true);
        ui->StartDateTimeEdit->setEnabled(true);
        ui->DeadlineDateTimeEdit->setEnabled(true);
        ui->ThroughCityCheckBox->setChecked(false);
        throughcity = travelers[ui->TravelerComboBox->currentIndex()].throughCity;
        activeThroughCity();

        ui->StartDateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->DeadlineDateTimeEdit->setDateTime(QDateTime::currentDateTime());
        ui->StrategyComboBox->setCurrentIndex(0);
        ui->StartComboBox->setCurrentIndex(0);
        ui->DestinationComboBox->setCurrentIndex(0);
        QVBoxLayout *listlayout = new QVBoxLayout;
        QWidget *containwidget = new QWidget(ui->PathList);
        containwidget->setLayout(listlayout);
        ui->PathList->setWidget(containwidget);
        ui->FareEdit->clear();
        ui->TotalTimeEdit->clear();
        ui->DurationText->clear();

        currentTraveler = -1;
    }
}

//获取用户所选策略
int Widget::getStrategy()
{
    return ui->StrategyComboBox->currentIndex();
}

//获取用户所选始发地
int Widget::getStart()
{
    return ui->StartComboBox->currentIndex();
}

//获取用户所选目的地
int Widget::getDestination()
{
    return ui->DestinationComboBox->currentIndex();
}

//获取截止时间
QDateTime Widget::getDeadline()
{
    return ui->DeadlineDateTimeEdit->dateTime();
}

//获取开始时间
QDateTime Widget::getStartTime()
{
    date = ui->StartDateTimeEdit->date();
    time = ui->StartDateTimeEdit->time();
    datetime = ui->StartDateTimeEdit->dateTime();
    date.getDate(&currentyear, &currentmonth, &currentday);
    currenthour = time.hour();
    currentmin = time.minute();

    startyear = currentyear;
    startmonth = currentmonth;
    startday = currentday;
    starthour = currenthour;
    startmin = currentmin;

    return datetime;
}

//获取已用时间
QDateTime Widget::getSpentTime()
{
    QDate systemStartDay = travelers[ui->TravelerComboBox->currentIndex()].systemStartTime.date();
    QTime systemStartTime = travelers[ui->TravelerComboBox->currentIndex()].systemStartTime.time();
    int systemstartyear, systemstartmonth, systemstartday;
    int systemstarthour, systemstartmin, systemstartsec, systemstartmsec;

    systemStartDay.getDate(&systemstartyear, &systemstartmonth, &systemstartday);
    systemstarthour = systemStartTime.hour();
    systemstartmin = systemStartTime.minute();
    systemstartsec = systemStartTime.second();
    systemstartmsec = systemStartTime.msec();

    QDate systemCurrentDay = QDate::currentDate();
    QTime systemCurrentTime = QTime::currentTime();
    int systemcurrentyear, systemcurrentmonth, systemcurrentday;
    int systemcurrenthour, systemcurrentmin, systemcurrentsec, systemcurrentmsec;
    systemCurrentDay.getDate(&systemcurrentyear, &systemcurrentmonth, &systemcurrentday);
    systemcurrenthour = systemCurrentTime.hour();
    systemcurrentmin = systemCurrentTime.minute();
    systemcurrentsec = systemCurrentTime.second();
    systemcurrentmsec = systemCurrentTime.msec();

    int duryear = systemcurrentyear - systemstartyear;
    int durmonth = systemcurrentmonth - systemstartmonth;
    int durday = systemcurrentday - systemstartday;
    int durhour = systemcurrenthour - systemstarthour;
    int durmin = systemcurrentmin - systemstartmin;
    int dursec = systemcurrentsec - systemstartsec;
    int durmsec = systemcurrentmsec - systemstartmsec;

    if (durmsec < 0)
    {
        dursec--;
        durmsec += 1000;
    }
    if (dursec < 0)
    {
        durmin--;
        dursec += 60;
    }
    if (durmin < 0)
    {
        durhour--;
        durmin += 60;
    }
    if (durhour < 0)
    {
        durday--;
        durhour += 24;
    }
    if (durday < 0)
    {
        durmonth--;
        switch (systemstartmonth)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            durday += 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            durday += 30;
            break;
        case 2:
            if (systemstartyear % 4 == 0 || systemstartyear % 400 == 0)
                durday += 29;
            else
                durday += 28;
            break;
        }
    }
    if (durmonth < 0)
    {
        duryear--;
        durmonth += 12;
    }

    durmsec *= 360;
    dursec *= 360;
    durmin *= 360;
    durhour *= 360;
    durday *= 360;
    durmonth *= 360;
    duryear *= 360;

    while (durmsec >= 1000)
    {
        durmsec -= 1000;
        dursec++;
    }
    while (dursec >= 60)
    {
        dursec -= 60;
        durmin++;
    }
    while (durmin >= 60)
    {
        durmin -= 60;
        durhour++;
    }
    while (durhour >= 24)
    {
        durhour -= 24;
        durday++;
    }
    durmonth += duryear * ((systemstartyear % 4 == 0 || systemstartyear % 400 == 0)?366:365);
    durday += durmonth * 30;

    if (startclickedtimes == 1)
    {
        durmsec++;
        if(durmsec == 60)
        {
             dursec++;
             durmsec = 0;
             if (dursec == 60)
             {
                 durmin++;
                 dursec = 0;
                 if (durmin == 60)
                 {
                     durhour++;
                     durmin = 0;
                     if (durhour == 24)
                     {
                         durday++;
                         durhour = 0;
                     }
                 }
             }
        }
    }
    QDateTime spentDateTime;
    QDate spentDate(0, 0, durday);
    QTime spentTime(durhour, durmin, dursec, 0);
    spentDateTime.setDate(spentDate);
    spentDateTime.setTime(spentTime);
    return spentDateTime;
}

//如果mstimer未激活，那么发出DoStartTimer信号
void Widget::timeStart()
{
    if (mstimer->isActive())
        return;
    emit DoStartTimer();
}

//显示开始出行到目前所用的时间
void Widget::displaySpentTime()
{

    QDate systemStartDay = travelers[ui->TravelerComboBox->currentIndex()].systemStartTime.date();
    QTime systemStartTime = travelers[ui->TravelerComboBox->currentIndex()].systemStartTime.time();
    int systemstartyear, systemstartmonth, systemstartday;
    int systemstarthour, systemstartmin, systemstartsec, systemstartmsec;
    systemStartDay.getDate(&systemstartyear, &systemstartmonth, &systemstartday);
    systemstarthour = systemStartTime.hour();
    systemstartmin = systemStartTime.minute();
    systemstartsec = systemStartTime.second();
    systemstartmsec = systemStartTime.msec();

    QDate systemCurrentDay = QDate::currentDate();
    QTime systemCurrentTime = QTime::currentTime();
    int systemcurrentyear, systemcurrentmonth, systemcurrentday;
    int systemcurrenthour, systemcurrentmin, systemcurrentsec, systemcurrentmsec;
    systemCurrentDay.getDate(&systemcurrentyear, &systemcurrentmonth, &systemcurrentday);
    systemcurrenthour = systemCurrentTime.hour();
    systemcurrentmin = systemCurrentTime.minute();
    systemcurrentsec = systemCurrentTime.second();
    systemcurrentmsec = systemCurrentTime.msec();

    int duryear = systemcurrentyear - systemstartyear;
    int durmonth = systemcurrentmonth - systemstartmonth;
    int durday = systemcurrentday - systemstartday;
    int durhour = systemcurrenthour - systemstarthour;
    int durmin = systemcurrentmin - systemstartmin;
    int dursec = systemcurrentsec - systemstartsec;
    int durmsec = systemcurrentmsec - systemstartmsec;

    if (durmsec < 0)
    {
        dursec--;
        durmsec += 1000;
    }
    if (dursec < 0)
    {
        durmin--;
        dursec += 60;
    }
    if (durmin < 0)
    {
        durhour--;
        durmin += 60;
    }
    if (durhour < 0)
    {
        durday--;
        durhour += 24;
    }
    if (durday < 0)
    {
        durmonth--;
        switch (systemstartmonth)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            durday += 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            durday += 30;
            break;
        case 2:
            if (systemstartyear % 4 == 0 || systemstartyear % 400 == 0)
                durday += 29;
            else
                durday += 28;
            break;
        }
    }
    if (durmonth < 0)
    {
        duryear--;
        durmonth += 12;
    }

    durmsec *= 360;
    dursec *= 360;
    durmin *= 360;
    durhour *= 360;
    durday *= 360;
    durmonth *= 360;
    duryear *= 360;

    while (durmsec >= 1000)
    {
        durmsec -= 1000;
        dursec++;
    }
    while (dursec >= 60)
    {
        dursec -= 60;
        durmin++;
    }
    while (durmin >= 60)
    {
        durmin -= 60;
        durhour++;
    }
    while (durhour >= 24)
    {
        durhour -= 24;
        durday++;
    }
    durmonth += duryear * ((systemstartyear % 4 == 0 || systemstartyear % 400 == 0)?366:365);
    durday += durmonth * 30;

    if (startclickedtimes == 1)
    {
        durmsec++;
        if(durmsec == 60)
        {
             dursec++;
             durmsec = 0;
             if (dursec == 60)
             {
                 durmin++;
                 dursec = 0;
                 if (durmin == 60)
                 {
                     durhour++;
                     durmin = 0;
                     if (durhour == 24)
                     {
                         durday++;
                         durhour = 0;
                     }
                 }
             }
        }
    }

    QString durationday = QString::number(durday);
    QString durationhour = QString::number(durhour);
    QString durationmin = QString::number(durmin);
    if (startclicked[ui->TravelerComboBox->currentIndex()])
    {
        if (travelers[ui->TravelerComboBox->currentIndex()].totalTime.date().day()*24*60 +
                travelers[ui->TravelerComboBox->currentIndex()].totalTime.time().hour()*60 +
                travelers[ui->TravelerComboBox->currentIndex()].totalTime.time().minute() >=
                durday*24*60 + durhour*60 + durmin)
        {
            ui->DurationText->setText(durationday + QString::fromWCharArray(L"天 ") + durationhour +
                                  QString::fromWCharArray(L"小时 ") + durationmin +
                                  QString::fromWCharArray(L"分钟"));
        }
        else
        {
            ui->StartButton->setEnabled(false);
            ui->DurationText->setText(QString::number(travelers[ui->TravelerComboBox->currentIndex()].totalTime.date().day())
                    + QString::fromWCharArray(L"天 ") +
                    QString::number(travelers[ui->TravelerComboBox->currentIndex()].totalTime.time().hour())
                    + QString::fromWCharArray(L"小时 ") +
                    QString::number(travelers[ui->TravelerComboBox->currentIndex()].totalTime.time().minute())
                    + QString::fromWCharArray(L"分钟"));
        }
    }
    else
        ui->DurationText->clear();
}

//直接在TotalTimeEdit显示方案所需总时间
void Widget::displayTotalTime()
{
    QDateTime totalTime = travelers[ui->TravelerComboBox->currentIndex()].totalTime;
    ui->TotalTimeEdit->setText(QString::number(totalTime.date().day()) + QString::fromWCharArray(L"天 ") +
                               QString::number(totalTime.time().hour()) + QString::fromWCharArray(L"小时 ") +
                               QString::number(totalTime.time().minute()) + QString::fromWCharArray(L"分钟"));
}

//显示方案所需经费
void Widget::displayFare(std::vector<Attribute> path)
{
    int totalcost = 0;
    for(std::vector<Attribute>::size_type index = 0;
            index != path.size(); index++)
    {
        totalcost += path[index].cost;
    }
    ui->FareEdit->setText(QString::number(totalcost) + QString::fromWCharArray(L"元"));
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
            vehiclelabel->setPixmap(QPixmap(":/car.ico"));
        else if (path[index].vehicle == 1)
            vehiclelabel->setPixmap(QPixmap(":/train.ico"));
        else if (path[index].vehicle == 2)
            vehiclelabel->setPixmap(QPixmap(":/plane.ico"));

        int beginhour = path[index].begin.hour();
        int beginmin = path[index].begin.minute();
        int endhour = path[index].end.hour();
        int endmin = path[index].end.minute();

        textlabel->setText(" " + numToCity(path[index].from) + "->" + numToCity(path[index].to) +
                           QString::fromWCharArray(L" 车次:") + path[index].num + "\n" +
                           " " + QString::fromWCharArray(L"出发:") + QString::number(beginhour) + ":" + QString::number(beginmin) +
                           QString::fromWCharArray(L" 到站:") + QString::number(endhour) + ":" + QString::number(endmin) + "\n" +
                           QString::fromWCharArray(L" 票价:") + QString::number(path[index].cost));

        QHBoxLayout *rowlayout = new QHBoxLayout;
        rowlayout->addWidget(vehiclelabel);
        rowlayout->addWidget(textlabel);
        listlayout->addLayout(rowlayout);
    }
    containwidget->setLayout(listlayout);
    ui->PathList->setWidget(containwidget);
}

//激活gridwidget中的checkbox并初始化throughcity
void Widget::activeThroughCity()
{
    ui->city0cbox->setChecked(throughcity[0]);
    ui->city1cbox->setChecked(throughcity[1]);
    ui->city2cbox->setChecked(throughcity[2]);
    ui->city3cbox->setChecked(throughcity[3]);
    ui->city4cbox->setChecked(throughcity[4]);
    ui->city5cbox->setChecked(throughcity[5]);
    ui->city6cbox->setChecked(throughcity[6]);
    ui->city7cbox->setChecked(throughcity[7]);
    ui->city8cbox->setChecked(throughcity[8]);
    ui->city9cbox->setChecked(throughcity[9]);
    ui->city10cbox->setChecked(throughcity[10]);
    ui->city11cbox->setChecked(throughcity[11]);

    if (ui->ThroughCityCheckBox->isChecked())
    {
        ui->city0cbox->setEnabled(true);
        ui->city1cbox->setEnabled(true);
        ui->city2cbox->setEnabled(true);
        ui->city3cbox->setEnabled(true);
        ui->city4cbox->setEnabled(true);
        ui->city5cbox->setEnabled(true);
        ui->city6cbox->setEnabled(true);
        ui->city7cbox->setEnabled(true);
        ui->city8cbox->setEnabled(true);
        ui->city9cbox->setEnabled(true);
        ui->city10cbox->setEnabled(true);
        ui->city11cbox->setEnabled(true);
    }
    else
    {
        ui->city0cbox->setEnabled(false);
        ui->city1cbox->setEnabled(false);
        ui->city2cbox->setEnabled(false);
        ui->city3cbox->setEnabled(false);
        ui->city4cbox->setEnabled(false);
        ui->city5cbox->setEnabled(false);
        ui->city6cbox->setEnabled(false);
        ui->city7cbox->setEnabled(false);
        ui->city8cbox->setEnabled(false);
        ui->city9cbox->setEnabled(false);
        ui->city10cbox->setEnabled(false);
        ui->city11cbox->setEnabled(false);
    }
}

//设置12个城市哪些被指定途经
void Widget::setThroungCity0()
{
   if (ui->city0cbox->isChecked())
       throughcity[0] = true;
   else
       throughcity[0] = false;
}
void Widget::setThroungCity1()
{
    if (ui->city1cbox->isChecked())
        throughcity[1] = true;
    else
        throughcity[1] = false;
}
void Widget::setThroungCity2()
{
    if (ui->city2cbox->isChecked())
        throughcity[2] = true;
    else
        throughcity[2] = false;
}
void Widget::setThroungCity3()
{
    if (ui->city3cbox->isChecked())
        throughcity[3] = true;
    else
        throughcity[3] = false;
}
void Widget::setThroungCity4()
{
   if (ui->city4cbox->isChecked())
       throughcity[4] = true;
   else
       throughcity[4]= false;
}
void Widget::setThroungCity5()
{
    if (ui->city5cbox->isChecked())
        throughcity[5] = true;
    else
        throughcity[5] = false;
}
void Widget::setThroungCity6()
{
    if (ui->city6cbox->isChecked())
        throughcity[6] = true;
    else
        throughcity[6] = false;
}
void Widget::setThroungCity7()
{
    if (ui->city7cbox->isChecked())
        throughcity[7] = true;
    else
        throughcity[7] = false;
}
void Widget::setThroungCity8()
{
    if (ui->city8cbox->isChecked())
        throughcity[8] = true;
    else
        throughcity[8] = false;
}
void Widget::setThroungCity9()
{
    if (ui->city9cbox->isChecked())
        throughcity[9] = true;
    else
        throughcity[9] = false;
}
void Widget::setThroungCity10()
{
    if (ui->city10cbox->isChecked())
        throughcity[10] = true;
    else
        throughcity[10] = false;
}
void Widget::setThroungCity11()
{
    if (ui->city11cbox->isChecked())
        throughcity[11] = true;
    else
        throughcity[11] = false;
}
