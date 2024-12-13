#ifndef FUELCAR_H
#define FUELCAR_H
#include <iostream>
#include "BaseCar.h"

using namespace std;

class FuelCar : public BaseCar {
private:
    string fuelType;
    double tankCapacity;

public:
    // Default constructor
    FuelCar();

    // constructor with parameters
    FuelCar(int carID, const string& model, const string& make, int year, double pricePerDay,
            int capacity, const string& color, const string& fuelType, double tankCapacity);

    // Getters and setters
    string getFuelType() const;
    void setFuelType(const string& fuelType);
    double getTankCapacity() const;
    void setTankCapacity(double tankCapacity);

    // Overridden methods
    string getType() const override;
    void serialize(ostream& out) const override;
    void deserialize(istream& in) override;
    void display() const override;
    bool isRented() const override;
    void setRented(bool status) override;

};

#endif
