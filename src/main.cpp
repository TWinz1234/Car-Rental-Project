#include <iostream>
#include "BaseCar.h"
#include "FuelCar.h"
#include "ElectricCar.h"

// function prototypes
void testCar();

int main()
{
    testCar();
    
    return 0;
}

void testCar()
{
    //BaseCar::BaseCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color)

    shared_ptr<BaseCar> bing = make_shared<ElectricCar>(1005, "Volt", "Chevy", 2017, 20.50, 4, "purple", 250);
    shared_ptr<BaseCar> boom = make_shared<FuelCar>(200, "Tahoe", "Chevy", 2020, 30.32, 5, "red", 17);
    
    /*bing->serialize(cout);
    cout << endl;
    boom->serialize(cout);
    cout << endl << endl;*/
    
    vector<shared_ptr<BaseCar>> myCars;
    myCars.push_back(bing);
    myCars.push_back(boom);
    
    string fileName = "CarInventory.txt";
    cout << "Saving to file: " << fileName << endl;
    BaseCar::saveToFile(fileName, myCars);
    
    cout << "Reading cars from file: " << fileName << endl;
    vector<shared_ptr<BaseCar>> myCars2 = BaseCar::readFromFile(fileName);
    cout << "mycars2 size is " << myCars2.size() << endl;
    
    int i = 0;
    for(const auto& car : myCars2)
    {
        cout << "Car index " << i++ << " Make: " << car->getMake() << " Model: " << car->getModel() << endl;
        //cout << typeid(*car).name() << endl;
    }
}