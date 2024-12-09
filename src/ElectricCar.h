#ifndef ELECTRICCAR_H
#define ELECTRICCAR_H
#include "BaseCar.h"

class ElectricCar: public BaseCar 
{
    public:
    ElectricCar();
    ElectricCar(int, string, string, int, double, int, string, int);
    int getRangePerCharge() const;
    void setRangePerCharge(int);
    string getType() const override;
    void serialize(ostream& out) const override;
    void deserialize(std::istream& in) override;

    private:
    int rangePerCharge;
};

#endif