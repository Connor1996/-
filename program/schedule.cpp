#include "schedule.h"

Schedule::Schedule()
{
    QFile file("database.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);

    QTextStream in(&file);
    QString from, to, number, begin, end, cost, vechile; //分别为出发地、目的地、班次、开始时间、结束时间、费用
    while(!in.atEnd())
    {
        in >> from >> to >> number >> begin >> end >> cost >> vechile;
        Attribute line(CityToNum(from), CityToNum(to), number, QDate::fromString(begin),
                       QDate::fromString(end), cost.toInt(), vechile.toInt());
        database.insert(std::make_pair(CityToNum(from), line));
    }
}

int CityToNum(QString city)
{
    int num;

    if(city == "北京")
        num = 0;
    else if(city =="上海")
        num = 1;
    else if(city =="西安")
        num = 2;
    else if(city =="武汉")
        num = 3;
    else if(city =="深圳")
        num = 4;
    else if(city =="郑州")
        num = 5;
    else if(city =="海南")
        num = 6;
    else if(city =="拉萨")
        num = 7;
    else if(city =="纽约")
        num = 8;
    else if(city =="首尔")
        num = 9;
    else if(city =="哈尔滨")
        num = 10;
    else if(city =="莫斯科")
        num = 11;

    return num;
}

std::vector<Attribute> Schedule::Dijkstra(int strategy, int origin, int destination)
{
    std::vector<int> value(11, INT_MAX);
    std::vector<bool> known(11, false);
    std::vector<Attribute> path;

    known[origin] = true;
    value[origin] = 0;
    int city = origin;
    while(1)
    {
        UpdateAdjacents(city, value, known, path);

        city = INT_MAX;
        for(std::vector<int>::iterator iter = value.begin();
            iter != value.end(); iter++)
        {
            if(!known[*iter])
                city = std::min(city, *iter);
        }
        if(city == -1)
            break;

        known[city] = true;
    }

    return path;
}

void Schedule::UpdateAdjacents(int city, std::vector<int>& value, std::vector<bool>& known,
                               std::vector<Attribute>& path)
{
    typedef std::multimap<int, Attribute>::size_type sz_type;
    sz_type entries = database.count(city);

    std::multimap<int, Attribute>::iterator iter = database.find(city);
    for(sz_type cnt = 0; cnt != entries; cnt++, iter++)
    {
        if(!known[iter->second.to] && value[iter->second.to] > value[city] + iter->second.cost)
        {
            value[iter->second.to] = value[city] + iter->second.cost;
            path[iter->second.to] = iter->second;
        }
    }
}
