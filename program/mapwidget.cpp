#include "mapwidget.h"

#include <QApplication>
#include <QStateMachine>
#include <QPushButton>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QState>
#include <QLabel>

//添加新的timer，使得绘图准确
MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent), state(-1)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/map.jpg")));
    this->setPalette(palette);

    paintmstimer = new QTimer;
    paintmstimer->start(1000/60);
    QObject::connect(paintmstimer, SIGNAL(timeout()), this, SLOT(update()));
}

//绘图实践，绘制旅行过程
void MapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    Widget *fatherPtr = (Widget *)parentWidget();
    if (fatherPtr->currentTraveler != -1)
    {
        painter.drawPixmap((setPointPos()), setPointGraph());
    }
}

//根据当前状态、交通方式决定图标
QPixmap MapWidget::setPointGraph()
{
    QPixmap pointGraph;
    switch(state)
    {
    case -2://arrived destination
        pointGraph = QPixmap(":/arrive.ico");
        break;
    case -1://pause waiting
        pointGraph = QPixmap(":/pause.ico");
        break;
    case 0:
        pointGraph = QPixmap(":/car.ico");
        break;
    case 1:
        pointGraph = QPixmap(":/train.ico");
        break;
    case 2:
        pointGraph = QPixmap(":/plane.ico");
        break;
    }

    return pointGraph;
}

//设置当前图标所处位置
QPointF MapWidget::setPointPos()
{
    Widget *fatherPtr = (Widget *)parentWidget();
    static QPointF pointPos;
    std::vector<Attribute> path = fatherPtr->travelers[fatherPtr->currentTraveler].getPlan();
    QDateTime spenttime = fatherPtr->getSpentTime();
    QDateTime starttime = fatherPtr->travelers[fatherPtr->currentTraveler].startTime;

    if(spenttime >= fatherPtr->travelers[fatherPtr->currentTraveler].totalTime)
    {
         pointPos = getCityCor(path[path.size()-1].to);
         state = -2;
         qDebug() << "State: Arrival";
    }
    else
        for (std::vector<Attribute>::size_type index = 0;
            index != path.size(); index++)
        {
            QDateTime departuredatetime = fatherPtr->travelers[fatherPtr->currentTraveler].getCityDepartureDateTime(path[index].from);
            QDateTime cityarrivaltime = fatherPtr->travelers[fatherPtr->currentTraveler].getCityArrivalDateTime(path[index].to);

            if (spenttime <= getSplitTime(starttime, departuredatetime))
            {
                pointPos = getCityCor(path[index].from);
                state = -1;
                qDebug() << spenttime << getSplitTime(starttime, departuredatetime);
                qDebug() << "State: Stop" << index << departuredatetime.time().hour() << departuredatetime.time().minute();
                break;
            }
            else if (spenttime <=
                     getSplitTime(starttime, cityarrivaltime))
            {
                pointPos = getCityCor(path[index].from);
                QDateTime spentTime = spenttime;
                QDateTime start2Begin = getSplitTime(starttime, departuredatetime);
                QDateTime start2End = getSplitTime(starttime, cityarrivaltime);
                pointPos += getMoveDistance(spentTime, start2Begin, start2End, path[index].from, path[index].to);
                state = path[index].vehicle;
                qDebug() << spenttime << getSplitTime(starttime, cityarrivaltime);
                qDebug() << "State: Run" << index;
                break;
            }
        }
    //qDebug() << pointPos.x() << pointPos.y();
   // qDebug() << "----------------------------";
    return pointPos;
}

