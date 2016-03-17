#include "schedule.h"

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

std::vector<Attribute> Schedule::Dijkstra(QDateTime startTime, int strategy, int origin,
                                          int destination, std::vector<QDateTime>& time)
{
    std::vector<int> value(12, INT_MAX);
    std::vector<bool> known(12, false);
    std::vector<Attribute> path(12);

    QDateTime currentTime = startTime;
    time[origin] = currentTime;
    known[origin] = true;
    value[origin] = 0;
    int city = origin;
    while(1)
    {
        UpdateAdjacents(city, value, time, known, path, strategy);
        qDebug() << "update success...";
        city = -1;

        if(strategy == 0)
        {
            int min = INT_MAX;

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
        }
        else if(strategy == 1)
        {
            QDateTime minn(QDate(7999, 12, 31), QTime(23, 59, 59));

            for(std::vector<QDateTime>::size_type ix = 0;
                ix != time.size(); ix++)
            {
                if(!known[ix] && minn > time[ix])
                {
                    minn = time[ix];
                    city = ix;
                    qDebug() << city;
                }
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
    //endTime = time[destination]
    return plan;
}

void Schedule::MakePlan(std::vector<Attribute>& plan, const std::vector<Attribute>& path,
                        int city, int origin)
{
    if(path[city].from == -1)
        return;
    if(city != origin)
    {
        MakePlan(plan, path, path[city].from, origin);
        plan.push_back(path[city]);
        qDebug() << path[city].from << path[city].num << path[city].to;
    }
}

void Schedule::UpdateAdjacents(int city, std::vector<int>& value, std::vector<QDateTime>& time, std::vector<bool>& known,
                               std::vector<Attribute>& path, int strategy)
{
    typedef std::multimap<int, Attribute>::size_type sz_type;
    sz_type entries = database.count(city);

    std::multimap<int, Attribute>::iterator iter = database.find(city);
    for(sz_type cnt = 0; cnt != entries; cnt++, iter++)
    {
        //判断是否时间跨天
        bool span;
        if(iter->second.begin <= iter->second.end)
            span = false;
        else
            span = true;

        if(strategy == 0)
        {
            //策略一:花费最少
            if(!known[iter->second.to] && value[iter->second.to] > value[city] + iter->second.cost)
            {
                value[iter->second.to] = value[city] + iter->second.cost;
                path[iter->second.to] = iter->second;
                time[iter->second.to].setTime(iter->second.end);
                if(span)
                    time[iter->second.to] = time[iter->second.to].addDays(1);
            }
        }
        else if(strategy == 1)
        {
            //策略二:时间最短
            if(!known[iter->second.to])
                //判断条件有四种情况：
                //第一种：行程不跨天，time[出发城市]的时间在行程出发时间之前，则用time[出发城市]的当天日期+行程到达时间与time[到达城市]比较
                //第二种：行程不跨天，time[出发城市]的时间在行程出发时间之后，则用time[出发城市]的下一天日期+行程到达时间与time[到达城市]比较
                //第三钟：行程跨天，time[出发城市]的时间在行程出发时间之前，则用time[出发城市]的下一天日期+行程到达时间与time[到达城市]比较
                //第四钟：行程跨天，time[出发城市]的时间在行程出发时间之后，则用time[出发城市]的后天日期+行程到达时间与time[到达城市]比较
                //若time[到底城市]，则更新值
                if(!span && time[iter->second.from].time() <= iter->second.begin &&
                        time[iter->second.to] > QDateTime(time[iter->second.from].date(), iter->second.end))
                {
                    time[iter->second.to] = QDateTime(time[iter->second.from].date(), iter->second.end);
                    path[iter->second.to] = iter->second;
                }
                else if(!span && time[iter->second.from].time() > iter->second.begin &&
                        time[iter->second.to] > QDateTime(time[iter->second.from].addDays(1).date(), iter->second.end))
                {
                    time[iter->second.to] = QDateTime(time[iter->second.from].addDays(1).date(), iter->second.end);
                    path[iter->second.to] = iter->second;
                }
                else if(span && time[iter->second.from].time() <= iter->second.begin &&
                        time[iter->second.to] > QDateTime(time[iter->second.from].addDays(1).date(), iter->second.end))
                {
                    time[iter->second.to] = QDateTime(time[iter->second.from].addDays(1).date(), iter->second.end);
                    path[iter->second.to] = iter->second;
                }
                else if(span && time[iter->second.from].time() > iter->second.begin &&
                        time[iter->second.to] > QDateTime(time[iter->second.from].addDays(2).date(), iter->second.end))
                {
                    time[iter->second.to] = QDateTime(time[iter->second.from].addDays(2).date(), iter->second.end);
                    path[iter->second.to] = iter->second;
                }
        }
    }
}
