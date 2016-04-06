#include "attribute.h"
#include "log.h"

Attribute::Attribute()
{
    this->from = -1;
}

Attribute::Attribute(int from, int to, QString num, QTime begin, QTime end, int cost, int vehicle)
{
    this->from = from;
    this->to = to;
    this->num = num;
    this->begin = begin;
    this->end = end;
    this->cost = cost;
    this->vehicle = vehicle;
}



