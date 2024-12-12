#include "Admin.h"
#include <iostream>
using namespace std;

// same thing here with the customer vs. admin account -> needs minor tweaking


Admin::Admin() {}

// Authenticate the password

bool Admin::authenticate(const string& password) const {
    return password == adminPassword;
}

// Add a car to the private inventory
void Admin::addCar(const shared_ptr<BaseCar>& car) {
    inventory.push_back(car);
    cout << "Car added to inventory.\n";
}

// List all cars in the private inventory
void Admin::listInventory() const {
    if (inventory.empty()) {
        cout << "Inventory is empty.\n";
        return;
    }
    cout << "Admin Inventory:\n";
    for (const auto& car : inventory) {
        car->display();
    }
}

// Process a payment -> payment processing class still needs to be made
// *** I think this will need to be edited ***
void Admin::processPayment(double amount) const {
    cout << "Payment of $" << amount << " processed successfully.\n";
}

void Admin::setInventory(std::vector<std::shared_ptr<BaseCar>> inv) {
    for (const auto& car : inv) {
        inventory.push_back(car);
    }
}