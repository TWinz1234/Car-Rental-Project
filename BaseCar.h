#ifndef BASECAR_H
#define BASECAR_H
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <memory>
using namespace std;

class BaseCar
{
public:
    BaseCar();
    BaseCar(int, string, string, int, double, int, string);
    int getCarID() const;
    void setCarID(int);
    string getModel() const;
    void setModel(string);
    string getMake() const;
    void setMake(string);
    int getYear() const;
    void setYear(int);
    double getPricePerDay() const;
    void setPricePerDay(double);
    int getCapacity() const;
    void setCapacity(int);
    string getColor() const;
    void setColor(string);
    virtual string getType() const;
    virtual void display() const;
    virtual void serialize(std::ostream& out) const;
    virtual void deserialize(std::istream& in);
    static void saveToFile(string fileName, const vector<shared_ptr<BaseCar>> cars);
    static vector<shared_ptr<BaseCar>> readFromFile(const string& fileName);


    // static add car function

    // use protected for proper inheritance
protected:
    int carID;
    string model;
    string make;
    int year;
    double pricePerDay;
    int capacity;
    string color;

};

#endif