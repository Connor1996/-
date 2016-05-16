#include "traveler.h"
#include "log.h"

Traveler::Traveler(int id, QDateTime startTime, QDateTime deadlineTime, QDateTime systemStartTime, int strategy, int origin,
                   int destination, bool isChecked, std::vector<bool> throughCity) :
    isChecked(isChecked), id(id), strategy(strategy), origin(origin), destination(destination),
    startTime(startTime), deadlineTime(deadlineTime), systemStartTime(systemStartTime),
    throughCity(throughCity), time(12, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59))),
    min(0x7FFFFFFF), minTime(QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)))
{
    if(strategy == 2 || isChecked)
    {
        std::vector<QDateTime> tempTime(12, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)));
        std::vector<int> tempValue(12);
        std::vector<bool> known(12, false);  //标记每个点是否被访问过
        std::vector<Attribute> path;     //记录每个点的移动路径
        tempTime[origin] = startTime;

        DFS(origin, path, known, tempTime, tempValue);
    }
    else
        plan = Dijkstra();
    totalTime = TotalDateTime();
}

QDateTime Traveler::TotalDateTime()
{
    QDateTime endTime = time[destination];

    int durationMin = (endTime.time().minute() - startTime.time().minute());
    int durationHour = (endTime.time().hour() - startTime.time().hour() - (int)((durationMin >= 0)?0:1));
    int durationDay = (endTime.date().day() - startTime.date().day() - (int)((durationHour >= 0)?0:1) + startTime.date().daysInMonth())
            % startTime.date().daysInMonth();
    durationMin = (durationMin + 60) % 60;
    durationHour = (durationHour + 24) % 24;

    return QDateTime(QDate(1, 1, durationDay+1), QTime(durationHour, durationMin, 0));
}

std::vector<Attribute> Traveler::getPlan()
{
    return this->plan;
}

std::vector<Attribute> Traveler::changePlan(int city, int strategy, int destination, QDateTime deadlineTime,
                                            bool isChecked, std::vector<bool> throughCity)
{
    //对旅客信息进行更改
    qDebug() << "in changePlan";
    std::vector<bool> known(12, false);  //标记每个点是否被访问过
    std::vector<Attribute> oldPlan = plan;
    //std::vector<QDateTime> oldTime = time;
    for(std::vector<Attribute>::iterator iter = oldPlan.begin(); iter != oldPlan.end(); iter++)
    {
        known[iter->from] = true;
        throughCity[iter->from] = false;

        if (iter->to == city)
        {
            startTime = time[iter->to];
            oldPlan.erase(++iter, oldPlan.end());
            break;
        }
    }
    plan.clear();
    this->origin = city;
    this->strategy = strategy;
    this->destination = destination;
    this->deadlineTime = deadlineTime;
    this->isChecked = isChecked;
    this->throughCity = throughCity;


    if(strategy == 2 || isChecked)
    {
        std::vector<QDateTime> tempTime(12, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)));
        std::vector<int> tempValue(12);
        std::vector<Attribute> path;     //记录每个点的移动路径
        tempTime[origin] = startTime;

        DFS(origin, path, known, tempTime, tempValue);
    }
    else
        plan = Dijkstra();
    totalTime = TotalDateTime();

    oldPlan.insert(oldPlan.end(), plan.begin(), plan.end());
    return oldPlan;
}

QDateTime Traveler::getCityArrivalDateTime(int index)
{
    return time[index];
}

QDateTime Traveler::getCityDepartureDateTime(int index)
{
    std::vector<Attribute>::size_type id = 0;
    QTime tempTime;

    for(; id != plan.size(); id++)
        if(plan[id].from == index)
        {
            tempTime = plan[id].begin; //获得当前城市的出发时间
            break;
        }

    QDateTime DepartureDateTime = time[index];
    if(DepartureDateTime.time() <= tempTime)
        return QDateTime(DepartureDateTime.date(), tempTime);
    else
        return QDateTime(DepartureDateTime.date().addDays(1), tempTime);
}


