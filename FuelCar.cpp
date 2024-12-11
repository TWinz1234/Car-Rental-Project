#include "FuelCar.h"
#include <iostream>

using namespace std;

// Default constructor
FuelCar::FuelCar() : BaseCar(), fuelType(""), tankCapacity(0.0) {}

// constructor with paramters
FuelCar::FuelCar(int carID, const string& model, const string& make, int year, double pricePerDay,
                 int capacity, const string& color, const string& fuelType, double tankCapacity)
    : BaseCar(carID, model, make, year, pricePerDay, capacity, color), fuelType(fuelType), tankCapacity(tankCapacity) {}

// Getters and setters
string FuelCar::getFuelType() const {
    return fuelType;
}

void FuelCar::setFuelType(const string& fuelType) {
    this->fuelType = fuelType;
}

double FuelCar::getTankCapacity() const {
    return tankCapacity;
}

void FuelCar::setTankCapacity(double tankCapacity) {
    this->tankCapacity = tankCapacity;
}

// Overridden methods
string FuelCar::getType() const {
    return "Fuel";
}

void FuelCar::serialize(ostream& out) const {
    BaseCar::serialize(out);
    out << fuelType << " " << tankCapacity << " ";
}

void FuelCar::deserialize(istream& in) {
    BaseCar::deserialize(in);
    in >> fuelType >> tankCapacity;
}

void FuelCar::display() const {
    BaseCar::display();
    cout << "Fuel Type: " << fuelType << ", Tank Capacity: " << tankCapacity << " liters" << endl;
}
