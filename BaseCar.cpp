#include "BaseCar.h"
#include "ElectricCar.h"
#include "FuelCar.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <memory>

using namespace std;

/* Timmy - I needed to add more to the constructors, I was getting intiation errors (the constructors just had primitive datatypes
 *
 */

// Constructors
BaseCar::BaseCar() {}

BaseCar::BaseCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color) {
    setCarID(carID);
    setModel(model);
    setMake(make);
    setYear(year);
    setPricePerDay(pricePerDay);
    setCapacity(capacity);
    setColor(color);
}

// Setter/getter functions
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

// Serialize/deserialize
// this is for formatting into the text files, I had to ChatGPT this part (I was having constant errors)
void BaseCar::serialize(std::ostream& out) const {
    out << carID << " " << model << " " << make << " " << year << " " << pricePerDay << " " << capacity << " " << color << " ";
}

void BaseCar::deserialize(std::istream& in) {
    in >> carID >> model >> make >> year >> pricePerDay >> capacity >> color;
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

// display case
void BaseCar::display() const {
    cout << "----------------------------------------\n";
    cout << "Car ID       : " << carID << endl;
    cout << "Model        : " << model << endl;
    cout << "Make         : " << make << endl;
    cout << "Year         : " << year << endl;
    cout << "Price Per Day: $" << pricePerDay << endl;
    cout << "Capacity     : " << capacity << " persons" << endl;
    cout << "Color        : " << color << endl;
    cout << "----------------------------------------\n";
}
