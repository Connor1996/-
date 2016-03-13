#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <QString>
#include <QDate>

class Attribute
{
public:
    Attribute();
    Attribute(int, int, QString, QDate, QDate, int, int);

    int from, to, cost, vehicle;
    QString num;
    QDate begin, end;

    QDate getDuration(int , int);
};

#endif // ATTRIBUTE_H
