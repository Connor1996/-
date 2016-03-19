#ifndef POINT_H
#define POINT_H

#include <QLabel>
#include <QWidget>
#include <QDebug>

class Point : public QLabel
{
    Q_OBJECT
public:
    Point(QWidget *parent = 0);

protected:
    void MoveEvent(QEvent * event);

signals:
    void arrival();
};

#endif // POINT_H
