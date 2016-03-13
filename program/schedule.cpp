#include "schedule.h"

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
    else if(city == "Hainan")
        num = 6;
    else if(city == "Lasa")
        num = 7;
    else if(city == "NewYork")
        num = 8;
    else if(city == "Seoul")
        num = 9;
    else if(city == "Haerbin")
        num = 10;
    else if(city == "Moscow")
        num = 11;

    return num;
}

std::vector<Attribute> Schedule::Dijkstra(QTime startTime, int strategy, int origin, int destination)
{
    std::vector<int> value(11, INT_MAX);
    std::vector<bool> known(11, false);
    std::vector<Attribute> path(11);

    QTime currentTime = startTime;
    known[origin] = true;
    value[origin] = 0;
    int city = origin;
    while(1)
    {
        UpdateAdjacents(city, value, known, path, currentTime);
        qDebug() << "update success...";
        int min = INT_MAX;
        city = -1;
        for(std::vector<int>::size_type ix = 0;
            ix != value.size(); ix++)
        {
            if(!known[ix] && min > value[ix])
            {
                min = value[ix];
                city = ix;
                qDebug() << city;
            }
        }
        if(city == -1)
            break;

        known[city] = true;
    }
    qDebug() << "loop finish...";
    std::vector<Attribute> plan;
    MakePlan(plan, path, destination, origin);
    qDebug() << "makeplan finish...";
    return plan;
}

void Schedule::MakePlan(std::vector<Attribute>& plan, const std::vector<Attribute>& path,
                        int city, int origin)
{
    if(city != origin)
    {
        //qDebug() << path[city].from << path[city].num << path[city].to;
        MakePlan(plan, path, path[city].from, origin);
        plan.push_back(path[city]);
        qDebug() << path[city].from << path[city].num << path[city].to;
    }
}

void Schedule::UpdateAdjacents(int city, std::vector<int>& value, std::vector<bool>& known,
                               std::vector<Attribute>& path, QTime currentTime)
{
    typedef std::multimap<int, Attribute>::size_type sz_type;
    sz_type entries = database.count(city);

    std::multimap<int, Attribute>::iterator iter = database.find(city);
    for(sz_type cnt = 0; cnt != entries; cnt++, iter++)
    {
        if(!known[iter->second.to] && value[iter->second.to] > value[city] + iter->second.cost
                && currentTime <= iter->second.begin)
        {
            value[iter->second.to] = value[city] + iter->second.cost;
            path[iter->second.to] = iter->second;
        }
    }
}
