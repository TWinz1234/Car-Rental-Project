#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H
#include <iostream>

#include "BaseCar.h"

using namespace std;

class ElectricCar : public BaseCar {
private:
    double batteryCapacity;   
    int rangePerCharge;      

public:
    // Constructors
    ElectricCar();
    ElectricCar(int carID, const string& model, const string& make, int year, double pricePerDay,
                int capacity, const string& color, double batteryCapacity, int rangePerCharge);

    // Getters and setters
    double getBatteryCapacity() const;
    void setBatteryCapacity(double batteryCapacity);
    int getRangePerCharge() const;
    void setRangePerCharge(int rangePerCharge);

    // Overridden methods
    string getType() const override;
    void serialize(ostream& out) const override;
    void deserialize(istream& in) override;
    void display() const override;

    bool isRented() const override;
    void setRented(bool status) override;

};

#endif
