#ifndef TRAVELER_H
#define TRAVELER_H

#include <vector>
#include "attribute.h"

class Traveler
{
public:
    Traveler(int, std::vector<Attribute>);

private:
    int id;
    std::vector<Attribute> plan;
};

#endif // TRAVELER_H
