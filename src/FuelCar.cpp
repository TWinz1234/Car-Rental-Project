#include "FuelCar.h"

// Constructors
FuelCar::FuelCar()
{
    
}

FuelCar::FuelCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color, int milesPerGallon) : 
BaseCar(carID, model, make, year, pricePerDay, capacity, color)
{
    setMilesPerGallon(milesPerGallon);
}

// Getter and setter functions
int FuelCar::getMilesPerGallon() const
{
    return milesPerGallon;
}

void FuelCar::setMilesPerGallon(int newMilesPerGallon)
{
    this->milesPerGallon = newMilesPerGallon;
}
//todo put type in const
string FuelCar::getType() const
{
    return "fuel";
}

// Serialize/deserialize
void FuelCar::serialize(ostream& out) const 
{
    BaseCar::serialize(out);
    out << milesPerGallon << " ";
}

void FuelCar::deserialize(std::istream& in)
{
    BaseCar::deserialize(in);
    in >> milesPerGallon;
}