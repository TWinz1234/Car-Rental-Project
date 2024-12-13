#include "Admin.h"
#include "FuelCar.h"
#include "ElectricCar.h"
#include <iostream>
using namespace std;

// same thing here with the customer vs. admin account -> needs minor adjustments
Admin::Admin() {}

// Authenticate the admin password -> return to menu if it doesn't work
bool Admin::authenticate(const string& password) const {
    return password == adminPassword;
}

// Add a car to the private inventory
// use vector beccause we weren't given a specific size limit, otherwise we should use an array
void Admin::addCar(const shared_ptr<BaseCar>& car) {
    inventory.push_back(car);
    cout << "Car added to inventory.\n";
}

// List all cars in the private inventory -> admin access only
void Admin::listInventory() const {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }

    cout << "\nAdmin Inventory:\n";
    cout << "------------------------------------------------------\n";
    for (const auto& car : inventory) {
        cout << "Car ID: " << car->getCarID() << "\n";
        cout << "Model: " << car->getModel() << "\n";
        cout << "Make: " << car->getMake() << "\n";
        cout << "Year: " << car->getYear() << "\n";
        cout << "Price Per Day: $" << car->getPricePerDay() << "\n";
        cout << "Capacity: " << car->getCapacity() << "\n";
        cout << "Color: " << car->getColor() << "\n";
        cout << "Rented: " << (car->isRented() ? "Yes" : "No") << "\n";

        // Additional details for specific car types
        if (auto fuelCar = dynamic_pointer_cast<FuelCar>(car)) {
            cout << "Fuel Type: " << fuelCar->getFuelType() << "\n";
            cout << "Tank Capacity: " << fuelCar->getTankCapacity() << " gallons\n";
        } else if (auto electricCar = dynamic_pointer_cast<ElectricCar>(car)) {
            cout << "Battery Capacity: " << electricCar->getBatteryCapacity() << " kWh\n";
            cout << "Range: " << electricCar->getRangePerCharge() << " miles\n";
        }
        cout << "------------------------------------------------------\n";
    }
}


// Process a payment -> show confirmation 
// *** I think this will need to be edited ***
void Admin::processPayment(double amount) const {
    cout << "Payment of $" << amount << " processed successfully.\n";
}

void Admin::setInventory(std::vector<std::shared_ptr<BaseCar>> inv) {
    for (const auto& car : inv) {
        inventory.push_back(car);
    }
}
