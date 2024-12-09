#include "ElectricCar.h"

// Constructors
ElectricCar::ElectricCar()
{
    
}

ElectricCar::ElectricCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color, int rangePerCharge) :
BaseCar(carID, model, make, year, pricePerDay, capacity, color)
{
    setRangePerCharge(rangePerCharge);
}

// Getter and setter functions
int ElectricCar::getRangePerCharge() const
{
    return rangePerCharge;
}

void ElectricCar::setRangePerCharge(int newRangePerCharge)
{
    this->rangePerCharge = newRangePerCharge;
}

string ElectricCar::getType() const
{
    return "electric";
}

// Serialize/deserialize
void ElectricCar::serialize(ostream& out) const 
{
    BaseCar::serialize(out);
    out << rangePerCharge << " ";
}

void ElectricCar::deserialize(std::istream& in)
{
    BaseCar::deserialize(in);
    in >> rangePerCharge;
}