#include "ElectricCar.h"
#include <iostream>

using namespace std;

// Default constructor
ElectricCar::ElectricCar() : BaseCar(), batteryCapacity(0), rangePerCharge(0) {}

// Parameterized constructor
ElectricCar::ElectricCar(int carID, const string& model, const string& make, int year, double pricePerDay,
                         int capacity, const string& color, double batteryCapacity, int rangePerCharge)
    : BaseCar(carID, model, make, year, pricePerDay, capacity, color), batteryCapacity(batteryCapacity), rangePerCharge(rangePerCharge) {}

// Getters
double ElectricCar::getBatteryCapacity() const {
    return batteryCapacity;
}

int ElectricCar::getRangePerCharge() const {
    return rangePerCharge;
}

// Setters
void ElectricCar::setBatteryCapacity(double batteryCapacity) {
    this->batteryCapacity = batteryCapacity;
}

void ElectricCar::setRangePerCharge(int rangePerCharge) {
    this->rangePerCharge = rangePerCharge;
}

// Overridden methods
string ElectricCar::getType() const {
    return "Electric";
}

void ElectricCar::serialize(ostream& out) const {
    BaseCar::serialize(out);
    out << batteryCapacity << " " << rangePerCharge << " ";
}

void ElectricCar::deserialize(istream& in) {
    BaseCar::deserialize(in);
    in >> batteryCapacity >> rangePerCharge;
}

void ElectricCar::display() const {
    BaseCar::display(); // Display common attributes
    cout << "Battery Capacity: " << batteryCapacity << " kWh, Range: " << rangePerCharge << " miles" << endl;
}


bool ElectricCar::isRented() const {
    return BaseCar::isRented();
}

void ElectricCar::setRented(bool status) {
    BaseCar::setRented(status);
}

