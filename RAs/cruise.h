#ifndef CRUISE_H
#define CRUISE_H

#include "ship.h"

class Cruise : public Ship {
private:
    int maxPassengers;

public:
    Cruise();
    Cruise(std::string name, int year);

    int getmaxPassengers() const;
    void setmaxPassengers(int passengers);

    void print() const override;
};

#endif // CRUISE_H