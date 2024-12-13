
#ifndef BASECAR_H
#define BASECAR_H
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

class BaseCar
{
public:
    BaseCar();
    BaseCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color, bool rented = false);
    // sets & getters
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

    // use virtual functions for electric and fuel cars -> enable polymorphism 
    virtual string getType() const;
    virtual void display() const;
    virtual void serialize(ostream& out) const;
    virtual void deserialize(istream& in);
    static void saveToFile(string fileName, const vector<shared_ptr<BaseCar>> cars);
    static vector<shared_ptr<BaseCar>> readFromFile(const string& fileName);
    virtual bool isRented() const;
    virtual void setRented(bool status);


    // use protected for proper inheritance -> allow electric & fuel car to have access
protected:
    int carID;
    string model;
    string make;
    int year;
    double pricePerDay;
    int capacity;
    string color;
    bool rented;


};

#endif
