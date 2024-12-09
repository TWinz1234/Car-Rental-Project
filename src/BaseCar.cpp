#include "BaseCar.h"
#include "ElectricCar.h"
#include "FuelCar.h"

// Constructors
BaseCar::BaseCar()
{

}

BaseCar::BaseCar(int carID, string model, string make, int year, double pricePerDay, int capacity, string color)
{
    setCarID(carID);
    setModel(model);
    setMake(make);
    setYear(year);
    setPricePerDay(pricePerDay);
    setCapacity(capacity);
    setColor(color);
}

// Setter/getter functions
int BaseCar::getCarID() const
{
    return carID;
}

void BaseCar::setCarID(int newCarID)
{
    this->carID = newCarID;
}

string BaseCar::getModel() const
{
    return model;
}

void BaseCar::setModel(string newModel)
{
    this->model = newModel;
}

string BaseCar::getMake() const
{
    return make;
}

void BaseCar::setMake(string newMake)
{
    this->make = newMake;
}

int BaseCar::getYear() const
{
    return year;
}

void BaseCar::setYear(int newYear)
{
    this->year = newYear;
}

double BaseCar::getPricePerDay() const
{
    return pricePerDay;
}

void BaseCar::setPricePerDay(double newPricePerDay)
{
    this->pricePerDay = newPricePerDay;
}

int BaseCar::getCapacity() const
{
    return capacity;
}

void BaseCar::setCapacity(int newCapacity)
{
    this->capacity = newCapacity;
}

string BaseCar::getColor() const
{
    return color;
}

void BaseCar::setColor(string newColor)
{
    this->color = newColor;
}

string BaseCar::getType() const
{
    return "base";
}


// Serialize/deserialize
void BaseCar::serialize(std::ostream& out) const
{
    out << carID << " " << model << " " << make << " " << year << " " << pricePerDay << " " << capacity << " " << color << " ";
}

void BaseCar::deserialize(std::istream& in)
{
    in >> carID >> model >> make >> year >> pricePerDay >> capacity >> color;
}

// Read/write to/from a file
void BaseCar::saveToFile(string fileName, const vector<shared_ptr<BaseCar>> cars)
{
    ofstream outfile(fileName);
    for(const auto& car : cars)
    {
        outfile << car->getType() << " ";
        car->serialize(outfile);
        outfile << "\n";
    }
    outfile.close();
    cout << "Cars added to inventory" << endl;
}

vector<shared_ptr<BaseCar>> BaseCar::readFromFile(const string& fileName)
{
    ifstream file(fileName);
    
    vector<shared_ptr<BaseCar>> cars;
    string type;
    
    while(!file.eof())
    {
        string line;
        getline(file, line);
        //cout << "line is " << line << endl;
        if(line.length() < 1)
        {
            continue;
        }
        istringstream iss(line);
        
        iss >> type;
        shared_ptr<BaseCar> car;
        if(type == "electric")
        {
            car = make_shared<ElectricCar>();
        }
        else if(type == "fuel")
        {
            car = make_shared<FuelCar>();
        }
        else
        {
            cout << "Error" << endl;
        }
        car->deserialize(iss);
        cars.push_back(car);
    }
    
    return cars;
}