#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QDate>

class Attribute
{
public:
    Attribute();
    Attribute(int, int, QString, QTime, QTime, int, int);

    int from, to, cost, vehicle;
    QString num;
    QTime begin, end;

    QTime getDuration(int , int);
};

#endif // ATTRIBUTE_H
