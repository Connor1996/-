#include "mapwidget.h"
#include <QApplication>
#include <QStateMachine>
#include <QPushButton>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QPainter>
#include <QState>
#include <QLabel>

MapWidget::MapWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setAutoFillBackground(true);
    QPalette palette = this->palette();
    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/map.jpg")));
    this->setPalette(palette);

//    Point *label = new Point(this);
//    label->setPixmap(QPixmap(":/point.png"));
//    label->setGeometry(0, 0, 120, 120);
//    label->setScaledContents(true);


//    QStateMachine *machine = new QStateMachine;     //新建状态机

//    QState *state1 = new QState(machine);     //状态
//    state1->assignProperty(label, "geometry",QRect(0,0,80,80));    //绑定button的geomertry属性
//    QState *state2 = new QState(machine);
//    state2->assignProperty(label,"geometry",QRect(400,400,80,80));
//    machine->setInitialState(state1);     //state1设为初始化状态


//    QPropertyAnimation *ani=new QPropertyAnimation(label,"geometry");
//    ani->setDuration(2000);
//    ani->setStartValue(QRect(100, 100, 120, 120));
//    ani->setEndValue(QRect(250, 250, 120, 120));
//    ani->setEasingCurve(QEasingCurve::OutBounce);   //动画效果—弹跳
//    ani->start();

//    QSignalTransition *transition1=state1->addTransition(label,SIGNAL(arrival()),state2);//动画触发信号
//    transition1->addAnimation(ani);
//    QSignalTransition *transition2=state2->addTransition(label,SIGNAL(arrival()),state1);
//    transition2->addAnimation(ani);

//    //machine->addDefaultAnimation(ani);
//    machine->start();     //开启状态机

}

void MapWidget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    qDebug() << "99";
    Widget *fatherPtr = (Widget *)parentWidget();
    if (fatherPtr->currentTraveler != -1)
    {
        std::vector<Attribute> path = fatherPtr->travelers[fatherPtr->currentTraveler].getPlan();
        painter.drawPixmap((setPointPos(path, fatherPtr)), setPointGraph());
    }
    update();
}

QPixmap MapWidget::setPointGraph()
{
    QPixmap pointGraph(":/point.png");
    return pointGraph;
}

QPointF MapWidget::setPointPos(std::vector<Attribute> &path, QWidget *fatherPtr)
{
    QPointF pointPos;
    for (std::vector<Attribute>::size_type index = 0;
        index != path.size(); index++)
        {

    }

    return pointPos;
}

QDateTime MapWidget::getSplitTime(QDateTime former, QDateTime later)
{
    int formerYear, formerMonth, formerDay,
            formerHour, formerMin;
    int laterYear, laterMonth, laterDay,
            laterHour, laterMin;
    QDate formerDate = former.date();
    QTime formerTime = former.time();
    QDate laterDate = later.date();
    QTime laterTime = later.time();
    formerDate.getDate(&formerYear, &formerMonth, &formerDay);
    formerHour = formerTime.hour();
    formerMin = formerTime.minute();
    laterDate.getDate(&laterYear, &laterMonth, &laterDay);
    laterHour = laterTime.hour();
    laterMin = laterTime.minute();

    QDateTime splitDateTime;
    int splitYear, splitMonth, splitDay,
            splitHour, splitMin;
    splitYear = laterYear - formerYear;
    splitMonth = laterMonth - formerMonth;
    splitDay = laterDay - formerDay;
    splitHour = laterHour - formerHour;
    splitMin = laterMin - formerMin;

    if (splitMin < 0)
    {
        splitMin += 60;
        splitHour--;
    }
    if (splitHour < 0)
    {
        splitHour += 24;
        splitDay--;
    }
    if (splitDay < 0)
    {
        splitMonth--;
        switch (formerMonth)
        {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            splitDay += 31;
            break;
        case 4:
        case 6:
        case 9:
        case 11:
            splitDay += 30;
            break;
        case 2:
            if (formerYear % 4 == 0 || formerYear % 400 == 0)
                splitDay += 29;
            else
                splitDay += 28;
            break;
        }
    }
    if (splitMonth < 0)
    {
        splitMonth += 12;
        splitYear--;
    }
    QDate splitDate(splitYear, splitMonth, splitDay);
    QTime splitTime(splitHour, splitMin, 0, 0);
    splitDateTime.setDate(splitDate);
    splitDateTime.setTime(splitTime);
    return splitDateTime;
}

QPointF MapWidget::getCityCor(int city)
{
    QPointF coordinate;
    int x, y;
    switch (city)
    {
    case 0:
        x = 20;
        y = 20;
        break;
    case 1:
        x = 95;
        y = 20;
        break;
    case 2:
        x = 170;
        y = 20;
        break;
    case 3:
        x = 245;
        y = 20;
        break;
    case 4:
        x = 20;
        y = 95;
        break;
    case 5:
        x = 95;
        y = 95;
        break;
    case 6:
        x = 170;
        y = 95;
        break;
    case 7:
        x = 245;
        y = 95;
        break;
    case 8:
        x = 20;
        y = 170;
        break;
    case 9:
        x = 95;
        y = 170;
        break;
    case 10:
        x = 170;
        y = 170;
        break;
    case 11:
        x = 245;
        y = 170;
    }
    coordinate.setX(x);
    coordinate.setY(y);
    return coordinate;
}
