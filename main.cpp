#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include "BaseCar.h"
#include "FuelCar.h"
#include "ElectricCar.h"
#include "Customer.h"
#include "Admin.h"

using namespace std;

void displayMainMenu();

void adminMenu(Admin& admin, vector<Customer>& customers, vector<shared_ptr<BaseCar>>& cars);
void customerMenu(vector<shared_ptr<BaseCar>>& cars);
void addCar(Admin& admin, vector<shared_ptr<BaseCar>>& cars);
void listCars(const vector<shared_ptr<BaseCar>>& cars);
void rentCar(vector<shared_ptr<BaseCar>>& cars);

int main() {
    cout << "Starting Car Rental System...\n" << endl;

    // figure out where the file system is running
    cout << "Current working directory: " << filesystem::current_path() << endl;

    // load data - not sure how to make this so it isn't local
    // windows prefix:
    string customerFilePrefix = "../../..";
    // mac prefix:
    // string customerFilePrefix = "..";
    vector<Customer> customers = Customer::readFromFile(customerFilePrefix + "/customers.txt");
    vector<shared_ptr<BaseCar>> cars = BaseCar::readFromFile(customerFilePrefix + "/CarInventory.txt");

    cout << "length of cars: " << cars.size() << endl;

    Admin admin;
    admin.setInventory(cars);

    cout << "Loaded " << customers.size() << " customers and " << cars.size() << " cars.\n" << flush;

    // choose between admin or customer
    int roleChoice;

    while (true) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> roleChoice;

        if (cin.fail()) {
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (roleChoice == 1) {
            customerMenu(cars);
        } else if (roleChoice == 2) {
            string password;
            cout << "Enter admin password: ";
            cin >> password;

            // authenticate admin passwrod (admin123)
            if (admin.authenticate(password)) {
                adminMenu(admin, customers, cars);
            } else {
                cout << "Invalid password. Access denied.\n";
            }
        } else if (roleChoice == 3) {
            cout << "Exiting the system. Goodbye!\n";
            break;
        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}

// main menu -> run relevant functions
void displayMainMenu() {
    cout << "\nCar Rental System Menu:\n"
         << "1. Customer\n"
         << "2. Admin\n"
         << "3. Exit\n";
}

// reference to admin, vectors of customer and basecar
void adminMenu(Admin& admin, vector<Customer>& customers, vector<shared_ptr<BaseCar>>& cars) {
    int choice;
    do {
        cout << "\nAdmin Menu:\n"
             << "1. View Inventory\n"
             << "2. Add Car to Inventory\n"
             << "3. View Customer Data\n"
             << "4. Exit to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        // input validation -> clear the cin, repeat
        if (cin.fail()) {
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        // use a switch case for users, populate relevant lists
        switch (choice) {
            case 1:
                admin.listInventory();
                break;
            case 2:
                addCar(admin, cars);
                break;
            case 3:
                if (customers.empty()) {
                    cout << "No customers available.\n";
                } else {
                    cout << "Customer List:\n";
                    for (const auto& customer : customers) {
                        customer.display();
                    }
                }
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

// populate customer menu
void customerMenu(vector<shared_ptr<BaseCar>>& cars) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n"
             << "1. View Cars\n"
             << "2. Rent a Car\n"
             << "3. Exit to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        // use case for customer
        switch (choice) {
            case 1:
                listCars(cars);
                break;
            case 2:
                rentCar(cars);
                break;
            case 3:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);
}

// add the car to the relevant inventory
// *** to be fixed ***
// this logic needs to be fixed -> if we enter whether it's electric or fuel, it needs to take that value and populate different menus
void addCar(Admin& admin, vector<shared_ptr<BaseCar>>& cars) {
    int carType;
    cout << "Enter Car Type (1 = Fuel, 2 = Electric): ";
    cin >> carType;

    // this part works
    if (carType == 1) {
        int carID, year, capacity;
        double pricePerDay, tankCapacity;
        string model, make, color, fuelType;

        cout << "Enter Car ID: ";
        cin >> carID;
        cout << "Enter Model: ";
        cin >> model;
        cout << "Enter Make: ";
        cin >> make;
        cout << "Enter Year: ";
        cin >> year;
        cout << "Enter Price Per Day: ";
        cin >> pricePerDay;
        cout << "Enter Capacity: ";
        cin >> capacity;
        cout << "Enter Color: ";
        cin >> color;
        cout << "Enter Tank Capacity (gallons): ";
        cin >> tankCapacity;

        // allocate and initiate in one step with make_shared
        // auto allows it to take value of <FuelCar>
        auto car = make_shared<FuelCar>(carID, model, make, year, pricePerDay, capacity, color, fuelType, tankCapacity);
        admin.addCar(car);
        cars.push_back(car);
    } else if (carType == 2) {
        int carID, year, capacity, rangePerCharge;
        double pricePerDay, batteryCapacity;
        string model, make, color;

        cout << "Enter Car ID: ";
        cin >> carID;
        cout << "Enter Model: ";
        cin >> model;
        cout << "Enter Make: ";
        cin >> make;
        cout << "Enter Year: ";
        cin >> year;
        cout << "Enter Price Per Day: ";
        cin >> pricePerDay;
        cout << "Enter Capacity: ";
        cin >> capacity;
        cout << "Enter Color: ";
        cin >> color;
        cout << "Enter Battery Capacity (kWh): ";
        cin >> batteryCapacity;
        cout << "Enter Range Per Charge (miles): ";
        cin >> rangePerCharge;

        auto car = make_shared<ElectricCar>(carID, model, make, year, pricePerDay, capacity, color, batteryCapacity, rangePerCharge);
        admin.addCar(car);
        cars.push_back(car);
    } else {
        cout << "Invalid car type.\n";
    }
}

// Displays the list of cars available in the inventory
void listCars(const vector<shared_ptr<BaseCar>>& cars) {
    if (cars.empty()) {
        cout << "No cars available in the inventory.\n";
        return;
    }
    cout << "Cars available for rent:\n";
    for (const auto& car : cars) {
        car->display();
    }
}

// Rent car processing
void rentCar(vector<shared_ptr<BaseCar>>& cars) {
    // display empty if no cars are there
    if (cars.empty()) {
        cout << "No cars available to rent.\n";
        return;
    }

    int carID;
    cout << "Enter the Car ID of the car you want to rent: ";
    cin >> carID;

    for (auto it = cars.begin(); it != cars.end(); ++it) {
        if ((*it)->getCarID() == carID) {
            cout << "You have rented the following car:\n";
            (*it)->display();
            cars.erase(it); // Remove the car from inventory
            return;
        }
    }

    cout << "Car with ID " << carID << " not found.\n";
}