//中途更改计划时调用，用于获得新计划的始发地
int MapWidget::nextCity()
{
    Widget *fatherPtr = (Widget *)parentWidget();
    std::vector<Attribute> path = fatherPtr->travelers[fatherPtr->currentTraveler].getPlan();
    int nextCity2Arrive;
    QDateTime spenttime = fatherPtr->getSpentTime();

    if(spenttime >= fatherPtr->travelers[fatherPtr->currentTraveler].totalTime)
    {
         nextCity2Arrive = -1;
         state = -2;
         qDebug() << "State: Arrival--next City to arrive is NULL" << nextCity2Arrive;
    }
    else
        for (std::vector<Attribute>::size_type index = 0;
            index != path.size(); index++)
        {
            QDateTime starttime = fatherPtr->travelers[fatherPtr->currentTraveler].startTime;
            QDateTime departuredatetime = fatherPtr->travelers[fatherPtr->currentTraveler].getCityDepartureDateTime(path[index].from);
            QDateTime cityarrivaltime = fatherPtr->travelers[fatherPtr->currentTraveler].getCityArrivalDateTime(path[index].to);
            if (spenttime <= getSplitTime(starttime, departuredatetime))
            {
                nextCity2Arrive = path[index].from;
                state = -1;
                //qDebug() << "State: Stop" << index << departuredatetime.time().hour() << departuredatetime.time().minute();
                qDebug() << "State : Stop--next city to arrive is the city now at" << nextCity2Arrive;
                break;
            }
            else if (spenttime <=
                     getSplitTime(starttime, cityarrivaltime))
            {
                nextCity2Arrive = path[index].to;
                state = path[index].vehicle;
                qDebug() << "State: Run--next city to arrive is the city on the other side of current path" << nextCity2Arrive;
                break;
            }
        }
    return nextCity2Arrive;
}

//获得两时间点之间的时间差，判断当前所处的状态
QDateTime MapWidget::getSplitTime(QDateTime former, QDateTime later)
{
    int durationSec = (later.time().second() - former.time().second());
    int durationMin = (later.time().minute() - former.time().minute() - (int)((durationSec >= 0)?0:1));
    int durationHour = (later.time().hour() - former.time().hour() - (int)((durationMin >= 0)?0:1));
    int durationDay = (later.date().day() - former.date().day() - (int)((durationHour >= 0)?0:1) + former.date().daysInMonth())
            % former.date().daysInMonth();
    durationSec = (durationSec + 60) % 60;
    durationMin = (durationMin + 60) % 60;
    durationHour = (durationHour + 24) % 24;

    return QDateTime(QDate(1, 1, durationDay+1), QTime(durationHour, durationMin, durationSec, 999));
}

//获得图形中各个城市的位置
QPointF MapWidget::getCityCor(int city)
{
    int x, y;
    switch (city)
    {
    case 0:
        x = 466 - 24;
        y = 150 - 24;
        break;
    case 1:
        x = 722 - 24;
        y = 393 - 24;
        break;
    case 2:
        x = 281 -24;
        y = 240 -24;
        break;
    case 3:
        x = 549 - 24;
        y = 316 - 24;
        break;
    case 4:
        x = 494 - 24;
        y = 474 - 24;
        break;
    case 5:
        x = 385 - 24;
        y = 316 - 24;
        break;
    case 6:
        x = 385 - 24;
        y = 671 - 24;
        break;
    case 7:
        x = 58 - 24;
        y = 363 - 24;
        break;
    case 8:
        x = 880 - 24;
        y = 500 - 24;
        break;
    case 9:
        x = 832 - 24;
        y = 212 - 24;
        break;
    case 10:
        x = 750 - 24;
        y = 57 - 24;
        break;
    case 11:
        x = 86 - 24;
        y = 80 - 24;
    }

    return QPointF(x, y);
}

///获得两个时间段的时间差，用于计算坐标增量
double MapWidget::getTimeDifference(QDateTime former, QDateTime later)
{

    int durationSec = (later.time().second() - former.time().second());
    int durationMin = (later.time().minute() - former.time().minute() - (int)((durationSec >= 0)?0:1));
    int durationHour = (later.time().hour() - former.time().hour() - (int)((durationMin >= 0)?0:1));
    int durationDay = (later.date().day() - former.date().day() - (int)((durationHour >= 0)?0:1) + former.date().daysInMonth())
            % former.date().daysInMonth();
    durationSec = (durationSec + 60) % 60;
    durationMin = (durationMin + 60) % 60;
    durationHour = (durationHour + 24) % 24;

    return (double)(durationDay * 86400 + durationHour * 3600 + durationMin * 60 + durationSec);
}

//计算坐标增量
QPointF MapWidget::getMoveDistance(QDateTime spentTime, QDateTime start2Begin, QDateTime start2End,
                                   int from, int to)
{
    double increaseRatio = getTimeDifference(start2Begin, spentTime)/getTimeDifference(start2Begin, start2End);
    double xIncrease = (getCityCor(to) - getCityCor(from)).x() * increaseRatio;
    double yIncrease = (getCityCor(to) - getCityCor(from)).y() * increaseRatio;

    return QPointF(xIncrease, yIncrease);
}