void Traveler::DFS(int city, std::vector<Attribute>& path, std::vector<bool>& known,
                   std::vector<QDateTime>& tempTime, std::vector<int>& tempValue)
{
    if (strategy == 2 && (tempTime[city] > deadlineTime || tempValue[city] > min)) //总时间大于截至时间，不满足约束条件
        return;
    if (strategy == 1 && tempTime[city] > minTime)
        return;
    if (strategy == 0 && tempValue[city] > min)
        return;

    known[city] = true; //标记此城市已访问过

    if (city == destination)
    {
        int ok = true;
        std::vector<bool> mark = throughCity;

        for (std::vector<Attribute>::size_type ix = 0; ix != path.size(); ix++) //将路径上的所有城市取消标志
                mark[path[ix].to] = false;
        mark[origin] = false;

        if (isChecked)
        {
            for (std::vector<bool>::size_type ix = 0; ix != mark.size(); ix++) //若必经城市还有点未取消标志，所有有城市未经过
            {
                if (mark[ix] == true)
                {
                    ok = false;
                    break;
                }
            }
        }
        if(strategy != 1 && tempValue[city] < min && ok) //若满足约束条件，则更新最小值并记录路径
        {
            min = tempValue[city];
            time = tempTime;
            plan = path;
        }
        else if (strategy == 1 && tempTime[city] < minTime && ok)
        {
            minTime = tempTime[city];
            time = tempTime;
            plan = path;
        }
    }
    else
    {
        typedef std::multimap<int, Attribute>::size_type sz_type;
        sz_type entries = Schedule::database.count(city);

        std::multimap<int, Attribute>::iterator iter = Schedule::database.find(city);
        std::multimap<int, Attribute>::iterator min = iter;
        bool start = true;
        for(sz_type cnt = 0; cnt != entries; cnt++, iter++)
        {
            if (known[iter->second.to] == true) //如果去往城市已经访问过，则忽略该路径
            {
                if (start)
                    min++;
                continue;
            }
            start = false;
            if (strategy != 2)
            {
                if (iter->second.to != min->second.to)
                {
                    path.push_back(min->second);

                    tempTime[min->second.to] = CalculateTime(min, tempTime);
                    tempValue[min->second.to] = tempValue[city] + min->second.cost;

                    DFS(min->second.to, path, known, tempTime, tempValue);

                    known[min->second.to] = false;
                    path.erase(path.end());

                    //min更新为新的城市
                    //priCity = iter->second.to;
                    min = iter;
                }
                else
                {
                    if (strategy == 0 && iter->second.cost < min->second.cost)
                        min = iter;
                    if (strategy == 1 && CalculateTime(iter, tempTime) < CalculateTime(min, tempTime))
                        min = iter;
                }
            }
            else
            {
                path.push_back(iter->second);

                //更新时间和花费
                tempTime[iter->second.to] = CalculateTime(iter, tempTime);
                tempValue[iter->second.to] = tempValue[city] + iter->second.cost;

                DFS(iter->second.to, path, known, tempTime, tempValue);

                known[iter->second.to] = false;
                path.erase(path.end());
            }
        }
        //循环结束后还需要处理一次min
        if (strategy != 2)
        {
            path.push_back(min->second);

            tempTime[min->second.to] = CalculateTime(min, tempTime);
            tempValue[min->second.to] = tempValue[city] + min->second.cost;

            DFS(min->second.to, path, known, tempTime, tempValue);

            known[min->second.to] = false;
            path.erase(path.end());
        }
    }
}

QDateTime Traveler::CalculateTime(const std::multimap<int, Attribute>::iterator& iter,
                                  std::vector<QDateTime>& tempTime) //计算时间
{
    QDateTime temp;

    //判断是否时间跨天
    bool span;
    if(iter->second.begin <= iter->second.end)
        span = false;
    else
        span = true;

    if(!span && tempTime[iter->second.from].time() <= iter->second.begin)
        temp = QDateTime(tempTime[iter->second.from].date(), iter->second.end);
    else if(!span && tempTime[iter->second.from].time() > iter->second.begin)
        temp = QDateTime(tempTime[iter->second.from].date().addDays(1), iter->second.end);
    else if(span && tempTime[iter->second.from].time() <= iter->second.begin)
        temp = QDateTime(tempTime[iter->second.from].date().addDays(1), iter->second.end);
    else if(span && tempTime[iter->second.from].time() > iter->second.begin)
        temp = QDateTime(tempTime[iter->second.from].date().addDays(2), iter->second.end);

    return temp;
}

std::vector<Attribute> Traveler::Dijkstra()
{
    std::vector<int> value(12, INT_MAX); //记录原点到每个点的权值之和
    std::vector<bool> known(12, false);  //标记每个点是否被访问过
    std::vector<Attribute> path(12);     //记录每个点的移动路径

    QDateTime currentTime = startTime;
    time[origin] = currentTime;
    known[origin] = true;
    value[origin] = 0;
    int city = origin;
    while(1)
    {
        UpdateAdjacents(city, value, known, path);
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
                    //qDebug() << city;
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
                    //qDebug() << city;
                }
            }
        }

        if(city == -1)
            break;

        known[city] = true;
    }
    qDebug() << "loop finish...";
    std::vector<Attribute> plan;
    MakePlan(destination, path, plan);
    qDebug() << "makeplan finish...";

    return plan;
}

void Traveler::MakePlan(int city, const std::vector<Attribute>& path, std::vector<Attribute> &plan)
{
    if(path[city].from == -1)
        return;
    if(city != origin)
    {
        MakePlan(path[city].from, path, plan);
        plan.push_back(path[city]);
        qDebug() << path[city].from << path[city].num << path[city].to;
    }
}

void Traveler::UpdateAdjacents(int city, std::vector<int>& value, std::vector<bool>& known, std::vector<Attribute>& path)
{
    typedef std::multimap<int, Attribute>::size_type sz_type;
    sz_type entries = Schedule::database.count(city);

    std::multimap<int, Attribute>::iterator iter = Schedule::database.find(city);
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
                //更新
                if(!span && time[iter->second.from].time() <= iter->second.begin)
                    time[iter->second.to] = QDateTime(time[iter->second.from].date(), iter->second.end);
                else if(!span && time[iter->second.from].time() > iter->second.begin)
                    time[iter->second.to] = QDateTime(time[iter->second.from].date().addDays(1), iter->second.end);
                else if(span && time[iter->second.from].time() <= iter->second.begin)
                    time[iter->second.to] = QDateTime(time[iter->second.from].date().addDays(1), iter->second.end);
                else if(span && time[iter->second.from].time() > iter->second.begin)
                    time[iter->second.to] = QDateTime(time[iter->second.from].date().addDays(2), iter->second.end);
            }
        }
        else if(strategy == 1)
        {
            //策略二:时间最短
            if(!known[iter->second.to])
            {
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
}

