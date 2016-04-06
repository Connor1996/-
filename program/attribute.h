#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QTime>

class Attribute
{
public:
    Attribute();
    Attribute(int, int, QString, QTime, QTime, int, int);

    int from, to, cost, vehicle;
    QString num;
    QTime begin, end;

};

#endif // ATTRIBUTE_H
