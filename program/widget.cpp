#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setFixedSize(1280, 720);
    this->setWindowTitle("Travel-Query-System");

    ui->StartDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->DeadlineDateTimeEdit->setDateTime(QDateTime::currentDateTime());
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
        getDeadline();
        std::vector<Attribute> path = schedule.Dijkstra(startDateTime, strategy, start, destination);

        displayTotalTime(path);
        displayFare(path);
        displayPath(path);

        ui->StartComboBox->setEnabled(false);
        ui->StrategyComboBox->setEnabled(false);
        startclickedtimes += 1;
        return;
    }
    if (startclickedtimes == 1)//不是首次运行，执行以下代码，如果目的地没有改变那么不作操作
    {
        if (priordestination != ui->DestinationComboBox->currentIndex())
        {
            //strategy = getStrategy();//如果涉及途中策略更改，则保留
            //start = getStart();
            priordestination = destination = getDestination();
            std::vector<Attribute> path = schedule.Dijkstra(startDateTime, strategy, start, destination);

            displayTotalTime(path);
            displayFare(path);
            displayPath(path);
            //getDeadline();//如果涉及第三策略下截止时间修订，则保留
        }
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

    ui->StartDateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->DeadlineDateTimeEdit->setDateTime(QDateTime::currentDateTime());

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

    ui->StartDateTimeEdit->setEnabled(false);
    return datetime;
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
    int durday = currentday - startday;
    int durhour = currenthour - starthour;
    int durmin = currentmin - startmin;

    if (durmin < 0)
    {
        durmin += 60;
        durhour--;
    }
    if (durhour < 0)
    {
        durhour += 24;
        durday--;
    }

    QString durationday = QString::number(durday);
    QString durationhour = QString::number(durhour);
    QString durationmin = QString::number(durmin);

    ui->DurationText->setText(durationday + QString::fromWCharArray(L"天 ") + durationhour + QString::fromWCharArray(L"小时 ") + durationmin + QString::fromWCharArray(L"分钟"));
}

//直接在TotalTimeEdit显示方案所需总时间
void Widget::displayTotalTime(std::vector<Attribute> path)
{
    QTime endtime = path[path.size()-1].end;
    int durationhour = endtime.hour() - starthour;
    int durationmin = endtime.minute() - startmin;
    int durationday = 0;

    if (starthour > path[0].begin.hour())
        durationday++;
    else if (startmin > path[0].begin.minute())
        durationday++;

    for(std::vector<Attribute>::size_type index = 0;
            index != path.size()-1; index++)
    {
        for(std::vector<Attribute>::size_type jndex = index + 1;
                jndex != path.size(); jndex++)
        {
            if (path[jndex].begin.hour() < path[index].end.hour())
            durationday ++;
            else if (path[jndex].begin.minute() < path[index].end.minute())
                durationday++;
        }
    }

    if (durationmin < 0)
    {
        durationmin = 60 + durationmin;
        durationhour--;
    }
    if (durationhour < 0)
    {
        durationhour = 24 + durationhour;
        durationday--;
    }

    ui->TotalTimeEdit->setText(QString::number(durationday) + QString::fromWCharArray(L"天 ") + QString::number(durationhour) + QString::fromWCharArray(L"小时 ") + QString::number(durationmin) + QString::fromWCharArray(L"分钟"));
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
            vehiclelabel->setPixmap(QPixmap(":/new/vehicle/resource/car.ico"));
        else if (path[index].vehicle == 1)
            vehiclelabel->setPixmap(QPixmap(":/new/vehicle/resource/train.ico"));
        else if (path[index].vehicle == 2)
            vehiclelabel->setPixmap(QPixmap(":/new/vehicle/resource/plane.ico"));

        int beginhour = path[index].begin.hour();
        int beginmin = path[index].begin.minute();
        int endhour = path[index].end.hour();
        int endmin = path[index].end.minute();

        textlabel->setText(" " + numToCity(path[index].from) + "->" + numToCity(path[index].to) +
                           QString::fromWCharArray(L" 车次:") + path[index].num + "\n" +
                           " " + QString::fromWCharArray(L"出发时间:") + QString::number(beginhour) + ":" + QString::number(beginmin) +
                           QString::fromWCharArray(L" 到站时间:") + QString::number(endhour) + ":" + QString::number(endmin) + "\n" +
                           QString::fromWCharArray(L" 票价:") + QString::number(path[index].cost));

        QHBoxLayout *rowlayout = new QHBoxLayout;
        rowlayout->addWidget(vehiclelabel);
        rowlayout->addWidget(textlabel);
        listlayout->addLayout(rowlayout);
    }
    containwidget->setLayout(listlayout);
    ui->PathList->setWidget(containwidget);
}
