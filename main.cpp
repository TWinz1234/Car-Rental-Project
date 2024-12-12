// Updated main.cpp
#include <iostream>
#include <vector>
#include <memory>
#include <filesystem>
#include "admin.h"
#include "BaseCar.h"
#include "FuelCar.h"
#include "ElectricCar.h"
#include "Customer.h"
#include "Payment.h"

using namespace std;

void displayMainMenu();
void adminMenu(Admin& admin, vector<Customer>& customers, vector<shared_ptr<BaseCar>>& cars);
void customerMenu(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers);
void addCar(Admin& admin, vector<shared_ptr<BaseCar>>& cars);
void listCars(const vector<shared_ptr<BaseCar>>& cars);
void rentCar(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers);
void searchCars(const vector<shared_ptr<BaseCar>>& cars);

int main() {
    cout << "Starting Car Rental System...\n" << endl;

    string relativePath = "./data"; // Relative directory for all data files

    vector<Customer> customers = Customer::readFromFile(relativePath + "/customers.txt");
    vector<shared_ptr<BaseCar>> cars = BaseCar::readFromFile(relativePath + "/CarInventory.txt");

    Admin admin;
    admin.setInventory(cars);

    cout << "Loaded " << customers.size() << " customers and " << cars.size() << " cars.\n" << flush;

    int roleChoice;

    while (true) {
        displayMainMenu();
        cout << "Enter your choice: ";
        cin >> roleChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        if (roleChoice == 1) {
            customerMenu(cars, customers);
        } else if (roleChoice == 2) {
            string password;
            cout << "Enter admin password: ";
            cin >> password;

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

void displayMainMenu() {
    cout << "\nCar Rental System Menu:\n"
         << "1. Customer\n"
         << "2. Admin\n"
         << "3. Exit\n";
}

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

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }

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

void customerMenu(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers) {
    int choice;
    do {
        cout << "\nCustomer Menu:\n"
             << "1. View Cars\n"
             << "2. Rent a Car\n"
             << "3. Search Cars\n"
             << "4. Exit to Main Menu\n"
             << "Enter your choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again.\n";
            continue;
        }

        switch (choice) {
            case 1:
                listCars(cars);
                break;
            case 2:
                rentCar(cars, customers);
                break;
            case 3:
                searchCars(cars);
                break;
            case 4:
                cout << "Returning to main menu...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);
}

void addCar(Admin& admin, vector<shared_ptr<BaseCar>>& cars) {
    int carType;
    cout << "Enter Car Type (1 = Fuel, 2 = Electric): ";
    cin >> carType;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    int carID = cars.size() + 1;
    int year, capacity;
    double pricePerDay;
    string model, make, color;

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

    if (carType == 1) {
        double tankCapacity;
        string fuelType;
        cout << "Enter Fuel Type: ";
        cin >> fuelType;
        cout << "Enter Tank Capacity (gallons): ";
        cin >> tankCapacity;
        auto car = make_shared<FuelCar>(carID, model, make, year, pricePerDay, capacity, color, fuelType, tankCapacity);
        cars.push_back(car);
    } else if (carType == 2) {
        double batteryCapacity;
        int rangePerCharge;
        cout << "Enter Battery Capacity (kWh): ";
        cin >> batteryCapacity;
        cout << "Enter Range Per Charge (miles): ";
        cin >> rangePerCharge;
        auto car = make_shared<ElectricCar>(carID, model, make, year, pricePerDay, capacity, color, batteryCapacity, rangePerCharge);
        cars.push_back(car);
    } else {
        cout << "Invalid car type.\n";
        return;
    }

    admin.addCar(cars.back());
    cout << "Car added successfully.\n";
}

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

void rentCar(vector<shared_ptr<BaseCar>>& cars, vector<Customer>& customers) {
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

            Customer newCustomer;
            newCustomer.setId(customers.size() + 1);
            cout << "Enter your details:\n";
            cout << "Name: ";
            string name;
            cin >> name;
            newCustomer.setName(name);
            cout << "Contact Number: ";
            string contactNum;
            cin >> contactNum;
            newCustomer.setContactNum(contactNum);
            
            customers.push_back(newCustomer);
            
            Payment payment = Payment::add();
            payment.saveToLedger();

            cars.erase(it);
            return;
        }
    }

    cout << "Car with ID " << carID << " not found.\n";
}

void searchCars(const vector<shared_ptr<BaseCar>>& cars) {
    cout << "Enter search criteria (1 = Model, 2 = Capacity): ";
    int choice;
    cin >> choice;

    if (choice == 1) {
        string model;
        cout << "Enter model to search: ";
        cin >> model;
        for (const auto& car : cars) {
            if (car->getModel() == model) {
                car->display();
            }
        }
    } else if (choice == 2) {
        int capacity;
        cout << "Enter capacity to search: ";
        cin >> capacity;
        for (const auto& car : cars) {
            if (car->getCapacity() == capacity) {
                car->display();
            }
        }
    } else {
        cout << "Invalid choice.\n";
    }
}
