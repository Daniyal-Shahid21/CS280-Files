#ifndef SHIP_H
#define SHIP_H

#include <string>

class Ship {
protected:
    std::string shName;
    int shYear;
    shipType shType;  // Note: shipType is already declared in RA9Prog.cpp

public:
    Ship(std::string name, int year, shipType type);

    std::string getShName() const;
    void setShName(std::string name);

    int getShYear() const;
    void setShYear(int year);

    shipType getShType() const;

    virtual void print() const = 0;
};

#endif // SHIP_H