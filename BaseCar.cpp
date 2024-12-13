#include "BaseCar.h"
#include "ElectricCar.h"
#include "FuelCar.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// Timmy - I just expanded on your constructors since we added more


// default constructor
BaseCar::BaseCar() {}

// paramater constructor
BaseCar::BaseCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color, bool rented)
    : carID(carID), model(model), make(make), year(year), pricePerDay(pricePerDay), capacity(capacity), color(color), rented(rented) {
    setCarID(carID);
    setModel(model);
    setMake(make);
    setYear(year);
    setPricePerDay(pricePerDay);
    setCapacity(capacity);
    setColor(color);

}
// Super class of Car, so we'll have a lot more data here
// Setter & getter functions
int BaseCar::getCarID() const { return carID; }
void BaseCar::setCarID(int newCarID) { this->carID = newCarID; }

string BaseCar::getModel() const { return model; }
void BaseCar::setModel(string newModel) { this->model = newModel; }

string BaseCar::getMake() const { return make; }
void BaseCar::setMake(string newMake) { this->make = newMake; }

int BaseCar::getYear() const { return year; }
void BaseCar::setYear(int newYear) { this->year = newYear; }

double BaseCar::getPricePerDay() const { return pricePerDay; }
void BaseCar::setPricePerDay(double newPricePerDay) { this->pricePerDay = newPricePerDay; }

int BaseCar::getCapacity() const { return capacity; }
void BaseCar::setCapacity(int newCapacity) { this->capacity = newCapacity; }

string BaseCar::getColor() const { return color; }
void BaseCar::setColor(string newColor) { this->color = newColor; }

string BaseCar::getType() const { return "base"; }

// Serialize/deserialize -> I looked this up and it said we need to do this to avoid the errors from adding to the list
// ostream = out -> write to file, istream = in => input from file
void BaseCar::serialize(std::ostream& out) const {
    out << carID << " " << model << " " << make << " " << year << " " << pricePerDay << " " << capacity << " " << color << " ";
}

// use this to display from file
void BaseCar::deserialize(std::istream& in) {
    in >> carID >> model >> make >> year >> pricePerDay >> capacity >> color;
}

// use boolean value if the car is rented
bool BaseCar::isRented() const {
    return rented;
}

// set the value if it's rented
void BaseCar::setRented(bool status) {
    rented = status;
}


// Read/write from the file
// use a vector so the function can grow -> the inventory list isn't defined for us
void BaseCar::saveToFile(string fileName, const vector<shared_ptr<BaseCar>> cars) {
    ofstream outfile(fileName);
    if (!outfile) {
        cerr << "Error: Unable to open file for writing: " << fileName << endl;
        return;
    }
    for (const auto& car : cars) {
        outfile << car->getType() << " ";
        car->serialize(outfile);
        outfile << "\n";
    }
    outfile.close();
    cout << "Car inventory saved to file: " << fileName << endl;
}

// Reads car inventory from a file, creates the subclass object(ElectricCar or FuelCar) based on the type of car in the file, and returns a vector of shared_ptr<BaseCar>
vector<shared_ptr<BaseCar>> BaseCar::readFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file) {
        cout << "File not found. Creating a new file: " << fileName << "\n";
        ofstream outFile(fileName); // Create an empty file if the file isn't found -> we might need this in class
        outFile.close();
        return {};
    }

    vector<shared_ptr<BaseCar>> cars;
    string type;

    while (!file.eof()) {
        string line;
        getline(file, line);
        if (line.empty()) continue;

        istringstream iss(line);
        iss >> type;

        shared_ptr<BaseCar> car;
        if (type == "electric") {
            car = make_shared<ElectricCar>();
        } else if (type == "fuel") {
            car = make_shared<FuelCar>();
        } else {
            cerr << "Unknown car type found: " << type << "\n";
            continue;
        }

        car->deserialize(iss);
        cars.push_back(car);
    }

    return cars;
}

// display the common car components -> super class attributes
void BaseCar::display() const {
    cout << "Car ID: " << carID << ", Model: " << model
         << ", Make: " << make << ", Year: " << year
         << ", Price Per Day: $" << pricePerDay
         << ", Capacity: " << capacity
         << ", Color: " << color
         << ", Rented: " << (rented ? "Yes" : "No") << endl;
}


