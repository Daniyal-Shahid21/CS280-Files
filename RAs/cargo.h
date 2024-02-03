#ifndef CARGO_H
#define CARGO_H

#include "ship.h"

class Cargo : public Ship {
private:
    int cargoCapacity;

public:
    Cargo();
    Cargo(std::string name, int year);

    int getCapacity() const;
    void setCapacity(int capacity);

    void print() const override;
};

#endif // CARGO_H