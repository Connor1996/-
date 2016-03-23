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

    Point *label = new Point(this);
    label->setPixmap(QPixmap(":/point.png"));
    label->setGeometry(0, 0, 120, 120);
    label->setScaledContents(true);


    QStateMachine *machine = new QStateMachine;     //新建状态机

    QState *state1 = new QState(machine);     //状态
    state1->assignProperty(label, "geometry",QRect(0,0,80,80));    //绑定button的geomertry属性
    QState *state2 = new QState(machine);
    state2->assignProperty(label,"geometry",QRect(400,400,80,80));
    machine->setInitialState(state1);     //state1设为初始化状态


    QPropertyAnimation *ani=new QPropertyAnimation(label,"geometry");
    ani->setDuration(2000);
    ani->setStartValue(QRect(100, 100, 120, 120));
    ani->setEndValue(QRect(250, 250, 120, 120));
    ani->setEasingCurve(QEasingCurve::OutBounce);   //动画效果—弹跳
    ani->start();

    QSignalTransition *transition1=state1->addTransition(label,SIGNAL(arrival()),state2);//动画触发信号
    transition1->addAnimation(ani);
    QSignalTransition *transition2=state2->addTransition(label,SIGNAL(arrival()),state1);
    transition2->addAnimation(ani);

    //machine->addDefaultAnimation(ani);
    machine->start();     //开启状态机

}

