#ifndef FUELCAR_H
#define FUELCAR_H
#include "BaseCar.h"

class FuelCar: public BaseCar 
{
    public:
    FuelCar();
    FuelCar(int, string, string, int, double, int, string, int);
    int getMilesPerGallon() const;
    void setMilesPerGallon(int);
    string getType() const override;
    void serialize(ostream& out) const override;
    void deserialize(std::istream& in) override;

    private:
    int milesPerGallon;
};
 
#endif