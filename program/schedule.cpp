#include "schedule.h"
#include "log.h"
std::multimap<int, Attribute> Schedule::database;

Schedule::Schedule()
{
    QFile file(":/database.txt");
    if(!file.open(QIODevice::ReadOnly))
    {
        qDebug() << "Could not open the file by reading";
        return;
    }

    QTextStream in(&file);
    QString from, to, number, begin, end, cost, vechile; //分别为出发地、目的地、班次、开始时间、结束时间、费用、交通方式
    while(!in.atEnd())
    {
        in >> from >> to >> number >> begin >> end >> cost >> vechile >> endl;
        if(from != "")
        {
            qDebug() << from << to << number << begin;
            Attribute line(CityToNum(from), CityToNum(to), number, QTime::fromString(begin),
                           QTime::fromString(end), cost.toInt(), vechile.toInt());
            database.insert(std::make_pair(CityToNum(from), line));
        }
    }
    qDebug() << "input success...";
}

int Schedule::CityToNum(QString city)
{
    int num = -1;

    if(city == "Beijing")
        num = 0;
    else if(city == "Shanghai")
        num = 1;
    else if(city == "Xi'an")
        num = 2;
    else if(city == "Wuhan")
        num = 3;
    else if(city == "Shenzhen")
        num = 4;
    else if(city == "Zhengzhou")
        num = 5;
    else if(city == "Haikou")
        num = 6;
    else if(city == "Lasa")
        num = 7;
    else if(city == "Tokyo")
        num = 8;
    else if(city == "Seoul")
        num = 9;
    else if(city == "Haerbin")
        num = 10;
    else if(city == "Moscow")
        num = 11;

    return num;
}
